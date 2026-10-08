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
