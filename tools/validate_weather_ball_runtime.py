#!/usr/bin/env python3
"""Validate Pokémon: Weather TM12 Weather Ball mechanics, acquisition, and reusability."""

from pathlib import Path
import json
import re
import sys

ROOT = Path(".")

def fail(msg):
    sys.exit("Weather Ball runtime-path validation failed: " + msg)

def text(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(haystack, needle, label):
    if needle not in haystack:
        fail(f"{label}: missing {needle!r}")

# Base move data stays FireRed Weather Ball: Normal, 50 BP, 100 accuracy, 10 PP.
moves = text("src/data/battle_moves.h")
m = re.search(r"\[MOVE_WEATHER_BALL\]\s*=\s*\{([\s\S]*?)\n\s*\},", moves)
if not m:
    fail("MOVE_WEATHER_BALL data block missing")
block = m.group(1)
for needle in (
    ".effect = EFFECT_WEATHER_BALL",
    ".power = 50",
    ".type = TYPE_NORMAL",
    ".accuracy = 100",
    ".pp = 10",
):
    require(block, needle, "Weather Ball base data")

# Eight weather categories + doubled power under any active category.
battle_h = text("include/constants/battle.h")
for needle in (
    "#define B_WEATHER_FOG                 (1 << 8)",
    "#define B_WEATHER_TOXIC_SMOG          (1 << 9)",
    "#define B_WEATHER_POLLEN              (1 << 10)",
    "#define B_WEATHER_GALE                (1 << 11)",
    "#define B_WEATHER_CUSTOM              (B_WEATHER_FOG | B_WEATHER_TOXIC_SMOG | B_WEATHER_POLLEN | B_WEATHER_GALE)",
    "#define B_WEATHER_ALL                 (B_WEATHER_ANY | B_WEATHER_CUSTOM)",
):
    require(battle_h, needle, "battle weather categories")

cmds = text("src/battle_script_commands.c")
start = cmds.rfind("static void Cmd_setweatherballtype(void)")
if start < 0:
    fail("Cmd_setweatherballtype implementation missing")
end = cmds.find("\n}\n", start)
wb = cmds[start:end + 3]
require(wb, "gBattleWeather & B_WEATHER_ALL", "Weather Ball power multiplier")
for weather, type_name in (
    ("B_WEATHER_RAIN", "TYPE_WATER"),
    ("B_WEATHER_SUN", "TYPE_FIRE"),
    ("B_WEATHER_SANDSTORM", "TYPE_ROCK"),
    ("B_WEATHER_HAIL", "TYPE_ICE"),
    ("B_WEATHER_FOG", "TYPE_GHOST"),
    ("B_WEATHER_TOXIC_SMOG", "TYPE_POISON"),
    ("B_WEATHER_POLLEN", "TYPE_BUG"),
    ("B_WEATHER_GALE", "TYPE_FLYING"),
):
    require(wb, f"gBattleWeather & {weather}", "Weather Ball weather mapping")
    require(wb, f"= {type_name} | F_DYNAMIC_TYPE_2;", "Weather Ball weather mapping")
require(wb, "= TYPE_NORMAL | F_DYNAMIC_TYPE_2;", "Weather Ball no-matched-weather fallback")

# Current acquisition authority: Cloudburst Mart sale, never a Gym reward.
mart = text("data/maps/PewterCity_Mart/scripts.inc")
require(mart, ".2byte ITEM_TM12_WEATHER_BALL", "Cloudburst Mart stock")

gym = text("data/maps/PewterCity_Gym/scripts.inc")
for forbidden in (
    "additem ITEM_TM12_WEATHER_BALL",
    "PewterCity_Gym_EventScript_GiveTM12FirstClear",
    "PewterCity_Gym_EventScript_GivePendingTM12",
    "goto_if_unset FLAG_GOT_TM12_FROM_RAINA",
):
    if forbidden in gym:
        fail(f"legacy Gym TM12 reward path remains: {forbidden}")
require(gym, "setflag FLAG_BADGE01_SQUALL", "Raina Squall Badge award")
require(gym, "msgbox PewterCity_Gym_Text_RainaFirstClearFinal", "Raina first-clear completion")

# TM12 item still resolves to Weather Ball and remains reusable.
items = json.loads(text("src/data/items.json"))
records = items["items"] if isinstance(items, dict) and "items" in items else items
if isinstance(records, dict):
    records = list(records.values())
tm12 = next((x for x in records if isinstance(x, dict) and x.get("itemId") == "ITEM_TM12"), None)
if not tm12 or tm12.get("moveId") != "WeatherBall":
    fail("ITEM_TM12 does not resolve to WeatherBall")

party = text("src/party_menu.c")
learn_start = party.find("static void Task_LearnedMove(u8 taskId)\n{", 100000)
if learn_start < 0:
    fail("Task_LearnedMove implementation missing")
learn_end = party.find("\n}\n", learn_start)
learn_block = party[learn_start:learn_end + 3]
if "RemoveBagItem" in learn_block:
    fail("ordinary TM learn path still consumes a TM")
require(learn_block, "TMs and HMs are permanently reusable", "ordinary reusable-TM path")

for func in ("static void CB2_UseItem(void)", "static void CB2_UseTMHMAfterForgettingMove(void)"):
    start = party.find(func)
    if start < 0:
        fail(f"{func} missing")
    end = party.find("\n}\n", start)
    fblock = party[start:end + 3]
    if "RemoveBagItem" in fblock:
        fail(f"{func} still consumes a TM")
    require(fblock, "TMs and HMs are permanently reusable", func)

print("Weather Ball source paths OK: 9-state mapping, Cloudburst Mart acquisition, and reusable TM learning validated.")
