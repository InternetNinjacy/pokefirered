// Pokémon: Sam Edition — Five Island locked ordinary-trainer package.
#define SAM5_DEF(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }

static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Alize[] = {
    SAM5_DEF(47, PIKACHU), SAM5_DEF(47, CLEFAIRY), SAM5_DEF(48, VAPOREON),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Rayna[] = {
    SAM5_DEF(49, DITTO), SAM5_DEF(49, PORYGON),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Jacki[] = {
    SAM5_DEF(48, PERSIAN), SAM5_DEF(48, CLEFABLE), SAM5_DEF(50, NINETALES),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Celina[] = {
    SAM5_DEF(49, BUTTERFREE), SAM5_DEF(49, VENOMOTH), SAM5_DEF(50, DITTO),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Gillian[] = {
    SAM5_DEF(48, RAICHU), SAM5_DEF(48, PERSIAN), SAM5_DEF(50, PORYGON2),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Destin[] = {
    SAM5_DEF(48, RATICATE), SAM5_DEF(49, PIDGEOT),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Daisy[] = {
    SAM5_DEF(50, DITTO), SAM5_DEF(50, PORYGON),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Lawson[] = {
    SAM5_DEF(48, ONIX), SAM5_DEF(48, GRAVELER), SAM5_DEF(49, MAROWAK),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Laura[] = {
    SAM5_DEF(48, NATU), SAM5_DEF(48, NATU), SAM5_DEF(50, XATU),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Selphy[] = {
    SAM5_DEF(49, PERSIAN), SAM5_DEF(49, PERSIAN),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Milo[] = {
    SAM5_DEF(49, PIDGEOT), SAM5_DEF(49, FARFETCHD),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Chaz[] = {
    SAM5_DEF(48, FEAROW), SAM5_DEF(48, DODRIO), SAM5_DEF(50, CROBAT),
};
static const struct TrainerMonNoItemDefaultMoves sParty_Sam5Harold[] = {
    SAM5_DEF(49, XATU), SAM5_DEF(50, PIDGEOT),
};

#undef SAM5_DEF
