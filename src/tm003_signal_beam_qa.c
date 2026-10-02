#include "global.h"
#include "battle.h"
#include "gba/isagbprint.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static struct BattleResources sQaBattleResources;
static struct ResourceFlags sQaResourceFlags;
static struct BattleStruct sQaBattleStruct;

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

static void InitBattleMon(struct BattlePokemon *mon, u16 attack, u16 defense, u16 spAttack, u16 spDefense)
{
    u8 i;

    CpuFill16(0, mon, sizeof(*mon));
    mon->species = SPECIES_BUTTERFREE;
    mon->attack = attack;
    mon->defense = defense;
    mon->spAttack = spAttack;
    mon->spDefense = spDefense;
    mon->speed = 100;
    mon->level = 50;
    mon->hp = 200;
    mon->maxHP = 200;
    mon->item = ITEM_NONE;
    mon->ability = ABILITY_NONE;
    mon->type1 = TYPE_BUG;
    mon->type2 = TYPE_FLYING;
    for (i = 0; i < NUM_BATTLE_STATS; i++)
        mon->statStages[i] = DEFAULT_STAT_STAGE;
}

static s32 Damage(u16 move, u16 sideStatus)
{
    gCurrentMove = move;
    gCritMultiplier = 1;
    gBattleWeather = 0;
    gBattleMovePower = 0;
    return CalculateBaseDamage(&gBattleMons[0], &gBattleMons[1], move, sideStatus, 75, 0, 0, 1);
}

static void CheckMoveData(void)
{
    if (gBattleMoves[MOVE_SIGNAL_BEAM].type != TYPE_BUG
     || gBattleMoves[MOVE_SIGNAL_BEAM].power != 75
     || gBattleMoves[MOVE_SIGNAL_BEAM].accuracy != 100)
        Fail("TM003 FAIL Signal Beam move data changed");
}

static void CheckAttackingStatSelection(void)
{
    s32 signalHighAtk;
    s32 signalHighSpAtk;
    s32 furyHighAtk;
    s32 furyHighSpAtk;
    s32 wailHighAtk;
    s32 wailHighSpAtk;

    InitBattleMon(&gBattleMons[1], 100, 100, 100, 100);

    InitBattleMon(&gBattleMons[0], 220, 100, 60, 100);
    signalHighAtk = Damage(MOVE_SIGNAL_BEAM, 0);
    furyHighAtk = Damage(MOVE_FURY_CUTTER, 0);
    wailHighAtk = Damage(MOVE_GHOSTLY_WAIL, 0);

    InitBattleMon(&gBattleMons[0], 60, 100, 220, 100);
    signalHighSpAtk = Damage(MOVE_SIGNAL_BEAM, 0);
    furyHighSpAtk = Damage(MOVE_FURY_CUTTER, 0);
    wailHighSpAtk = Damage(MOVE_GHOSTLY_WAIL, 0);

    if (signalHighSpAtk <= signalHighAtk * 2)
        Fail("TM003 FAIL Signal Beam not using SpAtk");
    if (furyHighAtk <= furyHighSpAtk * 2)
        Fail("TM003 FAIL physical Bug control changed");
    if (wailHighSpAtk <= wailHighAtk * 2)
        Fail("TM003 FAIL Ghostly Wail regression");
}

static void CheckDefendingStatSelection(void)
{
    s32 signalLowDef;
    s32 signalLowSpDef;
    s32 furyLowDef;
    s32 furyLowSpDef;

    InitBattleMon(&gBattleMons[0], 150, 100, 150, 100);

    InitBattleMon(&gBattleMons[1], 100, 50, 100, 200);
    signalLowDef = Damage(MOVE_SIGNAL_BEAM, 0);
    furyLowDef = Damage(MOVE_FURY_CUTTER, 0);

    InitBattleMon(&gBattleMons[1], 100, 200, 100, 50);
    signalLowSpDef = Damage(MOVE_SIGNAL_BEAM, 0);
    furyLowSpDef = Damage(MOVE_FURY_CUTTER, 0);

    if (signalLowSpDef <= signalLowDef * 2)
        Fail("TM003 FAIL Signal Beam not using SpDef");
    if (furyLowDef <= furyLowSpDef * 2)
        Fail("TM003 FAIL physical defense control changed");
}

static void CheckScreensAndBurn(void)
{
    s32 signalBase;
    s32 signalReflect;
    s32 signalLightScreen;
    s32 signalBurn;
    s32 furyBase;
    s32 furyReflect;
    s32 furyLightScreen;
    s32 furyBurn;

    InitBattleMon(&gBattleMons[0], 150, 100, 150, 100);
    InitBattleMon(&gBattleMons[1], 100, 100, 100, 100);

    signalBase = Damage(MOVE_SIGNAL_BEAM, 0);
    signalReflect = Damage(MOVE_SIGNAL_BEAM, SIDE_STATUS_REFLECT);
    signalLightScreen = Damage(MOVE_SIGNAL_BEAM, SIDE_STATUS_LIGHTSCREEN);

    furyBase = Damage(MOVE_FURY_CUTTER, 0);
    furyReflect = Damage(MOVE_FURY_CUTTER, SIDE_STATUS_REFLECT);
    furyLightScreen = Damage(MOVE_FURY_CUTTER, SIDE_STATUS_LIGHTSCREEN);

    if (signalReflect != signalBase)
        Fail("TM003 FAIL Reflect affected Signal Beam");
    if (signalLightScreen >= signalBase)
        Fail("TM003 FAIL Light Screen ignored Signal Beam");
    if (furyReflect >= furyBase)
        Fail("TM003 FAIL Reflect ignored physical Bug");
    if (furyLightScreen != furyBase)
        Fail("TM003 FAIL Light Screen affected physical Bug");

    gBattleMons[0].status1 = STATUS1_BURN;
    signalBurn = Damage(MOVE_SIGNAL_BEAM, 0);
    furyBurn = Damage(MOVE_FURY_CUTTER, 0);

    if (signalBurn != signalBase)
        Fail("TM003 FAIL burn reduced Signal Beam");
    if (furyBurn >= furyBase)
        Fail("TM003 FAIL burn did not reduce physical Bug");
}

void Tm003SignalBeam_RunRuntimeQa(void)
{
    gBattleResources = &sQaBattleResources;
    sQaBattleResources.flags = &sQaResourceFlags;
    gBattleStruct = &sQaBattleStruct;
    gBattleTypeFlags = BATTLE_TYPE_LINK;
    gBattlersCount = 2;
    gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
    gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

    CheckMoveData();
    CheckAttackingStatSelection();
    CheckDefendingStatSelection();
    CheckScreensAndBurn();

    QaLog("TM003 SIGNAL BEAM QA PASS special stats defenses screens burn ghostly");
    for (;;);
}
