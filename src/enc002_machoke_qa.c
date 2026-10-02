#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "save.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern void SetEnemyEventMonMoveSlot(void);

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

static void CheckMachokePackage(void)
{
    CreateScriptedWildMon(SPECIES_MACHOKE, 29, ITEM_BLACK_BELT);

    gSpecialVar_0x8004 = MOVE_KARATE_CHOP;
    gSpecialVar_0x8005 = 0;
    SetEnemyEventMonMoveSlot();
    gSpecialVar_0x8004 = MOVE_SEISMIC_TOSS;
    gSpecialVar_0x8005 = 1;
    SetEnemyEventMonMoveSlot();
    gSpecialVar_0x8004 = MOVE_FORESIGHT;
    gSpecialVar_0x8005 = 2;
    SetEnemyEventMonMoveSlot();
    gSpecialVar_0x8004 = MOVE_REVENGE;
    gSpecialVar_0x8005 = 3;
    SetEnemyEventMonMoveSlot();

    if (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL) != SPECIES_MACHOKE
     || GetMonData(&gEnemyParty[0], MON_DATA_LEVEL, NULL) != 29
     || GetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, NULL) != ITEM_BLACK_BELT
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE1, NULL) != MOVE_KARATE_CHOP
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE2, NULL) != MOVE_SEISMIC_TOSS
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE3, NULL) != MOVE_FORESIGHT
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE4, NULL) != MOVE_REVENGE)
        Fail("ENC002 MACHOKE QA FAIL package");
}

static void RunFresh(void)
{
    ClearSav2();
    ClearSav1();
    CheckMachokePackage();

    if (FlagGet(FLAG_STATIC_ROCK_TUNNEL_MACHOKE_COMPLETE))
        Fail("ENC002 MACHOKE QA FAIL dirty flag");

    FlagSet(FLAG_STATIC_ROCK_TUNNEL_MACHOKE_COMPLETE);
    if (!FlagGet(FLAG_STATIC_ROCK_TUNNEL_MACHOKE_COMPLETE))
        Fail("ENC002 MACHOKE QA FAIL set flag");

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("ENC002 MACHOKE QA FAIL save");

    Log("ENC002 MACHOKE QA PHASE1 PASS package flag save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_STATIC_ROCK_TUNNEL_MACHOKE_COMPLETE))
        Fail("ENC002 MACHOKE QA FAIL reload flag");

    CheckMachokePackage();
    Log("ENC002 MACHOKE QA PASS save reload package");
    for (;;);
}

void Enc002MachokeQa_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
