#!/usr/bin/env python3
"""Actual mGBA Qt boot smoke: render real frames, never publish the ROM.

This verifies emulator process liveness, video rendering, and Start input
delivery. It does NOT verify that intro/story/menus/save/load succeed.
"""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time
from PIL import Image, ImageStat

rom = Path(sys.argv[1]).resolve()
data = rom.read_bytes()
assert len(data) > 0xC0 and data[0xAC:0xB0] == b'BPRE'
evidence = {
    "commit": os.environ.get("GITHUB_SHA", "local"),
    "rom_sha256": hashlib.sha256(data).hexdigest(),
    "rom_size_bytes": len(data),
    "game_code": "BPRE",
    "emulator": "mgba-qt via Xvfb",
    "cases": {"B01_boot_render": "NOT RUN", "B01_start_input": "NOT RUN"},
}
outfile = Path("sam-emulator-boot-evidence.json")

def run(*args, timeout=8):
    return subprocess.run(args, check=True, capture_output=True, text=True, timeout=timeout).stdout.strip()

with tempfile.TemporaryDirectory() as tmp:
    env = dict(os.environ, HOME=tmp, XDG_CONFIG_HOME=tmp,
               QT_QPA_PLATFORM="xcb", SDL_AUDIODRIVER="dummy")
    log = open(Path(tmp) / "mgba.log", "w")
    proc = subprocess.Popen(["mgba-qt", str(rom)], env=env,
                            stdout=log, stderr=subprocess.STDOUT)
    try:
        window = None
        for _ in range(40):
            if proc.poll() is not None:
                raise RuntimeError("mGBA exited during boot; inspect the step logs")
            ids = run("xdotool", "search", "--onlyvisible", "--class", "mgba").splitlines() if subprocess.run(
                ["xdotool", "search", "--onlyvisible", "--class", "mgba"],
                capture_output=True).returncode == 0 else []
            if ids:
                window = ids[-1]
                break
            time.sleep(0.25)
        if not window:
            raise RuntimeError("mGBA game window did not appear")
        # Xvfb runs without a window manager; windowactivate requires one.
        # Address the target X window directly for screenshots and key input.
        time.sleep(6)
        if proc.poll() is not None:
            raise RuntimeError("mGBA quit before initial frame sampling")
        screens = []
        for label in ("initial", "after_start"):
            if label == "after_start":
                run("xdotool", "key", "--window", window, "Return")
                time.sleep(2)
            png = Path(tmp) / (label + ".png")
            run("import", "-window", window, str(png))
            with Image.open(png) as im:
                rgb = im.convert("RGB")
                stddev = ImageStat.Stat(rgb).stddev
                colors = rgb.getcolors(maxcolors=2_000_000)
                observation = {
                    "width": rgb.width, "height": rgb.height,
                    "channel_stddev": [round(v, 2) for v in stddev],
                    "distinct_colors": len(colors) if colors is not None else ">2000000",
                }
                screens.append(observation)
                if rgb.width < 200 or rgb.height < 150 or max(stddev) < 8:
                    raise RuntimeError(f"Blank/unexpected emulator framebuffer at {label}: {observation}")
            print(f"{label}: {observation}")
        if proc.poll() is not None:
            raise RuntimeError("mGBA terminated after Start input")
        evidence["screens"] = screens
        evidence["cases"]["B01_boot_render"] = "PASS: emulator alive and rendered nonblank frames"
        evidence["cases"]["B01_start_input"] = "INPUT SENT; scene transition not verified"
    finally:
        proc.terminate()
        try:
            proc.wait(timeout=5)
        except subprocess.TimeoutExpired:
            proc.kill()
        log.close()
        print((Path(tmp) / "mgba.log").read_text()[-2000:])
        outfile.write_text(json.dumps(evidence, indent=2) + "\n")
print(json.dumps(evidence, indent=2))
