# Pokémon: Sam Edition — Source Locator

This file is the human-readable companion to `PROGRAMMING_INDEX.yaml`.

It maps gameplay/programming concepts to verified source locations so future tasks can start with delta verification instead of repeating a full source audit.

## Rules

- Record only locations verified in source.
- Record the ref/commit used for verification.
- Do not infer implementation from design documentation.
- Do not treat a feature branch as integrated merely because code exists there.
- Update entries when a merge or refactor changes source surfaces.
- Keep Pokémon: Weather source evidence separate from Sam Edition.

## Current seeded entries

### Programming control surfaces

Verified on: `sam-edition-dev`

- `docs/sam_edition/IMPLEMENTATION_WORKFLOW.md`
- `docs/sam_edition/IMPLEMENTATION_BACKLOG.md`
- `docs/sam_edition/SOURCE_IMPLEMENTATION_AUDIT_2026-09-30.md`
- `docs/sam_edition/BASELINE.md`

### Current verified programming continuation tip

Production branch:

- `sam/gift-001-remaining-special-acquisitions`
- production head: `b1427e3700dc34514cfd134aaa14d82d2c651e72`
- draft PR: #88
- direct base: `sam/gift-001-starter-family-gifts` / draft PR #86 @ `be0c6ab2500f188ce20d49ae69b66f028dea332b`
- QA PR #87 remains evidence-only and is not production ancestry

PR #88 is the current delta-only production continuation. CI run `37066177714` compiled, linked, generated ELF/GBA/SYM, and stopped only at the expected stock FireRed SHA comparison; this matches the project’s existing modified-ROM production criterion.

### Group 2 — Special Acquisitions current source-routing state

Status: **POC COMPLETE**. Synchronized through Programming Readiness checkpoint `SYNC-2026-10-02-018`.

Production:
- branch: `sam/gift-001-remaining-special-acquisitions`
- draft PR: #88
- production head: `9ff410a1dfcdba149721e8c9b5dc7fba9b8fd0e0`
- base: `sam/gift-001-starter-family-gifts` / draft PR #86
- production CI: `37069196924`
- result: compile/link/ELF/GBA/SYM succeeded; only the expected modified-ROM stock FireRed SHA comparison failed
- PR #88 remains draft/open/unmerged

Final evidence-only QA:
- branch: `qa/gift-001-group2-final-runtime`
- draft PR: #90
- QA source: `26c2ed84ef6a486a91679f103a6de7e50ee3f483`
- run: `37069227822` — PASS
- QA ROM SHA-1: `d59142366a786b9a04c22e877bfb6a58a6456c6d`
- QA PR #90 must never become production ancestry
- earlier QA PRs #87/#89 remain evidence-only and must never become production ancestry

Current central resources:
- OT 52005 LUNA — Cleffa
- OT 52006 MELODY — Igglybuff
- OT 52007 SILPH — shared Silph identity for Silph Lapras / Rock Tunnel Porygon
- OT 52008 VENDOR — Route 4 purchased Magikarp
- OT 52009 CELADON — Game Corner Pokémon prizes
- OT 52010 LAB — Cinnabar fossil revivals
- next free authored Gift OT ID: 52011
- flags 0x373 / 0x374 / 0x375 / 0x376 — Cleffa / Igglybuff / Elekid Egg / Rock Tunnel Porygon

Verified production source surfaces:
- `include/constants/trade.h`
- `include/constants/flags.h`
- `include/script_pokemon_util.h`
- `data/specials.inc`
- `src/script_pokemon_util.c`
- `data/maps/Route4_PokemonCenter_1F/*`
- `data/maps/LavenderTown_PokemonCenter_1F/*`
- `data/maps/CeladonCity_GameCorner_PrizeRoom/scripts.inc`
- `data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/scripts.inc`
- `data/maps/SilphCo_7F/scripts.inc`
- `data/layouts/CeladonCity/map.bin`
- `data/maps/CeladonCity/map.json`
- `data/maps/CeladonCity_SurfHouse/map.json`
- `data/maps/CeladonCity_SurfHouse/scripts.inc`
- `data/maps/CeladonCity_SurfHouse/text.inc`
- `data/maps/map_groups.json`
- `data/event_scripts.s`

Implemented and QA-proven:
- LUNA Cleffa Lv8 one-time authored outsider Gift
- MELODY Igglybuff Lv18 one-time authored outsider Gift with Soothe Bell
- NORA Elekid one-time player-owned Gift Egg in a Surf-only Celadon house
- authored outsider conversion for purchased Magikarp, all current FireRed Game Corner prizes, Cinnabar fossil revivals, and Silph 7F Lapras
- party delivery, PC fallback, full-storage retry/failure safety, claim persistence and duplicate prevention
- success-only money/coin transaction ordering
- no false Pokédex caught state on failed outsider delivery
- Elekid player OT/ownership path and global exact 50% shiny Egg source path
- actual Celadon block-data geometry/warp registration for the Surf House
- real save/fresh-process reload persistence

Owner-system handoffs:
- Cinnabar Magby Egg: acquisition contract/mechanics are closed; final reward hookup remains under Town Side Quests/Cinnabar.
- Rock Tunnel Porygon: package/resources are closed; final visible recovery event remains under Thomas/Team Rocket.
- Oak Research Milestones: Chansey/Dratini Gift contracts and OT OAK / 52004 are closed, but the milestone ladder/151 unlock remains later P5 Oak-system implementation and is blocked by TM-001; it consumes SYS-GIFT but is not Group 2 work.
- None of these owner-system items is a remaining Group 2 blocker.

Group 1 — Breeding remains POC COMPLETE. Group 2 remains permanently numbered Group 2 — Special Acquisitions and is now POC COMPLETE.

### Group 3 — Species current-stack reconciliation

Verified through production continuation `d2b66dfee8cfe576ac2b12341f1ebd70f4a90ab3` / draft PR #84.

- SPEC-004 Ghost Families is POC COMPLETE with no new production patch. The current stack already contains the approved Duskull/Dusclops and Shuppet/Banette packages and the later Design Closure Gastly/Haunter/Gengar package.
- For Gastly/Haunter/Gengar, the later supersession inside the current species authority controls over stale roadmap prose: baseline Attack values, shared natural progression, Lv25/Lv42 evolutions, exact Design Closure final-68 TM rows, no TM39 Will-O-Wisp, and no HM compatibility.
- Dusknoir remains unauthorized and absent.
- SPEC-005 Early Bug Final Evolutions is POC COMPLETE with no new production patch. Current source matches the locked 450-BST stats and exact post-redesign natural learnsets/TM rows for Butterfree, Beedrill, Beautifly, and Dustox; TM-003 supplies the already-complete Signal Beam Special-class override.
- QA-004 evolution remains PASS. QA-005 final TM/HM matrix remains PASS on run `36962584342`, including representative Ghost-family and Early-Bug rows.
- SPEC-006 Nosepass / Generation-I pure-Rock cleanup is POC COMPLETE. Evidence-only draft PR #80, `qa/spec-006-rock-runtime` @ `e297c5242b10b12fe4651e6af4b7c42f2c552bd5`, passed QA-ROCK-001 on run `37036207034`; QA ROM SHA-1 `ea945aeeb4d24b37a25e81e789ff02efae8ff11e`. Runtime proved the six targets are pure Rock, Steelix remains Steel/Ground, Ground STAB and Electric immunity are gone, Water/Grass are exactly 2x, and AI type calculation agrees. No production defect was found; QA PR #80 is not production ancestry.
- SPEC-007 Feebas / Milotic is POC COMPLETE with no production patch. Evidence-only draft PR #81, `qa/spec-007-feebas-milotic-runtime` @ `61580f505211e3900e6f59c48b9c5b67082c7dd1`, passed run `37045556350`; QA ROM SHA-1 `c05cc4fe6bb5052806e8d75ab20c03bdd4473538`. Static/runtime QA verified species data, Lv20 evolution and Water Pulse timing, exact TM/HM compatibility, Milotic Water/Psychic battle behavior, Pokédex mapping/metadata, and inherited Route 6 acquisition surfaces. No production defect was found; QA PR #81 is not production ancestry.
- SPEC-008 Legendary Birds is POC COMPLETE. Draft production PR #83, `sam/spec-008-legendary-birds-breeding-closure` @ `204fb8043736e20a45eaed5eff5a5e1fa8dac802`, fixes the one current-stack defect found by QA: father-side TM inheritance could contaminate the exact locked Lv5 bred opening sets. The fix suppresses inherited move additions only for Articuno/Zapdos/Moltres. Evidence-only draft PR #82 @ `df1ffbb678f0a99d598747845f2224c6d9e8df9e` passed run `37050108196`; QA ROM SHA-1 `d625890fc47f21127c41d50e0dc5c6f4e4e09229`. Runtime proved same-species bird Eggs from Ditto, bird/bird incompatibility, exact Lv5 bred sets and exact Lv50 static sets.
- SPEC-009 current-stack core advanced on draft production PR #84, `sam/spec-009-current-stack-core` @ `d2b66dfee8cfe576ac2b12341f1ebd70f4a90ab3`. Parts 1–4 remain inherited. Ectoceon now receives Soul Rot and custom cry placeholders now route Leafeon→Eevee, Ectoceon→Vaporeon and Rhyperior→Rhydon using the engine's zero-based cry IDs. Evidence-only draft PR #85 @ `9e1ad638030d21b2dbd76d3f961b452cf8b371e6` passed run `37051864520`; QA ROM SHA-1 `28ac40980514bc56668deabea9cabb3b1849290b`. Runtime proved the locked Soul Rot effect and all three cry routes. Overall SPEC-009 remains IN PROGRESS for Pokédex, ROM-ready assets, trade/transfer safety, bounds/save-load and final integrated QA.
- The next source-ready Species task is SPEC-011 final 205-entry player-facing Pokédex source implementation from production PR #84.

### TM-003 Signal Beam move-class override

Production branch: `sam/tm-003-signal-beam-special-class`  
Draft PR: #64  
Production head: `fb9ba45065d6e87b28db24d76e800e57f72a7594`

Verified narrow production surfaces:

- `src/pokemon.c`
- `src/battle_script_commands.c`

Signal Beam joins the existing Ghostly Wail move-level Special-class exception without changing Bug globally. Production CI `36960016126`; isolated runtime QA `36960213040`, QA source `a724e917f639e1cb19e67a3e8909f1f926def0be`, ROM SHA-1 `791c217ab9a6596e3447a910f1ad61a9d93b26c5`.

### EVOL-001–003 evolution accessibility

Production branch: `sam/evol-001-003-accessibility`  
Draft PR: #65  
Production head: `60caa7ffdf2730bcd75c630c2f421cc30b554711`

Verified production surfaces:

- `include/constants/items.h`
- `src/data/item_icon_table.h`
- `src/data/items.json`
- `src/data/pokemon/evolution.h`
- `src/data/pokemon/item_effects.h`
- `src/party_menu.c`

Production CI `36961159729`; isolated runtime QA `36961288046`, QA source `fdc3b14b0551772ba8b32d96324e7faa32bdaf8c`, ROM SHA-1 `5c1c083070867654ae5625bcdb15c0e161242582`. QA-004 is PASS for the current authority/roster scope. Conditional Clamperl trade-item methods remain intentionally untouched.

### TM-004–005 compatibility matrix

Canonical implementation branches:

- `sam/tmcomp-part1-kanto-final-matrix` / draft PR #47
- `sam/tmcomp-part2-final-roster-extensions` / draft PR #48
- canonical TM-COMP tip: `10e48e687a414f621a554796aaff2c277d935b1f`

Primary data/runtime surfaces:

- `src/data/pokemon/tmhm_learnsets.h`
- `src/pokemon.c` → `CanMonLearnTMHM()`
- `src/party_menu.c` → TM/HM logical-index/item/move mapping helpers
- `include/constants/global.h` → 68 TM / 8 HM capacity

Current production PR #65 inherits PR #48 and retains the exact canonical compatibility blob `38e36d942662a38c864cf99c270fd64ede18490d`; no forward production transplant is required.

Focused QA branch: `qa/tm-004-005-compatibility`  
QA source: `b8a6dc980bbe306d4b49724f55561069ca807bdc`  
Successful run: `36962584342`  
QA ROM SHA-1: `28e65e065e466a0973843bc6985eeaa2fb6b8f69`

QA-005 is PASS: all 68 TM mappings and all 8 HM indexes were exercised at runtime, exact representative later-specialist rows were checked, bounds were checked, and active source contains no TM69–TM79 numbering.

### Ralts / Natu focused encounter packet

Production branch: `sam/enc-001-ralts-natu-final-tables`  
Draft PR: #67  
Production head: `1e03ef56cc063e3f9a2888640ec760e4d23d4c8a`

Verified unique production surface:

- `src/data/wild_encounters.json`

Focused QA `37004528658` validates current native-slot rates/levels for Route 5, Route 16, Berry Forest and Ruin Valley. Broader ENC-001 remains open for Feebas and Rock Tunnel Nosepass reconciliation. The older standalone Nosepass 4% branch is stale against the current 5% authority and must not be reused verbatim.


### ENC-001 Nosepass / Feebas completion

Production branch: `sam/enc-001-nosepass-feebas-final-tables`  
Draft PR: #69  
Production head: `9c2ffa3c8fcff5445cbcf9778cb9e766ae7e534a`

Unique production surfaces:

- `src/data/wild_encounters.json`
- `src/wild_encounter.c`

The source delta replaces stale deeper Rock Tunnel data with the current 5% Nosepass table and implements exact Route 6 Feebas Surf/fishing rates. Route 6 uses a map-local selection override because the global native Good Rod has only three slots; all non-Route-6 maps continue using native global weights.

Focused QA branch: `qa/enc-001-nosepass-feebas-final-tables`  
QA source: `c96ab7f8e70da3036574b6eeb5e090f9ae9cc2b8`  
Successful run: `37005383850`  
QA ROM SHA-1: `32d85fc0f0fdb208fe367fc19a7dd4d73dc921f9`

ENC-001 is COMPLETE for the current Ralts/Natu/Nosepass/Feebas packet. Broader encounter implementation remains under ENC-002/ENC-003 and QA-013.

### ENC-003 Surf/fishing verified partial

Production branch: `sam/enc-003-surf-fishing-finalization`  
Draft PR: #72  
Production head: `6e84b85cf47ad76fe81bf5d27a5aac1da127d79a`

Verified production surface:

- `src/data/wild_encounters.json`

Twenty FireRed Sevii/Cerulean water/fishing entries are encoded from Surf/Fishing Finalization v1.0. Existing land tables, per-map encounter rates, LeafGreen entries, Route 6's local exact-rate selector, and global native slot logic are preserved.

Production CI `37006480220`; isolated runtime QA `37006884530`, QA source `58cce3b6f53505bba929f07179cf23917694e844`, ROM SHA-1 `0a02ff27d52fdf6e7100178de438dd10d61ecfdd`. Runtime QA inspected compiled `gWildMonHeaders` and verified all 20 implemented tables.

No `MAP_SEVEN_ISLAND` wild header was created because its encounter-rate value is not present in FireRed source or current authority. ENC-003 remains IN PROGRESS for that single shoreline gap.

### Starter System

Production branch:

- `sam/start-001-004-starter-system`
- known production head at framework initialization: `2525442045c69501c5574a3827ebed7921c3b841`
- draft PR: #59
- base branch: `sam/spec-009-part4-evolution-integration`

Runtime QA branch:

- `qa/start-001-004-runtime`

The detailed file/symbol locator for this system should be populated from the already-completed Starter implementation audit rather than reconstructed from scratch.

## Expansion procedure

When a system is next touched:

1. Load its existing audit/handoff.
2. Verify branch/PR heads.
3. Verify the recorded source files/symbols still exist.
4. Add missing verified locations here and to `PROGRAMMING_INDEX.yaml`.
5. Perform only the delta audit required by subsequent changes.

This makes each completed programming task improve the speed of the next one.


## Detailed indexes

- Generic FireRed engine map: `docs/fire_red_framework/FIRERED_SOURCE_LOCATOR.md`
- Sam implementation-branch surfaces: `docs/sam_edition/SAM_BRANCH_SURFACE_INDEX.md`

Use the generic map for stable FireRed engine locations, then the Sam branch index for project-specific deltas.
