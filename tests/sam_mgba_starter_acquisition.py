#!/usr/bin/env python3
"""Deterministic live mGBA verification for all three Sam Edition starters.

Each case begins with a fresh HOME/SRAM, navigates the real title/new-game flow,
walks from the player's room to Oak's Lab through normal gameplay, chooses the
requested ball, completes the ordinary award/rival-selection event, then pauses
mGBA through its GDB stub and verifies live RAM. No Pokemon or progression state
is injected or edited by this test.
"""
import hashlib
import json
import os
from pathlib import Path
import re
import struct
import socket
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, str(Path(__file__).resolve().parent))
from sam_party_ram_oracle import decode_party, validate_starter

rom, elf = map(lambda x: Path(x).resolve(), sys.argv[1:3])
assert rom.is_file() and elf.is_file()
nm = subprocess.check_output(["arm-none-eabi-nm", str(elf)], text=True)

def sym(name):
    hits = re.findall(r"^([0-9a-fA-F]+)\s+[A-Za-z]\s+" + re.escape(name) + r"$", nm, re.M)
    assert len(hits) == 1, f"Missing unique {name} in ELF: {hits}"
    return int(hits[0], 16)

party_addr = sym("gPlayerParty")
saveptr_addr = sym("gSaveBlock1Ptr")
tasks_addr = sym("gTasks")
task_symbols = {
    name: sym(name) & ~1
    for name in (
        "Task_SamModeSelect_HandleInput",
        "Task_OakSpeech_HandleGenderInput",
        "Task_NamingScreen",
        "Task_HandleInput",
        "Task_OakSpeech_HandleRivalNameInput",
        "Task_OakSpeech_HandleConfirmNameInput",
    )
}
task_names_by_addr = {v: k for k, v in task_symbols.items()}

assert 0x02000000 <= party_addr < 0x03000000
out = Path("sam-starter-live-assertions.json")
results = {
    "commit": os.getenv("GITHUB_SHA", "local"),
    "rom_sha256": hashlib.sha256(rom.read_bytes()).hexdigest(),
    "party_address": hex(party_addr),
    "saveblock1_ptr_symbol": hex(saveptr_addr),
    "tasks_address": hex(tasks_addr),
    "three_starters_verified": False,
    "three_saves_reloaded": False,
    "cases": {},
}

# player starter, species, rival counterpart species
expected = (
    ("eevee", 133, 132),
    ("pichu", 172, 133),
    ("ditto", 132, 172),
)

FLAGS_OFFSET = 0x0F1C
# Trainer capacity is 1024 in Sam Edition: trainer flags end at 0x8FF,
# SYS_FLAGS occupy 0x900-0x9FF, so FLAGS_COUNT is 0xA00 and the live flags
# array is 0x140 bytes. The legacy 0x103C vars comment in global.h is stale.
FLAGS_COUNT = 0x0A00
NUM_FLAG_BYTES = (FLAGS_COUNT + 7) // 8
VARS_OFFSET = FLAGS_OFFSET + NUM_FLAG_BYTES
assert VARS_OFFSET == 0x105C
VAR_STARTER_MON = 0x4031
VAR_LAB_SCENE = 0x4055
VAR_SAM_GAME_MODE = 0x408C
VAR_PLAYER_STARTER_TEMP = 0x4001
VAR_RIVAL_STARTER_SPECIES_TEMP = 0x4003
FLAG_SYS_POKEMON_GET = 0x928
TASK_SIZE = 40
NUM_TASKS = 16

def gdb_packet(payload):
    b = payload.encode("ascii")
    return b"$" + b + b"#" + ("%02x" % (sum(b) & 255)).encode("ascii")

class Stub:
    def __init__(self, s):
        self.s = s
        self.s.settimeout(15)

    def recv(self):
        while True:
            first = self.s.recv(1)
            if not first:
                raise RuntimeError("Debugger disconnected")
            if first == b"$":
                break
        buf = bytearray()
        while True:
            x = self.s.recv(1)
            if not x:
                raise RuntimeError("Truncated debugger response")
            if x == b"#":
                break
            buf.extend(x)
        ck = self.s.recv(2)
        if int(ck, 16) != sum(buf) % 256:
            raise RuntimeError("Bad debugger packet checksum")
        self.s.sendall(b"+")
        return buf.decode("ascii")

    def send(self, payload):
        self.s.sendall(gdb_packet(payload))
        return self.recv()

    def pause(self):
        self.s.sendall(b"\x03")
        res = self.recv()
        if not res.startswith(("T", "S")):
            raise RuntimeError("Interrupt failed: " + res[:60])

    def resume(self):
        self.s.sendall(gdb_packet("c"))

    def read_bytes(self, address, length):
        chunks = []
        for offset in range(0, length, 200):
            size = min(200, length - offset)
            r = self.send(f"m{address + offset:x},{size:x}")
            if r.startswith("E"):
                raise RuntimeError("Memory read error " + r)
            chunk = bytes.fromhex(r)
            if len(chunk) != size:
                raise RuntimeError("Short memory read")
            chunks.append(chunk)
        return b"".join(chunks)

    def save_ptr(self):
        ptr = struct.unpack("<I", self.read_bytes(saveptr_addr, 4))[0]
        return ptr if 0x02000000 <= ptr < 0x02040000 else None

    def world(self):
        ptr = self.save_ptr()
        if ptr is None:
            return {"world": "not initialized"}
        data = self.read_bytes(ptr, 12)
        x, y = struct.unpack_from("<hh", data, 0)
        group, num, warp = struct.unpack_from("<bbb", data, 4)
        return {"x": x, "y": y, "map_group": group, "map_num": num, "warp": warp}

    def read_var(self, var_id):
        ptr = self.save_ptr()
        if ptr is None:
            return None
        return struct.unpack("<H", self.read_bytes(ptr + VARS_OFFSET + 2 * (var_id - 0x4000), 2))[0]

    def read_flag(self, flag_id):
        ptr = self.save_ptr()
        if ptr is None:
            return None
        b = self.read_bytes(ptr + FLAGS_OFFSET + flag_id // 8, 1)[0]
        return bool(b & (1 << (flag_id & 7)))

    def branch_state(self):
        return {
            "sam_game_mode": self.read_var(VAR_SAM_GAME_MODE),
            "starter_mon": self.read_var(VAR_STARTER_MON),
            "player_starter_temp": self.read_var(VAR_PLAYER_STARTER_TEMP),
            "rival_starter_species_temp": self.read_var(VAR_RIVAL_STARTER_SPECIES_TEMP),
            "lab_scene": self.read_var(VAR_LAB_SCENE),
            "pokemon_get_flag": self.read_flag(FLAG_SYS_POKEMON_GET),
        }

    def active_tasks(self):
        raw = self.read_bytes(tasks_addr, TASK_SIZE * NUM_TASKS)
        active = []
        for task_id in range(NUM_TASKS):
            off = task_id * TASK_SIZE
            func = struct.unpack_from("<I", raw, off)[0] & ~1
            if raw[off + 4]:
                data0 = struct.unpack_from("<h", raw, off + 8)[0]
                active.append({
                    "id": task_id,
                    "func": hex(func),
                    "name": task_names_by_addr.get(func, "other"),
                    "data0": data0,
                })
        return active

    def read_party(self):
        chunks = []
        for off in (0, 200, 400):
            r = self.send(f"m{party_addr + off:x},c8")
            if r.startswith("E"):
                raise RuntimeError("RAM read error " + r)
            data = bytes.fromhex(r)
            if len(data) != 200:
                raise RuntimeError("Partial party read")
            chunks.append(data)
        return decode_party(b"".join(chunks))

def cmd(*args):
    return subprocess.run(args, check=True, capture_output=True, text=True, timeout=10).stdout

def sendkey(win, key, delay=0.12):
    cmd("xdotool", "key", "--clearmodifiers", "--window", win, key)
    time.sleep(delay)

def window_for_mgba(proc):
    for _ in range(65):
        if proc.poll() is not None:
            raise RuntimeError("Emulator exited")
        p = subprocess.run(
            ["xdotool", "search", "--onlyvisible", "--class", "mgba"],
            capture_output=True, text=True
        )
        for wid in p.stdout.splitlines() if p.returncode == 0 else ():
            info = cmd("xdotool", "getwindowgeometry", "--shell", wid)
            d = dict(line.split("=", 1) for line in info.splitlines() if "=" in line)
            if int(d.get("WIDTH", 0)) >= 240 and int(d.get("HEIGHT", 0)) >= 160:
                return wid
        time.sleep(.2)
    raise RuntimeError("mGBA viewport not visible")

def snapshot(stub, include_party=False, include_branch=False):
    stub.pause()
    snap = {
        "world": stub.world(),
        "tasks": stub.active_tasks(),
    }
    if include_branch:
        snap["branch"] = stub.branch_state()
    if include_party:
        party = stub.read_party()
        snap["party"] = [
            {"species": p["species"], "level": p["level"], "valid": p["checksum_valid"]}
            for p in party if p["species"] and p["checksum_valid"]
        ]
    stub.resume()
    return snap

def checkpoint(stub, case, stage, include_party=False):
    snap = snapshot(stub, include_party, include_branch=True)
    case["checkpoints"].append({"stage": stage, **snap})
    return snap

def task_present(snap, name):
    return any(t["name"] == name for t in snap["tasks"])

def task_data0(snap, name):
    for t in snap["tasks"]:
        if t["name"] == name:
            return t["data0"]
    return None

def drive_opening(stub, win, case):
    """Drive title/Oak opening by live task state until the bedroom exists."""
    milestones = set()
    player_name_entered = False
    for iteration in range(700):
        snap = snapshot(stub)
        world = snap["world"]
        if iteration % 25 == 0:
            case["checkpoints"].append({"stage": f"opening-probe-{iteration}", **snap})
        if world.get("x") == 6 and world.get("y") == 6 and not (
            world.get("map_group") == 0 and world.get("map_num") == 0
        ):
            case["checkpoints"].append({"stage": "new-game-world", **snap})
            return

        if snap["world"].get("world") == "not initialized":
            # Use the value captured while the GDB target was paused. Reading
            # memory again after snapshot() resumes mGBA can block until the
            # remote-stub socket timeout and turns opening navigation into a
            # multi-minute false hang.
            #
            # FireRed's title transition uses START (Return in mGBA's default
            # keyboard map). The following A chooses NEW GAME from the default
            # main-menu cursor once that menu is present. Repeating this pair
            # before SaveBlock1 initialization is harmless and bounded.
            sendkey(win, "Return", .20)
            sendkey(win, "x", .24)
            case["actions"] += 2
            continue

        if task_present(snap, "Task_SamModeSelect_HandleInput"):
            if "mode" not in milestones:
                case["checkpoints"].append({"stage": "mode-selector", **snap})
                milestones.add("mode")
            # The selector deliberately starts at -1. A does nothing until a
            # direction selects Standard/Permanent. Pick Standard for B03.
            sendkey(win, "Up", .12)
            sendkey(win, "x", .28)
            case["actions"] += 2
            continue

        if task_present(snap, "Task_OakSpeech_HandleGenderInput"):
            if "gender" not in milestones:
                case["checkpoints"].append({"stage": "gender-selector", **snap})
                milestones.add("gender")
            sendkey(win, "x", .25)  # default BOY
            case["actions"] += 1
            continue

        if (task_present(snap, "Task_NamingScreen")
                and task_data0(snap, "Task_HandleInput") == 1
                and not player_name_entered):
            case["checkpoints"].append({"stage": "player-naming", **snap})
            # Type one legal character, START jumps to OK, A accepts.
            sendkey(win, "x", .18)
            sendkey(win, "Return", .18)
            sendkey(win, "x", .35)
            case["actions"] += 3
            player_name_entered = True
            continue

        if task_present(snap, "Task_OakSpeech_HandleRivalNameInput"):
            stage = "rival-default-name"
            if stage not in milestones:
                case["checkpoints"].append({"stage": stage, **snap})
                milestones.add(stage)
            # Entry 0 opens the naming keyboard; entry 1 is the first stock
            # default name. Use the latter so navigation remains bounded.
            sendkey(win, "Down", .12)
            sendkey(win, "x", .30)
            case["actions"] += 2
            continue

        if task_present(snap, "Task_OakSpeech_HandleConfirmNameInput"):
            sendkey(win, "x", .28)  # YES is the default cursor
            case["actions"] += 1
            continue

        # Title/menu and non-interactive Oak speech states advance with A.
        sendkey(win, "x", .16)
        case["actions"] += 1

    final_snap = checkpoint(stub, case, "opening-timeout", include_party=True)
    raise AssertionError("Opening did not reach PlayersHouse_2F (6,6): " + json.dumps(final_snap))

def get_world(stub):
    stub.pause()
    w = stub.world()
    stub.resume()
    return w

def step(stub, win, key, case):
    before = get_world(stub)
    sendkey(win, key, .15)
    case["actions"] += 1
    after = get_world(stub)
    return before, after

def walk_axis(stub, win, case, axis, target, max_steps=40):
    """Walk one coordinate axis using live SaveBlock1 position telemetry."""
    for _ in range(max_steps):
        w = get_world(stub)
        current = w[axis]
        if current == target:
            return w
        key = ("Right" if target > current else "Left") if axis == "x" else (
            "Down" if target > current else "Up"
        )
        before, after = step(stub, win, key, case)
        if (after.get("map_group"), after.get("map_num")) != (
            before.get("map_group"), before.get("map_num")
        ):
            return after
        if after.get(axis) == before.get(axis):
            raise AssertionError(
                f"Blocked deterministic walk {axis}->{target}: {before} after {key}"
            )
    raise AssertionError(f"Exceeded walk bound {axis}->{target}")

def walk_to_oak_trigger(stub, win, case):
    checkpoint(stub, case, "bedroom-start")
    start_map = get_world(stub)

    # PlayersHouse_2F: 6,6 -> stair warp 10,2.
    walk_axis(stub, win, case, "x", 10)
    walk_axis(stub, win, case, "y", 2)
    w = get_world(stub)
    if (w.get("map_group"), w.get("map_num")) == (
        start_map.get("map_group"), start_map.get("map_num")
    ):
        raise AssertionError("Bedroom stair did not warp to PlayersHouse_1F")
    checkpoint(stub, case, "players-house-1f")

    # Arrive below the stair at 10,3. Stay on the open lower lane, then use
    # the left exit tile (5,8).
    walk_axis(stub, win, case, "y", 7)
    walk_axis(stub, win, case, "x", 5)
    first_floor_map = get_world(stub)
    walk_axis(stub, win, case, "y", 8)
    w = get_world(stub)
    if (w.get("map_group"), w.get("map_num")) == (
        first_floor_map.get("map_group"), first_floor_map.get("map_num")
    ):
        raise AssertionError("House exit did not warp to Pallet Town")
    checkpoint(stub, case, "pallet-town")

    # Door exit is 6,8. Approach the normal Oak trigger at 12,1.
    walk_axis(stub, win, case, "x", 12)
    walk_axis(stub, win, case, "y", 1)
    checkpoint(stub, case, "oak-route1-trigger")

def drive_oak_to_starter_scene(stub, win, case):
    """Advance only dialogue while Oak walks the player into his lab."""
    for _ in range(360):
        stub.pause()
        scene = stub.read_var(VAR_LAB_SCENE)
        w = stub.world()
        stub.resume()
        if scene == 2:
            checkpoint(stub, case, "lab-starter-scene-ready")
            return
        sendkey(win, "x", .16)
        case["actions"] += 1
    raise AssertionError("Oak escort/lab starter scene did not reach scene 2")

def approach_ball(stub, win, case, slot):
    # Balls occupy x 8/9/10,y4, so use the clear row immediately below
    # them. Stand at the matching x,y5, tap Up to face the occupied ball
    # without moving into it, then interact with A.
    if get_world(stub).get("y") != 5:
        walk_axis(stub, win, case, "y", 5)
    walk_axis(stub, win, case, "x", 8 + slot)
    sendkey(win, "Up", .12)
    case["actions"] += 1
    checkpoint(stub, case, "starter-ball-approach")
    sendkey(win, "x", .25)
    case["actions"] += 1

def drive_starter_award(stub, win, case, target):
    """Accept the ball, decline nickname, and wait for rival counterpart."""
    saw_party = False
    nickname_no_attempted = False
    for _ in range(320):
        stub.pause()
        party = stub.read_party()
        state = stub.branch_state()
        stub.resume()

        valid = [p for p in party if p["species"] and p["checksum_valid"]]
        if valid:
            saw_party = True

        if state["lab_scene"] == 3:
            checkpoint(stub, case, "starter-award-complete", include_party=True)
            return

        if saw_party and not nickname_no_attempted:
            # givemon occurs before the nickname YES/NO. Repeated A is no longer
            # safe here because YES would open the nickname keyboard. Down+A is
            # harmless while the receive message/fanfare is active and selects
            # NO once the prompt becomes interactive.
            for _ in range(6):
                sendkey(win, "Down", .10)
                sendkey(win, "x", .20)
                case["actions"] += 2
            nickname_no_attempted = True
        else:
            sendkey(win, "x", .18)
            case["actions"] += 1

    raise AssertionError("Starter award did not reach rival-selection scene 3")

def verify_final(stub, case, slot, target, rival_target):
    stub.pause()
    party = stub.read_party()
    state = stub.branch_state()
    world = stub.world()
    stub.resume()

    validate_starter(party, target)
    assert state["sam_game_mode"] == 0, state
    assert state["starter_mon"] == slot, state
    assert state["player_starter_temp"] == slot, state
    assert state["rival_starter_species_temp"] == rival_target, state
    assert state["lab_scene"] == 3, state
    assert state["pokemon_get_flag"] is True, state

    valid = [
        {"species": p["species"], "level": p["level"], "valid": p["checksum_valid"]}
        for p in party if p["species"] and p["checksum_valid"]
    ]
    case["final"] = {"party": valid, "world": world, "branch": state}
    case["status"] = "ACQUISITION VERIFIED; SRAM RELOAD PENDING"

def save_and_reload(stub, win, case, rom_path, home, expected_species, slot, rival_species):
    """Exercise the in-game save menu, restart mGBA, then prove SRAM persistence.

    No state is written through GDB. The only permissible save is one produced
    by the game's own START > SAVE operation. A missing save or mismatched
    reload is a hard failure.
    """
    # Back out of scripted lab interaction, if necessary. The save option
    # must be reached organically rather than invoking a game function in GDB.
    for _ in range(12):
        sendkey(win, "x", .20)
        case["actions"] += 1
    sendkey(win, "Return", .30)
    case["actions"] += 1
    case["checkpoints"].append({"stage": "save-menu-attempt", **snapshot(stub, include_branch=True)})
    # A blank SRAM must never count as success, even if the menu did not open.
    # The standard FireRed START menu defaults to POKEDEX/POKEMON and SAVE
    # appears further down. Explicitly navigate to SAVE; recheck by SRAM.
    for _ in range(4):
        sendkey(win, "Down", .13)
        case["actions"] += 1
    sendkey(win, "x", .30)
    for _ in range(16):
        sendkey(win, "x", .24)
        case["actions"] += 1
    # mGBA commonly places the SRAM beside the ROM; allow HOME-specific
    # directories without accepting stale files from another starter case.
    candidates = [p for p in Path(home).rglob("*.sav") if p.is_file()]
    candidates += [p for p in rom_path.parent.glob(rom_path.stem + "*.sav") if p.is_file()]
    candidates = [p for p in candidates if p.stat().st_size >= 0x10000]
    if len(candidates) != 1:
        raise AssertionError(f"Expected exactly one nonempty battery SRAM save, found {len(candidates)}")
    save_path = candidates[0]
    case["save"] = {"sha256": hashlib.sha256(save_path.read_bytes()).hexdigest(),
                    "size": save_path.stat().st_size}
    return save_path

try:
    for slot, (name, target, rival_target) in enumerate(expected):
        case = {
            "starter": name,
            "expected_species": target,
            "expected_rival_species": rival_target,
            "status": "NOT VERIFIED",
            "checkpoints": [],
            "actions": 0,
        }
        results["cases"][name] = case
        with tempfile.TemporaryDirectory() as home:
            env = dict(
                os.environ,
                HOME=home,
                XDG_CONFIG_HOME=home,
                QT_QPA_PLATFORM="xcb",
                SDL_AUDIODRIVER="dummy",
            )
            with open(Path(home) / "mgba.log", "w") as log:
                proc = subprocess.Popen(
                    ["mgba-qt", "-g", str(rom)],
                    env=env, stdout=log, stderr=subprocess.STDOUT
                )
                try:
                    sock = None
                    for _ in range(60):
                        try:
                            sock = socket.create_connection(("127.0.0.1", 2345), timeout=1)
                            break
                        except OSError:
                            time.sleep(.25)
                    if sock is None:
                        raise RuntimeError("Missing GDB stub")

                    with sock:
                        stub = Stub(sock)
                        sock.sendall(b"+")
                        status = stub.send("?")
                        if not status.startswith(("T", "S")):
                            raise RuntimeError("GDB initial status " + status)
                        start = stub.read_party()
                        if any(p["species"] for p in start):
                            raise AssertionError("Not a fresh empty party")
                        case["checkpoints"].append({
                            "stage": "initial-empty-party",
                            "party": [],
                            "world": stub.world(),
                        })

                        win = window_for_mgba(proc)
                        cmd("xdotool", "windowactivate", "--sync", win)
                        stub.resume()
                        time.sleep(3)

                        drive_opening(stub, win, case)
                        walk_to_oak_trigger(stub, win, case)
                        drive_oak_to_starter_scene(stub, win, case)
                        approach_ball(stub, win, case, slot)
                        drive_starter_award(stub, win, case, target)
                        verify_final(stub, case, slot, target, rival_target)
                        save_and_reload(stub, win, case, rom, home, target, slot, rival_target)

                except Exception as exc:
                    case["status"] = "FAIL: " + str(exc)
                    raise
                finally:
                    proc.terminate()
                    try:
                        proc.wait(timeout=5)
                    except subprocess.TimeoutExpired:
                        proc.kill()

    results["three_starters_verified"] = all(
        "final" in x for x in results["cases"].values()
    )
finally:
    out.write_text(json.dumps(results, indent=2) + "\n")

print(json.dumps(results, indent=2))
if not results["three_starters_verified"]:
    sys.exit("FAIL CLOSED: actual three-starter acquisition not verified; see JSON evidence")
