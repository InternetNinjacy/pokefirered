# ART-QA-001 Part 1 — Authority reconciliation and binary audit limitations

Date 2026-10-08. Follow-up to `ART_QA_001_PART1_STATIC_INVENTORY_20261008.md`.

## Authoritative routing actually retrieved
Project-wide registry: `Pokemon_Sam_Edition_Sprite_Asset_Registry_v1.6_Full_Art_Asset_and_Document_Sync`, cited as governing baseline by live specialist Google Docs. The standalone base registry body itself was **not** retrieved; this is **partial reconciliation**, not full registry certification.

Retrieved specialist companions:
- `Pokemon_Sam_Edition_Sprite_Asset_Registry_Blue_Delta_v1.0` (Google Doc ID `1Q-AfK6fOstUNQOJkxaX4yWQvP7V1e43335lmM6h0BwE`). Approved Blue reference is **not itself ROM-ready**; approved large-image source and designed 64x64 implementation must not be conflated.
- `Pokemon_Sam_Edition_Sprite_Asset_Registry_Green_Delta_v1.0` (ID `1v9t7ZCh-zMEUgVF8C1knYvUnw19Bw-_Dy1ScrDRJwL8`). Green single battle `TRAINER_PIC_GREEN` and Route 4 paired `TRAINER_PIC_BLUE_GREEN` recorded as production-complete in PR #289. **OW_GREEN** is a separate custom rival overworld requirement; ordinary `graphics/object_events/pics/people/green_*.png` filenames belong to the engine's playable female avatar and are **not proof that OW_GREEN was supplied**.
- `Pokemon_Sam_Edition_Sprite_Asset_Registry_Thomas_Delta_v1.0` (ID `1Y4Fxo77YdwSR9HkBWGHr16oA4eZLyDee1Lodhc9hFzU`). Battle visual locked; approved Thomas directional walking source is also LOCKED and must **not** be replaced by a generic Rocket grunt. `graphics/trainers/front_pics/thomas.4bpp.lz` and matching palette exist in production. However **no dedicated `thomas` object-event image path** was found in the pinned tree. This is a binding/integration investigation, not permission to redesign.
- `Pokemon_Sam_Edition_Sprite_Asset_Registry_Gym5_Fuchsia_Delta_v1.2_Koga_Supersession` (ID `1Cc5BVOQQkcUCKUQnRbBNGl-XSAXFF20JoFHwASBIZYw`). Final Koga supersession overrules older Baz/Bushranger source sections; obsolete art allocations do not create new pre-playtest art requirements.

## Required action before Part 1 signoff
- Retrieve **full** base registry v1.6 and every later applicable specialist art delta; create a one-row-per-approved-asset matrix with exact approved source filenames and hash, gameplay-use binding, stock-replacement flag, and supersession/optional status.
- Inspect custom Thomas and Green rival overworld ownership separately from the standard player sprite files and confirm actual map object graphics IDs; flag any active generic stock substitutes.
- Run binary bytes through PNG signature, IHDR/PLTE/tRNS/IDAT/IEND and per-chunk CRC checks, indexed bit depth and color counts, dimensions/frame geometry, palette index 0, engine conversion tools, and matching final table pointers.
- Run actual target ROM build and an mGBA scene matrix. These were **not run here**.

## Connection limitation
The available GitHub connector returned UTF-8 decode errors for raw `.png` and other binary blob reads; the local terminal could not resolve github.com. Consequently there is **no legitimate binary-level checksum, PNG integrity, conversion or pixel validation result** from this continuation. Source file presence and Git tree byte sizes are not substitutes. No gameplay file or approved image was changed.

**Disposition: PART 1 STILL OPEN.** This checkpoint establishes missing/ambiguous authority relationships rather than fabricating PASS results.
