#include "global.h"
#include "battle.h"
#include "gba/isagbprint.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

#define QA_FLAGS  ((vu16 *)0x4FFF700)
#define QA_TEXT   ((volatile char *)0x4FFF600)

static struct BattleResources sRes;
static struct ResourceFlags sFlags;
static struct BattleStruct sStruct;

static void Log(const char *s)
{
    u32 i = 0;
    while (s[i] && i < 255)
    {
        QA_TEXT[i] = s[i];
        i++;
    }
    QA_TEXT[i] = 0;
    *QA_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *s)
{
    Log(s);
    for (;;);
}

static void InitMon(struct BattlePokemon *m, u16 atk, u16 def, u16 spa, u16 spd)
{
    u8 i;
    CpuFill16(0, m, sizeof(*m));
    m->species = SPECIES_GENGAR;
    m->attack = atk;
    m->defense = def;
    m->spAttack = spa;
    m->spDefense = spd;
    m->speed = 100;
    m->level = 50;
    m->hp = 200;
    m->maxHP = 200;
    m->ability = ABILITY_NONE;
    m->type1 = TYPE_GHOST;
    m->type2 = TYPE_POISON;
    for (i = 0; i < NUM_BATTLE_STATS; i++)
        m->statStages[i] = DEFAULT_STAT_STAGE;
}

static s32 Calc(u16 move)
{
    gCurrentMove = move;
    gCritMultiplier = 1;
    gBattleWeather = 0;
    gBattleMovePower = 0;
    return CalculateBaseDamage(&gBattleMons[0], &gBattleMons[1], move, 0, gBattleMoves[move].power, 0, 0, 1);
}

static void CheckData(void)
{
    const struct BattleMove *m;

    m = &gBattleMoves[MOVE_BOULDER_BASH];
    if (m->effect != EFFECT_DEFENSE_DOWN_HIT || m->power != 95 || m->type != TYPE_ROCK || m->accuracy != 90 || m->pp != 10 || m->secondaryEffectChance != 20)
        Fail("TM002 FAIL boulder");

    m = &gBattleMoves[MOVE_SHADOW_PUNCH];
    if (m->effect != EFFECT_SHADOW_PUNCH_SAM || m->power != 70 || m->type != TYPE_GHOST || m->accuracy != 0 || m->pp != 15)
        Fail("TM002 FAIL shadow");

    m = &gBattleMoves[MOVE_GHOSTLY_WAIL];
    if (m->effect != EFFECT_TRI_ATTACK || m->power != 100 || m->type != TYPE_GHOST || m->accuracy != 90 || m->pp != 5 || m->secondaryEffectChance != 20)
        Fail("TM002 FAIL wail");

    m = &gBattleMoves[MOVE_SEED_STRIKE];
    if (m->effect != EFFECT_SEED_STRIKE || m->power != 70 || m->type != TYPE_GRASS || m->accuracy != 95 || m->pp != 10)
        Fail("TM002 FAIL seed");

    m = &gBattleMoves[MOVE_NIGHT_TERROR];
    if (m->effect != EFFECT_FLINCH_HIT || m->power != 100 || m->type != TYPE_DARK || m->accuracy != 90 || m->pp != 10 || m->secondaryEffectChance != 20)
        Fail("TM002 FAIL night");
}

static void CheckDamage(void)
{
    const u16 moves[] = {MOVE_BOULDER_BASH, MOVE_SHADOW_PUNCH, MOVE_GHOSTLY_WAIL, MOVE_SEED_STRIKE, MOVE_NIGHT_TERROR};
    u8 i;
    InitMon(&gBattleMons[0], 150, 100, 150, 100);
    InitMon(&gBattleMons[1], 100, 100, 100, 100);
    for (i = 0; i < ARRAY_COUNT(moves); i++)
        if (Calc(moves[i]) <= 0)
            Fail("TM002 FAIL damage");
}

static void CheckWailClass(void)
{
    s32 atkBias;
    s32 spaBias;
    InitMon(&gBattleMons[1], 100, 100, 100, 100);
    InitMon(&gBattleMons[0], 220, 100, 60, 100);
    atkBias = Calc(MOVE_GHOSTLY_WAIL);
    InitMon(&gBattleMons[0], 60, 100, 220, 100);
    spaBias = Calc(MOVE_GHOSTLY_WAIL);
    if (spaBias <= atkBias * 2)
        Fail("TM002 FAIL wail class");
}

void Tm002CustomMoves_RunRuntimeQa(void)
{
    gBattleResources = &sRes;
    sRes.flags = &sFlags;
    gBattleStruct = &sStruct;
    gBattleTypeFlags = BATTLE_TYPE_LINK;
    gBattlersCount = 2;
    gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
    gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

    CheckData();
    CheckDamage();
    CheckWailClass();

    Log("TM002 QA PASS data damage wail scripts source");
    for (;;);
}
