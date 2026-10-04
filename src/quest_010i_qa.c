#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "constants/vars.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)
#define SQ_REWARD_PENDING     0x001F

void SamQuest010GiveMrMimeReward(void);

static const u8 sQaPlayerName[] = _("SAM");
static const u8 sCopycatName[] = _("COPYCAT");

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

static bool8 __attribute__((noinline)) QaIsTradedMon(struct Pokemon *mon)
{
    bool8 (*volatile func)(struct Pokemon *) = IsTradedMon;
    return func(mon);
}

static void ResetState(void)
{
    ClearSav2();
    ClearSav1();
    CpuFill16(0, &gPokemonStorage, sizeof(gPokemonStorage));
    gPokemonStoragePtr = &gPokemonStorage;
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
    StringCopy(gSaveBlock2Ptr->playerName, sQaPlayerName);
    gSaveBlock2Ptr->playerGender = MALE;
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;
}

static void FillParty(void)
{
    u8 i;
    for (i = 0; i < PARTY_SIZE; i++)
        CreateMon(&gPlayerParty[i], SPECIES_PIKACHU, 10, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = PARTY_SIZE;
}

static void FillStorage(void)
{
    u8 box, slot;
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
        for (slot = 0; slot < IN_BOX_COUNT; slot++)
            CreateBoxMon(GetBoxedMonPtr(box, slot), SPECIES_PIDGEY, 5, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static void CheckMrMimeMon(struct Pokemon *mon)
{
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    if (GetMonData(mon, MON_DATA_SPECIES, NULL) != SPECIES_MR_MIME
     || GetMonData(mon, MON_DATA_LEVEL, NULL) != 30
     || GetMonData(mon, MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
     || GetMonData(mon, MON_DATA_OT_ID, NULL) != OTID_GIFT_COPYCAT
     || !QaIsTradedMon(mon))
        Fail("QUEST010I QA FAIL Mr Mime package");
    GetMonData(mon, MON_DATA_OT_NAME, otName);
    if (StringCompare(otName, sCopycatName))
        Fail("QUEST010I QA FAIL Copycat OT");
    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    if (StringCompare(nickname, gSpeciesNames[SPECIES_MR_MIME]))
        Fail("QUEST010I QA FAIL nickname");
}

static void CheckPartyDelivery(void)
{
    ResetState();
    VarSet(VAR_SQ_SAFFRON_COUNT, SQ_REWARD_PENDING);
    SamQuest010GiveMrMimeReward();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY || gPlayerPartyCount != 1)
        Fail("QUEST010I QA FAIL party reward");
    CheckMrMimeMon(&gPlayerParty[0]);
}

static void CheckPcFallback(void)
{
    struct BoxPokemon *boxed;
    u8 otName[PLAYER_NAME_LENGTH + 1];

    ResetState();
    FillParty();
    VarSet(VAR_SQ_SAFFRON_COUNT, SQ_REWARD_PENDING);
    SamQuest010GiveMrMimeReward();
    if (gSpecialVar_Result != MON_GIVEN_TO_PC)
        Fail("QUEST010I QA FAIL PC fallback");
    boxed = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    if (GetBoxMonData(boxed, MON_DATA_SPECIES, NULL) != SPECIES_MR_MIME
     || GetBoxMonData(boxed, MON_DATA_LEVEL, NULL) != 30
     || GetBoxMonData(boxed, MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
     || GetBoxMonData(boxed, MON_DATA_OT_ID, NULL) != OTID_GIFT_COPYCAT)
        Fail("QUEST010I QA FAIL boxed package");
    GetBoxMonData(boxed, MON_DATA_OT_NAME, otName);
    if (StringCompare(otName, sCopycatName))
        Fail("QUEST010I QA FAIL boxed OT");
}

static void CheckFullStorageRetry(void)
{
    ResetState();
    FillParty();
    FillStorage();
    VarSet(VAR_SQ_SAFFRON_COUNT, SQ_REWARD_PENDING);
    SamQuest010GiveMrMimeReward();
    if (gSpecialVar_Result != MON_CANT_GIVE)
        Fail("QUEST010I QA FAIL full storage accepted");
    if (VarGet(VAR_SQ_SAFFRON_COUNT) != SQ_REWARD_PENDING || FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        Fail("QUEST010I QA FAIL pending mutated");

    CpuFill16(0, GetBoxedMonPtr(0, 0), sizeof(struct BoxPokemon));
    SamQuest010GiveMrMimeReward();
    if (gSpecialVar_Result != MON_GIVEN_TO_PC)
        Fail("QUEST010I QA FAIL retry delivery");
}

static void RunFresh(void)
{
    CheckPartyDelivery();
    CheckPcFallback();
    CheckFullStorageRetry();

    ResetState();
    VarSet(VAR_SQ_SAFFRON_COUNT, SQ_REWARD_PENDING);
    SamQuest010GiveMrMimeReward();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("QUEST010I QA FAIL final delivery");
    FlagSet(FLAG_SQ_SAFFRON_COMPLETE);
    CheckMrMimeMon(&gPlayerParty[0]);

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("QUEST010I QA FAIL save");
    Log("QUEST010I QA PHASE1 PASS reward delivery retry save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_SQ_SAFFRON_COMPLETE)
     || VarGet(VAR_SQ_SAFFRON_COUNT) != SQ_REWARD_PENDING
     || CalculatePlayerPartyCount() != 1)
        Fail("QUEST010I QA FAIL reload state");
    CheckMrMimeMon(&gPlayerParty[0]);
    Log("QUEST010I QA PASS completion persistence");
    for (;;);
}

void Quest010iQa_RunRuntimeQa(void)
{
    u8 loadStatus;
    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
