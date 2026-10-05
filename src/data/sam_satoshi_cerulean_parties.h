#ifndef GUARD_DATA_SAM_SATOSHI_CERULEAN_PARTIES_H
#define GUARD_DATA_SAM_SATOSHI_CERULEAN_PARTIES_H

// Pokémon: Sam Edition — Satoshi Cerulean Fire Gym practice/rematch package.
// Recovered from the existing Cerulean production implementation and staged
// independently so Satoshi-owned trainer data can advance without merging the
// full Cerulean Gym branch.

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiCeruleanPractice[] = {
    {
        .iv = 50,
        .lvl = 20,
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_ROAR, MOVE_LEER},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SatoshiCeruleanRematch[] = {
    {
        .iv = 200,
        .lvl = 55,
        .species = SPECIES_NINETALES,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_SAFEGUARD},
    },
    {
        .iv = 200,
        .lvl = 56,
        .species = SPECIES_MAGMAR,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_PSYCHIC, MOVE_CONFUSE_RAY, MOVE_BRICK_BREAK},
    },
    {
        .iv = 200,
        .lvl = 57,
        .species = SPECIES_RAPIDASH,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_BOUNCE, MOVE_IRON_TAIL, MOVE_SUNNY_DAY},
    },
    {
        .iv = 200,
        .lvl = 58,
        .species = SPECIES_TYPHLOSION,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_BRICK_BREAK, MOVE_AERIAL_ACE, MOVE_SMOKESCREEN},
    },
    {
        .iv = 200,
        .lvl = 59,
        .species = SPECIES_HOUNDOOM,
        .heldItem = ITEM_BLACK_GLASSES,
        .moves = {MOVE_FLAMETHROWER, MOVE_CRUNCH, MOVE_WILL_O_WISP, MOVE_ROAR},
    },
    {
        .iv = 200,
        .lvl = 60,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_FLAMETHROWER, MOVE_EXTREME_SPEED, MOVE_CRUNCH, MOVE_IRON_TAIL},
    },
};

#endif // GUARD_DATA_SAM_SATOSHI_CERULEAN_PARTIES_H
