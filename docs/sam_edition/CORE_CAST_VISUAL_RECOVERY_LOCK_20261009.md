# Core Cast Visual Recovery Lock — 2026-10-09

**Authority status: USER-APPROVED / LOCKED VISUAL REFERENCE.**  
**Implementation status: NOT ROM-READY; no gameplay, palette, or graphics-table change is implied by this document.**

## Scope and supersession
The user approved the reconstructed four-character comparison sheet for **Red (playable protagonist), Thomas, Blue, and Green**. These reconstructed visuals replace the missing historical individual ZI-09 overworld sheets as the production **visual reference basis**. They also govern future **battle-sprite correction**, including already integrated battle portraits. Earlier visual interpretations inconsistent with this approval are superseded for these four characters. No change to their story, battle data, roster, or roles was approved.

**Specific explicit visual revision:** Blue now has **BLUE HAIR**, replacing the previously locked brown-hair cue. Keep his long dark coat and red high collar. Avoid confusing him with brown-haired Red.

## Four approved visual identities
- **Red (player):** tousled brown hair; **visible red headband/bandana, absolutely no baseball cap**; red/dark layered adventurer clothing; dark pants, brown boots; youthful agile silhouette. Locke-*inspired*, not a literal Locke copy.
- **Thomas:** silver/white hair; purple accent; long white/light gray coat; dark Team Rocket uniform with red R where readable; elegant villain silhouette. Not a generic Rocket grunt.
- **Blue:** spiky **blue hair**; long dark coat, prominent high red collar/lining; confident male rival silhouette. Not vanilla Gary.
- **Green:** red hair, glasses cue, green-and-white outfit, composed feminine rival presentation. Distinct from the female playable protagonist.

## Approved source reference
The **latest four-character comparison image shown in the thread immediately before the user's “Thats perfect. Lets lock these designs in” approval** is the specific visual reference, with Red headband and Blue blue hair. The subsequently shown Red recreation/reference retains Red without a cap. It is a high-level composite **concept sheet**, NOT an engine-native sprite atlas. Its claimed 16-color palettes, frame boundaries and scale are illustrative and must not be copied as already-engine-tested binary facts.

User also explicitly approved using the same reconstructed visual identities to **correct battle art**. Do not silently overwrite current battle-sprite integration or opening art before inspecting affected references, producing faithful corrected assets, and validating in ROM.

## Archive and old source recovery
September 27 ZI-09 individual Blue, Green, Thomas and Red approved overworld sources could not be recovered from checked accessible archives. Historical originals, if later found, remain provenance, **not automatic replacements** for this later approved artwork.

## Production workstream split
**SPRITE-002A**: four-character ROM-native **overworld** conversion/integration, with special **playable Red** work across idle/walk/run/bike/surf/fishing/field moves/VS Seeker and relevant player presentation. Blue/Green/Thomas require distinct overworld ownership, palettes, directional walk frames, and targeted map events; preserve the generic Rocket class and separate female player asset. Blue's blue hair must be reflected throughout.

**SPRITE-001B**: follow-up **battle sprite consistency audit and corrections** for the four subjects (and directly coupled intro/League renderings), preserving previous battle-data and trainer IDs and the merged opening content. This does not implicitly certify replacements to preexisting merged battle assets.

**ART-QA-001**: binary PNG chunk/CRC/palette/frame/table pointer/build/in-emulator verification. User approval of conceptual sheet is not an art-engine QA pass.

## Current facts, caveats, and provenance
- Repo: `InternetNinjacy/pokefirered`; integration: `sam-edition-dev`.
- `ART_QA_001_THREE_RIVAL_OVERWORLD_AUDIT_20261008.md` identified: Oak Lab/Route 22 Blue stock Blue graphics; Green rival reuse of playable Green graphics; Mt. Moon Thomas generic Rocket male. Audit other appearances before replacements.
- PR #359 `sam/art-qa-001-part1-static-inventory` is a documentation-only predecessor; check its live state and rebase/merge doc-safe only.
- An approved illustration alone **cannot** be blindly cropped into valid GBA animation frames. Preserve the user-visible design; manually normalize poses/baselines/color indexing under standard FireRed formats.
- No implementation, ROM image build, mGBA check, or screenshot certification was executed by this lock.

## Retirement and handoff
**Thread retired after archiving the approval and furnishing the SPRITE-002A production prompt.** The production thread must apply **KNOWN STATE → VERIFY LIVE DELTA → IMPLEMENT ONLY THE DELTA**, verify latest code and parallel PR status, and separately identify any unavailable approved source bytes or unsafe binary upload path. Do not treat this document as a claim that sprites are already in the ROM.
