// Pokémon: Sam Edition — Batch 3 Cerulean-area ordinary trainer reconciliation.
// Route 24 grass-area trainer: settled local-ecology roster.
static const struct TrainerMonNoItemDefaultMoves sParty_SamRoute24CamperShane[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_PONYTA,
    },
};

// Batch 4 is included here so its party remaps are active before trainers.h is
// consumed by src/data.c, while leaving the shared vanilla party table untouched.
#include "sam_vermilion_trainer_parties.h"

// Batch 5 follows the same overlay path: keep live trainer IDs and records,
// but bind them to the settled Lavender / Rock Tunnel ordinary-trainer parties.
#include "sam_batch5_lavender_trainer_remaps.h"

// Batch 9 Cinnabar / Seafoam reconciliation uses the same non-invasive overlay path.
#include "sam_batch9_cinnabar_seafoam_trainer_remaps.h"

// ST-IMP-07 Routes 16-18 / Cycling Road.
#include "sam_batch7_cycling_road_trainer_remaps.h"

// ST-IMP-12 One Island first-visit ordinary trainers.
#include "sam_batch12_one_island_trainer_remaps.h"

// ST-IMP-13 Three Island / Bond Bridge ordinary trainers.
#include "sam_batch13_three_island_trainer_remaps.h"

// Five Island locked ordinary trainers; Rocket operation excluded.
#include "sam_batch14_five_island_trainer_remaps.h"

// Six Island locked ordinary trainers.
#include "sam_batch15_six_island_trainer_remaps.h"

// Seven Island ordinary trainers; Trainer Tower remains separate.
#include "sam_batch16_seven_island_trainer_remaps.h"
