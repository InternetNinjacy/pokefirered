# QA STEP 1 — Gyms 1–4 Early-Game Progression Source Audit (2026-10-08)

**Production audited:** `a0c45e3197fe479ffbe4a9dba43c6fd17301c269` on `sam-edition-dev`. Rule: KNOWN STATE → VERIFY LIVE DELTA → IMPLEMENT ONLY THE DELTA.

**Validation scope:** Source-level events, map JSON object-script labels, trainer names, badge/TM flags, map restoration hooks, historical PR comparison, and production CI. No emulator was run; no end-to-end battle or save-file regression is claimed.

| Gym | Active owner & source finding | Reward source | Unresolved runtime verification |
|---|---|---|---|
| Pewter | Boreal leader/rematch, overworld graphics and Satoshi hook, map scripts resolve | `FLAG_BADGE01_GET`, `ITEM_TM55_ICY_WIND` | trainer win/loss, badge and TM persistence, Satoshi, replay |
| Cerulean | Leilani leader/rematch, Lehua/Keahi trainers and overworld, Satoshi, stateful flame gate, all mapped script labels present (PR #335 merged) | `FLAG_BADGE02_GET`, `ITEM_TM39` | both routes, reset, order variations, collision, save/re-entry, TM one-time |
| Vermilion | Lt. Surge water authority battle script and object map, existing beam-puzzle metatile transitions, all map event labels found | `FLAG_BADGE03_GET`, `ITEM_TM34` | beam puzzle solvability and reload, victory/retry, gift guard |
| Celadon | Erika leader/rematch, Pinsir/Venomoth subjects, Satoshi, Field/Lab selectors and completion flags; all mapped script labels found | `FLAG_BADGE04_GET`, `ITEM_TM26_SIGNAL_BEAM` | both optional puzzle success/failure gates, any bypass, persistent state, rematch |

**Celadon old PR:** #287 is still open and has stale ancestry. Its important selector/completion, subject event and restoration script symbols were already observed in current production. Do not wholesale merge or close PR solely based on this sample; compare any specific delta before action.

**Vermilion old PR:** #205 is open and stale. Live source has Lt. Surge, beam gate and badge/TM reward. Do not import old branch without exact delta verification.

**CI:** Production SHA `a0c45e3` has a successful dedicated `Sam Edition Production Build` run `37766636343`; the legacy vanilla checksum comparison CI on that SHA is expected to fail for edited ROMs.

**Step 1 gate decision:** STATIC REGISTRATION AUDIT COMPLETE; RUNTIME PROGRESSION NOT VERIFIED. No confirmed source-level progression blocker identified in this audit, so no runtime code is modified and no unwarranted fix is merged. Do not claim the four Gyms gameplay-complete based on text inspection alone.

**Handoff to Step 2:** Check Fuchsia, Saffron, Cinnabar, Viridian against the new production HEAD, preserving Koga, Sabrina, Blaine and Giovanni implementations. Run emulator smoke tests across all eight Gyms before QA-ALL-002 or a playtest freeze.
