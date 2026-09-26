#!/usr/bin/env python3
"""Validate Cloudburst's Squall Badge and TM12 Weather Ball reward/runtime paths."""

from pathlib import Path
import hashlib
import json
import re
import struct
import sys

ROOT = Path(".")
BADGE_GIT_BLOB = "723b82dffd22afd9ad14149db419cd136e2f6c42"

def fail(msg):
    sys.exit("Cloudburst reward validation failed: " + msg)

def text(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(haystack, needle, label):
    if needle not in haystack:
        fail(f"{label}: missing {needle!r}")

def png_meta(path):
    data = (ROOT / path).read_bytes()
    if data[:8] != b"\x89PNG\r\n\x1a\n" or data[12:16] != b"IHDR":
        fail(f"{path}: invalid PNG/IHDR")
    width, height = struct.unpack(">II", data[16:24])
    return width, height, data[24], data[25]

def git_blob_sha1(data):
    return hashlib.sha1(f"blob {len(data)}\0".encode("ascii") + data).hexdigest()

def palette_count(path):
    lines = [line.strip() for line in text(path).splitlines() if line.strip()]
    if len(lines) < 3 or lines[0] != "JASC-PAL":
        fail(f"{path}: invalid JASC palette")
    if int(lines[2]) != 16 or len(lines[3:]) != 16:
        fail(f"{path}: expected exactly 16 palette colors")

# --- Squall Badge display path ---
badge_path = ROOT / "graphics/trainer_card/badges.png"
badge_data = badge_path.read_bytes()
meta = png_meta("graphics/trainer_card/badges.png")
if meta[:2] != (128, 16) or meta[2] != 4 or meta[3] != 3:
    fail(f"badge sheet: expected 128x16 4-bit indexed PNG, got {meta}")
if git_blob_sha1(badge_data) != BADGE_GIT_BLOB:
    fail("badge sheet changed; review Squall slot and deliberately update the approved fingerprint")

flags = text("include/constants/flags.h")
require(flags, "#define FLAG_BADGE01_SQUALL                                         FLAG_BADGE01_GET", "Squall badge flag alias")

gym_script = text("data/maps/PewterCity_Gym/scripts.inc")
require(gym_script, "setflag FLAG_BADGE01_SQUALL", "Cloudburst first-clear badge award")

card = text("src/trainer_card.c")
for needle in (
    'INCBIN_U32("graphics/trainer_card/badges.4bpp.lz")',
    'INCBIN_U16("graphics/trainer_card/badges.gbapal")',
    "for (i = 0, badgeFlag = FLAG_BADGE01_GET; badgeFlag <= FLAG_BADGE08_GET; badgeFlag++, i++)",
    "if (sTrainerCardDataPtr->hasBadge[i])",
):
    require(card, needle, "Trainer Card badge path")
# First badge is drawn from the first 2x2 badge tile block (tileNum starts at 192).
require(card, "u16 tileNum = 192;", "Trainer Card first badge tile")
require(card, "for (i = 0; i < NUM_BADGES; i++, tileNum += 2, x += 3)", "Trainer Card badge ordering")

# --- Weather Ball move + weather mapping ---
moves = text("src/data/battle_moves.h")
m = re.search(r"\[MOVE_WEATHER_BALL\]\s*=\s*\{([\s\S]*?)\n\s*\},", moves)
if not m:
    fail("MOVE_WEATHER_BALL data block missing")
move_block = m.group(1)
for needle in (
    ".effect = EFFECT_WEATHER_BALL",
    ".power = 50",
    ".type = TYPE_NORMAL",
    ".accuracy = 100",
    ".pp = 10",
):
    require(move_block, needle, "Weather Ball move data")

battle_h = text("include/constants/battle.h")
for needle in (
    "#define B_WEATHER_FOG                 (1 << 8)",
    "#define B_WEATHER_TOXIC_SMOG          (1 << 9)",
    "#define B_WEATHER_POLLEN              (1 << 10)",
    "#define B_WEATHER_GALE                (1 << 11)",
    "#define B_WEATHER_CUSTOM              (B_WEATHER_FOG | B_WEATHER_TOXIC_SMOG | B_WEATHER_POLLEN | B_WEATHER_GALE)",
    "#define B_WEATHER_ALL                 (B_WEATHER_ANY | B_WEATHER_CUSTOM)",
):
    require(battle_h, needle, "custom battle-weather category reservation")

cmds = text("src/battle_script_commands.c")
start = cmds.rfind("static void Cmd_setweatherballtype(void)")
if start < 0:
    fail("Cmd_setweatherballtype missing")
end = cmds.find("\n}\n", start)
wb = cmds[start:end + 3]
required_mappings = (
    ("B_WEATHER_RAIN", "TYPE_WATER"),
    ("B_WEATHER_SANDSTORM", "TYPE_ROCK"),
    ("B_WEATHER_SUN", "TYPE_FIRE"),
    ("B_WEATHER_HAIL", "TYPE_ICE"),
    ("B_WEATHER_FOG", "TYPE_GHOST"),
    ("B_WEATHER_TOXIC_SMOG", "TYPE_POISON"),
    ("B_WEATHER_POLLEN", "TYPE_BUG"),
    ("B_WEATHER_GALE", "TYPE_FLYING"),
)
require(wb, "gBattleWeather & B_WEATHER_ALL", "Weather Ball power doubling")
for weather, type_name in required_mappings:
    require(wb, f"gBattleWeather & {weather}", "Weather Ball weather mapping")
    require(wb, f"= {type_name} | F_DYNAMIC_TYPE_2;", "Weather Ball weather mapping")

items = json.loads(text("src/data/items.json"))["items"]
tm12 = next((item for item in items if item.get("itemId") == "ITEM_TM12"), None)
if tm12 is None or tm12.get("moveId") != "WeatherBall":
    fail("TM12 item does not resolve to WeatherBall")

require(gym_script, "additem ITEM_TM12_WEATHER_BALL", "Cloudburst TM12 reward")
require(gym_script, "setflag FLAG_GOT_TM12_FROM_RAINA", "Cloudburst TM12 one-time guard")

# --- Reusable TM path ---
party = text("src/party_menu.c")
learn_start = party.find("static void Task_LearnedMove(u8 taskId)\n{", 100000)
if learn_start < 0:
    fail("Task_LearnedMove implementation missing")
learn_end = party.find("\n}\n", learn_start)
learn_block = party[learn_start:learn_end + 3]
if "RemoveBagItem" in learn_block:
    fail("normal TM/HM learn path still consumes the machine")
require(learn_block, "TMs and HMs are permanently reusable", "normal reusable-TM path")

for func_name in ("static void CB2_UseItem(void)", "static void CB2_UseTMHMAfterForgettingMove(void)"):
    start = party.find(func_name)
    if start < 0:
        fail(f"{func_name} missing")
    end = party.find("\n}\n", start)
    block = party[start:end + 3]
    require(block, "TMs and HMs are permanently reusable", func_name)

print("Cloudburst reward paths OK: Squall badge display wiring + TM12 Weather Ball source behavior validated.")
