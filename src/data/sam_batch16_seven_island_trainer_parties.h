// Pokemon Sam Edition - Seven Island ordinary trainer parties.
#define SAM7I_DEF(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }

static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IMiah[] = { SAM7I_DEF(52, BELLOSSOM), SAM7I_DEF(52, VILEPLUME) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IMason[] = { SAM7I_DEF(50, ELECTRODE), SAM7I_DEF(50, MAGNETON), SAM7I_DEF(51, HYPNO) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7INicolas[] = { SAM7I_DEF(51, VICTREEBEL), SAM7I_DEF(52, EXEGGUTOR) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IMadeline[] = { SAM7I_DEF(51, VILEPLUME), SAM7I_DEF(52, TANGELA), SAM7I_DEF(52, CLEFABLE) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IEveJon[] = { SAM7I_DEF(51, GOLDUCK), SAM7I_DEF(51, VAPOREON), SAM7I_DEF(52, STARMIE), SAM7I_DEF(52, RAICHU) };

static const struct TrainerMonNoItemDefaultMoves sParty_Sam7ILexNya[] = { SAM7I_DEF(52, TAUROS), SAM7I_DEF(52, MILTANK) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IEvan[] = { SAM7I_DEF(51, SANDSLASH), SAM7I_DEF(51, LICKITUNG), SAM7I_DEF(52, KANGASKHAN) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IJackson[] = { SAM7I_DEF(51, TANGELA), SAM7I_DEF(51, EXEGGUTOR), SAM7I_DEF(52, VICTREEBEL) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IKatelyn[] = { SAM7I_DEF(53, CHANSEY), SAM7I_DEF(52, CLEFABLE) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7ICyndy[] = { SAM7I_DEF(51, PRIMEAPE), SAM7I_DEF(51, HITMONTOP), SAM7I_DEF(52, MACHOKE), SAM7I_DEF(52, HITMONCHAN) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7ILeroy[] = { SAM7I_DEF(52, RHYDON), SAM7I_DEF(52, SLOWBRO), SAM7I_DEF(53, MACHAMP), SAM7I_DEF(53, KANGASKHAN) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IMichelle[] = { SAM7I_DEF(52, PERSIAN), SAM7I_DEF(52, DEWGONG), SAM7I_DEF(53, NINETALES), SAM7I_DEF(53, RAPIDASH) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7ILarry[] = { SAM7I_DEF(53, POLIWRATH), SAM7I_DEF(54, MACHAMP) };

static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IBrandon[] = { SAM7I_DEF(52, ONIX), SAM7I_DEF(53, NOSEPASS), SAM7I_DEF(53, RHYDON) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IClifford[] = { SAM7I_DEF(52, MAROWAK), SAM7I_DEF(52, GOLDUCK), SAM7I_DEF(53, PERSIAN) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IEdna[] = { SAM7I_DEF(52, DITTO), SAM7I_DEF(53, PORYGON) };
static const struct TrainerMonNoItemDefaultMoves sParty_Sam7IBenjamin[] = { SAM7I_DEF(52, GRAVELER), SAM7I_DEF(53, MAROWAK), SAM7I_DEF(53, SANDSLASH) };

#undef SAM7I_DEF
