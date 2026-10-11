# ART-QA-001 — three-rival custom overworld source/binding disposition

Date: 2026-10-08
Production inspected: `sam-edition-dev` as part of PR #359. This is an audit **finding**, not a claim that sprite conversion has occurred.

## Authority (September 27, 2026 ZI-09 locks)
1. **Blue** — `Pokemon_Sam_Edition_Sprite_Asset_Registry_Blue_Delta_v1.0`, Google Doc `1Q-AfK6fOstUNQOJkxaX4yWQvP7V1e43335lmM6h0BwE`: approved directional/walking sheet; spiky brown hair, long dark coat, red collar/lining; vanilla Gary/Blue forbidden as final art.
2. **Green** — `Pokemon_Sam_Edition_Sprite_Asset_Registry_Green_Delta_v1.0`, Google Doc `1v9t7ZCh-zMEUgVF8C1knYvUnw19Bw-_Dy1ScrDRJwL8`: approved directional/walking sheet; red hair, glasses impression, green-white clothing; vanilla Leaf/player Green forbidden as final rival art. Exact standalone source recovery/resync remains separately identified in delta.
3. **Thomas** — `Pokemon_Sam_Edition_Sprite_Asset_Registry_Thomas_Delta_v1.0`, Google Doc `1Y4Fxo77YdwSR9HkBWGHr16oA4eZLyDee1Lodhc9hFzU`: approved directional/walking sheet; silver-white/purple hair, white long coat and black/red Rocket uniform; generic Rocket grunt forbidden as final art.

## Direct production binding checks
| Character | Verified source locations / engine pointers | Disposition |
|---|---|---|
| Blue | `data/maps/PalletTown_ProfessorOaksLab/map.json` uses `OBJ_EVENT_GFX_BLUE`; `data/maps/Route22/map.json` uses same. `include/constants/event_objects.h` defines Blue ID 72. Pointer `gObjectEventGraphicsInfo_Blue` resolves through `sPicTable_Blue` and `graphics/object_events/pics/people/blue.4bpp`. | Binding exists, but points to previously existing Blue sprite; approved custom Blue overworld conversion not verified and must not be assumed. |
| Green | Oak Lab and Viridian City maps use `OBJ_EVENT_GFX_GREEN_NORMAL` (ID 7), which points to `gObjectEventGraphicsInfo_GreenNormal` / `sPicTable_GreenNormal` / `graphics/object_events/pics/people/green_normal.4bpp`, tied to `OBJ_EVENT_PAL_TAG_PLAYER_GREEN`. | Reuses player/avatar Green world graphics, not proven to be approved rival custom art. Dedicated rival asset/slot is required unless an approved custom artwork conversion is demonstrably bound without breaking player graphics. |
| Thomas | `data/maps/MtMoon_B2F/map.json` has `LOCALID_THOMAS_MT_MOON` explicitly using `OBJ_EVENT_GFX_ROCKET_M` (ID 49), whose info points to `sPicTable_RocketM`. No `OBJ_EVENT_GFX_THOMAS` constant or `gObjectEventGraphicsInfo_Thomas` pointer identified in checked tables; no `thomas` path under `graphics/object_events/pics/people` in pinned tree. | **Confirmed active generic-Rocket substitution at Mt. Moon**; must replace after approved source conversion and new binding. Broader scene-by-scene mapping still required. |

## Implementation contract
- Never invent, redraw or regenerate unapproved designs. Retrieve each exact approved sheet through its art authority/source folder.
- Preserve original sources; create correctly sliced 16x32 directional/walk frames, legal 4bpp GBA palettes/transparency, frame tables, registered object graphics IDs, independent palettes if required, and controlled map substitutions.
- Blue: convert approved coat/red-collar visual rather than retaining default Blue presentation.
- Green: **do not** repurpose all player-facing `GREEN_NORMAL` graphics; the Green rival must remain visually distinct from the player's female avatar.
- Thomas: replace only scripted Thomas objects, **not** genuine generic male Rocket trainers.
- Run PNG binary checks, converted 4bpp dimensions/frame counts, palette pointer/slot and OAM bounds; then ROM build and mGBA walking/facing/battle-trigger/reload scene checks.
- No art data has been generated or binary-validated in this checkpoint. Do not mark these custom overworld assets COMPLETE.

## Scope after this delta
The art gate has **three** explicit rivals requiring custom world sprite closure: **Thomas, Blue, Green**, not only Thomas and Green. All remain OPEN for finished source conversion/insertion/visual proof.
