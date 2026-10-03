# ENC-002 — Route 24 Abra implementation checkpoint

Production branch: `sam/enc-002-gfx-abra-assets`

Implemented:
- approved Abra 16x16 nine-frame 4bpp overworld asset
- dedicated palette source
- `OBJ_EVENT_GFX_ABRA = 162`
- dedicated object-event palette tag `0x111E`
- object-event palette registration
- nine-frame pic table registration
- graphics-info registration using 16x16 OAM and `PALSLOT_NPC_SPECIAL`
- graphics-info pointer registration
- Route 24 visible static object at (5,17), west/left of Nugget Bridge
- Abra Lv.10 holding TwistedSpoon
- encounter-specific Confusion replacing Teleport
- capture/defeat complete and remove the encounter
- flee preserves the encounter
- defeat awards TwistedSpoon directly
- persistent completion flag `FLAG_STATIC_ROUTE24_ABRA_COMPLETE = 0x362`

QA gate:
- production CI build required
- focused runtime QA required before the Abra packet is called complete
- QA evidence branch must not become production ancestry
