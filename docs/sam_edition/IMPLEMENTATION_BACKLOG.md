# Pokémon: Sam Edition — Backlog mirror

Snapshot: 2026-10-07. Native Programming Readiness Registry Backlog is authoritative; this is a repository navigation mirror. Task IDs are unchanged. COMPLETE refers to programming closure under deferred assembled-ROM playtesting policy.

| Task | System | Workstream | Status | Dependency / next action |
|---|---|---|---|---|
| ENV-001 | SYS-CORE | Programming Environment | COMPLETE | BLK-002 |
| ENV-002 | SYS-CORE | Programming Environment | COMPLETE | ENV-001 |
| ARCH-001 | SYS-TRAIN | Trainer Architecture | COMPLETE | ENV-001 |
| ARCH-002 | SYS-CORE | Save Architecture | COMPLETE | ENV-001 |
| ARCH-003 | SYS-CORE | Flags / Variables | COMPLETE | ENV-001 |
| ARCH-004 | SYS-SPEC | Species Architecture | COMPLETE | ENV-001 |
| ARCH-005 | SYS-TM | Move / Item Architecture | COMPLETE | ENV-001 (satisfied) |
| ARCH-006 | SYS-SPRITES | Graphics Architecture | COMPLETE | ENV-001 (satisfied) |
| CORE-001 | SYS-CORE | Play Modes | COMPLETE | None — architecture prerequisites cleared |
| CORE-002 | SYS-CORE | Permanent Mode | COMPLETE | CORE-001; ARCH-002 |
| CORE-003 | SYS-CORE | Permanent Mode | COMPLETE | CORE-001; ARCH-002 |
| CORE-004 | SYS-CORE | Permanent Mode | COMPLETE | CORE-002 COMPLETE; CORE-003 COMPLETE |
| BREED-001 | SYS-BREED | Route 5 Day Care | COMPLETE |  |
| BREED-002 | SYS-BREED | Breeding | COMPLETE |  |
| BREED-003 | SYS-BIRDS | Legendary Birds | COMPLETE |  |
| GIFT-001 | SYS-GIFT | Special Acquisition | COMPLETE |  |
| GIFT-002 | SYS-GIFT | Reward Delivery | COMPLETE |  |
| EVOL-001 | SYS-EVOL | Evolution | COMPLETE | None |
| EVOL-002 | SYS-EVOL | Evolution | COMPLETE | None |
| EVOL-003 | SYS-EVOL | Evolution | COMPLETE | None |
| START-001 | SYS-START | Starter Selection | COMPLETE | ARCH-003 |
| START-002 | SYS-START | Brick | COMPLETE | ARCH-005 |
| START-003 | SYS-START | Adaptive Gene | COMPLETE | ARCH-005 |
| START-004 | SYS-START | Starter Tutorial | COMPLETE | None - exact starter tutorial dialogue is closed |
| TM-001 | SYS-TM | TM Architecture | COMPLETE | ARCH-005 (satisfied) |
| TM-002 | SYS-TM | Custom Moves | COMPLETE | ARCH-005 (satisfied) |
| TM-003 | SYS-TM | Move Overrides | COMPLETE | None — Signal Beam override runtime verified; Shadow Punch was already implemented |
| TM-004 | SYS-TM | Compatibility | COMPLETE | None |
| TM-005 | SYS-TM | Compatibility | COMPLETE | None |
| SPEC-001 | SYS-SPEC | Type Retrofit | COMPLETE | ARCH-004 |
| SPEC-002 | SYS-DARK | Dark-Type Retrofit | COMPLETE | ARCH-004 |
| SPEC-003 | SYS-SPEC | Ralts / Natu | COMPLETE | TM-004 |
| SPEC-004 | SYS-SPEC | Ghost Families | COMPLETE |  |
| SPEC-005 | SYS-BUG | Early Bug Final Evolutions | COMPLETE |  |
| SPEC-006 | SYS-SPEC | Nosepass / Rock Cleanup | COMPLETE |  |
| SPEC-007 | SYS-SPEC | Feebas / Milotic | COMPLETE |  |
| SPEC-008 | SYS-BIRDS | Legendary Birds | COMPLETE |  |
| SPEC-009 | SYS-SPEC | Custom Species Integration | COMPLETE | None |
| SPEC-010 | SYS-HOT | Tropius | COMPLETE |  |
| SPEC-011 | SYS-SPEC | Pokédex Numbering | COMPLETE | None |
| ENC-001 | SYS-ENC | Locked Encounter Packets | COMPLETE | SPEC-003; SPEC-006; SPEC-007 |
| ENC-002 | SYS-ENC | Static Overworld | COMPLETE |  |
| ENC-003 | SYS-ENC | Fishing | COMPLETE |  |
| ENC-004 | SYS-ENC | Encounter Freeze | COMPLETE |  |
| TRAIN-001 | SYS-TRAIN | Ordinary Trainers | COMPLETE |  |
| TRAIN-002 | SYS-TRAIN | S.S. Anne Correction | COMPLETE | None — replacement decision closed |
| TRAIN-003 | SYS-TRAIN | Mt. Moon Correction | COMPLETE | None — replacement decision closed |
| TRAIN-004 | SYS-TRAIN | Double Battle Cadence | COMPLETE |  |
| RIV-001 | SYS-RIVALS | Blue | COMPLETE |  |
| RIV-002 | SYS-RIVALS | Green | COMPLETE |  |
| RIV-003 | SYS-RIVALS | Route 4 Double Battle | COMPLETE | None |
| RIV-011 | SYS-THOMAS | Thomas Trainer Data | COMPLETE | None |
| RIV-016 | SYS-THOMAS | Thomas Story Events | PARTIAL | Mt. Moon merged #294. Independent Cinnabar Lab exit implemented by continuation; exact Lab dialogue/fossil sets found. Mansion fossil slot/Gengar/format mapping against protected six records remains BLK-THOMAS-FOSSIL. See THOMAS_CINNABAR_FOSSIL_CONTINUITY.md. |
| ROCKET-001 | SYS-ROCKET | Rocket Framework | COMPLETE | PR #297: shared operation/evidence state, Dossier and approved Viridian hook; merge/CI tracked on PR. |
| ROCKET-002 | SYS-ROCKET | Rocket Operations | IN PROGRESS | Five Island PR #295 and Viridian PR #297 complete as bounded slices. Thread 1D owns remaining conversions/evidence hooks; Delivery 02 needs fossil-theft wording reconciliation. |
| SAT-001 | SYS-SATOSHI | Satoshi Practice System | COMPLETE |  |
| SAT-002 | SYS-SATOSHI | Satoshi Postgame | COMPLETE |  |
| SAT-003 | SYS-SATOSHI | Viridian Satoshi Integration | COMPLETE |  |
| SAT-004 | SYS-SATOSHI | Pewter Rematch | COMPLETE |  |
| SAT-005 | SYS-SATOSHI | Cerulean Rematch | COMPLETE |  |
| GYM1-001 | SYS-GYM1 | Pewter Endurance Gym | IN PROGRESS | Current production lacks approved Gym1 map/script integration; historical PR #93 is not merged. |
| GYM2-001 | SYS-GYM2 | Cerulean Fire Gym | COMPLETE |  |
| GYM3-001 | SYS-GYM3 | Vermilion Water Gym | COMPLETE | None |
| GYM4-001 | SYS-GYM4 | Celadon Bug Gym | COMPLETE |  |
| GYM5-001 | SYS-GYM5 | Fuchsia Normal Gym | COMPLETE | ARCH-001; ARCH-003 (satisfied) |
| GYM6-001 | SYS-GYM6 | Saffron Ghost Gym | COMPLETE |  |
| GYM6-002 | SYS-GYM6 | Phantom Badge | COMPLETE |  |
| GYM7-001 | SYS-GYM7 | Cinnabar Rock Gym | COMPLETE |  |
| GYM8-001 | SYS-GYM8 | Viridian Dragon Gym | READY | Restore approved Dragon/Dominion/TM54 package from PR #169/#175; preserve current Satoshi and Thomas. |
| QUEST-001 | SYS-QUEST | Quest Framework | COMPLETE | ARCH-003 |
| QUEST-002 | SYS-QUEST | Pallet — A Helping Hand | COMPLETE | QUEST-001 |
| QUEST-003 | SYS-QUEST | Viridian Runaway Nidoran | COMPLETE |  |
| QUEST-004 | SYS-QUEST | Pewter — The Museum Challenge | COMPLETE |  |
| QUEST-005 | SYS-QUEST | Cerulean — The Broken Waterworks | COMPLETE |  |
| QUEST-006 | SYS-QUEST | Vermilion — Pollution at the Docks | COMPLETE |  |
| QUEST-007 | SYS-QUEST | Lavender — The Restless Memorial | COMPLETE |  |
| QUEST-008 | SYS-QUEST | Celadon — The Rooftop Eevee | COMPLETE | QUEST-001 |
| QUEST-009 | SYS-QUEST | Fuchsia — Safari Census | COMPLETE |  |
| QUEST-010 | SYS-QUEST | Saffron — Copycat's Collection | COMPLETE |  |
| QUEST-011 | SYS-QUEST | Cinnabar — Field Research Recovery | COMPLETE | QUEST-001; TM-001 |
| HOT-001 | SYS-HOT | Saffron Hothouse | COMPLETE |  |
| HOT-002 | SYS-HOT | Saffron Hothouse Dialogue | COMPLETE |  |
| OAK-001 | SYS-GIFT | Oak Research Milestones | COMPLETE |  |
| OAK-002 | SYS-TRAIN | Youngster Joey Superboss | COMPLETE |  |
| TITLE-001 | SYS-TITLE | Title Screen | COMPLETE | None |
| TITLE-002 | SYS-TITLE | Title Screen Integration | COMPLETE | None |
| TITLE-003 | SYS-TITLE | Title Cry | COMPLETE | None |
| SPRITE-001 | SYS-SPRITES | Battle Sprites | READY | None — ARCH-006 satisfied |
| SPRITE-002 | SYS-SPRITES | Overworld Sprites | READY | None — ARCH-006 satisfied |
| SPRITE-003 | SYS-SPRITES | Pokémon / Icon Assets | COMPLETE | None |
| QA-ALL-001 | SYS-CORE | Continuous Integration | READY | ENV-001 |
| QA-ALL-002 | SYS-CORE | Full Regression | DEFERRED | All implementation work |
| DOC-001 | SYS-CORE | Implementation Status | READY |  |
| DOC-002 | SYS-CORE | Implementation Contracts | COMPLETE |  |
| DOC-003 | SYS-CORE | GitHub Workflow | COMPLETE |  |
| DOC-004 | SYS-CORE | Implementation Manifest | COMPLETE |  |
| GYM2-002 | SYS-GYM2 | Leilani Postgame Rematch | COMPLETE |  |
| GYM-AUDIT-001 | SYS-CORE | Custom Gym Closure Audit | READY |  |
| NGP-001 | SYS-NGP | New Game+ | COMPLETE |  |
| NGP-002 | SYS-NGP | New Game+ | COMPLETE | NGP-001 |
| NGP-003 | SYS-NGP | New Game+ | COMPLETE | NGP-002 |
| NGP-004 | SYS-NGP | New Game+ | COMPLETE | NGP-003, NGP-006 |
| NGP-005 | SYS-NGP | New Game+ | COMPLETE | NGP-004, NGP-006 |
| NGP-006 | SYS-NGP | New Game+ | COMPLETE | NGP-003 |
