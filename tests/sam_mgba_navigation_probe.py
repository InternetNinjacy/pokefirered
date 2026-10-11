#!/usr/bin/env python3
"""Bounded GUI input exploration with non-ROM, non-screenshot evidence.

Requires a built ROM, DISPLAY (Xvfb) and mGBA Qt. This is explicitly NOT a
semantic starter/party verification. Each branch starts with clean HOME/SRAM.
"""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time
from PIL import Image, ImageChops, ImageStat

rom = Path(sys.argv[1]).resolve()
assert rom.is_file()
raw = rom.read_bytes()
assert raw[0xAC:0xB0] == b"BPRE"
result = {"commit": os.environ.get("GITHUB_SHA", "local"),
          "rom_sha256": hashlib.sha256(raw).hexdigest(),
          "cases": {}, "limitations": "GUI input and frame differences only; does not confirm game-state, starter species, battle or save success."}

def cmd(*args):
    return subprocess.run(args, check=True, capture_output=True, text=True, timeout=10).stdout.strip()

def sample(win, destination):
    cmd("import", "-window", win, str(destination))
    with Image.open(destination) as im:
        rgb = im.convert("RGB")
        stat = ImageStat.Stat(rgb)
        return {"size": list(rgb.size), "stddev": round(max(stat.stddev),2),
                "digest": hashlib.sha256(rgb.tobytes()).hexdigest()}

def press(win, key, delay=1.0):
    cmd("xdotool", "key", "--clearmodifiers", "--window", win, key)
    time.sleep(delay)

try:
    for branch, direction in (("starter_slot_0",0),("starter_slot_1",1),("starter_slot_2",2)):
        with tempfile.TemporaryDirectory() as home:
            env = dict(os.environ, HOME=home, XDG_CONFIG_HOME=home,
                       QT_QPA_PLATFORM="xcb", SDL_AUDIODRIVER="dummy")
            with open(Path(home)/"emulator.log","w") as logfile:
                proc = subprocess.Popen(["mgba-qt",str(rom)], env=env, stdout=logfile,stderr=subprocess.STDOUT)
                evidence = {"input_trace":[], "captures":[], "status":"NOT VERIFIED"}
                result["cases"][branch] = evidence
                try:
                    win = None
                    for _ in range(60):
                        if proc.poll() is not None:
                            raise RuntimeError("mGBA quit before visible window")
                        found = subprocess.run(["xdotool","search","--onlyvisible","--class","mgba"],
                                               capture_output=True,text=True)
                        for w in found.stdout.splitlines() if found.returncode == 0 else []:
                            geo=cmd("xdotool","getwindowgeometry","--shell",w)
                            dims=dict(line.split("=",1) for line in geo.splitlines() if "=" in line)
                            if int(dims.get("WIDTH",0))>=240 and int(dims.get("HEIGHT",0))>=160:
                                win=w
                                break
                        if win: break
                        time.sleep(0.2)
                    if not win: raise RuntimeError("No mGBA video window")
                    time.sleep(5)
                    with tempfile.TemporaryDirectory() as tmp:
                        def capture(label):
                            path=Path(tmp)/(label+".png")
                            obs=sample(win,path)
                            evidence["captures"].append({"checkpoint":label,**obs})
                            if obs["size"][0]<240 or obs["size"][1]<160 or obs["stddev"]<8:
                                raise RuntimeError("Blank or wrong emulator window at "+label)
                        capture("boot")
                        # A bounded probing trace, NOT a claimed deterministic game
                        # walkthrough. A title/intro can require variable timing.
                        sequence=[("Return",2),("Return",2),("z",1),("Return",2)]
                        sequence += [("z",0.8)]*8
                        sequence += [("Return",1),("z",1)]*5
                        sequence += [("Down",0.4)]*direction
                        sequence += [("z",2),("z",1),("Return",2)]
                        for i,(key,delay) in enumerate(sequence):
                            press(win,key,delay)
                            evidence["input_trace"].append(key)
                            if i in (1,8,len(sequence)-1):
                                capture("checkpoint_"+str(i))
                        if proc.poll() is not None:
                            raise RuntimeError("Emulator quit during input replay")
                        evidence["status"]="PASS: GUI liveness, inputs dispatched and nonblank frames; starter selection NOT VERIFIED"
                except Exception as e:
                    evidence["status"]="FAIL: "+str(e)
                    raise
                finally:
                    proc.terminate()
                    try: proc.wait(timeout=4)
                    except subprocess.TimeoutExpired: proc.kill()
finally:
    Path("sam-emulator-navigation-evidence.json").write_text(json.dumps(result,indent=2)+"\n")
print(json.dumps(result,indent=2))
