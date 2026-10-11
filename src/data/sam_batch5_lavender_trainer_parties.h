// Pokemon Sam Edition - TRAINERS Batch 5
// Lavender / Rock Tunnel ordinary-trainer party authority overlay.
// Level-up/default moves only, no held items.

#define SAM_MON(level, mon) { .iv = 0, .lvl = (level), .species = SPECIES_##mon }

// Route 9 / Route 10 north approach
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerAlicia[] = {
    SAM_MON(21, GLOOM), SAM_MON(21, WEEPINBELL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerJeremy[] = {
    SAM_MON(22, MACHOP), SAM_MON(22, GEODUDE), SAM_MON(22, ONIX),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5BugCatcherBrent[] = {
    SAM_MON(22, BEEDRILL), SAM_MON(22, BUTTERFREE), SAM_MON(22, VENONAT),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5CamperChris[] = {
    SAM_MON(22, GROWLITHE), SAM_MON(23, CHARMELEON),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerAlan[] = {
    SAM_MON(22, DIGLETT), SAM_MON(22, ONIX), SAM_MON(23, CUBONE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5BugCatcherConner[] = {
    SAM_MON(22, PARAS), SAM_MON(22, BUTTERFREE), SAM_MON(23, BEEDRILL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5CamperDrew[] = {
    SAM_MON(22, VOLTORB), SAM_MON(22, MAGNEMITE), SAM_MON(23, KADABRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerBrice[] = {
    SAM_MON(23, MACHOP), SAM_MON(23, CUBONE), SAM_MON(23, ONIX),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerCaitlin[] = {
    SAM_MON(24, MEOWTH),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerHeidi[] = {
    SAM_MON(23, MAGNEMITE), SAM_MON(23, VOLTORB), SAM_MON(24, PIKACHU), SAM_MON(24, CLEFAIRY),
};

// Rock Tunnel, in settled traversal order.
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PokemaniacAshton[] = {
    SAM_MON(24, CUBONE), SAM_MON(24, SLOWPOKE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PokemaniacWinston[] = {
    SAM_MON(26, SLOWPOKE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerMartha[] = {
    SAM_MON(23, IVYSAUR), SAM_MON(23, GLOOM), SAM_MON(24, CLEFAIRY),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PokemaniacSteve[] = {
    SAM_MON(23, CHARMELEON), SAM_MON(23, CUBONE), SAM_MON(24, KADABRA),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerAllen[] = {
    SAM_MON(25, GRAVELER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerEric[] = {
    SAM_MON(23, MACHOP), SAM_MON(23, ONIX), SAM_MON(24, GEODUDE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerLenny[] = {
    SAM_MON(23, GEODUDE), SAM_MON(23, MACHOP), SAM_MON(24, GRAVELER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerOliver[] = {
    SAM_MON(24, ONIX), SAM_MON(24, GEODUDE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerLucas[] = {
    SAM_MON(24, GRAVELER), SAM_MON(24, ONIX), SAM_MON(24, MACHOP),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerSofia[] = {
    SAM_MON(23, JIGGLYPUFF), SAM_MON(23, PIDGEOTTO), SAM_MON(23, MEOWTH),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5HikerDudley[] = {
    SAM_MON(24, GRAVELER), SAM_MON(24, MACHOP), SAM_MON(24, ONIX),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PokemaniacCooper[] = {
    SAM_MON(23, SLOWPOKE), SAM_MON(23, SLOWPOKE), SAM_MON(24, SLOWPOKE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerLeah[] = {
    SAM_MON(23, WEEPINBELL), SAM_MON(24, CLEFAIRY),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerDana[] = {
    SAM_MON(23, PIDGEOTTO), SAM_MON(23, RATICATE), SAM_MON(24, WEEPINBELL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5PicnickerAriana[] = {
    SAM_MON(23, MEOWTH), SAM_MON(23, GLOOM), SAM_MON(24, PIDGEOTTO), SAM_MON(24, CLEFAIRY),
};

// Pokemon Tower Channelers, floors 3F-6F in settled floor/object order.
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerPatricia[] = {
    SAM_MON(25, GASTLY), SAM_MON(25, DUSKULL),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerCarly[] = {
    SAM_MON(25, GASTLY), SAM_MON(25, SHUPPET), SAM_MON(26, CUBONE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerHope[] = {
    SAM_MON(27, HAUNTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerLaurel[] = {
    SAM_MON(26, DUSKULL), SAM_MON(26, GASTLY), SAM_MON(27, SHUPPET),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerJody[] = {
    SAM_MON(26, CUBONE), SAM_MON(26, GASTLY),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerPaula[] = {
    SAM_MON(26, SHUPPET), SAM_MON(27, HAUNTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerRuth[] = {
    SAM_MON(27, LICKITUNG),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerTammy[] = {
    SAM_MON(26, GASTLY), SAM_MON(26, GASTLY), SAM_MON(27, HAUNTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerKarina[] = {
    SAM_MON(27, DUSKULL), SAM_MON(27, SHUPPET), SAM_MON(27, CUBONE),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerJanae[] = {
    SAM_MON(27, HAUNTER), SAM_MON(27, DUSKULL), SAM_MON(28, SHUPPET),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerAngelica[] = {
    SAM_MON(27, GASTLY), SAM_MON(28, HAUNTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerJennifer[] = {
    SAM_MON(28, LICKITUNG), SAM_MON(28, HAUNTER),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5ChannelerEmilia[] = {
    SAM_MON(28, HAUNTER), SAM_MON(28, SHUPPET), SAM_MON(28, DUSKULL),
};

// Tower Rocket slots 20-21 remain ordinary; the former first Rocket slot is
// specialist-owned by Thomas and is deliberately not remapped here.
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5RocketGrunt20[] = {
    SAM_MON(29, ARBOK), SAM_MON(29, HYPNO), SAM_MON(29, GOLBAT),
};
static const struct TrainerMonNoItemDefaultMoves sParty_SamB5RocketGrunt21[] = {
    SAM_MON(29, MACHOKE), SAM_MON(29, MUK), SAM_MON(30, RATICATE),
};

#undef SAM_MON
