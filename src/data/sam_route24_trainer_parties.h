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
#include "data/sam_vermilion_trainer_parties.h"
