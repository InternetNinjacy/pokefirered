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

#define INT_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define INT_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern void MarkSamOriginalStarter(void);

static void QaLog(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        INT_QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    INT_QA_MGBA_DEBUG_STRING[i] = '\0';
    *INT_QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    QaLog(text);
    for (;;);
}

static void ResetParty(void)
{
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
}

static void SetHp(struct Pokemon *mon, u16 hp)
{
    u8 data[2] = {hp, hp >> 8};
    SetMonData(mon, MON_DATA_HP, data);
}

static void CheckStarterMode(u16 species, u16 expectedItem, u16 mode)
{
    bool8 marked;
    u16 evolvedSpecies;

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, mode);

    if (ScriptGiveSamStarter(species) != MON_GIVEN_TO_PARTY)
        Fail("STARTCORE FAIL grant");
    MarkSamOriginalStarter();

    marked = GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER);
    if ((mode == 1 && !marked) || (mode == 0 && marked))
        Fail("STARTCORE FAIL protection mode");

    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != expectedItem)
        Fail("STARTCORE FAIL held item");

    if (species == SPECIES_EEVEE && GetMonGender(&gPlayerParty[0]) != MON_MALE)
        Fail("STARTCORE FAIL Eevee gender");

    SetHp(&gPlayerParty[0], 0);
    TryMarkMonPermanentDead(&gPlayerParty[0]);
    if (GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("STARTCORE FAIL starter death");

    CreateMon(&gPlayerParty[1], species, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 2;
    if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("STARTCORE FAIL same species protected");
    SetHp(&gPlayerParty[1], 0);
    TryMarkMonPermanentDead(&gPlayerParty[1]);
    if (mode == 1 && !GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("STARTCORE FAIL permanent nonstarter");
    if (mode == 0 && GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("STARTCORE FAIL standard nonstarter");

    if (mode == 1)
    {
        if (species == SPECIES_EEVEE)
            evolvedSpecies = SPECIES_VAPOREON;
        else if (species == SPECIES_PICHU)
            evolvedSpecies = SPECIES_PIKACHU;
        else
            evolvedSpecies = SPECIES_DITTO;
        SetMonData(&gPlayerParty[0], MON_DATA_SPECIES, &evolvedSpecies);
        if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
            Fail("STARTCORE FAIL evolution protection");
    }
}

static void RunFresh(void)
{
    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));

    CheckStarterMode(SPECIES_EEVEE, ITEM_NONE, 0);
    CheckStarterMode(SPECIES_PICHU, ITEM_NONE, 0);
    CheckStarterMode(SPECIES_DITTO, ITEM_ADAPTIVE_GENE, 0);
    CheckStarterMode(SPECIES_EEVEE, ITEM_NONE, 1);
    CheckStarterMode(SPECIES_PICHU, ITEM_NONE, 1);
    CheckStarterMode(SPECIES_DITTO, ITEM_ADAPTIVE_GENE, 1);

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, 1);
    if (ScriptGiveSamStarter(SPECIES_DITTO) != MON_GIVEN_TO_PARTY)
        Fail("STARTCORE FAIL persistence grant");
    MarkSamOriginalStarter();
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("STARTCORE FAIL save");

    QaLog("STARTCORE PHASE1 PASS six starter-mode paths exact protection state saved");
    for (;;);
}

static void RunReload(void)
{
    if (VarGet(VAR_SAM_GAME_MODE) != 1)
        Fail("STARTCORE FAIL mode reload");
    if (gPlayerPartyCount != 1
     || GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_DITTO
     || GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != ITEM_ADAPTIVE_GENE
     || !GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("STARTCORE FAIL reload state");

    QaLog("STARTCORE PASS six-path mode starter protection gene save reload");
    for (;;);
}

void StartCoreIntegration_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
