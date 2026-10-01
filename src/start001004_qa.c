#include "global.h"
#include "battle.h"
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

#define START_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define START_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern u32 ApplyAdaptiveGeneDamageModifier(u32 damage, u8 battler);

static void QaLog(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        START_QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    START_QA_MGBA_DEBUG_STRING[i] = '\0';
    *START_QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
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

static void CheckStarterGrant(u16 species, u16 expectedItem)
{
    ResetParty();
    if (ScriptGiveSamStarter(species) != MON_GIVEN_TO_PARTY)
        Fail("STARTQA FAIL starter grant result");
    if (gPlayerPartyCount != 1)
        Fail("STARTQA FAIL starter count");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != species)
        Fail("STARTQA FAIL starter species");
    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != expectedItem)
        Fail("STARTQA FAIL starter item");
    if (species == SPECIES_EEVEE && GetMonGender(&gPlayerParty[0]) != MON_MALE)
        Fail("STARTQA FAIL starter Eevee gender");
}

static void CheckRivalMappings(void)
{
    static const u16 sBlue[3] = {SPECIES_DITTO, SPECIES_EEVEE, SPECIES_PICHU};
    static const u16 sGreen[3] = {SPECIES_PICHU, SPECIES_DITTO, SPECIES_EEVEE};
    static const u16 sBlueEndpoint[3] = {SPECIES_DITTO, SPECIES_FLAREON, SPECIES_RAICHU};
    static const u16 sGreenEndpoint[3] = {SPECIES_RAICHU, SPECIES_DITTO, SPECIES_ESPEON};
    u8 i;

    for (i = 0; i < 3; i++)
    {
        VarSet(VAR_STARTER_MON, i);
        GetSamBlueStarterSpecies();
        if (gSpecialVar_Result != sBlue[i])
            Fail("STARTQA FAIL Blue mapping");
        GetSamGreenStarterSpecies();
        if (gSpecialVar_Result != sGreen[i])
            Fail("STARTQA FAIL Green mapping");
        GetSamBlueStarterEndpointSpecies();
        if (gSpecialVar_Result != sBlueEndpoint[i])
            Fail("STARTQA FAIL Blue endpoint");
        GetSamGreenStarterEndpointSpecies();
        if (gSpecialVar_Result != sGreenEndpoint[i])
            Fail("STARTQA FAIL Green endpoint");
    }
}

static void CheckEvolutions(void)
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_EEVEE, 15, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_WATER_STONE) != SPECIES_VAPOREON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_THUNDER_STONE) != SPECIES_JOLTEON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_FIRE_STONE) != SPECIES_FLAREON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_SUN_STONE) != SPECIES_ESPEON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_MOON_STONE) != SPECIES_UMBREON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LEAF_STONE) != SPECIES_LEAFEON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_BRICK) != SPECIES_ECTOCEON)
        Fail("STARTQA FAIL Eevee evolution route");

    CreateMon(&mon, SPECIES_PICHU, 15, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_PIKACHU)
        Fail("STARTQA FAIL Pichu level evolution");

    CreateMon(&mon, SPECIES_PIKACHU, 35, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_RAICHU)
        Fail("STARTQA FAIL Pikachu level evolution");
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_THUNDER_STONE) != SPECIES_RAICHU)
        Fail("STARTQA FAIL Pikachu stone evolution");

    CreateMon(&mon, SPECIES_PICHU, 15, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_BRICK) != SPECIES_NONE)
        Fail("STARTQA FAIL Brick invalid target");
}

static void CheckAdaptiveGene(void)
{
    u16 item;
    u16 transformedSpecies = SPECIES_VAPOREON;

    ResetParty();
    CreateMon(&gPlayerParty[0], SPECIES_DITTO, 20, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 1;
    gBattlerPartyIndexes[0] = 0;
    gBattleMons[0].species = transformedSpecies;
    gBattleMons[0].item = ITEM_ADAPTIVE_GENE;

    if (ApplyAdaptiveGeneDamageModifier(5, 0) != 6
     || ApplyAdaptiveGeneDamageModifier(9, 0) != 10
     || ApplyAdaptiveGeneDamageModifier(10, 0) != 12
     || ApplyAdaptiveGeneDamageModifier(99, 0) != 118)
        Fail("STARTQA FAIL Adaptive Gene rounding");

    item = ITEM_NONE;
    gBattleMons[0].item = item;
    if (ApplyAdaptiveGeneDamageModifier(100, 0) != 100)
        Fail("STARTQA FAIL Adaptive Gene removal");

    CreateMon(&gPlayerParty[0], SPECIES_EEVEE, 20, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gBattleMons[0].species = SPECIES_DITTO;
    gBattleMons[0].item = ITEM_ADAPTIVE_GENE;
    if (ApplyAdaptiveGeneDamageModifier(100, 0) != 100)
        Fail("STARTQA FAIL non-Ditto original");
}

static void RunFresh(void)
{
    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));

    CheckStarterGrant(SPECIES_EEVEE, ITEM_NONE);
    CheckStarterGrant(SPECIES_PICHU, ITEM_NONE);
    CheckStarterGrant(SPECIES_DITTO, ITEM_ADAPTIVE_GENE);
    CheckRivalMappings();
    CheckEvolutions();
    CheckAdaptiveGene();

    ResetParty();
    if (ScriptGiveSamStarter(SPECIES_DITTO) != MON_GIVEN_TO_PARTY)
        Fail("STARTQA FAIL persistence grant");
    VarSet(VAR_STARTER_MON, 2);
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("STARTQA FAIL save");

    QaLog("STARTQA PHASE1 PASS starter mapping evolution gene state saved");
    for (;;);
}

static void RunReload(void)
{
    if (VarGet(VAR_STARTER_MON) != 2)
        Fail("STARTQA FAIL starter state reload");
    if (gPlayerPartyCount != 1
     || GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_DITTO
     || GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != ITEM_ADAPTIVE_GENE)
        Fail("STARTQA FAIL starter/item reload");

    QaLog("STARTQA PASS runtime starter mapping evolution gene rounding save reload");
    for (;;);
}

void Start001004_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
