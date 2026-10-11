// Pokemon Sam Edition - Six Island ordinary trainer parties.
#define SAM6_DEF(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }

static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Samir[] = { SAM6_DEF(49, GOLDUCK), SAM6_DEF(50, SEADRA) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Edward[] = { SAM6_DEF(49, KINGLER), SAM6_DEF(49, STARMIE), SAM6_DEF(50, SEAKING) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Rose[] = { SAM6_DEF(50, DEWGONG), SAM6_DEF(51, VAPOREON), SAM6_DEF(51, GOLDUCK) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Denise[] = { SAM6_DEF(49, POLIWRATH), SAM6_DEF(49, SEADRA), SAM6_DEF(50, TENTACRUEL), SAM6_DEF(51, STARMIE) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Jaclyn[] = { SAM6_DEF(49, VICTREEBEL), SAM6_DEF(50, BELLOSSOM), SAM6_DEF(50, TANGELA) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Bethany[] = { SAM6_DEF(50, VENUSAUR), SAM6_DEF(49, BUTTERFREE), SAM6_DEF(50, PARASECT) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Riley[] = { SAM6_DEF(49, BEEDRILL), SAM6_DEF(50, VENOMOTH), SAM6_DEF(51, SCYTHER) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Garret[] = { SAM6_DEF(49, BUTTERFREE), SAM6_DEF(49, BEEDRILL), SAM6_DEF(50, VENOMOTH) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Jonah[] = { SAM6_DEF(50, PARASECT), SAM6_DEF(51, PINSIR) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Vance[] = { SAM6_DEF(50, SCYTHER), SAM6_DEF(50, PINSIR), SAM6_DEF(52, SCIZOR) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Tylor[] = { SAM6_DEF(50, FEAROW), SAM6_DEF(51, DODRIO), SAM6_DEF(51, CROBAT) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Mymo[] = { SAM6_DEF(50, KADABRA), SAM6_DEF(52, XATU) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Stanly[] = { SAM6_DEF(50, SANDSLASH), SAM6_DEF(51, MAROWAK), SAM6_DEF(52, RHYDON) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Foster[] = { SAM6_DEF(50, GRAVELER), SAM6_DEF(50, NOSEPASS), SAM6_DEF(51, MACHOKE), SAM6_DEF(51, ONIX) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam6Hector[] = { SAM6_DEF(51, XATU), SAM6_DEF(51, KADABRA), SAM6_DEF(52, EXEGGUTOR) };

#undef SAM6_DEF
