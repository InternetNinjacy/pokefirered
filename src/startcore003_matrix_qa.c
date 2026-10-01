#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/vars.h"

#define MATRIX_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define MATRIX_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern void MarkSamOriginalStarter(void);

static void Log(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        MATRIX_QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    MATRIX_QA_MGBA_DEBUG_STRING[i] = '\0';
    *MATRIX_QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    Log(text);
    for (;;);
}

static void ResetParty(void)
{
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
}

static void SetHp(struct Pokemon *mon, u16 hp)
{
    SetMonData(mon, MON_DATA_HP, &hp);
}

static void CheckOnePath(u8 mode, u8 starterChoice, u16 species, u16 expectedItem)
{
    bool8 shouldBeProtected = (mode == 1);

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, mode);
    VarSet(VAR_STARTER_MON, starterChoice);

    if (ScriptGiveSamStarter(species) != MON_GIVEN_TO_PARTY)
        Fail("STARTCORE FAIL grant");
    MarkSamOriginalStarter();

    if (gPlayerPartyCount != 1)
        Fail("STARTCORE FAIL count");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != species)
        Fail("STARTCORE FAIL species");
    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != expectedItem)
        Fail("STARTCORE FAIL held item");
    if (species == SPECIES_EEVEE && GetMonGender(&gPlayerParty[0]) != MON_MALE)
        Fail("STARTCORE FAIL Eevee gender");

    if (!!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER) != shouldBeProtected)
        Fail("STARTCORE FAIL marker mode gate");

    SetHp(&gPlayerParty[0], 0);
    TryMarkMonPermanentDead(&gPlayerParty[0]);
    if (GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("STARTCORE FAIL starter marked dead");

    CreateMon(&gPlayerParty[1], species, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 2;
    SetHp(&gPlayerParty[1], 0);
    TryMarkMonPermanentDead(&gPlayerParty[1]);

    if (mode == 1)
    {
        if (!GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
            Fail("STARTCORE FAIL nonstarter not dead");
        if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER))
            Fail("STARTCORE FAIL same species protected");
    }
    else
    {
        if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
            Fail("STARTCORE FAIL standard death state");
    }
}

static void CheckMatrix(void)
{
    u8 mode;

    for (mode = 0; mode <= 1; mode++)
    {
        CheckOnePath(mode, 0, SPECIES_EEVEE, ITEM_NONE);
        CheckOnePath(mode, 1, SPECIES_PICHU, ITEM_NONE);
        CheckOnePath(mode, 2, SPECIES_DITTO, ITEM_ADAPTIVE_GENE);
    }
}

static void RunFresh(void)
{
    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));

    CheckMatrix();

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, 1);
    VarSet(VAR_STARTER_MON, 2);
    if (ScriptGiveSamStarter(SPECIES_DITTO) != MON_GIVEN_TO_PARTY)
        Fail("STARTCORE FAIL persistence grant");
    MarkSamOriginalStarter();

    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("STARTCORE FAIL persistence marker setup");
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("STARTCORE FAIL save");

    Log("STARTCORE PHASE1 PASS six path matrix saved");
    for (;;);
}

static void RunReload(void)
{
    if (VarGet(VAR_SAM_GAME_MODE) != 1 || VarGet(VAR_STARTER_MON) != 2)
        Fail("STARTCORE FAIL vars reload");
    if (gPlayerPartyCount != 1
     || GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_DITTO
     || GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != ITEM_ADAPTIVE_GENE
     || !GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("STARTCORE FAIL protected starter reload");

    Log("STARTCORE PASS six starter mode paths marker death save reload");
    for (;;);
}

void StartCore003_RunRuntimeMatrixQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
