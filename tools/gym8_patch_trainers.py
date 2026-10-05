from pathlib import Path

path = Path("src/data/trainers.h")
text = path.read_text()

if "[TRAINER_SATOSHI_VIRIDIAN_PRACTICE]" in text:
    raise SystemExit(0)

anchor = "    [TRAINER_HIKER_CLIFF_PEWTER] = {"
block = '''    [TRAINER_SATOSHI_VIRIDIAN_PRACTICE] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SATOSHI,
        .trainerName = _("SATOSHI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_SatoshiViridianPractice),
    },
    [TRAINER_SATOSHI_VIRIDIAN_REMATCH] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SATOSHI,
        .trainerName = _("SATOSHI"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_SatoshiViridianRematch),
    },
'''

if anchor not in text:
    raise SystemExit("expected trainer insertion anchor not found")

path.write_text(text.replace(anchor, block + anchor, 1))
