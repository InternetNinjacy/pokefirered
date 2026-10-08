# QA-7B-OPENING-REPAIR — source reconciliation (2026-10-08)

Production inspected: `sam-edition-dev` at PR base `3d4e5462288363f71b67c6f13eb5958156dd4300`. This is a **partial repair checkpoint**, not an emulator sign-off.

## Confirmed directly in production source
- `src/oak_speech.c`: FireRed `sBlueNameChoices[0]` points to `gNameChoice_Green`, while Green independently has presets GREEN/SUSAN/AMY/JESS and `SaveBlock1.samEdition.greenName`. Scoped fix in PR #354 replaces the complete Blue preset list with the locked BLUE/DEREK/PJ/DILLON, preserving Green's independent GREEN/SUSAN/AMY/JESS list.
- `data/maps/PalletTown_ProfessorOaksLab/scripts.inc`: `EventScript_RivalTakesStarter` removes `LOCALID_OAKS_LAB_RIVAL` immediately before adding independent `LOCALID_OAKS_LAB_GREEN`. Scoped fix in PR #355 keeps Blue's map object while adding Green.
- `data/maps/PalletTown_ProfessorOaksLab/map.json` already declares separate Blue and Green local IDs, with Green's map visibility controlled by `FLAG_TEMP_15`.
- `src/oak_speech.c` currently still references stock Oak-speech `graphics/oak_speech/rival` for Blue and the female player portrait as a temporary Green display. PR #356 independently extracts the exact approved historical `sam/opening-intro` Blue and Green PNG + JASC palette blobs (64x96 indexed PNG; 32-color palettes) and binds their initial and naming-return display paths. Build/visual palette and transparency QA remain outstanding; do not substitute stock or generate replacement art.

## Applicable Blue/Green authority verified
- Green Decision Record v1.0: the mandatory, non-victory-gated Oak's Lab battle belongs to Green immediately after starter selection; her opening repeat and post-battle lines are locked.
- Blue Decision Record v1.0: Blue's first solo encounter is Route 22, not an Oak's Lab battle. Do **not** re-enable vanilla Blue Lab trainerbattles to address this defect.

## Suspected, not proven
- The immediate Blue removal and the scene-3 Green trigger may interact with the reported Lab battle flow. Retaining Blue does **not** prove choreography, collisions or battle completion.
- Legacy labels mentioning Bulbasaur/Squirtle/Charmander are not themselves defects; the starter script's `givemon` uses Eevee/Pichu/Ditto.
- Intro palette/transparency/dimensions may still be incorrect; this checkpoint has no visually reviewed emulator frames.

## Runtime gate remains open
- PR #353 (`QA 7B-2`) is an open fail-closed three-starter mGBA RAM assertion probe, not passing evidence. Its failed workflow run 37807775265 exited in `drive_opening`: never reached PlayersHouse_2F, read world (0,0), no active tasks and no party. This is a harness/intro navigation failure until independently reproduced as an in-game opening defect; it never reached the starter acquisition assertion.
- The older QA Step 7B runbook was explicitly NOT RUN at its baseline.
- Run three isolated *new* SRAM games on an exact-hash ROM: Eevee, Pichu, Ditto. For each confirm intro portraits/names and the first approved battle (win/loss where applicable), check party species/level and distinct rival identities, perform battery save, close emulator, relaunch, load and reach Route 1.
- Preserve emulator version, ROM SHA256, per-branch recorded video/screenshots, party/flags/scene evidence and post-reload state.
- Do not mark QA Step 7B COMPLETE, merge red tests, or freeze a playtest candidate until the matrix passes.

## Integration boundaries
PRs #354 and #355 are deliberately independent and based on current production. Validate CI and affected runtime behavior before merging; do not cherry-pick historical opening branches wholesale.

## Scoped repair PRs and validation checkpoint
- #354: full approved Blue preset correction; production ROM build, host regression, emulator boot smoke and RAM capture checks passed at the recorded head; broader CI/navigation jobs must still settle before merge.
- #355: retain Blue object when Green is introduced; production build, CI, host regression, generic boot smoke, RAM capture and scripted navigation check all passed at commit `73937d0289150c06e434fe32fc447ae2c86e1697`. These generic tests do not prove the Green battle cannot freeze, Blue's collision/movement is correct, or save/reload/Route 1 functionality.
- #356: exact four historical approved opening Blue/Green asset binaries + scoped loader bindings; awaiting full CI and emulator visual inspection, and not yet merged.

## PNG integrity remediation and production merge delta
- PR #354 was merged into `sam-edition-dev` with merge SHA `5587e96bc067652f92d8eae6444aa982f14f875f`. Blue's locked BLUE/DEREK/PJ/DILLON presets are now production source.
- PR #356 initially failed CI build due to malformed historical indexed PNG PLTE header/CRC, not invalid C portrait wiring. The recovered Blue and Green source images each declare a 768-byte palette despite containing a 696-byte PLTE followed by a valid 1-byte tRNS transparency chunk. Repair commit `e1f2f4520340a65b9b1a99a0e67bb237763895e9` changes only PLTE length fields and PLTE CRC32 in the two PNG blobs; all other PNG bytes, including indexed art, transparency and IDAT pixels, remain untouched. All five PNG chunk CRCs were reverified for both. Rebuild and actual emulator visual inspection remain required before merging.
- Because production advanced with #354, reconcile/rebase #355 and #356 against new production before further integration. Keep all outstanding runtime test gates open.

## POST-MERGE STATUS — 2026-10-08 (supersedes older pending wording above)

Production `sam-edition-dev` now includes all three bounded opening repairs:

- PR #354 merged, SHA `5587e96bc067652f92d8eae6444aa982f14f875f`: canonical Blue default names BLUE/DEREK/PJ/DILLON, separate from Green.
- PR #355 merged, SHA `41f42abcb3ed4ffd46e91ace6258308eccce9ae3`: retains the independent Blue Lab object while Green is introduced, and adds this QA checkpoint.
- PR #356 merged, SHA `128b9cc7232e722c791633f27ed5cbf4aad7ba8f`: binds approved historic Blue/Green opening portraits with minimal PNG container repairs; approved Sam player images remain intact.

Before merge, each final PR head passed the six existing workflows: production build, CI, host regression, emulator boot smoke, scripted navigation probe and live party RAM capture. This is **not** evidence of an uninterrupted three-starter opening through the Green battle and battery save/reload.

A combined-production-head CI was queued at first readback; retain **QA-7B OPEN / HUMAN EMULATOR GATE PENDING** until an exact-ROM SHA run genuinely verifies Eevee, Pichu and Ditto independently through first Green battle, battery SRAM save, full emulator restart/reload and Route 1. PR #353's failed acquisition test is not a passing result. Preserve separate defect classifications: corrected source defects vs unconfirmed freeze root cause.
