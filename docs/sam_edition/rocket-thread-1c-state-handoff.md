# Thread 1C — Rocket organization and evidence state

## Production reconciliation

Thread started from `8fec01b87a765a6426941dc158a874ebe3c94221` (Mt. Moon PR #294). Five Island PR #295 merged during implementation; the slice was reconstructed onto `3d4063a825b914cbc9d8b50f9c8a00dd4b43e341`. The later documentation-only PR #296 was also reconciled at `8c3bbdaaae97ff1e4c446aca7dbbcf8209d7fdf2`. Its warehouse scripts, trainer records 900/901, ace-last engine hook, layout and progression are preserved. No historical branch ancestry was imported.

Authority: current Team Rocket Organization Decision Record and Implementation Addendum; Project Readiness Closure Decision Record, September 27 Event #1 exact-content lock; current Thomas/Mt. Moon specialist authority takes precedence over older Rocket fossil and Thomas encounter descriptions.

## Integrated scope

- Shared monotonic operation and evidence helpers accept exactly one centrally registered bit, reject unknown/combined bits, preserve unrelated saved bits, and do not depend on owning the Dossier.
- Rocket Dossier is a real Key Item with stock Fame Checker icon and ordinary field text pages. Its Bag name is `RKT. DOSSIER` to fit the existing 14-byte item-name buffer. Delivery 01/03/04 texts preserve approved words, with FireRed-compatible punctuation and text segmentation.
- Delivery 01 is acquired through the approved early Viridian theft/fence operation. Pages 03/04 are bound to the reader, but their event consumers belong to Thread 1D and are not unlocked here.
- Viridian operation appears only after the Pokédex/parcel-return milestone. Thief is noncombatant and flees; the ordinary fence uses Rattata Lv4 / Zubat Lv5, Single, no held items or healing items, basic early AI.
- Victory records Recovered Goods as transient event state and automatically returns the player to the Mart clerk. Exactly five Poké Balls and one Dossier are delivered with independent capacity checkpoints. A blocked Bag does not repeat the battle, duplicate rewards, or loop an automatic frame scene. Clerk retains shopping and a short approved thank-you line.
- Battle loss advances no persistent operation/reward/evidence state. NPCs reload for retry; both remain absent after victory. Ordinary Viridian, Green, Gym, Oak's Parcel and shop progression are preserved.
- NG+ retains its defined Key Item carryover and clears event variables through existing InitEventData. An already carried Dossier is reused; evidence starts empty for the new run.

## Allocations and consumer interface

| Symbol | Allocation | Rule |
| --- | --- | --- |
| ITEM_ROCKET_DOSSIER | 247 | Key Item, not registerable |
| TRAINER_ROCKET_VIRIDIAN_FENCE | 902 | NUM_TRAINERS 903; 900/901 preserved |
| VAR_SAM_ROCKET_OPERATIONS | 0x40A2 | Independent persistent completion bitset |
| VAR_SAM_ROCKET_EVIDENCE | 0x40A3 | Independent persistent approved-entry bitset |
| VAR_SAM_ROCKET_VIRIDIAN | 0x40A4 | 0 pending; 1 recovered; 2 goods returned/Balls owed; 3 Dossier owed; 4 complete |
| FLAG_HIDE_ROCKET_VIRIDIAN_OPERATION | 0x35D | Derived shared NPC visibility |
| Viridian objects | local IDs 11/12 | Thief (31,24), fence (32,24); approach (31,25) |

`include/constants/sam_rocket.h` owns the bit names. Scripts pass exactly one operation/evidence bit in `VAR_0x8004`, then `callnative Script_SamRocketCompleteOperation`, `Script_SamRocketCheckOperation`, `Script_SamRocketRecordEvidence`, or `Script_SamRocketCheckEvidence`. `VAR_RESULT` reports validity or whether the queried bit is present. Operation completion never implies evidence or grants rewards by itself; the owning event must complete its transaction before recording either.

Operation bit slots cover the currently named Viridian, Mt. Moon, Cerulean, Vermilion, Lavender, Celadon, Fuchsia, Saffron, Cinnabar, Viridian cleanup and Five Island operations. Unconverted vanilla events do not mark these bits automatically. Main-story flags remain owned by vanilla/current specialist scripts.

## Authority gap and remaining work

Delivery 02's older `FOSSIL STOCK - UNSECURED` / Super Nerd keeps the unchosen fossil outcome conflicts with the reopened Thomas theft in production. Evidence bit 1 is reserved but rejected by the helper, and the contradictory page is not bound. Current reconciled wording is required before Thread 1D attaches that entry. This does not block the independently complete shared layer/Viridian slice.

Thread 1D owns remaining operation conversions and evidence consumers, including Cerulean and Nugget Bridge entry hooks. Preserve the existing six Thomas encounters, reopened Mt. Moon encounter, and merged Five Island content. Do not restore obsolete Thomas Victory Road/postgame or older two-Grunt Viridian scenes. Do not grant player-owned rescue Pokémon without their exact specialist packages. SYS-ROCKET remains PARTIAL overall.

## Validation

`python3 tests/test_sam_rocket_state.py` passes: real compiled state helper, valid/invalid/combined bit requests, preservation, script-path execution for blackout, all Bag-capacity combinations, retries, exactly-five reward, NG+ carried Dossier, and unchanged production trainer/map/warehouse/Thomas source. Existing `tests/test_thomas_mt_moon.py` passes. Map JSON conversion, item generation, FireRed charmap preprocessing and new-text pixel-width checks pass. `git diff --check` passes. Full ROM compilation/linking is checked by the PR's seven-variant CI before merge. Human runtime/playthrough testing remains deferred.
