// Pokémon: Sam Edition — Batch 9 Cinnabar / Seafoam ordinary-trainer parties.
// Current trainer-construction rules: settled species/levels, default level-up moves,
// no held items. Live trainer identities/records are preserved through remaps.
#define SAM_BATCH9_MON(level_, mon_) { .iv = 0, .lvl = (level_), .species = SPECIES_##mon_ }

// Route 19 — 10 encounters.
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Reece[] = {
    SAM_BATCH9_MON(32, TENTACOOL), SAM_BATCH9_MON(32, SHELLDER), SAM_BATCH9_MON(33, STARYU),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Richard[] = {
    SAM_BATCH9_MON(32, HORSEA), SAM_BATCH9_MON(32, KRABBY), SAM_BATCH9_MON(33, STARYU),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Tony[] = {
    SAM_BATCH9_MON(34, SEADRA), SAM_BATCH9_MON(34, TENTACRUEL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Matthew[] = {
    SAM_BATCH9_MON(32, STARYU), SAM_BATCH9_MON(32, SHELLDER), SAM_BATCH9_MON(34, CLOYSTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Douglas[] = {
    SAM_BATCH9_MON(34, KINGLER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_David[] = {
    SAM_BATCH9_MON(34, POLIWRATH), SAM_BATCH9_MON(33, SEADRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Axle[] = {
    SAM_BATCH9_MON(32, POLIWHIRL), SAM_BATCH9_MON(32, HORSEA), SAM_BATCH9_MON(34, SEADRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Alice[] = {
    SAM_BATCH9_MON(35, VAPOREON),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Connie[] = {
    SAM_BATCH9_MON(33, TENTACOOL), SAM_BATCH9_MON(33, STARYU), SAM_BATCH9_MON(35, DEWGONG),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Anya[] = {
    SAM_BATCH9_MON(35, STARMIE),
};

// Route 20 — 7 encounters. Seafoam Islands itself remains trainer-free.
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Melissa[] = {
    SAM_BATCH9_MON(33, SHELLDER), SAM_BATCH9_MON(33, SEEL), SAM_BATCH9_MON(35, CLOYSTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Missy[] = {
    SAM_BATCH9_MON(35, SEADRA), SAM_BATCH9_MON(35, TENTACRUEL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Nora[] = {
    SAM_BATCH9_MON(34, STARYU), SAM_BATCH9_MON(34, SLOWPOKE), SAM_BATCH9_MON(35, SLOWBRO),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Roger[] = {
    SAM_BATCH9_MON(36, DEWGONG),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Dean[] = {
    SAM_BATCH9_MON(34, KINGLER), SAM_BATCH9_MON(34, STARMIE), SAM_BATCH9_MON(35, SEADRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Irene[] = {
    SAM_BATCH9_MON(35, POLIWRATH), SAM_BATCH9_MON(35, TENTACRUEL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Barry[] = {
    SAM_BATCH9_MON(34, FEAROW), SAM_BATCH9_MON(36, PIDGEOT), SAM_BATCH9_MON(36, DODRIO),
};

// Route 21 — 9 encounters.
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Ronald[] = {
    SAM_BATCH9_MON(35, MAGIKARP), SAM_BATCH9_MON(35, MAGIKARP), SAM_BATCH9_MON(37, GYARADOS),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Wade[] = {
    SAM_BATCH9_MON(35, SEAKING), SAM_BATCH9_MON(35, GOLDEEN), SAM_BATCH9_MON(36, SEAKING),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Spencer[] = {
    SAM_BATCH9_MON(36, SEADRA), SAM_BATCH9_MON(36, TENTACRUEL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_LilIan[] = {
    SAM_BATCH9_MON(36, POLIWRATH), SAM_BATCH9_MON(36, KINGLER), SAM_BATCH9_MON(37, PRIMEAPE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Claude[] = {
    SAM_BATCH9_MON(35, SHELLDER), SAM_BATCH9_MON(37, CLOYSTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Nolan[] = {
    SAM_BATCH9_MON(35, HORSEA), SAM_BATCH9_MON(36, SEADRA), SAM_BATCH9_MON(37, STARMIE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Jack[] = {
    SAM_BATCH9_MON(38, STARMIE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Jerome[] = {
    SAM_BATCH9_MON(35, STARYU), SAM_BATCH9_MON(36, WARTORTLE), SAM_BATCH9_MON(36, SEADRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Roland[] = {
    SAM_BATCH9_MON(36, TENTACRUEL), SAM_BATCH9_MON(38, GYARADOS),
};

// Cinnabar Pokémon Mansion — corrected abandoned-dorm package, 6 encounters.
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Arnie[] = {
    SAM_BATCH9_MON(35, MEOWTH), SAM_BATCH9_MON(35, GROWLITHE), SAM_BATCH9_MON(36, RATICATE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Ted[] = {
    SAM_BATCH9_MON(35, PORYGON), SAM_BATCH9_MON(35, MAGNEMITE), SAM_BATCH9_MON(36, KADABRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Simon[] = {
    SAM_BATCH9_MON(38, NINETALES),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Braydon[] = {
    SAM_BATCH9_MON(36, DITTO), SAM_BATCH9_MON(37, HYPNO), SAM_BATCH9_MON(37, WEEZING),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Lewis[] = {
    SAM_BATCH9_MON(36, PERSIAN), SAM_BATCH9_MON(36, MAGMAR), SAM_BATCH9_MON(38, RAPIDASH),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamBatch9_Ivan[] = {
    SAM_BATCH9_MON(37, ELECTRODE), SAM_BATCH9_MON(37, MAGNETON), SAM_BATCH9_MON(38, ALAKAZAM),
};

#undef SAM_BATCH9_MON
