#include "global.h"
#include "gba/isagbprint.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern bool8 Spec008QaBuildBirdDittoEgg(u16 bird, u16 *eggSpecies, u16 *moves);
extern u8 Spec008QaBirdPairCompatibility(u16 birdA, u16 birdB);

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
    CreateMon(mon, species, level, 20, TRUE, 0x12345678, OT_ID_PLAYER_ID, 0);
}

static void ExpectMoves(u16 species, u8 level, const u16 *moves, u8 count)
{
    struct Pokemon mon;
    u8 i;

    MakeMon(&mon, species, level);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 actual = GetMonData(&mon, MON_DATA_MOVE1 + i);
        u16 expected = (i < count) ? moves[i] : MOVE_NONE;
        if (actual != expected)
            Fail("SPEC008 FAIL generated moves");
    }
}

static void ExpectEggMoves(u16 bird, const u16 *moves, u8 count)
{
    u16 eggSpecies = SPECIES_NONE;
    u16 actualMoves[MAX_MON_MOVES] = {0};
    u8 i;

    if (!Spec008QaBuildBirdDittoEgg(bird, &eggSpecies, actualMoves))
        Fail("SPEC008 FAIL bird Ditto compatibility");
    if (eggSpecies != bird)
        Fail("SPEC008 FAIL bird Egg species");
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 expected = (i < count) ? moves[i] : MOVE_NONE;
        if (actualMoves[i] != expected)
            Fail("SPEC008 FAIL bird Egg moves");
    }
}

static void CheckSpeciesAndBreeding(void)
{
    static const u16 birds[] = {SPECIES_ARTICUNO, SPECIES_ZAPDOS, SPECIES_MOLTRES};
    u8 i;

    for (i = 0; i < ARRAY_COUNT(birds); i++)
    {
        const struct SpeciesInfo *info = &gSpeciesInfo[birds[i]];
        if (info->genderRatio != MON_GENDERLESS
         || info->eggGroups[0] != EGG_GROUP_FLYING
         || info->eggGroups[1] != EGG_GROUP_FLYING
         || info->abilities[0] != ABILITY_PRESSURE)
            Fail("SPEC008 FAIL bird breeding metadata");
    }

    if (Spec008QaBirdPairCompatibility(SPECIES_ARTICUNO, SPECIES_ZAPDOS) != 0
     || Spec008QaBirdPairCompatibility(SPECIES_ZAPDOS, SPECIES_MOLTRES) != 0
     || Spec008QaBirdPairCompatibility(SPECIES_MOLTRES, SPECIES_ARTICUNO) != 0)
        Fail("SPEC008 FAIL bird bird incompatible");
}

static void CheckMoves(void)
{
    static const u16 a5[] = {MOVE_GUST, MOVE_POWDER_SNOW, MOVE_HAZE};
    static const u16 a50[] = {MOVE_ICY_WIND, MOVE_AGILITY, MOVE_DRILL_PECK, MOVE_ICE_BEAM};
    static const u16 z5[] = {MOVE_PECK, MOVE_THUNDER_SHOCK, MOVE_SHOCK_WAVE};
    static const u16 z50[] = {MOVE_THUNDER_WAVE, MOVE_AGILITY, MOVE_DRILL_PECK, MOVE_THUNDERBOLT};
    static const u16 m5[] = {MOVE_EMBER, MOVE_FIRE_SPIN, MOVE_PECK};
    static const u16 m50[] = {MOVE_WING_ATTACK, MOVE_AGILITY, MOVE_WILL_O_WISP, MOVE_FLAMETHROWER};

    ExpectMoves(SPECIES_ARTICUNO, 5, a5, ARRAY_COUNT(a5));
    ExpectMoves(SPECIES_ARTICUNO, 50, a50, ARRAY_COUNT(a50));
    ExpectMoves(SPECIES_ZAPDOS, 5, z5, ARRAY_COUNT(z5));
    ExpectMoves(SPECIES_ZAPDOS, 50, z50, ARRAY_COUNT(z50));
    ExpectMoves(SPECIES_MOLTRES, 5, m5, ARRAY_COUNT(m5));
    ExpectMoves(SPECIES_MOLTRES, 50, m50, ARRAY_COUNT(m50));

    ExpectEggMoves(SPECIES_ARTICUNO, a5, ARRAY_COUNT(a5));
    ExpectEggMoves(SPECIES_ZAPDOS, z5, ARRAY_COUNT(z5));
    ExpectEggMoves(SPECIES_MOLTRES, m5, ARRAY_COUNT(m5));
}

void Spec008QaLegendaryBirds_RunRuntimeQa(void)
{
    MgbaOpen();
    CheckSpeciesAndBreeding();
    CheckMoves();
    Log("SPEC008 QA PASS bird Ditto eggs Lv5 and Lv50 moves");
    for (;;);
}
