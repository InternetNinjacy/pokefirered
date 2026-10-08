#ifndef GUARD_DATA_SAM_SATOSHI_TRAINER_PARTIES_H
#define GUARD_DATA_SAM_SATOSHI_TRAINER_PARTIES_H

// Pokémon: Sam Edition — reusable Satoshi-owned trainer data.
//
// Gym 6 (Saffron) remains owned by its completed production integration.
// Gym 8 (Viridian) is included here after live reconciliation found its historical
// production integration absent from sam-edition-dev ancestry.
// This file carries reusable practice/rematch party records.

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiPewterPractice[] = {
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_SEEL,
        .moves = {MOVE_HEADBUTT, MOVE_GROWL, MOVE_NONE, MOVE_NONE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SatoshiPewterRematch[] = {
    {
        .iv = 200,
        .lvl = 55,
        .species = SPECIES_GOLDUCK,
        .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_PSYCHIC, MOVE_CALM_MIND},
    },
    {
        .iv = 200,
        .lvl = 56,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
        .moves = {MOVE_BRICK_BREAK, MOVE_ICE_PUNCH, MOVE_THUNDER_PUNCH, MOVE_MACH_PUNCH},
    },
    {
        .iv = 200,
        .lvl = 57,
        .species = SPECIES_KANGASKHAN,
        .heldItem = ITEM_SILK_SCARF,
        .moves = {MOVE_BODY_SLAM, MOVE_ICE_PUNCH, MOVE_EARTHQUAKE, MOVE_BRICK_BREAK},
    },
    {
        .iv = 200,
        .lvl = 58,
        .species = SPECIES_CHANSEY,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_SOFT_BOILED, MOVE_THUNDER_WAVE, MOVE_SEISMIC_TOSS},
    },
    {
        .iv = 200,
        .lvl = 59,
        .species = SPECIES_RHYDON,
        .heldItem = ITEM_HARD_STONE,
        .moves = {MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_MEGAHORN, MOVE_BRICK_BREAK},
    },
    {
        .iv = 200,
        .lvl = 60,
        .species = SPECIES_DEWGONG,
        .heldItem = ITEM_SHELL_BELL,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_BODY_SLAM, MOVE_ENCORE},
    },
};

// Current Cerulean exception recovered from merged PR #164 authority.
// Do not regress this package to the older Charmander / Salamence draft.
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

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiVermilionPractice[] = {
    {
        .iv = 50,
        .lvl = 19,
        .species = SPECIES_POLIWAG,
        .moves = {MOVE_BUBBLE, MOVE_HYPNOSIS, MOVE_DOUBLE_SLAP, MOVE_RAIN_DANCE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SatoshiVermilionRematch[] = {
    {
        .iv = 200,
        .lvl = 58,
        .species = SPECIES_TENTACRUEL,
        .heldItem = ITEM_POISON_BARB,
        .moves = {MOVE_SURF, MOVE_SLUDGE_BOMB, MOVE_GIGA_DRAIN, MOVE_TOXIC},
    },
    {
        .iv = 200,
        .lvl = 58,
        .species = SPECIES_KINGLER,
        .heldItem = ITEM_SCOPE_LENS,
        .moves = {MOVE_CRABHAMMER, MOVE_BRICK_BREAK, MOVE_MUD_SHOT, MOVE_PROTECT},
    },
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
        .species = SPECIES_NIDOQUEEN,
        .heldItem = ITEM_SOFT_SAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_SLUDGE_BOMB, MOVE_ICE_BEAM, MOVE_THUNDERBOLT},
    },
    {
        .iv = 200,
        .lvl = 61,
        .species = SPECIES_BLASTOISE,
        .heldItem = ITEM_SHELL_BELL,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_BITE, MOVE_PROTECT},
    },
    {
        .iv = 200,
        .lvl = 62,
        .species = SPECIES_POLIWRATH,
        .heldItem = ITEM_BLACK_BELT,
        .moves = {MOVE_SURF, MOVE_BRICK_BREAK, MOVE_ICE_BEAM, MOVE_HYPNOSIS},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiCeladonPractice[] = {
    {
        .iv = 50,
        .lvl = 25,
        .species = SPECIES_BUTTERFREE,
        .moves = {MOVE_CONFUSION, MOVE_STUN_SPORE, MOVE_SLEEP_POWDER, MOVE_SUPERSONIC},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SatoshiCeladonRematch[] = {
    {
        .iv = 200,
        .lvl = 56,
        .species = SPECIES_VILEPLUME,
        .heldItem = ITEM_MIRACLE_SEED,
        .moves = {MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_TOXIC, MOVE_MOONLIGHT},
    },
    {
        .iv = 200,
        .lvl = 57,
        .species = SPECIES_SANDSLASH,
        .heldItem = ITEM_SOFT_SAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_BRICK_BREAK, MOVE_SWORDS_DANCE},
    },
    {
        .iv = 200,
        .lvl = 58,
        .species = SPECIES_JOLTEON,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_BITE, MOVE_THUNDER_WAVE, MOVE_DOUBLE_KICK},
    },
    {
        .iv = 200,
        .lvl = 59,
        .species = SPECIES_AERODACTYL,
        .heldItem = ITEM_HARD_STONE,
        .moves = {MOVE_ROCK_SLIDE, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE, MOVE_DOUBLE_EDGE},
    },
    {
        .iv = 200,
        .lvl = 60,
        .species = SPECIES_SCIZOR,
        .heldItem = ITEM_METAL_COAT,
        .moves = {MOVE_FURY_CUTTER, MOVE_STEEL_WING, MOVE_BRICK_BREAK, MOVE_SWORDS_DANCE},
    },
    {
        .iv = 200,
        .lvl = 61,
        .species = SPECIES_BUTTERFREE,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_SIGNAL_BEAM, MOVE_PSYCHIC, MOVE_SLEEP_POWDER, MOVE_DREAM_EATER},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiFuchsiaPractice[] = {
    {
        .iv = 50,
        .lvl = 30,
        .species = SPECIES_RATICATE,
        .moves = {MOVE_HYPER_FANG, MOVE_QUICK_ATTACK, MOVE_FOCUS_ENERGY, MOVE_SCARY_FACE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_SatoshiFuchsiaRematch[] = {
    {
        .iv = 200,
        .lvl = 57,
        .species = SPECIES_WIGGLYTUFF,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_BODY_SLAM, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_FLAMETHROWER},
    },
    {
        .iv = 200,
        .lvl = 58,
        .species = SPECIES_WEEZING,
        .heldItem = ITEM_POISON_BARB,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_WILL_O_WISP, MOVE_THUNDERBOLT, MOVE_HAZE},
    },
    {
        .iv = 200,
        .lvl = 59,
        .species = SPECIES_PIDGEOT,
        .heldItem = ITEM_SHARP_BEAK,
        .moves = {MOVE_RETURN, MOVE_AERIAL_ACE, MOVE_STEEL_WING, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 200,
        .lvl = 60,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_TWISTED_SPOON,
        .moves = {MOVE_PSYCHIC, MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH, MOVE_RECOVER},
    },
    {
        .iv = 200,
        .lvl = 61,
        .species = SPECIES_LICKITUNG,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_BODY_SLAM, MOVE_SHADOW_BALL, MOVE_BRICK_BREAK, MOVE_REST},
    },
    {
        .iv = 200,
        .lvl = 62,
        .species = SPECIES_RATICATE,
        .heldItem = ITEM_SILK_SCARF,
        .moves = {MOVE_FACADE, MOVE_SHADOW_BALL, MOVE_BRICK_BREAK, MOVE_QUICK_ATTACK},
    },
};

// Recovered from the completed Cinnabar production package. The rematch
// deliberately has no held items or trainer healing; do not normalize it to
// the other Satoshi rematches.
static const struct TrainerMonNoItemCustomMoves sParty_SatoshiCinnabarPractice[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_ROCK_SLIDE, MOVE_DIG, MOVE_SCARY_FACE, MOVE_TAKE_DOWN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SatoshiCinnabarRematch[] = {
    {
        .iv = 0,
        .lvl = 55,
        .species = SPECIES_NOSEPASS,
        .moves = {MOVE_ROCK_SLIDE, MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE, MOVE_SANDSTORM},
    },
    {
        .iv = 0,
        .lvl = 55,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_BRICK_BREAK, MOVE_EXPLOSION},
    },
    {
        .iv = 0,
        .lvl = 56,
        .species = SPECIES_KABUTO,
        .moves = {MOVE_ROCK_SLIDE, MOVE_SURF, MOVE_GIGA_DRAIN, MOVE_PROTECT},
    },
    {
        .iv = 0,
        .lvl = 56,
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_THUNDERBOLT, MOVE_TRI_ATTACK, MOVE_THUNDER_WAVE, MOVE_REFLECT},
    },
    {
        .iv = 0,
        .lvl = 57,
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_PSYCHIC, MOVE_GIGA_DRAIN, MOVE_SLEEP_POWDER, MOVE_LEECH_SEED},
    },
    {
        .iv = 0,
        .lvl = 59,
        .species = SPECIES_RHYPERIOR,
        .moves = {MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_MEGAHORN, MOVE_BRICK_BREAK},
    },
};


static const struct TrainerMonNoItemCustomMoves sParty_SatoshiViridianPractice[] = {
    {
        .iv = 50,
        .lvl = 37,
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

#endif // GUARD_DATA_SAM_SATOSHI_TRAINER_PARTIES_H
