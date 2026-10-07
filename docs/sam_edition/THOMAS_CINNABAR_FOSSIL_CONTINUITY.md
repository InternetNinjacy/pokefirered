# RIV-016 — Cinnabar fossil continuity reconciliation

Starting production: `8c3bbdaaae97ff1e4c446aca7dbbcf8209d7fdf2`.
Branch: `sam/thomas-cinnabar-fossil-continuity`.
PR: `#298`.
Feature head: `c8dbc5abc890810e0a5b7db768c995ec928201c5`.
Ending gameplay production / merge: `aa3d3859d44aeb2b27334a5eda08b9b683733e82`.
Final seven-variant CI: `37663794925` — PASS.
Integration refreshed after parallel PR #297 merged into production `53ef5073bda7ee7c7abca9e27310eab9f2ce2c36`. Only overlapping documentation required resolution; current Rocket source/allocations were preserved. PR #298 then merged the independent Lab slice into `sam-edition-dev` at `aa3d3859d44aeb2b27334a5eda08b9b683733e82`.

Classification: **A, battle authority closed / implementation pending**. BLK-THOMAS-FOSSIL is **DESIGN-CLOSED** as of Thread 02 on October 7, 2026. The Thread 01 blocker snapshot below is retained only as historical provenance.

## Authority reconciliation, before coding

Authority order: current bounded-thread instruction; October 6 Mt. Moon reopening Decision Record / Implementation Addendum; October 5 terminal Thomas closure for non-conflicting later records; non-conflicting September 29 exact specialist dialogue; current Cinnabar Lab/campus and acquisition authorities. Current Registry, Design Bible v1.119, Canon Authority Index v1.49 and active PR #297 allocation contract were inspected. Uploaded older encounter records are historical acquisition provenance, not current Thomas authority.

| Continuity element | Authority says | Starting live production has | Delta |
|---|---|---|---|
| Mt. Moon stolen-fossil state | Thomas retains Miguel's unchosen fossil, after victory only | Scene 0x408B: 3 stole Dome, 4 stole Helix; 2 pending battle/theft | Already complete, reuse unchanged |
| Player's kept fossil | Permanently retained until legitimate revival | Transaction-safe original fossil acquisition | No change |
| Cinnabar fossil revival | Helix/Omanyte, Dome/Kabuto, Old Amber/Aerodactyl | Existing revival and authored LAB ownership delivery | No change |
| Opposite-fossil researcher | Separate university specimen after successful original revival | ResearchRoom handoff, capacity-safe, uses restoration state and fossil flags | No change; flags cannot be used to infer original choice after handoff |
| Thomas Lab hook | Non-battle exit after restoring stolen fossil; exact September 29 text expressly referenced by reopening | No Thomas object or dialogue | Implement independent non-battle exit scene |
| Thomas Mansion hook | Existing current encounter preserved; older fossil debut requirement reasserted by reopening | B1F stage4 battle to stage5, trainer788, fixed six-Pokémon Single | Preserve current routing pending roster reconciliation |
| Fossil-specific Thomas branch | Dome stolen -> Kabuto/Kabutops; Helix stolen -> Omanyte/Omastar | Mt. Moon scene stores provenance; Mansion does not consume it | Lab consumes completion state; Mansion data remains blocked |
| Trainer party dependency | Old fossil packages Lv45/Mystic Water, Kabutops Rock Slide/Brick Break/Water Pulse/Protect; Omastar Surf/Ice Beam/AncientPower/Protect | Protected Mansion party Claydol43/Houndoom44/Magneton44/Seadra45/Machamp46/Salamence47; no Gengar | Exact fossil sets found, but no approved mapping into current roster, Gengar package or new format/traits contract |
| Dialogue dependency | Lab text closed, no battle/crime; old Mansion dialogue assumes Gengar+fossil and theatrical Thomas | Current Mansion dialogue/characterization preserved by newer closure | Lab exact text valid; do not overwrite current Mansion dialogue wholesale |
| Completion/progression state | One-time Lab exit; fossil remains Thomas's property; no player reward | Existing main arc4/5, quit state and normal event reset | Add independent Lab complete/hide flags; do not advance main arc |

The old Power Plant prerequisite is retired by the October 5 route; no live Thomas Power Plant completion state exists to consume. The independent Lab overlay uses the existing Cinnabar encounter window (arc stage4, after Silph and before Mansion), completed Mt. Moon theft (scene3/4), no quit flag, and no prior Lab completion. It does not create another operation/evidence state or gate Mansion, Gym7, Secret Key or fossil revival. If the player clears Mansion first, the preview scene is suppressed rather than playing out of order. No additional fossil acquisition or inventory transaction occurs: the approved dialogue is the representation of Thomas's private revival; the completion flag records the witnessed exit, not a second fossil/species branch.

## Implemented independent slice

Lab Entrance receives one stock Rocket actor at (6,7), local ID2, and an automatic frame scene. All original Lab Entrance objects, warps, background events and scripts remain; its original ready-fossil transition still runs first. All other Lab/Mansion maps, six Thomas trainer records/parties/traits/dialogue, and Mt. Moon source remain byte-identical to the starting production checkpoint. Player arrival tiles are cleared before Thomas walks to the exit; no permanent path obstruction is added. Exact approved wording is preserved with textbox wrapping only. No battle, reward, item removal, Pokémon transfer, main arc advancement or new Rocket evidence is added.

Resources centrally allocated before coding:
- `FLAG_THOMAS_CINNABAR_LAB_COMPLETE = 0x35E`, ordinary persistent current-run event flag.
- `FLAG_HIDE_THOMAS_CINNABAR_LAB = 0x35F`, derived persistent visibility.
- `VAR_TEMP_0` is an entry-reset frame trigger; no new persistent variable.
- Existing `VAR_MAP_SCENE_MT_MOON_B2F = 0x408B` and `VAR_THOMAS_ARC_STAGE = 0x40A1` are read, never changed by this scene.
- No trainer ID allocated; 784–789 and 847 unchanged. Active PR #297 owns 902, 0x35D and 0x40A2–0x40A4; Five Island owns 900/901. These are not consumed here.

## Historical blocker snapshot — superseded by Thread 02

This was the state when Thread 01 retired and is retained only as provenance. Thread 02 closes these questions in `THOMAS_CINNABAR_FOSSIL_BATTLE_AUTHORITY.md`.

The exact fossil sets and Lab dialogue were **found**, not missing. Thread 01 still needed:
1. approval for how fossil45 joined the current full six-member Mansion roster;
2. reconciliation of the older Gengar+fossil opening with the current roster lacking Gengar;
3. Single-versus-Double resolution for the current Mansion package; and
4. Mansion dialogue / Lab-before-battle treatment.

No older all-Double/Gastly lineage, Power Plant gate, Victory Road or postgame package was silently restored. No stale branch was merged.

## Thread 02 authority closure — October 7, 2026

Current explicit instruction closes the remaining party identity question: **Seadra is replaced by the stolen-fossil branch for the remainder of Thomas's battles from Cinnabar Mansion forward.** This is a permanent active-battle-team substitution, not a one-battle cameo. The current approved seven-battle cadence therefore ends with fossil participation at both Cinnabar Mansion and Viridian Gym; Kingdra no longer appears in Thomas's Viridian battle.

The implementation-ready details are defined in `docs/sam_edition/THOMAS_CINNABAR_FOSSIL_BATTLE_AUTHORITY.md`. In summary:
- Cinnabar Mansion remains the existing trainer 788 **Single Battle**.
- Gengar is not reintroduced.
- Seadra Lv45 is replaced by Kabutops Lv45 or Omastar Lv45 using the already-locked Mystic Water fossil package.
- Viridian remains the existing trainer 789 **Single Battle**.
- Kingdra Lv52 is replaced by the same branch fossil at the current production slot level/IV tier; fossil-specific item/moves come from the closed Thomas specialist progression.
- The fossil branch is read from the Mt. Moon theft state directly. The Lab scene remains optional/non-gating.
- Current Mansion/Viridian characterization and progression stay intact; no stale Gengar-dependent dialogue, all-Double rule, Power Plant, Victory Road, or postgame Thomas package returns.
- Secret Key, Mansion traversal, loss/retry, Viridian Doll handoff, Giovanni routing, and seven-battle cadence remain unchanged.

BLK-THOMAS-FOSSIL is **DESIGN-CLOSED / IMPLEMENTATION-PENDING**. The next thread may implement only this battle-data/script delta and its focused tests. SYS-THOMAS remains PARTIAL until that implementation is merged and the deferred assembled-ROM playtest is eventually performed.

## Validation and limits

`python tests/test_thomas_cinnabar_lab.py` executes actual authored gate/scene commands under a host event harness: 960 combinations of theft, arc, Lab completion/quit, player restoration and researcher handoff. Both original choices work even after both fossil flags become set. Zero/unrevived, already revived, in-progress revival and completed opposite-fossil handoff preserve inventory/choice; normal ready-fossil transition remains correct. Once-only/re-entry, serialized ordinary event-state persistence, all three entrance paths and walkable layout tiles checked. No duplication or loss because the scene has no inventory/Pokémon commands. Host serialization is logic evidence, not an emulator save/load claim.

NG+ review: NewGameInitData clears SaveBlock1 and InitEventData resets ordinary flags/vars; carryover restores Pokémon/items and specific allowed identities, not these event flags or theft/main-arc state. Carried fossils cannot trigger Thomas: theft must be completed anew. The independent university researcher remains unchanged.

Existing Mt. Moon actual-helper tests pass; six trainer records, traits, unrelated maps, fossil scientist/researcher/Protector scripts and Mansion progression preserved. Map/local-ID generation, text preprocessing, text pixel-width checks, flag collision audit and `git diff --check` passed. Full compile/link/symbol checks passed in final seven-variant CI run `37663794925` before PR #298 merged at `aa3d3859d44aeb2b27334a5eda08b9b683733e82`. Assembled-ROM gameplay and real movement/save-load testing remain deferred.

Current native records should now carry the Thread 02 design-closure checkpoint. Older missing-Lab/missing-exact-fossil-set and open-Mansion-mapping assertions are superseded by the October 7, 2026 closure; prior dated production checkpoints remain provenance.


## Thread 02 authority closure — October 7, 2026

Current explicit instruction closes the remaining party-identity question: **Seadra is replaced by the stolen-fossil branch for the remainder of Thomas's battles from Cinnabar Mansion forward.** This is a persistent active-battle-team substitution, not a one-battle cameo. The current seven-battle route therefore ends with fossil participation at both Cinnabar Mansion and Viridian Gym; Kingdra no longer appears in Thomas's Viridian battle.

The exact implementation-ready package is defined in `docs/sam_edition/THOMAS_CINNABAR_FOSSIL_BATTLE_AUTHORITY.md`. Cinnabar and Viridian stay Single Battles, Gengar is not restored, the fossil branch comes directly from the Mt. Moon theft state, and the Lab preview remains optional/non-gating. Current dialogue/progression remains authoritative unless the implementation thread requires a minimal technical hook.

BLK-THOMAS-FOSSIL is **DESIGN-CLOSED / IMPLEMENTATION-PENDING**. SYS-THOMAS remains PARTIAL until the battle delta is implemented and merged. Assembled-ROM gameplay remains deferred to the final integrated playtest phase.
