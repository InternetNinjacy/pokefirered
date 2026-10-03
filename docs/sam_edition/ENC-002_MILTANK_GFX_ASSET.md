# ENC-002 GFX — Miltank asset checkpoint

Status: art direction approved; engine source asset created and re-indexed to an existing native object-event palette.

Authority:
- species-specific Option A overworld graphic
- faithful FireRed / Generation III miniature overworld presentation
- Route 5 static Miltank remains a separate encounter implementation step

Engine asset contract:
- 16x16 pixels per logical frame
- nine logical frames
- east-facing frames mirrored from west by engine behavior
- indexed 4bpp
- maximum 16 palette entries
- palette index 0 reserved for transparency
- no alpha, anti-aliasing, or gradients

Logical frame order:
0. south / front neutral
1. north / back neutral
2. west / side neutral
3. south walk A
4. south walk B
5. north walk A
6. north walk B
7. west walk A
8. west walk B

Recognition priorities:
1. compact pink bovine silhouette
2. cream horns / ear silhouette
3. dark head and body markings
4. cream muzzle
5. prominent pink udder
6. readable tail in side/back frames
7. dark hooves

Generated engine resource:
- `graphics/object_events/pics/pokemon/miltank.4bpp`

Palette routing:
- the artwork is indexed directly against FireRed's already-registered `gObjectEventPal_NpcPink` / `OBJ_EVENT_PAL_TAG_NPC_PINK` palette
- this preserves the required pink/cream/dark/white read while avoiding a new global object-palette allocation
- no unrelated sprite is substituted; only the palette resource is reused

Validation:
- 9 frames x 16x16
- 128 bytes per 4bpp frame
- total graphics payload: 1152 bytes
- transparency index: 0

SHA-256:
- miltank.4bpp: `a22af6358c8e8025f67b0d4311ae4f940eee086cc24fa7c7d24065db334fd473`

Implementation state:
- `OBJ_EVENT_GFX_MILTANK = 163` allocated
- Route 5 object placed at implementation-owned coordinate `(27,24)`, in the open grass immediately east of the Day Care and away from the door/mandatory route
- Route 5 Lv.18 Miltank @ Silk Scarf scripted with Tackle / Rollout / Defense Curl / Stomp
- `FLAG_STATIC_ROUTE5_MILTANK_COMPLETE = 0x363`
- capture/defeat complete and remove; flee preserves

Remaining steps:
- register nine-frame pic table / graphics info / pointer using the existing native pink palette tag
- build verification
- focused runtime/save-load QA
