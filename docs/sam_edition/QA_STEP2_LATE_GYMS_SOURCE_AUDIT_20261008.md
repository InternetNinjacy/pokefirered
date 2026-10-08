# QA STEP 2 — Gyms 5–8 Late-Game Progression Source Audit (2026-10-08)

Production baseline: `6c58cdfea1b0cee8e8a1d163955bf62c7d91f17b` on `sam-edition-dev`. WORKFLOW: KNOWN STATE → VERIFY LIVE DELTA → FIX ONLY CONFIRMED BLOCKERS.

## Audit results

| Gym | Source inspected and registered | Gameplay/runtime verification not yet performed |
|---|---|---|
| Fuchsia (5) | Koga remains active Normal-type leader; `TRAINER_LEADER_KOGA`; `FLAG_BADGE05_GET` and `ITEM_TM42` reward logic with bag-space retry. Mapped trainer NPC scripts resolve. The superseded Baz/Bushranger objects are not active requirements. | Invisible-wall traversal; Koga battle, badge, item retry/save persistence; gym re-entry. No explicit Gym-local Satoshi event is present; the authority audit must not invent one. |
| Saffron (6) | Sabrina Ghost Gym; `TRAINER_LEADER_SABRINA` + rematch; `FLAG_BADGE06_GET`, `ITEM_TM30_GHOSTLY_WAIL`; teleporter map links; Satoshi practice/postgame flows routed through `SaffronCity_Gym_EventScript_GymGuy` on an object with `OBJ_EVENT_GFX_SATOSHI`. Mapped object labels resolve. | Teleporter reachability, Satoshi's pre/post victory states, practice retry, badge, TM bag-full retry, rematch, save/reload. |
| Cinnabar (7) | Blaine Rock/Strata authority; leader/rematch, geology practicum trainer objects and background interactions; `FLAG_BADGE07_GET`, `ITEM_TM23_BOULDER_BASH`, Satoshi practice/postgame flows. Mapped object scripts resolve. | Route topology, practicum controls, rematch, Satoshi retry, reward and persistence. Legacy script symbol names referring to TM38/Fire Blast display **correct** current TM23 Boulder Bash text; no functional defect established by those names. |
| Viridian (8) | Giovanni Ground/Dominion authority; `TRAINER_LEADER_GIOVANNI`, `FLAG_BADGE08_GET`, `ITEM_TM54_PSYCHIC`; Thomas event, Satoshi practice, and trainer objects. Victory sets `VAR_MAP_SCENE_ROUTE22=3`. Mapped object labels resolve. | Giovanni/Thomas order and retry, gym entry/exit, post-badge Satoshi, reward and Route22/Victory Road transition. |

Map and script pairs inspected:
- `data/maps/FuchsiaCity_Gym/{map.json,scripts.inc}`
- `data/maps/SaffronCity_Gym/{map.json,scripts.inc}`
- `data/maps/CinnabarIsland_Gym/{map.json,scripts.inc,text.inc}`
- `data/maps/ViridianCity_Gym/{map.json,scripts.inc}`
- `data/maps/Route22/scripts.inc` and `data/maps/VictoryRoad_1F/scripts.inc`

Every active Gym map object script label was found in the corresponding script file. All four Gyms include leader battle, defeat/badge and configured TM paths. Historical Fuchsia/Koga, Gym6 Saffron, Gym7 Cinnabar and Gym8 Viridian production closure records were considered; historical PRs were not wholesale imported. Verified source text handles Cinnabar's TM23 Boulder Bash and Strata Badge despite legacy names.

## Validation boundary

This is a **static source-level integration audit**, not emulator gameplay. No victory, loss, badge reward, save/reload, maze navigation, scene transition or softlock test was run. No confirmed source-level defect requiring a runtime change was identified. Reopening superseded art or polishing legacy labels is not a pre-playtest blocker.

## Step 2 result and Step 3 handoff

Step 2 STATIC AUDIT COMPLETE; RUNTIME QA REQUIRED. Preserve all four integrated Gyms and assign them to the integrated regression test plan.

STEP 3 — Blue / Green / Thomas rivals: reconcile fresh production and historical PRs; examine starter-dependent teams, event order, encounter state, defeat/retry, Cinnabar fossil continuity, and League transitions. Fix only proven deltas; do not mistake stale backlog or unmerged historical branches for present implementation gaps. No emulator claims without emulator evidence.
