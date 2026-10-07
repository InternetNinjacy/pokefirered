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
