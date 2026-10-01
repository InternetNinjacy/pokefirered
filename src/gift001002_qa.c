#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "save.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define GIFT_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define GIFT_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static const u8 sGiftQaPlayerName[] = _("SAM");
static const u8 sGiftQaOtName[] = _("FERN");

extern const u8 Gift001002Qa_EventScript_ClaimBulbasaur[];

static void GiftQaLog(const char *text)
{
    u32 i = 0;

    while (text[i] != '\0' && i < 255)
    {
        GIFT_QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    GIFT_QA_MGBA_DEBUG_STRING[i] = '\0';
    *GIFT_QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void GiftQaFail(const char *text)
{
    GiftQaLog(text);
    for (;;);
}

static void ResetGiftQaState(void)
{
    ClearSav2();
    ClearSav1();
    CpuFill16(0, &gPokemonStorage, sizeof(gPokemonStorage));
    gPokemonStoragePtr = &gPokemonStorage;
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;

    StringCopy(gSaveBlock2Ptr->playerName, sGiftQaPlayerName);
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;
}

static void FillParty(void)
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
        CreateMon(&gPlayerParty[i], SPECIES_RATTATA, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = PARTY_SIZE;
}

static void FillStorage(void)
{
    u8 box;
    u8 slot;

    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (slot = 0; slot < IN_BOX_COUNT; slot++)
            CreateBoxMon(GetBoxedMonPtr(box, slot), SPECIES_PIDGEY, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    }
}

static void CheckCoreDeliveryBehavior(void)
{
    u8 result;
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u32 otId;
    struct BoxPokemon *boxedMon;
    u16 nationalDexNum;

    result = ScriptGiveMon(SPECIES_BULBASAUR, 10, ITEM_MIRACLE_SEED, (u32)sGiftQaOtName, 52001, FEMALE);
    if (result != MON_GIVEN_TO_PARTY)
        GiftQaFail("GIFT QA FAIL preowned party delivery");

    otId = GetMonData(&gPlayerParty[0], MON_DATA_OT_ID, NULL);
    GetMonData(&gPlayerParty[0], MON_DATA_OT_NAME, otName);
    if (otId != 52001 || StringCompare(otName, sGiftQaOtName))
        GiftQaFail("GIFT QA FAIL authored OT not preserved");
    if (!IsTradedMon(&gPlayerParty[0]))
        GiftQaFail("GIFT QA FAIL preowned mon not outsider");

    {
        u16 evolvedSpecies = SPECIES_IVYSAUR;
        SetMonData(&gPlayerParty[0], MON_DATA_SPECIES, &evolvedSpecies);
    }
    if (!IsTradedMon(&gPlayerParty[0]))
        GiftQaFail("GIFT QA FAIL outsider state lost on evolution");

    ResetGiftQaState();
    result = ScriptGiveMon(SPECIES_PIKACHU, 10, ITEM_NONE, 0, 0, 0);
    if (result != MON_GIVEN_TO_PARTY || IsTradedMon(&gPlayerParty[0]))
        GiftQaFail("GIFT QA FAIL vanilla givemon ownership changed");

    ResetGiftQaState();
    FillParty();
    result = ScriptGiveMon(SPECIES_BULBASAUR, 10, ITEM_MIRACLE_SEED, (u32)sGiftQaOtName, 52001, FEMALE);
    if (result != MON_GIVEN_TO_PC)
        GiftQaFail("GIFT QA FAIL full-party PC delivery");
    boxedMon = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    otId = GetBoxMonData(boxedMon, MON_DATA_OT_ID, NULL);
    GetBoxMonData(boxedMon, MON_DATA_OT_NAME, otName);
    if (otId != 52001 || StringCompare(otName, sGiftQaOtName))
        GiftQaFail("GIFT QA FAIL boxed OT not preserved");

    ResetGiftQaState();
    FillParty();
    FillStorage();
    nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_BULBASAUR);
    if (GetSetPokedexFlag(nationalDexNum, FLAG_GET_CAUGHT))
        GiftQaFail("GIFT QA FAIL dex precondition");
    result = ScriptGiveMon(SPECIES_BULBASAUR, 10, ITEM_MIRACLE_SEED, (u32)sGiftQaOtName, 52001, FEMALE);
    if (result != MON_CANT_GIVE)
        GiftQaFail("GIFT QA FAIL full storage accepted reward");
    if (GetSetPokedexFlag(nationalDexNum, FLAG_GET_CAUGHT))
        GiftQaFail("GIFT QA FAIL failed reward set dex");
}

static void RunFresh(void)
{
    u8 otName[PLAYER_NAME_LENGTH + 1];

    ResetGiftQaState();
    CheckCoreDeliveryBehavior();

    ResetGiftQaState();
    FlagClear(FLAG_GOT_LAPRAS_FROM_SILPH);
    gSpecialVar_0x8000 = 0xFFFF;

    RunScriptImmediately(Gift001002Qa_EventScript_ClaimBulbasaur);

    if (gSpecialVar_0x8000 != 1)
        GiftQaFail("GIFT QA FAIL one-time script success path");
    if (!FlagGet(FLAG_GOT_LAPRAS_FROM_SILPH))
        GiftQaFail("GIFT QA FAIL one-time claim flag not set");
    if (gPlayerPartyCount != 1
     || GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_BULBASAUR)
        GiftQaFail("GIFT QA FAIL scripted reward delivery");

    GetMonData(&gPlayerParty[0], MON_DATA_OT_NAME, otName);
    if (GetMonData(&gPlayerParty[0], MON_DATA_OT_ID, NULL) != 52001
     || StringCompare(otName, sGiftQaOtName)
     || !IsTradedMon(&gPlayerParty[0]))
        GiftQaFail("GIFT QA FAIL scripted reward ownership");

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        GiftQaFail("GIFT QA FAIL save after scripted claim");

    GiftQaLog("GIFT QA PHASE1 PASS one-time script claimed and saved");
    for (;;);
}

static void RunReload(void)
{
    u8 beforeCount;
    u8 otName[PLAYER_NAME_LENGTH + 1];

    if (!FlagGet(FLAG_GOT_LAPRAS_FROM_SILPH))
        GiftQaFail("GIFT QA FAIL claim flag reload");
    if (gPlayerPartyCount != 1
     || GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_BULBASAUR)
        GiftQaFail("GIFT QA FAIL reward reload");

    GetMonData(&gPlayerParty[0], MON_DATA_OT_NAME, otName);
    if (GetMonData(&gPlayerParty[0], MON_DATA_OT_ID, NULL) != 52001
     || StringCompare(otName, sGiftQaOtName)
     || !IsTradedMon(&gPlayerParty[0]))
        GiftQaFail("GIFT QA FAIL ownership reload");

    beforeCount = gPlayerPartyCount;
    gSpecialVar_0x8000 = 0xFFFF;
    RunScriptImmediately(Gift001002Qa_EventScript_ClaimBulbasaur);

    if (gSpecialVar_0x8000 != 2)
        GiftQaFail("GIFT QA FAIL reclaim did not take claimed branch");
    if (gPlayerPartyCount != beforeCount)
        GiftQaFail("GIFT QA FAIL duplicate party reward");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_BULBASAUR)
        GiftQaFail("GIFT QA FAIL original reward changed");

    GiftQaLog("GIFT QA PASS core plus one-time script save reload reclaim blocked");
    for (;;);
}

void Gift001002_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
