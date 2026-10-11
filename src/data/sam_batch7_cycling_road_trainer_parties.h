// Pokémon: Sam Edition — ST-IMP-07 Routes 16-18 / Cycling Road.
// Locked roster/format package from Standard Trainer Decision Record v1.0.
// Ordinary trainers carry no held items. Custom-move arrays encode locked move sets;
// otherwise current level-up/default moves are used.

#define SAM7_DEF(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }
#define SAM7_MOV(level, mon, m1, m2, m3, m4) { .iv = 0, .lvl = (level), .species = SPECIES_##mon, .moves = { MOVE_##m1, MOVE_##m2, MOVE_##m3, MOVE_##m4 } }

// Route 16 — 6 encounters.
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7BikerLao[] = {
    SAM7_DEF(30, RATICATE), SAM7_DEF(30, ARBOK), SAM7_DEF(30, KOFFING),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7CueBallKoji[] = {
    SAM7_MOV(30, MACHOKE, KARATE_CHOP, SEISMIC_TOSS, ROCK_TOMB, FOCUS_ENERGY),
    SAM7_MOV(30, PRIMEAPE, BRICK_BREAK, FURY_SWIPES, SCREECH, FOCUS_ENERGY),
    SAM7_MOV(31, HITMONLEE, BRICK_BREAK, ROLLING_KICK, MEDITATE, FOCUS_ENERGY),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7CueBallLuke[] = {
    SAM7_MOV(31, HITMONCHAN, MACH_PUNCH, BRICK_BREAK, THUNDER_PUNCH, AGILITY),
    SAM7_MOV(31, MACHOKE, KARATE_CHOP, ROCK_TOMB, SEISMIC_TOSS, FOCUS_ENERGY),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BikerRuben[] = {
    SAM7_MOV(30, GOLBAT, WING_ATTACK, BITE, CONFUSE_RAY, SCREECH),
    SAM7_MOV(30, WEEZING, SLUDGE_BOMB, SMOKESCREEN, HAZE, SELF_DESTRUCT),
    SAM7_MOV(31, MUK, DISABLE, SLUDGE, MINIMIZE, SCREECH),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7CueBallCamron[] = {
    SAM7_DEF(32, HITMONTOP), SAM7_DEF(32, PRIMEAPE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BikerHideo[] = {
    SAM7_MOV(33, WEEZING, SLUDGE_BOMB, SMOKESCREEN, HAZE, SELF_DESTRUCT),
};

// Route 17 — 10 encounters.
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BikerVirgil[] = {
    SAM7_MOV(31, ARBOK, SLUDGE_BOMB, GLARE, BITE, SCREECH),
    SAM7_MOV(31, MUK, SLUDGE_BOMB, DISABLE, ACID_ARMOR, MINIMIZE),
    SAM7_MOV(32, RATICATE, HYPER_FANG, QUICK_ATTACK, PURSUIT, SCARY_FACE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7CueBallIsaiah[] = {
    SAM7_DEF(32, MACHOKE), SAM7_DEF(32, HITMONLEE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7CueBallRaul[] = {
    SAM7_MOV(31, PRIMEAPE, BRICK_BREAK, KARATE_CHOP, SCREECH, FURY_SWIPES),
    SAM7_MOV(31, HITMONCHAN, MACH_PUNCH, THUNDER_PUNCH, ICE_PUNCH, AGILITY),
    SAM7_MOV(32, MACHOKE, KARATE_CHOP, ROCK_TOMB, SEISMIC_TOSS, FOCUS_ENERGY),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BikerNikolas[] = {
    SAM7_MOV(33, MUK, SLUDGE_BOMB, ACID_ARMOR, MINIMIZE, DISABLE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BikerBilly[] = {
    SAM7_MOV(31, ELECTRODE, THUNDER_WAVE, LIGHT_SCREEN, SCREECH, SHOCK_WAVE),
    SAM7_MOV(31, WEEZING, SLUDGE_BOMB, SMOKESCREEN, HAZE, SELF_DESTRUCT),
    SAM7_MOV(32, GOLBAT, SUPERSONIC, BITE, WING_ATTACK, CONFUSE_RAY),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7CueBallJamal[] = {
    SAM7_DEF(33, MACHOKE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7CueBallZeek[] = {
    SAM7_DEF(31, MACHOKE), SAM7_DEF(31, PRIMEAPE), SAM7_DEF(32, HITMONLEE), SAM7_DEF(32, HITMONCHAN),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7CueBallCorey[] = {
    SAM7_DEF(33, HITMONTOP), SAM7_DEF(33, PRIMEAPE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB7BikerWilliam[] = {
    SAM7_DEF(32, RATICATE), SAM7_DEF(32, ARBOK), SAM7_DEF(33, MUK),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BikerJaxon[] = {
    SAM7_MOV(33, CROBAT, WING_ATTACK, BITE, CONFUSE_RAY, SCREECH),
    SAM7_MOV(32, WEEZING, SLUDGE_BOMB, SMOKESCREEN, HAZE, SELF_DESTRUCT),
    SAM7_MOV(32, MUK, DISABLE, SLUDGE, MINIMIZE, SCREECH),
    SAM7_MOV(32, ARBOK, POISON_STING, BITE, GLARE, SCREECH),
};

// Route 18 — 3 encounters.
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BirdKeeperJacob[] = {
    SAM7_MOV(31, FEAROW, GROWL, LEER, FURY_ATTACK, PURSUIT),
    SAM7_MOV(31, FARFETCHD, FURY_ATTACK, KNOCK_OFF, FURY_CUTTER, SWORDS_DANCE),
    SAM7_MOV(32, DODRIO, GROWL, PURSUIT, FURY_ATTACK, TRI_ATTACK),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BirdKeeperRamiro[] = {
    SAM7_MOV(32, XATU, PSYCHIC, CONFUSE_RAY, NIGHT_SHADE, REFLECT),
    SAM7_MOV(31, PIDGEOTTO, WING_ATTACK, SAND_ATTACK, QUICK_ATTACK, WHIRLWIND),
    SAM7_MOV(32, FEAROW, LEER, FURY_ATTACK, PURSUIT, MIRROR_MOVE),
    SAM7_MOV(32, FARFETCHD, FURY_ATTACK, KNOCK_OFF, FURY_CUTTER, SWORDS_DANCE),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB7BirdKeeperWilton[] = {
    SAM7_MOV(34, DODRIO, AERIAL_ACE, TRI_ATTACK, PURSUIT, AGILITY),
};

#undef SAM7_MOV
#undef SAM7_DEF
