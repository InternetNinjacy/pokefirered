# QA STEP 3 — Blue, Green, Thomas rival source audit (2026-10-08)

**Audited source:** `sam-edition-dev` at `2c46707649db5888de60b8e48f6fc2d7e28b4bed`.

**Scope:** Static source inspection only. No emulator or full campaign runtime regression was performed. No source-confirmed gameplay regression justified code changes.

## Blue
- League slot 2 resides at `data/maps/PokemonLeague_BrunosRoom/scripts.inc`, with Water / Fire / Electric first-clear and rematch trainer package branches.
- Starter selection branch comments and trainer references are present; full starter-route simulations and all six battle loadouts have not been run in emulator.

## Green
- `src/data/trainers.h` contains Oak, S.S. Anne, Celadon, Fuchsia, Saffron, Three Island, Viridian, Champion, and postgame starter-dependent packages.
- Verified mapped scripts reference Green in Oak's Lab, S.S. Anne 2F Corridor, Three Island, and Champion room. `PokemonLeague_ChampionsRoom/scripts.inc` uses the three Espeon/Ditto/Raichu Champion and postgame families and reveal flags.
- Open historical PRs #264 and #269 remain unmerged with outdated ancestry. Their existence does not prove code absent; neither should be bulk merged. A complete map-by-map encounter and defeat/retry simulation remains necessary.

## Thomas
- `MtMoon_B2F/scripts.inc` has the Thomas theft encounter and fossil-result flags.
- `CinnabarIsland_PokemonLab_Entrance/scripts.inc` gates the non-battle Lab continuity by Thomas arc stage; the Experiment Room remains the standard fossil-revival system.
- `PokemonMansion_B1F/scripts.inc` includes the Cinnabar Thomas battle and arc-stage gate; `ViridianCity_Gym/scripts.inc` includes Thomas's final battle and handoff.
- Live `docs/sam_edition/THOMAS_CINNABAR_FOSSIL_CONTINUITY.md` explicitly marks `RIV-016 COMPLETE` and `BLK-THOMAS-FOSSIL CLOSED`; later language supersedes older notes in the same document. Do not reopen a closed blocker or add an eighth battle.
- Dedicated source test scripts exist: `tests/test_thomas_mt_moon.py`, `tests/test_thomas_cinnabar_lab.py`, `tests/test_thomas_cinnabar_fossil_battle.py`. Their existence is established; this audit did not execute these host tests or emulator gameplay.

## Production build
The dedicated Sam Edition Production Build completed successfully for the audited SHA (workflow run `37769248263`). Legacy vanilla comparison CI failed on that head, as expected for edited ROM contents.

## Exit / Step 4 handoff
**STEP 3 STATIC AUDIT COMPLETE; runtime rival QA pending.** No unsafe historical PR merge or unrelated gameplay change was made. Required integrated regression: starter permutations; rival chronological encounter gates; win/loss/retry; defeated flags; Mt. Moon theft branch; Cinnabar Lab/Mansion/Viridian ordering; Blue League and Green Champion rematch/Hall of Fame.

**STEP 4 — Team Rocket:** reconcile current `sam-edition-dev`, inspect Rocket operation/evidence dependencies and Thomas crossovers, compare stale #244 and individual delivery PRs against source, validate warehouse and endgame state paths, fix only confirmed live defects, then stop with Step 5 League handoff.
