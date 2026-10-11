// Pokémon: Sam Edition — ST-IMP-12 One Island first-visit ordinary trainers.
#define SAM12_DEF(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }
#define SAM12_MOV(level, mon, m1, m2, m3, m4) { .iv = 0, .lvl = (level), .species = SPECIES_##mon, .moves = { MOVE_##m1, MOVE_##m2, MOVE_##m3, MOVE_##m4 } }

static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Amara[] = {
    SAM12_DEF(36, SEEL), SAM12_DEF(38, DEWGONG),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Abigail[] = {
    SAM12_DEF(36, PSYDUCK), SAM12_DEF(38, GOLDUCK), SAM12_DEF(38, STARMIE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB12Claire[] = {
    SAM12_MOV(36, PERSIAN, FAKE_OUT, SLASH, BITE, SCREECH),
    SAM12_MOV(36, CLEFABLE, BODY_SLAM, SING, ENCORE, WATER_PULSE),
    SAM12_MOV(38, RAICHU, THUNDERBOLT, BRICK_BREAK, THUNDER_WAVE, QUICK_ATTACK),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Tanya[] = {
    SAM12_DEF(39, HITMONLEE), SAM12_DEF(39, HITMONCHAN),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Bryce[] = {
    SAM12_DEF(37, NIDORINO), SAM12_DEF(37, SANDSLASH), SAM12_DEF(38, RATICATE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Garrett[] = {
    SAM12_DEF(38, CLOYSTER), SAM12_DEF(39, BLASTOISE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB12MikKia[] = {
    SAM12_MOV(39, MACHOKE, BRICK_BREAK, ROCK_TOMB, SEISMIC_TOSS, FOCUS_ENERGY),
    SAM12_MOV(39, PRIMEAPE, BRICK_BREAK, SCREECH, ROCK_SLIDE, FURY_SWIPES),
    SAM12_MOV(40, HITMONTOP, MACH_PUNCH, TRIPLE_KICK, QUICK_ATTACK, AGILITY),
    SAM12_MOV(40, MACHAMP, CROSS_CHOP, ROCK_SLIDE, BULK_UP, SEISMIC_TOSS),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Hugh[] = {
    SAM12_DEF(39, PRIMEAPE), SAM12_DEF(40, MACHOKE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Shea[] = {
    SAM12_DEF(39, MACHOKE), SAM12_DEF(39, HITMONLEE), SAM12_DEF(40, HITMONCHAN),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Sharon[] = {
    SAM12_DEF(40, PRIMEAPE), SAM12_DEF(40, HITMONTOP),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB12Finn[] = {
    SAM12_MOV(40, STARMIE, SURF, PSYCHIC, RECOVER, THUNDER_WAVE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Maria[] = {
    SAM12_DEF(38, SEADRA), SAM12_DEF(38, TENTACRUEL), SAM12_DEF(39, KINGLER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Tommy[] = {
    SAM12_DEF(38, SEAKING), SAM12_DEF(39, KINGLER), SAM12_DEF(40, GYARADOS),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Beth[] = {
    SAM12_DEF(39, VICTREEBEL), SAM12_DEF(40, VILEPLUME), SAM12_DEF(40, BELLOSSOM),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB12Jocelyn[] = {
    SAM12_DEF(40, HITMONCHAN), SAM12_DEF(40, HITMONLEE), SAM12_DEF(41, PRIMEAPE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB12Logan[] = {
    SAM12_MOV(42, EXEGGUTOR, PSYCHIC, GIGA_DRAIN, SLEEP_POWDER, REFLECT),
    SAM12_MOV(42, ARCANINE, FLAMETHROWER, BITE, EXTREME_SPEED, ROAR),
};

#undef SAM12_MOV
#undef SAM12_DEF
