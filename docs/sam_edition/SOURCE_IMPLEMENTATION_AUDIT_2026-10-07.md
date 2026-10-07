# RIV-016 / Thread 02 — Mansion fossil battle authority audit

Reconciled from live `sam-edition-dev` at `7933d29450eec22655e2a98821e28153733d2569` after PR #299. Result: **B, PARTIALLY SPECIFIED**. No gameplay-safe delta remains. The October 6 reopening requires the evolved stolen fossil to debut in the Mansion battle, but current production protects trainer 788 as a full six-member Single roster (Claydol43/Houndoom44/Magneton44/Seadra45/Machamp46/Salamence47). No newer specialist authority resolves fossil slot/separate package, Gengar package/opening, Single-vs-Double/starter architecture, or resulting Mansion dialogue/Lab ordering. No source gameplay or resource allocation is changed. `BLK-THOMAS-FOSSIL` remains PARTIAL for Mansion only; SYS-THOMAS remains PARTIAL. Exact current handoff: [THOMAS_MANSION_FOSSIL_BATTLE_AUTHORITY_AUDIT.md](THOMAS_MANSION_FOSSIL_BATTLE_AUTHORITY_AUDIT.md).

# RIV-016 Cinnabar fossil continuity continuation

Starting production 8c3bbdaaae97ff1e4c446aca7dbbcf8209d7fdf2. Authority is partially specified: exact Lab dialogue and Lv45 fossil sets are found in the specialist record, but older Gengar/fossil Mansion architecture conflicts with the protected current six-member Single roster. Independent one-time Lab exit is implemented in the Entrance map using completed MtMoon scene3/4, current arc4 and centrally allocated flags35E/35F. No player fossil transaction, main arc change, trainer change or PowerPlant dependency. BLK-THOMAS-FOSSIL remains PARTIAL for Mansion roster/format mapping; SYS-THOMAS remains PARTIAL. Detailed reconciliation and verification: THOMAS_CINNABAR_FOSSIL_CONTINUITY.md. Earlier missing-Lab/exact-set assertions below are historical starting-state evidence.

PR #298 is production-merged into `sam-edition-dev` at `aa3d3859d44aeb2b27334a5eda08b9b683733e82` from validated feature head `c8dbc5abc890810e0a5b7db768c995ec928201c5`. Final integrated seven-variant CI run `37663794925` passed; initial seven-variant run `37663134291` had already passed. The independent Lab slice is production-complete. This does not close `BLK-THOMAS-FOSSIL`, which remains PARTIAL only for the Mansion roster/Gengar/format/dialogue mapping.

## ROCKET-001 / Thread 1C — shared state and Viridian — PR #297

Reconciled onto production `8c3bbdaaae97ff1e4c446aca7dbbcf8209d7fdf2` after both Five Island gameplay #295 and documentation #296 merged. Shared operation/evidence bitsets, actual Rocket Dossier Key Item, approved text-page reader and exact Viridian thief/fence operation are implemented. Trainer 902; item 247; vars 0x40A2–0x40A4; derived visibility flag 0x35D. Victory-only automatic goods return awards exactly five Poké Balls and the Dossier. Capacity checkpoints avoid duplicate rewards/frame loops; NG+ carries the item but clears run evidence and reuses the carried copy.

Real-helper and actual-script-path host checks, baseline Thomas checks, map/item generation, charmap and text-width checks, YAML validation and `git diff --check` pass. PR #297 tracks seven-variant compile/link and merge evidence. The new state is independent of vanilla story flags. Existing maps/trainers, Green, parcel/shop, Mt. Moon and Five Island source are preserved. [Consumer contract and bounded handoff](rocket-thread-1c-state-handoff.md).

ROCKET-001 shared framework is implementation-complete; SYS-ROCKET and ROCKET-002 remain PARTIAL / IN PROGRESS. Delivery 01 is unlocked here; approved Delivery 03/04 reader pages await Thread 1D event hooks. Delivery 02 is deliberately unbound because its older fossil-stock outcome conflicts with the current Thomas theft; reconciled authority is required. No missing rescue package or obsolete Thomas content was invented. Full assembled-ROM playtesting remains deferred. This status supersedes older shared-framework-pending wording below; prior source snapshots remain provenance.

## RIV-016 / Thread 1B source delta — PR #294

The approved Mt. Moon fossil encounter and one-usable-mon Double fallback are implemented in PR #294 on the reconciled PR #293 documentation ancestry. Original map objects, ordinary Rockets, fossil revival/opposite-fossil researcher and six baseline Thomas records/data remain unchanged. Host helper/static checks pass; ROM CI and merge evidence are tracked on the PR.

Source discrepancy: current Cinnabar Lab has no Thomas scene and the Mansion Thomas party is fixed, despite the reopening addendum describing fossil hooks as existing. The new stolen-fossil state is persistent/derivable; later fossil integration is not falsely marked complete and requires specialist reconciliation of the preserve-six-data rule. This supersedes older pending-Mt-Moon status below only when PR #294 is merged.

# Current documentation and source reconciliation — 2026-10-07

CURRENT DOCUMENT / FRAMEWORK RECONCILIATION — 7 OCTOBER 2026
This current-state overlay supersedes conflicting earlier status and branch instructions below; earlier dated sections remain historical provenance. It changes no approved gameplay mechanics.
Production authority: InternetNinjacy/pokefirered, sam-edition-dev; initial audit head dc7b53826ef5cd4a5e13165dbc4ab79018f327c6; refreshed production head ca15b79af8aea55664fc190e03b5d4672d4de940 (PR #292). master is not Sam production; sam-baseline remains immutable.
Authority order: current explicit project decision, newest applicable specialist authority, newest non-conflicting Design Bible, earlier authorities. The Canon Authority Index routes authorities; the Registry Backlog owns operational task status; merged source establishes what is actually implemented.
Completed programming remains COMPLETE while full assembled-ROM playtesting is deferred. No new build or runtime result is claimed by this documentation audit.
Current closure: Gym4 Celadon Parts 1–5 (final PR #288), Gym6/Saffron and Phantom Badge (#259), Gym7/Cinnabar and Strata Badge (#271–280), Hothouse (#254), final TM68 architecture/compatibility (#262), ordinary trainers (#261), Permanent Mode hooks (#253), reusable Satoshi (#263), physical Satoshi reconciliation (#270), Blue Elite Four #2 (#265), Elite Four core (#267), Green Champion wiring/dialogue/portraits (#285–291). Owner-specific Celadon/Cinnabar Satoshi hookups are now covered by their later Gym closures.
Concurrent update reconciled: PR #292 restored the six original Thomas encounters and shared dependencies onto live production; the latest preserve-existing-data instruction keeps those six original Single Battle records. New Mt. Moon mandatory Double/fallback, Rocket organization/evidence conversion, Five Island and final Thomas/Rocket closure remain separate pending owner work. Earlier claims of prior six-battle presence at dc7b538 were superseded by this recovery.
Remaining verified implementation deltas: Gym1 approved Ice/Hail/Boreal/Fortitude package is absent from current Pewter production (stock Brock/TM39; historical PR #93 is a donor, not integration). Gym8 still needs restoration of the later approved Dragon/Dominion/TM54 Psychic package (PR #169/#175); older Psychic/Command specialist text is superseded where it conflicts; live Giovanni/TM26 stock path persists alongside restored Satoshi. New Mt. Moon Thomas fossil-finale encounter remains unintegrated; preserve earlier Thomas closure and use the newer specialist victory-only theft / normal loss-and-retry instructions. Separate League final assembly, shared asset pipeline, recurring integration checks, and deferred full-game QA remain distinct work.
Green custom walking source is APPROVED / LOCKED in its specialist implementation addendum and Sprite Asset Registry. A separately recoverable engine-ready binary was not located in this pass. Use the approved existing fallback; missing binary recovery is sprite work, not absent design approval or reopened rival gameplay.
Current routing: Programming Guide https://docs.google.com/document/d/1WPlg320RdRXTB4PBJ2LlT_40XnLkMeyJbZwHgwYKrhI/edit ; Programming Readiness Registry https://docs.google.com/spreadsheets/d/11OkfEtbKugQbIbDj8NqLfdCVc_E-gYFLGy22MprlgAQ/edit ; framework https://docs.google.com/document/d/13eV6C18GF5T57jRBET4OEhvgonppPPTjQvNrTChF2H4/edit .
Coverage: 567 unique discovered project files retrieved for text inventory/reconciliation, including historical versions; current authority/control surfaces and selected live production source checked. This is not a visual audit of every binary asset or release certification.


## Source locations

- Gym1: `data/maps/PewterCity_Gym/map.json`, `scripts.inc`, `text.inc`.
- Gym8: `data/maps/ViridianCity_Gym/scripts.inc`; preserve current Satoshi and restored Thomas.
- Mt. Moon: `data/maps/MtMoon_B2F/scripts.inc`, `map.json`.
- Champion: `data/maps/PokemonLeague_ChampionsRoom/scripts.inc`; `src/data/sam_green_trainer_parties.h`; trainer graphics and slide selection source.
- Shared state: `include/new_game.h`, `src/new_game.c`; Hothouse state/gift source.

## Validation boundaries

Documentation-only correction; no gameplay or assets changed. All 567 discovered document texts retrieved, current authority/control surfaces reconciled, selected production source inspected. Historical archives retain their dated conclusions. No full ROM compile, emulator playtest, or complete binary asset audit performed in this pass. Recorded previous build evidence is attributed as previous evidence.

## Five Island Thread 1E production closure

This scoped checkpoint supersedes earlier Five Island-pending wording above. PR #295 merged into `sam-edition-dev` at `3d4063a825b914cbc9d8b50f9c8a00dd4b43e341`; validated feature head `8b4d0a3993bae2661f14fca1fcd0cee035ae4ec9`. All seven ROM builds passed CI run `37657349808`, with map/script/ID audits, preservation checks, once-only/re-entry review, actual-helper host tests and `git diff --check` passing. Production tree matches the validated feature. Full assembled-ROM playtesting remains deferred.

Exact accepted content is in [the Thread 1E package](../five-island-thread-1e-content-proposal.md). Implemented seven warehouse trainers/dialogue, scoped support-before-ace order, two stock-class Scientist objects, one-time NPC forced-growth demonstrations and shutdown cleanup. No player Pokemon mutation or new flags/vars/items; existing Gideon/Sapphire, puzzle, map events and Sevii progression preserved. Scientists use trainer IDs 900/901 within capacity 1024, with NUM_TRAINERS 902. Existing Thread 1B/Thomas 847 changes are preserved.

Specialist Rocket/Thomas Addenda, Programming Readiness Registry records and current Design Bible/Canon Authority Index/Document Sync Index are verified at `SYNC-2026-10-07-1E-COMPLETE`. Only Five Island is complete; broader SYS-ROCKET/SYS-THOMAS remain PARTIAL, including separate Thomas fossil continuity. Earlier snapshots remain historical provenance.
