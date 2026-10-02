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
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trade.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static const u8 sQaPlayerName[] = _("SAM");
static const u8 sOtFern[] = _("FERN");
static const u8 sOtAsher[] = _("ASHER");
static const u8 sOtMarina[] = _("MARINA");

extern const u8 GiftStarterFamilyQa_EventScript_ClaimFern[];

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
    CpuFill16(0, &gPokemonStorage, sizeof(gPokemonStorage));
    gPokemonStoragePtr = &gPokemonStorage;
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
    StringCopy(gSaveBlock2Ptr->playerName, sQaPlayerName);
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;
}

static void FillParty(void)
{
    u8 i;
    for (i = 0; i < PARTY_SIZE; i++)
        CreateMon(&gPlayerParty[i], SPECIES_RATTATA, 5, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = PARTY_SIZE;
}

static void FillStorage(void)
{
    u8 box, slot;
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
        for (slot = 0; slot < IN_BOX_COUNT; slot++)
            CreateBoxMon(GetBoxedMonPtr(box, slot), SPECIES_PIDGEY, 5, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static void CheckPackage(struct Pokemon *mon, u16 species, u8 level, u8 gender, u8 nature,
                         u16 item, u32 otId, const u8 *otName,
                         u16 move1, u16 move2, u16 move3, u16 move4)
{
    u8 actualOtName[PLAYER_NAME_LENGTH + 1];
    if (GetMonData(mon, MON_DATA_SPECIES, NULL) != species
     || GetMonData(mon, MON_DATA_LEVEL, NULL) != level
     || GetMonGender(mon) != gender
     || GetNature(mon) != nature
     || GetMonData(mon, MON_DATA_HELD_ITEM, NULL) != item
     || GetMonData(mon, MON_DATA_OT_ID, NULL) != otId)
        Fail("GIFT STARTER QA FAIL fixed package fields");

    GetMonData(mon, MON_DATA_OT_NAME, actualOtName);
    if (StringCompare(actualOtName, otName) || !IsTradedMon(mon))
        Fail("GIFT STARTER QA FAIL authored outsider ownership");

    if (GetMonData(mon, MON_DATA_MOVE1, NULL) != move1
     || GetMonData(mon, MON_DATA_MOVE2, NULL) != move2
     || GetMonData(mon, MON_DATA_MOVE3, NULL) != move3
     || GetMonData(mon, MON_DATA_MOVE4, NULL) != move4)
        Fail("GIFT STARTER QA FAIL exact moves");
}

static void GiveAndCheckAllThree(void)
{
    gSpecialVar_0x8004 = 0;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT STARTER QA FAIL Fern delivery");
    CheckPackage(&gPlayerParty[0], SPECIES_BULBASAUR, 10, MON_FEMALE, NATURE_CALM,
                 ITEM_MIRACLE_SEED, OTID_GIFT_FERN, sOtFern,
                 MOVE_TACKLE, MOVE_GROWL, MOVE_LEECH_SEED, MOVE_VINE_WHIP);

    gSpecialVar_0x8004 = 1;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT STARTER QA FAIL Asher delivery");
    CheckPackage(&gPlayerParty[1], SPECIES_CHARMANDER, 15, MON_MALE, NATURE_MODEST,
                 ITEM_CHARCOAL, OTID_GIFT_ASHER, sOtAsher,
                 MOVE_EMBER, MOVE_METAL_CLAW, MOVE_SMOKESCREEN, MOVE_DRAGON_RAGE);

    gSpecialVar_0x8004 = 2;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT STARTER QA FAIL Marina delivery");
    CheckPackage(&gPlayerParty[2], SPECIES_SQUIRTLE, 18, MON_FEMALE, NATURE_BOLD,
                 ITEM_MYSTIC_WATER, OTID_GIFT_MARINA, sOtMarina,
                 MOVE_WATER_GUN, MOVE_BITE, MOVE_WITHDRAW, MOVE_RAPID_SPIN);
}

static void CheckStoragePaths(void)
{
    struct BoxPokemon *boxed;
    u8 name[PLAYER_NAME_LENGTH + 1];
    u16 nationalDexNum;

    ResetState();
    FillParty();
    gSpecialVar_0x8004 = 2;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PC)
        Fail("GIFT STARTER QA FAIL PC fallback");
    boxed = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    if (GetBoxMonData(boxed, MON_DATA_SPECIES, NULL) != SPECIES_SQUIRTLE
     || GetBoxMonData(boxed, MON_DATA_OT_ID, NULL) != OTID_GIFT_MARINA)
        Fail("GIFT STARTER QA FAIL boxed package");
    GetBoxMonData(boxed, MON_DATA_OT_NAME, name);
    if (StringCompare(name, sOtMarina))
        Fail("GIFT STARTER QA FAIL boxed OT");

    ResetState();
    FillParty();
    FillStorage();
    nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_CHARMANDER);
    if (GetSetPokedexFlag(nationalDexNum, FLAG_GET_CAUGHT))
        Fail("GIFT STARTER QA FAIL dex precondition");
    gSpecialVar_0x8004 = 1;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_CANT_GIVE)
        Fail("GIFT STARTER QA FAIL full storage accepted");
    if (GetSetPokedexFlag(nationalDexNum, FLAG_GET_CAUGHT))
        Fail("GIFT STARTER QA FAIL failed delivery set dex");
}

static void RunFresh(void)
{
    ResetState();
    GiveAndCheckAllThree();
    CheckStoragePaths();

    ResetState();
    FlagClear(FLAG_GIFT_FERN_BULBASAUR_CLAIMED);
    gSpecialVar_0x8000 = 0xFFFF;
    RunScriptImmediately(GiftStarterFamilyQa_EventScript_ClaimFern);

    if (gSpecialVar_0x8000 != 1
     || !FlagGet(FLAG_GIFT_FERN_BULBASAUR_CLAIMED)
     || gPlayerPartyCount != 1)
        Fail("GIFT STARTER QA FAIL one-time claim script");
    CheckPackage(&gPlayerParty[0], SPECIES_BULBASAUR, 10, MON_FEMALE, NATURE_CALM,
                 ITEM_MIRACLE_SEED, OTID_GIFT_FERN, sOtFern,
                 MOVE_TACKLE, MOVE_GROWL, MOVE_LEECH_SEED, MOVE_VINE_WHIP);

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("GIFT STARTER QA FAIL save");

    Log("GIFT STARTER QA PHASE1 PASS exact packages delivery and save");
    for (;;);
}

static void RunReload(void)
{
    u8 beforeCount;

    if (!FlagGet(FLAG_GIFT_FERN_BULBASAUR_CLAIMED) || gPlayerPartyCount != 1)
        Fail("GIFT STARTER QA FAIL reload state");
    CheckPackage(&gPlayerParty[0], SPECIES_BULBASAUR, 10, MON_FEMALE, NATURE_CALM,
                 ITEM_MIRACLE_SEED, OTID_GIFT_FERN, sOtFern,
                 MOVE_TACKLE, MOVE_GROWL, MOVE_LEECH_SEED, MOVE_VINE_WHIP);

    beforeCount = gPlayerPartyCount;
    gSpecialVar_0x8000 = 0xFFFF;
    RunScriptImmediately(GiftStarterFamilyQa_EventScript_ClaimFern);
    if (gSpecialVar_0x8000 != 2 || gPlayerPartyCount != beforeCount)
        Fail("GIFT STARTER QA FAIL duplicate claim");

    Log("GIFT STARTER QA PASS save reload claim persistence");
    for (;;);
}

void GiftStarterFamilyQa_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
