# MEW-001 — S.S. Anne Truck Mew

Status: COMPLETE in production. PR #318 merged to `sam-edition-dev` at `3a6d5c63012ccbf397ae89c51f15a02db19bf781`. Full assembled-ROM playtest remains deferred.

## Locked player-facing behavior

- Mew is Lv. 50 exactly.
- The event is an optional secret, not a quest.
- After the S.S. Anne departs, the original harbor guard is retired and the harbor can be re-entered.
- Existing map geometry requires Surf to reach the isolated truck platform.
- The truck requires Strength to move.
- Moving the truck reveals a visible overworld Mew.
- Interacting with Mew starts a normal capturable static battle.
- Capture or defeat permanently resolves the encounter.
- Running or teleporting away leaves Mew available for another attempt.
- Two Vermilion NPCs provide vague truck/noise/meowing rumors only. They never name Mew or explain the solution.

## Implementation

### Persistent flags

- 0x36A `FLAG_STATIC_SS_ANNE_TRUCK_MEW_COMPLETE`
- 0x36B `FLAG_STATIC_SS_ANNE_TRUCK_MOVED`
- 0x36C `FLAG_HIDE_STATIC_SS_ANNE_TRUCK_MEW`
- 0x36D `FLAG_HIDE_VERMILION_SS_ANNE_GUARD`
- 0x36E `FLAG_HIDE_VERMILION_SEAGALLOP_SAILOR`

These were selected after current-production reconciliation; 0x368-0x369 are already owned by Celadon Gym state.

### Files

- `include/constants/flags.h`
- `data/maps/SSAnne_Exterior/map.json`
- `data/maps/SSAnne_Exterior/scripts.inc`
- `data/maps/VermilionCity/map.json`
- `data/maps/VermilionCity/scripts.inc`
- `data/maps/VermilionCity/text.inc`

### Harbor routing

Before S.S. Anne departure, the original ticket guard remains active. After departure, that guard is hidden and the ticket trigger allows free harbor re-entry. A separate Seagallop sailor remains available for later ferry service without restoring the old harbor block.

### Truck and Mew state

The truck interaction becomes relevant only after the S.S. Anne departure state reaches the normal post-departure value. Strength use sets the persistent truck-moved flag and reveals the Mew object. The Mew object remains visible across reloads until the battle is resolved by capture or defeat.

### Battle semantics

The encounter uses the ordinary scripted wild-battle path rather than the legendary-battle helper. Mew is generated at Lv. 50 and is normally capturable. Only `B_OUTCOME_CAUGHT` and `B_OUTCOME_WON` complete the event. Escape/teleport does not consume it.

## Deferred runtime validation

Full interactive validation belongs to the assembled-ROM playtest pass. Include these checks:

1. Before S.S. Anne departure, normal ticket/ship access is unchanged.
2. Immediately after departure, the harbor can be re-entered.
3. Reach the truck only through the intended Surf geometry.
4. Without Strength authorization, the truck does not move.
5. With Strength, the truck moves/reveals Mew once.
6. Mew is visibly present at Lv. 50 encounter point.
7. Capture permanently removes Mew.
8. Defeat permanently removes Mew.
9. Run/teleport leaves Mew available.
10. Save/reload after truck movement but before battle preserves revealed Mew.
11. Save/reload after completion keeps Mew gone.
12. Both Vermilion rumors remain vague and do not name Mew or explain Surf/Strength.
13. Seagallop ferry access remains usable later.
14. Existing Lava Cookie hidden item remains intact.


## Production closure

- Production PR: #318
- Merge commit: `3a6d5c63012ccbf397ae89c51f15a02db19bf781`
- Final feature head: `d950ba08ea2aad857d0ec17b44ed2c72087a7dde`
- Thread status: RETIRED FROM ACTIVE DEVELOPMENT
- Remaining Mew-specific work: assembled-ROM regression only.

The final PR CI run failed on duplicate Satoshi Viridian trainer-party definitions in `src/data/sam_satoshi_trainer_parties.h` and `src/data/sam_satoshi_viridian_parties.h`. That is a separate production build blocker and does not reopen MEW-001.
