# QA STEP 7 — Integrated runtime regression execution gate (2026-10-08)

Baseline at creation: `sam-edition-dev` @ `319c5750edd3c7d955eb93280c8f5807f6172a1e`.

## Evidence boundary

The dedicated `Sam Edition Production Build` workflow compiles the modified FireRed, verifies header/ROM size and emits a SHA-256 evidence artifact only. It is **not an emulator run**. Vanilla comparison `CI` red alone is not a Sam build failure.
The new `Sam Edition Host Regression` workflow executes the four existing Rocket and Thomas host/mini-harness tests on every production push and PR. These are actual tests, but do **not** run the assembled GBA ROM. The previous Step 1–6 static audits and prior specialist tests are not substitutes for player traversal.
**No assembled-ROM gameplay or full-game save/load test is claimed here.**

## Step 7 actual acceptance gate

- **Build baseline:** production head has successful dedicated modified-ROM build, recorded commit+size+game code+SHA256.
- **Host regression:** all four host tests pass on the same head. Fix any demonstrated test regressions using bounded changes; do not blindly merge historical branches.
- **Emulator, fresh save:** test Standard/Permanent (if applicable), each of Eevee/Pichu/Ditto starter branches, lab opening, rival tutorial, National Dex/Pokédex, item receipt, save/reload.
- **Eight Gym critical path:** tests for puzzles/gates, trainer defeat/retry, badge and TM rewards, full-Bag retries, world traversal and HM permissions, Satoshi state, scene persistence.
- **Rivals/Rocket:** Blue/Green/Thomas story-order and loss/retry, fossil branch, all four dossier entries, all 11 Rocket operation consumers, Five Island forced-growth warehouse and Doll/ending state.
- **League/Hall of Fame:** Lorelei → Blue → Agatha → Lance → Green, all three player starters, first/repeat branch and rewards, whiteout clears, Hall of Fame saves and game-clear unlocks, credits/exterior choreography, postgame League rerun.
- **Sevii/postgame:** Celio, network Ruby/Sapphire, boat/travel/return, gifts/static Mew/missable content and necessary postgame gates.
- **NG+:** start after Hall of Fame, preserve Trainer ID/OT and bags/PC/all party-to-box Pokémon, block before new starter+Pokédex, full-storage safe refusal, save/reload, keep prior Hall of Fame behavior as specified, win again and repeat NG+.
- **Adverse paths:** interrupted/revisited scenes, reset after defeat, bag and PC capacity boundaries, retry after saving/reloading and no duplicate rewards.

A run is PASS only if an actual emulator/ROM run is evidenced with scenario, ROM SHA, save-state setup, outcome, and reproduction trace. Report unrun as NOT RUN, not PASS.

## Production disposition

**STEP 7 HOST-GATE AUTOMATION PROVIDED; INTEGRATED EMULATOR REGRESSION NOT EXECUTED / OPEN.**
Do not set QA-ALL-002 or PLAYTEST-CANDIDATE-1 complete until the scenario matrix is executed and critical blockers resolved. Step 8 must not freeze a candidate merely from successful compile and host tests.
