# Sam Edition League Phase 5 integration

This directory carries the binary room payload in text-safe base64 parts so GitHub/CI can reproduce the exact locked Phase 4 maps and room-specific tilesets without requiring manual binary uploads.

Run:

```
python3 tools/sam_league_phase5/install_payload.py
```

The installer writes the five locked League map binaries, five room-specific tileset PNG/metatile/attribute payloads, Green's Champion border, and each room's custom palette 05 source file into their source-tree locations.

The source declarations and layout bindings live directly in the branch diff. The payload is an implementation transport only.
