# Pokémon: Sam Edition — Source-First Implementation Audit

**Audit date:** 2026-09-30  
**Branch used as integration baseline:** `sam-edition-dev`

## Authority rule

This document records implementation/source state only. It does **not** reopen closed design canon.

Use this order when judging implementation progress:

1. Current explicit project instruction and newest Sam Edition specialist authority govern design/canon.
2. Verified source state governs whether something is actually coded.
3. The Programming Readiness Registry remains the live task/status surface.
4. Older READY/BLOCKED labels must not be treated as proof that code is absent or present without checking source.
5. Pokémon: Weather branches (`weather-*`, `wth-*`) are a separate project and are never evidence of Sam Edition implementation.

## Integration baseline

`sam-edition-dev` is the consolidation target. During this audit it remained primarily baseline source plus project/programming documentation; major Sam Edition implementation work existed on feature branches.

## Substantially implemented but not fully integrated

### Pokémon League
- Branch: `sam/league-phase5-integration`
- PR: #12
- Audit state: 64 commits ahead of `sam-edition-dev`.
- Contains substantial League room, trainer, script, dialogue, save-layout, trainer-architecture, Blue/Green and related integration work.
- Remaining: consolidation with other Sam branches, allocation reconciliation, remaining hooks, build/runtime/emulator QA.

### Opening / title / mode selection
- Branch: `sam/opening-intro`
- Audit state: 33 commits ahead of `sam-edition-dev`.
- Contains the alternate-Kanto Oak intro/title presentation, Blue/Green naming support, persistent Green name, and Standard/Permanent mode selection/persistence.
- Remaining: reconcile with the newer shared save layout and integrate/build/runtime QA.

### Gym 2 — Cerulean
- Branch: `sam-gym2-cerulean-complete`
- Validation PR: #8
- Audit state: 68 commits ahead of the common baseline and 6 commits behind `sam-edition-dev`.
- Source includes the Cerulean Gym map, scripts, dialogue, trainer data/parties, trainer and overworld graphics, badge work, event/state constants and supporting code.
- Treat as **integration/reconciliation/QA**, not redesign or from-scratch Gym programming.

## Implemented narrow feature branches

### ARCH-005 resource constants
- Branch: `sam/arch-005-resource-constants`
- PR: #4
- Implements custom move IDs, TM51–TM68 item IDs, Brick, Adaptive Gene, Protector and Soul Rot allocations.
- Does **not** by itself implement the full 68-TM engine, move behavior/data or compatibility matrix.

### SPEC-006 Nosepass / Gen I Rock cleanup
- Branch: `sam/spec-006-nosepass-rock-cleanup`
- PR: #2
- Implements the locked Rock-type cleanup subpackage.
- Remaining: integration and regression; TM compatibility remains a separate responsibility.

### ENC-001 Nosepass Rock Tunnel
- Branch: `sam/enc-001-nosepass-rock-tunnel`
- PR: #3
- Implements the Nosepass Rock Tunnel encounter subpacket.
- Do not infer broad encounter completion from this isolated change.

## Gym implementation state

All eight Sam Edition Gym **designs are custom and closed unless a newer specialist authority explicitly says otherwise**. Vanilla FireRed code still occupying a Gym slot in `sam-edition-dev` is an old implementation placeholder, not the intended design.

| Gym | Source state on 2026-09-30 |
| --- | --- |
| Gym 1 — Pewter | Finalized design; no Sam-specific implementation branch/PR found; implementation still required |
| Gym 2 — Cerulean | Substantially implemented on `sam-gym2-cerulean-complete`; integration/QA remaining |
| Gym 3 — Vermilion | Finalized design; no Sam-specific implementation branch/PR found; implementation still required |
| Gym 4 — Celadon | Finalized design; no Sam-specific implementation branch/PR found; implementation still required |
| Gym 5 — Fuchsia | `sam-gym5-fuchsia` exists, but only a 3-commit resource scaffold; bulk implementation remains |
| Gym 6 — Saffron | Finalized design; no Sam-specific implementation branch/PR found; implementation still required |
| Gym 7 — Cinnabar | Finalized design; no Sam-specific implementation branch/PR found; implementation still required |
| Gym 8 — Viridian | Finalized design; no Sam-specific implementation branch/PR found; implementation still required |

### Gym 5 detail
`sam-gym5-fuchsia` was 3 commits ahead / 4 behind `sam-edition-dev` during this audit. Its diff was limited to opponent IDs, trainer constants and trainer-class naming. It is scaffolding, not a full Gym implementation.

### Gym 8 caution
The League branch contains ordinary global Giovanni/leader records and incidental Dragon Dance references. Those are **not** evidence that the finalized Sam Edition Viridian Gym has been implemented.

## Core-cast overworld art closure

For **Red, Blue, Green, Thomas and Satoshi**:
- visual design: CLOSED;
- approved individual overworld source art: CLOSED / APPROVED;
- regeneration/redesign: NOT REQUIRED;
- ROM-native conversion, graphics allocation, insertion, event hookup and in-game QA: OPEN.

Future work must use the approved source art as implementation input. Do not regenerate these five characters unless implementation exposes a genuine technical impossibility that requires an explicit reopen.

## Source-first continuation rule

Before declaring a Sam feature unimplemented:
1. inspect `sam-edition-dev`;
2. inspect active Sam-specific branches and PRs;
3. inspect large integration branches for buried implementation;
4. exclude all Pokémon: Weather branches;
5. only then classify the feature as genuinely still requiring programming.

Before declaring a feature finished:
1. distinguish code existing on a feature branch from code integrated into the consolidated tree;
2. verify build status;
3. verify runtime/emulator acceptance where required;
4. update the Programming Readiness Registry.

## Shared core-engine audit — 2026-09-30

### Permanent Mode
- `sam/opening-intro` already implements the Standard/Permanent selector and persists `VAR_SAM_GAME_MODE`.
- No downstream permanent-death mechanics were found: no per-Pokémon death marker, protected-original-starter marker, faint hook, healing/revival guard, PC/Day Care eligibility guard or blackout integration.
- The existing `BoxPokemon` header exposes unused persistent bits, so the current authority's low-impact per-individual marker strategy is technically viable without growing the Pokémon structure.
- Classification: **partial implementation**. CORE-001 is integration/QA work; CORE-002–004 remain genuine engine work.

### Starter and evolution
- Starter design is closed around Eevee / Pichu / Ditto with deterministic Blue/Green assignment.
- No Sam-specific starter implementation branch/commit was found.
- No Sam deterministic evolution-method implementation branch/commit was found for the locked single-player evolution package.
- Classification: **design closed, implementation absent**.

### Special acquisition / outsider behavior
- Vanilla source already contains the needed effect primitives:
  - `IsTradedMon()` drives the ×1.5 outsider/traded EXP branch.
  - `IsMonDisobedient()` applies badge-based outsider obedience.
- Vanilla `ScriptGiveMon()` creates player-OT Pokémon, so qualifying Sam Gift/Purchase/Game Corner/Fossil/Rocket-recovery acquisitions cannot use it unchanged.
- No Sam shared qualifying-acquisition constructor/delivery implementation was found.
- Classification: **design closed; reuse vanilla mechanics; shared Sam routing still required**.

### TM01–TM68 and custom moves
- `sam/arch-005-resource-constants` allocates TM51–68 item IDs and custom move IDs only.
- TM Case/range/mapping expansion is not implemented.
- No move-data/effect entries were found for Boulder Bash, Ghostly Wail, Seed Strike or Night Terror.
- Stock Shadow Punch remains 60 BP / 20 PP / always-hit in audited source; the Sam 70 BP / 15 PP + screen-break modification is not implemented.
- Signal Beam/Shadow Punch class/effect override work remains under TM-003.
- Current Programming Readiness Registry/TM-005 closure confirms the current roster's TM/HM compatibility **design is fully closed**. Older archival notes listing later-added families as OPEN/authority-trace are stale snapshots.
- Literal ROM species × TM01–TM68 compatibility encoding remains absent.
- Classification: **constants partial; engine/data implementation still required; compatibility design closed**.

### Custom species foundation
- Ordinary Gen III species used by Sam exist in baseline source.
- No `SPECIES_LEAFEON`, `SPECIES_ECTOCEON` or `SPECIES_RHYPERIOR` constants/data implementation was found on audited Sam branches.
- Current closed architecture assigns Leafeon=412, Ectoceon=413, Rhyperior=414, with Egg shifted to 415; OLD_UNOWN slots remain untouched.
- ARCH-004 must implement the species-table expansion before SPEC-009 can integrate the three species; ARCH-006 remains the graphics-allocation dependency.
- Classification: **architecture/design closed; source implementation absent**.

### Reusable Satoshi infrastructure
- `sam/league-phase5-integration` reserves `gymSatoshiPostgameAux[0x30]` in Sam save data.
- No reusable Satoshi practice state machine, Gym scripts, first-Hall-of-Fame rematch conversion, or Viridian Thomas/Satoshi coexistence implementation was found.
- All eight specialist battle packages remain design/data closed and should be mapped into one reusable system rather than reauthored.
- Classification: **save-layout scaffold only; SAT-001–003 remain implementation work**.

## Shared core-engine audit conclusion

The originally requested shared layer has now been source-audited end to end:

| Package | Source-first state |
| --- | --- |
| Permanent Mode | Partial: selector/persistence coded; mechanics absent |
| Starter system | Design closed; implementation absent |
| Evolution accessibility | Design closed; implementation absent |
| Special acquisition | Vanilla primitives reusable; Sam shared routing absent |
| TM01–68 | Constants partial; engine/mapping absent |
| TM compatibility | Design fully closed; literal ROM matrix absent |
| Custom moves | IDs allocated; move behavior/data absent |
| Custom species foundation | Architecture closed; implementation absent |
| Satoshi reusable system | Save allocation scaffold only; state machine absent |

The Programming Readiness Registry has been synchronized to these findings. Future completion work should treat these as implementation/integration/QA tasks and must not reopen closed design.

## Architecture/global-data blocker audit — 2026-09-30

### ARCH-004 species append architecture
- Current `sam-edition-dev` still ends the ordinary species constants at `SPECIES_CHIMECHO = 411`, followed by `SPECIES_EGG = 412` and `NUM_SPECIES = SPECIES_EGG`.
- No `SPECIES_LEAFEON`, `SPECIES_ECTOCEON` or `SPECIES_RHYPERIOR` implementation exists on audited Sam branches.
- `SPECIES_OLD_UNOWN_B` through `SPECIES_OLD_UNOWN_Z` remain actively represented in species/graphics tables and must not be repurposed.
- Closed architecture remains: Leafeon=412, Ectoceon=413, Rhyperior=414, Egg=415; derived Unown IDs follow the new `NUM_SPECIES`.
- Implementation must audit all species-indexed tables and graphics/Pokédex/learnset/evolution bounds after the shift.
- Classification: **design/architecture closed; source implementation absent; P0 blocker**.

### ARCH-006 graphics allocation architecture
- The Resource Registry reserves OBJ 152–223 and Trainer Pic 148–223, preserving dynamic OBJ 240–255.
- No centralized Sam graphics-allocation implementation was found on `sam-edition-dev`.
- `sam-gym2-cerulean-complete` already proves the range is usable with feature-local allocations including Leilani OBJ 152, Satoshi OBJ 155, Leilani trainer pic 148 and Satoshi trainer pic 151.
- Satoshi still uses Professor Oak battle-art fallback on the Gym 2 branch, so final art conversion/insertion remains open.
- Classification: **registry allocation closed; central source encoding absent; feature-local allocations must be reconciled before broad merging**.

### Shared SaveBlock1 reconciliation
- `sam/opening-intro` and `sam/league-phase5-integration` use the same 0xF0 `SamEditionSaveData` internal functional layout:
  - 0x00–0x0F core;
  - 0x10–0x4F global mechanics;
  - 0x50–0x57 Green name;
  - 0x58–0x8F rival/Rocket;
  - 0x90–0xBF Gym/Satoshi/postgame;
  - 0xC0–0xEF future.
- Opening places the block at SaveBlock1 0x348C and carries temporary 0xA0 tail padding.
- League uses the compensated final placement at 0x352C, keeps `ramScript` at 0x361C and preserves total SaveBlock1 size 0x3D68.
- Integration direction is therefore clear: keep the League physical save layout and port opening's Green-name/game-mode initialization/preservation logic into it.
- Classification: **two compatible partial implementations requiring reconciliation, not redesign**.

### Route 5 Day Care / breeding
- FireRed source already contains a two-slot Day Care, compatibility, Egg-generation and hatching engine in `src/daycare.c`.
- Route 5 still uses its separate vanilla `route5DayCareMon` single-Pokémon script path on `sam-edition-dev`, `sam/opening-intro` and `sam/league-phase5-integration`.
- No Sam Route 5 conversion, one-pending-Egg rule, 50% Egg shiny rule, Sam withdrawal-fee rule, Permanent-dead deposit rejection, starter-protection interaction or legendary-bird Ditto-only override was found.
- The implementation should reuse the existing two-slot Gen III breeding primitives rather than create another breeding engine.
- Classification: **underlying engine support exists; Sam Route 5 behavior not implemented**.

## Dependency consequence

The next implementation-critical sequence is now source-confirmed:

1. reconcile ARCH-002 shared save layout;
2. implement ARCH-004 species append architecture;
3. implement ARCH-006 centralized graphics allocations;
4. finish ARCH-003 central symbol insertion;
5. implement core Permanent/starter/evolution/Gift mechanics;
6. route Route 5 into the existing breeding engine;
7. encode global species/TM/evolution data;
8. then merge map/Gym/rival feature branches against the stabilized architecture.

## Symbols, trainer architecture, Pokédex and encounter audit — 2026-09-30

### ARCH-001 trainer architecture
- `sam/league-phase5-integration` implements `MAX_TRAINERS_COUNT=1024`.
- Trainer flags extend through 0x8FF; `SYS_FLAGS` begins at 0x900; `FLAGS_COUNT` is 0xA00.
- SaveBlock1 remains 0x3D68 and the League branch carries static assertions for the compensated layout.
- Classification: **ARCH-001 COMPLETE at architecture/compile level**. Individual trainer packages still require integration/runtime QA.

### ARCH-003 central symbol insertion
- Central registry allocations are internally coherent, but source insertion is incomplete:
  - opening: `VAR_SAM_GAME_MODE=0x408C`;
  - Gym 2: Satoshi practice flags 0x310–0x317 and `VAR_SAM_CERULEAN_GYM_FLAME_STATE=0x40A0`;
  - League: Green flags 0x340/0x341.
- Most remaining 0x300–0x37F flags and 0x408C–0x40A9 variables are still exposed only as generic `FLAG_0x*` / `VAR_0x*` names on the shared branch.
- Known branch collision: `sam-gym5-fuchsia` assigns trainer IDs 743–750 to Bushrangers/Baz/Satoshi. The central registry assigns 743–758 to Satoshi practice/rematch records, and Gym 2 already follows that central allocation.
- Gym 5 must be renumbered into the approved free Gym/trainer range before merge.
- Classification: **central allocations closed; source insertion partial; collision cleanup required**.

### ARCH-006 trainer graphics/class collision
- `sam-gym2-cerulean-complete` locally uses trainer pics 148–151 for Leilani/Lehua/Keahi/Satoshi and trainer class 107 for FIRE DANCER.
- `sam-gym5-fuchsia` independently uses trainer pics 148–151 for Baz/Bushrangers/Satoshi and trainer class 107 for BUSHRANGER.
- The central Symbol Registry explicitly allocates FIRE DANCER=107. Gym 5's branch-local 107 therefore cannot survive consolidation.
- Classification: **central range policy sound; feature-local graphics/class IDs conflict and must be reassigned before merge**.

### Final Sam Pokédex numbering
- Final design authority is closed at a gapless 001–205 player-facing Pokédex with Mew #205.
- Current source still uses vanilla `NATIONAL_DEX_*` numbering through Deoxys, with `KANTO_DEX_COUNT=NATIONAL_DEX_MEW` and `NATIONAL_DEX_COUNT=NATIONAL_DEX_DEOXYS`.
- No Sam 205-entry player-facing display-number mapping/order implementation was found on audited branches.
- Internal engine/National species IDs do not need to equal Sam display numbers; the implementation should add the Sam mapping/order layer rather than destabilize internal species identity unnecessarily.
- Classification: **design complete; ROM implementation absent**. The Programming Readiness Registry was corrected so SPEC-011 is no longer treated as finished ROM work.

### Encounter distribution breadth
- Current readiness authority treats encounter design as closed/programmer-ready.
- `sam-edition-dev/src/data/wild_encounters.json` contains none of several locked Sam markers checked during this audit: Smoochum, Feebas, rare Bulbasaur/Squirtle/Charmander wild sources, Nosepass, Duskull, Shuppet or Tropius.
- Among audited active Sam branches, only `sam/enc-001-nosepass-rock-tunnel` changes `wild_encounters.json`.
- That branch places Nosepass Lv24–26 in the older 4% land slot; the current central registry/authority requires Rock Tunnel B1F Nosepass at 5% Lv24–26.
- Classification: **broad encounter implementation absent; ENC-001 is a narrow stale-rate packet needing reconciliation**.

## Dependency consequence

The global implementation picture is now tighter:
1. ARCH-001 trainer capacity is no longer a blocker.
2. ARCH-002 save reconciliation remains integration work.
3. ARCH-003 must centralize symbols and clean branch-local ID collisions.
4. ARCH-004 must expand species tables.
5. ARCH-006 must assign unique graphics/class IDs across feature branches.
6. Final Sam Pokédex display numbering must be implemented after/with species architecture.
7. Encounter tables require a broad encoding pass; Nosepass alone does not materially reduce that workload.

## CHK-2026-09-30-007 — Global Pokémon data / statics / acquisitions / ordinary trainers

### Global species data
- On `sam-edition-dev`, `src/data/pokemon/species_info.h`, `src/data/pokemon/level_up_learnsets.h`, and `src/data/pokemon/evolution.h` remain baseline outside narrow feature work.
- Existing Gen III entries are reusable implementation scaffolds, but the closed Sam-specific species packets are not broadly encoded.
- Ralts/Natu, the three Ghost-family packages, early Bug final evolutions, Feebas/Milotic, and the legendary-bird learnset package remain implementation work.
- Milotic's baseline stats already match the locked 95/60/79/100/125/81 target, but its typing remains Water/Water and Feebas still uses Beauty-based evolution instead of the locked Lv20 method.
- `sam/spec-006-nosepass-rock-cleanup` is narrow: it changes only Geodude, Graveler, Golem, Onix, Rhyhorn, and Rhydon to pure Rock. Nosepass remains baseline and Steelix is unchanged.

### Custom item / ability runtime
- `sam/arch-005-resource-constants` allocates Soul Rot, Brick, Adaptive Gene, and Protector resources.
- No corresponding Sam runtime behavior was found for those resources.
- Classification: **allocation foundation only; gameplay behavior still requires implementation**.

### Visible static encounters
- No active Sam branch/commit was found for the approved visible static encounter packages reviewed in this checkpoint.
- FireRed's existing encounter primitives are reusable, but the Sam persistence, map-event, reward, and item behavior remains to be encoded.
- Classification: **design closed; implementation absent**.

### Special acquisitions and NPC trades
- `src/data/ingame_trades.h` on `sam-edition-dev` remains the vanilla trade table.
- The redesigned Sam NPC trades are not encoded.
- The shared qualifying-acquisition delivery path and safe one-time reward helper remain unimplemented.
- Classification: **design closed; vanilla engine reusable; Sam content/routing absent**.

### Ordinary trainer tables
- `src/data/trainers.h` and `src/data/trainer_parties.h` on `sam-edition-dev` remain baseline.
- The broad ordinary-trainer redesign through Seven Island is not encoded on the integration branch.
- The approved S.S. Anne Lickitung and Mt. Moon Fury Cutter corrections also remain to be integrated.
- Focused trainer work on League/Gym branches must not be mistaken for ordinary-trainer completion.

### CHK-007 conclusion
CHK-2026-09-30-007 confirms that the global Pokémon-data layer is **design-heavy but source-light**. Most remaining work is dependency-sensitive encoding and integration against already-closed authorities, not additional broad creative design.

## Immediate next audit

Continue into the remaining global-data implementation surfaces:
- exact species-data packets already closed versus still absent in source;
- level-up learnsets;
- evolution tables;
- abilities/items that support those species;
- static encounters and special-acquisition scripts;
- ordinary trainer-table implementation breadth outside League/Gym2 scaffolds.

