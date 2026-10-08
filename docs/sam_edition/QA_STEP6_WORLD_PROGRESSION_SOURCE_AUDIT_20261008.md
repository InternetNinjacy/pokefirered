# QA STEP 6 — Whole-world progression and required-systems source audit (2026-10-08)

**Baseline:** `sam-edition-dev` @ `f90d1b777bb4c575e85fad548c0ef03dc036d78e` (merged Step 5 PR #343).
**Method:** KNOWN STATE → VERIFY LIVE DELTA → IMPLEMENT ONLY THE DELTA.
**Scope limit:** selected production-source registration/transition checks and the already merged Step 1–5 source audits. Not emulator traversal, new ROM build, test execution, or a complete automated graph proof of all Kanto/Sevii maps.

## Controlling source vs stale status

`docs/sam_edition/IMPLEMENTATION_BACKLOG.md` is a dated registry mirror, not live source evidence. Its RIV-016/ROCKET-002 text still references superseded fossil/Rocket blockers, whereas newer merged Thomas #302/#303, Rocket deliveries and Step 3/4 source audits established the later state. Do not reintroduce old implementations from it. Separate remaining sprite work and QA-ALL-002 must not be confused with an absent underlying gameplay system.

## Required progression/source findings

1. **New game / starter / Pokédex:** `src/new_game.c` initializes run state, national Pokédex compatibility and initial spawn, and preserves NG+ carryover when selected. `data/maps/PalletTown_ProfessorOaksLab/scripts.inc` has current starter scene, starter-branch rival scene, Pokédex grant and `FLAG_SYS_POKEDEX_GET`. Earlier merged system records mark START-001–004 and SPEC-011 complete. Do not claim startup scene/trainer/PC gating runtime tested.
2. **Kanto eight Gyms:** the source registrations, battle/reward scripts and map actors documented in `QA_STEP1_EARLY_GYMS_SOURCE_AUDIT_20261008.md` and `QA_STEP2_LATE_GYMS_SOURCE_AUDIT_20261008.md` stand. A particular badge/TM success and revisit state remains untested in emulator.
3. **Route 22 and Victory Road access:** `data/maps/Route22/scripts.inc` contains separate early and late rival event/scene state; Gym 8 source sets `VAR_MAP_SCENE_ROUTE22=3`. `data/maps/Route22/map.json` leads to Route22 North Entrance; `data/maps/Route23/map.json` includes Route22 North Entrance and Victory Road 1F/2F warps; `data/maps/Route23/scripts.inc` contains seven named badge gate NPC/trigger scripts in addition to the initial Boulder gate elsewhere; `data/maps/VictoryRoad_1F/scripts.inc` contains a switch/barrier mechanism, and the 1F map has 2F and Route23 warps. **Not yet proved:** each gate checks the intended current badge flag, map passability, field-move availability, boulder resets, or player path to Indigo Plateau. Legacy vanilla badge names remain in Route23 text/script identifiers and must be checked for current player-facing accuracy without assuming misbehavior from names alone.
4. **League entry/completion:** `data/maps/IndigoPlateau_PokemonCenter_1F/map.json` warps into Lorelei; current League source has room sequence and Hall-of-Fame routing as audited in Step 5. PR #327 removed obsolete Sevii/National Dex League door gate. Whiteout, repeat runs and NG+ are runtime gates, not source-defect findings in this step.
5. **Core required systems:** current backlog registry mirror marks play modes/Permanent, breeding, gifts, evolutions, TM/compatibility, species/encounters/fishing, ordinary trainers, Satoshi, side quests, title and NG+ production-complete. Presence/status is **not** proof that every reward is accessible, every species is obtainable, or all moves/flags behave in a completed ROM.
6. **Sevii and postgame:** `data/maps/OneIsland_PokemonCenter_1F/scripts.inc` retains Celio/Bill meeting and Network Machine Ruby/Sapphire state transitions. Five Island Rocket Warehouse and Rocket/Thomas crossovers were source-audited Step 4. This is **not** a complete islands-to-islands event-order or Ruby/Sapphire/Seagallop regression.
7. **Sprites:** current `SPRITE_002_REQUIRED_OVERWORLD_AUDIT_20261008.md` verifies Satoshi artwork registration, flags legacy Baz/Bushranger placeholders as superseded, and warns against equating asset-table entries to mapped gameplay appearances. `SPRITE-001` remains distinct; no cosmetic polish is a pre-playtest gate without a concrete required-asset regression.

## QA-ALL-002 integrated execution handoff (priority order)

- Fresh save: Standard and Permanent opening, all three starters, first rival outcome and retry; Oak's Pokédex grant; save/reload.
- Kanto travel: first four Gyms and later four Gyms with required story/event gates, Surf/Cut/Strength/Fly availability and appropriate badge permissions, item/TM rewards (including full bag), Satoshi interactions and map re-entry.
- Route22 early/late scene, Route22 North Entrance, all Route23 badge guards, Victory Road boulders/switches across floor transitions and re-entry, physical route to Indigo Plateau.
- Item/gift/statics/acquisitions: seeded representative encounters by rods/water/land, evolution methods, Pokédex registration, TMs and shop stock, S.S. Anne truck Mew and protected S.S. Anne departure/Seagallop conditions. Verify true missability, bag/PC capacities and save reload.
- Rival/Rocket/Thomas operations, dossier delivery order, major NPC rewards and retry branches as Step 3/4 carry-forward.
- Sevii travel, Celio Ruby/Sapphire progression, Five Island warehouse and relevant postgame islands/exits, League first-clear and repeat, Hall of Fame, credits, NG+ carryover and recursive replay as Step 5 carry-forward.
- Adverse-path checks: whiteout, interrupted or skipped optional content, repeated dialogue, full inventory/PC, re-entries, save/reload, Permanent loss-state transitions and NG+ Pokémon lock until starter + Pokédex.

## Disposition

**STEP 6 SELECTED SOURCE AUDIT COMPLETE, FULL WORLD-TRAVERSAL/GRAPH AND EMULATOR REGRESSION NOT EXECUTED.**
No proven new gameplay-source defect was established from the files inspected, so this PR changes audit documentation only. This does not certify all maps, trainer rosters, all awards, all encounter cells or required art; source claims above are narrowly scoped. Do not call PLAYTEST-CANDIDATE-1 ready from source audits. Step 7 must execute critical-path smoke tests, log defects with reproducible save/ROM SHA, patch and rerun. Step 8 freezes only a validated production head.
