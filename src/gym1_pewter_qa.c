#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "save.h"
#include "constants/flags.h"

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

static void RunFresh(void)
{
    ClearSav2();
    ClearSav1();

    if (FlagGet(FLAG_BADGE01_GET)
     || FlagGet(FLAG_SATOSHI_PEWTER_PRACTICE_WON)
     || FlagGet(FLAG_GYM1_TM55_RECEIVED))
        Fail("GYM1 QA FAIL dirty fresh flags");

    FlagSet(FLAG_SATOSHI_PEWTER_PRACTICE_WON);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_GYM1_TM55_RECEIVED);

    if (!FlagGet(FLAG_SATOSHI_PEWTER_PRACTICE_WON)
     || !FlagGet(FLAG_BADGE01_GET)
     || !FlagGet(FLAG_GYM1_TM55_RECEIVED))
        Fail("GYM1 QA FAIL set flags");

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("GYM1 QA FAIL save");

    Log("GYM1 QA PHASE1 PASS persistent state save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_SATOSHI_PEWTER_PRACTICE_WON)
     || !FlagGet(FLAG_BADGE01_GET)
     || !FlagGet(FLAG_GYM1_TM55_RECEIVED))
        Fail("GYM1 QA FAIL reload flags");

    Log("GYM1 QA PASS persistent state reload");
    for (;;);
}

void Gym1Qa_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
