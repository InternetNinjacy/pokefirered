# ART-QA-001 / Part 1 — Custom sprite inventory and static source audit

Audit date: 2026-10-08
Production branch: `sam-edition-dev`
Pinned production Git tree SHA: `6f0f251874806382ac476ff584203bfe09f05407`
Disposition: **PARTIAL / NOT SIGNED OFF**. This is a verified source-tree and selected loader/binding audit. It does **not** claim a completed authoritative art registry reconciliation, decompression test, pixel-level validation, compiled ROM test, or runtime screenshot coverage.

## Authority and exclusions
- PRs #354, #355, #356 already merged. Do not recreate Blue/Green opening art.
- The game-wide ART-QA gate `docs/sam_edition/ART_QA_001_CUSTOM_IMAGE_GAMEWIDE_GATE_20261008.md` requires explicit source approvals, dimension/palette checks, pointer mapping and runtime views. Its visual gate remains open.
- `docs/sam_edition/SPRITE_002_REQUIRED_OVERWORLD_AUDIT_20261008.md` assigns Cerulean Leilani/Lehua/Keahi world-sprite integration to GYM2 PR #335 and notes superseded Baz/Bushranger placeholders are not active requirements. Satoshi and Hawthorne use dedicated 2304-byte 4bpp overworld assets; Boreal has a dedicated graphic.
- The newest standalone *authoritative Sprite / Art Asset Registry* was not available in the checked repository tree or the provided thread attachments. Therefore "every approved unique image" cannot be certified from source inventory alone; reconcile that document before signing off.

## Inventory: confirmed on Git tree
Notation: **present** means exact path exists on pinned tree; **wired** means loader source explicitly inspected; **unverified** means PNG/palette binary or runtime not tested.

| Group | Relevant assets in tree | Evidence / static status | Runtime status |
|---|---|---|---|
| Opening Blue | `graphics/oak_speech/blue/pic.png`, `pal.pal` | present; `src/oak_speech.c` has dedicated Blue 8bpp resource and palette loader | not visually verified |
| Opening Green | `graphics/oak_speech/green/pic.png`, `pal.pal` | present; dedicated Green 8bpp resource and palette loader | not visually verified |
| Opening player / Oak | `graphics/oak_speech/{red,leaf,oak}/pic.png` and `pal.pal` | present; 8bpp resource declarations observed | not visually verified |
| Green world movement | `graphics/object_events/pics/people/green_{normal,bike,fish,item,surf,surf_run,vs_seeker_bike}.png` | present; corresponding 4bpp `INCBIN` references in `src/data/object_events/object_event_graphics.h` | not visually verified |
| Blue world | `graphics/object_events/pics/people/blue.png` | present; `gObjectEventPic_Blue` 4bpp include observed | not visually verified |
| Thomas trainer art | `graphics/trainers/front_pics/thomas.4bpp.lz`, `graphics/trainers/palettes/thomas.gbapal.lz` | present; implementation provenance PR #314 | not visually verified |
| Green trainer art | `graphics/trainers/front_pics/green.4bpp.lz`, `green_league_{opening,defeat}.4bpp.lz`; matching `green*.gbapal.lz` | present; independent battle/League assets; current use-site audit still pending | not visually verified |
| Blue battle/League | `graphics/trainers/front_pics/blue_green.4bpp.lz`, `blue_league_{opening,defeat}.4bpp.lz`; matching palettes | present; independent art resources; current use-site audit still pending | not visually verified |
| League opponents | `{lorelei,agatha,lance}_league_{opening,defeat}.4bpp.lz` with `*_league.gbapal.lz` | present; PRs #332/#334 integration provenance; table/scene testing pending | not visually verified |
| Pewter | `graphics/trainers/front_pics/leader_boreal_front_pic.png`; `graphics/object_events/pics/people/boreal.png` | present; dedicated art from restored Gym 1 | not visually verified |
| Hawthorne | `graphics/trainers/front_pics/hawthorne.4bpp.lz`; `graphics/object_events/pics/people/hawthorne.4bpp`; palettes | present; overworld `.4bpp` exactly 2304 bytes | not visually verified |
| Satoshi | `graphics/trainers/front_pics/satoshi.4bpp.lz`; `graphics/object_events/pics/people/satoshi.4bpp`; palettes | present; overworld `.4bpp` exactly 2304 bytes, declared on dedicated object graphics ID 155 | not visually verified |
| Cerulean trio | `graphics/trainers/front_pics/{leilani,lehua,keahi}.4bpp.lz`; world PNGs and palettes | present; known object-graphics binding recovery belongs to GYM2 #335 | integration open; runtime unverified |
| Vermilion | `graphics/trainers/front_pics/leader_lt_surge_sam.4bpp.lz`, paired `.gbapal.lz` | present; PR #326 provenance | not visually verified |
| Celadon | `leader_erika_sam.4bpp.lz`, `maya_celadon.4bpp.lz`, `nora_celadon.4bpp.lz`; palettes | present; PR #329 provenance | not visually verified |
| Trainer Card | `graphics/trainer_card/badges.png` | present; per-badge source approval/palette check outstanding | not visually verified |
| Sam title screen | `graphics/title_screen/sam/title_screen.gbapal`, `title_screen_part{0,1,2,3}.4bpp` | present; 4800,4800,4800,4798 bytes respectively; `src/title_screen.c` explicitly appends 2-byte tail at VRAM+0x4AFE so short last file alone is **not** proof of corruption | not visually verified |
| Pokémon graphics | `graphics/pokemon/*` directory includes species graphics | baseline-wide directories present, but custom-species vs stock identification NOT reconciled | not visually verified |
| Quest/Rocket/credits/menu artwork | art may exist in general engine folders | no authoritative unique custom-image list verified; do not infer closure | not visually verified |

## Static check results and gaps
1. **PASS (tree and selected source checks):** above exact paths exist in pinned Git tree; opening portrait/overworld includes and Sam title layout are explicitly present in inspected source.
2. **PASS (special case, source reasoning):** title segment 3 is 4798 bytes, with explicit 2-byte `sSamTitleScreen_TilesTail` appended by `LoadSamTitleScreen`. Do not 'repair' the length to 4800 absent stronger evidence.
3. **OPEN — image integrity:** direct PNG bytes were not retrieved through the connected GitHub text API (binary requests rejected). Therefore IHDR/PLTE/tRNS/chunk CRC, palette transparency, 4/8bpp conversion and image-frame geometries were **not** tested in this Part 1 checkpoint.
4. **OPEN — registry:** obtain and reconcile latest authoritative Sprite/Art Asset Registry, including approved image revisions, source provenance, hidden/unused/superseded declarations and new species art.
5. **OPEN — pointer coverage:** expand loader and trainer/object table checks across **every active location**; presence is not evidence of usage. Pay special attention to stock fallbacks, palette ownership, rival intro re-entry, League win/defeat art and GYM2 world objects.
6. **OPEN — compile/static automation:** verify all converted asset blobs and palette allocations using real checked-out binary bytes and the build toolchain; inspect stack/object/OAM/frame offsets and VRAM bounds.
7. **OPEN — visual gate:** capture mGBA in-scene appearance, movement/facing, shiny/normal, save/reload and all relevant game states with ROM hash recorded.

## Explicit non-blocking vs blocking distinctions
- **No new art requested:** merged opening art; no replacements authorized.
- **Legacy allocations not active blockers:** Baz/Bushranger superseded by Koga.
- **Unresolved integration:** Cerulean world objects must be checked against the eventual final GYM2 production delta before closure.
- **Signoff:** ART-QA-001 remains OPEN. A final Part 1 completion requires the authoritative registry and automated binary checks; Part 2 runtime evidence is separately required before full ART-QA signoff.
