# SPRITE-002 / ZI-09 — Blue, Green, Thomas source recovery checkpoint
Date: 2026-10-08

## Canon
`Pokemon_Sam_Edition_ZI-09_Core_Cast_Overworld_Remote_Closure_Delta_v1.0` (Google Doc `1F4q0CpxmN-tgbVb_AjG1LJy4VGzCX00ICUSO_5R0utw`) explicitly says the individual Blue, Green and Thomas source sheets were approved/locked September 27. Their appearance must not be reinvented. One-sheet-per-character / four directions / idle and walking required. Conversion/integration is still computer-dependent.

## Recovery performed
- Blue canonical folder `1DbJfneY3q1RSYokC9AEzSCy0bdg0AyrN`: contains approved battle source, League opening/defeat paired references, registry. No named Blue approved directional/walk overworld sheet found in its direct children.
- Green canonical folder `1s6ncxYEc9ENtORavD_2_7l3Pn53huU4q`: contains battle references, paired battle resources, registry. No named Green approved directional/walk overworld sheet found in its direct children. Specialist registry explicitly warns standalone approved OW source requires recovery/resync.
- Thomas canonical art folder `1zefxk6LTOQ6uIMxsFu-x0IYxsZRlzxMx`: contains Thomas approved *battle* reference and registry. No named Thomas approved directional/walk overworld sheet found in direct children.
- Drive image searches for `Blue Overworld`, `Green Overworld`, `Thomas Overworld`, and `ZI-09` did not identify the three expected canonical individual overworld sheets.
- No matching `thomas` overworld binary was found in the production Git tree. Blue map objects still use base `OBJ_EVENT_GFX_BLUE`; Green rival map objects use *player Green* ID; Mt. Moon Thomas uses Rocket male ID.

## Actual blocker
**APPROVED SOURCE BINARY MISSING FROM VERIFIED RECOVERY SURFACES.** Approval is intact; do not confuse absence of a recovered file with design permission. Without source pixel bytes and their known directional geometry, no conversion, palette reduction, animation slicing or safe in-ROM insertion can be certified. No fake image, borrowed sprite, or guess-based conversion may be merged.

## Resume conditions
1. Recover exact approved individual Blue/Green/Thomas September 27 ZI-09 PNGs from the original approved conversation/other authorized art archive; compare visually to locked traits and source provenance.
2. Persist originals unchanged in their corresponding character canonical folders, alongside SHA-256 and source dimensions.
3. Generate engine-ready derivatives (16x32 directional frames, walking frame table, transparent index 0 and legal indexed palette), validate against FireRed object graphics file/table conventions and GBA display constraints.
4. Allocate three independent object-event graphics IDs and graphics-info/palette records, preserving player Green; change only actual rival object references (including dynamically assigned graphics if any), never generic Rocket NPCs.
5. Build and run targeted mGBA tests on every scene/heading/turning/walking/re-entry/save-load with screenshot and exact ROM hash evidence.

## Status
**BLOCKED ON ORIGINAL APPROVED SPRITE SHEET BYTES**. No code/assets changed; documenting the truthful blocker only.
