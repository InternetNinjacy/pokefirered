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

## Immediate next audit

Continue with the shared core-engine layer:
- Permanent Mode downstream mechanics;
- Gift/outsider EXP behavior;
- starter/evolution logic;
- TM01–TM68 engine and compatibility;
- custom moves;
- custom species foundation;
- reusable Satoshi/rematch infrastructure.

Do not repeat the Gym branch archaeology above unless repository state changes after this audit.
