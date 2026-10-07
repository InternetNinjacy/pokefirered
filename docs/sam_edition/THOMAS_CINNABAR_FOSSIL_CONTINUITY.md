# RIV-016E — fossil continuation through Viridian

Explicit October 7 authority supersedes the PR #302 **Cinnabar-only** limitation while preserving the rest of that closure.

**Seadra is replaced by Thomas's stolen-fossil branch for the remainder of his battles from Cinnabar Mansion forward.** In the current seven-battle route, that means the fossil appears at both Cinnabar Mansion and Viridian Gym. The Seadra/Kingdra battle lineage ends after Silph Co.; Kingdra is no longer the normal-story Viridian sixth slot.

Cinnabar remains exactly as merged in PR #302: trainer 788 Single, no Gengar, slot 4 fossil at Lv45 from Mt. Moon state 3/4, Lab optional, current dialogue and retry/victory routing preserved.

Viridian continuation is now locked: trainer 789 remains Single; the first five members remain unchanged; party slot 6 uses the same fossil branch at the existing Lv52 / IV-tier-24 point. Dome stolen -> Kabutops Lv52 @ Mystic Water with Rock Slide / Brick Break / Water Pulse / Protect. Helix stolen -> Omastar Lv52 @ Mystic Water with Hydro Pump / Ice Beam / AncientPower / Protect.

No new trainer, flag, variable, item, map object, story event, or Thomas battle is added. Existing Doll handoff, quit-Rocket transition and Giovanni routing remain unchanged. The static Kingdra baseline may remain only as an invalid/debug-state fallback; it does not appear on the authored story path.

Authority detail: [THOMAS_FOSSIL_CONTINUATION_AUTHORITY.md](THOMAS_FOSSIL_CONTINUATION_AUTHORITY.md).

Current implementation branch: `sam/riv-016e-viridian-fossil-continuation`. RIV-016 is reopened only for this bounded continuation delta and returns to COMPLETE when the follow-up implementation merges.

---

# RIV-016 final closure — Thread 03 / PR #302

The prior PARTIAL sections below are retained as implementation provenance and are superseded for current status by this closure.

Thread 02 explicitly approved the remaining Mansion contract: trainer 788 remains a **Single Battle**; **no Gengar** is added; the existing Cinnabar six-member package is preserved except that **Seadra is replaced only for the Cinnabar battle** by Thomas's evolved stolen fossil; the PR #298 Lab scene is optional; current Mansion dialogue is preserved.

Runtime selection consumes only the durable Mt. Moon theft state already established by PR #294:
- `VAR_MAP_SCENE_MT_MOON_B2F == 3` (Dome stolen) -> Kabutops Lv45 @ Mystic Water, Rock Slide / Brick Break / Water Pulse / Protect.
- `VAR_MAP_SCENE_MT_MOON_B2F == 4` (Helix stolen) -> Omastar Lv45 @ Mystic Water, Surf / Ice Beam / AncientPower / Protect.

The branch is applied only while constructing trainer 788's enemy party. IDs 784–789 remain the six existing Thomas encounters; no second Mansion trainer record is allocated. The other five Cinnabar members and all five other baseline Thomas encounters remain untouched. The fossil branch does not read the player's current fossil inventory, revival state, researcher handoff flags, or Lab completion, so later player-side fossil actions cannot change Thomas's species and no fossil can be duplicated or removed.

Existing Mansion progression already provides the required retry/victory behavior and is deliberately preserved: a loss does not execute the post-battle stage setter, so Thomas remains stage 4 and returns on load; victory advances to `THOMAS_ARC_CINNABAR_CLEARED`, hides the Mansion actor, and exposes the Viridian encounter. Secret Key/traversal and unrelated Mansion content are unchanged.

Host/static validation is owned by `tests/test_thomas_cinnabar_fossil_battle.py`; seven-variant compile/link validation is required on PR #302. Assembled-ROM gameplay remains deferred by project policy.

**RIV-016: COMPLETE after PR #302 merge.**  
**BLK-THOMAS-FOSSIL: CLOSED.**

---

# RIV-016 — Cinnabar fossil continuity reconciliation

Starting production: `8c3bbdaaae97ff1e4c446aca7dbbcf8209d7fdf2`.
Branch: `sam/thomas-cinnabar-fossil-continuity`.
PR: `#298`.
Feature head: `c8dbc5abc890810e0a5b7db768c995ec928201c5`.
Ending gameplay production / merge: `aa3d3859d44aeb2b27334a5eda08b9b683733e82`.
Final seven-variant CI: `37663794925` — PASS.
Integration refreshed after parallel PR #297 merged into production `53ef5073bda7ee7c7abca9e27310eab9f2ce2c36`. Only overlapping documentation required resolution; current Rocket source/allocations were preserved. PR #298 then merged the independent Lab slice into `sam-edition-dev` at `aa3d3859d44aeb2b27334a5eda08b9b683733e82`.

Classification: **B, partially specified**. BLK-THOMAS-FOSSIL remains **PARTIAL**.

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

## Remaining narrow authority blocker

Do not mark SYS-THOMAS complete or close BLK-THOMAS-FOSSIL.
The exact fossil sets and Lab dialogue are **found**, not missing. Needed:
1. Approve how fossil45 joins the current full six-member Mansion roster: replacement slot or an explicitly separate current battle package.
2. Reconcile the older Gengar+fossil opening with the current roster lacking Gengar; exact Gengar data, other retained/changed slots and traits if required.
3. Resolve Single vs Double for this current Mansion package and the corresponding starter/fossil branch architecture. Current six records remain protected until explicit authority changes them.
4. Approve any Mansion dialogue change needed for that final package and whether to require the Lab scene before battle. Preserve loss/retry, Secret Key, ordinary Mansion traversal and current arc progression.

No older all-Double/Gastly lineage, Power Plant gate, Victory Road or postgame package is silently restored. No stale branch is merged.

## Validation and limits

`python tests/test_thomas_cinnabar_lab.py` executes actual authored gate/scene commands under a host event harness: 960 combinations of theft, arc, Lab completion/quit, player restoration and researcher handoff. Both original choices work even after both fossil flags become set. Zero/unrevived, already revived, in-progress revival and completed opposite-fossil handoff preserve inventory/choice; normal ready-fossil transition remains correct. Once-only/re-entry, serialized ordinary event-state persistence, all three entrance paths and walkable layout tiles checked. No duplication or loss because the scene has no inventory/Pokémon commands. Host serialization is logic evidence, not an emulator save/load claim.

NG+ review: NewGameInitData clears SaveBlock1 and InitEventData resets ordinary flags/vars; carryover restores Pokémon/items and specific allowed identities, not these event flags or theft/main-arc state. Carried fossils cannot trigger Thomas: theft must be completed anew. The independent university researcher remains unchanged.

Existing Mt. Moon actual-helper tests pass; six trainer records, traits, unrelated maps, fossil scientist/researcher/Protector scripts and Mansion progression preserved. Map/local-ID generation, text preprocessing, text pixel-width checks, flag collision audit and `git diff --check` passed. Full compile/link/symbol checks passed in final seven-variant CI run `37663794925` before PR #298 merged at `aa3d3859d44aeb2b27334a5eda08b9b683733e82`. Assembled-ROM gameplay and real movement/save-load testing remain deferred.

Current native records should carry the RIV-016 Cinnabar Lab partial-closure checkpoint and this precise remaining blocker. Older missing-Lab/missing-exact-fossil-set assertions are superseded by this audit, while prior dated production checkpoints remain provenance.


## Thread 02 — Mansion authority re-audit (7933d29450eec22655e2a98821e28153733d2569)

A fresh current-production and Drive-authority reconciliation found **no new gameplay-safe Mansion delta** after PR #299. The October 6 reopening still requires Thomas's evolved stolen fossil to debut in the Pokémon Mansion battle, while the current protected trainer 788 remains a full six-member Single roster with no fossil or Gengar. No newer specialist authority identifies the fossil replacement slot/separate package, current Gengar package, Single-versus-Double/starter architecture, or resulting Mansion dialogue/Lab-ordering rule.

Classification remains **B, partially specified**. `BLK-THOMAS-FOSSIL` remains **PARTIAL / Mansion blocked**; the completed Lab slice is not reopened. No trainer, party, map, dialogue, flag, variable, fossil inventory, or battle code is changed by this audit. Exact handoff: [THOMAS_MANSION_FOSSIL_BATTLE_AUTHORITY_AUDIT.md](THOMAS_MANSION_FOSSIL_BATTLE_AUTHORITY_AUDIT.md).
