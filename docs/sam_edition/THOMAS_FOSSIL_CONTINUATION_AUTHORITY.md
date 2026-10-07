# RIV-016E — Thomas fossil continuation authority

Date: October 7, 2026  
Status: **LOCKED / IMPLEMENTATION AUTHORIZED**

## Superseding explicit instruction

The Cinnabar-only scope recorded by PR #302 is superseded only on one point:

**Seadra -> the stolen fossil for the remainder of Thomas's battles from Cinnabar Mansion forward.**

This is a persistent active-team lineage replacement, not a one-battle cameo.

The current seven-battle Thomas cadence remains unchanged. The affected current battles are:
1. Cinnabar Mansion.
2. Viridian Gym immediately before Giovanni.

No eighth Thomas battle is created.

## Preserved earlier closure

PR #302 remains correct for Cinnabar:
- trainer 788 stays Single;
- Gengar remains absent;
- party slot 4 replaces Seadra Lv45 from durable Mt. Moon theft state;
- state 3 / Dome stolen -> Kabutops Lv45 @ Mystic Water — Rock Slide / Brick Break / Water Pulse / Protect;
- state 4 / Helix stolen -> Omastar Lv45 @ Mystic Water — Surf / Ice Beam / AncientPower / Protect;
- Lab preview remains optional/non-gating;
- current Mansion dialogue, loss/retry and victory-only stage progression remain unchanged.

## Viridian continuation

Trainer 789 stays the existing Single Battle. The first five current production members remain unchanged:
1. Claydol Lv48.
2. Houndoom Lv49.
3. Magneton Lv49.
4. Machamp Lv50.
5. Salamence Lv51.

The sixth active battle slot no longer resolves to Kingdra on the normal story path. The same persistent fossil branch occupies that slot at the existing production Lv52 / IV-tier-24 difficulty point.

### Dome stolen -> Kabutops
- Kabutops Lv52 @ Mystic Water
- Rock Slide / Brick Break / Water Pulse / Protect

### Helix stolen -> Omastar
- Omastar Lv52 @ Mystic Water
- Hydro Pump / Ice Beam / AncientPower / Protect

The branch must continue to derive from `VAR_MAP_SCENE_MT_MOON_B2F`:
- state 3 = Dome stolen = Kabutops;
- state 4 = Helix stolen = Omastar.

Do not infer the branch from player inventory, Lab revival, or the university's separate opposite-fossil specimen.

The existing static Kingdra record may remain as an invalid/debug-state fallback if the runtime branch state is not 3 or 4. On the authored story path, Kingdra does not appear after Cinnabar.

## Unchanged routing

Do not restore Gengar, historical all-Double architecture, Power Plant, Victory Road, or postgame Thomas material.

Preserve:
- Viridian trainer 789 and Single format;
- existing Viridian dialogue;
- Doll handoff and quit-Rocket transition;
- Giovanni routing;
- trainer IDs 784-789;
- seven-battle cadence;
- existing Mt. Moon Double Battle;
- optional Cinnabar Lab preview;
- no new fossil item/Pokemon transaction;
- assembled-ROM playtest deferral.

## Implementation boundary

The implementation delta is only:
1. carry the already-implemented stolen-fossil branch from trainer 788 into trainer 789;
2. replace the normal-story Kingdra sixth slot at runtime with the branch fossil;
3. preserve the existing generated identity/IV tier and current Viridian Lv52 difficulty point;
4. validate both theft branches and the unchanged Viridian post-battle routing.

No new trainer ID, flag, variable, map object, story event, or item is authorized or required.
