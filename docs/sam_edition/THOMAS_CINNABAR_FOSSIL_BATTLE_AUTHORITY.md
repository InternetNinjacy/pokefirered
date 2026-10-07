# BLK-THOMAS-FOSSIL — Cinnabar / Viridian battle authority closure

Date: October 7, 2026
Scope: Thomas stolen-fossil battle mapping only
Status: **DESIGN-CLOSED / IMPLEMENTATION-PENDING**

## Current explicit ruling

**Seadra -> fossil for the remainder of Thomas's battles from this point forward.**

"From this point forward" begins at the Cinnabar Mansion fossil debut. In the currently approved seven-battle Thomas route, the only Thomas battles at or after that point are Cinnabar Mansion and Viridian Gym immediately before Giovanni.

The substitution is persistent across those remaining battles. It is not a one-battle cameo. The Seadra/Kingdra battle lineage therefore stops after Silph Co.; Kingdra is removed from the current Viridian Thomas battle. No additional Thomas battle is created.

If Thomas's route is ever explicitly reopened to add later battles, the fossil remains the successor to this active-team slot unless newer explicit authority says otherwise.

## Fossil branch source

Use the already-implemented Mt. Moon theft provenance:
- scene state 3 / Thomas stole Dome -> **Kabuto/Kabutops branch**;
- scene state 4 / Thomas stole Helix -> **Omanyte/Omastar branch**.

Do not infer Thomas's branch from the player's current fossil inventory or from the university's independent opposite-fossil specimen. Do not create another fossil-choice variable.

The fossil is Thomas's stolen/private Pokemon progression. No player inventory or Pokemon transaction is added at either battle.

## Cinnabar Mansion — locked battle package

Keep the existing Thomas Cinnabar encounter, trainer allocation and progression shell. Trainer 788 remains the implementation target. The battle remains a **Single Battle**.

Party order:
1. Claydol Lv43 — unchanged.
2. Houndoom Lv44 — unchanged.
3. Magneton Lv44 — unchanged.
4. **Fossil branch Lv45** — replaces Seadra Lv45.
5. Machamp Lv46 — unchanged.
6. Salamence Lv47 — unchanged.

Dome stolen -> Kabutops:
- Kabutops Lv45 @ Mystic Water
- Rock Slide / Brick Break / Water Pulse / Protect
- use the current replaced slot's Thomas IV tier.

Helix stolen -> Omastar:
- Omastar Lv45 @ Mystic Water
- Surf / Ice Beam / AncientPower / Protect
- use the current replaced slot's Thomas IV tier.

The fossil's first combat appearance remains Cinnabar Mansion.

## Viridian Gym — locked continuation rule

Keep the existing Thomas Viridian encounter, trainer allocation and progression shell. Trainer 789 remains the implementation target. The battle remains a **Single Battle**.

The current first five production members remain unchanged:
1. Claydol Lv48.
2. Houndoom Lv49.
3. Magneton Lv49.
4. Machamp Lv50.
5. Salamence Lv51.

The sixth slot is no longer Kingdra. It is the same persistent fossil branch Thomas used at Cinnabar.

To preserve the current production difficulty curve while applying the closed species progression, the replacement keeps the current production sixth-slot level and IV tier.

Dome stolen -> Kabutops:
- Kabutops Lv52 @ Mystic Water
- Rock Slide / Brick Break / Water Pulse / Protect
- current production sixth-slot Thomas IV tier.

Helix stolen -> Omastar:
- Omastar Lv52 @ Mystic Water
- Hydro Pump / Ice Beam / AncientPower / Protect
- current production sixth-slot Thomas IV tier.

This reconciles current production's Viridian slot level/trait tier with the Thomas specialist fossil branch's species-specific item and moves. The older specialist Lv51 Viridian fossil level is superseded by the current production Lv52 sixth-slot curve.

## Gengar and battle format

Do **not** add Gengar to either current battle.

The older Gengar + fossil opening and older global "every Thomas battle is Double" package are superseded for the current production Cinnabar/Viridian records. Current production's Single format remains authoritative for these existing later battles.

The separately locked Mt. Moon encounter remains its own mandatory Double Battle. This closure does not change Mt. Moon.

## Dialogue and event routing

Do not restore stale Gengar-dependent Mansion staging or wholesale older Thomas dialogue.

Current production Cinnabar and Viridian characterization remains authoritative. No additional dialogue is required solely to validate the fossil slot; the fossil branch is already established by Mt. Moon provenance and the optional Cinnabar Lab preview.

The Lab preview remains optional and non-gating. If skipped, Mansion still branches correctly from Mt. Moon theft state; clearing Mansion first continues to suppress the late Lab preview.

Preserve Cinnabar loss/retry behavior, Mansion switches/traversal/Secret Key, Thomas arc progression, Viridian Doll handoff/quit-Rocket transition, Giovanni routing, and the approved seven-battle cadence. No Victory Road or postgame Thomas battle is added.

## Implementation delta for the next thread

The next implementation thread should:
1. provide branch-aware Cinnabar trainer 788 party data with fossil replacing Seadra;
2. provide branch-aware Viridian trainer 789 party data with fossil replacing Kingdra;
3. select the branch from the persisted Mt. Moon theft state;
4. keep both battles Single and preserve current scripts/dialogue/progression unless a minimal technical hook is required;
5. add focused tests for both fossil branches at both battles, no Seadra/Kingdra after Silph, correct loss/retry/progression, and no Lab hard gate.

No broader Thomas redesign is authorized by this record.

## Status

**BLK-THOMAS-FOSSIL: CLOSED at design/authority level.**
**Implementation: pending Thread 03.**
**SYS-THOMAS: remains PARTIAL until implementation merges; assembled-ROM playtest remains deferred to the project's final integrated test phase.**
