#!/usr/bin/env python3
from pathlib import Path
import re, sys

ROOT = Path(__file__).resolve().parents[2]
errors = []

def read(path):
    p = ROOT / path
    if not p.exists():
        errors.append(f"missing file: {path}")
        return ""
    return p.read_text(encoding="utf-8")

def require(path, needle, label=None):
    text = read(path)
    if needle not in text:
        errors.append(label or f"{path}: missing {needle!r}")

def forbid(path, needle, label=None):
    text = read(path)
    if needle in text:
        errors.append(label or f"{path}: forbidden {needle!r}")

# Room-specific tileset bindings and identity fallbacks.
bindings = {
    "LAYOUT_POKEMON_LEAGUE_LORELEIS_ROOM": "gTileset_PokemonLeagueLorelei",
    "LAYOUT_POKEMON_LEAGUE_BRUNOS_ROOM": "gTileset_PokemonLeagueBlue",
    "LAYOUT_POKEMON_LEAGUE_AGATHAS_ROOM": "gTileset_PokemonLeagueAgatha",
    "LAYOUT_POKEMON_LEAGUE_LANCES_ROOM": "gTileset_PokemonLeagueLance",
    "LAYOUT_POKEMON_LEAGUE_CHAMPIONS_ROOM": "gTileset_PokemonLeagueGreen",
}
layouts = read("data/layouts/layouts.json")
for layout, tileset in bindings.items():
    pos = layouts.find(f'"id": "{layout}"')
    if pos < 0 or tileset not in layouts[pos:pos+700]:
        errors.append(f"{layout}: expected {tileset}")

require("data/maps/PokemonLeague_BrunosRoom/map.json", '"graphics_id": "OBJ_EVENT_GFX_BLUE"')
require("data/maps/PokemonLeague_ChampionsRoom/map.json", '"graphics_id": "OBJ_EVENT_GFX_GREEN_NORMAL"')

# Hall-of-Fame completion, not the vanilla RS-link flag, selects League rematches.
league_scripts = [
    "data/maps/PokemonLeague_LoreleisRoom/scripts.inc",
    "data/maps/PokemonLeague_BrunosRoom/scripts.inc",
    "data/maps/PokemonLeague_AgathasRoom/scripts.inc",
    "data/maps/PokemonLeague_LancesRoom/scripts.inc",
    "data/maps/PokemonLeague_ChampionsRoom/scripts.inc",
]
for path in league_scripts:
    forbid(path, "FLAG_SYS_CAN_LINK_WITH_RS", f"{path}: stale vanilla rematch gate remains")
    require(path, "FLAG_SYS_GAME_CLEAR", f"{path}: Hall-of-Fame rematch gate missing")

# Per-run Elite Four state must still reset for a new League challenge.
hof = read("data/scripts/hall_of_fame.inc")
for flag in ["FLAG_DEFEATED_LORELEI", "FLAG_DEFEATED_BRUNO", "FLAG_DEFEATED_AGATHA", "FLAG_DEFEATED_LANCE"]:
    if f"clearflag {flag}" not in hof:
        errors.append(f"Hall of Fame reset missing {flag}")

# Exact current Sam E4 first-clear species/levels.
party_text = read("src/data/trainer_parties.h")
expected = {
    "sParty_EliteFourLorelei": [(52,"KANGASKHAN"),(52,"PERSIAN"),(53,"WIGGLYTUFF"),(53,"LICKITUNG"),(54,"MILTANK"),(55,"TAUROS")],
    "sParty_EliteFourBruno": [(54,"NINETALES"),(54,"RAPIDASH"),(55,"ARCANINE"),(55,"CHARIZARD"),(56,"MAGMAR"),(57,"FLAREON")],
    "sParty_EliteFourAgatha": [(55,"CROBAT"),(55,"TENTACRUEL"),(56,"WEEZING"),(56,"NIDOKING"),(57,"GENGAR"),(58,"MUK")],
    "sParty_EliteFourLance": [(56,"PIDGEOT"),(56,"DODRIO"),(57,"SCYTHER"),(57,"FEAROW"),(58,"AERODACTYL"),(59,"DRAGONITE")],
    "sParty_EliteFourBlueWater": [(54,"LANTURN"),(54,"LUDICOLO"),(55,"KINGDRA"),(55,"SWAMPERT"),(56,"STARMIE"),(57,"DITTO")],
    "sParty_EliteFourBlueElectric": [(54,"ELECTRODE"),(54,"MAGNETON"),(55,"AMPHAROS"),(55,"MANECTRIC"),(56,"ELECTABUZZ"),(57,"RAICHU")],
}
for name, mons in expected.items():
    m = re.search(rf"static const struct TrainerMonItemCustomMoves {name}\[\] = \{{(.*?)\n\}};", party_text, re.S)
    if not m:
        errors.append(f"missing trainer party {name}")
        continue
    body = m.group(1)
    found = [(int(l), s) for l,s in re.findall(r"\.lvl = (\d+),\s*\n\s*\.species = SPECIES_([A-Z0-9_]+),", body)]
    if found != mons:
        errors.append(f"{name}: expected {mons}, found {found}")

# Blue branch IDs and exactly two Full Restores on specialist E4 records.
opp = read("include/constants/opponents.h")
for symbol in ["TRAINER_ELITE_FOUR_BLUE_WATER","TRAINER_ELITE_FOUR_BLUE_ELECTRIC",
               "TRAINER_ELITE_FOUR_BLUE_WATER_2","TRAINER_ELITE_FOUR_BLUE_ELECTRIC_2"]:
    if symbol not in opp:
        errors.append(f"missing Blue trainer ID {symbol}")

trainers = read("src/data/trainers.h")
for symbol in ["TRAINER_ELITE_FOUR_LORELEI","TRAINER_ELITE_FOUR_BRUNO",
               "TRAINER_ELITE_FOUR_AGATHA","TRAINER_ELITE_FOUR_LANCE",
               "TRAINER_ELITE_FOUR_BLUE_WATER","TRAINER_ELITE_FOUR_BLUE_ELECTRIC"]:
    m = re.search(rf"\[{symbol}\] = \{{(.*?)\n    \}},", trainers, re.S)
    if not m:
        errors.append(f"missing trainer record {symbol}")
    elif ".items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE}" not in m.group(1):
        errors.append(f"{symbol}: expected exactly two Full Restores")

if errors:
    print("Sam League static validation FAILED:")
    for e in errors:
        print(" -", e)
    sys.exit(1)

print("Sam League static validation passed.")
