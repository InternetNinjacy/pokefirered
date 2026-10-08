# ART-QA-001 — Custom image game-wide audit gate
Date: 2026-10-08. Status: **OPEN, visual verification outstanding**.

## Verified current-state evidence
- `src/oak_speech.c` binds dedicated `BLUE_PIC` and `GREEN_PIC` assets for initial introductions and naming-screen returns. Both load their own palettes into BG palette 6 and 8bpp compressed tiles. The two .pal sources contain 32 JASC entries each.
- PR #356 repaired malformed historical PNG palette chunk lengths and CRCs without redrawing the pixel payload. Its final-head production build, CI, boot smoke, host regression, scripted navigation and RAM capture passed; those do **not** prove pixels display correctly.
- The combined production commit `708d6d0b1fa861c95a11d0bc8ffb2a4797e47119` has a failing *legacy* CI build due to the expected-ROM SHA-1 comparison (`pokefirered.gba: FAILED` after link/objcopy), not an identified artwork conversion error. Record independently of Sam Edition production-build checks.

## Audit required before full-game playtest freeze
1. Inventory every approved **unique** art asset from the newest authoritative Sprite/Art Registry, including intro portraits, player sprites, rivals (Blue, Green, Thomas), all custom Gym/Satoshi/Rocket/League trainer and overworld images, custom Pokémon battle/front/back/shiny/icons, menus/title/credits and quest graphics.
2. For **each** inventory row: approved source, repository path, PNG/tiles/palette conversion, width/height/frame count, 4bpp/8bpp and transparency validity, engine table/loader pointer, palette sharing, runtime locations, baseline ROM hash, static validation status, visual verification status.
3. Automate PNG IHDR, PLTE, tRNS and CRC integrity, dimensions and palette counts, frame geometry, conversion-tool success, palette allocation and missing asset/pointer checks. Flag unintended stock substitutes, palette corruption, frame offsets, clipping, wrong facing and VRAM overflow.
4. In mGBA record screenshots/video and save/reload transitions for every appearance. Explicitly test intro and re-entry images, trainer battle front/back and overworld walking/facing, shiny and normal battle variants, animations, and repeated appearances under changed scene states.
5. Test every important setting: Oak Lab, Route 22 and later rival fights, eight Gyms, League/Champion, Rocket and Five Island, quests, postgame and NG+ when images recur. Verify images in actual scenes, not merely that they compile.

## Closure policy
No ART-QA-001 signoff without **complete authoritative registry reconciliation plus per-asset static results and per-use runtime snapshots**. Open defects must be categorized by asset/binding/engine/scene and fixed with only the approved art; no unapproved redraws or stock art substitutions. Keep QA-7B three-starter save/restart acceptance separate and OPEN.
