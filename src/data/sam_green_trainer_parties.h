// Pokémon: Sam Edition — Green rival specialist parties.
// Locked by Green Decision Record v1.0. Route 4 remains owned by the already-merged shared battle package.

static const struct TrainerMonNoItemCustomMoves sParty_Green_OAK_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 5,
        .species = SPECIES_DITTO,
        .moves = {MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_Green_OAK_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 5,
        .species = SPECIES_EEVEE,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_HELPING_HAND, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_Green_OAK_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 5,
        .species = SPECIES_PICHU,
        .moves = {MOVE_THUNDER_SHOCK, MOVE_CHARM, MOVE_NONE, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_Green_SS_ANNE_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 21,
        .species = SPECIES_DITTO,
        .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_PROTECT, MOVE_NONE},
    },
    {
        .iv = 255,
        .lvl = 20,
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_ROAR, MOVE_LEER},
    },
    {
        .iv = 255,
        .lvl = 19,
        .species = SPECIES_NIDORINO,
        .moves = {MOVE_DOUBLE_KICK, MOVE_PECK, MOVE_FOCUS_ENERGY, MOVE_LEER},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_Green_SS_ANNE_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 21,
        .species = SPECIES_ESPEON,
        .moves = {MOVE_CONFUSION, MOVE_HELPING_HAND, MOVE_SAND_ATTACK, MOVE_TACKLE},
    },
    {
        .iv = 255,
        .lvl = 20,
        .species = SPECIES_GYARADOS,
        .moves = {MOVE_WATER_PULSE, MOVE_BITE, MOVE_TACKLE, MOVE_SPLASH},
    },
    {
        .iv = 255,
        .lvl = 19,
        .species = SPECIES_ZUBAT,
        .moves = {MOVE_BITE, MOVE_SUPERSONIC, MOVE_ASTONISH, MOVE_LEECH_LIFE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_Green_SS_ANNE_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 21,
        .species = SPECIES_PIKACHU,
        .moves = {MOVE_THUNDER_SHOCK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_SLAM},
    },
    {
        .iv = 255,
        .lvl = 20,
        .species = SPECIES_IVYSAUR,
        .moves = {MOVE_VINE_WHIP, MOVE_SLEEP_POWDER, MOVE_LEECH_SEED, MOVE_TACKLE},
    },
    {
        .iv = 255,
        .lvl = 19,
        .species = SPECIES_MACHOP,
        .moves = {MOVE_KARATE_CHOP, MOVE_SEISMIC_TOSS, MOVE_FOCUS_ENERGY, MOVE_LEER},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_CELADON_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 28,
        .species = SPECIES_DITTO,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_PROTECT, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 27,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_BITE, MOVE_DIG, MOVE_ROAR},
    },
    {
        .iv = 255,
        .lvl = 26,
        .species = SPECIES_NIDOKING,
        .heldItem = ITEM_SOFT_SAND,
        .moves = {MOVE_DIG, MOVE_DOUBLE_KICK, MOVE_ROCK_TOMB, MOVE_FOCUS_ENERGY},
    },
    {
        .iv = 255,
        .lvl = 25,
        .species = SPECIES_PINSIR,
        .heldItem = ITEM_BLACK_BELT,
        .moves = {MOVE_VICE_GRIP, MOVE_BRICK_BREAK, MOVE_ROCK_TOMB, MOVE_FOCUS_ENERGY},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_CELADON_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 28,
        .species = SPECIES_ESPEON,
        .heldItem = ITEM_TWISTED_SPOON,
        .moves = {MOVE_CONFUSION, MOVE_QUICK_ATTACK, MOVE_REFLECT, MOVE_SAND_ATTACK},
    },
    {
        .iv = 255,
        .lvl = 27,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_WATER_PULSE, MOVE_BITE, MOVE_DRAGON_RAGE, MOVE_RETURN},
    },
    {
        .iv = 255,
        .lvl = 26,
        .species = SPECIES_GOLBAT,
        .heldItem = ITEM_SHARP_BEAK,
        .moves = {MOVE_WING_ATTACK, MOVE_BITE, MOVE_CONFUSE_RAY, MOVE_ASTONISH},
    },
    {
        .iv = 255,
        .lvl = 25,
        .species = SPECIES_ONIX,
        .heldItem = ITEM_QUICK_CLAW,
        .moves = {MOVE_DIG, MOVE_ROCK_TOMB, MOVE_SCREECH, MOVE_BIND},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_CELADON_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 28,
        .species = SPECIES_RAICHU,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_SLAM},
    },
    {
        .iv = 255,
        .lvl = 27,
        .species = SPECIES_IVYSAUR,
        .heldItem = ITEM_MIRACLE_SEED,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SLEEP_POWDER, MOVE_LEECH_SEED, MOVE_TAKE_DOWN},
    },
    {
        .iv = 255,
        .lvl = 26,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
        .moves = {MOVE_BRICK_BREAK, MOVE_SEISMIC_TOSS, MOVE_ROCK_TOMB, MOVE_FOCUS_ENERGY},
    },
    {
        .iv = 255,
        .lvl = 25,
        .species = SPECIES_PORYGON,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_RECOVER, MOVE_PSYBEAM, MOVE_AGILITY},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_FUCHSIA_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 35,
        .species = SPECIES_DITTO,
        .heldItem = ITEM_ADAPTIVE_GENE,
        .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_PROTECT, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 34,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_BITE, MOVE_DIG, MOVE_ROAR},
    },
    {
        .iv = 255,
        .lvl = 33,
        .species = SPECIES_NIDOKING,
        .heldItem = ITEM_SOFT_SAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_SLUDGE_BOMB, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 32,
        .species = SPECIES_PINSIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_SWORDS_DANCE, MOVE_RETURN, MOVE_BRICK_BREAK, MOVE_ROCK_TOMB},
    },
    {
        .iv = 255,
        .lvl = 31,
        .species = SPECIES_SHELLDER,
        .heldItem = ITEM_NEVER_MELT_ICE,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_PROTECT, MOVE_SUPERSONIC},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_FUCHSIA_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 35,
        .species = SPECIES_ESPEON,
        .heldItem = ITEM_TWISTED_SPOON,
        .moves = {MOVE_PSYCHIC, MOVE_REFLECT, MOVE_SWIFT, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 255,
        .lvl = 34,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_WATER_PULSE, MOVE_BITE, MOVE_RETURN, MOVE_DRAGON_RAGE},
    },
    {
        .iv = 255,
        .lvl = 33,
        .species = SPECIES_GOLBAT,
        .heldItem = ITEM_SHARP_BEAK,
        .moves = {MOVE_WING_ATTACK, MOVE_BITE, MOVE_CONFUSE_RAY, MOVE_STEEL_WING},
    },
    {
        .iv = 255,
        .lvl = 32,
        .species = SPECIES_ONIX,
        .heldItem = ITEM_QUICK_CLAW,
        .moves = {MOVE_DIG, MOVE_ROCK_SLIDE, MOVE_TOXIC, MOVE_SCREECH},
    },
    {
        .iv = 255,
        .lvl = 31,
        .species = SPECIES_SNORLAX,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_BODY_SLAM, MOVE_SHADOW_BALL, MOVE_REST, MOVE_CURSE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_FUCHSIA_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 35,
        .species = SPECIES_RAICHU,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_DIG},
    },
    {
        .iv = 255,
        .lvl = 34,
        .species = SPECIES_IVYSAUR,
        .heldItem = ITEM_MIRACLE_SEED,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SLEEP_POWDER, MOVE_LEECH_SEED, MOVE_SLUDGE_BOMB},
    },
    {
        .iv = 255,
        .lvl = 33,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
        .moves = {MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE, MOVE_SEISMIC_TOSS, MOVE_FOCUS_ENERGY},
    },
    {
        .iv = 255,
        .lvl = 32,
        .species = SPECIES_PORYGON,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_RECOVER, MOVE_PSYBEAM, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 31,
        .species = SPECIES_DRATINI,
        .heldItem = ITEM_DRAGON_FANG,
        .moves = {MOVE_DRAGON_RAGE, MOVE_THUNDER_WAVE, MOVE_SURF, MOVE_DRAGON_DANCE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_SAFFRON_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 35,
        .species = SPECIES_CLOYSTER,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_PROTECT, MOVE_SURF, MOVE_ICE_BEAM, MOVE_EXPLOSION},
    },
    {
        .iv = 255,
        .lvl = 37,
        .species = SPECIES_NIDOKING,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_SLUDGE_BOMB, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 38,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_WHITE_HERB,
        .moves = {MOVE_OVERHEAT, MOVE_RETURN, MOVE_BITE, MOVE_IRON_TAIL},
    },
    {
        .iv = 255,
        .lvl = 36,
        .species = SPECIES_PINSIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_SWORDS_DANCE, MOVE_RETURN, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 39,
        .species = SPECIES_DITTO,
        .heldItem = ITEM_ADAPTIVE_GENE,
        .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_PROTECT, MOVE_SUBSTITUTE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_SAFFRON_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 38,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_RETURN, MOVE_TAUNT},
    },
    {
        .iv = 255,
        .lvl = 36,
        .species = SPECIES_STEELIX,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_TOXIC, MOVE_EXPLOSION},
    },
    {
        .iv = 255,
        .lvl = 37,
        .species = SPECIES_CROBAT,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_AERIAL_ACE, MOVE_SHADOW_BALL, MOVE_STEEL_WING},
    },
    {
        .iv = 255,
        .lvl = 35,
        .species = SPECIES_SNORLAX,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_CURSE, MOVE_BODY_SLAM, MOVE_SHADOW_BALL, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 39,
        .species = SPECIES_ESPEON,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_PSYBEAM, MOVE_REFLECT},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_SAFFRON_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 38,
        .species = SPECIES_VENUSAUR,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_SLEEP_POWDER, MOVE_LEECH_SEED, MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB},
    },
    {
        .iv = 255,
        .lvl = 36,
        .species = SPECIES_PORYGON,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_RECOVER, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 37,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_HIDDEN_POWER},
    },
    {
        .iv = 255,
        .lvl = 35,
        .species = SPECIES_DRAGONAIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_RETURN, MOVE_SURF, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 39,
        .species = SPECIES_RAICHU,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_SUBSTITUTE, MOVE_SURF, MOVE_THUNDER_WAVE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_THREE_ISLAND_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 40,
        .species = SPECIES_CLOYSTER,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_SPIKES, MOVE_SURF, MOVE_ICE_BEAM, MOVE_EXPLOSION},
    },
    {
        .iv = 255,
        .lvl = 42,
        .species = SPECIES_NIDOKING,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_SLUDGE_BOMB, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 43,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_WHITE_HERB,
        .moves = {MOVE_OVERHEAT, MOVE_RETURN, MOVE_BITE, MOVE_IRON_TAIL},
    },
    {
        .iv = 255,
        .lvl = 41,
        .species = SPECIES_PINSIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_SWORDS_DANCE, MOVE_RETURN, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 39,
        .species = SPECIES_HAUNTER,
        .heldItem = ITEM_SPELL_TAG,
        .moves = {MOVE_THUNDERBOLT, MOVE_PSYCHIC, MOVE_GIGA_DRAIN, MOVE_DESTINY_BOND},
    },
    {
        .iv = 255,
        .lvl = 44,
        .species = SPECIES_DITTO,
        .heldItem = ITEM_ADAPTIVE_GENE,
        .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_PROTECT, MOVE_SUBSTITUTE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_THREE_ISLAND_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 43,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_RETURN, MOVE_TAUNT},
    },
    {
        .iv = 255,
        .lvl = 41,
        .species = SPECIES_STEELIX,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_TOXIC, MOVE_EXPLOSION},
    },
    {
        .iv = 255,
        .lvl = 42,
        .species = SPECIES_CROBAT,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_AERIAL_ACE, MOVE_SHADOW_BALL, MOVE_STEEL_WING},
    },
    {
        .iv = 255,
        .lvl = 40,
        .species = SPECIES_SNORLAX,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_CURSE, MOVE_BODY_SLAM, MOVE_SHADOW_BALL, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 39,
        .species = SPECIES_CHARIZARD,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_BELLY_DRUM, MOVE_FLAMETHROWER, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE},
    },
    {
        .iv = 255,
        .lvl = 44,
        .species = SPECIES_ESPEON,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_PSYBEAM, MOVE_REFLECT},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_THREE_ISLAND_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 43,
        .species = SPECIES_VENUSAUR,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_SLEEP_POWDER, MOVE_LEECH_SEED, MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB},
    },
    {
        .iv = 255,
        .lvl = 41,
        .species = SPECIES_PORYGON,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_RECOVER, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 42,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_HIDDEN_POWER},
    },
    {
        .iv = 255,
        .lvl = 39,
        .species = SPECIES_STARMIE,
        .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_RECOVER},
    },
    {
        .iv = 255,
        .lvl = 40,
        .species = SPECIES_DRAGONAIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_RETURN, MOVE_SURF, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 44,
        .species = SPECIES_RAICHU,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_SUBSTITUTE, MOVE_SURF, MOVE_THUNDER_WAVE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_VIRIDIAN_DITTO[] =
{
    {
        .iv = 255,
        .lvl = 45,
        .species = SPECIES_CLOYSTER,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_SPIKES, MOVE_SURF, MOVE_ICE_BEAM, MOVE_EXPLOSION},
    },
    {
        .iv = 255,
        .lvl = 47,
        .species = SPECIES_NIDOKING,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_EARTHQUAKE, MOVE_SLUDGE_BOMB, MOVE_MEGAHORN, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 48,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_WHITE_HERB,
        .moves = {MOVE_OVERHEAT, MOVE_RETURN, MOVE_CRUNCH, MOVE_IRON_TAIL},
    },
    {
        .iv = 255,
        .lvl = 46,
        .species = SPECIES_PINSIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_SWORDS_DANCE, MOVE_RETURN, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 44,
        .species = SPECIES_GENGAR,
        .heldItem = ITEM_SPELL_TAG,
        .moves = {MOVE_THUNDERBOLT, MOVE_PSYCHIC, MOVE_GIGA_DRAIN, MOVE_DESTINY_BOND},
    },
    {
        .iv = 255,
        .lvl = 49,
        .species = SPECIES_DITTO,
        .heldItem = ITEM_ADAPTIVE_GENE,
        .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_PROTECT, MOVE_SUBSTITUTE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_VIRIDIAN_ESPEON[] =
{
    {
        .iv = 255,
        .lvl = 48,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_RETURN, MOVE_TAUNT},
    },
    {
        .iv = 255,
        .lvl = 46,
        .species = SPECIES_STEELIX,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_TOXIC, MOVE_EXPLOSION},
    },
    {
        .iv = 255,
        .lvl = 47,
        .species = SPECIES_CROBAT,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_AERIAL_ACE, MOVE_SHADOW_BALL, MOVE_STEEL_WING},
    },
    {
        .iv = 255,
        .lvl = 45,
        .species = SPECIES_SNORLAX,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_CURSE, MOVE_BODY_SLAM, MOVE_SHADOW_BALL, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 44,
        .species = SPECIES_CHARIZARD,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_BELLY_DRUM, MOVE_FLAMETHROWER, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE},
    },
    {
        .iv = 255,
        .lvl = 49,
        .species = SPECIES_ESPEON,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_PSYBEAM, MOVE_REFLECT},
    },
};

static const struct TrainerMonItemCustomMoves sParty_Green_VIRIDIAN_RAICHU[] =
{
    {
        .iv = 255,
        .lvl = 48,
        .species = SPECIES_VENUSAUR,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_SLEEP_POWDER, MOVE_LEECH_SEED, MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB},
    },
    {
        .iv = 255,
        .lvl = 46,
        .species = SPECIES_PORYGON2,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_RECOVER, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 47,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_CHOICE_BAND,
        .moves = {MOVE_CROSS_CHOP, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_HIDDEN_POWER},
    },
    {
        .iv = 255,
        .lvl = 44,
        .species = SPECIES_STARMIE,
        .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_RECOVER},
    },
    {
        .iv = 255,
        .lvl = 45,
        .species = SPECIES_DRAGONAIR,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_RETURN, MOVE_SURF, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 49,
        .species = SPECIES_RAICHU,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_SUBSTITUTE, MOVE_SURF, MOVE_THUNDER_WAVE},
    },
};
