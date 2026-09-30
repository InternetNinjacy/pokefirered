# Pokémon: Sam Edition — GitHub Implementation Workflow

This repository is the implementation workspace for **Pokémon: Sam Edition**.

The active integration branch is `sam-edition-dev`.

## Source-of-truth order

1. Current explicit project decision.
2. Current Canon Authority Index.
3. Current specialist design authority.
4. Current specialist Implementation Addendum / Programmer Handoff and its Standard Implementation Contract.
5. Programming Readiness Registry:
   - Backlog = operational work queue
   - Symbol Registry = numeric/symbol allocation truth
   - Dependencies = dependency graph
   - QA Matrix = shared acceptance/regression tests
   - Blocking Decisions = unresolved inputs
   - Contract Coverage = implementation-contract coverage
6. Source code after a change has been merged and QA has passed.

Design documentation explains **what and why**. Source code becomes the truth for **what is actually implemented**.

## Stable task IDs

Every implementation change must carry the Backlog Task ID, for example `ARCH-003`, `TM-001`, or `GYM4-001`.

Do not create a parallel task numbering system in GitHub.

## Branch naming

Create task branches from `sam-edition-dev`:

```
sam/<task-id-lowercase>-<short-slug>
```

Examples:

```
sam/arch-003-symbol-registry
sam/tm-001-tm68-architecture
sam/gym4-001-celadon
```

A task may use more than one branch only when there is a concrete technical reason.

## Commit naming

Prefix meaningful commits with the Task ID:

```
ARCH-003: add Sam flag and variable constants
TM-001: add logical TM51-TM68 mapping
```

## Pull request naming

Use:

```
[TASK-ID] Short implementation description
```

Example:

```
[ARCH-003] Add central Sam Edition symbols
```

Target `sam-edition-dev` unless the current implementation plan explicitly says otherwise.

## Required PR body

Every Sam Edition PR should state:

- **Task ID**
- **Authority / requirements used**
- **Dependencies satisfied**
- **Symbol Registry entries used or added**
- **Implementation summary**
- **Must-preserve / out-of-scope checks**
- **Acceptance tests run**
- **Build result**
- **Known blockers or follow-ups**

Do not claim COMPLETE merely because code exists.

## Status mapping

Drive Backlog status is the project status authority.

- **READY** — may be implemented.
- **BLOCKED** — do not invent missing design or technical input.
- **IN PROGRESS** — active implementation branch/PR exists.
- **QA** — code is present; required acceptance/regression tests are running.
- **COMPLETE** — implementation is merged and required QA has passed.
- **DEFERRED** — intentionally postponed.

GitHub issue state does not override the Drive Backlog state.

## Implementation Contract rule

Before coding a feature, read its current Standard Implementation Contract.

At minimum verify:

1. Inputs / Dependencies
2. Required Outputs
3. Code / Data Surfaces
4. Assets
5. Persistent State / IDs
6. Must Preserve / Out of Scope
7. Failure / Recovery Behavior
8. Acceptance Tests
9. Completion Gate

If a required field is unresolved, keep that subtask blocked.

## Numeric resource rule

Never invent a Sam Edition numeric resource inside a feature branch.

All Sam-specific:

- species IDs
- move IDs
- item IDs
- ability IDs
- trainer IDs
- trainer class IDs
- flags
- variables
- sprite / trainer-pic IDs
- other reserved numeric resources

must come from the current **Symbol Registry**.

States marked **DERIVED** or **REUSE EXISTING** must not receive redundant persistent storage.

Script addresses remain linker-resolved; do not manually reserve raw addresses.

## QA rule

Every merged implementation task must pass:

- its specialist acceptance tests;
- its Backlog "Done When / Acceptance" criterion;
- applicable shared QA Matrix cases;
- a clean build;
- save/load and exit/re-entry tests for stateful features;
- focused regression showing unrelated systems were not changed.

## Documentation sync after merge

After a Sam Edition implementation PR merges:

1. Update the Drive Backlog status.
2. Record the GitHub issue / branch / PR / commit reference.
3. Update Readiness when the system-level state changes.
4. Update QA Matrix results when tests were completed.
5. Update Symbol Registry if implementation consumed or added an approved resource.
6. Update specialist implementation documentation only when implementation discoveries materially change the technical handoff.

Do not create a new numbered Design Bible / Index / Roadmap merely because code changed.

## Phase trackers

GitHub phase tracker issues group the Drive Backlog by P0–P7 for repository navigation.

They are views of the Drive Backlog, not a second source of project status.

Task-specific branches and PRs always use the stable Backlog Task ID.
