#include "global.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "constants/abilities.h"
#include "constants/global.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/types.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

#define QA_STAGE_INDEX 4
#define QA_STAGE_SAVED 0x53

extern void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon *src);
extern void BoxMonAtToMon(u8 boxId, u8 boxPosition, struct Pokemon *dst);

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

static void MakeMon(struct Pokemon *mon, u16 species, u8 level)
{
    CreateMon(mon, species, level, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static bool8 IndexInList(u8 index, const u8 *list, u8 count)
{
    u8 i;
    for (i = 0; i < count; i++)
        if (list[i] == index)
            return TRUE;
    return FALSE;
}

static void ExpectFullMachineSet(u16 species, const u8 *tms, u8 tmCount, const u8 *hms, u8 hmCount)
{
    struct Pokemon mon;
    u8 i;

    MakeMon(&mon, species, 25);
    for (i = 0; i < NUM_TECHNICAL_MACHINES; i++)
    {
        bool8 expected = IndexInList(i + 1, tms, tmCount);
        bool8 actual = CanMonLearnTMHM(&mon, i) != 0;
        if (actual != expected)
            Fail("RN001 FAIL exact TM set");
    }

    for (i = 0; i < NUM_HIDDEN_MACHINES; i++)
    {
        bool8 expected = IndexInList(i + 1, hms, hmCount);
        bool8 actual = CanMonLearnTMHM(&mon, NUM_TECHNICAL_MACHINES + i) != 0;
        if (actual != expected)
            Fail("RN001 FAIL exact HM set");
    }
}

static void CheckSpeciesAndMachines(void)
{
    static const u8 raltsTms[] = {1,2,4,5,14,20,29,34,38,42,46,47,48,50,51,52,53,54,55,56,64,68};
    static const u8 gardevoirTms[] = {1,2,3,4,5,14,20,29,34,38,42,46,47,48,50,51,52,53,54,55,56,64,68};
    static const u8 natuTms[] = {2,4,5,11,12,13,14,29,32,38,42,43,45,50,51,52,53,54,64,68};
    static const u8 xatuTms[] = {2,3,4,5,11,12,13,14,29,32,38,42,43,45,50,51,52,53,54,64,68};
    static const u8 flashOnly[] = {5};
    static const u8 xatuHms[] = {2,5};

    if (gSpeciesInfo[SPECIES_RALTS].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_RALTS].types[1] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_KIRLIA].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_KIRLIA].types[1] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_GARDEVOIR].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_GARDEVOIR].types[1] != TYPE_PSYCHIC)
        Fail("RN001 FAIL Ralts family typing");

    if (gSpeciesInfo[SPECIES_NATU].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_NATU].types[1] != TYPE_FLYING
     || gSpeciesInfo[SPECIES_XATU].types[0] != TYPE_PSYCHIC
     || gSpeciesInfo[SPECIES_XATU].types[1] != TYPE_FLYING)
        Fail("RN001 FAIL Natu family typing");

    if (gSpeciesInfo[SPECIES_RALTS].abilities[0] != ABILITY_SYNCHRONIZE
     || gSpeciesInfo[SPECIES_RALTS].abilities[1] != ABILITY_TRACE
     || gSpeciesInfo[SPECIES_NATU].abilities[0] != ABILITY_SYNCHRONIZE
     || gSpeciesInfo[SPECIES_NATU].abilities[1] != ABILITY_EARLY_BIRD)
        Fail("RN001 FAIL abilities");

    ExpectFullMachineSet(SPECIES_RALTS, raltsTms, ARRAY_COUNT(raltsTms), flashOnly, ARRAY_COUNT(flashOnly));
    ExpectFullMachineSet(SPECIES_KIRLIA, raltsTms, ARRAY_COUNT(raltsTms), flashOnly, ARRAY_COUNT(flashOnly));
    ExpectFullMachineSet(SPECIES_GARDEVOIR, gardevoirTms, ARRAY_COUNT(gardevoirTms), flashOnly, ARRAY_COUNT(flashOnly));
    ExpectFullMachineSet(SPECIES_NATU, natuTms, ARRAY_COUNT(natuTms), flashOnly, ARRAY_COUNT(flashOnly));
    ExpectFullMachineSet(SPECIES_XATU, xatuTms, ARRAY_COUNT(xatuTms), xatuHms, ARRAY_COUNT(xatuHms));
}

static void CheckEvolution(u16 species, u8 belowLevel, u8 evolveLevel, u16 expected)
{
    struct Pokemon mon;

    MakeMon(&mon, species, belowLevel);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_NONE)
        Fail("RN001 FAIL early evolution");

    MakeMon(&mon, species, evolveLevel);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != expected)
        Fail("RN001 FAIL evolution threshold");
}

static void CheckEvolutionThresholds(void)
{
    CheckEvolution(SPECIES_RALTS, 19, 20, SPECIES_KIRLIA);
    CheckEvolution(SPECIES_KIRLIA, 29, 30, SPECIES_GARDEVOIR);
    CheckEvolution(SPECIES_NATU, 24, 25, SPECIES_XATU);
}

static void CheckDexRoundTrip(u16 species)
{
    u16 dex = SpeciesToNationalPokedexNum(species);
    if (dex == 0 || NationalPokedexNumToSpecies(dex) != species)
        Fail("RN001 FAIL Pokedex mapping");
    GetSetPokedexFlag(dex, FLAG_SET_SEEN);
    GetSetPokedexFlag(dex, FLAG_SET_CAUGHT);
    if (!GetSetPokedexFlag(dex, FLAG_GET_SEEN) || !GetSetPokedexFlag(dex, FLAG_GET_CAUGHT))
        Fail("RN001 FAIL Pokedex registration");
}

static void PrepareAndSave(void)
{
    struct Pokemon temp;

    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;

    CheckSpeciesAndMachines();
    CheckEvolutionThresholds();

    MakeMon(&gPlayerParty[0], SPECIES_RALTS, 16);
    MakeMon(&gPlayerParty[1], SPECIES_NATU, 24);
    gPlayerPartyCount = 2;

    MakeMon(&temp, SPECIES_KIRLIA, 25);
    SetBoxMonAt(0, 0, &temp.box);
    MakeMon(&temp, SPECIES_XATU, 35);
    SetBoxMonAt(0, 1, &temp.box);

    CheckDexRoundTrip(SPECIES_RALTS);
    CheckDexRoundTrip(SPECIES_KIRLIA);
    CheckDexRoundTrip(SPECIES_GARDEVOIR);
    CheckDexRoundTrip(SPECIES_NATU);
    CheckDexRoundTrip(SPECIES_XATU);

    gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] = QA_STAGE_SAVED;
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("RN001 FAIL save");

    Log("RN001 PHASE1 PASS species evolution machines party PC dex saved");
    for (;;);
}

static void CheckReload(void)
{
    struct Pokemon temp;
    const u16 species[] = {SPECIES_RALTS, SPECIES_KIRLIA, SPECIES_GARDEVOIR, SPECIES_NATU, SPECIES_XATU};
    u8 i;

    if (gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] != QA_STAGE_SAVED)
        Fail("RN001 FAIL stage reload");
    if (gPlayerPartyCount != 2
     || GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_RALTS
     || GetMonData(&gPlayerParty[1], MON_DATA_SPECIES) != SPECIES_NATU)
        Fail("RN001 FAIL party reload");

    BoxMonAtToMon(0, 0, &temp);
    if (GetMonData(&temp, MON_DATA_SPECIES) != SPECIES_KIRLIA)
        Fail("RN001 FAIL Kirlia PC reload");
    BoxMonAtToMon(0, 1, &temp);
    if (GetMonData(&temp, MON_DATA_SPECIES) != SPECIES_XATU)
        Fail("RN001 FAIL Xatu PC reload");

    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        u16 dex = SpeciesToNationalPokedexNum(species[i]);
        if (!GetSetPokedexFlag(dex, FLAG_GET_SEEN) || !GetSetPokedexFlag(dex, FLAG_GET_CAUGHT))
            Fail("RN001 FAIL dex reload");
    }

    CheckSpeciesAndMachines();
    CheckEvolutionThresholds();

    Log("RN001 QA PASS reload party PC dex evolution exact TMHM");
    for (;;);
}

void Spec003QaRn001_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);

    if (loadStatus != SAVE_STATUS_OK)
        PrepareAndSave();

    CheckReload();
}
