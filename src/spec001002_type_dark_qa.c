#include "global.h"
#include "battle.h"
#include "battle_script_commands.h"
#include "gba/isagbprint.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static void QaLog(const char *text)
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
    QaLog(text);
    for (;;);
}

static void LoadBattleTypes(u8 battler, u16 species)
{
    gBattleMons[battler].species = species;
    gBattleMons[battler].type1 = gSpeciesInfo[species].types[0];
    gBattleMons[battler].type2 = gSpeciesInfo[species].types[1];
    gBattleMons[battler].ability = ABILITY_NONE;
    gBattleMons[battler].hp = 100;
    gBattleMons[battler].maxHP = 100;
    gBattleMons[battler].status2 = 0;
}

static s32 TypeDamage(u16 move, u16 attackerSpecies, u16 defenderSpecies, u8 *flags)
{
    LoadBattleTypes(0, attackerSpecies);
    LoadBattleTypes(1, defenderSpecies);
    gBattleMoveDamage = 100;
    *flags = TypeCalc(move, 0, 1);
    return gBattleMoveDamage;
}

static void CheckTypeFields(void)
{
    static const u16 pureFlying[] =
    {
        SPECIES_PIDGEY, SPECIES_PIDGEOTTO, SPECIES_PIDGEOT,
        SPECIES_SPEAROW, SPECIES_FARFETCHD, SPECIES_DODUO, SPECIES_DODRIO
    };
    static const u16 normalDark[] =
    {
        SPECIES_RATTATA, SPECIES_RATICATE, SPECIES_MEOWTH, SPECIES_PERSIAN, SPECIES_TAUROS
    };
    u8 i;

    for (i = 0; i < ARRAY_COUNT(pureFlying); i++)
        if (gSpeciesInfo[pureFlying[i]].types[0] != TYPE_FLYING
         || gSpeciesInfo[pureFlying[i]].types[1] != TYPE_FLYING)
            Fail("SPEC001002 FAIL pure Flying field");

    if (gSpeciesInfo[SPECIES_PSYDUCK].types[0] != TYPE_WATER
     || gSpeciesInfo[SPECIES_PSYDUCK].types[1] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_GOLDUCK].types[0] != TYPE_WATER
     || gSpeciesInfo[SPECIES_GOLDUCK].types[1] != TYPE_PSYCHIC)
        Fail("SPEC001002 FAIL Psyduck family types");

    if (gSpeciesInfo[SPECIES_FEAROW].types[0] != TYPE_DARK
     || gSpeciesInfo[SPECIES_FEAROW].types[1] != TYPE_FLYING)
        Fail("SPEC001002 FAIL Fearow exception");

    for (i = 0; i < ARRAY_COUNT(normalDark); i++)
        if (gSpeciesInfo[normalDark[i]].types[0] != TYPE_NORMAL
         || gSpeciesInfo[normalDark[i]].types[1] != TYPE_DARK)
            Fail("SPEC001002 FAIL Normal Dark field");

    if (gSpeciesInfo[SPECIES_EKANS].types[0] != TYPE_POISON
     || gSpeciesInfo[SPECIES_EKANS].types[1] != TYPE_DARK
     || gSpeciesInfo[SPECIES_ARBOK].types[0] != TYPE_POISON
     || gSpeciesInfo[SPECIES_ARBOK].types[1] != TYPE_DARK)
        Fail("SPEC001002 FAIL Ekans family types");

    if (gSpeciesInfo[SPECIES_DROWZEE].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_DROWZEE].types[1] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_HYPNO].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_HYPNO].types[1] != TYPE_DARK)
        Fail("SPEC001002 FAIL Drowzee Hypno types");

    if (gSpeciesInfo[SPECIES_CUBONE].types[0] != TYPE_GROUND
     || gSpeciesInfo[SPECIES_CUBONE].types[1] != TYPE_DARK
     || gSpeciesInfo[SPECIES_MAROWAK].types[0] != TYPE_GROUND
     || gSpeciesInfo[SPECIES_MAROWAK].types[1] != TYPE_DARK)
        Fail("SPEC001002 FAIL Cubone family types");
}

static void CheckPureFlyingBattleRules(void)
{
    u8 flags;
    s32 flyingStab = TypeDamage(MOVE_AERIAL_ACE, SPECIES_PIDGEY, SPECIES_CASTFORM, &flags);
    s32 normalNoStab = TypeDamage(MOVE_QUICK_ATTACK, SPECIES_PIDGEY, SPECIES_CASTFORM, &flags);
    s32 fighting = TypeDamage(MOVE_BRICK_BREAK, SPECIES_PSYDUCK, SPECIES_PIDGEY, &flags);
    s32 ghost = TypeDamage(MOVE_SHADOW_BALL, SPECIES_PSYDUCK, SPECIES_PIDGEY, &flags);
    s32 ground = TypeDamage(MOVE_EARTHQUAKE, SPECIES_PSYDUCK, SPECIES_PIDGEY, &flags);

    if (flyingStab != 150 || normalNoStab != 100)
        Fail("SPEC001002 FAIL Flying STAB regression");
    if (fighting != 50)
        Fail("SPEC001002 FAIL Flying Fighting resist");
    if (ghost != 100 || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("SPEC001002 FAIL obsolete Normal Ghost immunity");
    if (ground != 0 || !(flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("SPEC001002 FAIL Flying Ground immunity");
}

static void CheckPsyduckFamilyBattleRules(void)
{
    u8 flags;
    s32 waterStab = TypeDamage(MOVE_WATER_GUN, SPECIES_PSYDUCK, SPECIES_CASTFORM, &flags);
    s32 psychicStab = TypeDamage(MOVE_CONFUSION, SPECIES_PSYDUCK, SPECIES_CASTFORM, &flags);
    static const u16 weaknessMoves[] =
    {
        MOVE_THUNDERBOLT, MOVE_RAZOR_LEAF, MOVE_SIGNAL_BEAM, MOVE_SHADOW_BALL, MOVE_BITE
    };
    u8 i;

    if (waterStab != 150 || psychicStab != 150)
        Fail("SPEC001002 FAIL Water Psychic STAB");

    for (i = 0; i < ARRAY_COUNT(weaknessMoves); i++)
    {
        flags = AI_TypeCalc(weaknessMoves[i], SPECIES_PSYDUCK, ABILITY_NONE);
        if (!(flags & MOVE_RESULT_SUPER_EFFECTIVE))
            Fail("SPEC001002 FAIL Psyduck defensive typing");
    }
}

static void CheckDarkBattleRules(void)
{
    u8 flags;
    s32 darkStab = TypeDamage(MOVE_BITE, SPECIES_RATTATA, SPECIES_CASTFORM, &flags);

    if (darkStab != 150)
        Fail("SPEC001002 FAIL Dark STAB");

    flags = AI_TypeCalc(MOVE_PSYCHIC, SPECIES_FEAROW, ABILITY_NONE);
    if (!(flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("SPEC001002 FAIL Fearow Dark Psychic immunity");

    flags = AI_TypeCalc(MOVE_THUNDERBOLT, SPECIES_FEAROW, ABILITY_NONE);
    if (!(flags & MOVE_RESULT_SUPER_EFFECTIVE))
        Fail("SPEC001002 FAIL Fearow Flying weakness");
}

void Spec001002TypeDark_RunQa(void)
{
    gBattleTypeFlags = BATTLE_TYPE_LINK;
    gBattlersCount = 2;

    CheckTypeFields();
    CheckPureFlyingBattleRules();
    CheckPsyduckFamilyBattleRules();
    CheckDarkBattleRules();

    QaLog("SPEC001002 QA PASS type fields STAB immunity weakness dark inheritance");
    for (;;);
}
