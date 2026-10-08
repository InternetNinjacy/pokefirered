# SPRITE-002 — Satoshi Overworld Integration

## Current production candidate

Nine 16×32 four-direction overworld frames have been converted to native FireRed 4bpp graphics and a 16-entry BGR555 palette. Their raw binary resources live in:

- `graphics/object_events/pics/people/satoshi.4bpp` (2304 bytes, git blob `a866f160f0fe110497d1e925ea894ece87e5bbf8`)
- `graphics/object_events/palettes/satoshi.gbapal` (32 bytes, git blob `27111675941d907c701cdfe5de022e05b5b81e91`)

The two blobs are verified byte-identical to the local generated native artifacts. The repo's object graphics tables and event-movement palette table register `OBJ_EVENT_GFX_SATOSHI = 155` and `OBJ_EVENT_PAL_TAG_SATOSHI = 0x1123`; all nine frame entries use the existing standard 16×32 event animation semantics.

User-approved character description: authentic Pokémon FireRed / Gen III GBA adult NPC, short dark hair, rectangular glasses, dark blazer, light shirt, khaki trousers, dark shoes. The lost historical directional source is not claimed recovered. This is newly reconstructed production art. Approved modern presentation references are not falsely described as proof of native pixels.

## Validation

- 16×32 × nine frames, 4bpp graphics byte count 2304, BGR555 palette 32 bytes.
- GitHub Actions CI on implementation head `fbf82ee6500f7c8cff6b59ee3b533418b2771638` **passed** (run 37752832647).
- No GYM2 runtime files or trainer portrait files changed.
- Emulator-side appearance/animation QA remains for the assembled playtest, separate from ROM compile verification.

## Closure

The SPRITE-002 Satoshi overworld **implementation slice** may be merged after a clean CI check on this documentation-only update. This does not claim that all other SPRITE-002 characters or full-game playtest auditing are closed.
