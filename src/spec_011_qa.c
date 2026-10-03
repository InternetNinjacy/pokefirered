#include "global.h"
#include "gba/isagbprint.h"
#include "pokemon.h"
#include "constants/sam_pokedex.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

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

void Spec011Qa_RunRuntimeQa(void)
{
    u16 samDexNum;
    u16 otherDexNum;
    u16 species;
    u16 otherSpecies;

    MgbaOpen();

    if (SAM_DEX_COUNT != 205)
        Fail("SPEC011 QA FAIL count");

    for (samDexNum = 1; samDexNum <= SAM_DEX_COUNT; samDexNum++)
    {
        species = SamPokedexNumToSpecies(samDexNum);
        if (species == SPECIES_NONE)
            Fail("SPEC011 QA FAIL missing entry");

        if (SpeciesToSamPokedexNum(species) != samDexNum)
            Fail("SPEC011 QA FAIL reverse mapping");

        if (SpeciesToPokedexNum(species) != samDexNum)
            Fail("SPEC011 QA FAIL display number");

        for (otherDexNum = samDexNum + 1; otherDexNum <= SAM_DEX_COUNT; otherDexNum++)
        {
            otherSpecies = SamPokedexNumToSpecies(otherDexNum);
            if (otherSpecies == species)
                Fail("SPEC011 QA FAIL duplicate species");
        }
    }

    if (SamPokedexNumToSpecies(0) != SPECIES_NONE
     || SamPokedexNumToSpecies(SAM_DEX_COUNT + 1) != SPECIES_NONE
     || SpeciesToSamPokedexNum(SPECIES_NONE) != 0)
        Fail("SPEC011 QA FAIL bounds");

    if (SamPokedexNumToSpecies(SAM_DEX_RHYPERIOR) != SPECIES_RHYPERIOR
     || SpeciesToPokedexNum(SPECIES_RHYPERIOR) != SAM_DEX_RHYPERIOR)
        Fail("SPEC011 QA FAIL Rhyperior");

    if (SamPokedexNumToSpecies(SAM_DEX_LEAFEON) != SPECIES_LEAFEON
     || SpeciesToPokedexNum(SPECIES_LEAFEON) != SAM_DEX_LEAFEON)
        Fail("SPEC011 QA FAIL Leafeon");

    if (SamPokedexNumToSpecies(SAM_DEX_ECTOCEON) != SPECIES_ECTOCEON
     || SpeciesToPokedexNum(SPECIES_ECTOCEON) != SAM_DEX_ECTOCEON)
        Fail("SPEC011 QA FAIL Ectoceon");

    if (SamPokedexNumToSpecies(SAM_DEX_MEWTWO) != SPECIES_MEWTWO
     || SpeciesToPokedexNum(SPECIES_MEWTWO) != SAM_DEX_MEWTWO)
        Fail("SPEC011 QA FAIL Mewtwo");

    if (SamPokedexNumToSpecies(SAM_DEX_MEW) != SPECIES_MEW
     || SpeciesToPokedexNum(SPECIES_MEW) != SAM_DEX_MEW)
        Fail("SPEC011 QA FAIL Mew");

    Log("SPEC011 QA PASS 205-entry display mapping");
    for (;;);
}
