# SPRITE-002A — Core cast overworld conversion: source-access gate

Date: 2026-10-10
Production read-only reconciliation: `sam-edition-dev` at `42fdafd0a6ad7c1a3794a57eda33ec5c84d0c059`
Status: **BLOCKED ON APPROVED COMPARISON IMAGE BYTES; NO ART OR GAMEPLAY CHANGE**

## Authority and strict supersession
`CORE_CAST_VISUAL_RECOVERY_LOCK_20261009.md` merged through PR #359 locks:
- Red: brown tousled hair, visible RED headband/bandana, no cap, red/dark layered adventurer outfit.
- Thomas: silver/white hair, purple accents, light long coat, dark Rocket uniform and red R if readable.
- Blue: BLUE spiky hair, long dark coat, prominent red collar; old brown hair superseded.
- Green: red hair, glasses, green-and-white clothing, distinct from playable female sprite.
The source of truth is **the actual final four-character October 9 approved comparison image**, not historic missing standalone ZI-09 originals or a newly invented reconstruction. Description alone cannot justify pixels.

## Verified source delta
- `include/constants/event_objects.h`: player Red IDs 0–6, female player Green IDs 7–13, Rocket male 49, Blue 72; fixed Sam IDs currently 152–170 (`NUM_OBJ_EVENT_GFX=171`); 240–255 reserved for variable graphic IDs. Future allocations must check newest head.
- `data/maps/MtMoon_B2F/map.json`: `LOCALID_THOMAS_MT_MOON` still uses `OBJ_EVENT_GFX_ROCKET_M`. Adjacent accomplice and normal grunts also use that graphic intentionally; preserve those bindings.
- `data/maps/PalletTown_ProfessorOaksLab/map.json`: rival Blue uses `OBJ_EVENT_GFX_BLUE`; rival Green uses `OBJ_EVENT_GFX_GREEN_NORMAL` (player avatar).
- `src/data/object_events/object_event_graphics_info.h` shows Red has separately registered normal, bike, surf, and field-move pic/animation setups. One normal sheet is not enough for playable Red.
- `ART_QA_001_THREE_RIVAL_OVERWORLD_AUDIT_20261008.md` reports prior stock Blue and player-Green art, and Thomas grunt fallback. Full map/script occurrence census still OPEN.

## Blocker
The approved final comparison image was referenced by the visual lock, but its image **bytes** were not retrievable from the visible October 10 inputs, available attachments, or retained project-conversation text. Only design descriptions were available. Raw binary access to GitHub via connected text tools was also not established; local `git ls-remote` could not resolve github.com. No visual image extraction/derivative frame editing, 4bpp conversion, ROM build, emulator execution, or binary QA was performed. A narrative/art-description approximation is forbidden.

## Four independently gated production packages
| Package | Remaining implementation | Test status |
|---|---|---|
| A — Red | Build distinct source and ROM derivatives for walking/idle/running/bike/surf/fish/field/VS Seeker, check palette and animation bindings; do not alter female player | OPEN |
| B — Thomas | Convert directional NPC set; register new gfx ID/info/palette and replace **Thomas-only** map and scripted references | OPEN |
| C — Blue | Convert blue-haired directional set; retain dedicated rival ID and fix every actual overworld/script occurrence | OPEN |
| D — Green | Allocate standalone rival graphics info/ID/palette and replace only Green-rival references, never female player world assets | OPEN |

For each package: verify dimensional geometry and frame order; indexed 4bpp 16-color palette including transparent index; PNG chunk/CRC integrity and conversions; OAM/animation pointers, table sizes and ID/palette capacity; full build; emulator-facing directions, walking, transition, scene arrival, and save/reload behavior. Red requires all player actions. Every unexecuted check remains **OPEN**, never PASS.

## Records/handoff
- Do not overwrite merged battle and League assets in SPRITE-002A. Record follow-up `SPRITE-001B` correction: Blue battle/League art must be checked for the October 9 BLUE-hair supersession, likewise ensure Red, Thomas and Green align with locked appearances.
- Full Sprite/Art Registry v1.6 and later specialist deltas, ZI-09 records, Design Bible, and implementation records still require source-file-level reconciliation before closure.
- Next unblock action: user supplies the **approved October 9 final four-character comparison image file** as accessible attachment. Preserve it separately from derived 4bpp/PNG engine assets. Do not redesign.
- Keep this checkpoint documentation-only. There is no basis for a character-package merge yet.
