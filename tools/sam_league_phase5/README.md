# Sam Edition League Phase 5 integration

This directory transports the locked Phase 4 League room binaries as text-safe base64 payload parts so GitHub Actions can reconstruct the exact room assets before compiling.

CI runs:

```
python3 tools/sam_league_phase5/install_payload.py
```

The installer:
- reconstructs the payload ZIP from `payload.part*`;
- creates five independent Pokemon League secondary tilesets from the live vanilla League base;
- injects each room's custom 4bpp tile payload into its locked secondary tile IDs;
- installs each room's metatiles and metatile attributes;
- installs palette 05 for each custom room tileset;
- installs the locked Lorelei, Blue, Agatha, Lance, and Green map binaries;
- installs Green's Champion-room border;
- verifies that the branch-side tileset declarations and layout bindings are present.

The generated binary files are build products of this transport layer and do not need to be committed individually. The source declarations and layout bindings remain ordinary branch changes.
