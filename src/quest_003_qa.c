#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "item.h"
#include "load_save.h"
#include "pokemon.h"
#include "save.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/vars.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static const u8 sQaPlayerName[] = _("SAM");

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

static void ResetState(void)
{
    ClearSav2();
    ClearSav1();
    SetBagPocketsPointers();
    ClearBag();
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
    StringCopy(gSaveBlock2Ptr->playerName, sQaPlayerName);
    gSaveBlock2Ptr->playerGender = MALE;
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;
}

static void CheckSpearowPackage(void)
{
    struct Pokemon mon;
    u16 move;

    CreateMon(&mon, SPECIES_SPEAROW, 6, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    if (GetMonData(&mon, MON_DATA_SPECIES, NULL) != SPECIES_SPEAROW
     || GetMonData(&mon, MON_DATA_LEVEL, NULL) != 6)
        Fail("QUEST003 QA FAIL Spearow identity");

    move = GetMonData(&mon, MON_DATA_MOVE1, NULL);
    if (move != MOVE_PECK)
        Fail("QUEST003 QA FAIL Spearow move1");
    move = GetMonData(&mon, MON_DATA_MOVE2, NULL);
    if (move != MOVE_GROWL)
        Fail("QUEST003 QA FAIL Spearow move2");
}

static void CheckRewardPending(void)
{
    ResetState();
    FlagSet(FLAG_SYS_POKEDEX_GET);
    VarSet(VAR_SQ_VIRIDIAN_STATE, 3);

    if (!AddBagItem(ITEM_POKE_BALL, 997))
        Fail("QUEST003 QA FAIL bag setup");
    if (CheckBagHasSpace(ITEM_POKE_BALL, 5))
        Fail("QUEST003 QA FAIL full bag accepted");
    if (BagGetQuantityByItemId(ITEM_POKE_BALL) != 997
     || VarGet(VAR_SQ_VIRIDIAN_STATE) != 3
     || FlagGet(FLAG_SQ_VIRIDIAN_COMPLETE))
        Fail("QUEST003 QA FAIL pending reward state");
}

static void RunFresh(void)
{
    CheckSpearowPackage();
    CheckRewardPending();

    ResetState();
    FlagSet(FLAG_SYS_POKEDEX_GET);
    VarSet(VAR_SQ_VIRIDIAN_STATE, 1);
    if (VarGet(VAR_SQ_VIRIDIAN_STATE) != 1)
        Fail("QUEST003 QA FAIL active state");

    VarSet(VAR_SQ_VIRIDIAN_STATE, 2);
    if (VarGet(VAR_SQ_VIRIDIAN_STATE) != 2)
        Fail("QUEST003 QA FAIL resolved state");

    VarSet(VAR_SQ_VIRIDIAN_STATE, 3);
    if (!CheckBagHasSpace(ITEM_POKE_BALL, 5) || !AddBagItem(ITEM_POKE_BALL, 5))
        Fail("QUEST003 QA FAIL reward delivery");
    VarSet(VAR_SQ_VIRIDIAN_STATE, 4);
    FlagSet(FLAG_SQ_VIRIDIAN_COMPLETE);

    if (BagGetQuantityByItemId(ITEM_POKE_BALL) != 5)
        Fail("QUEST003 QA FAIL reward quantity");
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("QUEST003 QA FAIL save");

    Log("QUEST003 QA PHASE1 PASS state reward save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_SYS_POKEDEX_GET)
     || !FlagGet(FLAG_SQ_VIRIDIAN_COMPLETE)
     || VarGet(VAR_SQ_VIRIDIAN_STATE) != 4
     || BagGetQuantityByItemId(ITEM_POKE_BALL) != 5)
        Fail("QUEST003 QA FAIL reload state");

    Log("QUEST003 QA PASS reload completion");
    for (;;);
}

void Quest003Qa_RunRuntimeQa(void)
{
    u8 loadStatus;
    MgbaOpen();
    SetSaveBlocksPointers();
    SetBagPocketsPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    SetBagPocketsPointers();
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
