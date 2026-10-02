# FireRed Source-Location Index

Verified baseline: `pret/pokefirered` commit `c75f352304d529f6ba92d4f74b9cf8b5c3810788`
Target: Pokémon FireRed, English revision 0

This is the reusable engine map for FireRed ROM-hack projects. It records verified source locations and important execution symbols. Project-specific changes belong in the project's own source locator.

## Species / Pokémon data

**Identity and limits**
- `include/constants/species.h`
  - numeric `SPECIES_*` constants
  - baseline ordinary species end: `SPECIES_CHIMECHO = 411`
  - baseline `SPECIES_EGG = 412`
  - `NUM_SPECIES` derives from `SPECIES_EGG`
  - derived Unown constants follow `NUM_SPECIES`

**Base species data**
- `src/data/pokemon/species_info.h`
  - per-species base stats, types, catch rate, EXP yield, EV yield, held items, gender ratio, egg cycles, friendship, growth rate, egg groups, abilities, Safari flee rate, body color, flip flag

**Level-up learnsets**
- `src/data/pokemon/level_up_learnsets.h`
- `src/data/pokemon/level_up_learnset_pointers.h`

**Egg / tutor learnsets**
- `src/data/pokemon/egg_moves.h`
- `src/data/pokemon/tutor_learnsets.h`

**Pokédex**
- `src/data/pokemon/pokedex_entries.h`
- `src/data/pokemon/pokedex_categories.h`
- `src/data/pokemon/pokedex_orders.h`
- `src/data/pokemon/pokedex_text.h`
- `src/data/pokemon/pokedex_text_fr.h`
- `src/data/pokemon/pokedex_text_lg.h`

**Pokémon construction / runtime**
- `src/pokemon.c`
  - `CreateMon()`
  - species data is read through `gSpeciesInfo[species]`
  - experience uses `gExperienceTables`

## Evolution system

**Evolution method constants**
- `include/constants/pokemon.h`
  - `EVO_FRIENDSHIP`, `EVO_FRIENDSHIP_DAY`, `EVO_FRIENDSHIP_NIGHT`
  - `EVO_LEVEL`, `EVO_TRADE`, `EVO_TRADE_ITEM`, `EVO_ITEM`
  - attack/defense personality/special-level methods and `EVO_BEAUTY`
  - modes: `EVO_MODE_NORMAL`, `EVO_MODE_TRADE`, `EVO_MODE_ITEM_USE`, `EVO_MODE_ITEM_CHECK`

**Evolution table**
- `src/data/pokemon/evolution.h`
  - `gEvolutionTable[NUM_SPECIES][EVOS_PER_MON]`
  - each entry supplies method, parameter, and target species

**Runtime evaluator**
- `src/pokemon.c`
  - `GetEvolutionTargetSpecies(struct Pokemon *mon, u8 type, u16 evolutionItem)`
  - reads `gEvolutionTable`
  - handles normal/level, trade/held-item, and item-use evolution routes

**Evolution-stone item path**
- `src/pokemon.c`
  - item-effect handling calls `GetEvolutionTargetSpecies(..., EVO_MODE_ITEM_USE, item)`
  - successful item evolution calls `BeginEvolutionScene()`
- `src/item_use.c`
  - `FieldUseFunc_EvolutionStone` path is represented by `FieldUseFunc_EvoItem` in item data
  - `ItemUseCB_EvolutionStone`

**Evolution scene**
- `src/evolution_scene.c`
- `src/evolution_graphics.c`
- headers in `include/evolution_scene.h`, `include/evolution_graphics.h`

## Starter system

FireRed's starter selection is primarily script-driven rather than a standalone starter module.

**Primary script**
- `data/maps/PalletTown_ProfessorOaksLab/scripts.inc`
  - temporary variables: `PLAYER_STARTER_NUM`, `PLAYER_STARTER_SPECIES`, `RIVAL_STARTER_SPECIES`, `RIVAL_STARTER_ID`
  - `PalletTown_ProfessorOaksLab_ChooseStarterScene`
  - `PalletTown_ProfessorOaksLab_EventScript_ConfirmStarterChoice`
  - `PalletTown_ProfessorOaksLab_EventScript_ChoseStarter`
  - `PalletTown_ProfessorOaksLab_EventScript_RivalPicksStarter`
  - starter grant uses `givemon`
  - selection persists through `VAR_STARTER_MON`

**Starter dialogue**
- `data/maps/PalletTown_ProfessorOaksLab/text.inc`

**Starter/rival battle trainer data**
- `src/data/trainers.h`
- `src/data/trainer_parties.h`
- trainer constants are generated/defined through the trainer constant surfaces used by the repository

There is no baseline `src/starter_choose.c`.

## Items

**Item IDs**
- `include/constants/items.h`
  - `ITEM_*` numeric constants
  - baseline TM01–TM50 occupy item IDs 289–338
  - HMs follow TM50

**Authoring data**
- `src/data/items.json`
  - name, ID, price, hold effect, description, pocket, item type, field-use function, battle-use function, secondary ID
  - TM/HM entries additionally carry `moveId`
  - evolution stones use `FieldUseFunc_EvoItem`

**Generated item table**
- `src/item.c` includes generated `data/items.h`
- runtime item accessors read `gItems[]`, including:
  - `ItemId_GetName()`
  - `ItemId_GetPrice()`
  - `ItemId_GetHoldEffect()`
  - `ItemId_GetPocket()`
  - `ItemId_GetType()`
  - `ItemId_GetFieldFunc()`
  - `ItemId_GetBattleFunc()`

**Out-of-battle item behavior**
- `src/item_use.c`

**Item effects on Pokémon**
- `src/data/pokemon/item_effects.h`
- `include/constants/item_effects.h`

**Bag storage / capacity**
- `include/constants/global.h`
- `include/global.h`
- `src/item.c`

## TM / HM system

**Item definitions and move mapping**
- `include/constants/items.h`
- `src/data/items.json`
  - TM entries use `moveId` to map the TM item to a move

**TM Case UI / flow**
- `src/tm_case.c`
  - reads TM Case pocket
  - invokes `ItemIdToBattleMoveId(itemId)`
  - routes field use through `ItemUseCB_TMHM`

**TM/HM item recognition / party-use routing**
- `src/item_use.c`
  - `CheckIfItemIsTMHMOrEvolutionStone()`
  - TM/HM entries route to the party menu

**Compatibility matrix**
- `src/data/pokemon/tmhm_learnsets.h`
  - `sTMHMLearnsets[][2]`
  - `TMHM_LEARNSET(...)`
  - baseline storage is two 32-bit words per species

**Compatibility runtime**
- `src/pokemon.c`
  - `CanMonLearnTMHM(struct Pokemon *mon, u8 tm)`
  - indices 0–31 use word 0; indices 32+ use word 1

**TM Case bag capacity**
- `include/constants/global.h`
  - baseline `BAG_TMHM_COUNT = 58` (50 TMs + 8 HMs)

Changes that expand the machine count can therefore touch more than item data: item constants/data, TM Case/UI assumptions, compatibility bit capacity, save/bag capacity, and any helper that converts item IDs to move IDs.

## Moves / battle move data

**Move IDs**
- `include/constants/moves.h`

**Move effects**
- `include/constants/battle_move_effects.h`

**Move data**
- `src/data/battle_moves.h`

**Move names / descriptions**
- `src/data/text/move_names.h`
- `src/move_descriptions.c`

**Battle scripting**
- `data/battle_scripts_1.s`
- `data/battle_scripts_2.s`
- `src/battle_script_commands.c`
- `include/constants/battle_script_commands.h`

**Battle animation scripts**
- `data/battle_anim_scripts.s`
- `src/battle_anim*.c`

## Wild encounters

**Authoring data**
- `src/data/wild_encounters.json`
  - map key
  - base label
  - land/water/rock-smash/fishing encounter sections
  - encounter rates
  - per-slot min/max levels and species

**Generated runtime table**
- `src/wild_encounter.c` includes generated `data/wild_encounters.h`

**Runtime encounter logic**
- `src/wild_encounter.c`
  - `ChooseWildMonIndex_Land()`
  - `ChooseWildMonIndex_WaterRock()`
  - `ChooseWildMonIndex_Fishing()`
  - `ChooseWildMonLevel()`
  - `GetCurrentMapWildMonHeaderId()`
  - `GenerateWildMon()`
  - `TryGenerateWildMon()`
  - fishing generation and encounter-rate tests

**Related presentation / Pokédex area logic**
- `src/wild_pokemon_area.c`
- `include/wild_encounter.h`
- `include/wild_pokemon_area.h`

For ordinary encounter-distribution edits, `src/data/wild_encounters.json` is the primary data surface; engine files should only change when encounter behavior itself changes.

## Trainers

**Trainer records**
- `src/data/trainers.h`
  - `gTrainers[]`
  - trainer class, encounter music/gender, trainer pic, name, items, AI flags, party flags, party pointer

**Party definitions**
- `src/data/trainer_parties.h`
  - static party arrays using the trainer-mon structures appropriate to items/custom moves/default moves

**Trainer constants / classes**
- `include/constants/trainers.h`
- `include/constants/trainer_types.h`
- `include/constants/opponents.h` where present in project branches

**Battle setup / execution**
- `src/battle_setup.c`
- `src/trainer_see.c`
- `src/battle_main.c`
- `include/battle_setup.h`
- `include/trainer_see.h`

**Trainer graphics**
- `src/data/trainer_graphics/`
- `src/trainer_pokemon_sprites.c`
- `include/trainer_front_sprites.h`

Map scripts invoke trainers through event-script trainer battle commands; a trainer implementation may therefore span map scripts + constants + trainer record + party + graphics.

## Save / persistent state

**Persistent structures**
- `include/global.h`
  - `struct SaveBlock2`
  - `struct SaveBlock1`
  - `struct BoxPokemon` / `struct Pokemon` definitions and storage relationships
  - `SaveBlock1` contains player party, item pockets, flags and vars
  - `SaveBlock2` contains player/profile/system state

**RAM save-block ownership / pointer relocation**
- `src/load_save.c`
  - `gSaveBlock1`, `gSaveBlock2`
  - `gSaveBlock1Ptr`, `gSaveBlock2Ptr`
  - `SetSaveBlocksPointers()`
  - `MoveSaveBlocks_ResetHeap()`
  - `SavePlayerParty()`, `LoadPlayerParty()`
  - `SaveSerializedGame()`, `LoadSerializedGame()`
  - bag load/save helpers

**Flash sector layout / serialization**
- `src/save.c`
  - `sSaveSlotLayout`
  - SaveBlock2 occupies its save sector
  - SaveBlock1 spans the configured SaveBlock1 sectors
  - compile-time size assertions protect sector capacity
  - sector write/read/checksum/recovery logic

**Flags / vars**
- persistent arrays are part of `SaveBlock1`
- event access is through the event-data system and constants in `include/constants/flags.h` / `include/constants/vars.h`

Any hack that adds persistent fields must audit structure size, offsets, serialization layout, compatibility assumptions, and save/load QA.

## Maps / event scripting

**Map scripts and text**
- `data/maps/<MapName>/scripts.inc`
- `data/maps/<MapName>/text.inc`
- map JSON and layout data under `data/maps/` and `data/layouts/`

**Global scripts**
- `data/event_scripts.s`
- `data/scripts/`
- `data/specials.inc`

**Script command runtime**
- `src/scrcmd.c`
- `src/script_pokemon_util.c`
- `include/script_pokemon_util.h`

This is the primary surface for story events, one-time gifts, state gates, map transitions and trainer-battle invocation.

## Graphics

**Pokémon graphics tables**
- `src/data/pokemon_graphics/front_pic_table.h`
- `src/data/pokemon_graphics/back_pic_table.h`
- `src/data/pokemon_graphics/front_pic_coordinates.h`
- `src/data/pokemon_graphics/back_pic_coordinates.h`
- `src/data/pokemon_graphics/palette_table.h`
- `src/data/pokemon_graphics/shiny_palette_table.h`
- `src/data/pokemon_graphics/footprint_table.h`
- `src/data/pokemon_graphics/enemy_mon_elevation.h`

**Trainer graphics**
- `src/data/trainer_graphics/`

**Raw assets**
- `graphics/`

## How future projects should use this index

Do not rescan these baseline locations for every new FireRed hack. Start with this index, verify the project's baseline commit, and then record only the project's deltas.

A full generic rescan is needed only if the project uses a materially different pokefirered baseline or an engine refactor changes these surfaces.
