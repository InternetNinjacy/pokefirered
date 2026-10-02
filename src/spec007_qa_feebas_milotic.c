#include "global.h"
#include "battle.h"
#include "gba/isagbprint.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokedex.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern u8 TypeCalc(u16 move, u8 attacker, u8 defender);
extern u8 AI_TypeCalc(u16 move, u16 targetSpecies, u8 targetAbility);

static void Log(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    QA_MGBA_DEBUG_STRING[i] = '\0';
    *QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    Log(text);
    for (;;);
}

static void MakeMon(struct Pokemon *mon, u16 species, u8 level)
{
    CreateMon(mon, species, level, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static bool8 MonHasMove(struct Pokemon *mon, u16 move)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMonData(mon, MON_DATA_MOVE1 + i) == move)
            return TRUE;
    }
    return FALSE;
}

static bool8 IndexInList(u8 index, const u8 *list, u8 count)
{
    u8 i;
    for (i = 0; i < count; i++)
        if (list[i] == index)
            return TRUE;
    return FALSE;
}

static void ExpectMachineSet(u16 species, const u8 *tmNumbers, u8 tmCount, const u8 *hmNumbers, u8 hmCount)
{
    struct Pokemon mon;
    u8 i;

    MakeMon(&mon, species, 50);

    for (i = 0; i < NUM_TECHNICAL_MACHINES; i++)
    {
        bool8 expected = IndexInList(i + 1, tmNumbers, tmCount);
        bool8 actual = CanMonLearnTMHM(&mon, i) != 0;
        if (actual != expected)
            Fail("SPEC007 FAIL exact TM matrix");
    }

    for (i = 0; i < NUM_HIDDEN_MACHINES; i++)
    {
        bool8 expected = IndexInList(i + 1, hmNumbers, hmCount);
        bool8 actual = CanMonLearnTMHM(&mon, NUM_TECHNICAL_MACHINES + i) != 0;
        if (actual != expected)
            Fail("SPEC007 FAIL exact HM matrix");
    }
}

static void CheckSpeciesData(void)
{
    const struct SpeciesInfo *feebas = &gSpeciesInfo[SPECIES_FEEBAS];
    const struct SpeciesInfo *milotic = &gSpeciesInfo[SPECIES_MILOTIC];

    if (feebas->baseHP != 20 || feebas->baseAttack != 15 || feebas->baseDefense != 20
     || feebas->baseSpAttack != 10 || feebas->baseSpDefense != 55 || feebas->baseSpeed != 80
     || feebas->types[0] != TYPE_WATER || feebas->types[1] != TYPE_WATER
     || feebas->catchRate != 255 || feebas->expYield != 61
     || feebas->evYield_Speed != 1 || feebas->evYield_HP != 0
     || feebas->evYield_Attack != 0 || feebas->evYield_Defense != 0
     || feebas->evYield_SpAttack != 0 || feebas->evYield_SpDefense != 0
     || feebas->itemCommon != ITEM_NONE || feebas->itemRare != ITEM_NONE
     || feebas->eggCycles != 20
     || feebas->friendship != 70 || feebas->growthRate != GROWTH_ERRATIC
     || feebas->eggGroups[0] != EGG_GROUP_WATER_1 || feebas->eggGroups[1] != EGG_GROUP_DRAGON
     || feebas->abilities[0] != ABILITY_SWIFT_SWIM || feebas->abilities[1] != ABILITY_NONE
     || feebas->bodyColor != BODY_COLOR_BROWN)
        Fail("SPEC007 FAIL Feebas species data");

    if (milotic->baseHP != 95 || milotic->baseAttack != 60 || milotic->baseDefense != 79
     || milotic->baseSpAttack != 100 || milotic->baseSpDefense != 125 || milotic->baseSpeed != 81
     || milotic->types[0] != TYPE_WATER || milotic->types[1] != TYPE_PSYCHIC
     || milotic->catchRate != 60 || milotic->expYield != 213
     || milotic->evYield_SpDefense != 2 || milotic->evYield_HP != 0
     || milotic->evYield_Attack != 0 || milotic->evYield_Defense != 0
     || milotic->evYield_Speed != 0 || milotic->evYield_SpAttack != 0
     || milotic->itemCommon != ITEM_NONE || milotic->itemRare != ITEM_NONE
     || milotic->eggCycles != 20
     || milotic->friendship != 70 || milotic->growthRate != GROWTH_ERRATIC
     || milotic->eggGroups[0] != EGG_GROUP_WATER_1 || milotic->eggGroups[1] != EGG_GROUP_DRAGON
     || milotic->abilities[0] != ABILITY_MARVEL_SCALE || milotic->abilities[1] != ABILITY_NONE
     || milotic->bodyColor != BODY_COLOR_PINK)
        Fail("SPEC007 FAIL Milotic species data");
}

static void CheckLevelTwentyFlow(void)
{
    struct Pokemon mon;
    u8 level = 20;
    u16 none = MOVE_NONE;
    u16 learned;

    MakeMon(&mon, SPECIES_FEEBAS, 19);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_NONE)
        Fail("SPEC007 FAIL Feebas evolves early");

    SetMonData(&mon, MON_DATA_LEVEL, &level);
    SetMonData(&mon, MON_DATA_MOVE1, &none);

    learned = MonTryLearningNewMove(&mon, TRUE);
    if (learned != MOVE_WATER_PULSE || !MonHasMove(&mon, MOVE_WATER_PULSE))
        Fail("SPEC007 FAIL Water Pulse at level 20");

    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_MILOTIC)
        Fail("SPEC007 FAIL level 20 evolution");

    MakeMon(&mon, SPECIES_MILOTIC, 21);
    if (!MonHasMove(&mon, MOVE_PSYBEAM))
        Fail("SPEC007 FAIL Psybeam level 21");

    MakeMon(&mon, SPECIES_MILOTIC, 40);
    if (!MonHasMove(&mon, MOVE_PSYCHIC))
        Fail("SPEC007 FAIL Psychic level 40");

    MakeMon(&mon, SPECIES_MILOTIC, 55);
    if (!MonHasMove(&mon, MOVE_MIRROR_COAT))
        Fail("SPEC007 FAIL Mirror Coat level 55");
}

static void CheckMachineCompatibility(void)
{
    static const u8 feebasTms[] = {2,4,5,14,40,42,55,57,58,59,68};
    static const u8 miloticTms[] = {2,3,4,5,14,40,41,42,51,52,53,54,55,57,58,59,60,68};
    static const u8 waterHms[] = {3,7};

    ExpectMachineSet(SPECIES_FEEBAS, feebasTms, ARRAY_COUNT(feebasTms), waterHms, ARRAY_COUNT(waterHms));
    ExpectMachineSet(SPECIES_MILOTIC, miloticTms, ARRAY_COUNT(miloticTms), waterHms, ARRAY_COUNT(waterHms));
}

static void SetBattleMonTypes(u8 battler, u16 species)
{
    gBattleMons[battler].type1 = gSpeciesInfo[species].types[0];
    gBattleMons[battler].type2 = gSpeciesInfo[species].types[1];
    gBattleMons[battler].ability = ABILITY_NONE;
    gBattleMons[battler].status2 = 0;
}

static void CheckBattleTyping(void)
{
    u8 flags;

    SetBattleMonTypes(0, SPECIES_RATTATA);
    SetBattleMonTypes(1, SPECIES_MILOTIC);

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_BRICK_BREAK, 0, 1);
    if (gBattleMoveDamage != 50 || !(flags & MOVE_RESULT_NOT_VERY_EFFECTIVE))
        Fail("SPEC007 FAIL Psychic resistance");

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_CRUNCH, 0, 1);
    if (gBattleMoveDamage != 200 || !(flags & MOVE_RESULT_SUPER_EFFECTIVE))
        Fail("SPEC007 FAIL Psychic weakness");

    SetBattleMonTypes(0, SPECIES_MILOTIC);
    SetBattleMonTypes(1, SPECIES_RATTATA);

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_SURF, 0, 1);
    if (gBattleMoveDamage != 150 || (flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        Fail("SPEC007 FAIL Water STAB");

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_PSYCHIC, 0, 1);
    if (gBattleMoveDamage != 150 || (flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        Fail("SPEC007 FAIL Psychic STAB");

    flags = AI_TypeCalc(MOVE_BRICK_BREAK, SPECIES_MILOTIC, ABILITY_NONE);
    if (!(flags & MOVE_RESULT_NOT_VERY_EFFECTIVE) || (flags & MOVE_RESULT_SUPER_EFFECTIVE))
        Fail("SPEC007 FAIL AI Psychic resistance");

    flags = AI_TypeCalc(MOVE_CRUNCH, SPECIES_MILOTIC, ABILITY_NONE);
    if (!(flags & MOVE_RESULT_SUPER_EFFECTIVE) || (flags & MOVE_RESULT_NOT_VERY_EFFECTIVE))
        Fail("SPEC007 FAIL AI Psychic weakness");
}

static void CheckPokedexRuntime(void)
{
    if (NATIONAL_DEX_FEEBAS != 349 || NATIONAL_DEX_MILOTIC != 350)
        Fail("SPEC007 FAIL National Dex constants");
    if (SpeciesToNationalPokedexNum(SPECIES_FEEBAS) != NATIONAL_DEX_FEEBAS
     || SpeciesToNationalPokedexNum(SPECIES_MILOTIC) != NATIONAL_DEX_MILOTIC)
        Fail("SPEC007 FAIL species Dex mapping");
    if (GetPokedexHeightWeight(NATIONAL_DEX_FEEBAS, 0) != 6
     || GetPokedexHeightWeight(NATIONAL_DEX_FEEBAS, 1) != 74
     || GetPokedexHeightWeight(NATIONAL_DEX_MILOTIC, 0) != 62
     || GetPokedexHeightWeight(NATIONAL_DEX_MILOTIC, 1) != 1620)
        Fail("SPEC007 FAIL Dex height weight");
}

void Spec007QaFeebasMilotic_RunRuntimeQa(void)
{
    MgbaOpen();
    CheckSpeciesData();
    CheckLevelTwentyFlow();
    CheckMachineCompatibility();
    CheckBattleTyping();
    CheckPokedexRuntime();

    Log("SPEC007 QA PASS species lv20 typing machines dex");
    for (;;);
}
