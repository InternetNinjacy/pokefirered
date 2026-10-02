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
static const u8 sOtLuna[] = _("LUNA");
static const u8 sOtMelody[] = _("MELODY");
static const u8 sOtVendor[] = _("VENDOR");
static const u8 sOtCeladon[] = _("CELADON");
static const u8 sOtLab[] = _("LAB");
static const u8 sOtSilph[] = _("SILPH");

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

static void CheckOt(struct Pokemon *mon, u16 species, u8 level, u32 otId, const u8 *otName)
{
    u8 actualOtName[PLAYER_NAME_LENGTH + 1];
    if (GetMonData(mon, MON_DATA_SPECIES, NULL) != species
     || GetMonData(mon, MON_DATA_LEVEL, NULL) != level
     || GetMonData(mon, MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
     || GetMonData(mon, MON_DATA_OT_ID, NULL) != otId)
        Fail("GIFT REMAIN QA FAIL authored package");
    GetMonData(mon, MON_DATA_OT_NAME, actualOtName);
    if (StringCompare(actualOtName, otName) || !IsTradedMon(mon))
        Fail("GIFT REMAIN QA FAIL outsider OT");
}

static void CheckCleffa(struct Pokemon *mon)
{
    u8 name[PLAYER_NAME_LENGTH + 1];
    GetMonData(mon, MON_DATA_OT_NAME, name);
    if (GetMonData(mon, MON_DATA_SPECIES, NULL) != SPECIES_CLEFFA
     || GetMonData(mon, MON_DATA_LEVEL, NULL) != 8
     || GetMonGender(mon) != MON_FEMALE
     || GetNature(mon) != NATURE_CALM
     || GetMonData(mon, MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
     || GetMonData(mon, MON_DATA_OT_ID, NULL) != OTID_GIFT_LUNA
     || StringCompare(name, sOtLuna)
     || !IsTradedMon(mon)
     || GetMonData(mon, MON_DATA_MOVE1, NULL) != MOVE_POUND
     || GetMonData(mon, MON_DATA_MOVE2, NULL) != MOVE_CHARM
     || GetMonData(mon, MON_DATA_MOVE3, NULL) != MOVE_ENCORE
     || GetMonData(mon, MON_DATA_MOVE4, NULL) != MOVE_SWEET_KISS)
        Fail("GIFT REMAIN QA FAIL Cleffa");
}

static void CheckIgglybuff(struct Pokemon *mon)
{
    u8 name[PLAYER_NAME_LENGTH + 1];
    GetMonData(mon, MON_DATA_OT_NAME, name);
    if (GetMonData(mon, MON_DATA_SPECIES, NULL) != SPECIES_IGGLYBUFF
     || GetMonData(mon, MON_DATA_LEVEL, NULL) != 18
     || GetMonGender(mon) != MON_FEMALE
     || GetNature(mon) != NATURE_BOLD
     || GetMonData(mon, MON_DATA_HELD_ITEM, NULL) != ITEM_SOOTHE_BELL
     || GetMonData(mon, MON_DATA_OT_ID, NULL) != OTID_GIFT_MELODY
     || StringCompare(name, sOtMelody)
     || !IsTradedMon(mon)
     || GetMonData(mon, MON_DATA_MOVE1, NULL) != MOVE_SING
     || GetMonData(mon, MON_DATA_MOVE2, NULL) != MOVE_DEFENSE_CURL
     || GetMonData(mon, MON_DATA_MOVE3, NULL) != MOVE_POUND
     || GetMonData(mon, MON_DATA_MOVE4, NULL) != MOVE_SWEET_KISS)
        Fail("GIFT REMAIN QA FAIL Igglybuff");
}

static void GiveStock(u16 species, u8 level, u16 profile, u32 otId, const u8 *otName)
{
    ResetState();
    gSpecialVar_0x8004 = species;
    gSpecialVar_0x8005 = level;
    gSpecialVar_0x8006 = profile;
    GiveSamPreOwnedMon();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY || gPlayerPartyCount != 1)
        Fail("GIFT REMAIN QA FAIL stock delivery");
    CheckOt(&gPlayerParty[0], species, level, otId, otName);
}

static void CheckStoragePaths(void)
{
    struct BoxPokemon *boxed;
    u8 name[PLAYER_NAME_LENGTH + 1];
    u16 dex;

    ResetState();
    FillParty();
    gSpecialVar_0x8004 = SPECIES_LAPRAS;
    gSpecialVar_0x8005 = 25;
    gSpecialVar_0x8006 = SAM_PREOWNED_OT_SILPH;
    GiveSamPreOwnedMon();
    if (gSpecialVar_Result != MON_GIVEN_TO_PC)
        Fail("GIFT REMAIN QA FAIL PC fallback");
    boxed = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    if (GetBoxMonData(boxed, MON_DATA_SPECIES, NULL) != SPECIES_LAPRAS
     || GetBoxMonData(boxed, MON_DATA_OT_ID, NULL) != OTID_SILPH)
        Fail("GIFT REMAIN QA FAIL boxed SILPH");
    GetBoxMonData(boxed, MON_DATA_OT_NAME, name);
    if (StringCompare(name, sOtSilph))
        Fail("GIFT REMAIN QA FAIL boxed SILPH name");

    ResetState();
    FillParty();
    FillStorage();
    dex = SpeciesToNationalPokedexNum(SPECIES_PORYGON);
    gSpecialVar_0x8004 = SPECIES_PORYGON;
    gSpecialVar_0x8005 = 26;
    gSpecialVar_0x8006 = SAM_PREOWNED_OT_GAME_CORNER;
    GiveSamPreOwnedMon();
    if (gSpecialVar_Result != MON_CANT_GIVE)
        Fail("GIFT REMAIN QA FAIL full storage accepted");
    if (GetSetPokedexFlag(dex, FLAG_GET_CAUGHT))
        Fail("GIFT REMAIN QA FAIL failed delivery set dex");
}

static void RunFresh(void)
{
    ResetState();

    gSpecialVar_0x8004 = 3;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT REMAIN QA FAIL Cleffa delivery");
    CheckCleffa(&gPlayerParty[0]);

    gSpecialVar_0x8004 = 4;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT REMAIN QA FAIL Igglybuff delivery");
    CheckIgglybuff(&gPlayerParty[1]);

    GiveStock(SPECIES_MAGIKARP, 5, SAM_PREOWNED_OT_VENDOR, OTID_PURCHASE_MAGIKARP_VENDOR, sOtVendor);
    GiveStock(SPECIES_ABRA, 9, SAM_PREOWNED_OT_GAME_CORNER, OTID_GAME_CORNER_CELADON, sOtCeladon);
    GiveStock(SPECIES_OMANYTE, 5, SAM_PREOWNED_OT_FOSSIL_LAB, OTID_FOSSIL_CINNABAR_LAB, sOtLab);
    GiveStock(SPECIES_LAPRAS, 25, SAM_PREOWNED_OT_SILPH, OTID_SILPH, sOtSilph);
    CheckStoragePaths();

    ResetState();
    gSpecialVar_0x8004 = 3;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT REMAIN QA FAIL Cleffa save delivery");
    gSpecialVar_0x8004 = 4;
    GiveSamStarterFamilyGift();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("GIFT REMAIN QA FAIL Iggly save delivery");
    FlagSet(FLAG_GIFT_LUNA_CLEFFA_CLAIMED);
    FlagSet(FLAG_GIFT_MELODY_IGGLYBUFF_CLAIMED);

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("GIFT REMAIN QA FAIL save");

    Log("GIFT REMAIN QA PHASE1 PASS packages storage and save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_GIFT_LUNA_CLEFFA_CLAIMED)
     || !FlagGet(FLAG_GIFT_MELODY_IGGLYBUFF_CLAIMED)
     || gPlayerPartyCount != 2)
        Fail("GIFT REMAIN QA FAIL reload state");

    CheckCleffa(&gPlayerParty[0]);
    CheckIgglybuff(&gPlayerParty[1]);
    Log("GIFT REMAIN QA PASS save reload persistence");
    for (;;);
}

void GiftRemainingQa_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
