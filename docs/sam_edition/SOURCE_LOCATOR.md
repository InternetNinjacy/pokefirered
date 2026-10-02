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

- `sam/enc-003-surf-fishing-finalization`
- production head: `6e84b85cf47ad76fe81bf5d27a5aac1da127d79a`
- draft PR: #72
- base branch: `sam/enc-001-nosepass-feebas-final-tables` / draft PR #69

Focused QA branch:

- `qa/enc-003-surf-fishing-finalization`
- QA source: `58cce3b6f53505bba929f07179cf23917694e844`
- successful run: `37006884530`
- QA ROM SHA-1: `0a02ff27d52fdf6e7100178de438dd10d61ecfdd`

This is the current delta-only production continuation point. PR #72 is stacked on verified ENC-001 PR #69. QA branches are evidence/instrumentation only and must not be used as production ancestors. BREED PR #66 is explicitly blocked and is not a valid production continuation point.

ENC-003 is verified partial: 20 source-supported FireRed Surf/fishing tables are implemented and QA-passed. The remaining Seven Island shoreline entry is blocked because FireRed has no existing `MAP_SEVEN_ISLAND` wild header and current authority supplies no encounter-rate value; do not infer one.

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
