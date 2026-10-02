# Pokémon: Sam Edition — Branch / Source-Surface Index

Framework baseline: `docs/fire_red_framework/FIRERED_SOURCE_LOCATOR.md`
Comparison base used for this pass: `sam-edition-dev`
Live `sam-edition-dev` head at framework initialization: `1ac7382fd5ecb34cb2de6bdf5bba8e7fcf08e869`

This file records verified Sam-specific implementation surfaces. It is not a status authority and does not replace the Programming Readiness Registry.

## Starter System production bundle

Branch: `sam/start-001-004-starter-system`
Known production head: `2525442045c69501c5574a3827ebed7921c3b841`
Draft PR: #59
Base: `sam/spec-009-part4-evolution-integration`

Verified changed surfaces relative to `sam-edition-dev` include:

- starter/event flow:
  - `data/maps/PalletTown_ProfessorOaksLab/scripts.inc`
  - `data/maps/PalletTown_ProfessorOaksLab/text.inc`
- starter-related distribution/shop scripts:
  - `data/maps/CeladonCity_DepartmentStore_4F/scripts.inc`
  - `data/maps/PewterCity_Mart/scripts.inc`
  - `data/maps/ViridianCity_Mart/scripts.inc`
- constants:
  - abilities, battle move effects, flags, items, moves, opponents, Pokémon methods, vars
- save/data structures:
  - `include/global.h`
- item/TM/evolution/species data:
  - `src/data/items.json`
  - `src/data/pokemon/evolution.h`
  - `src/data/pokemon/item_effects.h`
  - `src/data/pokemon/species_info.h`
  - `src/data/pokemon/tmhm_learnsets.h`
  - level-up learnset and Pokédex text surfaces
- runtime:
  - `src/item.c`
  - `src/item_menu.c`
  - `src/party_menu.c`
  - `src/pokemon.c`
  - `src/script_pokemon_util.c`
  - `src/tm_case.c`
  - `src/battle_script_commands.c`
- trainer data:
  - `src/data/trainers.h`
  - `src/data/trainer_parties.h`

Runtime QA branch: `qa/start-001-004-runtime`

## Species / evolution integration chain

### `sam/spec-009-part4-evolution-integration`

This branch is a broad integration base. Verified touched surfaces include:

- `include/constants/{abilities,battle_move_effects,flags,global,items,moves,opponents,pokemon,vars}.h`
- `include/global.h`
- `src/data/items.json`
- `src/data/pokemon/evolution.h`
- `src/data/pokemon/{level_up_learnsets,level_up_learnset_pointers,species_info,tmhm_learnsets}.h`
- Pokédex text
- `src/item.c`
- `src/party_menu.c`
- `src/pokemon.c`
- `src/tm_case.c`
- move/battle data and trainer records

### `sam/spec-009-custom-species-integration`

Narrow verified custom-species data surfaces:

- `src/data/pokemon/species_info.h`
- `src/data/pokemon/level_up_learnsets.h`
- `src/data/pokemon/level_up_learnset_pointers.h`

### `sam/arch-004-species-append`

At this scan it is behind `sam-edition-dev` with no unique changed files in the compare result. Do not treat the branch name alone as evidence of current implementation.

## Resource constants

Branch: `sam/arch-005-resource-constants`

Verified unique surfaces:

- `include/constants/abilities.h`
- `include/constants/items.h`
- `include/constants/moves.h`

This is allocation/constants scope; it is not by itself proof of full behavior.

## Permanent Mode / per-Pokémon persistent state

### CORE-001

Branch: `sam/core-001-mode-selection-integration`

Verified unique surfaces:
- `src/oak_speech.c`
- `.github/workflows/core001-mode-qa.yml`

### CORE-002 / CORE-003

Branch: `sam/core-002-003-permanent-mon-state`

Verified surfaces:
- `include/constants/pokemon.h`
- `include/pokemon.h`
- `src/pokemon.c`
- `src/battle_controller_player.c`
- `src/evolution_scene.c`
- `src/script_pokemon_util.c`
- `data/specials.inc`
- Pallet Lab starter script

### CORE-004

Branch: `sam/core-004-healing-revival`

Builds on the same core surfaces as CORE-002/003, adding healing/revival enforcement in the relevant runtime paths.

## Special acquisition / gift core

Branch: `sam/gift-001-002-special-acquisition-core`

Verified additional/shared surfaces include:

- `asm/macros/event.inc`
- `src/scrcmd.c`
- `src/script_pokemon_util.c`
- `include/script_pokemon_util.h`
- map/shop/starter scripts
- `src/data/trainers.h` and `trainer_parties.h`
- the integrated species/item/TM/evolution runtime surfaces inherited on this branch

Because this branch is an integration descendant, changed-file lists include inherited work. Use per-commit or parent comparison when isolating only GIFT logic.

## Encounter distribution

Branch: `sam/enc-001-nosepass-rock-tunnel`

Narrow verified surface:
- `src/data/wild_encounters.json`

This is a useful pattern: ordinary Sam encounter-distribution changes should generally stay data-only unless behavior changes.

## TM core and compatibility

### Machine mapping

Branch: `sam/tmcore-part1-machine-mapping`

Verified TM-related surfaces include:
- `include/constants/items.h`
- `include/constants/moves.h`
- `include/constants/global.h`
- `src/data/items.json`
- `src/data/item_icon_table.h`
- `src/item.c`
- `src/party_menu.c`
- `src/pokemon.c`
- `src/tm_case.c`
- move/species/evolution data inherited in the integration chain
- `src/save.c` appears in this branch lineage and must be checked when machine-capacity changes affect persistent structures

### Compatibility capacity

Branch: `sam/tmcore-part2-compatibility-capacity`

Adds/touches:
- `src/data/pokemon/tmhm_learnsets.h`
- the same TM runtime/capacity surfaces above

### Compatibility matrix

Branches:
- `sam/tmcomp-part1-kanto-final-matrix`
- `sam/tmcomp-part2-final-roster-extensions`

Primary compatibility data surface:
- `src/data/pokemon/tmhm_learnsets.h`

The branch lineage also contains broader TM/species integration changes. Isolate a compatibility-only change by comparing to its immediate parent rather than to `sam-edition-dev`.

## Opening / intro

Branch: `sam/opening-intro`

Verified surfaces:
- `data/text/new_game_intro.inc`
- `src/new_game.c`
- `src/oak_speech.c`
- `src/title_screen.c`
- `include/constants/vars.h`
- `include/event_scripts.h`
- `include/global.h`
- Oak-speech character graphics
- Sam title-screen graphics

## League integration

Branch: `sam/league-phase5-integration`

Verified broad surfaces include:
- Pokémon League map scripts/text/maps
- `src/data/trainers.h`
- `src/data/trainer_parties.h`
- trainer/opponent/flag/item constants
- `src/battle_main.c`
- `src/battle_message.c`
- `src/battle_script_commands.c`
- `src/battle_setup.c`
- `src/pokemon.c`
- `src/save.c`
- tileset data
- League installation/verification tooling under `tools/sam_league_phase5/`

This branch is a large integration branch and must not be treated as a narrow source locator for one feature.

## Practical lookup rules

When a future Sam task references:

- **species stats/types/abilities** → start at `src/data/pokemon/species_info.h`
- **level-up moves** → `level_up_learnsets.h` + pointer table
- **evolution method/data** → `include/constants/pokemon.h` + `evolution.h` + `GetEvolutionTargetSpecies()`
- **new/evolution item** → item constant + `items.json` + item-use/evolution runtime as needed
- **TM mapping** → item constants + `items.json` + `tm_case.c`
- **TM compatibility** → `tmhm_learnsets.h` + `CanMonLearnTMHM()`
- **wild placement** → `src/data/wild_encounters.json`
- **trainer team** → `trainer_parties.h` + `trainers.h`
- **trainer event** → trainer data + map script
- **starter flow** → Pallet Lab scripts/text first, then Sam runtime helpers
- **persistent gameplay state** → `include/global.h` / Pokémon structure + save/load surfaces
- **new story state** → flags/vars + map/global scripts, auditing persistence and allocation authority

## Maintenance rule

After a feature is merged and QA-passed, update this index with its final integrated source locations and remove obsolete branch-only caveats. This converts branch-discovery knowledge into durable project knowledge.
