from pathlib import Path
import json


def replace_once(text, old, new, label):
    if new in text:
        return text
    if old not in text:
        raise SystemExit(f"missing anchor: {label}")
    return text.replace(old, new, 1)


opp = Path("include/constants/opponents.h")
s = opp.read_text()
anchor = """#define TRAINER_BLUE_ONE_ISLAND_WATER              804
#define TRAINER_BLUE_ONE_ISLAND_ELECTRIC           805
#define TRAINER_BLUE_ONE_ISLAND_FIRE               806
"""
block = anchor + """
// Route 4 mandatory shared Blue + Green Double Battle.
#define TRAINER_BLUE_GREEN_ROUTE4_WATER_PIKACHU    807
#define TRAINER_BLUE_GREEN_ROUTE4_FIRE_DITTO       808
#define TRAINER_BLUE_GREEN_ROUTE4_ELECTRIC_EEVEE   809
"""
s = replace_once(s, anchor, block, "Route 4 trainer IDs")
s = s.replace("#define NUM_TRAINERS                             807", "#define NUM_TRAINERS                             810")
opp.write_text(s)

parties = Path("src/data/sam_blue_parties.h")
s = parties.read_text()
if "sParty_BlueGreenRoute4WaterPikachu" not in s:
    s += r'''

// Route 4 mandatory shared Blue + Green Double Battle.
// Player Eevee -> Blue Water + Green Raichu branch.
static const struct TrainerMonNoItemCustomMoves sParty_BlueGreenRoute4WaterPikachu[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 255, .lvl = 16, .species = SPECIES_PIKACHU, .moves = {MOVE_THUNDER_SHOCK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_TAIL_WHIP}},
    {.iv = 70, .lvl = 14, .species = SPECIES_CHINCHOU, .moves = {MOVE_WATER_GUN, MOVE_THUNDER_SHOCK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC}},
    {.iv = 255, .lvl = 14, .species = SPECIES_BULBASAUR, .moves = {MOVE_VINE_WHIP, MOVE_LEECH_SEED, MOVE_TACKLE, MOVE_GROWL}},
};

// Player Pichu -> Blue Fire + Green Ditto branch.
static const struct TrainerMonNoItemCustomMoves sParty_BlueGreenRoute4FireDitto[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_FLAREON, .moves = {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_SAND_ATTACK, MOVE_HELPING_HAND}},
    {.iv = 255, .lvl = 16, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_NONE, MOVE_NONE}},
    {.iv = 70, .lvl = 14, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_GROWL}},
    {.iv = 255, .lvl = 14, .species = SPECIES_GROWLITHE, .moves = {MOVE_EMBER, MOVE_BITE, MOVE_LEER, MOVE_ROAR}},
};

// Player Ditto -> Blue Electric + Green Espeon branch.
static const struct TrainerMonNoItemCustomMoves sParty_BlueGreenRoute4ElectricEevee[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_PIKACHU, .moves = {MOVE_THUNDERBOLT, MOVE_QUICK_ATTACK, MOVE_BRICK_BREAK, MOVE_THUNDER_WAVE}},
    {.iv = 255, .lvl = 16, .species = SPECIES_EEVEE, .moves = {MOVE_TACKLE, MOVE_HELPING_HAND, MOVE_SAND_ATTACK, MOVE_GROWL}},
    {.iv = 70, .lvl = 14, .species = SPECIES_VOLTORB, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SONIC_BOOM, MOVE_ROLLOUT}},
    {.iv = 255, .lvl = 15, .species = SPECIES_MAGIKARP, .moves = {MOVE_TACKLE, MOVE_SPLASH, MOVE_NONE, MOVE_NONE}},
};
'''
parties.write_text(s)

trainers = Path("src/data/trainers.h")
s = trainers.read_text()
if "[TRAINER_BLUE_GREEN_ROUTE4_WATER_PIKACHU]" not in s:
    records = r'''
    [TRAINER_BLUE_GREEN_ROUTE4_WATER_PIKACHU] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("BLUE & GREEN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BlueGreenRoute4WaterPikachu),
    },
    [TRAINER_BLUE_GREEN_ROUTE4_FIRE_DITTO] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("BLUE & GREEN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BlueGreenRoute4FireDitto),
    },
    [TRAINER_BLUE_GREEN_ROUTE4_ELECTRIC_EEVEE] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("BLUE & GREEN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BlueGreenRoute4ElectricEevee),
    },
'''
    close = s.rfind("\n};")
    if close < 0:
        raise SystemExit("trainer table closing brace not found")
    s = s[:close] + "\n" + records + s[close:]
trainers.write_text(s)

scripts = Path("data/maps/Route4/scripts.inc")
scripts.write_text(r'''Route4_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_OnTransition
	.byte 0

Route4_OnTransition::
	setvar VAR_TEMP_1, 0
	call_if_eq VAR_STARTER_MON, 0, Route4_EventScript_CheckWaterPikachu
	call_if_eq VAR_STARTER_MON, 1, Route4_EventScript_CheckFireDitto
	call_if_eq VAR_STARTER_MON, 2, Route4_EventScript_CheckElectricEevee
	goto_if_eq VAR_TEMP_1, 1, Route4_EventScript_ShowBlueGreen
	goto Route4_EventScript_HideBlueGreen
	end

Route4_EventScript_CheckWaterPikachu::
	checktrainerflag TRAINER_BLUE_GREEN_ROUTE4_WATER_PIKACHU
	goto_if TRUE, Route4_EventScript_CheckDone
	setvar VAR_TEMP_1, 1
	return

Route4_EventScript_CheckFireDitto::
	checktrainerflag TRAINER_BLUE_GREEN_ROUTE4_FIRE_DITTO
	goto_if TRUE, Route4_EventScript_CheckDone
	setvar VAR_TEMP_1, 1
	return

Route4_EventScript_CheckElectricEevee::
	checktrainerflag TRAINER_BLUE_GREEN_ROUTE4_ELECTRIC_EEVEE
	goto_if TRUE, Route4_EventScript_CheckDone
	setvar VAR_TEMP_1, 1
	return

Route4_EventScript_CheckDone::
	return

Route4_EventScript_ShowBlueGreen::
	showobjectat 8, MAP_ROUTE4
	showobjectat 9, MAP_ROUTE4
	end

Route4_EventScript_HideBlueGreen::
	hideobjectat 8, MAP_ROUTE4
	hideobjectat 9, MAP_ROUTE4
	end

Route4_EventScript_BlueGreenTrigger::
	setvar VAR_LAST_TALKED, 8
	goto Route4_EventScript_BlueGreen
	end

Route4_EventScript_BlueGreen::
	lockall
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, Route4_EventScript_NotEnoughMons
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_ENCOUNTER_RIVAL, 0
	faceplayer
	msgbox Route4_Text_BlueArrival
	call_if_eq VAR_STARTER_MON, 0, Route4_EventScript_BlueWaterIntro
	call_if_eq VAR_STARTER_MON, 1, Route4_EventScript_BlueFireIntro
	call_if_eq VAR_STARTER_MON, 2, Route4_EventScript_BlueElectricIntro
	msgbox Route4_Text_BlueCallsGreen
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenReply
	goto_if_eq VAR_STARTER_MON, 0, Route4_EventScript_BattleWaterPikachu
	goto_if_eq VAR_STARTER_MON, 1, Route4_EventScript_BattleFireDitto
	goto_if_eq VAR_STARTER_MON, 2, Route4_EventScript_BattleElectricEevee
	releaseall
	end

Route4_EventScript_BlueWaterIntro::
	msgbox Route4_Text_BlueWaterIntro
	return

Route4_EventScript_BlueFireIntro::
	msgbox Route4_Text_BlueFireIntro
	return

Route4_EventScript_BlueElectricIntro::
	msgbox Route4_Text_BlueElectricIntro
	return

Route4_EventScript_BattleWaterPikachu::
	trainerbattle_double TRAINER_BLUE_GREEN_ROUTE4_WATER_PIKACHU, Route4_Text_GreenReady, Route4_Text_BlueGreenDefeat, Route4_Text_NeedTwoPokemon, Route4_EventScript_BlueGreenAfterBattle
	end

Route4_EventScript_BattleFireDitto::
	trainerbattle_double TRAINER_BLUE_GREEN_ROUTE4_FIRE_DITTO, Route4_Text_GreenReady, Route4_Text_BlueGreenDefeat, Route4_Text_NeedTwoPokemon, Route4_EventScript_BlueGreenAfterBattle
	end

Route4_EventScript_BattleElectricEevee::
	trainerbattle_double TRAINER_BLUE_GREEN_ROUTE4_ELECTRIC_EEVEE, Route4_Text_GreenReady, Route4_Text_BlueGreenDefeat, Route4_Text_NeedTwoPokemon, Route4_EventScript_BlueGreenAfterBattle
	end

Route4_EventScript_BlueGreenAfterBattle::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BluePostBattle
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenPostBattle
	closemessage
	fadedefaultbgm
	hideobjectat 8, MAP_ROUTE4
	hideobjectat 9, MAP_ROUTE4
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route4_EventScript_NotEnoughMons::
	msgbox Route4_Text_NeedTwoPokemon
	releaseall
	end

Route4_EventScript_Unused::
	end

Route4_EventScript_Woman::
	msgbox Route4_Text_TrippedOverGeodude, MSGBOX_NPC
	end

Route4_EventScript_MtMoonSign::
	msgbox Route4_Text_MtMoonEntrance, MSGBOX_SIGN
	end

Route4_EventScript_RouteSign::
	msgbox Route4_Text_RouteSign, MSGBOX_SIGN
	end
''')

text = Path("data/maps/Route4/text.inc")
s = text.read_text()
if "Route4_Text_BlueArrival::" not in s:
    s += r'''

Route4_Text_BlueArrival::
    .string "RED! You made it through MT. MOON!\n"
    .string "LET'S GOOOOOO!$"

Route4_Text_BlueWaterIntro::
    .string "Okay, you HAVE to see this.\p"
    .string "Ditto and Chinchou are ready!$"

Route4_Text_BlueFireIntro::
    .string "Okay, you HAVE to see this.\p"
    .string "Remember Eevee? Check him out now!\p"
    .string "And dude, I found a PONYTA!$"

Route4_Text_BlueElectricIntro::
    .string "Okay, you HAVE to see this.\p"
    .string "Pichu evolved! Check out PIKACHU!\p"
    .string "And I found a Voltorb!$"

Route4_Text_BlueCallsGreen::
    .string "GREEN! We're doing this!$"

Route4_Text_GreenReply::
    .string "Two against one?\p"
    .string "That was the idea.$"

Route4_Text_GreenReady::
    .string "Ready, RED?$"

Route4_Text_BlueGreenDefeat::
    .string "No way! You beat both of us?$"

Route4_Text_BluePostBattle::
    .string "THAT WAS SICK!\p"
    .string "We gotta do that again!$"

Route4_Text_GreenPostBattle::
    .string "Separately next time.\p"
    .string "I want to know which one of us\n"
    .string "was the problem.$"

Route4_Text_NeedTwoPokemon::
    .string "Bring at least two POKéMON that can\n"
    .string "battle. Then we're doing this.$"
'''
text.write_text(s)

map_path = Path("data/maps/Route4/map.json")
data = json.loads(map_path.read_text())
if not any(str(o.get("local_id")) == "8" for o in data["object_events"]):
    blue = {
        "local_id": "8", "type": "object", "graphics_id": "OBJ_EVENT_GFX_BLUE",
        "x": 35, "y": 4, "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_LEFT",
        "movement_range_x": 1, "movement_range_y": 1, "trainer_type": "TRAINER_TYPE_NONE",
        "trainer_sight_or_berry_tree_id": "0", "script": "Route4_EventScript_BlueGreen", "flag": "0"
    }
    green = {
        "local_id": "9", "type": "object", "graphics_id": "OBJ_EVENT_GFX_GREEN_NORMAL",
        "x": 35, "y": 6, "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_LEFT",
        "movement_range_x": 1, "movement_range_y": 1, "trainer_type": "TRAINER_TYPE_NONE",
        "trainer_sight_or_berry_tree_id": "0", "script": "Route4_EventScript_BlueGreen", "flag": "0"
    }
    clone_index = next((i for i, o in enumerate(data["object_events"]) if o.get("type") == "clone"), len(data["object_events"]))
    data["object_events"][clone_index:clone_index] = [blue, green]
trigger = {
    "type": "trigger", "x": 34, "y": 5, "elevation": 3,
    "var": "VAR_TEMP_1", "var_value": "1", "script": "Route4_EventScript_BlueGreenTrigger"
}
if not any(e.get("script") == "Route4_EventScript_BlueGreenTrigger" for e in data["coord_events"]):
    data["coord_events"].append(trigger)
map_path.write_text(json.dumps(data, indent=2, ensure_ascii=False) + "\n")
