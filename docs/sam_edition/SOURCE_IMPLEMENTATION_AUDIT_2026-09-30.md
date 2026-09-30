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

## CHK-2026-09-30-008 — Release / integration / build state

### Build and CI evidence
- `sam-edition-dev` head used by the audit passed CI run #181, including the comparison/build matrix.
- `sam/league-phase5-integration` passed Sam-specific CI run #177, including the League payload validation and Sam Edition FireRed build.
- `sam-gym2-cerulean-complete` latest observed CI run #30 failed at the vanilla `Compare FireRed` step. Because this branch intentionally changes the ROM, that result is not by itself proof of a compile failure; it still lacks the purpose-built successful Sam build validation available for League.
- Opening and Gym 5 did not have current CI evidence in this audit.
- Classification: **build environment is healthy; feature-level validation is uneven**.

### Branch integration state
Relative to `sam-edition-dev` at this checkpoint, the major feature branches were divergent rather than cleanly stacked:
- opening: 33 commits ahead / 4 behind;
- League: 64 ahead / 4 behind;
- Gym 2: 68 ahead / 10 behind;
- Gym 5: 3 ahead / 8 behind;
- SPEC-006: 1 ahead / 4 behind;
- ENC-001: 1 ahead / 4 behind;
- ARCH-005: 3 ahead / 4 behind.

Much of the integration-branch movement is documentation/workflow, but the divergence is real and should be reconciled before broad new parallel implementation expands.

### Registry completion snapshot
The Programming Readiness Registry contained 98 tracked Backlog tasks:
- 11 COMPLETE;
- 9 IN PROGRESS;
- 73 READY;
- 4 BLOCKED;
- 1 DEFERRED.

READY primarily means programmer-ready/design-closed, not implemented. COMPLETE also includes some design/data closure work, so raw task counts must not be treated as ROM completion percentage.

### Release gates
- Full-game regression has not begun and remains deferred until implementation/integration is substantially complete.
- Approved source art still requires ROM-native conversion, allocation, insertion, hookup, and QA where applicable.
- Major feature branches must be consolidated against the stabilized architecture and then revalidated with clean Sam-specific builds.
- Final release acceptance still requires the full QA Matrix plus runtime/emulator testing.

### Completion estimate
Source-first audit estimate at this checkpoint:
- creative/design specification: roughly 90–95% complete;
- actual ROM/source implementation: roughly 15–20%;
- integrated/tested/release-ready game: roughly 10–15%;
- practical single-number answer for “how close is the ROM to actually finished?”: about 20%, with a reasonable source-audit range of 15–25%.

This estimate is an audit assessment, not a substitute for task-level Registry status.

### CHK-008 conclusion
The project is specification-heavy and implementation-light. The shortest path is to consolidate the P0 architecture first, then encode the large closed-data layer, integrate existing opening/Gym2/League work, implement the remaining story/Gym/world packages, and only then enter full-game regression.

## CHK-2026-09-30-009 — Exact global-data packet coverage

### SPEC-001–SPEC-011 source map
- SPEC-001 Type Retrofit: closed/programmer-ready; no matching Sam source implementation found.
- SPEC-002 Dark-Type Retrofit: closed/programmer-ready; no dedicated Sam implementation found.
- SPEC-003 Ralts/Natu: closed; Sam-specific deltas are not encoded on the integration branch.
- SPEC-004 Ghost Families: closed; Sam-specific family deltas are not encoded.
- SPEC-005 Early Bug Final Evolutions: closed; redesigned stats/learnsets/TM deltas are not encoded.
- SPEC-006 Nosepass / Rock Cleanup: **narrow partial implementation only**; the feature branch changes six Gen I Rock-family type fields and does not represent full package completion.
- SPEC-007 Feebas/Milotic: closed; baseline Milotic stats happen to match the locked target, but Sam typing/evolution changes remain absent.
- SPEC-008 Legendary Birds: closed; Sam learnset/capture-move package remains absent.
- SPEC-009 Custom Species Integration: design/architecture closed but source implementation absent; blocked by ARCH-004/ARCH-006.
- SPEC-010 Tropius: design closure is complete; integration-branch source still reflects baseline rather than a distinct Sam implementation packet.
- SPEC-011 Sam Pokédex display numbering: final 001–205 design is closed; source mapping remains absent.

### Related systems
- Evolution accessibility, special-acquisition routing, visible statics, and ordinary trainer encoding remain as classified in CHK-007.
- No hidden matching Sam implementation commit was identified for the absent packets during the checkpoint search.

### CHK-009 conclusion
The exact packet map confirms that most global-data work is literal source encoding against already-closed authorities. Existing vanilla Gen III entries are useful scaffolding, but must not be counted as Sam implementation when the Sam packet changes data or behavior.

## Immediate next audit

Continue into the remaining story/world implementation breadth:
- Team Rocket city-operation scripts and Thomas non-League battles;
- Blue/Green non-League rival encounters;
- Professor Oak research milestones and Professor Palm routing/status;
- town side quests and Saffron Hothouse;
- Mew truck/harbor event and opposite-fossil handoff;
- map/event implementation breadth outside the already-coded opening, League, and Gym 2 packages.


## CHK-2026-09-30-010 — Story / world map-script implementation breadth

### Source coverage result
- Compared every active Sam feature branch against `sam-edition-dev`: opening, League, Gym 2, Gym 5, SPEC-006, ENC-001 and ARCH-005.
- Outside the already-known opening, League and Gym 2 packages, no active Sam branch carries broad story/world map-script changes.
- Repository commit searches found no separate Sam implementation commits for Team Rocket, Thomas, Professor Oak milestones, Mew, Hothouse, town side quests, fossil handoff, or non-League Blue/Green story encounters.
- Classification: **design is substantially closed; broad world/story implementation is absent**.

### Blue / Green outside the League
- League Blue/Green work remains genuine partial implementation and must be preserved.
- No non-League Blue/Green map/script package was found on active Sam branches.
- The mandatory Route 4 Blue+Green Double Battle and other non-League rival encounters therefore remain implementation work.
- Classification: **League slices implemented-but-unintegrated; non-League rival scripting absent**.

### Team Rocket / Thomas
- Current readiness authority locks the Team Rocket / Thomas event matrix, including the Viridian theft/fencing event, Mt. Moon, Cerulean burglary, Nugget Bridge Thomas #1, Rock Tunnel/Porygon, Celadon, Lavender, Silph, Cinnabar, Giovanni dissolution, Victory Road Thomas and post-League Viridian Thomas.
- No corresponding broad Sam map/script implementation was found on active branches.
- Thomas trainer data and chronology remain READY rather than coded.
- Shared Rocket evidence/recovery/state plumbing is also absent.
- Classification: **design closed; implementation absent outside reusable vanilla map/story scaffolding**.

### Professor Oak research milestones
- No implementation was found for the locked 30/50/75/100/125/151 OWNED-species milestone ladder or Joey unlock/reset loop.
- Existing Oak/new-game work on `sam/opening-intro` is intro/name/mode work, not the research-milestone system.
- OAK-001/OAK-002 remain blocked by their recorded shared implementation dependencies.
- Classification: **design/dialogue closed; source implementation absent**.

### Professor Palm
- Live Drive authority/backlog search at this checkpoint found no current Sam Edition Professor Palm specialist authority or Programming Readiness Registry task.
- Therefore no Palm package is counted as current Sam implementation work from memory/history alone.
- If a current authority is later located or Tom explicitly restores/imports the package, add it through a new verified checkpoint rather than silently importing stale material.

### Town side quests
- The current Town Side Quest implementation authority explicitly states that ROM implementation was not completed by its synchronization pass.
- No active Sam branch carries the reusable quest framework or the ten town quest map/script packages.
- QUEST-001 through the individual quest tasks remain source implementation work; shared Gift handling is a dependency for Pokémon-reward quests.
- Classification: **design/content closed; implementation absent**.

### Saffron Hothouse
- No Hothouse map/script/battle implementation was found on active Sam branches.
- Current registry authority keeps creative design/dialogue closed; HOT-001 is blocked only by implementation/assets/shared Gift integration/QA.
- Classification: **design closed; implementation absent**.

### Mew truck / harbor rumor hooks
- Current readiness authority locks the two post-S.S.-Anne Vermilion rumor hooks and the mechanical Mew event: Lv50, Surf + Strength access, movable truck, visible overworld Mew, one-time static, permanent loss if defeated.
- No Sam map/script implementation for the rumor NPC updates or truck/Mew event was found on active branches.
- Classification: **design closed; implementation absent**.

### Cinnabar opposite-fossil handoff
- Current readiness authority locks the post-revival opposite-fossil handoff, including Bag-full retry and one-time delivery behavior.
- No Sam implementation was found on active branches.
- Classification: **design closed; implementation absent**.

### CHK-010 conclusion
The remaining story/world layer is substantially more complete on paper than in source. The implementation strategy should reuse recognizable FireRed map/story scaffolding where the governing Sam authority preserves it, then overlay the locked Sam state/event changes rather than rebuilding Kanto wholesale.

The next source-first audit should cover **remaining UI/assets/map-resource breadth and release-critical non-story systems not yet mapped**, then reconcile the resulting dependency order against the P0/P1 implementation queue before coding begins.

## CHK-2026-09-30-011 — UI / assets / map-resource breadth

### Title screen
- `sam/opening-intro` contains a real Sam title-screen implementation, not merely a design handoff: native title palette/tile resources exist under `graphics/title_screen/sam/`, and `src/title_screen.c` loads them through the title-screen flow.
- The audited accepted-transition path contains no `PlayCry` call; the locked no-Pokémon-cry behavior is therefore coded on the feature branch.
- TITLE-001/002/003 were corrected from untouched READY work to **IN PROGRESS / feature-branch implementation**.
- Remaining: reconcile the branch with the integration tree, visually verify against the approved composition, run a clean Sam-specific build, and runtime-test idle/skip/input/main-menu/save-clear behavior.
- Classification: **substantially implemented on feature branch; not integrated/QA-passed**.

### Character / trainer sprite pipeline
- The Character Sprite Implementation Tracker remains the operational asset surface.
- At this checkpoint its Control Center reports extensive pending conversion/open-creation work and **zero in-game-tested packages**; source branches likewise show substantial custom graphics insertion mainly in opening and Gym 2.
- Approved source art must be distinguished from ROM-native conversion/insertion. Source approval is not implementation completion.
- The tracker still contained stale Open/Create-overworld wording for core-cast characters. Red, Blue, Green, Thomas and Satoshi were reconciled to **Approved Source / Pending Conversion** for overworld art in accordance with the current project closure: preserve the approved individual source art and do not regenerate it unless a technical impossibility explicitly reopens canon.
- League-specific Blue/Green battle-pose requirements remain separate from their closed overworld source art.

### Gym / badge / trainer art
- Several Gym packages have approved or working source art but still need ROM-native palette/index/frame conversion and in-engine QA.
- Gym 2 proves the insertion path is viable but also exposes the need for ARCH-006 centralized allocation before broad branch consolidation.
- Some badge/trainer-art packages remain genuinely open or working rather than source-approved; those remain asset-production tasks and are not evidence that the associated Gym design is open.
- Classification: **mixed asset readiness; broad conversion/insertion/QA workload remains**.

### Custom species assets
- SPRITE-003 remains downstream of SPEC-009 and ARCH-006.
- Because Leafeon/Ectoceon/Rhyperior species-table integration is not yet implemented, their battle/back/shiny/menu/footprint/cry integration cannot be considered complete even where source art exists.
- Classification: **dependency-blocked integration work**.

### Map/resource breadth
- Active branch comparison continues to show custom map/resource implementation concentrated in the already-known Gym 2 and League packages, with opening/title resources on the opening branch.
- There is no hidden broad map-resource layer that materially changes the CHK-010 story/world conclusion.

### CHK-011 conclusion
The asset/UI layer is further along than the broad world scripting layer because the opening/title package and Gym 2 contain real converted/in-source resources. It is still far from release-ready: most approved art needs conversion/insertion, no character package is recorded as in-game-tested in the asset tracker, custom-species assets depend on unresolved architecture implementation, and several genuinely open badge/trainer assets remain.

The next audit should now reconcile **the final dependency/execution order** across every verified checkpoint and turn the source-first findings into a concrete implementation sequence, without reopening closed design.
