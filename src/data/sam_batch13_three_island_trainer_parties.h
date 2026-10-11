// Pokémon: Sam Edition — ST-IMP-13 Three Island / Bond Bridge ordinary trainers.
#define SAM13_DEF(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }
#define SAM13_MOV(level, mon, m1, m2, m3, m4) { .iv = 0, .lvl = (level), .species = SPECIES_##mon, .moves = { MOVE_##m1, MOVE_##m2, MOVE_##m3, MOVE_##m4 } }

// Three Island biker story sequence.
static const struct TrainerMonNoItemDefaultMoves sParty_SamB13BikerGoon1[] = {
    SAM13_DEF(38, KOFFING), SAM13_DEF(38, GRIMER), SAM13_DEF(39, RATICATE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB13BikerGoon2[] = {
    SAM13_DEF(38, ARBOK), SAM13_DEF(39, GOLBAT),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB13BikerGoon3[] = {
    SAM13_MOV(39, KOFFING, SLUDGE_BOMB, SMOKESCREEN, HAZE, SELF_DESTRUCT),
    SAM13_MOV(39, GRIMER, SLUDGE_BOMB, DISABLE, MINIMIZE, ACID_ARMOR),
    SAM13_MOV(40, GOLBAT, WING_ATTACK, BITE, CONFUSE_RAY, SCREECH),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB13Paxton[] = {
    SAM13_MOV(40, WEEZING, SLUDGE_BOMB, SMOKESCREEN, HAZE, SELF_DESTRUCT),
    SAM13_MOV(40, MUK, SLUDGE_BOMB, ACID_ARMOR, DISABLE, MINIMIZE),
    SAM13_MOV(41, PRIMEAPE, BRICK_BREAK, ROCK_SLIDE, SCREECH, FURY_SWIPES),
};

// Bond Bridge.
static const struct TrainerMonNoItemDefaultMoves sParty_SamB13Nikki[] = {
    SAM13_DEF(38, VICTREEBEL), SAM13_DEF(39, BELLOSSOM),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB13Violet[] = {
    SAM13_DEF(38, VENUSAUR), SAM13_DEF(38, CLEFABLE), SAM13_DEF(39, TANGELA),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB13Amira[] = {
    SAM13_MOV(38, POLIWHIRL, SURF, HYPNOSIS, BODY_SLAM, RAIN_DANCE),
    SAM13_MOV(39, POLITOED, SURF, PSYCHIC, HYPNOSIS, BODY_SLAM),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB13Alexis[] = {
    SAM13_DEF(38, STARYU), SAM13_DEF(38, KRABBY), SAM13_DEF(39, STARMIE), SAM13_DEF(39, KINGLER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB13Tisha[] = {
    SAM13_DEF(40, KINGLER), SAM13_DEF(40, DEWGONG),
};
static const struct TrainerMonNoItemCustomMoves sParty_SamB13JoyMeg[] = {
    SAM13_MOV(40, CLEFABLE, BODY_SLAM, SING, ENCORE, WATER_PULSE),
    SAM13_MOV(40, WIGGLYTUFF, BODY_SLAM, SING, DISABLE, BRICK_BREAK),
};

#undef SAM13_MOV
#undef SAM13_DEF
