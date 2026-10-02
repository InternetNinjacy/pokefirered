# Pokémon: Sam Edition — Branch / Source-Surface Index

Framework baseline: `docs/fire_red_framework/FIRERED_SOURCE_LOCATOR.md`
Comparison base used for this pass: `sam-edition-dev`
Live `sam-edition-dev` head at framework initialization: `1ac7382fd5ecb34cb2de6bdf5bba8e7fcf08e869`

This file records verified Sam-specific implementation surfaces. It is not a status authority and does not replace the Programming Readiness Registry.

## Current verified production continuation tip

Branch: `sam/train-002-003-focused-corrections`  
Draft PR: #73  
Production head: `5b1bde65e321f09a5895a8a4b99f26cd7784d359`  
Base: `sam/enc-003-surf-fishing-finalization` / draft PR #72

Production work should continue delta-only from this head or a later documented verified production descendant. The isolated QA branch `qa/train-002-003-focused-corrections` / draft QA PR #74 is evidence/instrumentation only and is not a production ancestor. BREED PR #66 remains blocked and must not become production ancestry.

TRAIN-002 and TRAIN-003 are COMPLETE at this tip. ENC-003 remains verified partial: its 20 source-supported FireRed Surf/fishing tables remain inherited and QA-passed, while Seven Island shoreline remains blocked because FireRed has no existing `MAP_SEVEN_ISLAND` wild header and current authority supplies no encounter-rate value.

## TRAIN-002/003 focused corrections — complete

Production branch: `sam/train-002-003-focused-corrections`  
Draft PR: #73  
Production head: `5b1bde65e321f09a5895a8a4b99f26cd7784d359`  
Parent: `sam/enc-003-surf-fishing-finalization` / draft PR #72

Unique production surfaces:

- `src/data/trainer_parties.h`
- `src/data/trainers.h`

Verified scope:

- S.S. Anne Gentleman Thomas compiles as Growlithe Lv18 / Lickitung Lv18 / Persian Lv20 and remains a Single Battle.
- Mt. Moon Bug Catcher Kent compiles as a Double Battle with Weedle Lv11 / Kakuna Lv11 and the exact approved custom moves, including Fury Cutter.
- Bug Bite is not introduced by the production delta.
- Adjacent Bug Catcher Robby remains a Single/default-moves regression control.

Production CI: `37008464595` — compile/link/ELF/GBA/SYM succeeded; only stock-ROM SHA comparison failed.

QA branch: `qa/train-002-003-focused-corrections`  
Draft QA PR: #74  
QA source: `aef75c74110bc6ecb7608d50a9d3353ed708943b`  
Run: `37016542530`  
QA ROM SHA-1: `33f7f9c71db9347328d7e2cbcaf1526ad0374fe9`

The first QA attempt failed only in a QA-side source-parser boundary before build/runtime. The harness was corrected on the QA branch; production PR #73 was unchanged. QA PR #74 is evidence only and must never be used as production ancestry.

## ENC-001 completed locked packet

Production chain:

- PR #67: `sam/enc-001-ralts-natu-final-tables` @ `1e03ef56cc063e3f9a2888640ec760e4d23d4c8a`
- PR #69: `sam/enc-001-nosepass-feebas-final-tables` @ `9c2ffa3c8fcff5445cbcf9778cb9e766ae7e534a`

Verified production surfaces:

- `src/data/wild_encounters.json`
- `src/wild_encounter.c` (Route 6-only exact Surf/fishing selector; global weights unchanged)

PR #67 QA: run `37004528658`, QA source `08533e014c8040502ed6f3aa5e5e3f3943562ac0`, ROM `e554917c75f6500a919e2f1862598340b70b7f65`.

PR #69 QA: run `37005383850`, QA source `c96ab7f8e70da3036574b6eeb5e090f9ae9cc2b8`, ROM `32d85fc0f0fdb208fe367fc19a7dd4d73dc921f9`.

Current locked packet result: Ralts/Natu/Nosepass/Feebas focused encounter programming is complete. Route 6 requires the local selector because native Good Rod has only three 60/20/20 slots and cannot directly express the locked four-species 40/30/20/10 table. This exception is Route 6-only.

## ENC-003 Surf/fishing finalization — verified partial

Production branch: `sam/enc-003-surf-fishing-finalization`  
Draft PR: #72  
Production head: `6e84b85cf47ad76fe81bf5d27a5aac1da127d79a`  
Parent: `sam/enc-001-nosepass-feebas-final-tables` / draft PR #69

Unique production surface:

- `src/data/wild_encounters.json`

Verified scope:

- 20 FireRed Sevii/Cerulean water/fishing entries encoded from Surf/Fishing Finalization v1.0.
- Native slot ordering remains unchanged.
- Existing per-map encounter-rate values are preserved.
- Land tables, all LeafGreen entries, Route 6's PR #69 local Feebas selector and `src/wild_encounter.c` global/native selectors are unchanged.
- No `MAP_SEVEN_ISLAND` wild header was created because no authoritative encounter-rate value exists for that missing source header.

Production CI: `37006480220` — compile/link/ELF/GBA/SYM succeeded; only stock-ROM SHA comparison failed.

QA branch: `qa/enc-003-surf-fishing-finalization`  
QA source: `58cce3b6f53505bba929f07179cf23917694e844`  
Run: `37006884530`  
QA ROM SHA-1: `0a02ff27d52fdf6e7100178de438dd10d61ecfdd`

Runtime QA inspected compiled `gWildMonHeaders` and verified exact species, levels, slot order and preserved encounter rates for all 20 implemented maps.

ENC-003 remains IN PROGRESS pending Seven Island shoreline header/rate resolution.

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

### Current-stack CORE-001–004 reconciliation

Production branch: `sam/core-001-004-current-stack-integration`  
Draft PR: #63  
Production head: `0b7f1481134d13fbcdea90b7fb99edb01ce3b639`  
Base: `sam/gift-001-npc-trades` / draft PR #62

Verified production delta relative to PR #62 is limited to:

- `src/oak_speech.c`
- `include/pokemon.h`
- `include/constants/pokemon.h`
- `src/pokemon.c`
- `src/script_pokemon_util.c`
- `src/battle_controller_player.c`
- `src/evolution_scene.c`
- `data/specials.inc`
- `data/maps/PalletTown_ProfessorOaksLab/scripts.inc`

The current Starter path is reconciled as `GiveSamStarter -> MarkSamOriginalStarter`; the obsolete vanilla `givemon` insertion was not copied over the newer Starter implementation.

Production CI run `36957629488` compiled, linked, generated ELF/GBA/SYM, and stopped only at the expected stock-ROM SHA comparison.

Isolated QA branch: `qa/core-001-004-current-stack-runtime`  
QA source: `59ce704108a16559047737d25723c663a6dc3188`  
Runtime run: `36958060624`  
QA ROM SHA-1: `a55794ae62ed5295a3c0bd2baf22e9ca10918d40`

The QA branch is a clean descendant of production and changes only four QA/instrumentation files. It is not a production ancestor.

Runtime QA passed all six starter×mode paths, both mode states through real save/fresh-process reload, exact individual death/protection, evolution retention, Adaptive Gene, PC round-trip, common healing/revive restrictions, Standard regression, and authored-OT IMUGI integrity.

CORE-001 remains QA pending one real human interactive selector smoke. CORE-002/003/004 remain COMPLETE.

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

### GIFT-001 nine standard NPC trades

Branch: `sam/gift-001-npc-trades`  
Draft PR: #62  
Verified production head: `76ed58d096e88f4beb898c944d69c61760f15d35`  
Parent: `sam/gift-001-002-special-acquisition-core`

Verified unique production surfaces relative to PR #60:

- trade package data:
  - `include/constants/trade.h`
  - `src/data/ingame_trades.h`
- in-game trade runtime:
  - `src/trade_scene.c`
- nine trade-script bindings:
  - `data/maps/Route2_House/scripts.inc`
  - `data/maps/CeruleanCity_House3/scripts.inc`
  - `data/maps/UndergroundPath_NorthEntrance/scripts.inc`
  - `data/maps/VermilionCity_House2/scripts.inc`
  - `data/maps/Route11_EastEntrance_2F/scripts.inc`
  - `data/maps/Route18_EastEntrance_2F/scripts.inc`
  - `data/maps/CinnabarIsland_PokemonLab_Lounge/scripts.inc`
  - `data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/scripts.inc`
- IMUGI dialogue:
  - `data/maps/VermilionCity_House2/text.inc`

Runtime QA branch: `qa/gift-001-npc-trades-runtime`  
QA source: `c0dbfdc18492a8893aa10a28ca549cea079c3841`  
GitHub Actions run: `36956041525`  
QA ROM SHA-1: `54b28df3645156de944f983864111633b0c7868a`

The runtime QA passed all nine fixed packages, invalid/egg/empty selection rejection, six-Pokémon full-party replacement, all nine one-time flags, real save/reload, and outsider ownership through IMUGI evolution. QA also exposed a real Gen III encryption-key defect in authored-OT creation; the verified production fix creates the Pokémon with the authored OT ID from the start rather than overwriting OT ID after encrypted substructure creation.

PR #62 remains draft/open/unmerged. It is an earlier verified gameplay-stack layer; the current continuation tip is the verified PR #65 production head documented above.

## Encounter distribution

### Current verified Ralts/Natu packet

Production branch: `sam/enc-001-ralts-natu-final-tables`  
Draft PR: #67  
Production head: `1e03ef56cc063e3f9a2888640ec760e4d23d4c8a`  
Base: `sam/evol-001-003-accessibility` / draft PR #65

Unique production surface:
- `src/data/wild_encounters.json`

Focused QA branch: `qa/enc-001-ralts-natu-final-tables`  
QA source: `08533e014c8040502ed6f3aa5e5e3f3943562ac0`  
Run: `37004528658`  
QA ROM SHA-1: `e554917c75f6500a919e2f1862598340b70b7f65`

Verified tables:
- Route 5: Ralts 10% at the current-authority level range.
- Route 16: Natu 8% and Eevee 2%.
- Berry Forest: Kirlia 5% preserved in the native-slot realization.
- Ruin Valley: Natu 10%, Nosepass 5%, Xatu 5% preserved in the native-slot realization.

The production delta is exactly one encounter data file. Focused QA validates native slot weights/rates/levels and a clean modified-ROM build.

ENC-001 remains IN PROGRESS. Feebas and Rock Tunnel Nosepass still require reconciliation. The historical branch `sam/enc-001-nosepass-rock-tunnel` contains an older 4% Rock Tunnel realization and must not be merged verbatim because current authority requires 5% Lv24–26.

Ordinary Sam encounter-distribution changes should generally remain data-only unless the governing authority requires behavior changes.

## TM-003 Signal Beam special-class override

Production branch: `sam/tm-003-signal-beam-special-class`  
Draft PR: #64  
Production head: `fb9ba45065d6e87b28db24d76e800e57f72a7594`  
Base: `sam/core-001-004-current-stack-integration` / draft PR #63

Verified unique production surfaces:

- `src/pokemon.c`
- `src/battle_script_commands.c`

The delta extends the existing Ghostly Wail move-level Special-class pattern to Signal Beam. Signal Beam remains Bug-type; other Bug moves remain Gen III physical. Production CI run `36960016126` generated the modified ROM before the expected stock-ROM SHA mismatch.

Runtime QA branch: `qa/tm-003-signal-beam-special-class`  
QA source: `a724e917f639e1cb19e67a3e8909f1f926def0be`  
Runtime run: `36960213040`  
QA ROM SHA-1: `791c217ab9a6596e3447a910f1ad61a9d93b26c5`

## EVOL-001–003 evolution accessibility

Production branch: `sam/evol-001-003-accessibility`  
Draft PR: #65  
Production head: `60caa7ffdf2730bcd75c630c2f421cc30b554711`  
Base: `sam/tm-003-signal-beam-special-class` / draft PR #64

Verified production surfaces:

- `include/constants/items.h`
- `src/data/item_icon_table.h`
- `src/data/items.json`
- `src/data/pokemon/evolution.h`
- `src/data/pokemon/item_effects.h`
- `src/party_menu.c`

Verified implementation:
- EVOL-001: pure-trade Kadabra/Machoke/Graveler routes are Lv42; the already-correct Haunter Lv42 route is preserved.
- EVOL-002: authorized King's Rock, Metal Coat, Dragon Scale, Up-Grade, and Protector routes use the ordinary item-evolution path; `ITEM_PROTECTOR=246` is the allocated item; stock National-Dex blocking is removed for these deterministic Sam routes.
- EVOL-003: current fixed-level friendship/Beauty replacements are encoded. Conditional Clamperl methods remain untouched.

Production CI run `36961159729` generated the modified ROM before the expected stock-ROM SHA mismatch.

Runtime QA branch: `qa/evol-001-003-accessibility`  
QA source: `fdc3b14b0551772ba8b32d96324e7faa32bdaf8c`  
Runtime run: `36961288046`  
QA ROM SHA-1: `5c1c083070867654ae5625bcdb15c0e161242582`

The QA branch is one instrumentation-only commit ahead of production and is not a production ancestor. QA-004 is PASS for the current authority/roster scope.

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

Canonical branches:
- `sam/tmcomp-part1-kanto-final-matrix` / draft PR #47
- `sam/tmcomp-part2-final-roster-extensions` / draft PR #48
- canonical Part 2 head: `10e48e687a414f621a554796aaff2c277d935b1f`

Primary compatibility data surface:
- `src/data/pokemon/tmhm_learnsets.h`

Current verified production PR #65 is a descendant of PR #48 and still contains the exact canonical compatibility blob `38e36d942662a38c864cf99c270fd64ede18490d`. Therefore TM-004/TM-005 required no additional production delta.

Runtime/static QA branch: `qa/tm-004-005-compatibility`  
QA source: `b8a6dc980bbe306d4b49724f55561069ca807bdc`  
Run: `36962584342`  
QA ROM SHA-1: `28e65e065e466a0973843bc6985eeaa2fb6b8f69`

QA verified all 68 TM move mappings, all 8 HM indexes/boundaries, Ditto/Mew all-TM handling, exact representative current specialist rows, and no active-source TM69–TM79 numbering. TM-004 and TM-005 are COMPLETE; QA-005 is PASS. The QA branch is evidence-only.

The branch lineage also contains broader TM/species integration changes. Isolate historical compatibility deltas by comparing each TM-COMP branch to its immediate parent rather than to `sam-edition-dev`.

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
