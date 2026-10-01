#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define GIFT_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define GIFT_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static const u8 sGiftQaPlayerName[] = _("SAM");
static const u8 sGiftQaOtName[] = _("FERN");

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

void Gift001002_RunRuntimeQa(void)
{
    u8 result;
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u32 otId;
    struct BoxPokemon *boxedMon;
    u16 nationalDexNum;

    MgbaOpen();
    ResetGiftQaState();

    result = ScriptGiveMon(SPECIES_BULBASAUR, 10, ITEM_MIRACLE_SEED, (u32)sGiftQaOtName, 52001, MON_FEMALE);
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
    result = ScriptGiveMon(SPECIES_BULBASAUR, 10, ITEM_MIRACLE_SEED, (u32)sGiftQaOtName, 52001, MON_FEMALE);
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
    result = ScriptGiveMon(SPECIES_BULBASAUR, 10, ITEM_MIRACLE_SEED, (u32)sGiftQaOtName, 52001, MON_FEMALE);
    if (result != MON_CANT_GIVE)
        GiftQaFail("GIFT QA FAIL full storage accepted reward");
    if (GetSetPokedexFlag(nationalDexNum, FLAG_GET_CAUGHT))
        GiftQaFail("GIFT QA FAIL failed reward set dex");

    GiftQaLog("GIFT QA PASS outsider evolution party pc full-storage");
    for (;;);
}
