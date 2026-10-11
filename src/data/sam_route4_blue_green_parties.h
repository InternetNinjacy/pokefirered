// Pokémon: Sam Edition — shared Route 4 Blue + Green Double Battle.
// Authority: Blue/Green specialist records; exactly two Pokémon per rival.
// Party order alternates Blue lead / Green lead / Blue reserve / Green reserve.

static const struct TrainerMonNoItemCustomMoves sParty_SamRoute4BlueGreenWater[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 255, .lvl = 16, .species = SPECIES_PIKACHU, .moves = {MOVE_THUNDER_SHOCK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_TAIL_WHIP}},
    {.iv = 70, .lvl = 14, .species = SPECIES_CHINCHOU, .moves = {MOVE_WATER_GUN, MOVE_THUNDER_SHOCK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC}},
    {.iv = 255, .lvl = 14, .species = SPECIES_BULBASAUR, .moves = {MOVE_VINE_WHIP, MOVE_LEECH_SEED, MOVE_TACKLE, MOVE_GROWL}},
};

static const struct TrainerMonNoItemCustomMoves sParty_SamRoute4BlueGreenElectric[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_PIKACHU, .moves = {MOVE_THUNDERBOLT, MOVE_QUICK_ATTACK, MOVE_BRICK_BREAK, MOVE_THUNDER_WAVE}},
    {.iv = 255, .lvl = 16, .species = SPECIES_EEVEE, .moves = {MOVE_TACKLE, MOVE_HELPING_HAND, MOVE_SAND_ATTACK, MOVE_GROWL}},
    {.iv = 70, .lvl = 14, .species = SPECIES_VOLTORB, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SONIC_BOOM, MOVE_ROLLOUT}},
    {.iv = 255, .lvl = 15, .species = SPECIES_MAGIKARP, .moves = {MOVE_TACKLE, MOVE_SPLASH, MOVE_NONE, MOVE_NONE}},
};

static const struct TrainerMonNoItemCustomMoves sParty_SamRoute4BlueGreenFire[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_FLAREON, .moves = {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_SAND_ATTACK, MOVE_HELPING_HAND}},
    {.iv = 255, .lvl = 16, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_NONE, MOVE_NONE}},
    {.iv = 70, .lvl = 14, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_GROWL}},
    {.iv = 255, .lvl = 14, .species = SPECIES_GROWLITHE, .moves = {MOVE_EMBER, MOVE_BITE, MOVE_LEER, MOVE_ROAR}},
};
