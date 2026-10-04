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
#include "constants/trade.h"
#include "constants/vars.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static const u8 sQaPlayerName[] = _("SAM");
static const u8 sMira[] = _("MIRA");

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

static void CheckMiraPartyMon(struct Pokemon *mon)
{
    u8 name[PLAYER_NAME_LENGTH + 1];
    GetMonData(mon, MON_DATA_OT_NAME, name);
    if (GetMonData(mon, MON_DATA_SPECIES, NULL) != SPECIES_TYROGUE
     || GetMonData(mon, MON_DATA_LEVEL, NULL) != 5
     || GetMonGender(mon) != MON_MALE
     || GetMonData(mon, MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
     || GetMonData(mon, MON_DATA_OT_ID, NULL) != OTID_GIFT_MIRA
     || StringCompare(name, sMira)
     || !IsTradedMon(mon))
        Fail("QUEST002 QA FAIL MIRA package");
}

static void GiveMiraTyrogue(void)
{
    gSpecialVar_0x8004 = SPECIES_TYROGUE;
    gSpecialVar_0x8005 = 5;
    gSpecialVar_0x8006 = SAM_PREOWNED_OT_MIRA;
    GiveSamPreOwnedMon();
}

static void CheckStoragePaths(void)
{
    struct BoxPokemon *boxed;
    u8 name[PLAYER_NAME_LENGTH + 1];
    u16 dex;

    ResetState();
    FillParty();
    VarSet(VAR_SQ_PALLET_STATE, 2);
    GiveMiraTyrogue();
    if (gSpecialVar_Result != MON_GIVEN_TO_PC)
        Fail("QUEST002 QA FAIL PC fallback");
    boxed = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    GetBoxMonData(boxed, MON_DATA_OT_NAME, name);
    if (GetBoxMonData(boxed, MON_DATA_SPECIES, NULL) != SPECIES_TYROGUE
     || GetBoxMonData(boxed, MON_DATA_OT_ID, NULL) != OTID_GIFT_MIRA
     || StringCompare(name, sMira)
     || VarGet(VAR_SQ_PALLET_STATE) != 2
     || FlagGet(FLAG_SQ_PALLET_COMPLETE))
        Fail("QUEST002 QA FAIL boxed/pending");

    ResetState();
    FillParty();
    FillStorage();
    VarSet(VAR_SQ_PALLET_STATE, 2);
    dex = SpeciesToNationalPokedexNum(SPECIES_TYROGUE);
    GiveMiraTyrogue();
    if (gSpecialVar_Result != MON_CANT_GIVE
     || VarGet(VAR_SQ_PALLET_STATE) != 2
     || FlagGet(FLAG_SQ_PALLET_COMPLETE)
     || GetSetPokedexFlag(dex, FLAG_GET_CAUGHT))
        Fail("QUEST002 QA FAIL full storage pending");
}

static void RunFresh(void)
{
    ResetState();
    FlagSet(FLAG_SYS_POKEDEX_GET);
    VarSet(VAR_SQ_PALLET_STATE, 2);
    GiveMiraTyrogue();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY || gPlayerPartyCount != 1)
        Fail("QUEST002 QA FAIL party delivery");
    CheckMiraPartyMon(&gPlayerParty[0]);

    CheckStoragePaths();

    ResetState();
    FlagSet(FLAG_SYS_POKEDEX_GET);
    VarSet(VAR_SQ_PALLET_STATE, 2);
    GiveMiraTyrogue();
    if (gSpecialVar_Result != MON_GIVEN_TO_PARTY)
        Fail("QUEST002 QA FAIL save delivery");
    VarSet(VAR_SQ_PALLET_STATE, 3);
    FlagSet(FLAG_SQ_PALLET_COMPLETE);
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("QUEST002 QA FAIL save");
    Log("QUEST002 QA PHASE1 PASS gift storage save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_SYS_POKEDEX_GET)
     || !FlagGet(FLAG_SQ_PALLET_COMPLETE)
     || VarGet(VAR_SQ_PALLET_STATE) != 3
     || gPlayerPartyCount != 1)
        Fail("QUEST002 QA FAIL reload state");
    CheckMiraPartyMon(&gPlayerParty[0]);
    Log("QUEST002 QA PASS reload completion");
    for (;;);
}

void Quest002Qa_RunRuntimeQa(void)
{
    u8 loadStatus;
    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
