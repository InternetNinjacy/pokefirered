from pathlib import Path


def replace_once(path, old, new):
    p = Path(path)
    text = p.read_text()
    count = text.count(old)
    if count != 1:
        raise SystemExit(f"{path}: expected exactly one match, found {count}: {old[:80]!r}")
    p.write_text(text.replace(old, new, 1))


def insert_before_last(path, marker, addition):
    p = Path(path)
    text = p.read_text()
    pos = text.rfind(marker)
    if pos < 0:
        raise SystemExit(f"{path}: final marker not found")
    p.write_text(text[:pos] + addition + text[pos:])

# 1) Six generic trainer item slots and matching battle-history capacity.
replace_once(
    "include/battle.h",
    "#define MAX_TRAINER_ITEMS 4",
    "#define MAX_TRAINER_ITEMS 6")
replace_once(
    "include/battle.h",
    "u16 trainerItems[MAX_BATTLERS_COUNT];",
    "u16 trainerItems[MAX_TRAINER_ITEMS];")

# 2) Generic AI classification for trainer-use Max Revive.
replace_once(
    "include/battle_ai_switch_items.h",
    "    AI_ITEM_GUARD_SPECS,\n    AI_ITEM_NOT_RECOGNIZABLE",
    "    AI_ITEM_GUARD_SPECS,\n    AI_ITEM_REVIVE,\n    AI_ITEM_NOT_RECOGNIZABLE")

replace_once(
    "src/battle_ai_switch_items.c",
    "static u8 GetAI_ItemType(u8 itemId, const u8 *itemEffect) // NOTE: should take u16 as item Id argument\n{\n    if (itemId == ITEM_FULL_RESTORE)\n        return AI_ITEM_FULL_RESTORE;",
    "static u8 GetAI_ItemType(u16 itemId, const u8 *itemEffect)\n{\n    if (itemId == ITEM_MAX_REVIVE)\n        return AI_ITEM_REVIVE;\n    if (itemId == ITEM_FULL_RESTORE)\n        return AI_ITEM_FULL_RESTORE;")

replace_once(
    "src/battle_ai_switch_items.c",
    "        case AI_ITEM_GUARD_SPECS:\n            battlerSide = GetBattlerSide(gActiveBattler);\n            if (gDisableStructs[gActiveBattler].isFirstTurn && gSideTimers[battlerSide].mistTimer == 0)\n                shouldUse = TRUE;\n            break;\n        case AI_ITEM_NOT_RECOGNIZABLE:",
    "        case AI_ITEM_GUARD_SPECS:\n            battlerSide = GetBattlerSide(gActiveBattler);\n            if (gDisableStructs[gActiveBattler].isFirstTurn && gSideTimers[battlerSide].mistTimer == 0)\n                shouldUse = TRUE;\n            break;\n        case AI_ITEM_REVIVE:\n            *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) = 0;\n            for (paramOffset = 0; paramOffset < PARTY_SIZE; paramOffset++)\n            {\n                u16 species = GetMonData(&gEnemyParty[paramOffset], MON_DATA_SPECIES_OR_EGG);\n                if (species != SPECIES_NONE\n                 && species != SPECIES_EGG\n                 && GetMonData(&gEnemyParty[paramOffset], MON_DATA_HP) == 0)\n                {\n                    *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) = paramOffset + 1;\n                    shouldUse = TRUE;\n                    break;\n                }\n            }\n            break;\n        case AI_ITEM_NOT_RECOGNIZABLE:")

# 3) Route generic trainer Max Revive to the fainted reserve selected by the AI.
replace_once(
    "src/battle_script_commands.c",
    "static void Cmd_useitemonopponent(void)\n{\n    gBattlerInMenuId = gBattlerAttacker;\n    PokemonUseItemEffects(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]], gLastUsedItem, gBattlerPartyIndexes[gBattlerAttacker], 0, TRUE);\n    gBattlescriptCurrInstr++;\n}",
    "static void Cmd_useitemonopponent(void)\n{\n    u8 partyIndex = gBattlerPartyIndexes[gBattlerAttacker];\n\n    gBattlerInMenuId = gBattlerAttacker;\n    if (gLastUsedItem == ITEM_MAX_REVIVE\n     && *(gBattleStruct->AI_itemType + gBattlerAttacker / 2) == AI_ITEM_REVIVE\n     && *(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) != 0)\n        partyIndex = *(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) - 1;\n\n    PokemonUseItemEffects(&gEnemyParty[partyIndex], gLastUsedItem, partyIndex, 0, TRUE);\n    gBattlescriptCurrInstr++;\n}")

# 4) Joey has a battle-specific 50,000 base payout. moneyMultiplier remains native,
# so Amulet Coin continues to double the reward normally.
replace_once(
    "src/battle_script_commands.c",
    "            party4 = gTrainers[gTrainerBattleOpponent_A].party.ItemCustomMoves; // Needed to Match. Has no effect.\n            moneyReward = 4 * lastMonLevel * gBattleStruct->moneyMultiplier * (gBattleTypeFlags & BATTLE_TYPE_DOUBLE ? 2 : 1) * gTrainerMoneyTable[i].value;",
    "            party4 = gTrainers[gTrainerBattleOpponent_A].party.ItemCustomMoves; // Needed to Match. Has no effect.\n            if (gTrainerBattleOpponent_A == TRAINER_YOUNGSTER_JOEY)\n                moneyReward = 50000 * gBattleStruct->moneyMultiplier;\n            else\n                moneyReward = 4 * lastMonLevel * gBattleStruct->moneyMultiplier * (gBattleTypeFlags & BATTLE_TYPE_DOUBLE ? 2 : 1) * gTrainerMoneyTable[i].value;")

# 5) Exact Joey Nature/EV/IV profile, applied after the ordinary trainer-party build.
replace_once(
    "src/battle_main.c",
    "                personalityValue += nameHash << 8;\n                fixedIV = partyData[i].iv * MAX_PER_STAT_IVS / 255;\n                CreateMon(&party[i], partyData[i].species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);\n                SetMonData(&party[i], MON_DATA_HELD_ITEM, &partyData[i].heldItem);\n\n                for (j = 0; j < MAX_MON_MOVES; j++)",
    "                personalityValue += nameHash << 8;\n                if (trainerNum == TRAINER_YOUNGSTER_JOEY)\n                {\n                    static const u8 sJoeyNatures[PARTY_SIZE] =\n                    {\n                        NATURE_TIMID, NATURE_MODEST, NATURE_MODEST,\n                        NATURE_BOLD, NATURE_ADAMANT, NATURE_TIMID\n                    };\n                    personalityValue += (sJoeyNatures[i] + NUM_NATURES - (personalityValue % NUM_NATURES)) % NUM_NATURES;\n                }\n                fixedIV = partyData[i].iv * MAX_PER_STAT_IVS / 255;\n                CreateMon(&party[i], partyData[i].species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);\n                SetMonData(&party[i], MON_DATA_HELD_ITEM, &partyData[i].heldItem);\n\n                for (j = 0; j < MAX_MON_MOVES; j++)")

replace_once(
    "src/battle_main.c",
    "            // Sam Edition Blue: force the authored Hidden Power Grass on League Manectric",
    "            if (trainerNum == TRAINER_YOUNGSTER_JOEY)\n            {\n                static const u8 sJoeyEvs[PARTY_SIZE][NUM_STATS] =\n                {\n                    {  4,   0,   0, 252, 252,   0}, // Zapdos\n                    {252,   0,   0,   0, 252,   4}, // Gardevoir\n                    {  4,   0,   0, 252, 252,   0}, // Moltres\n                    {252,   0, 252,   0,   0,   4}, // Articuno\n                    {  0, 252,   0, 252,   0,   4}, // Dragonite\n                    {  4,   0,   0, 252, 252,   0}, // Mewtwo\n                };\n                static const u8 sJoeyHpGrassIvs[NUM_STATS] = {31, 30, 31, 30, 30, 31};\n                u8 value;\n                u8 abilityNum = 0;\n\n                for (j = 0; j < NUM_STATS; j++)\n                {\n                    value = sJoeyEvs[i][j];\n                    SetMonData(&party[i], MON_DATA_HP_EV + j, &value);\n                    value = (i == 0 || i == 2) ? sJoeyHpGrassIvs[j] : 31;\n                    SetMonData(&party[i], MON_DATA_HP_IV + j, &value);\n                }\n                SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum);\n                CalculateMonStats(&party[i]);\n            }\n\n            // Sam Edition Blue: force the authored Hidden Power Grass on League Manectric")

# 6) Modular Joey party data.
replace_once(
    "src/data.c",
    "#include \"data/sam_blue_parties.h\"",
    "#include \"data/sam_blue_parties.h\"\n#include \"data/sam_joey_parties.h\"")

# 7) Activate Joey's reserved trainer ID.
replace_once(
    "include/constants/opponents.h",
    "#define NUM_TRAINERS                             807",
    "#define NUM_TRAINERS                             941")

# 8) Add Joey trainer record immediately before the final gTrainers array close.
joey_record = r'''    [TRAINER_YOUNGSTER_JOEY] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOEY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_MAX_REVIVE, ITEM_MAX_REVIVE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_HP_AWARE,
        .party = ITEM_CUSTOM_MOVES(sParty_YoungsterJoeySuperboss),
    },

'''
insert_before_last("src/data/trainers.h", "    };", joey_record)

# New modular party file.
Path("src/data/sam_joey_parties.h").write_text(r'''// Pokémon: Sam Edition — OAK-002 Youngster Joey superboss party.
// Exact Lv. 80 moves/items are authoritative here. Nature/EV/IV profiles are
// applied by the shared trainer-party constructor so the stock party format remains intact.
static const struct TrainerMonItemCustomMoves sParty_YoungsterJoeySuperboss[] =
{
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_ZAPDOS,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_THUNDERBOLT, MOVE_HIDDEN_POWER, MOVE_DRILL_PECK, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_GARDEVOIR,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_CALM_MIND, MOVE_WILL_O_WISP},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_MOLTRES,
        .heldItem = ITEM_WHITE_HERB,
        .moves = {MOVE_FIRE_BLAST, MOVE_SKY_ATTACK, MOVE_OVERHEAT, MOVE_HIDDEN_POWER},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_ARTICUNO,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_ROAR, MOVE_TOXIC, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE, MOVE_BRICK_BREAK},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_MEWTWO,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_PSYCHIC, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_RECOVER},
    },
};
''')

print("Chunk 3 Joey production patch applied.")
