// Pokémon: Sam Edition — Vermilion Gym current authority overlay.
// The historical Slowpoke/Poliwhirl/Starmie draft remains in trainer_parties.h
// under a legacy symbol; this is the current production party for Lt. Surge.

static const struct TrainerMonNoItemCustomMoves sParty_LeaderSurgeVermilion[] = {
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_WAILMER,
        .moves = {MOVE_WATER_PULSE, MOVE_ROLLOUT, MOVE_ASTONISH, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 27,
        .species = SPECIES_CORPHISH,
        .moves = {MOVE_WATER_PULSE, MOVE_VICE_GRIP, MOVE_LEER, MOVE_HARDEN},
    },
    {
        .iv = 100,
        .lvl = 29,
        .species = SPECIES_SHARPEDO,
        .moves = {MOVE_WATER_PULSE, MOVE_BITE, MOVE_SCREECH, MOVE_SCARY_FACE},
    },
};
