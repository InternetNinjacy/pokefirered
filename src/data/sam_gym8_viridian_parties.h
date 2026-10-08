// Pokemon: Sam Edition - Viridian Gym 8 locked trainer packages.
// Ordinary Gym Trainers use default level-up moves unless a held item was explicitly locked.

static const struct TrainerMonNoItemDefaultMoves sParty_SamGym8Cole[] = {
    {.iv = 40, .lvl = 39, .species = SPECIES_HOUNDOOM},
    {.iv = 40, .lvl = 39, .species = SPECIES_DRAGONAIR},
};

static const struct TrainerMonItemDefaultMoves sParty_SamGym8Kiyo[] = {
    {.iv = 100, .lvl = 43, .species = SPECIES_SHELGON, .heldItem = ITEM_SITRUS_BERRY},
};

static const struct TrainerMonNoItemDefaultMoves sParty_SamGym8Samuel[] = {
    {.iv = 100, .lvl = 37, .species = SPECIES_MAGNETON},
    {.iv = 100, .lvl = 37, .species = SPECIES_MACHAMP},
    {.iv = 100, .lvl = 38, .species = SPECIES_STARMIE},
    {.iv = 100, .lvl = 39, .species = SPECIES_SCIZOR},
    {.iv = 100, .lvl = 39, .species = SPECIES_VIBRAVA},
};

static const struct TrainerMonNoItemDefaultMoves sParty_SamGym8Yuji[] = {
    {.iv = 100, .lvl = 38, .species = SPECIES_ARCANINE},
    {.iv = 100, .lvl = 38, .species = SPECIES_LAPRAS},
    {.iv = 100, .lvl = 38, .species = SPECIES_HERACROSS},
    {.iv = 100, .lvl = 38, .species = SPECIES_ALAKAZAM},
    {.iv = 100, .lvl = 38, .species = SPECIES_DRAGONAIR},
};

static const struct TrainerMonNoItemDefaultMoves sParty_SamGym8Atsushi[] = {
    {.iv = 100, .lvl = 40, .species = SPECIES_HARIYAMA},
    {.iv = 100, .lvl = 40, .species = SPECIES_SHELGON},
};

static const struct TrainerMonItemDefaultMoves sParty_SamGym8Jason[] = {
    {.iv = 40, .lvl = 43, .species = SPECIES_VIBRAVA, .heldItem = ITEM_SITRUS_BERRY},
};

static const struct TrainerMonNoItemDefaultMoves sParty_SamGym8Warren[] = {
    {.iv = 100, .lvl = 37, .species = SPECIES_AMPHAROS},
    {.iv = 100, .lvl = 37, .species = SPECIES_STEELIX},
    {.iv = 100, .lvl = 38, .species = SPECIES_GARDEVOIR},
    {.iv = 100, .lvl = 39, .species = SPECIES_LUDICOLO},
    {.iv = 100, .lvl = 39, .species = SPECIES_DRAGONAIR},
};

static const struct TrainerMonNoItemDefaultMoves sParty_SamGym8Takashi[] = {
    {.iv = 100, .lvl = 38, .species = SPECIES_WALREIN},
    {.iv = 100, .lvl = 38, .species = SPECIES_ELECTABUZZ},
    {.iv = 100, .lvl = 38, .species = SPECIES_VIBRAVA},
};

static const struct TrainerMonItemCustomMoves sParty_SamGym8Giovanni[] = {
    {
        .iv = 0, .lvl = 42, .species = SPECIES_DRAGONAIR, .heldItem = ITEM_NONE,
        .moves = {MOVE_THUNDER_WAVE, MOVE_ICE_BEAM, MOVE_SURF, MOVE_DRAGON_RAGE},
    },
    {
        .iv = 0, .lvl = 44, .species = SPECIES_KINGDRA, .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_RAIN_DANCE},
    },
    {
        .iv = 0, .lvl = 45, .species = SPECIES_FLYGON, .heldItem = ITEM_SOFT_SAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_DRAGON_BREATH, MOVE_CRUNCH, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 0, .lvl = 45, .species = SPECIES_ALTARIA, .heldItem = ITEM_NONE,
        .moves = {MOVE_AERIAL_ACE, MOVE_DRAGON_BREATH, MOVE_SING, MOVE_SAFEGUARD},
    },
    {
        .iv = 0, .lvl = 50, .species = SPECIES_SALAMENCE, .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_CLAW, MOVE_EARTHQUAKE, MOVE_AERIAL_ACE, MOVE_FLAMETHROWER},
    },
};
