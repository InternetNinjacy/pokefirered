# QA-7B-OPENING-REPAIR — source reconciliation (2026-10-08)

Production inspected: `sam-edition-dev` at PR base `3d4e5462288363f71b67c6f13eb5958156dd4300`. This is a **partial repair checkpoint**, not an emulator sign-off.

## Confirmed directly in production source
- `src/oak_speech.c`: FireRed `sBlueNameChoices[0]` points to `gNameChoice_Green`, while Green independently has presets GREEN/SUSAN/AMY/JESS and `SaveBlock1.samEdition.greenName`. Scoped fix in PR #354 replaces only that Blue preset with BLUE.
- `data/maps/PalletTown_ProfessorOaksLab/scripts.inc`: `EventScript_RivalTakesStarter` removes `LOCALID_OAKS_LAB_RIVAL` immediately before adding independent `LOCALID_OAKS_LAB_GREEN`. Scoped fix in PR #355 keeps Blue's map object while adding Green.
- `data/maps/PalletTown_ProfessorOaksLab/map.json` already declares separate Blue and Green local IDs, with Green's map visibility controlled by `FLAG_TEMP_15`.
- `src/oak_speech.c` currently still references stock Oak-speech `graphics/oak_speech/rival` for Blue and the female player portrait as a temporary Green display. Portrait changes require checking the current Sprite/Art Asset Registry and locating exact approved source binaries; do not substitute stock or generate replacement art.

## Suspected, not proven
- The immediate Blue removal and the scene-3 Green trigger may interact with the reported Lab battle flow. Retaining Blue does **not** prove choreography, collisions or battle completion.
- Legacy labels mentioning Bulbasaur/Squirtle/Charmander are not themselves defects; the starter script's `givemon` uses Eevee/Pichu/Ditto.
- Intro palette/transparency/dimensions may still be incorrect; this checkpoint has no visually reviewed emulator frames.

## Runtime gate remains open
- PR #353 (`QA 7B-2`) is an open fail-closed three-starter mGBA RAM assertion probe, not passing evidence.
- The older QA Step 7B runbook was explicitly NOT RUN at its baseline.
- Run three isolated *new* SRAM games on an exact-hash ROM: Eevee, Pichu, Ditto. For each confirm intro portraits/names and the first approved battle (win/loss where applicable), check party species/level and distinct rival identities, perform battery save, close emulator, relaunch, load and reach Route 1.
- Preserve emulator version, ROM SHA256, per-branch recorded video/screenshots, party/flags/scene evidence and post-reload state.
- Do not mark QA Step 7B COMPLETE, merge red tests, or freeze a playtest candidate until the matrix passes.

## Integration boundaries
PRs #354 and #355 are deliberately independent and based on current production. Validate CI and affected runtime behavior before merging; do not cherry-pick historical opening branches wholesale.
