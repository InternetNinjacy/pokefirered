// Sam Edition production overlay for Tropius.
// The live species table is preserved verbatim in species_info_base.h.  This
// wrapper redirects only the legacy Tropius initializer to a placeholder that
// is overwritten later in the base table, then installs the closed Sam Edition
// Tropius package at the real species index.

#undef SPECIES_TROPIUS
#define SPECIES_TROPIUS 369] = \
    { \
        .baseHP = 110, \
        .baseAttack = 95, \
        .baseDefense = 105, \
        .baseSpeed = 65, \
        .baseSpAttack = 105, \
        .baseSpDefense = 100, \
        .types = {TYPE_GRASS, TYPE_FLYING}, \
        .catchRate = 200, \
        .expYield = 169, \
        .evYield_HP = 2, \
        .evYield_Attack = 0, \
        .evYield_Defense = 0, \
        .evYield_Speed = 0, \
        .evYield_SpAttack = 0, \
        .evYield_SpDefense = 0, \
        .itemCommon = ITEM_NONE, \
        .itemRare = ITEM_NONE, \
        .genderRatio = PERCENT_FEMALE(50), \
        .eggCycles = 25, \
        .friendship = 70, \
        .growthRate = GROWTH_SLOW, \
        .eggGroups = {EGG_GROUP_MONSTER, EGG_GROUP_GRASS}, \
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE}, \
        .safariZoneFleeRate = 0, \
        .bodyColor = BODY_COLOR_GREEN, \
        .noFlip = FALSE, \
    }, \
    [SPECIES_OLD_UNOWN_B

#include "data/pokemon/species_info_base.h"

#undef SPECIES_TROPIUS
#define SPECIES_TROPIUS 369
