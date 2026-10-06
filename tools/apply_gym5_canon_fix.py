from pathlib import Path
import re

PARTIES = Path("src/data/trainer_parties.h")
TRAINERS = Path("src/data/trainers.h")
GYM_SCRIPTS = Path("data/maps/FuchsiaCity_Gym/scripts.inc")
GYM_TEXT = Path("data/maps/FuchsiaCity_Gym/text.inc")
CITY_TEXT = Path("data/maps/FuchsiaCity/text.inc")

parties = PARTIES.read_text()
trainers = TRAINERS.read_text()
gym_scripts = GYM_SCRIPTS.read_text()
gym_text = GYM_TEXT.read_text()
city_text = CITY_TEXT.read_text()


def replace_party(name, struct_type, mons):
    global parties
    pat = re.compile(rf"static const struct \w+ {re.escape(name)}\[\] = \{{.*?\n\}};", re.S)
    matches = list(pat.finditer(parties))
    if len(matches) != 1:
        raise SystemExit(f"Expected exactly one party block for {name}, found {len(matches)}")
    m = matches[0]
    lines = [f"static const struct {struct_type} {name}[] = {{"]
    for mon in mons:
        lines.append("    {")
        lines.append("        .iv = 0,")
        lines.append(f"        .lvl = {mon['lvl']},")
        lines.append(f"        .species = SPECIES_{mon['species']},")
        if "item" in mon:
            lines.append(f"        .heldItem = {mon['item']},")
        if "moves" in mon:
            moves = ", ".join(f"MOVE_{move}" for move in mon["moves"])
            lines.append(f"        .moves = {{{moves}}},")
        lines.append("    },")
    lines.append("};")
    parties = parties[:m.start()] + "\n".join(lines) + parties[m.end():]


replace_party("sParty_JugglerNate", "TrainerMonNoItemDefaultMoves", [
    {"species": "SPINDA", "lvl": 34},
    {"species": "DUNSPARCE", "lvl": 34},
])
replace_party("sParty_JugglerKayden", "TrainerMonItemDefaultMoves", [
    {"species": "ZANGOOSE", "lvl": 38, "item": "ITEM_SITRUS_BERRY"},
])
replace_party("sParty_JugglerKirk", "TrainerMonNoItemDefaultMoves", [
    {"species": "AIPOM", "lvl": 31},
    {"species": "GIRAFARIG", "lvl": 31},
    {"species": "SMEARGLE", "lvl": 31},
    {"species": "CASTFORM", "lvl": 31},
])
replace_party("sParty_TamerEdgar", "TrainerMonNoItemDefaultMoves", [
    {"species": "KANGASKHAN", "lvl": 33},
    {"species": "URSARING", "lvl": 33},
    {"species": "MILTANK", "lvl": 33},
])
replace_party("sParty_TamerPhil", "TrainerMonNoItemDefaultMoves", [
    {"species": "STANTLER", "lvl": 34},
    {"species": "DODRIO", "lvl": 34},
])
replace_party("sParty_JugglerShawn", "TrainerMonNoItemDefaultMoves", [
    {"species": "PORYGON", "lvl": 34},
    {"species": "WIGGLYTUFF", "lvl": 34},
])
replace_party("sParty_LeaderKoga", "TrainerMonItemCustomMoves", [
    {"species": "KECLEON", "lvl": 37, "item": "ITEM_NONE", "moves": ["SHADOW_BALL", "BRICK_BREAK", "SLASH", "SCREECH"]},
    {"species": "PERSIAN", "lvl": 38, "item": "ITEM_NONE", "moves": ["SLASH", "FAKE_OUT", "BITE", "SCREECH"]},
    {"species": "PORYGON2", "lvl": 39, "item": "ITEM_NONE", "moves": ["TRI_ATTACK", "PSYBEAM", "RECOVER", "AGILITY"]},
    {"species": "EXPLOUD", "lvl": 41, "item": "ITEM_NONE", "moves": ["RETURN", "BRICK_BREAK", "SHADOW_BALL", "HOWL"]},
    {"species": "TAUROS", "lvl": 43, "item": "ITEM_SILK_SCARF", "moves": ["BODY_SLAM", "EARTHQUAKE", "ROCK_TOMB", "SCARY_FACE"]},
])

party_macros = {
    "sParty_JugglerNate": "NO_ITEM_DEFAULT_MOVES",
    "sParty_JugglerKayden": "ITEM_DEFAULT_MOVES",
    "sParty_JugglerKirk": "NO_ITEM_DEFAULT_MOVES",
    "sParty_TamerEdgar": "NO_ITEM_DEFAULT_MOVES",
    "sParty_TamerPhil": "NO_ITEM_DEFAULT_MOVES",
    "sParty_JugglerShawn": "NO_ITEM_DEFAULT_MOVES",
    "sParty_LeaderKoga": "ITEM_CUSTOM_MOVES",
}
for party_name, macro in party_macros.items():
    trainers, count = re.subn(
        rf"\b[A-Z_]+\({re.escape(party_name)}\)",
        f"{macro}({party_name})",
        trainers,
        count=1,
    )
    if count != 1:
        raise SystemExit(f"Trainer party reference replacement failed for {party_name}: {count}")

koga_match = re.search(r"\[TRAINER_LEADER_KOGA\]\s*=\s*\{.*?\n    \},", trainers, re.S)
if not koga_match:
    raise SystemExit("Koga trainer metadata record not found")
koga_record = koga_match.group(0)
required_koga_metadata = [
    ".items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL}",
    ".aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY",
    ".party = ITEM_CUSTOM_MOVES(sParty_LeaderKoga)",
]
for needle in required_koga_metadata:
    if needle not in koga_record:
        raise SystemExit(f"Koga metadata does not match locked stock-AI/healing package: {needle}")

required_script_fragments = [
    "setflag FLAG_BADGE05_GET",
    "set_gym_trainers 5",
    "goto_if_unset FLAG_GOT_TM06_FROM_KOGA, FuchsiaCity_Gym_EventScript_GiveTM42",
    "giveitem_msg FuchsiaCity_Gym_Text_ReceivedTM42FromKoga, ITEM_TM42",
    "setflag FLAG_GOT_TM06_FROM_KOGA",
    "FuchsiaCity_Gym_Text_KogaExplainVeilBadge",
    "FuchsiaCity_Gym_Text_KogaExplainTM42",
]
for needle in required_script_fragments:
    if needle not in gym_scripts:
        raise SystemExit(f"Locked Fuchsia script fragment missing: {needle}")
if "giveitem_msg FuchsiaCity_Gym_Text_ReceivedTM06FromKoga, ITEM_TM06" in gym_scripts:
    raise SystemExit("Legacy TM06 reward is still active")

required_dialogue_fragments = [
    "What you notice first is exactly",
    "You saw through the distraction!",
    "I'll show you something easy to",
    "Hah! You didn't take the bait!",
    "Watch closely! The trick is not",
    "You kept your attention where it",
    "Normal POKéMON can look",
    "You were ready for more than one",
    "Go ahead. Decide what my plan is",
    "So much for catching you by",
    "By the time you reach KOGA, you",
    "You didn't give me the opening I",
    "master of\\n\"\n    .string \"techniques that leave an opponent",
    "You refused every false",
    "the VEIL BADGE!",
    "use SURF outside of battle",
    "TM42 contains\\n\"\n    .string \"FACADE.",
    "Do not battle the opponent you",
]
for needle in required_dialogue_fragments:
    if needle not in gym_text:
        raise SystemExit(f"Locked Fuchsia dialogue fragment missing: {needle}")

# Gym Guide dialogue was not part of the locked custom Trainer/Leader dialogue package.
# Restore the pre-redesign guide text instead of retaining invented copy from the earlier bad squash.
gym_guide_pattern = re.compile(
    r"FuchsiaCity_Gym_Text_GymGuyAdvice::.*?(?=FuchsiaCity_Gym_Text_GymStatue::)",
    re.S,
)
gym_guide_replacement = r'''FuchsiaCity_Gym_Text_GymGuyAdvice::
    .string "Yo!\n"
    .string "Champ in the making!\p"
    .string "FUCHSIA GYM is a tricked-up place.\n"
    .string "It's riddled with invisible walls!\p"
    .string "KOGA might appear close, but he's\n"
    .string "blocked off.\p"
    .string "You have to find gaps in the walls\n"
    .string "to reach him.$"

FuchsiaCity_Gym_Text_GymGuyPostVictory::
    .string "It's amazing how ninja can terrify,\n"
    .string "even now!$"

'''
gym_text, guide_count = gym_guide_pattern.subn(lambda _: gym_guide_replacement, gym_text, count=1)
if guide_count != 1:
    raise SystemExit(f"Gym Guide text replacement failed: {guide_count}")

old_sign = '''FuchsiaCity_Text_GymSign::
    .string "FUCHSIA CITY POKéMON GYM\\n"
    .string "LEADER: KOGA\\l"
    .string "The Poisonous Ninja Master$"'''
new_sign = '''FuchsiaCity_Text_GymSign::
    .string "FUCHSIA CITY POKéMON GYM\\n"
    .string "LEADER: KOGA\\l"
    .string "Master of Misdirection$"'''
if old_sign in city_text:
    city_text = city_text.replace(old_sign, new_sign, 1)
elif new_sign not in city_text:
    raise SystemExit("Fuchsia Gym exterior sign did not match expected old or locked text")

PARTIES.write_text(parties)
TRAINERS.write_text(trainers)
GYM_TEXT.write_text(gym_text)
CITY_TEXT.write_text(city_text)
