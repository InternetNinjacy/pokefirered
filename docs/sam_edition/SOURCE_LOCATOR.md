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

- `sam/core-001-004-current-stack-integration`
- production head: `0b7f1481134d13fbcdea90b7fb99edb01ce3b639`
- draft PR: #63
- base branch: `sam/gift-001-npc-trades` / draft PR #62

Runtime QA branch:

- `qa/core-001-004-current-stack-runtime`
- QA source: `59ce704108a16559047737d25723c663a6dc3188`
- successful run: `36958060624`
- QA ROM SHA-1: `a55794ae62ed5295a3c0bd2baf22e9ca10918d40`

This is the current delta-only production continuation point. The QA branch is evidence/instrumentation only and must not be used as a production ancestor.

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
