# RIV-016 / Thread 02 — Thomas Mansion fossil battle authority audit

Starting production: `7933d29450eec22655e2a98821e28153733d2569`.
Working branch: `sam/thomas-fossil-battle-authority-audit`.
Scope: Team Rocket / Thomas — Cinnabar fossil continuity closure, Mansion battle authority only.

## Result

Classification: **B — PARTIALLY SPECIFIED**.

No gameplay-safe delta remains under current authority. The October 6 Mt. Moon reopening makes the later Mansion fossil debut mandatory, so the requirement is not stale or superseded. The current October 7 production closure simultaneously protects the existing six-member Single Battle Mansion package until an explicit current mapping replaces it. No newer specialist authority resolves that collision.

Accordingly, this pass changes documentation only. It does not alter trainer 788, the Mansion map, Thomas state, fossil inventory, Lab state, dialogue, flags, variables, or battle code.

## Live reconciliation

| Continuity element | Current authority says | Live production at start | Delta |
|---|---|---|---|
| Mt. Moon stolen-fossil state | Thomas controls Miguel's unchosen fossil after Red wins | Scene 0x408B persists 3 = Dome stolen, 4 = Helix stolen | None |
| Player's kept fossil | Red keeps the chosen fossil | Existing transaction-safe Mt. Moon acquisition | None |
| Cinnabar fossil revival | Normal player revival remains independent | Existing Lab fossil revival | None |
| Opposite-fossil researcher | Separate university specimen; does not represent Thomas's stolen fossil | Existing independent researcher handoff | None |
| Thomas Cinnabar Lab hook | One-time non-battle exit after Thomas revives the stolen fossil | Production-complete through PR #298 | None |
| Thomas Mansion hook | Evolved stolen fossil must first appear in combat here | Existing stage-4 -> stage-5 Thomas battle, trainer 788 | Battle data does not consume fossil branch |
| Fossil-specific branch | Helix stolen -> Omastar; Dome stolen -> Kabutops | Mt. Moon provenance is available | Branch selection exists; roster insertion is blocked |
| Fossil battle package | Lv45 fossil evolution; current closure records exact Mystic Water sets | No fossil in trainer 788 party | Exact slot/replacement architecture is missing |
| Gengar dependency | Older package expects Gengar and preferably Gengar + fossil opening | Current protected Mansion roster has no Gengar | Current Gengar insertion/package is not authorized |
| Battle format | Older lineage says Double; current protected trainer 788 is Single | `.doubleBattle = FALSE` | Current format change is not authorized |
| Starter branch | Older lineage includes starter-counter branching | Current protected Mansion roster has no starter branch | Current branch architecture is not authorized |
| Dialogue / ordering | Preserve current Mansion scene unless a later package changes it; Lab ordering question remains open | Current Mansion dialogue and arc routing are implemented | Any change remains authority-blocked |
| Completion/progression | Mansion victory advances existing Thomas arc and must preserve Secret Key/traversal | Current stage transition is live | None unless final battle package explicitly changes it |

## Current protected production package

Trainer: `TRAINER_THOMAS_CINNABAR_MANSION` / ID 788.

Current battle format: Single.

Current six:
1. Claydol Lv43
2. Houndoom Lv44
3. Magneton Lv44
4. Seadra Lv45
5. Machamp Lv46
6. Salamence Lv47

This roster is full. Current authority does not identify which slot the fossil replaces, whether a separate current package supersedes all or part of this roster, or whether Gengar returns.

The current fossil packages already recorded by the latest reconciliation are:
- Player kept Helix / Thomas stole Dome -> **Kabutops Lv45 @ Mystic Water** — Rock Slide / Brick Break / Water Pulse / Protect.
- Player kept Dome / Thomas stole Helix -> **Omastar Lv45 @ Mystic Water** — Surf / Ice Beam / AncientPower / Protect.

Those exact fossil sets are not the blocker. The blocker is how they legally enter the current protected Mansion battle.

## Exact remaining authority required

Before any Mansion battle source is edited, current authority must explicitly close all applicable items below:

1. **Roster mapping:** identify which current Mansion slot the fossil replaces, or define the complete separate current Mansion package that supersedes trainer 788's six.
2. **Gengar:** state whether Gengar is present in the current Mansion battle. If yes, define its exact level, item, moves, current persistent-trait expectations, slot, and any member displaced by it.
3. **Battle architecture:** choose Single or Double for the current Mansion battle. If Double, define the intended opening pair and confirm whether the existing one-usable-player Thomas fallback applies here. Define any starter-counter branching retained in this battle.
4. **Dialogue / ordering:** approve any changes to Mansion pre-battle, defeat, or post-battle dialogue, and state whether witnessing/completing the Lab exit scene is required before the Mansion battle or merely optional continuity.

No historical all-Double/Gastly-line, Power Plant, Victory Road, or postgame package may be restored as a shortcut. No stale Thomas branch may overwrite the current six records.

## Fossil-state safety result

Both provenance branches are already durable and independent of the player's later revival/researcher path:
- Helix kept / Dome stolen -> Thomas fossil branch = Kabutops.
- Dome kept / Helix stolen -> Thomas fossil branch = Omastar.

The PR #298 Lab scene reads the original Mt. Moon theft record, not the later player fossil inventory flags, so player revival and the opposite-fossil researcher cannot flip Thomas's branch. The Lab scene performs no inventory/Pokémon transaction, preventing fossil duplication or loss. Re-entry is one-time; ordinary story flags/vars reset under NG+ while defined carryover remains separate.

No additional save-state, trainer, flag, variable, or item allocation is justified by this audit.

## Parallel-work reconciliation

PRs #294, #295, #297, #298 and #299 are already merged into current production. No newer open Rocket/Thomas PR supplies a Mansion authority contract. Open historical PR #244 is stale provenance and is not valid production ancestry for this decision.

## Thread disposition

- Independent authority-supported implementation remaining: **none**.
- Gameplay files changed: **none**.
- New trainer IDs / flags / vars: **none**.
- BLK-THOMAS-FOSSIL: **PARTIAL / Mansion authority blocked**.
- SYS-THOMAS: **PARTIAL**.
- Safe next action: obtain the four Mansion decisions above, then begin a new bounded implementation pass from then-current `sam-edition-dev`.
