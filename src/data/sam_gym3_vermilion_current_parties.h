// Pokémon: Sam Edition — Vermilion Gym current authority overlay.
// This file supersedes the stale Slowpoke/Poliwhirl/Starmie draft party
// that remains in trainer_parties.h for ancestry/history compatibility.

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
