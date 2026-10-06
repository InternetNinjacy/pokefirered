// Saffron Hothouse trainer parties.
//
// The Hothouse deliberately consumes otherwise-unused Ruby/Sapphire dummy
// trainer slots for battle presentation.  The live FireRed trainer table is
// left intact; src/data.c redirects only those dummy party pointers here.

static const struct TrainerMonNoItemCustomMoves sParty_SamHothouseIrrigation[] = {
    {
        .iv = 100,
        .lvl = 28,
        .species = SPECIES_EXEGGCUTE,
        .moves = {MOVE_CONFUSION, MOVE_LEECH_SEED, MOVE_REFLECT, MOVE_STUN_SPORE},
    },
    {
        .iv = 100,
        .lvl = 28,
        .species = SPECIES_PARASECT,
        .moves = {MOVE_MEGA_DRAIN, MOVE_SLASH, MOVE_STUN_SPORE, MOVE_GROWTH},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SamHothouseSun[] = {
    {
        .iv = 100,
        .lvl = 28,
        .species = SPECIES_WEEPINBELL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_SLEEP_POWDER, MOVE_GROWTH},
    },
    {
        .iv = 100,
        .lvl = 29,
        .species = SPECIES_IVYSAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_LEECH_SEED, MOVE_SLEEP_POWDER, MOVE_TAKE_DOWN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SamHothouseClimate[] = {
    {
        .iv = 100,
        .lvl = 29,
        .species = SPECIES_GLOOM,
        .moves = {MOVE_MEGA_DRAIN, MOVE_ACID, MOVE_STUN_SPORE, MOVE_MOONLIGHT},
    },
    {
        .iv = 100,
        .lvl = 29,
        .species = SPECIES_TANGELA,
        .moves = {MOVE_MEGA_DRAIN, MOVE_BIND, MOVE_SLEEP_POWDER, MOVE_GROWTH},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SamHothouseSoil[] = {
    {
        .iv = 100,
        .lvl = 28,
        .species = SPECIES_BULBASAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_LEECH_SEED, MOVE_POISON_POWDER, MOVE_TAKE_DOWN},
    },
    {
        .iv = 100,
        .lvl = 30,
        .species = SPECIES_LEAFEON,
        .moves = {MOVE_RAZOR_LEAF, MOVE_BITE, MOVE_QUICK_ATTACK, MOVE_SYNTHESIS},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SamHothouseHawthorne[] = {
    {
        .iv = 100,
        .lvl = 30,
        .species = SPECIES_BELLOSSOM,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_MAGICAL_LEAF, MOVE_SLEEP_POWDER, MOVE_STUN_SPORE, MOVE_MOONLIGHT},
    },
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_VICTREEBEL,
        .heldItem = ITEM_MIRACLE_SEED,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SLUDGE_BOMB, MOVE_SLEEP_POWDER, MOVE_GROWTH},
    },
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_EXEGGUTOR,
        .heldItem = ITEM_TWISTED_SPOON,
        .moves = {MOVE_PSYCHIC, MOVE_LEECH_SEED, MOVE_REFLECT, MOVE_STUN_SPORE},
    },
    {
        .iv = 100,
        .lvl = 32,
        .species = SPECIES_VENUSAUR,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_LEECH_SEED, MOVE_SYNTHESIS},
    },
};
