#!/usr/bin/env python3
"""Read live gPlayerParty from mGBA GDB stub; never manufacture starter PASS.

GDB read is a real emulator RAM capture. Input steering and story flags need
separate deterministic checkpoint logic before individual starter PASS claims.
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
from sam_party_ram_oracle import decode_party

rom=Path(sys.argv[1]).resolve()
elf=Path(sys.argv[2]).resolve()
assert rom.is_file() and elf.is_file()
symbols=subprocess.check_output(["arm-none-eabi-nm",str(elf)],text=True)
matches=re.findall(r"^([0-9a-fA-F]+)\s+[A-Za-z]\s+gPlayerParty$",symbols,re.M)
if len(matches)!=1:
    raise RuntimeError("Cannot resolve unique gPlayerParty ELF symbol")
address=int(matches[0],16)
assert 0x02000000 <= address < 0x03000000, hex(address)
output=Path("sam-live-party-evidence.json")
result={"commit":os.environ.get("GITHUB_SHA","local"),
        "rom_sha256":hashlib.sha256(rom.read_bytes()).hexdigest(),
        "gPlayerParty_address":hex(address),
        "memory_capture":"NOT RUN",
        "starter_acquisition":{"eevee":"NOT VERIFIED","pichu":"NOT VERIFIED","ditto":"NOT VERIFIED"}}
try:
    with tempfile.TemporaryDirectory() as home:
        env=dict(os.environ,HOME=home,XDG_CONFIG_HOME=home,QT_QPA_PLATFORM="xcb",SDL_AUDIODRIVER="dummy")
        with open(Path(home)/"mgba.log","w") as log:
            proc=subprocess.Popen(["mgba-qt","-g",str(rom)],env=env,stdout=log,stderr=subprocess.STDOUT)
            try:
                # mGBA -g starts a GDB remote stub on localhost:2345.
                sock=None
                for _ in range(60):
                    if proc.poll() is not None: raise RuntimeError("mGBA exited before GDB attach")
                    try:
                        sock=socket.create_connection(("127.0.0.1",2345),timeout=1)
                        break
                    except OSError:
                        time.sleep(0.25)
                if sock is None: raise RuntimeError("GDB stub did not open port 2345")
                with sock:
                    sock.settimeout(8)
                    def packet(payload):
                        data=payload.encode("ascii")
                        return b"$"+data+b"#"+("%02x"%(sum(data)%256)).encode("ascii")
                    def response():
                        # Skip acknowledgements and async output until a framed response.
                        while sock.recv(1)!=b"$": pass
                        body=bytearray()
                        while True:
                            b=sock.recv(1)
                            if b==b"#": break
                            if not b: raise RuntimeError("GDB socket closed")
                            body.extend(b)
                        checksum=sock.recv(2)
                        if int(checksum,16)!=sum(body)%256:
                            raise RuntimeError("GDB response checksum mismatch")
                        sock.sendall(b"+")
                        return body.decode("ascii")
                    sock.sendall(b"+")
                    sock.sendall(packet("?"))
                    status=response()
                    if not status.startswith(("S","T")):
                        raise RuntimeError("Unexpected GDB initial status "+status[:80])
                    sock.sendall(packet(f"m{address:x},258"))
                    memory=response()
                    if memory.startswith("E"):
                        raise RuntimeError("GDB memory read failed: "+memory)
                    data=bytes.fromhex(memory)
                    if len(data)!=600:
                        raise RuntimeError(f"Expected 600 live bytes, got {len(data)}")
                    party=decode_party(data)
                    result["memory_capture"]="PASS: 600 live bytes from actual mGBA GDB RAM"
                    result["party"]=party
                    result["party_raw_sha256"]=hashlib.sha256(data).hexdigest()
                    # Do not assume this paused-at-attach state has acquired a starter.
                    print(json.dumps({"status":status,"address":hex(address),"party":party},indent=2))
            finally:
                proc.terminate()
                try:proc.wait(timeout=5)
                except subprocess.TimeoutExpired:proc.kill()
finally:
    output.write_text(json.dumps(result,indent=2)+"\n")
print(json.dumps(result,indent=2))
