#include "global.h"
#include "data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/sam_pokedex.h"

#define QA_MGBA_DEBUG_ENABLE ((vu16 *)0x4FFF780)
#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon *src);

static const u16 sSpecies[] =
{
    SPECIES_LEAFEON,
    SPECIES_ECTOCEON,
    SPECIES_RHYPERIOR,
};

static const u16 sBacking[] =
{
    412,
    413,
    414,
};

static const u16 sDisplay[] =
{
    183,
    184,
    146,
};

static void Log(const char *text)
{
    u32 i = 0;

    *QA_MGBA_DEBUG_ENABLE = 0xC0DE;
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

static void CheckRuntimeIndexSurfaces(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sSpecies); i++)
    {
        u16 species = sSpecies[i];
        struct Pokemon mon;

        CreateMon(&mon, species, 35, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);

        if (GetMonData(&mon, MON_DATA_SPECIES) != species)
            Fail("SPEC009BOUNDS FAIL create species");
        if (gSpeciesInfo[species].baseHP == 0)
            Fail("SPEC009BOUNDS FAIL species info");
        if (gLevelUpLearnsets[species] == NULL)
            Fail("SPEC009BOUNDS FAIL learnset ptr");
        if (SpeciesToNationalPokedexNum(species) != sBacking[i])
            Fail("SPEC009BOUNDS FAIL backing map");
        if (NationalPokedexNumToSpecies(sBacking[i]) != species)
            Fail("SPEC009BOUNDS FAIL reverse backing map");
        if (SpeciesToSamPokedexNum(species) != sDisplay[i])
            Fail("SPEC009BOUNDS FAIL display map");
        if (SamPokedexNumToSpecies(sDisplay[i]) != species)
            Fail("SPEC009BOUNDS FAIL reverse display map");
        if (gMonFrontPicTable[species].data == NULL
         || gMonBackPicTable[species].data == NULL
         || gMonPaletteTable[species].data == NULL
         || gMonShinyPaletteTable[species].data == NULL)
            Fail("SPEC009BOUNDS FAIL graphics table");
        if (gMonFrontPicCoords[species].size == 0
         || gMonBackPicCoords[species].size == 0)
            Fail("SPEC009BOUNDS FAIL coords");
        if (gMonIconTable[species] == NULL)
            Fail("SPEC009BOUNDS FAIL icon table");
        if (GetMonIconPaletteIndexFromSpecies(species) > 2)
            Fail("SPEC009BOUNDS FAIL icon palette");
        if (SpeciesToCryId(species - 1) > 0x1FF)
            Fail("SPEC009BOUNDS FAIL cry lookup");
    }
}

static void SetDexFlags(void)
{
    u32 i;

    ResetPokedex();
    for (i = 0; i < ARRAY_COUNT(sSpecies); i++)
    {
        GetSetPokedexFlag(sBacking[i], FLAG_SET_SEEN);
        GetSetPokedexFlag(sBacking[i], FLAG_SET_CAUGHT);
        if (!GetSetPokedexFlag(sBacking[i], FLAG_GET_SEEN))
            Fail("SPEC009BOUNDS FAIL get seen");
        if (!GetSetPokedexFlag(sBacking[i], FLAG_GET_CAUGHT))
            Fail("SPEC009BOUNDS FAIL get caught");
    }
}

static void RunFresh(void)
{
    u32 i;

    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;

    CheckRuntimeIndexSurfaces();
    SetDexFlags();

    for (i = 0; i < ARRAY_COUNT(sSpecies); i++)
    {
        CreateMon(&gPlayerParty[i], sSpecies[i], 35 + i, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != sSpecies[i])
            Fail("SPEC009BOUNDS FAIL party before save");
        SetBoxMonAt(0, i, &gPlayerParty[i].box);
        if (GetBoxMonDataAt(0, i, MON_DATA_SPECIES) != sSpecies[i])
            Fail("SPEC009BOUNDS FAIL box before save");
    }
    gPlayerPartyCount = ARRAY_COUNT(sSpecies);

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("SPEC009BOUNDS FAIL save");

    Log("SPEC009BOUNDS PHASE1 PASS indexes party box dex saved");
    for (;;);
}

static void RunReload(void)
{
    u32 i;

    if (gPlayerPartyCount != ARRAY_COUNT(sSpecies))
        Fail("SPEC009BOUNDS FAIL party count reload");

    for (i = 0; i < ARRAY_COUNT(sSpecies); i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != sSpecies[i])
            Fail("SPEC009BOUNDS FAIL party species reload");
        if (GetBoxMonDataAt(0, i, MON_DATA_SPECIES) != sSpecies[i])
            Fail("SPEC009BOUNDS FAIL box species reload");
        if (!GetSetPokedexFlag(sBacking[i], FLAG_GET_SEEN)
         || !GetSetPokedexFlag(sBacking[i], FLAG_GET_CAUGHT))
            Fail("SPEC009BOUNDS FAIL dex flags reload");
        if (SpeciesToNationalPokedexNum(sSpecies[i]) != sBacking[i]
         || SpeciesToSamPokedexNum(sSpecies[i]) != sDisplay[i])
            Fail("SPEC009BOUNDS FAIL mappings reload");
    }

    CheckRuntimeIndexSurfaces();

    Log("SPEC009BOUNDS QA PASS bounds and save reload");
    for (;;);
}

void Spec009BoundsSaveQa_Run(void)
{
    u8 loadStatus;

    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
