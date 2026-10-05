#ifndef GUARD_DATA_SAM_SATOSHI_VIRIDIAN_PARTIES_H
#define GUARD_DATA_SAM_SATOSHI_VIRIDIAN_PARTIES_H

// Pokemon: Sam Edition - Viridian Dragon Gym Satoshi practice/rematch package.
// Practice remains below the current regular-trainer floor (Lv. 37).

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiViridianPractice[] = {
    {
        .iv = 50,
        .lvl = 36,
        .species = SPECIES_DRATINI,
        .moves = {MOVE_DRAGON_RAGE, MOVE_THUNDER_WAVE, MOVE_SLAM, MOVE_AGILITY},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SatoshiViridianRematch[] = {
    {
        .iv = 200,
        .lvl = 59,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_RETURN, MOVE_EARTHQUAKE, MOVE_HYDRO_PUMP},
    },
    {
        .iv = 200,
        .lvl = 60,
        .species = SPECIES_LAPRAS,
        .heldItem = ITEM_NEVER_MELT_ICE,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_THUNDERBOLT, MOVE_SING},
    },
    {
        .iv = 200,
        .lvl = 60,
        .species = SPECIES_TYRANITAR,
        .heldItem = ITEM_HARD_STONE,
        .moves = {MOVE_ROCK_SLIDE, MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_BRICK_BREAK},
    },
    {
        .iv = 200,
        .lvl = 61,
        .species = SPECIES_AERODACTYL,
        .heldItem = ITEM_HARD_STONE,
        .moves = {MOVE_ROCK_SLIDE, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE, MOVE_DOUBLE_EDGE},
    },
    {
        .iv = 200,
        .lvl = 62,
        .species = SPECIES_CHARIZARD,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_AERIAL_ACE, MOVE_DRAGON_CLAW, MOVE_BRICK_BREAK},
    },
    {
        .iv = 200,
        .lvl = 63,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_DRAGON_CLAW, MOVE_ICE_BEAM, MOVE_THUNDER_WAVE, MOVE_WING_ATTACK},
    },
};

#endif // GUARD_DATA_SAM_SATOSHI_VIRIDIAN_PARTIES_H
