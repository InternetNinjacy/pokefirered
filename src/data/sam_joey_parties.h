// Pokémon: Sam Edition — OAK-002 Youngster Joey superboss party.
// Exact Lv. 80 moves/items are authoritative here. Nature/EV/IV profiles are
// applied by the shared trainer-party constructor so the stock party format remains intact.
static const struct TrainerMonItemCustomMoves sParty_YoungsterJoeySuperboss[] =
{
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_ZAPDOS,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_THUNDERBOLT, MOVE_HIDDEN_POWER, MOVE_THUNDER_WAVE, MOVE_LIGHT_SCREEN},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_GARDEVOIR,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_HYPNOSIS},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_MOLTRES,
        .heldItem = ITEM_WHITE_HERB,
        .moves = {MOVE_OVERHEAT, MOVE_FLAMETHROWER, MOVE_HIDDEN_POWER, MOVE_SUNNY_DAY},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_ARTICUNO,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_TOXIC, MOVE_REFLECT, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_AERIAL_ACE, MOVE_BRICK_BREAK},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_MEWTWO,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_PSYCHIC, MOVE_ICE_BEAM, MOVE_BRICK_BREAK, MOVE_RECOVER},
    },
};
