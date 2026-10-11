# QA STEP 7B — First-boot / early-game emulator regression checkpoint (2026-10-08)

**Current source baseline:** `sam-edition-dev` @ `d06a973f24cad95b0074b86c0151fd1baa443fd3` (Step 7A #346).
**Build evidence:** `Sam Edition Production Build` run 37784441003 passed on this SHA; BPRE, 16777216 bytes; SHA-256 `9c9cdcb915151e8e5f69e8a4d650202bf068b6bcf18cb2bd238f96bc68135907`.
**Host evidence:** `Sam Edition Host Regression` run 37784441232 passed on the same SHA.
**Execution boundary:** At this checkpoint the current executor has no installed GBA emulator or ROM build toolchain; GitHub Actions uploads build evidence only, not the copyrighted ROM. Therefore no ROM boot, input replay, save creation, emulator screenshot, or save/reload result was actually produced. Do not mark scenarios PASS below until demonstrated on actual assembled ROM.

## 7B bounded runtime matrix

| Case | Setup/action | Mandatory acceptance | Execution |
|---|---|---|---|
| B01 | Load exact-SHA ROM in mGBA or equivalent with empty SRAM | Title draws without hang/crash, controls work, game mode/new-game choice functions | NOT RUN |
| B02 | Start standard run; name character and rivals as offered | Pallet opening, movement and script ownership progress without softlock | NOT RUN |
| B03 | Start one fresh save for each Eevee, Pichu, Ditto starter slot | Correct species and level in party, correct counterpart, intended Oak text/art; no stale vanilla content displayed | NOT RUN |
| B04 | For each starter branch, win first scripted rival battle | Correct battle trainer/team, return to map, once-only flags and NPC movement | NOT RUN |
| B05 | Reproduce first rival defeat and restart/revisit | No lost starter, invisible rival, scripted lock or double reward | NOT RUN |
| B06 | Progress Oak's Parcel and Pokédex acquisition | Pokedex functions after grant, intended National Dex scope available, progression to Viridian/Pewter | NOT RUN |
| B07 | Save/reload after starter, after rival, after Pokédex | Party/OT/Trainer ID, items, flags and location survive SRAM load | NOT RUN |
| B08 | Visit Viridian, Route 1/22, early Route 2/Viridian Forest and Pewter | All required entrances/exits, NPC collisions, checkpoint scripts and return travel remain traversable | NOT RUN |
| B09 | Repeat first-boot path in Permanent Mode | Correct mode startup, visible rules and whiteout behavior without softlock | NOT RUN |

## Test execution instructions (no copyrighted ROM in repository)

1. Build local clone of `sam-edition-dev` at the stated SHA using the documented modified-ROM configuration `GAME_VERSION=FIRERED GAME_LANGUAGE=ENGLISH GAME_REVISION=0 MODERN=0 COMPARE=0 make -j2 all`. A valid personal FireRed base is handled separately by the build environment; never publish game ROM.
2. Confirm `sha256sum pokefirered.gba` matches the SHA above **before running**. If the head moves, record the new build and fingerprint; don't combine logs across differing builds.
3. Run an emulator with clean `*.sav` for each starting branch, take emulator screenshots or video and record frame/input sequence for unexpected behavior. Do not use only save states as substitutes for battery SRAM save/reload.
4. Record each case as PASS, FAIL or NOT RUN, with emulator version, build SHA, setup, result, and saved reproduction. Do not misclassify static source registration as PASS.
5. For FAIL, open bounded defect work, fix only the demonstrated behavior, rebuild and rerun changed + adjacent cases. Keep release freeze blocked until emulator critical path passes.

## Source-specific watchlist

- `data/maps/PalletTown_ProfessorOaksLab/scripts.inc` contains starter-choice and rival branches with legacy symbol names and Bulbasaur/Squirtle/Charmander phrasing. Verify actual **player-visible** species, party, rival matchup and dialogue for Sam's Eevee/Pichu/Ditto design. The mere presence of legacy script labels is not sufficient proof of a defect.
- `src/new_game.c` keeps NG+ separate from normal new-game initialization; all B-series fresh runs must use a truly empty save for baseline testing.
- First-route Oak tutorial and Pokédex, Route22 early rival and progression gates are high-risk for scene-flag or save/reload problems.

## Disposition

**STEP 7B PREPARED / NO EMULATOR EXECUTION EVIDENCE.** Head build and host test are green, but B01–B09 are **NOT RUN**. Do not claim first boot or game progression verified; do not close Step 7 or freeze PLAYTEST-CANDIDATE-1.
