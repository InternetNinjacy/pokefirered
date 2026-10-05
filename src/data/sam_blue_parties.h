// Pokémon: Sam Edition — Blue main-rival party data.
// Authority: Blue Decision Record v1.0 + Blue Implementation Addendum v1.0.
// Branch naming reflects Blue's team identity, not the player's selected starter.

// Route 22
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute22Water[] = {
    {.iv = 50, .lvl = 9, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute22Electric[] = {
    {.iv = 50, .lvl = 9, .species = SPECIES_PICHU, .moves = {MOVE_THUNDERBOLT, MOVE_QUICK_ATTACK, MOVE_SWEET_KISS, MOVE_TAIL_WHIP}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute22Fire[] = {
    {.iv = 50, .lvl = 9, .species = SPECIES_EEVEE, .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_TAIL_WHIP, MOVE_QUICK_ATTACK}},
};

// Route 4 mandatory Double Battle with Green
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute4Water[] = {
    // Blue lead / Green lead, then Blue replacement / Green replacement.
    {.iv = 70, .lvl = 16, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 255, .lvl = 16, .species = SPECIES_PIKACHU, .moves = {MOVE_THUNDER_SHOCK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_TAIL_WHIP}},
    {.iv = 70, .lvl = 14, .species = SPECIES_CHINCHOU, .moves = {MOVE_WATER_GUN, MOVE_THUNDER_SHOCK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC}},
    {.iv = 255, .lvl = 14, .species = SPECIES_BULBASAUR, .moves = {MOVE_VINE_WHIP, MOVE_LEECH_SEED, MOVE_TACKLE, MOVE_GROWL}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute4Electric[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_PIKACHU, .moves = {MOVE_THUNDERBOLT, MOVE_QUICK_ATTACK, MOVE_BRICK_BREAK, MOVE_THUNDER_WAVE}},
    {.iv = 255, .lvl = 16, .species = SPECIES_EEVEE, .moves = {MOVE_TACKLE, MOVE_HELPING_HAND, MOVE_SAND_ATTACK, MOVE_GROWL}},
    {.iv = 70, .lvl = 14, .species = SPECIES_VOLTORB, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SONIC_BOOM, MOVE_ROLLOUT}},
    {.iv = 255, .lvl = 15, .species = SPECIES_MAGIKARP, .moves = {MOVE_TACKLE, MOVE_SPLASH, MOVE_NONE, MOVE_NONE}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute4Fire[] = {
    {.iv = 70, .lvl = 16, .species = SPECIES_FLAREON, .moves = {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_SAND_ATTACK, MOVE_HELPING_HAND}},
    {.iv = 255, .lvl = 16, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_TOXIC, MOVE_NONE, MOVE_NONE}},
    {.iv = 70, .lvl = 14, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_GROWL}},
    {.iv = 255, .lvl = 14, .species = SPECIES_GROWLITHE, .moves = {MOVE_EMBER, MOVE_BITE, MOVE_LEER, MOVE_ROAR}},
};

// Route 11
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute11Water[] = {
    {.iv = 90, .lvl = 23, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 90, .lvl = 21, .species = SPECIES_CHINCHOU, .moves = {MOVE_WATER_GUN, MOVE_THUNDER_SHOCK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC}},
    {.iv = 90, .lvl = 20, .species = SPECIES_LOMBRE, .moves = {MOVE_ABSORB, MOVE_WATER_GUN, MOVE_FAKE_OUT, MOVE_NATURE_POWER}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute11Electric[] = {
    {.iv = 90, .lvl = 23, .species = SPECIES_RAICHU, .moves = {MOVE_THUNDERBOLT, MOVE_BRICK_BREAK, MOVE_QUICK_ATTACK, MOVE_SLAM}},
    {.iv = 90, .lvl = 21, .species = SPECIES_VOLTORB, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SONIC_BOOM, MOVE_ROLLOUT}},
    {.iv = 90, .lvl = 20, .species = SPECIES_FLAAFFY, .moves = {MOVE_THUNDERBOLT, MOVE_BODY_SLAM, MOVE_THUNDER_WAVE, MOVE_HEADBUTT}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute11Fire[] = {
    {.iv = 90, .lvl = 23, .species = SPECIES_FLAREON, .moves = {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_BITE, MOVE_HELPING_HAND}},
    {.iv = 90, .lvl = 21, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_STOMP, MOVE_TAIL_WHIP, MOVE_GROWL}},
    {.iv = 90, .lvl = 20, .species = SPECIES_GROWLITHE, .moves = {MOVE_EMBER, MOVE_BITE, MOVE_ROAR, MOVE_LEER}},
};

// Route 10
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute10Water[] = {
    {.iv = 110, .lvl = 27, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 110, .lvl = 27, .species = SPECIES_LANTURN, .moves = {MOVE_WATER_GUN, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC}},
    {.iv = 110, .lvl = 25, .species = SPECIES_LOMBRE, .moves = {MOVE_WATER_GUN, MOVE_ABSORB, MOVE_FAKE_OUT, MOVE_NATURE_POWER}},
    {.iv = 110, .lvl = 23, .species = SPECIES_HORSEA, .moves = {MOVE_WATER_GUN, MOVE_SMOKESCREEN, MOVE_LEER, MOVE_BUBBLE}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute10Electric[] = {
    {.iv = 110, .lvl = 27, .species = SPECIES_RAICHU, .moves = {MOVE_THUNDERBOLT, MOVE_BRICK_BREAK, MOVE_QUICK_ATTACK, MOVE_SLAM}},
    {.iv = 110, .lvl = 25, .species = SPECIES_VOLTORB, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SONIC_BOOM, MOVE_ROLLOUT}},
    {.iv = 110, .lvl = 24, .species = SPECIES_FLAAFFY, .moves = {MOVE_THUNDERBOLT, MOVE_BODY_SLAM, MOVE_THUNDER_WAVE, MOVE_HEADBUTT}},
    {.iv = 110, .lvl = 23, .species = SPECIES_MAGNEMITE, .moves = {MOVE_THUNDERBOLT, MOVE_SONIC_BOOM, MOVE_SUPERSONIC, MOVE_THUNDER_WAVE}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueRoute10Fire[] = {
    {.iv = 110, .lvl = 27, .species = SPECIES_FLAREON, .moves = {MOVE_FIRE_SPIN, MOVE_QUICK_ATTACK, MOVE_BITE, MOVE_HELPING_HAND}},
    {.iv = 110, .lvl = 25, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_STOMP, MOVE_TAIL_WHIP, MOVE_GROWL}},
    {.iv = 110, .lvl = 24, .species = SPECIES_GROWLITHE, .moves = {MOVE_EMBER, MOVE_BITE, MOVE_ROAR, MOVE_LEER}},
    {.iv = 110, .lvl = 23, .species = SPECIES_CHARMELEON, .moves = {MOVE_EMBER, MOVE_METAL_CLAW, MOVE_SMOKESCREEN, MOVE_SCARY_FACE}},
};

// Pokémon Tower
static const struct TrainerMonNoItemCustomMoves sParty_BlueTowerWater[] = {
    {.iv = 130, .lvl = 31, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 130, .lvl = 29, .species = SPECIES_LANTURN, .moves = {MOVE_WATER_PULSE, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC}},
    {.iv = 130, .lvl = 28, .species = SPECIES_LOMBRE, .moves = {MOVE_WATER_PULSE, MOVE_ABSORB, MOVE_FAKE_OUT, MOVE_NATURE_POWER}},
    {.iv = 130, .lvl = 27, .species = SPECIES_HORSEA, .moves = {MOVE_WATER_PULSE, MOVE_SMOKESCREEN, MOVE_LEER, MOVE_BUBBLE}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueTowerElectric[] = {
    {.iv = 130, .lvl = 31, .species = SPECIES_RAICHU, .moves = {MOVE_THUNDERBOLT, MOVE_BRICK_BREAK, MOVE_QUICK_ATTACK, MOVE_SLAM}},
    {.iv = 130, .lvl = 30, .species = SPECIES_ELECTRODE, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SELF_DESTRUCT, MOVE_SWIFT}},
    {.iv = 130, .lvl = 28, .species = SPECIES_FLAAFFY, .moves = {MOVE_THUNDERBOLT, MOVE_BODY_SLAM, MOVE_THUNDER_WAVE, MOVE_HEADBUTT}},
    {.iv = 130, .lvl = 27, .species = SPECIES_MAGNEMITE, .moves = {MOVE_THUNDERBOLT, MOVE_SONIC_BOOM, MOVE_SUPERSONIC, MOVE_THUNDER_WAVE}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueTowerFire[] = {
    {.iv = 130, .lvl = 31, .species = SPECIES_FLAREON, .moves = {MOVE_FIRE_SPIN, MOVE_QUICK_ATTACK, MOVE_BITE, MOVE_HELPING_HAND}},
    {.iv = 130, .lvl = 29, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_STOMP, MOVE_TAIL_WHIP, MOVE_GROWL}},
    {.iv = 130, .lvl = 28, .species = SPECIES_GROWLITHE, .moves = {MOVE_EMBER, MOVE_BITE, MOVE_ROAR, MOVE_LEER}},
    {.iv = 130, .lvl = 27, .species = SPECIES_CHARMELEON, .moves = {MOVE_EMBER, MOVE_METAL_CLAW, MOVE_SMOKESCREEN, MOVE_SCARY_FACE}},
    {.iv = 130, .lvl = 26, .species = SPECIES_VULPIX, .moves = {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY}},
};

// Silph Co.
static const struct TrainerMonNoItemCustomMoves sParty_BlueSilphWater[] = {
    {.iv = 150, .lvl = 35, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_NONE, MOVE_NONE}},
    {.iv = 150, .lvl = 33, .species = SPECIES_LANTURN, .moves = {MOVE_WATER_PULSE, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_CONFUSE_RAY}},
    {.iv = 150, .lvl = 32, .species = SPECIES_LOMBRE, .moves = {MOVE_WATER_PULSE, MOVE_MEGA_DRAIN, MOVE_FAKE_OUT, MOVE_NATURE_POWER}},
    {.iv = 150, .lvl = 32, .species = SPECIES_SEADRA, .moves = {MOVE_WATER_PULSE, MOVE_TWISTER, MOVE_SMOKESCREEN, MOVE_AGILITY}},
    {.iv = 150, .lvl = 31, .species = SPECIES_MARSHTOMP, .moves = {MOVE_WATER_PULSE, MOVE_MUD_SHOT, MOVE_ROCK_TOMB, MOVE_PROTECT}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueSilphElectric[] = {
    {.iv = 150, .lvl = 35, .species = SPECIES_RAICHU, .moves = {MOVE_THUNDERBOLT, MOVE_BRICK_BREAK, MOVE_QUICK_ATTACK, MOVE_SLAM}},
    {.iv = 150, .lvl = 34, .species = SPECIES_ELECTRODE, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SELF_DESTRUCT, MOVE_SWIFT}},
    {.iv = 150, .lvl = 33, .species = SPECIES_AMPHAROS, .moves = {MOVE_THUNDERBOLT, MOVE_FIRE_PUNCH, MOVE_BODY_SLAM, MOVE_THUNDER_WAVE}},
    {.iv = 150, .lvl = 32, .species = SPECIES_MAGNETON, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_SONIC_BOOM, MOVE_SUPERSONIC}},
    {.iv = 150, .lvl = 31, .species = SPECIES_MANECTRIC, .moves = {MOVE_THUNDERBOLT, MOVE_BITE, MOVE_QUICK_ATTACK, MOVE_ROAR}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueSilphFire[] = {
    {.iv = 150, .lvl = 35, .species = SPECIES_FLAREON, .moves = {MOVE_FIRE_SPIN, MOVE_QUICK_ATTACK, MOVE_BITE, MOVE_SHADOW_BALL}},
    {.iv = 150, .lvl = 33, .species = SPECIES_PONYTA, .moves = {MOVE_EMBER, MOVE_STOMP, MOVE_AGILITY, MOVE_TAIL_WHIP}},
    {.iv = 150, .lvl = 34, .species = SPECIES_ARCANINE, .moves = {MOVE_FLAME_WHEEL, MOVE_BITE, MOVE_TAKE_DOWN, MOVE_ROAR}},
    {.iv = 150, .lvl = 32, .species = SPECIES_CHARMELEON, .moves = {MOVE_EMBER, MOVE_METAL_CLAW, MOVE_SLASH, MOVE_SMOKESCREEN}},
    {.iv = 150, .lvl = 31, .species = SPECIES_VULPIX, .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK}},
};

// Cinnabar
static const struct TrainerMonNoItemCustomMoves sParty_BlueCinnabarWater[] = {
    {.iv = 180, .lvl = 40, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_PROTECT, MOVE_NONE}},
    {.iv = 180, .lvl = 38, .species = SPECIES_LANTURN, .moves = {MOVE_SURF, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_CONFUSE_RAY}},
    {.iv = 180, .lvl = 37, .species = SPECIES_LOMBRE, .moves = {MOVE_SURF, MOVE_MEGA_DRAIN, MOVE_FAKE_OUT, MOVE_NATURE_POWER}},
    {.iv = 180, .lvl = 38, .species = SPECIES_SEADRA, .moves = {MOVE_SURF, MOVE_TWISTER, MOVE_SMOKESCREEN, MOVE_AGILITY}},
    {.iv = 180, .lvl = 40, .species = SPECIES_SWAMPERT, .moves = {MOVE_SURF, MOVE_MUD_SHOT, MOVE_ROCK_TOMB, MOVE_PROTECT}},
    {.iv = 180, .lvl = 38, .species = SPECIES_STARYU, .moves = {MOVE_SURF, MOVE_PSYCHIC, MOVE_RECOVER, MOVE_SWIFT}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueCinnabarElectric[] = {
    {.iv = 180, .lvl = 40, .species = SPECIES_RAICHU, .moves = {MOVE_THUNDERBOLT, MOVE_BRICK_BREAK, MOVE_IRON_TAIL, MOVE_QUICK_ATTACK}},
    {.iv = 180, .lvl = 39, .species = SPECIES_ELECTRODE, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_EXPLOSION}},
    {.iv = 180, .lvl = 38, .species = SPECIES_AMPHAROS, .moves = {MOVE_THUNDERBOLT, MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH, MOVE_BODY_SLAM}},
    {.iv = 180, .lvl = 38, .species = SPECIES_MAGNETON, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_TRI_ATTACK}},
    {.iv = 180, .lvl = 37, .species = SPECIES_MANECTRIC, .moves = {MOVE_THUNDERBOLT, MOVE_FLAMETHROWER, MOVE_CRUNCH, MOVE_QUICK_ATTACK}},
    {.iv = 180, .lvl = 38, .species = SPECIES_ELECTABUZZ, .moves = {MOVE_THUNDERBOLT, MOVE_ICE_PUNCH, MOVE_BRICK_BREAK, MOVE_PSYCHIC}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueCinnabarFire[] = {
    {.iv = 180, .lvl = 40, .species = SPECIES_FLAREON, .moves = {MOVE_FLAMETHROWER, MOVE_QUICK_ATTACK, MOVE_BITE, MOVE_SHADOW_BALL}},
    {.iv = 180, .lvl = 38, .species = SPECIES_PONYTA, .moves = {MOVE_FIRE_SPIN, MOVE_STOMP, MOVE_AGILITY, MOVE_TAKE_DOWN}},
    {.iv = 180, .lvl = 39, .species = SPECIES_ARCANINE, .moves = {MOVE_FLAME_WHEEL, MOVE_BITE, MOVE_TAKE_DOWN, MOVE_ROAR}},
    {.iv = 180, .lvl = 40, .species = SPECIES_CHARIZARD, .moves = {MOVE_FLAMETHROWER, MOVE_WING_ATTACK, MOVE_SLASH, MOVE_SMOKESCREEN}},
    {.iv = 180, .lvl = 37, .species = SPECIES_VULPIX, .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK}},
    {.iv = 180, .lvl = 38, .species = SPECIES_MAGMAR, .moves = {MOVE_FIRE_PUNCH, MOVE_CONFUSE_RAY, MOVE_SMOKESCREEN, MOVE_FAINT_ATTACK}},
};

// One Island
static const struct TrainerMonNoItemCustomMoves sParty_BlueOneIslandWater[] = {
    {.iv = 210, .lvl = 45, .species = SPECIES_DITTO, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_PROTECT, MOVE_NONE}},
    {.iv = 210, .lvl = 43, .species = SPECIES_LANTURN, .moves = {MOVE_SURF, MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE, MOVE_CONFUSE_RAY}},
    {.iv = 210, .lvl = 43, .species = SPECIES_LUDICOLO, .moves = {MOVE_SURF, MOVE_GIGA_DRAIN, MOVE_FAKE_OUT, MOVE_ICE_BEAM}},
    {.iv = 210, .lvl = 44, .species = SPECIES_KINGDRA, .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_AGILITY}},
    {.iv = 210, .lvl = 45, .species = SPECIES_SWAMPERT, .moves = {MOVE_SURF, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_PROTECT}},
    {.iv = 210, .lvl = 44, .species = SPECIES_STARMIE, .moves = {MOVE_SURF, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_RECOVER}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueOneIslandElectric[] = {
    {.iv = 210, .lvl = 45, .species = SPECIES_RAICHU, .moves = {MOVE_THUNDERBOLT, MOVE_BRICK_BREAK, MOVE_IRON_TAIL, MOVE_QUICK_ATTACK}},
    {.iv = 210, .lvl = 44, .species = SPECIES_ELECTRODE, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_EXPLOSION}},
    {.iv = 210, .lvl = 43, .species = SPECIES_AMPHAROS, .moves = {MOVE_THUNDERBOLT, MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH, MOVE_BODY_SLAM}},
    {.iv = 210, .lvl = 43, .species = SPECIES_MAGNETON, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_TRI_ATTACK}},
    {.iv = 210, .lvl = 43, .species = SPECIES_MANECTRIC, .moves = {MOVE_THUNDERBOLT, MOVE_FLAMETHROWER, MOVE_CRUNCH, MOVE_QUICK_ATTACK}},
    {.iv = 210, .lvl = 44, .species = SPECIES_ELECTABUZZ, .moves = {MOVE_THUNDERBOLT, MOVE_ICE_PUNCH, MOVE_BRICK_BREAK, MOVE_PSYCHIC}},
};
static const struct TrainerMonNoItemCustomMoves sParty_BlueOneIslandFire[] = {
    {.iv = 210, .lvl = 44, .species = SPECIES_FLAREON, .moves = {MOVE_FLAMETHROWER, MOVE_QUICK_ATTACK, MOVE_BITE, MOVE_SHADOW_BALL}},
    {.iv = 210, .lvl = 43, .species = SPECIES_RAPIDASH, .moves = {MOVE_FLAMETHROWER, MOVE_STOMP, MOVE_AGILITY, MOVE_TAKE_DOWN}},
    {.iv = 210, .lvl = 44, .species = SPECIES_ARCANINE, .moves = {MOVE_FLAMETHROWER, MOVE_BITE, MOVE_TAKE_DOWN, MOVE_ROAR}},
    {.iv = 210, .lvl = 45, .species = SPECIES_CHARIZARD, .moves = {MOVE_FLAMETHROWER, MOVE_WING_ATTACK, MOVE_SLASH, MOVE_SMOKESCREEN}},
    {.iv = 210, .lvl = 43, .species = SPECIES_NINETALES, .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK}},
    {.iv = 210, .lvl = 43, .species = SPECIES_MAGMAR, .moves = {MOVE_FIRE_PUNCH, MOVE_CONFUSE_RAY, MOVE_SMOKESCREEN, MOVE_FAINT_ATTACK}},
};

// Elite Four first clear — Fire branch occupies legacy Bruno trainer slot.
static const struct TrainerMonItemCustomMoves sParty_BlueEliteFire[] = {
    {.iv = 250, .lvl = 54, .species = SPECIES_NINETALES, .heldItem = ITEM_LEFTOVERS, .moves = {MOVE_FLAMETHROWER, MOVE_SUNNY_DAY, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY}},
    {.iv = 250, .lvl = 54, .species = SPECIES_RAPIDASH, .heldItem = ITEM_SCOPE_LENS, .moves = {MOVE_FLAMETHROWER, MOVE_STOMP, MOVE_IRON_TAIL, MOVE_AGILITY}},
    {.iv = 250, .lvl = 55, .species = SPECIES_ARCANINE, .heldItem = ITEM_LUM_BERRY, .moves = {MOVE_FLAMETHROWER, MOVE_EXTREME_SPEED, MOVE_BITE, MOVE_IRON_TAIL}},
    {.iv = 250, .lvl = 55, .species = SPECIES_CHARIZARD, .heldItem = ITEM_WHITE_HERB, .moves = {MOVE_OVERHEAT, MOVE_AERIAL_ACE, MOVE_BRICK_BREAK, MOVE_SLASH}},
    {.iv = 250, .lvl = 55, .species = SPECIES_MAGMAR, .heldItem = ITEM_SALAC_BERRY, .moves = {MOVE_FIRE_PUNCH, MOVE_PSYCHIC, MOVE_THUNDER_PUNCH, MOVE_CONFUSE_RAY}},
    {.iv = 250, .lvl = 57, .species = SPECIES_FLAREON, .heldItem = ITEM_CHOICE_BAND, .moves = {MOVE_SHADOW_BALL, MOVE_RETURN, MOVE_QUICK_ATTACK, MOVE_IRON_TAIL}},
};
static const struct TrainerMonItemCustomMoves sParty_BlueEliteWater[] = {
    {.iv = 250, .lvl = 54, .species = SPECIES_LANTURN, .heldItem = ITEM_LEFTOVERS, .moves = {MOVE_SURF, MOVE_THUNDERBOLT, MOVE_ICE_BEAM, MOVE_THUNDER_WAVE}},
    {.iv = 250, .lvl = 54, .species = SPECIES_LUDICOLO, .heldItem = ITEM_CHESTO_BERRY, .moves = {MOVE_SURF, MOVE_GIGA_DRAIN, MOVE_ICE_BEAM, MOVE_REST}},
    {.iv = 250, .lvl = 55, .species = SPECIES_KINGDRA, .heldItem = ITEM_LUM_BERRY, .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_AGILITY}},
    {.iv = 250, .lvl = 55, .species = SPECIES_SWAMPERT, .heldItem = ITEM_CHOICE_BAND, .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_BRICK_BREAK, MOVE_RETURN}},
    {.iv = 250, .lvl = 56, .species = SPECIES_STARMIE, .heldItem = ITEM_PETAYA_BERRY, .moves = {MOVE_SURF, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_ICE_BEAM}},
    {.iv = 250, .lvl = 57, .species = SPECIES_DITTO, .heldItem = ITEM_METAL_POWDER, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_PROTECT, MOVE_SUBSTITUTE}},
};
static const struct TrainerMonItemCustomMoves sParty_BlueEliteElectric[] = {
    {.iv = 250, .lvl = 54, .species = SPECIES_ELECTRODE, .heldItem = ITEM_FOCUS_BAND, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_EXPLOSION}},
    {.iv = 250, .lvl = 54, .species = SPECIES_MAGNETON, .heldItem = ITEM_LEFTOVERS, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_TRI_ATTACK}},
    {.iv = 250, .lvl = 55, .species = SPECIES_AMPHAROS, .heldItem = ITEM_QUICK_CLAW, .moves = {MOVE_THUNDERBOLT, MOVE_ICE_PUNCH, MOVE_BRICK_BREAK, MOVE_BODY_SLAM}},
    {.iv = 250, .lvl = 55, .species = SPECIES_MANECTRIC, .heldItem = ITEM_PETAYA_BERRY, .moves = {MOVE_THUNDERBOLT, MOVE_CRUNCH, MOVE_HIDDEN_POWER, MOVE_THUNDER}},
    {.iv = 250, .lvl = 56, .species = SPECIES_ELECTABUZZ, .heldItem = ITEM_SCOPE_LENS, .moves = {MOVE_THUNDERBOLT, MOVE_ICE_PUNCH, MOVE_PSYCHIC, MOVE_BRICK_BREAK}},
    {.iv = 250, .lvl = 57, .species = SPECIES_RAICHU, .heldItem = ITEM_LUM_BERRY, .moves = {MOVE_THUNDERBOLT, MOVE_SURF, MOVE_BRICK_BREAK, MOVE_IRON_TAIL}},
};

// Elite Four rematch — locked +10 levels, same builds.
static const struct TrainerMonItemCustomMoves sParty_BlueEliteFireRematch[] = {
    {.iv = 250, .lvl = 64, .species = SPECIES_NINETALES, .heldItem = ITEM_LEFTOVERS, .moves = {MOVE_FLAMETHROWER, MOVE_SUNNY_DAY, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY}},
    {.iv = 250, .lvl = 64, .species = SPECIES_RAPIDASH, .heldItem = ITEM_SCOPE_LENS, .moves = {MOVE_FLAMETHROWER, MOVE_STOMP, MOVE_IRON_TAIL, MOVE_AGILITY}},
    {.iv = 250, .lvl = 65, .species = SPECIES_ARCANINE, .heldItem = ITEM_LUM_BERRY, .moves = {MOVE_FLAMETHROWER, MOVE_EXTREME_SPEED, MOVE_BITE, MOVE_IRON_TAIL}},
    {.iv = 250, .lvl = 65, .species = SPECIES_CHARIZARD, .heldItem = ITEM_WHITE_HERB, .moves = {MOVE_OVERHEAT, MOVE_AERIAL_ACE, MOVE_BRICK_BREAK, MOVE_SLASH}},
    {.iv = 250, .lvl = 65, .species = SPECIES_MAGMAR, .heldItem = ITEM_SALAC_BERRY, .moves = {MOVE_FIRE_PUNCH, MOVE_PSYCHIC, MOVE_THUNDER_PUNCH, MOVE_CONFUSE_RAY}},
    {.iv = 250, .lvl = 67, .species = SPECIES_FLAREON, .heldItem = ITEM_CHOICE_BAND, .moves = {MOVE_SHADOW_BALL, MOVE_RETURN, MOVE_QUICK_ATTACK, MOVE_IRON_TAIL}},
};
static const struct TrainerMonItemCustomMoves sParty_BlueEliteWaterRematch[] = {
    {.iv = 250, .lvl = 64, .species = SPECIES_LANTURN, .heldItem = ITEM_LEFTOVERS, .moves = {MOVE_SURF, MOVE_THUNDERBOLT, MOVE_ICE_BEAM, MOVE_THUNDER_WAVE}},
    {.iv = 250, .lvl = 64, .species = SPECIES_LUDICOLO, .heldItem = ITEM_CHESTO_BERRY, .moves = {MOVE_SURF, MOVE_GIGA_DRAIN, MOVE_ICE_BEAM, MOVE_REST}},
    {.iv = 250, .lvl = 65, .species = SPECIES_KINGDRA, .heldItem = ITEM_LUM_BERRY, .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_DRAGON_BREATH, MOVE_AGILITY}},
    {.iv = 250, .lvl = 65, .species = SPECIES_SWAMPERT, .heldItem = ITEM_CHOICE_BAND, .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_BRICK_BREAK, MOVE_RETURN}},
    {.iv = 250, .lvl = 66, .species = SPECIES_STARMIE, .heldItem = ITEM_PETAYA_BERRY, .moves = {MOVE_SURF, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_ICE_BEAM}},
    {.iv = 250, .lvl = 67, .species = SPECIES_DITTO, .heldItem = ITEM_METAL_POWDER, .moves = {MOVE_TRANSFORM, MOVE_WILL_O_WISP, MOVE_PROTECT, MOVE_SUBSTITUTE}},
};
static const struct TrainerMonItemCustomMoves sParty_BlueEliteElectricRematch[] = {
    {.iv = 250, .lvl = 64, .species = SPECIES_ELECTRODE, .heldItem = ITEM_FOCUS_BAND, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_EXPLOSION}},
    {.iv = 250, .lvl = 64, .species = SPECIES_MAGNETON, .heldItem = ITEM_LEFTOVERS, .moves = {MOVE_THUNDERBOLT, MOVE_RAIN_DANCE, MOVE_THUNDER, MOVE_TRI_ATTACK}},
    {.iv = 250, .lvl = 65, .species = SPECIES_AMPHAROS, .heldItem = ITEM_QUICK_CLAW, .moves = {MOVE_THUNDERBOLT, MOVE_ICE_PUNCH, MOVE_BRICK_BREAK, MOVE_BODY_SLAM}},
    {.iv = 250, .lvl = 65, .species = SPECIES_MANECTRIC, .heldItem = ITEM_PETAYA_BERRY, .moves = {MOVE_THUNDERBOLT, MOVE_CRUNCH, MOVE_HIDDEN_POWER, MOVE_THUNDER}},
    {.iv = 250, .lvl = 66, .species = SPECIES_ELECTABUZZ, .heldItem = ITEM_SCOPE_LENS, .moves = {MOVE_THUNDERBOLT, MOVE_ICE_PUNCH, MOVE_PSYCHIC, MOVE_BRICK_BREAK}},
    {.iv = 250, .lvl = 67, .species = SPECIES_RAICHU, .heldItem = ITEM_LUM_BERRY, .moves = {MOVE_THUNDERBOLT, MOVE_SURF, MOVE_BRICK_BREAK, MOVE_IRON_TAIL}},
};
