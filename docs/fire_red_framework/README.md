# Pokémon FireRed ROM-Hack Programming Framework

This directory defines the reusable programming-management framework for FireRed ROM hacks based on pret/pokefirered.

The framework is project-agnostic. Project-specific records live in that project's own documentation directory.

## Purpose

The framework exists to reduce repeated discovery work. A project should preserve durable knowledge about:

- repository and baseline identity;
- authority/source-of-truth order;
- stable work IDs;
- dependencies and blockers;
- code/data locations;
- branches, pull requests, and commits;
- build and runtime QA evidence;
- known-good ROM/build hashes;
- resource allocations;
- implementation status.

The normal workflow is therefore:

1. Refresh live repository state.
2. Load the project index.
3. Load only the authority sections and code surfaces relevant to the selected work item.
4. Verify deltas from the recorded state.
5. Implement on a feature branch.
6. Build and run required QA.
7. Update the project index and authoritative project registry.
8. Merge only when the project's merge gate is satisfied.

Do not repeatedly rediscover a system from scratch unless its architecture, authority, or implementation surface has materially changed.

## FireRed baseline assumption

Projects using this framework target Pokémon FireRed and a pret/pokefirered-derived source tree.

Each project must still record its exact upstream commit, game revision, language, expected clean-build hash, and project integration branch. Do not assume those values are identical across projects.

## Layers

### Layer 1 — Generic FireRed framework

Reusable across FireRed hacks:

- workflow conventions;
- project-index field definitions;
- source-locator structure;
- dependency tracking;
- QA evidence structure;
- live-state refresh rules.

### Layer 2 — Project instance

Specific to one ROM hack:

- project name;
- baseline commit;
- integration branch;
- authority documents;
- work IDs;
- resource allocations;
- feature branches and PRs;
- current implementation status;
- known-good builds;
- project-specific source locations.

## Trust model

A project should distinguish four different kinds of truth:

1. **Design/canon authority** — what the project intends.
2. **Registry/index state** — what work is authorized, blocked, active, or complete.
3. **Verified source state** — what code actually exists on a named ref.
4. **QA evidence** — what has actually built and passed runtime/regression testing.

None of these should silently substitute for another.

## Refresh rule

At the beginning of a programming session:

- fetch the current integration-branch head;
- inspect relevant open/draft PRs and feature branches;
- compare recorded refs against live GitHub;
- mark stale entries before implementation;
- refresh only affected source-locator records unless a structural change requires a wider rescan.

A full repository rescan is appropriate when:

- the upstream baseline changes;
- a major engine refactor lands;
- a large integration branch reorganizes source surfaces;
- the project index is known to be stale or incomplete.

## Work-item minimum record

Every programming work item should record:

- stable ID;
- title;
- system/category;
- status;
- priority;
- dependencies;
- blockers;
- governing authority;
- source/code surfaces;
- branch;
- PR;
- relevant commits;
- acceptance tests;
- build result;
- runtime QA result;
- known-good artifact hash when applicable;
- last verified ref/date.

## Source Locator

The source locator is not a copy of the repository tree. It is a curated map from gameplay/system concepts to the files and symbols programmers actually need.

Example:

```yaml
starter_selection:
  files:
    - src/new_game.c
    - data/scripts/...
  symbols:
    - VAR_...
  notes:
    - "Selection and rival assignment are coupled."
```

Only add locations that have been verified in source.

## Dependency graph

Dependencies should use stable work IDs whenever possible.

A work item may be:

- independent;
- sequentially dependent;
- blocked by an unresolved design decision;
- blocked by resource allocation;
- blocked by integration/QA;
- safe to perform in parallel.

The project index should make this explicit so scheduling does not have to be reconstructed from prose.

## QA evidence

"Code exists" is not equivalent to "complete."

Record separately:

- compile/build pass;
- static/source verification;
- emulator/runtime pass;
- save/load persistence pass;
- regression pass;
- artifact hash;
- source commit used for QA.

## Branch discipline

Project-specific branch naming may vary, but every feature branch must map back to a stable work ID or clearly defined meta task.

Framework/meta work should not be mixed into gameplay branches unless necessary.

## Reuse for a new FireRed hack

For a new project:

1. Copy the project-index template.
2. Record the exact FireRed baseline.
3. Record the project's authority hierarchy.
4. Scan the repository and populate the initial source locator.
5. Import the project's implementation backlog/dependency graph.
6. Record resource allocations.
7. Establish the integration branch and feature-branch convention.
8. Begin implementation using delta verification rather than repeated discovery.


## Reusable FireRed source map

The verified baseline engine map is maintained in:

- `docs/fire_red_framework/FIRERED_SOURCE_LOCATOR.md`

Future FireRed projects should inherit that map first and record only project-specific deltas unless they use a materially different pokefirered baseline.
