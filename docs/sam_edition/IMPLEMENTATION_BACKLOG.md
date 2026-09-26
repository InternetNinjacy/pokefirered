# Pokémon: Sam Edition — Implementation Backlog Mirror

> **Operational source of truth:** the Google Drive `Pokemon_Sam_Edition_Programming_Readiness_Registry_v1.0` Backlog tab.
>
> This file is a repository-local mirror for programmers. If this file and Drive disagree, **Drive controls status and requirements** until the mirror is refreshed.

Active integration branch: `sam-edition-dev`

Workflow rules: `docs/sam_edition/IMPLEMENTATION_WORKFLOW.md`

GitHub Issues are disabled for this repository, so Sam Edition uses **stable Task IDs + task branches + pull requests** rather than issue numbers.

## Status legend

- `READY` — may be implemented
- `BLOCKED` — missing approved input; do not guess
- `IN PROGRESS` — active branch/PR
- `QA` — implementation exists; testing in progress
- `COMPLETE` — merged and required QA passed
- `DEFERRED` — intentionally postponed


## P0 Environment & Architecture

- [ ] **ENV-001** · P0 · SYS-CORE · **READY** — Reproduce clean pret/pokefirered baseline build and verify expected ROM SHA-1  
  Depends on / blocked by: BLK-002
- [ ] **ENV-002** · P0 · SYS-CORE · **READY** — Document reproducible local build/toolchain procedure for Sam Edition development  
  Depends on / blocked by: ENV-001
- [ ] **ARCH-001** · P0 · SYS-TRAIN · **READY** — Expand trainer capacity to MAX_TRAINERS_COUNT=1024 and preserve stock IDs  
  Depends on / blocked by: ENV-001
- [ ] **ARCH-002** · P0 · SYS-CORE · **READY** — Implement compensated SaveBlock1 layout and 240-byte SamEditionSaveData block  
  Depends on / blocked by: ENV-001
- [ ] **ARCH-003** · P0 · SYS-CORE · **READY** — Implement the central Symbol Registry assignments as source-tree constants/headers; keep registry and code synchronized  
  Depends on / blocked by: ENV-001
- [ ] **ARCH-004** · P0 · SYS-SPEC · **READY** — Apply species append architecture for Leafeon/Ectoceon/Rhyperior and Egg shift  
  Depends on / blocked by: ENV-001
- [ ] **ARCH-005** · P0 · SYS-TM · **READY** — Apply custom move, item, TM51–68, and ability constant allocations  
  Depends on / blocked by: ENV-001
- [ ] **ARCH-006** · P1 · SYS-SPRITES · **READY** — Reserve and document trainer/OBJ graphics ranges for Sam assets  
  Depends on / blocked by: ENV-001
- [x] **DOC-002** · P0 · SYS-CORE · **COMPLETE** — Standardize current specialist technical authorities with Implementation Contract + Acceptance Test blocks

## P1 Core Engine Systems

- [ ] **CORE-001** · P0 · SYS-CORE · **READY** — Implement new-game Standard/Permanent mode selection and persistent mode state  
  Depends on / blocked by: ARCH-002; ARCH-003
- [ ] **CORE-002** · P0 · SYS-CORE · **READY** — Implement persistent individual death state for non-starter player Pokémon  
  Depends on / blocked by: CORE-001; ARCH-002
- [ ] **CORE-003** · P0 · SYS-CORE · **READY** — Implement protected-starter individual flag/state through evolution and storage  
  Depends on / blocked by: CORE-001; ARCH-002
- [ ] **CORE-004** · P1 · SYS-CORE · **READY** — Enforce common-path healing/revival restrictions for permanent-dead Pokémon  
  Depends on / blocked by: CORE-002
- [ ] **BREED-001** · P0 · SYS-BREED · **READY** — Convert Route 5 Day Care to two deposited Pokémon  
  Depends on / blocked by: ARCH-002; ARCH-003
- [ ] **BREED-002** · P0 · SYS-BREED · **READY** — Enable Gen III compatibility, Egg generation, pickup, and persistence at Route 5  
  Depends on / blocked by: BREED-001
- [ ] **BREED-003** · P1 · SYS-BIRDS · **READY** — Implement genderless Ditto-only breeding eligibility for Articuno/Zapdos/Moltres  
  Depends on / blocked by: BREED-002
- [ ] **GIFT-001** · P0 · SYS-GIFT · **READY** — Implement shared 1.5× EXP + badge-obedience behavior for qualifying acquisitions  
  Depends on / blocked by: ARCH-002
- [ ] **GIFT-002** · P1 · SYS-GIFT · **READY** — Implement safe full-party handling for one-time Pokémon rewards  
  Depends on / blocked by: GIFT-001
- [ ] **EVOL-001** · P0 · SYS-EVOL · **READY** — Implement Lv42 replacements for pure trade evolutions  
  Depends on / blocked by: ARCH-004
- [ ] **EVOL-002** · P1 · SYS-EVOL · **READY** — Implement direct-use held-item trade evolutions  
  Depends on / blocked by: ARCH-005
- [ ] **EVOL-003** · P1 · SYS-EVOL · **READY** — Implement friendship/day-night/Beauty replacement methods  
  Depends on / blocked by: ARCH-004
- [ ] **START-001** · P0 · SYS-START · **READY** — Implement Eevee/Pichu/Ditto starter selection and deterministic Blue/Green branch assignment  
  Depends on / blocked by: ARCH-003
- [ ] **START-002** · P1 · SYS-START · **READY** — Implement Brick item data, Eevee-only evolution use, consumption rules, and shop distribution  
  Depends on / blocked by: ARCH-005
- [ ] **START-003** · P0 · SYS-START · **READY** — Implement Adaptive Gene original-species Ditto damage hook and exclusions  
  Depends on / blocked by: ARCH-005
- [ ] **TM-001** · P0 · SYS-TM · **READY** — Implement final logical TM01–TM68 item/move mapping including TM51–68 placeholder item IDs  
  Depends on / blocked by: ARCH-005
- [ ] **TM-002** · P0 · SYS-TM · **READY** — Implement Boulder Bash, Ghostly Wail, Seed Strike, and Night Terror move data/effects  
  Depends on / blocked by: ARCH-005
- [ ] **TM-003** · P0 · SYS-TM · **READY** — Implement Signal Beam special-class override and current Shadow Punch modification  
  Depends on / blocked by: TM-002

## P4 Story / Gyms / Trainers

- [ ] **START-004** · P2 · SYS-START · **BLOCKED** — Implement starter tutorial flow and exact text once current dialogue is finalized  
  Depends on / blocked by: Open starter tutorial dialogue
- [ ] **TRAIN-001** · P1 · SYS-TRAIN · **READY** — Encode ordinary trainer teams/formats that are already design-closed  
  Depends on / blocked by: ARCH-001
- [ ] **TRAIN-002** · P1 · SYS-TRAIN · **BLOCKED** — Choose and encode replacement for unauthorized Houndour slot  
  Depends on / blocked by: Open replacement decision
- [ ] **TRAIN-003** · P1 · SYS-TRAIN · **BLOCKED** — Replace out-of-scope Bug Bite move without adding Bug Bite globally  
  Depends on / blocked by: Open replacement decision
- [ ] **TRAIN-004** · P2 · SYS-TRAIN · **BLOCKED** — Finish remaining ordinary trainer Single/Double assignments toward ~40% target  
  Depends on / blocked by: Trainer-by-trainer assignments still open
- [ ] **RIV-001** · P1 · SYS-RIVALS · **READY** — Implement Blue branch teams, trainer records, encounters, dialogue hooks, and Elite Four routing  
  Depends on / blocked by: START-001; ARCH-001
- [ ] **RIV-002** · P1 · SYS-RIVALS · **READY** — Implement Green branch teams, trainer records, encounters, Champion routing, and dialogue hooks  
  Depends on / blocked by: START-001; ARCH-001
- [ ] **RIV-003** · P1 · SYS-RIVALS · **READY** — Implement mandatory Blue+Green Route 4 Double Battle event  
  Depends on / blocked by: RIV-001; RIV-002
- [ ] **THOMAS-001** · P1 · SYS-THOMAS · **READY** — Encode Thomas’s canonical six-slot branch architecture and all battle records  
  Depends on / blocked by: ARCH-001
- [ ] **THOMAS-002** · P1 · SYS-THOMAS · **READY** — Implement Thomas encounter chronology and map scripts through Viridian takeover  
  Depends on / blocked by: ARCH-003; THOMAS-001
- [ ] **ROCKET-001** · P1 · SYS-ROCKET · **READY** — Implement shared Rocket evidence/recovery/state conventions used by city operations  
  Depends on / blocked by: GIFT-001; ARCH-003
- [ ] **ROCKET-002** · P2 · SYS-ROCKET · **READY** — Implement locked city operation sequence in progression order  
  Depends on / blocked by: ROCKET-001
- [ ] **SAT-001** · P1 · SYS-SATOSHI · **READY** — Implement reusable eight-Gym Satoshi practice state machine  
  Depends on / blocked by: ARCH-001; ARCH-003
- [ ] **SAT-002** · P1 · SYS-SATOSHI · **READY** — Implement first-Hall-of-Fame conversion to repeatable rematch routing  
  Depends on / blocked by: SAT-001
- [ ] **SAT-003** · P1 · SYS-SATOSHI · **READY** — Implement Satoshi entrance rematch alongside Thomas boss-slot takeover  
  Depends on / blocked by: SAT-002; THOMAS-002
- [ ] **SAT-004** · P1 · SYS-SATOSHI · **BLOCKED** — Finalize exact Pewter Satoshi rematch tuning  
  Depends on / blocked by: BLK-SAT-02
- [ ] **SAT-005** · P1 · SYS-SATOSHI · **BLOCKED** — Finalize exact Cerulean Satoshi rematch tuning and final reward wording dependency  
  Depends on / blocked by: BLK-SAT-03; Gym2 reward wording
- [ ] **GYM1-001** · P1 · SYS-GYM1 · **READY** — Implement closed Gym1 puzzle/battle/reward package  
  Depends on / blocked by: ARCH-001; ARCH-003
- [ ] **GYM2-001** · P1 · SYS-GYM2 · **READY** — Implement flame-gate state machine, trainers, Leilani battle, and TM39 reward hook  
  Depends on / blocked by: ARCH-001; ARCH-003; TM-001
- [ ] **GYM3-001** · P1 · SYS-GYM3 · **READY** — Implement water-redirection/floating-dock puzzle, trainers, Surge battles, and reward  
  Depends on / blocked by: ARCH-001; ARCH-003
- [ ] **GYM4-001** · P1 · SYS-GYM4 · **READY** — Audit current specialist handoff and encode closed trainer/Erika packages including Signal Beam reconciliation  
  Depends on / blocked by: TM-003; ARCH-001
- [ ] **GYM5-001** · P1 · SYS-GYM5 · **READY** — Implement straight-line gauntlet, Bushranger trainers, Baz battles, reward, and rematch  
  Depends on / blocked by: ARCH-001; ARCH-003
- [ ] **GYM6-001** · P1 · SYS-GYM6 · **READY** — Implement retained warp topology, trainer-class retheme, Sabrina battles, TM30 reward, and rematch  
  Depends on / blocked by: ARCH-001; ARCH-003; TM-002
- [ ] **GYM7-001** · P1 · SYS-GYM7 · **READY** — Implement closed Gym7 quiz/trainer/Blaine/Satoshi/reward package  
  Depends on / blocked by: ARCH-001; ARCH-003
- [ ] **GYM8-001** · P1 · SYS-GYM8 · **READY** — Audit current specialist package, assign central IDs, and implement Giovanni first battle / postgame Thomas takeover  
  Depends on / blocked by: ARCH-001; ARCH-003; THOMAS-002

## P2 Global Data Layer

- [ ] **TM-004** · P1 · SYS-TM · **READY** — Encode all currently closed TM01–TM68 species compatibility rows  
  Depends on / blocked by: TM-001; ARCH-004
- [ ] **TM-005** · P1 · SYS-TM · **BLOCKED** — Close and encode remaining compatibility audits still marked OPEN by current TM authority  
  Depends on / blocked by: BLK-008 and any current open species audits
- [ ] **SPEC-001** · P0 · SYS-SPEC · **READY** — Apply pure-Flying and Water/Psychic Psyduck/Golduck type retrofit  
  Depends on / blocked by: ARCH-004
- [ ] **SPEC-002** · P1 · SYS-DARK · **READY** — Apply current Dark-type retrofit packet  
  Depends on / blocked by: ARCH-004
- [ ] **SPEC-003** · P0 · SYS-SPEC · **READY** — Implement focused Ralts/Kirlia/Gardevoir and Natu/Xatu species packet  
  Depends on / blocked by: TM-004
- [ ] **SPEC-004** · P1 · SYS-SPEC · **READY** — Implement completed Duskull/Dusclops, Shuppet/Banette, and Gastly/Haunter/Gengar species packages  
  Depends on / blocked by: TM-004
- [ ] **SPEC-005** · P1 · SYS-BUG · **READY** — Implement Butterfree/Beedrill/Beautifly/Dustox stats, learnsets, and final TM deltas  
  Depends on / blocked by: TM-003; TM-004
- [ ] **SPEC-006** · P1 · SYS-SPEC · **READY** — Implement Nosepass package and Generation I pure-Rock type cleanup  
  Depends on / blocked by: TM-004
- [ ] **SPEC-007** · P1 · SYS-SPEC · **READY** — Implement complete Feebas/Milotic species package  
  Depends on / blocked by: TM-004
- [ ] **SPEC-008** · P1 · SYS-BIRDS · **READY** — Implement locked Articuno/Zapdos/Moltres natural learnsets and Lv50 capture move outcomes  
  Depends on / blocked by: TM-004
- [ ] **SPEC-009** · P1 · SYS-SPEC · **READY** — Integrate Leafeon, Ectoceon, and Rhyperior species tables/graphics hooks/metadata using allocated IDs  
  Depends on / blocked by: ARCH-004; ARCH-006
- [ ] **SPEC-010** · P0 · SYS-HOT · **BLOCKED** — Close Tropius global natural learnset and TM/HM compatibility audit  
  Depends on / blocked by: BLK-008

## P7 Integration / Release

- [x] **SPEC-011** · P3 · SYS-SPEC · **COMPLETE** — Assign final sequential Sam Edition Pokédex display numbering after roster closure  
  Depends on / blocked by: None — roster closed at 205 species. Final authority: Pokemon_Sam_Edition_Pokedex_Final_Numbering_Authority_v1.0; Mew = #205.
- [ ] **QA-ALL-001** · P0 · SYS-CORE · **READY** — Run clean build and focused regression after each merged feature branch  
  Depends on / blocked by: ENV-001
- [ ] **QA-ALL-002** · P1 · SYS-CORE · **DEFERRED** — Execute full QA Matrix before release candidate  
  Depends on / blocked by: All implementation work
- [ ] **DOC-001** · P2 · SYS-CORE · **READY** — Update Backlog/Readiness/QA/Resource Registry in place after each merged feature

## P3 Shared Gameplay Infrastructure

- [ ] **ENC-001** · P1 · SYS-ENC · **READY** — Insert already-locked Ralts/Natu/Nosepass/Feebas encounter placements  
  Depends on / blocked by: SPEC-003; SPEC-006; SPEC-007
- [ ] **ENC-002** · P1 · SYS-ENC · **READY** — Implement currently approved visible one-time static encounters and persistence  
  Depends on / blocked by: ARCH-003
- [ ] **ENC-003** · P1 · SYS-ENC · **BLOCKED** — Finalize and encode map-by-map fishing/Surf tables  
  Depends on / blocked by: Exact fishing tables still open
- [ ] **ENC-004** · P2 · SYS-ENC · **BLOCKED** — Freeze remaining wild encounter tables after final roster/species closure  
  Depends on / blocked by: SYS-SPEC; TM-005

## P6 Assets / UI

- [ ] **GYM6-002** · P2 · SYS-GYM6 · **BLOCKED** — Finalize source approval, ROM conversion, insertion, and in-game QA  
  Depends on / blocked by: Phantom Badge source approval
- [ ] **TITLE-001** · P1 · SYS-TITLE · **READY** — Build native 240×160 Plan A title composition from approved master  
  Depends on / blocked by: ENV-001
- [ ] **TITLE-002** · P1 · SYS-TITLE · **READY** — Insert title assets using stock BG architecture and preserve input/main-menu transition  
  Depends on / blocked by: TITLE-001
- [ ] **TITLE-003** · P2 · SYS-TITLE · **BLOCKED** — Explicitly decide and implement title-screen cry behavior  
  Depends on / blocked by: BLK-TITLE-01
- [ ] **SPRITE-001** · P1 · SYS-SPRITES · **READY** — Convert approved trainer/character battle references to ROM-ready Gen III indexed assets  
  Depends on / blocked by: ARCH-006
- [ ] **SPRITE-002** · P1 · SYS-SPRITES · **READY** — Convert approved overworld references/sheets to ROM-ready OBJ assets  
  Depends on / blocked by: ARCH-006
- [ ] **SPRITE-003** · P2 · SYS-SPRITES · **READY** — Finish custom species battle/back/shiny/menu/footprint/cry integration where still open  
  Depends on / blocked by: SPEC-009; ARCH-006

## P5 Optional Content / World

- [ ] **QUEST-001** · P1 · SYS-QUEST · **READY** — Establish reusable one-time quest flag/state/reward scripting pattern  
  Depends on / blocked by: ARCH-003; GIFT-001
- [ ] **QUEST-002** · P2 · SYS-QUEST · **READY** — Implement Pallet side quest and Tyrogue reward  
  Depends on / blocked by: QUEST-001; GIFT-001
- [ ] **QUEST-003** · P2 · SYS-QUEST · **READY** — Implement Nidoran rescue/Spearow battle quest  
  Depends on / blocked by: QUEST-001
- [ ] **QUEST-004** · P2 · SYS-QUEST · **READY** — Implement museum puzzle and Sandshrew reward  
  Depends on / blocked by: QUEST-001; GIFT-001
- [ ] **QUEST-005** · P2 · SYS-QUEST · **READY** — Implement valve puzzle, Mystic Water reward, and hidden Rare Candy  
  Depends on / blocked by: QUEST-001
- [ ] **QUEST-006** · P2 · SYS-QUEST · **READY** — Implement Grimer+Muk Double Battle and Poison Barb reward  
  Depends on / blocked by: QUEST-001
- [ ] **QUEST-007** · P2 · SYS-QUEST · **READY** — Implement offering puzzle, noncatchable Haunter, and Spell Tag reward  
  Depends on / blocked by: QUEST-001
- [ ] **QUEST-008** · P2 · SYS-QUEST · **READY** — Implement Mansion/rooftop chase and female Eevee reward  
  Depends on / blocked by: QUEST-001; GIFT-001
- [ ] **QUEST-009** · P2 · SYS-QUEST · **READY** — Implement field-identification/tracking quest and Scope Lens reward  
  Depends on / blocked by: QUEST-001
- [ ] **QUEST-010** · P2 · SYS-QUEST · **READY** — Implement permanent submission of Pidgey/Rattata/Oddish and Mr. Mime reward  
  Depends on / blocked by: QUEST-001; GIFT-001
- [ ] **QUEST-011** · P2 · SYS-QUEST · **READY** — Implement Surf shoreline sequence, Tentacruel finale, and TM17 Earthquake reward  
  Depends on / blocked by: QUEST-001; TM-001
- [ ] **HOT-001** · P1 · SYS-HOT · **BLOCKED** — Implement four-control environment puzzle, gardener battles, Hawthorne, and one-time Tropius Gift flow  
  Depends on / blocked by: SPEC-010; GIFT-001
- [ ] **HOT-002** · P2 · SYS-HOT · **BLOCKED** — Apply final Saffron voice pass to approved clue/story beats  
  Depends on / blocked by: BLK-010
- [ ] **OAK-001** · P1 · SYS-GIFT · **READY** — Implement OWNED-species milestone reward ladder at 30/50/75/100/125/151  
  Depends on / blocked by: GIFT-001; TM-001
- [ ] **OAK-002** · P1 · SYS-TRAIN · **READY** — Implement 151-owned unlock, trainer package, healing AI inventory, loss/retry, and League-clear reset  
  Depends on / blocked by: OAK-001; ARCH-001; ARCH-003

## Task execution

For any task:

1. Confirm the task is `READY`.
2. Read the current specialist Implementation Contract.
3. Confirm dependencies and Symbol Registry allocations.
4. Branch from `sam-edition-dev` using `sam/<task-id>-<slug>`.
5. Prefix meaningful commits with the Task ID.
6. Open a PR to `sam-edition-dev` titled `[TASK-ID] ...`.
7. Run the task's acceptance tests plus applicable shared QA.
8. After merge/QA, update the Drive Backlog and refresh this mirror.

Do not create unregistered numeric IDs or solve blocked design questions in code.
