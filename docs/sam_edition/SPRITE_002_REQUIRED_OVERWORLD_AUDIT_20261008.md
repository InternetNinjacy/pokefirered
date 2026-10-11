# SPRITE-002 required overworld art audit — 2026-10-08

Production baseline: `sam-edition-dev`. This is a source-checked audit, not a claim that emulator-side QA has finished.

## Active registration findings

- `OBJ_EVENT_GFX_SATOSHI = 155` now binds `gObjectEventGraphicsInfo_Satoshi`; implementation PR #336 merged and its implementation CI was green.
- Boreal and Hawthorne retain dedicated graphics info bindings.
- Leilani, Lehua, Keahi still bind `gObjectEventGraphicsInfo_ProfOak`; active Cerulean replacement is being recovered separately in GYM2 draft PR #335.
- Baz, male Bushranger and female Bushranger still reserve IDs pointing to `gObjectEventGraphicsInfo_ProfOak`, but **they are superseded by Koga and do not block gameplay-required sprite closure**.

## Fuchsia supersession evidence

`Pokemon_Sam_Edition_Sprite_Asset_Registry_Gym5_Fuchsia_Delta_v1.2_Koga_Supersession` (October 6, 2026) explicitly removes the Baz/Bushranger/Ripper Badge assets from active Gym 5 dependencies after Koga restoration. Current `data/maps/FuchsiaCity_Gym/map.json` uses `OBJ_EVENT_GFX_KOGA`; `data/maps/FuchsiaCity_Gym/scripts.inc` routes battle and badge reward through Koga. Do not restore superseded sprites merely because legacy constants remain.

## Disposition

- Satoshi art slice: implementation merged. Emulator appearance/animation still belongs to assembled ROM playtest QA.
- Baz/Bushranger placeholders: **non-blocking legacy allocations**.
- Cerulean trio: **GYM2-owned unresolved integration**, not independent sprite generation.
- No independently established outstanding gameplay-required overworld asset is justified by the audited placeholder entries outside GYM2. This is not a comprehensive proof that every story map uses the right object graphic.

No cosmetic polishing required for pre-playtest closure. Do not conflate reserved ID with an actively used encounter.
