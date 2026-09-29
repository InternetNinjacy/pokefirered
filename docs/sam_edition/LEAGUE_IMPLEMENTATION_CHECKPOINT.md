# Pokémon: Sam Edition — League Implementation Checkpoint

Working repository: `InternetNinjacy/pokefirered`  
Working branch: `sam/league-phase5-integration`  
Draft PR: #12 -> `sam-edition-dev`  
Rule: actual GitHub/source/CI state wins if this file is stale.

## LAST VERIFIED GOOD STATE

- Latest verified source commit: `b22d3961c3b65d7e32cdffa0a04420465c5ba561` — “League dialogue: preserve approved Trainer casing”.
- CI run: `36625708495` — SUCCESS.
- Sam League static validation: PASS.
- Standard FireRed build: PASS.
- Modern build: PASS.
- Draft PR #12 remains OPEN and DRAFT and MUST NOT be merged until the League package is validated.

## COMPLETED

- Five locked Phase 4 League room map/tile payloads reconstruct reproducibly in CI.
- Independent derivative secondary tilesets are bound for Lorelei, Blue, Agatha, Lance, and Green.
- Lorelei / Blue / Agatha / Lance first-clear and rematch trainer parties are encoded and statically checked.
- Blue occupies the vanilla Bruno physical slot and has Fire / Water / Electric specialist branches wired to the documented starter-slot contract.
- Lorelei locked first-clear dialogue is installed.
- Agatha and Lance locked first-clear pre-battle, defeat, and advance dialogue is installed from the later approved Elite Four closure conversation.
- Lorelei, Agatha, and Lance rematches now each use their locked rematch pre-battle, defeat, and post-battle dialogue rather than vanilla/shared first-clear text.
- All three rooms route rematch trainer losses to dedicated `Text_RematchDefeat` labels and route immediate/repeat post-battle interaction by Hall-of-Fame state.
- Stale vanilla Lorelei Ice-specialist rematch text, Agatha Oak-centered vanilla dialogue, Lance Dragon-specialist text, and Lance's vanilla rival-Champion reveal are removed from the live room text.
- Static League validation guards the rematch dialogue labels/routing and prevents the stale Lorelei/Lance vanilla dialogue from silently returning.
- League first-clear/rematch routing now uses Hall-of-Fame state rather than the stale RS-link flag.
- Existing Hall-of-Fame reset still clears the four per-run Elite Four defeated flags.
- Green Champion/title-challenge exact competitive party construction is implemented with per-stat IVs, EVs, nature, ability slot, held item, and exact moves.
- All three Green Champion starter branches and +10 title-challenge branches are wired.
- Green first-clear Champion and postgame title-challenge trainer records, labels, reveal state, rematch state, and locked dialogue are integrated.
- Green no longer aliases Blue's rival-name storage. Dedicated persistent Green-name storage and battle-name routing exist with canonical GREEN fallback.
- Sam save reserve / trainer-flag capacity required by the League integration is centrally allocated and statically asserted.
- The Green naming regression is guarded: the custom placeholder token is `GREEN_NAME`, avoiding collision with FireRed's existing `GREEN` color constant.
- `PLACEHOLDER_ID_GREEN` is wired to `ExpandPlaceholder_GreenName`.
- Adaptive Gene is reconciled to authoritative item ID 245 in the League branch and Green's Ditto records now use the named `ITEM_ADAPTIVE_GENE` symbol.
- Adaptive Gene's League/runtime effect is implemented as a 1.20x multiplier on standard calculated damaging moves when the holder's original party species is Ditto. The original party species check preserves eligibility after Transform; self-damage is excluded.
- Transform preserves Ditto's held item in the live battle struct layout, so Adaptive Gene remains held after transformation.
- Green's trainer-owned held items are protected from permanent player farming through player-side Thief/Covet and Trick during her six League trainer records.
- The live Hidden Power calculation was verified against Green's locked IVs: Raichu = Ice / 70 BP; Machamp = Ghost / 70 BP.
- A field-by-field audit of all six Green first-clear/rematch arrays found no discrepancies in species, order, levels, items, moves, natures, ability slots, IVs, or EVs.
- First-clear Green uses `TRAINER_CLASS_CHAMPION`; postgame Green uses `TRAINER_CLASS_PKMN_TRAINER`.
- Both first-clear Green and the postgame title challenge are explicitly forced to `MUS_VS_CHAMPION`.
- Starter-dependent Green branch routing matches the locked contract: player Ditto -> Green Espeon; player Pichu -> Green Ditto; player Eevee -> Green Raichu.
- Static League validation now guards the Green naming fix and the League-side Adaptive Gene / anti-farming / Champion-theme integration.
- Current source passes static validation, standard FireRed compilation, and modern compilation.

## CURRENT

Manual implementation blocks are the controlling workflow. There is no active compiler blocker.

Next work block: League state/progression regression.

## NEXT — MANUAL 30–60 MINUTE WORK BLOCKS

1. **DONE — Repair overnight Green integration / restore green baseline.**  
   Fix the Green placeholder compiler collision, wire placeholder expansion correctly, add regression validation, and prove standard + modern builds are green.

2. **DONE — Green runtime/resource closure.**  
   Adaptive Gene League behavior, held-item anti-farming, Hidden Power behavior, exact competitive construction, Champion/title-challenge labels/music, and starter-branch routing are reconciled and verified.

3. **DONE — Elite Four dialogue + script closure.**  
   Recovered and installed the approved Agatha/Lance first-clear and Lorelei/Agatha/Lance rematch dialogue, separated rematch defeat/post-battle paths, added regression guards, and proved static/standard/modern builds green.

4. **League state/progression regression.**  
   Audit first-clear versus rematch selection, four per-run defeated flags, Hall-of-Fame reset, Green reveal/title-challenge state, save/reload reconstruction, doors/warps, blackout/retry behavior, and repeated League runs. Add static guards where practical.

5. **League paired battle-sprite integration — engine/hook layer.**  
   Implement the opening/defeat sprite presentation mechanism so each League opponent can show an opening battle sprite and a distinct defeat sprite after the win, without disturbing ordinary trainer battles.

6. **League paired battle-sprite integration — assets/registries.**  
   Convert/register the approved Lorelei, Blue, Agatha, Lance, and Green opening/defeat assets available in project authorities; use fallbacks only where explicitly permitted, identify any truly missing approved source art, and compile-test all five.

7. **League combat/AI/healing verification.**  
   Verify exact parties, held items, two-Full-Restore rules, strongest intended stock AI/switch behavior, Blue branches, Green competitive construction, Hidden Power results, and rematch levels against current specialist authorities. Fix source discrepancies only; do not rebalance from preference.

8. **Full League integration/regression pass.**  
   Run static validation plus standard/modern builds; inspect all five room bindings, script references, resource IDs, save allocations, trainer tables, dialogue symbols, and cross-map progression. Repair any remaining compile/link/data defects.

9. **Test-candidate packaging.**  
   Produce the coherent test ROM/build artifact if available through CI, record the exact commit, and write a concise human gameplay/visual QA route covering first clear, loss/retry, Hall of Fame, rematch, save/reload, rooms, sprites, dialogue, and all Blue/Green starter branches.

## BLOCKERS / DECISIONS NEEDED

No user decision is currently required.

Known implementation dependencies to resolve from source/authority:
- The Sam starter trio itself is not yet integrated on `sam-edition-dev`; League branch routing currently follows the locked intended starter-slot contract. Do not rewrite unrelated starter work unless it becomes necessary to make League testing coherent.
- Full player-facing Adaptive Gene acquisition/item presentation remains global starter/resource work; the League-side ID, held-item use, damage mechanic, and anti-farming behavior are complete.
- Final paired opening/defeat battle-sprite integration must use approved project assets/registries; do not invent final character art.

## DO NOT REDO

- Do not recreate or replace the five locked Phase 4 room payloads.
- Do not collapse the five custom League rooms back into the shared vanilla Pokémon League secondary tileset.
- Do not restore `FLAG_SYS_CAN_LINK_WITH_RS` as the League rematch gate.
- Do not change the locked E4 order: Lorelei -> Blue -> Agatha -> Lance -> Green.
- Do not restore Bruno as the second Elite Four member.
- Do not overwrite Blue with a Champion package from another project.
- Do not use Pokémon Weather content or any separate FireRed hack as Sam authority.
- Do not merge PR #12 until explicitly directed.
- Do not treat current Blue/Green fallback battle graphics as satisfying the final paired opening/defeat presentation.
- Do not claim runtime/gameplay-final status merely from compile success.
- Do not recreate Green's competitive trainer schema, save allocations, Adaptive Gene League behavior, or anti-farming guard; they now compile and are guarded.

## RECOVERY PROCEDURE

For every manual continuation block:
1. Read this checkpoint.
2. Inspect the actual branch head, recent changes, draft PR, and latest CI.
3. Reconcile this checkpoint to durable repository state.
4. Work only genuinely unfinished items.
5. Commit safe progress to the working branch.
6. Build/validate and repair ordinary failures within the same work block where practical.
7. Update this checkpoint last.
