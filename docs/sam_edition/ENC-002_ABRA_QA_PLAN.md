# ENC-002 — Route 24 Abra focused QA plan

Production source under test: `sam/enc-002-gfx-abra-assets`.

Focused acceptance checks:
- `OBJ_EVENT_GFX_ABRA = 162` and `NUM_OBJ_EVENT_GFX = 163`
- dedicated Abra palette tag and palette registration
- nine-frame 16x16 Abra pic table and graphics-info pointer registration
- exactly one Route 24 static Abra object using `FLAG_STATIC_ROUTE24_ABRA_COMPLETE`
- implementation-owned placement remains west/left of Nugget Bridge
- battle package: Abra Lv.10 @ TwistedSpoon
- encounter-specific attack is Confusion
- capture and defeat complete/remove the static
- flee does not set the completion flag
- defeated Abra awards TwistedSpoon directly
- capture path does not also award the direct knockout reward
- completion flag survives real save/fresh-process reload
- static remains an ordinary wild capture with no Special Acquisition EXP/obedience behavior

The runtime QA branch is evidence-only and must never become production ancestry.
