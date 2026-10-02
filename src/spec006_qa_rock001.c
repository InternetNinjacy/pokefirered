#include "global.h"
#include "battle.h"
#include "gba/isagbprint.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/moves.h"
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

static void ExpectPureRock(u16 species)
{
    if (gSpeciesInfo[species].types[0] != TYPE_ROCK
     || gSpeciesInfo[species].types[1] != TYPE_ROCK)
        Fail("ROCK001 FAIL pure Rock typing");
}

static void SetBattleMonTypes(u8 battler, u16 species)
{
    gBattleMons[battler].type1 = gSpeciesInfo[species].types[0];
    gBattleMons[battler].type2 = gSpeciesInfo[species].types[1];
    gBattleMons[battler].ability = ABILITY_NONE;
    gBattleMons[battler].status2 = 0;
}

static void CheckPlayerBattleTypeMath(void)
{
    u8 flags;

    SetBattleMonTypes(0, SPECIES_RHYDON);
    SetBattleMonTypes(1, SPECIES_RATTATA);

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_EARTHQUAKE, 0, 1);
    if (gBattleMoveDamage != 100 || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("ROCK001 FAIL Ground STAB removed");

    SetBattleMonTypes(0, SPECIES_RATTATA);
    SetBattleMonTypes(1, SPECIES_RHYDON);

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_THUNDERBOLT, 0, 1);
    if (gBattleMoveDamage != 100 || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("ROCK001 FAIL Electric immunity removed");

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_SURF, 0, 1);
    if (gBattleMoveDamage != 200
     || !(flags & MOVE_RESULT_SUPER_EFFECTIVE)
     || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("ROCK001 FAIL Water exactly 2x");

    gBattleMoveDamage = 100;
    flags = TypeCalc(MOVE_GIGA_DRAIN, 0, 1);
    if (gBattleMoveDamage != 200
     || !(flags & MOVE_RESULT_SUPER_EFFECTIVE)
     || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("ROCK001 FAIL Grass exactly 2x");
}

static void CheckAiTypeMath(void)
{
    u8 flags;

    flags = AI_TypeCalc(MOVE_THUNDERBOLT, SPECIES_RHYDON, ABILITY_NONE);
    if (flags & MOVE_RESULT_DOESNT_AFFECT_FOE)
        Fail("ROCK001 FAIL AI Electric immunity");

    flags = AI_TypeCalc(MOVE_SURF, SPECIES_RHYDON, ABILITY_NONE);
    if (!(flags & MOVE_RESULT_SUPER_EFFECTIVE)
     || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("ROCK001 FAIL AI Water");

    flags = AI_TypeCalc(MOVE_GIGA_DRAIN, SPECIES_RHYDON, ABILITY_NONE);
    if (!(flags & MOVE_RESULT_SUPER_EFFECTIVE)
     || (flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
        Fail("ROCK001 FAIL AI Grass");
}

static void CheckSpeciesData(void)
{
    static const u16 pureRockSpecies[] =
    {
        SPECIES_GEODUDE,
        SPECIES_GRAVELER,
        SPECIES_GOLEM,
        SPECIES_ONIX,
        SPECIES_RHYHORN,
        SPECIES_RHYDON,
    };
    u8 i;

    for (i = 0; i < ARRAY_COUNT(pureRockSpecies); i++)
        ExpectPureRock(pureRockSpecies[i]);

    if (gSpeciesInfo[SPECIES_STEELIX].types[0] != TYPE_STEEL
     || gSpeciesInfo[SPECIES_STEELIX].types[1] != TYPE_GROUND)
        Fail("ROCK001 FAIL Steelix control");

    if (gSpeciesInfo[SPECIES_NOSEPASS].baseHP != 30
     || gSpeciesInfo[SPECIES_NOSEPASS].baseAttack != 45
     || gSpeciesInfo[SPECIES_NOSEPASS].baseDefense != 135
     || gSpeciesInfo[SPECIES_NOSEPASS].baseSpAttack != 45
     || gSpeciesInfo[SPECIES_NOSEPASS].baseSpDefense != 90
     || gSpeciesInfo[SPECIES_NOSEPASS].baseSpeed != 30
     || gSpeciesInfo[SPECIES_NOSEPASS].types[0] != TYPE_ROCK
     || gSpeciesInfo[SPECIES_NOSEPASS].types[1] != TYPE_ROCK
     || gSpeciesInfo[SPECIES_NOSEPASS].abilities[0] != ABILITY_STURDY
     || gSpeciesInfo[SPECIES_NOSEPASS].abilities[1] != ABILITY_MAGNET_PULL)
        Fail("ROCK001 FAIL Nosepass package");
}

void Spec006QaRock_RunRuntimeQa(void)
{
    MgbaOpen();
    CheckSpeciesData();
    CheckPlayerBattleTypeMath();
    CheckAiTypeMath();
    Log("ROCK001 QA PASS pure Rock runtime type math and AI");
    for (;;);
}
