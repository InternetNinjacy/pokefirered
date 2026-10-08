#!/usr/bin/env python3
"""Genuine, fail-closed starter acquisition exploration on three fresh mGBA runs.

Drives real keyboard controls in mGBA, pauses via GDB and reads real party
bytes. Never reports a starter PASS without a valid decoded level-5 party.
A bounded action script is explicitly exploratory, not a guaranteed route.
"""
import hashlib
import json
import os
from pathlib import Path
import re
import socket
import subprocess
import sys
import tempfile
import time
sys.path.insert(0,str(Path(__file__).resolve().parent))
from sam_party_ram_oracle import decode_party, validate_starter

rom, elf=map(lambda x:Path(x).resolve(),sys.argv[1:3])
assert rom.is_file() and elf.is_file()
nm=subprocess.check_output(["arm-none-eabi-nm",str(elf)],text=True)
m=re.findall(r"^([0-9a-fA-F]+)\s+[A-Za-z]\s+gPlayerParty$",nm,re.M)
assert len(m)==1, "Missing unique gPlayerParty in ELF"
addr=int(m[0],16)
assert 0x02000000<=addr<0x03000000
out=Path("sam-starter-live-assertions.json")
results={"commit":os.getenv("GITHUB_SHA","local"),
         "rom_sha256":hashlib.sha256(rom.read_bytes()).hexdigest(),
         "party_address":hex(addr),"three_starters_verified":False,"cases":{}}
expected=(("eevee",133),("pichu",172),("ditto",132))

def gdb_packet(payload):
    b=payload.encode("ascii")
    return b"$"+b+b"#"+("%02x"%(sum(b)&255)).encode("ascii")

class Stub:
    def __init__(self,s):self.s=s;self.s.settimeout(15)
    def recv(self):
        while True:
            first=self.s.recv(1)
            if not first:raise RuntimeError("Debugger disconnected")
            if first==b"$":break
        buf=bytearray()
        while True:
            x=self.s.recv(1)
            if not x:raise RuntimeError("Truncated debugger response")
            if x==b"#":break
            buf.extend(x)
        ck=self.s.recv(2)
        if int(ck,16)!=sum(buf)%256:raise RuntimeError("Bad debugger packet checksum")
        self.s.sendall(b"+")
        return buf.decode("ascii")
    def send(self,payload):
        self.s.sendall(gdb_packet(payload))
        return self.recv()
    def pause(self):
        self.s.sendall(b"\x03")
        res=self.recv()
        if not res.startswith(("T","S")):raise RuntimeError("Interrupt failed: "+res[:60])
    def resume(self):
        # 'c' has no synchronous response until the target stops.
        self.s.sendall(gdb_packet("c"))
        return
    def read_party(self):
        chunks=[]
        for off in (0,200,400):
            r=self.send(f"m{addr+off:x},c8")
            if r.startswith("E"):raise RuntimeError("RAM read error "+r)
            data=bytes.fromhex(r)
            if len(data)!=200:raise RuntimeError("Partial party read")
            chunks.append(data)
        return decode_party(b"".join(chunks))

def cmd(*args):
    return subprocess.run(args,check=True,capture_output=True,text=True,timeout=10).stdout

def sendkey(win,key,delay=0.12):
    cmd("xdotool","key","--clearmodifiers","--window",win,key)
    time.sleep(delay)

def window_for_mgba(proc):
    for _ in range(65):
        if proc.poll() is not None:raise RuntimeError("Emulator exited")
        p=subprocess.run(["xdotool","search","--onlyvisible","--class","mgba"],
                         capture_output=True,text=True)
        for wid in p.stdout.splitlines() if p.returncode==0 else ():
            info=cmd("xdotool","getwindowgeometry","--shell",wid)
            d=dict(line.split("=",1) for line in info.splitlines() if "=" in line)
            if int(d.get("WIDTH",0))>=240 and int(d.get("HEIGHT",0))>=160:
                return wid
        time.sleep(.2)
    raise RuntimeError("mGBA viewport not visible")

def inspect(stub,case,stage,target):
    stub.pause()
    party=stub.read_party()
    valid=[{"species":p["species"],"level":p["level"],"valid":p["checksum_valid"]}
           for p in party if p["species"] and p["checksum_valid"]]
    case["checkpoints"].append({"stage":stage,"party":valid})
    try:
        validate_starter(party,target)
        case["status"]="PASS: live emulator RAM confirms one level-5 "+case["starter"]
        return True
    except AssertionError:
        stub.resume()
        return False

try:
    for slot,(name,target) in enumerate(expected):
        case={"starter":name,"status":"NOT VERIFIED","checkpoints":[],"actions":0}
        results["cases"][name]=case
        with tempfile.TemporaryDirectory() as home:
            env=dict(os.environ,HOME=home,XDG_CONFIG_HOME=home,
                     QT_QPA_PLATFORM="xcb",SDL_AUDIODRIVER="dummy")
            with open(Path(home)/"mgba.log","w") as log:
                proc=subprocess.Popen(["mgba-qt","-g",str(rom)],env=env,
                                      stdout=log,stderr=subprocess.STDOUT)
                try:
                    sock=None
                    for _ in range(60):
                        try:
                            sock=socket.create_connection(("127.0.0.1",2345),timeout=1);break
                        except OSError:time.sleep(.25)
                    if sock is None:raise RuntimeError("Missing GDB stub")
                    with sock:
                        stub=Stub(sock)
                        sock.sendall(b"+")
                        status=stub.send("?")
                        if not status.startswith(("T","S")):
                            raise RuntimeError("GDB initial status "+status)
                        start=stub.read_party()
                        if any(p["species"] for p in start):
                            raise AssertionError("Not a fresh empty party")
                        case["checkpoints"].append({"stage":"initial-empty-party","party":[]})
                        win=window_for_mgba(proc)
                        stub.resume()
                        time.sleep(4)
                        # UI-only exploratory replay. x = mGBA default A, z = B.
                        # Include moves from bedroom to Oak's lab, with bounded
                        # attempts and periodic party inspection, never a fake pass.
                        stages=[
                          ("title-and-intro",[("Return",0.6)]*3+[("x",.45)]*45),
                          ("intro-name-confirm",[("Down",.2),("x",.5)]*10+[("x",.4)]*45),
                          ("pallet-exit",[("Down",.2)]*11+[("x",.2)]*7+
                           [("Left",.2),("Down",.2),("Down",.2),("Down",.2)]*5),
                          ("oak-lab-approach",[("Up",.2)]*8+[("x",.4)]*15),
                          ("starter-left",[("Left",.3)]*3+[("Up",.3)]*7+[("x",.4)]*15),
                        ]
                        # Offset target ball horizontally, while preserving all
                        # captures as unverified until a true party is observed.
                        if slot:stages.append(("starter-offset", [("Right",.3)]*slot+[("x",.4)]*25))
                        stages.append(("choice-confirm",[("x",.4)]*35))
                        acquired=False
                        for label,actions in stages:
                            for key,delay in actions:
                                sendkey(win,key,delay)
                                case["actions"]+=1
                            if inspect(stub,case,label,target):
                                acquired=True;break
                        if not acquired:
                            case["status"]="NOT VERIFIED: bounded UI replay never produced expected party"
                finally:
                    proc.terminate()
                    try:proc.wait(timeout=5)
                    except subprocess.TimeoutExpired:proc.kill()
    results["three_starters_verified"]=all(x["status"].startswith("PASS") for x in results["cases"].values())
finally:
    out.write_text(json.dumps(results,indent=2)+"\n")
print(json.dumps(results,indent=2))
if not results["three_starters_verified"]:
    sys.exit("FAIL CLOSED: actual three-starter acquisition not verified; see JSON checkpoint evidence")
