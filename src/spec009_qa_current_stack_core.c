#include "global.h"
#include "gba/isagbprint.h"
#include "battle.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

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

static void InitBattleMon(struct BattlePokemon *mon)
{
    u8 i;
    CpuFill16(0, mon, sizeof(*mon));
    mon->species = SPECIES_ECTOCEON;
    mon->attack = 100;
    mon->defense = 100;
    mon->speed = 100;
    mon->spAttack = 100;
    mon->spDefense = 100;
    mon->hp = 100;
    mon->maxHP = 100;
    mon->level = 50;
    mon->item = ITEM_NONE;
    for (i = 0; i < NUM_BATTLE_STATS; i++)
        mon->statStages[i] = DEFAULT_STAT_STAGE;
}

static void CheckSoulRot(void)
{
    struct BattlePokemon attacker;
    struct BattlePokemon defender;
    s32 neutral;
    s32 unpoisoned;
    s32 poisoned;

    InitBattleMon(&attacker);
    InitBattleMon(&defender);
    defender.species = SPECIES_DITTO;

    gBattleTypeFlags = 0;
    gBattleWeather = 0;
    gCritMultiplier = 1;
    gCurrentMove = MOVE_SHADOW_BALL;

    attacker.ability = ABILITY_NONE;
    defender.status1 = 0;
    neutral = CalculateBaseDamage(&attacker, &defender, MOVE_SHADOW_BALL, 0, 80, TYPE_GHOST, 0, 1);

    attacker.ability = ABILITY_SOUL_ROT;
    unpoisoned = CalculateBaseDamage(&attacker, &defender, MOVE_SHADOW_BALL, 0, 80, TYPE_GHOST, 0, 1);
    if (unpoisoned != neutral)
        Fail("SPEC009 FAIL Soul Rot unpoisoned");

    defender.status1 = STATUS1_POISON;
    poisoned = CalculateBaseDamage(&attacker, &defender, MOVE_SHADOW_BALL, 0, 80, TYPE_GHOST, 0, 1);
    if (poisoned != (130 * neutral) / 100)
        Fail("SPEC009 FAIL Soul Rot poisoned");

    gCurrentMove = MOVE_BODY_SLAM;
    attacker.ability = ABILITY_NONE;
    neutral = CalculateBaseDamage(&attacker, &defender, MOVE_BODY_SLAM, 0, 80, TYPE_NORMAL, 0, 1);
    attacker.ability = ABILITY_SOUL_ROT;
    if (CalculateBaseDamage(&attacker, &defender, MOVE_BODY_SLAM, 0, 80, TYPE_NORMAL, 0, 1) != neutral)
        Fail("SPEC009 FAIL Soul Rot non-Ghost");
}

static void CheckSpeciesAndCries(void)
{
    struct Pokemon mon;

    if (gSpeciesInfo[SPECIES_ECTOCEON].abilities[0] != ABILITY_SOUL_ROT)
        Fail("SPEC009 FAIL Ectoceon ability data");

    CreateMon(&mon, SPECIES_ECTOCEON, 20, 20, TRUE, 0x12345678, OT_ID_PLAYER_ID, 0);
    if (GetMonAbility(&mon) != ABILITY_SOUL_ROT)
        Fail("SPEC009 FAIL Ectoceon runtime ability");

    if (SpeciesToCryId(SPECIES_LEAFEON - 1) != SpeciesToCryId(SPECIES_EEVEE - 1))
        Fail("SPEC009 FAIL Leafeon cry");
    if (SpeciesToCryId(SPECIES_ECTOCEON - 1) != SpeciesToCryId(SPECIES_VAPOREON - 1))
        Fail("SPEC009 FAIL Ectoceon cry");
    if (SpeciesToCryId(SPECIES_RHYPERIOR - 1) != SpeciesToCryId(SPECIES_RHYDON - 1))
        Fail("SPEC009 FAIL Rhyperior cry");
}

void Spec009QaCurrentStackCore_RunRuntimeQa(void)
{
    MgbaOpen();
    CheckSpeciesAndCries();
    CheckSoulRot();
    Log("SPEC009 CORE QA PASS Soul Rot assignment effect and fixed cries");
    for (;;);
}
