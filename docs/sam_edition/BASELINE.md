# Pokémon: Sam Edition — Codebase Baseline

Status: **LOCKED IMPLEMENTATION BASELINE**

## Upstream

- Upstream repository: `pret/pokefirered`
- Upstream baseline commit: `c75f352304d529f6ba92d4f74b9cf8b5c3810788`
- Target game: Pokémon FireRed, English, revision 0 / original release
- Build output: `pokefirered.gba`
- Required clean-baseline SHA-1: `41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc`

At the baseline commit, `config.mk` defaults to FIRERED / revision 0 / ENGLISH, and `firered.sha1` contains the required SHA-1 above.

## Sam Edition repository / branches

Repository: `InternetNinjacy/pokefirered`

- `sam-baseline` — immutable pointer to the untouched upstream baseline commit. Do not commit Sam Edition changes here.
- `sam-edition-dev` — integration/development branch for Sam Edition.
- Existing fork `master` predates the Sam Edition baseline setup and contains experimental commits. It is **not** the Sam Edition baseline and must not be used as the starting point for implementation.

## Workflow rule

1. Preserve `sam-baseline` unchanged.
2. Create implementation feature branches from `sam-edition-dev` for meaningful work units.
3. Merge/rebase back into `sam-edition-dev` only after the relevant build and regression checks pass.
4. Do not start gameplay implementation until the resource-allocation audit is accepted.
5. Do not claim a reproducible baseline build until `pokefirered.gba` has actually been built from `sam-baseline` and its SHA-1 has been checked.

## Current build gate — resolved prior evidence

Registry Blocking Decisions records a successful untouched-baseline build: Ubuntu 24.04.1 LTS, agbcc `da598c1d918402c42c0c0d7128ba14567f3175e9`, binutils 2.42, Git 2.43, Make 4.3, GCC 13.3; `make compare` OK and SHA-1 `41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc`. This audit did not rerun that build.

Modified Sam builds use the established `COMPARE=0` targets; the vanilla SHA must not be applied as a modified-ROM gate. Record the actual checkout, command, toolchain, result and generated artifact hash.
