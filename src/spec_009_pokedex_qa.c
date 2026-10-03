#include "global.h"
#include "gba/isagbprint.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/pokedex.h"
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

void Spec009PokedexQa_RunRuntimeQa(void)
{
    if (NATIONAL_DEX_COUNT != NATIONAL_DEX_DEOXYS || NATIONAL_DEX_DEOXYS != 386)
        Fail("SPEC009DEX QA FAIL national count");

    if (SAM_DEX_FLAG_LEAFEON != 412
     || SAM_DEX_FLAG_ECTOCEON != 413
     || SAM_DEX_FLAG_RHYPERIOR != 414)
        Fail("SPEC009DEX QA FAIL backing ids");

    if (SAM_DEX_FLAG_MAX > DEX_FLAGS_NO * 8)
        Fail("SPEC009DEX QA FAIL flag capacity");

    if (SpeciesToNationalPokedexNum(SPECIES_LEAFEON) != SAM_DEX_FLAG_LEAFEON
     || SpeciesToNationalPokedexNum(SPECIES_ECTOCEON) != SAM_DEX_FLAG_ECTOCEON
     || SpeciesToNationalPokedexNum(SPECIES_RHYPERIOR) != SAM_DEX_FLAG_RHYPERIOR)
        Fail("SPEC009DEX QA FAIL forward map");

    if (NationalPokedexNumToSpecies(SAM_DEX_FLAG_LEAFEON) != SPECIES_LEAFEON
     || NationalPokedexNumToSpecies(SAM_DEX_FLAG_ECTOCEON) != SPECIES_ECTOCEON
     || NationalPokedexNumToSpecies(SAM_DEX_FLAG_RHYPERIOR) != SPECIES_RHYPERIOR)
        Fail("SPEC009DEX QA FAIL reverse map");

    if (SpeciesToNationalPokedexNum(SPECIES_OLD_UNOWN_B) != NATIONAL_DEX_OLD_UNOWN_B
     || SpeciesToNationalPokedexNum(SPECIES_OLD_UNOWN_C) != NATIONAL_DEX_OLD_UNOWN_C
     || SpeciesToNationalPokedexNum(SPECIES_OLD_UNOWN_D) != NATIONAL_DEX_OLD_UNOWN_D)
        Fail("SPEC009DEX QA FAIL old unown collision");

    GetSetPokedexFlag(SAM_DEX_FLAG_LEAFEON, FLAG_SET_SEEN);
    GetSetPokedexFlag(SAM_DEX_FLAG_LEAFEON, FLAG_SET_CAUGHT);
    if (!GetSetPokedexFlag(SAM_DEX_FLAG_LEAFEON, FLAG_GET_SEEN)
     || !GetSetPokedexFlag(SAM_DEX_FLAG_LEAFEON, FLAG_GET_CAUGHT))
        Fail("SPEC009DEX QA FAIL Leafeon flags");

    if (GetSetPokedexFlag(SAM_DEX_FLAG_ECTOCEON, FLAG_GET_SEEN)
     || GetSetPokedexFlag(SAM_DEX_FLAG_RHYPERIOR, FLAG_GET_SEEN))
        Fail("SPEC009DEX QA FAIL flag isolation");

    GetSetPokedexFlag(SAM_DEX_FLAG_ECTOCEON, FLAG_SET_SEEN);
    GetSetPokedexFlag(SAM_DEX_FLAG_ECTOCEON, FLAG_SET_CAUGHT);
    GetSetPokedexFlag(SAM_DEX_FLAG_RHYPERIOR, FLAG_SET_SEEN);
    GetSetPokedexFlag(SAM_DEX_FLAG_RHYPERIOR, FLAG_SET_CAUGHT);

    if (!GetSetPokedexFlag(SAM_DEX_FLAG_ECTOCEON, FLAG_GET_CAUGHT)
     || !GetSetPokedexFlag(SAM_DEX_FLAG_RHYPERIOR, FLAG_GET_CAUGHT))
        Fail("SPEC009DEX QA FAIL custom flags");

    Log("SPEC009DEX QA PASS custom seen-owned backing");
    for (;;);
}
