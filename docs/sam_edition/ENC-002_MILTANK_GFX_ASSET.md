# ENC-002 GFX — Miltank asset checkpoint

Status: art direction approved; engine source asset created.

Authority:
- species-specific Option A overworld graphic
- faithful FireRed / Generation III miniature overworld presentation
- Route 5 static Miltank remains a separate encounter implementation step

Engine asset contract:
- 16x16 pixels per logical frame
- nine logical frames
- east-facing frames mirrored from west by engine behavior
- indexed 4bpp
- 16 palette entries
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

Generated engine resources:
- `graphics/object_events/pics/pokemon/miltank.4bpp`
- `graphics/object_events/palettes/miltank.pal`

Validation:
- 9 frames x 16x16
- 128 bytes per 4bpp frame
- total graphics payload: 1152 bytes
- palette entries: 16
- transparency index: 0

SHA-256:
- miltank.4bpp: `c88053b8ea11a45f551c8af8dfb0ce4f5f1c78c36798a1c8ab69f2c548a45600`
- miltank.pal: `3a6c9a1a33fa3a0885973e2a5e7c92b77a56fe0a094cf520b5cc866e0801befa`

Next implementation steps:
- allocate `OBJ_EVENT_GFX_MILTANK = 163`
- register dedicated object-event palette tag
- register nine-frame pic table / graphics info / pointer
- implement Route 5 Lv.18 Miltank @ Silk Scarf with Tackle / Rollout / Defense Curl / Stomp
- use `FLAG_STATIC_ROUTE5_MILTANK_COMPLETE = 0x363`
- capture/defeat complete and remove; flee preserves
- focused build/runtime QA
