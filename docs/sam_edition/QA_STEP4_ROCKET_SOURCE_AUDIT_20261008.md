# QA STEP 4 — Rocket progression source audit (2026-10-08)

Baseline: `sam-edition-dev` at `e2fe1f98052381bf7637d1399cdece27f42753a2`. Scope is static inspection and current historical-PR reconciliation, **not emulator gameplay**.

## Confirmed production facts

- Shared operation/evidence definitions: `include/constants/sam_rocket.h`; helper: `src/sam_rocket_state.c`; dossier: `data/scripts/sam_rocket.inc`. Four dossier delivery entries are defined and displayed conditionally.
- Delivery 01: Viridian operation integrated under PR #297 with a durable operation/state and guarded rewards (inspect `data/maps/ViridianCity/scripts.inc`; test contract `tests/test_sam_rocket_state.py`).
- Delivery 02: `data/maps/MtMoon_B2F/scripts.inc` records `ROCKET_OPERATION_MT_MOON` and `ROCKET_EVIDENCE_DELIVERY_02` after Thomas's battle/theft flow; PR #307 merged and older failed-theft narration was superseded.
- Delivery 03: `data/maps/CeruleanCity_House2/scripts.inc` contains the TM08 reward, completion operation, `ROCKET_EVIDENCE_DELIVERY_03`, and owed-reward state. PR #305 was superseded by #310, itself superseded by **merged PR #309**. Do not re-merge these stale PRs.
- Delivery 04: `data/maps/Route24/scripts.inc` calls `Script_SamRocketRecordEvidence` with `ROCKET_EVIDENCE_DELIVERY_04` after the Nugget Bridge Thomas trainer victory; PR #306 merged.
- Five Island forced-growth warehouse: PR #295 merged. `data/maps/FiveIsland_RocketWarehouse/scripts.inc` includes Admin/Scientist battles, cage/computer text branches, persistent warehouse-clear and actor-hide flags. Do not reopen approved battle/art packages without a verified fault.
- Thomas Viridian crossover: `data/maps/ViridianCity_Gym/scripts.inc` contains trainer fight, Poké Doll reward retries and farewell state. Thomas fossil continuity is already marked CLOSED in the current continuity file.

## Historical PR disposition

PR #244 remains a draft historical Rocket restoration branch and is **not** evidence that the above merged deliveries are absent. #295, #297, #306, #307 and #309 are merged; #305/#310 were explicitly retired as superseded.

## Remaining verification / blocker classification

- Stale `docs/sam_edition/IMPLEMENTATION_BACKLOG.md` still describes `ROCKET-002` as in progress and Delivery 02 as needing reconciliation. Its status conflicts with the merged delivery/source evidence, so it is **not controlling completion evidence**.
- Source references exist for the four Dossier deliveries and the major Rocket crossover/warehouse events. This does **not** prove every one of the 11 operation-bit definitions has an authored runtime consumer; a complete operation-by-operation map audit must still be performed in integrated regression. Do not assert `ROCKET-002` globally COMPLETE on this sample alone.
- Emulator QA still needed: Viridian reward/bag-capacity retry, Mt. Moon defeat/retry/theft branch, Cerulean TM08 receipt and reload, Route24 victory-only evidence, Five Island cage/release and shutdown, final Thomas Doll/retry, all-order dossier visibility and NG+ persistence.
- Host test `tests/test_sam_rocket_state.py` exists but was **not executed** in this documentation-only audit.
- No source-confirmed gameplay defect justified modifying live events in this step. No old Rocket PRs were wholesale merged.

**STEP 4 status: static progression evidence audited, no gameplay patch; runtime gate remains outstanding.** STEP 5 HANDOFF: reconcile newest `sam-edition-dev`, audit Lorelei → Blue → Agatha → Lance → Green, Champion/Hall of Fame, repeat League, NG+ carryover/unlock, and required transitions. Fix verified source defects only; do not assert emulator playtesting without execution.
