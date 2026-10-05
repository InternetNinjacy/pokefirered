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
        .moves = {MOVE_THUNDERBOLT, MOVE_HIDDEN_POWER, MOVE_DRILL_PECK, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_GARDEVOIR,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_CALM_MIND, MOVE_WILL_O_WISP},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_MOLTRES,
        .heldItem = ITEM_WHITE_HERB,
        .moves = {MOVE_FIRE_BLAST, MOVE_SKY_ATTACK, MOVE_OVERHEAT, MOVE_HIDDEN_POWER},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_ARTICUNO,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_ROAR, MOVE_TOXIC, MOVE_REST},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_LUM_BERRY,
        .moves = {MOVE_DRAGON_DANCE, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE, MOVE_BRICK_BREAK},
    },
    {
        .iv = 255,
        .lvl = 80,
        .species = SPECIES_MEWTWO,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_PSYCHIC, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_RECOVER},
    },
};
