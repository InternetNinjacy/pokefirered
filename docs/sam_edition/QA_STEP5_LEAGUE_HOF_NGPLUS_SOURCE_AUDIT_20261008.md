# QA STEP 5 — League / Hall of Fame / NG+ source regression audit (2026-10-08)

Production baseline: `sam-edition-dev` @ `d6d391310df45e576c33cfa7fe221be17303fd67` (after merged QA Step 4 PR #342). Audit-only: no emulator execution, gameplay patch, ROM build, or host test executed in this step.

## Current authority and older work
- `docs/sam_edition/LEAGUE_FINAL_ASSEMBLY_CLOSURE_2026-10-07.md` records **League Final Assembly COMPLETE** from merged PRs #265, #267, #285, #289–291, #320, #327 and existing NG+ PR #252.
- Historical Phase 5 PR #12 is not a safe integration source. Do not reopen it wholesale.
- An earlier static closure is implementation evidence, not an emulator regression pass.

## Source-confirmed League chain
- Warps in `data/maps/PokemonLeague_{LoreleisRoom,BrunosRoom,AgathasRoom,LancesRoom,ChampionsRoom,HallOfFame}/map.json` lead in order **Lorelei → Blue → Agatha → Lance → Green → Hall of Fame**.
- The physically legacy-named `BrunosRoom` has `OBJ_EVENT_GFX_BLUE`. `data/maps/PokemonLeague_BrunosRoom/scripts.inc` dispatches three first-clear Blue trainers and three rematch variants using `VAR_STARTER_MON` 0/1/2. The `FLAG_DEFEATED_BRUNO` identifier remains compatibility state, not a Bruno battle.
- Lorelei, Agatha and Lance each dispatch first-clear/rematch trainer battles based on `FLAG_SYS_GAME_CLEAR`; win sets their room victory flag and opens their exit.
- `data/maps/PokemonLeague_ChampionsRoom/scripts.inc` dispatches six Green trainer records, with starter branches (2 Espeon, 1 Ditto, 0 Raichu), first-clear vs postgame selection by `FLAG_SYS_GAME_CLEAR`, persistent Green reveal and postgame intro flags, victory-only Champion completion, Oak choreography and Hall-of-Fame warp. Its Oak/Green-specific reaction speech is explicitly authority-open and the stale Blue-targeted line is intentionally omitted; this is not a discovered gameplay blocker.
- `data/scripts/hall_of_fame.inc` resets Lorelei, Bruno-slot/Blue, Agatha, Lance, Champion defeat flags and all six Green League trainer flags, plus `VAR_MAP_SCENE_POKEMON_LEAGUE`. `src/overworld.c` whiteout calls the shared League reset.
- `data/maps/PokemonLeague_HallOfFame/scripts.inc` enters the Hall of Fame after the recording effect and calls shared completion/reset, then `EnterHallOfFame`. `src/hall_of_fame.c` contains the Hall-of-Fame saving/display transition and routes to Indigo Plateau exterior credits. `data/maps/IndigoPlateau_Exterior/map.json` credits actor graphics use Green.

## Source-confirmed NG+ mechanics
- `src/main_menu.c` reads `FLAG_SYS_GAME_CLEAR` from the valid completed save to label the title option `NEW GAME+` and sets `gNewGamePlusRequested` on selection. It guards insufficient collection storage capacity without silently falling back to destructive vanilla New Game.
- `src/new_game.c` snapshots Trainer ID, bag/key items/Poké Balls/TMs/berries, PC items, registered item, complete boxed storage and special reserve storage; migrates the old party into available PC/reserve slots; restores those items/collection after the ordinary new-game reset; re-keys encrypted bag quantities; and clears prior-cycle `FLAG_SYS_GAME_CLEAR` on NG+ initialization. This supports recursive eligibility after another completion.
- `src/save.c` saves/loads the NG+ reserve tail with checksum handling, and `src/pokemon_storage_system.c` provides the reserve. This is structural evidence, not proof that every carryover/save/reload edge case is safe.

## Important unproved transitions / runtime gates
1. Verify by trace plus emulator that first Hall of Fame *actually sets and persists* `FLAG_SYS_GAME_CLEAR` before return to title, so `NEW GAME+` appears on a genuine first clear; sampled Hall-of-Fame map scripts alone do not contain that explicit assignment.
2. Traverse the actual room path and confirm every door close/open, rival trainer branch, per-run flag reset, defeat/whiteout retry, Champion loss and credits movement.
3. Verify postgame League reruns select all +10 packages, first/repeat Champion dialog, save/reload and Hall-of-Fame records.
4. Verify NG+ title unlock and start, retained Trainer ID/OT, inventory quantities, PC and party migration (including full storage), Pokémon quarantine until starter+Pokédex, old Hall-of-Fame records handling, pre/post-save reload and repeated NG+.
5. Verify the modified-ROM production workflow at the exact current branch SHA; none of these emulator checks or a new build has run in Step 5.
6. Existing Sprite-001 battle art closure remains its own workstream; source routing cannot certify sprite appearance.

## Step 5 disposition
**SOURCE AUDIT COMPLETE; EMULATOR REGRESSION NOT EXECUTED.** No demonstrated source defect in sampled production justifies changing gameplay here. The explicit first-clear `FLAG_SYS_GAME_CLEAR` setter should be traced during integrated QA; do not call NG+ runtime PASS solely because a menu checks that flag. Carry all listed emulator cases to QA-ALL-002 / Step 7. Proceed to Step 6 world-progression audit using newest `sam-edition-dev`, and do not freeze `PLAYTEST-CANDIDATE-1` on source inspection alone.
