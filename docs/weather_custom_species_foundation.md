# Pokémon: Weather custom species foundation

This branch reserves the shared custom-species and evolution-item namespaces needed by Weather and its paired-version compatibility layer.

## Shared species IDs

| ID | Symbol |
|---:|---|
| 412 | SPECIES_LEAFEON |
| 413 | SPECIES_GLACEON |
| 414 | SPECIES_ECTOCEON |
| 415 | SPECIES_TALICE |
| 416 | SPECIES_FELSENMEER |
| 417 | SPECIES_PYROLANTE |
| 418 | SPECIES_EGG |

The custom species IDs are intended to remain stable. Future custom species append after 417; existing custom IDs are not renumbered.

## Shared item IDs

375–382 remain the Apricorn block already reserved by SHARED-001.

| ID | Symbol |
|---:|---|
| 383 | ITEM_ICE_STONE |
| 384 | ITEM_BRICK |

## Talice/Felsenmeer foundation

Talice and Felsenmeer now have:
- species constants and National Dex slots;
- names;
- locked base stats, typing, abilities, capture/EXP/EV/friendship/hatch metadata;
- Geodude + Ice Stone -> Talice and Talice Lv.36 -> Felsenmeer evolution routing;
- locked level-up learnsets;
- cry routing (Talice -> Graveler cry, Felsenmeer -> Golem cry);
- compile-safe temporary battle/icon/palette/footprint mappings to Graveler/Golem.

The temporary graphic mappings are scaffolding only. They must be replaced with the approved Talice/Felsenmeer source-ready graphics before visual integration is considered complete.

TM/HM compatibility remains dependent on the Weather TM01–TM73 source expansion and is intentionally not encoded against the vanilla TM numbering.
