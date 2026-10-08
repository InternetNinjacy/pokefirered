# SPRITE-002 — Satoshi overworld asset integration checkpoint

Status: **STAGED, NOT IMPLEMENTED / NOT MERGEABLE**.

The user approved a reconstructed Satoshi four-direction walking reference after the original September 27 source sheet could not be recovered. This is a **new implementation asset**, not the missing approved original. The accepted visual reference is `Satoshi_Overworld_Approved_Visual_Reference_v2.png` (conversation artifact). The pixel-refined 16-frame candidate is `Satoshi_Overworld_16x32_Refined_v2.png` (conversation artifact; 64x128 RGBA, 4x4 frames of 16x32, 14 opaque colors). Preview: `Satoshi_Overworld_Refined_Preview_v2.png`.

## Remaining integration gates

1. Transfer the **exact** native PNG bytes into this branch as `graphics/object_events/pics/people/satoshi.png`, without re-encoding via the GitHub UTF-8 contents endpoint. File bytes currently exist in conversation artifact storage, not the GitHub tree.
2. Verify directional ordering, transparent pixel treatment, color indexing and walking animation frames against the project’s existing `Boreal` or `Hawthorne` overworld engine implementations.
3. Add Satoshi-specific palette, object graphics declarations, event object graphics table binding, and registered `OBJ_EVENT_GFX_SATOSHI` **155**; do not change trainer portraits or Gym2.
4. Run ROM build CI and verify no unresolved assets or link symbols; review in-game sprite clarity.
5. Only then mark SPRITE-002 Satoshi slice complete and merge independently of GYM2.

No existing Satoshi story, trainer data, flags or map scripts may be modified by this asset-only work.

## 2026-10-07 front-frame audit

The user rejected the earlier oversized/non-FireRed visual presentation. A revised FireRed-style front-facing visual was provisionally accepted. The earlier v2 full walking sheet **must not be assumed approved** on that basis.

A real 16x32 RGBA front-frame **staging** image has now been exported as conversation artifact `Satoshi_FireRed_Front_16x32_Staging.png`, with an exact nearest-neighbor comparison `Satoshi_FireRed_Front_Native_vs_16x_Preview.png`. Technical inspection: 16x32, 14 visible colors, only alpha 0/255, occupied pixel bounds (x=1..14, y=4..30). This extraction derives from the prior v2 candidate and requires comparison/approval against the newer front-facing FireRed visual reference; it is **not** a ROM graphics integration or proof of style approval. The newer preview alone is not a directly reusable 16x32 PNG.

Do not merge until all 4 directions and animations are confirmed visually, exact native binary bytes are committed, ID 155 is bound, and a complete CI/build succeeds.
