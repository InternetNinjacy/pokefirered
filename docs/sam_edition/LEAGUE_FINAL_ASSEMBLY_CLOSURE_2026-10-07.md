# Pokémon: Sam Edition — League Final Assembly Closure

Date: 2026-10-07

## Status

**LEAGUE — FINAL LEAGUE ASSEMBLY: COMPLETE**

Production branch at closure audit start: `497a28606d3226a9fcc06442f52a935afcdde815`.

Full assembled-ROM human playtesting remains deferred until the complete game is assembled.

## Final production sequence

`Lorelei → Blue → Agatha → Lance → Green`

Blue occupies the former Bruno physical room as Elite Four #2. The legacy Bruno map/local-script identifiers and `FLAG_DEFEATED_BRUNO` are retained only as compatibility identifiers for that physical slot; Bruno is not restored as an opponent.

## Production changes completed in this workstream

### PR #320 — Champion reset / credits identity
Merged as `a075bb585d8189c14ff93fbff7aab66cc2c4e465`.

- Replaced obsolete vanilla Blue Champion trainer-flag resets with all six Green Champion/postgame trainer flags in the shared League reset.
- Removed duplicate Green flag clearing from the Hall of Fame room.
- Changed the post-Hall-of-Fame Indigo Plateau departing-Champion object from Blue to the approved Green overworld fallback.
- Preserved the existing Hall of Fame and credits choreography.

CI for the reconciled PR head passed the configured build matrix.

### PR #327 — League entrance / repeat-run gate
Merged as `041390db33e2c7aadfe08c3e1de444efb668c4b0`.

- Removed vanilla FireRed's National Dex / Sevii completion gate from the Indigo Plateau League entrance.
- Preserved the Indigo Plateau respawn setup.
- Preserved all unrelated Sevii progression.
- Restored unconditional access to the assembled League for the first clear and repeat postgame runs.

CI run #1176 passed FireRed, FireRed rev1, FireRed rev10, LeafGreen, LeafGreen rev1, LeafGreen rev10, and Build Modern.

Historical PR #325 was retired as stale and replaced by #327 on current production ancestry.

## Verified preserved production work

The final audit confirmed that the following already-merged work remains intact:

- Blue Elite Four #2 / former Bruno-room integration from PR #265.
- Lorelei, Agatha, and Lance core League work from PR #267.
- Green Champion trainer/data package and Champion/postgame routing from PR #285.
- Green approved battle-art integration and exact Champion dialogue/state work from PRs #289–#291.
- Hall of Fame recording/save flow.
- Existing credits flow.
- New Game Plus eligibility and recursive completion implementation from PR #252.

## Final state-machine audit

The merged production source now satisfies all of the following:

- Room warps form the required order: Lorelei → Blue → Agatha → Lance → Green → Hall of Fame.
- Green has all three first-clear Champion branches and all three +10 postgame title-challenge branches.
- `FLAG_GREEN_CHAMPION_REVEALED` is persistent across a loss so the surprise reveal does not replay.
- `FLAG_GREEN_TITLE_CHALLENGE_SEEN` persists the postgame title-challenge framing.
- Green League losses use ordinary whiteout behavior.
- Whiteout runs the shared League reset, clearing the full per-run Elite Four/Green state and restarting the next attempt from the beginning.
- The shared League reset clears all six Green League trainer flags and contains no obsolete vanilla Blue Champion trainer-flag reset.
- Hall of Fame sets/preserves `FLAG_SYS_GAME_CLEAR` as the first-clear/postgame discriminator.
- NG+ clears prior-cycle `FLAG_SYS_GAME_CLEAR` only when the new cycle begins, allowing a later Hall of Fame to unlock another recursive NG+ cycle.
- The obsolete Sevii/National-Dex League door closure is absent.
- The post-Hall-of-Fame exterior scene uses Green rather than Blue in the departing-Champion slot.

## Documentation synchronization

Current Postgame Rematch System decision and implementation authorities were synchronized on 2026-10-07 to supersede older Blue-#4 / Green-immediately-after-Blue wording. Current authority now explicitly uses Lorelei → Blue → Agatha → Lance → Green for both first-clear and repeat League runs.

## External work not owned by this workstream

SPRITE-001 remains a separate asset workstream. Any still-unfinished approved opening/defeat battle-sprite pairs for League members are owned there and do not reopen the completed League room/order/Hall-of-Fame/NG+ assembly.

## Blockers

None within League Final Assembly.

## Handoff

Do not reopen the old Phase 5 branch or historical PR #12 as an integration source. Future League changes must start from current `sam-edition-dev` and preserve this closure unless canon is explicitly reopened.
