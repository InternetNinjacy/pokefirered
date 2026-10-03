# ENC-002 GFX — Abra asset checkpoint

Status: art direction approved; engine asset steps 1–5 completed.

Approved source intent:
- Pokémon FireRed / Generation III overworld style
- 16x16 pixels per logical frame
- nine logical frames
- east-facing frames mirrored from west by engine behavior
- indexed 4bpp
- maximum 16 palette entries
- palette index 0 reserved for transparency
- no alpha in engine data, no anti-aliasing, no gradients

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

Recognition priorities retained from the approved development sheet:
1. oversized pointed ears
2. broad yellow head
3. narrow/closed eyes
4. brown shoulder/chest armor
5. readable angular tail
6. compact yellow body with brown accents
7. withdrawn/resting Abra posture

Generated engine resources:
- `graphics/object_events/pics/pokemon/abra.4bpp`
- `graphics/object_events/palettes/abra.pal`

Validation:
- 9 frames x 16x16
- 128 bytes per 4bpp frame
- total graphics payload: 1152 bytes
- palette entries: 16
- transparency index: 0
- nearest-neighbor native-size review performed before export

SHA-256:
- abra.4bpp: `ec014edffeb55df46a1a44bc8d5f0f5511630cd9f8eaa2663696dbb00577e105`
- abra.pal: `dd124974bafa6f2e3b5715c5be9dc8981cf3499e6a4bb61fa1aef3d58c3245e9`

Deliberately not done in this checkpoint:
- `OBJ_EVENT_GFX_ABRA` allocation
- graphics-info pointer/table integration
- map/static encounter implementation
- build/runtime QA

Those begin with step 6 of the approved workflow.
