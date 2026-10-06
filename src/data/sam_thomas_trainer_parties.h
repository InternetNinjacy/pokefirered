#ifndef GUARD_DATA_SAM_THOMAS_TRAINER_PARTIES_H
#define GUARD_DATA_SAM_THOMAS_TRAINER_PARTIES_H

// Pokémon: Sam Edition — THOMAS six-battle Team Rocket rival package.
//
// Current Thomas authority retains the closed six-battle progression:
// Nugget Bridge -> Celadon Hideout -> Pokemon Tower -> Silph Co. ->
// Cinnabar Mansion -> Viridian Gym before Giovanni.
//
// This header stages the exact battle-facing party data only. It is intentionally
// separate from map hookups and the already-merged Thomas state/dialogue router.
// Persistent Nature/Ability/friendship handling is not encoded here because the
// stock TrainerMon records do not own those fields; that integration remains a
// separate Thomas battle-construction delta.

// The TrainerMon iv byte scales to the ordinary trainer IV range. These values
// preserve the intended relative tiers for Thomas's permanent partners while the
// persistent-trait hook remains separate.
#define THOMAS_IV_TIER_22 181
#define THOMAS_IV_TIER_24 198
#define THOMAS_IV_TIER_31 255

static const struct TrainerMonNoItemCustomMoves sParty_ThomasNugget[] = {
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 18,
        .species = SPECIES_HORSEA,
        .moves = {MOVE_BUBBLE, MOVE_DRAGON_BREATH, MOVE_SMOKESCREEN, MOVE_LEER},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 19,
        .species = SPECIES_MACHOP,
        .moves = {MOVE_KARATE_CHOP, MOVE_SEISMIC_TOSS, MOVE_FOCUS_ENERGY, MOVE_LOW_KICK},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ThomasCeladon[] = {
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 26,
        .species = SPECIES_HORSEA,
        .moves = {MOVE_WATER_PULSE, MOVE_DRAGON_BREATH, MOVE_SMOKESCREEN, MOVE_LEER},
    },
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 27,
        .species = SPECIES_HOUNDOOM,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_SMOG, MOVE_ROAR},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 28,
        .species = SPECIES_MACHOKE,
        .moves = {MOVE_KARATE_CHOP, MOVE_REVENGE, MOVE_ROCK_TOMB, MOVE_SEISMIC_TOSS},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ThomasPokemonTower[] = {
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 29,
        .species = SPECIES_BALTOY,
        .moves = {MOVE_PSYBEAM, MOVE_ANCIENT_POWER, MOVE_ROCK_TOMB, MOVE_MUD_SLAP},
    },
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 30,
        .species = SPECIES_HOUNDOOM,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_SMOG, MOVE_ROAR},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 31,
        .species = SPECIES_MACHOKE,
        .moves = {MOVE_REVENGE, MOVE_KARATE_CHOP, MOVE_ROCK_TOMB, MOVE_SEISMIC_TOSS},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 32,
        .species = SPECIES_SEADRA,
        .moves = {MOVE_WATER_PULSE, MOVE_DRAGON_BREATH, MOVE_TWISTER, MOVE_SMOKESCREEN},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ThomasSilph[] = {
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 39,
        .species = SPECIES_MAGNETON,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_METAL_SOUND, MOVE_SWIFT},
    },
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 38,
        .species = SPECIES_CLAYDOL,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_EARTHQUAKE, MOVE_ANCIENT_POWER, MOVE_REFLECT},
    },
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 38,
        .species = SPECIES_HOUNDOOM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_FLAMETHROWER, MOVE_BITE, MOVE_SLUDGE_BOMB, MOVE_TORMENT},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 37,
        .species = SPECIES_SEADRA,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_SMOKESCREEN},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 40,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE, MOVE_REVENGE, MOVE_BULK_UP},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ThomasCinnabar[] = {
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 43,
        .species = SPECIES_CLAYDOL,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_COSMIC_POWER},
    },
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 44,
        .species = SPECIES_HOUNDOOM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_FLAMETHROWER, MOVE_FAINT_ATTACK, MOVE_SLUDGE_BOMB, MOVE_TORMENT},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 44,
        .species = SPECIES_MAGNETON,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE, MOVE_TRI_ATTACK, MOVE_METAL_SOUND},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 45,
        .species = SPECIES_SEADRA,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_AGILITY},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 46,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_CROSS_CHOP, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_BULK_UP},
    },
    {
        .iv = THOMAS_IV_TIER_31,
        .lvl = 47,
        .species = SPECIES_SALAMENCE,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE, MOVE_FRUSTRATION},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ThomasViridian[] = {
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 48,
        .species = SPECIES_CLAYDOL,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_PSYCHIC, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_COSMIC_POWER},
    },
    {
        .iv = THOMAS_IV_TIER_22,
        .lvl = 49,
        .species = SPECIES_HOUNDOOM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_FLAMETHROWER, MOVE_FAINT_ATTACK, MOVE_SLUDGE_BOMB, MOVE_TORMENT},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 49,
        .species = SPECIES_MAGNETON,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE, MOVE_REFLECT, MOVE_METAL_SOUND},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 50,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_CROSS_CHOP, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_BULK_UP},
    },
    {
        .iv = THOMAS_IV_TIER_31,
        .lvl = 51,
        .species = SPECIES_SALAMENCE,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE, MOVE_FRUSTRATION},
    },
    {
        .iv = THOMAS_IV_TIER_24,
        .lvl = 52,
        .species = SPECIES_KINGDRA,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_REST},
    },
};

#undef THOMAS_IV_TIER_22
#undef THOMAS_IV_TIER_24
#undef THOMAS_IV_TIER_31

#endif // GUARD_DATA_SAM_THOMAS_TRAINER_PARTIES_H
