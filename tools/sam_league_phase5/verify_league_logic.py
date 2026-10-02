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

# League room progression must remain strictly Lorelei -> Blue -> Agatha -> Lance -> Green.
# These scene-state checks protect against accidental room-order regressions while preserving
# the vanilla League door architecture.
scene_expectations = [
    ("data/maps/PokemonLeague_LoreleisRoom/scripts.inc", 0, 1, "FLAG_DEFEATED_LORELEI"),
    ("data/maps/PokemonLeague_BrunosRoom/scripts.inc", 1, 2, "FLAG_DEFEATED_BRUNO"),
    ("data/maps/PokemonLeague_AgathasRoom/scripts.inc", 2, 3, "FLAG_DEFEATED_AGATHA"),
    ("data/maps/PokemonLeague_LancesRoom/scripts.inc", 3, 4, "FLAG_DEFEATED_LANCE"),
]
for path, enter_scene, exit_scene, defeated_flag in scene_expectations:
    require(path,
            f"map_script_2 VAR_MAP_SCENE_POKEMON_LEAGUE, {enter_scene},",
            f"{path}: wrong League room-entry scene gate; expected {enter_scene}")
    require(path,
            f"setvar VAR_MAP_SCENE_POKEMON_LEAGUE, {exit_scene}",
            f"{path}: wrong League room-exit scene state; expected {exit_scene}")
    script = read(path)
    battle_pos = script.find("trainerbattle_no_intro")
    flag_pos = script.find(f"setflag {defeated_flag}")
    if battle_pos < 0 or flag_pos < 0 or flag_pos < battle_pos:
        errors.append(f"{path}: {defeated_flag} must be set only after the trainer battle returns victorious")

# Champion room is only reachable after Lance advances the shared League scene to 4.
require("data/maps/PokemonLeague_ChampionsRoom/scripts.inc",
        "map_script_2 VAR_MAP_SCENE_POKEMON_LEAGUE, 4,",
        "Champion room must remain gated behind completed Lance-room progression")

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
    "sParty_EliteFourLorelei2": [(62,"KANGASKHAN"),(62,"PERSIAN"),(63,"WIGGLYTUFF"),(63,"LICKITUNG"),(64,"MILTANK"),(65,"TAUROS")],
    "sParty_EliteFourBruno2": [(64,"NINETALES"),(64,"RAPIDASH"),(65,"ARCANINE"),(65,"CHARIZARD"),(66,"MAGMAR"),(67,"FLAREON")],
    "sParty_EliteFourAgatha2": [(65,"CROBAT"),(65,"TENTACRUEL"),(66,"WEEZING"),(66,"NIDOKING"),(67,"GENGAR"),(68,"MUK")],
    "sParty_EliteFourLance2": [(66,"PIDGEOT"),(66,"DODRIO"),(67,"SCYTHER"),(67,"FEAROW"),(68,"AERODACTYL"),(69,"DRAGONITE")],
    "sParty_EliteFourBlueWater2": [(64,"LANTURN"),(64,"LUDICOLO"),(65,"KINGDRA"),(65,"SWAMPERT"),(66,"STARMIE"),(67,"DITTO")],
    "sParty_EliteFourBlueElectric2": [(64,"ELECTRODE"),(64,"MAGNETON"),(65,"AMPHAROS"),(65,"MANECTRIC"),(66,"ELECTABUZZ"),(67,"RAICHU")],
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

# Central Sam resource allocations used by League integration.
for symbol, value in [
    ("TRAINER_ELITE_FOUR_BLUE_WATER", "800"),
    ("TRAINER_ELITE_FOUR_BLUE_ELECTRIC", "801"),
    ("TRAINER_ELITE_FOUR_BLUE_WATER_2", "802"),
    ("TRAINER_ELITE_FOUR_BLUE_ELECTRIC_2", "803"),
]:
    if not re.search(rf"#define\s+{symbol}\s+{value}\b", opp):
        errors.append(f"{symbol}: expected centrally allocated trainer ID {value}")
if not re.search(r"#define\s+NUM_TRAINERS\s+804\b", opp):
    errors.append("NUM_TRAINERS must cover Blue ID 803 exactly")
if not re.search(r"#define\s+MAX_TRAINERS_COUNT\s+1024\b", opp):
    errors.append("MAX_TRAINERS_COUNT must use Sam Edition central 1024 capacity")

flags_text = read("include/constants/flags.h")
for symbol, value in [
    ("FLAG_GREEN_CHAMPION_REVEALED", "0x340"),
    ("FLAG_GREEN_TITLE_CHALLENGE_SEEN", "0x341"),
]:
    if not re.search(rf"#define\s+{symbol}\s+{value}\b", flags_text):
        errors.append(f"{symbol}: expected central rival allocation {value}")
require("include/global.h", "struct SamEditionSaveData")
require("include/global.h", "greenName[PLAYER_NAME_LENGTH + 1]")
require("include/global.h", "struct SamEditionSaveData samEdition;")
require("src/save.c", "STATIC_ASSERT(sizeof(struct SamEditionSaveData) == 0xF0")
require("src/save.c", "STATIC_ASSERT(sizeof(struct SaveBlock1) == 0x3D68")

# Green Champion exact competitive-construction integration.
require("include/constants/trainers.h", "F_TRAINER_PARTY_COMPETITIVE")
require("include/battle.h", "struct TrainerMonCompetitiveMoves")
require("include/battle.h", "#define COMPETITIVE_MOVES(party)")
require("src/battle_main.c", "MON_DATA_ABILITY_NUM")
require("src/battle_main.c", "MON_DATA_HP_IV + j")
require("src/battle_main.c", "MON_DATA_HP_EV + j")
require("src/battle_setup.c", "F_TRAINER_PARTY_COMPETITIVE")

# Adaptive Gene is the authoritative item-245 identity and its Ditto-only
# damage rule must use original party species so Transform does not disable it.
require("include/constants/items.h", "#define ITEM_ADAPTIVE_GENE 245")
require("include/constants/items.h", "#define ITEM_0F5 ITEM_ADAPTIVE_GENE")
require("src/pokemon.c", "attacker->item == ITEM_ADAPTIVE_GENE && battlerIdAtk != battlerIdDef")
require("src/pokemon.c", "GetMonData(&party[gBattlerPartyIndexes[battlerIdAtk]], MON_DATA_SPECIES) == SPECIES_DITTO")

# Green's trainer-held equipment is battle-only: player-side steal/swap effects
# must not create permanent acquisition sources.
require("src/battle_script_commands.c", "static bool32 IsGreenLeagueTrainerBattle(void)")
require("src/battle_script_commands.c", "IsGreenLeagueTrainerBattle()")
require("src/battle_script_commands.c", "GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER")
require("src/battle_script_commands.c", "GetBattlerSide(gBattlerTarget) == B_SIDE_OPPONENT")

# Both the first Champion fight and the postgame PKMN TRAINER title challenge
# use the existing Champion battle theme.
require("src/battle_setup.c", "static bool32 IsGreenLeagueTrainer(u16 trainerId)")
require("src/battle_setup.c", "song = MUS_VS_CHAMPION")
require("src/battle_setup.c", "CreateBattleStartTask(GetTrainerBattleTransition(), song)")

# Green has independent persistent naming. Keep its placeholder distinct from the
# existing GREEN palette constant in charmap.txt, and ensure expansion is wired.
require("include/characters.h", "#define PLACEHOLDER_ID_GREEN         0xE")
require("charmap.txt", "GREEN_NAME     = FD 0E")
forbid("charmap.txt", "GREEN          = FD 0E",
       "Green-name placeholder must not collide with the GREEN color constant")
require("src/string_util.c",
        "[PLACEHOLDER_ID_GREEN]        = ExpandPlaceholder_GreenName")
require("src/battle_message.c", "toCpy = GetGreenName()")

green_expected = {
    # Legacy vanilla Champion array names are source IDs only.
    # VAR_STARTER_MON 2 = player Ditto -> Green Espeon.
    "sParty_ChampionFirstSquirtle": [(59,"GYARADOS"),(57,"STEELIX"),(58,"CROBAT"),(56,"SNORLAX"),(55,"CHARIZARD"),(60,"ESPEON")],
    # VAR_STARTER_MON 1 = player Pichu -> Green Ditto.
    "sParty_ChampionFirstBulbasaur": [(56,"CLOYSTER"),(58,"NIDOKING"),(59,"ARCANINE"),(57,"PINSIR"),(55,"GENGAR"),(60,"DITTO")],
    # VAR_STARTER_MON 0 = player Eevee -> Green Raichu.
    "sParty_ChampionFirstCharmander": [(59,"VENUSAUR"),(57,"PORYGON2"),(58,"MACHAMP"),(55,"STARMIE"),(56,"DRAGONITE"),(60,"RAICHU")],
    "sParty_ChampionRematchSquirtle": [(69,"GYARADOS"),(67,"STEELIX"),(68,"CROBAT"),(66,"SNORLAX"),(65,"CHARIZARD"),(70,"ESPEON")],
    "sParty_ChampionRematchBulbasaur": [(66,"CLOYSTER"),(68,"NIDOKING"),(69,"ARCANINE"),(67,"PINSIR"),(65,"GENGAR"),(70,"DITTO")],
    "sParty_ChampionRematchCharmander": [(69,"VENUSAUR"),(67,"PORYGON2"),(68,"MACHAMP"),(65,"STARMIE"),(66,"DRAGONITE"),(70,"RAICHU")],
}
for name, mons in green_expected.items():
    m = re.search(rf"static const struct TrainerMonCompetitiveMoves {name}\[\] = \{{(.*?)\n\}};", party_text, re.S)
    if not m:
        errors.append(f"missing Green competitive party {name}")
        continue
    body = m.group(1)
    found = [(int(l), s) for l,s in re.findall(r"\.lvl = (\d+),\s*\n\s*\.species = SPECIES_([A-Z0-9_]+),", body)]
    if found != mons:
        errors.append(f"{name}: expected {mons}, found {found}")

# Green's Ditto branches use the named Adaptive Gene symbol, not a raw placeholder.
for name in ["sParty_ChampionFirstBulbasaur", "sParty_ChampionRematchBulbasaur"]:
    m = re.search(rf"static const struct TrainerMonCompetitiveMoves {name}\\[\\] = \\{{(.*?)\\n\\}};", party_text, re.S)
    if m:
        sm = re.search(r"\\.species = SPECIES_DITTO,(.*?)(?=\\n    \\},|\\Z)", m.group(1), re.S)
        if not sm or ".heldItem = ITEM_ADAPTIVE_GENE" not in sm.group(1):
            errors.append(f"{name} DITTO: expected ITEM_ADAPTIVE_GENE")

# Hidden Power construction is exact and must not drift.
for name, species, expected_ivs in [
    ("sParty_ChampionFirstCharmander", "MACHAMP", "31, 31, 30, 31, 31, 30"),
    ("sParty_ChampionFirstCharmander", "RAICHU", "30, 30, 30, 31, 31, 31"),
    ("sParty_ChampionRematchCharmander", "MACHAMP", "31, 31, 30, 31, 31, 30"),
    ("sParty_ChampionRematchCharmander", "RAICHU", "30, 30, 30, 31, 31, 31"),
]:
    m = re.search(rf"static const struct TrainerMonCompetitiveMoves {name}\[\] = \{{(.*?)\n\}};", party_text, re.S)
    if m:
        sm = re.search(rf"\.species = SPECIES_{species},(.*?)(?=\n    \}},|\Z)", m.group(1), re.S)
        if not sm or f".ivs = {{{expected_ivs}}}" not in sm.group(1):
            errors.append(f"{name} {species}: expected IVs {expected_ivs}")

champ_script = read("data/maps/PokemonLeague_ChampionsRoom/scripts.inc")
for route in [
    "call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_BattleSquirtle",
    "call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_BattleBulbasaur",
    "call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_BattleCharmander",
    "call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_RematchSquirtle",
    "call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_RematchBulbasaur",
    "call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_RematchCharmander",
]:
    if route not in champ_script:
        errors.append(f"Champion branch route missing: {route}")

for trainer in [
    "TRAINER_CHAMPION_FIRST_SQUIRTLE","TRAINER_CHAMPION_FIRST_BULBASAUR","TRAINER_CHAMPION_FIRST_CHARMANDER",
    "TRAINER_CHAMPION_REMATCH_SQUIRTLE","TRAINER_CHAMPION_REMATCH_BULBASAUR","TRAINER_CHAMPION_REMATCH_CHARMANDER",
]:
    m = re.search(rf"\[{trainer}\] = \{{(.*?)\n    \}},", trainers, re.S)
    if not m:
        errors.append(f"missing Green trainer record {trainer}")
        continue
    body = m.group(1)
    if ".items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE}" not in body:
        errors.append(f"{trainer}: expected exactly two Full Restores")
    if ".party = COMPETITIVE_MOVES(" not in body:
        errors.append(f"{trainer}: expected competitive party schema")

for trainer in [
    "TRAINER_CHAMPION_FIRST_SQUIRTLE","TRAINER_CHAMPION_FIRST_BULBASAUR","TRAINER_CHAMPION_FIRST_CHARMANDER",
]:
    m = re.search(rf"\[{trainer}\] = \{{(.*?)\n    \}},", trainers, re.S)
    if m and ".trainerClass = TRAINER_CLASS_CHAMPION" not in m.group(1):
        errors.append(f"{trainer}: first-clear Green must use CHAMPION label")

for trainer in [
    "TRAINER_CHAMPION_REMATCH_SQUIRTLE","TRAINER_CHAMPION_REMATCH_BULBASAUR","TRAINER_CHAMPION_REMATCH_CHARMANDER",
]:
    m = re.search(rf"\[{trainer}\] = \{{(.*?)\n    \}},", trainers, re.S)
    if m and ".trainerClass = TRAINER_CLASS_PKMN_TRAINER" not in m.group(1):
        errors.append(f"{trainer}: postgame Green must be PKMN TRAINER, not persistent Champion")

# Elite Four dialogue/script closure: exact approved first-clear and rematch
# content must remain separate so postgame runs do not reuse first-clear text.
for room, trainer in [
    ("LoreleisRoom", "LORELEI"),
    ("AgathasRoom", "AGATHA"),
    ("LancesRoom", "LANCE"),
]:
    script_path = f"data/maps/PokemonLeague_{room}/scripts.inc"
    require(script_path,
            f"trainerbattle_no_intro TRAINER_ELITE_FOUR_{trainer}_2, PokemonLeague_{room}_Text_RematchDefeat")
    require(script_path, f"PokemonLeague_{room}_EventScript_ShowFirstPostBattle")
    require(script_path, f"PokemonLeague_{room}_EventScript_ShowRematchPostBattle")
    require(script_path, f"PokemonLeague_{room}_Text_RematchPostBattle")

require("data/maps/PokemonLeague_AgathasRoom/text.inc", "So. You've made it past BLUE.")
require("data/maps/PokemonLeague_AgathasRoom/text.inc", "Let me teach you a little patience.")
require("data/maps/PokemonLeague_AgathasRoom/text.inc", "Let's see how patient the CHAMPION")
require("data/maps/PokemonLeague_AgathasRoom/text.inc", "That's why you're wearing the title.")
require("data/maps/PokemonLeague_LancesRoom/text.inc", "But Flying POKéMON are fascinating.")
require("data/maps/PokemonLeague_LancesRoom/text.inc", "Try to keep up!")
require("data/maps/PokemonLeague_LancesRoom/text.inc", "GREEN is through that door.")
require("data/maps/PokemonLeague_LancesRoom/text.inc", "I need another notebook.")
require("data/maps/PokemonLeague_LoreleisRoom/text.inc", "Back for another performance?")
require("data/maps/PokemonLeague_LoreleisRoom/text.inc", "Let's give them a show!")
forbid("data/maps/PokemonLeague_LoreleisRoom/text.inc", "icy POKéMON",
       "Lorelei rematch must not regress to vanilla Ice-specialist dialogue")
forbid("data/maps/PokemonLeague_LancesRoom/text.inc", "LANCE the dragon",
       "Lance must not regress to vanilla Dragon-specialist dialogue")
forbid("data/maps/PokemonLeague_LancesRoom/text.inc", "His name is",
       "Lance must not regress to vanilla rival-Champion reveal")

flags = read("include/constants/flags.h")
for flag in ["FLAG_GREEN_CHAMPION_REVEALED", "FLAG_GREEN_TITLE_CHALLENGE_SEEN"]:
    if flag not in flags:
        errors.append(f"missing persistent Green presentation flag {flag}")

require("data/maps/PokemonLeague_ChampionsRoom/scripts.inc",
        "setflag FLAG_GREEN_CHAMPION_REVEALED",
        "Green reveal flag must be set before the first Champion battle")
require("data/maps/PokemonLeague_ChampionsRoom/scripts.inc",
        "setflag FLAG_GREEN_TITLE_CHALLENGE_SEEN",
        "Green title-challenge seen flag must be set before the postgame battle")
for trainer in ["SQUIRTLE","BULBASAUR","CHARMANDER"]:
    require("data/maps/PokemonLeague_ChampionsRoom/scripts.inc",
            f"trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_{trainer}, PokemonLeague_ChampionsRoom_Text_RematchDefeat",
            f"Green {trainer} title challenge must use rematch defeat text")
forbid("data/maps/PokemonLeague_ChampionsRoom/scripts.inc",
       "msgbox PokemonLeague_ChampionsRoom_Text_OakImDisappointedRival",
       "Oak's Green-specific Champion-room reaction is authority-open and must not be invented/called")

if errors:
    print("Sam League static validation FAILED:")
    for e in errors:
        print(" -", e)
    sys.exit(1)

print("Sam League static validation passed.")
