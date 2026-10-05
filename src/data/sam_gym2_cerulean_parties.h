// Pokémon: Sam Edition — Cerulean Fire Gym trainer and Leader parties.
// Current locked Gym2 package only. Trainer records and map bindings are integrated separately.

static const struct TrainerMonNoItemCustomMoves sParty_FireDancerLehua[] = {
    {
        .iv = 60,
        .lvl = 18,
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_LEER, MOVE_ROAR},
    },
    {
        .iv = 60,
        .lvl = 19,
        .species = SPECIES_PONYTA,
        .moves = {MOVE_EMBER, MOVE_STOMP, MOVE_TAIL_WHIP, MOVE_AGILITY},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_FireDancerKeahi[] = {
    {
        .iv = 60,
        .lvl = 19,
        .species = SPECIES_VULPIX,
        .moves = {MOVE_EMBER, MOVE_CONFUSE_RAY, MOVE_TAIL_WHIP, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 60,
        .lvl = 20,
        .species = SPECIES_CHARMELEON,
        .moves = {MOVE_EMBER, MOVE_METAL_CLAW, MOVE_SMOKESCREEN, MOVE_SCRATCH},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderLeilani[] = {
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_FLAREON,
        .moves = {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_SAND_ATTACK, MOVE_TAIL_WHIP},
    },
    {
        .iv = 100,
        .lvl = 21,
        .species = SPECIES_MAGMAR,
        .moves = {MOVE_EMBER, MOVE_SMOKESCREEN, MOVE_LEER, MOVE_KARATE_CHOP},
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_NINETALES,
        .moves = {MOVE_EMBER, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK, MOVE_WILL_O_WISP},
    },
};

static const struct TrainerMonItemCustomMoves sParty_LeaderLeilaniRematch[] = {
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_FLAREON,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_SHADOW_BALL, MOVE_QUICK_ATTACK, MOVE_WILL_O_WISP},
    },
    {
        .iv = 255,
        .lvl = 60,
        .species = SPECIES_MAGMAR,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_FLAMETHROWER, MOVE_THUNDER_PUNCH, MOVE_PSYCHIC, MOVE_CONFUSE_RAY},
    },
    {
        .iv = 255,
        .lvl = 61,
        .species = SPECIES_CAMERUPT,
        .heldItem = ITEM_QUICK_CLAW,
        .moves = {MOVE_ERUPTION, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_FLAMETHROWER},
    },
    {
        .iv = 255,
        .lvl = 62,
        .species = SPECIES_CHARIZARD,
        .heldItem = ITEM_SHARP_BEAK,
        .moves = {MOVE_FLAMETHROWER, MOVE_AERIAL_ACE, MOVE_BRICK_BREAK, MOVE_DRAGON_CLAW},
    },
    {
        .iv = 255,
        .lvl = 63,
        .species = SPECIES_BLAZIKEN,
        .heldItem = ITEM_BLACK_BELT,
        .moves = {MOVE_BLAZE_KICK, MOVE_SKY_UPPERCUT, MOVE_ROCK_SLIDE, MOVE_BULK_UP},
    },
    {
        .iv = 255,
        .lvl = 64,
        .species = SPECIES_NINETALES,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_SUNNY_DAY},
    },
};
