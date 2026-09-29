# Pokémon: Sam Edition — League Implementation Checkpoint

Working repository: `InternetNinjacy/pokefirered`  
Working branch: `sam/league-phase5-integration`  
Draft PR: #12 -> `sam-edition-dev`  
Rule: actual GitHub/source/CI state wins if this file is stale.

## LAST VERIFIED GOOD STATE

- Verified good source commit before this checkpoint: `024e9f05d2cadf990fb1291d9d5ba234f8b34de3` — “League QA: verify rematch level curves”.
- CI run: `36511002987` — SUCCESS.
- Sam League static validation: PASS.
- Standard FireRed build: PASS.
- Modern build: PASS.
- Draft PR #12 is open, draft, cleanly mergeable, and MUST NOT be merged during overnight work.

## COMPLETED

- Five locked Phase 4 League room map/tile payloads reconstruct in CI.
- Independent derivative secondary tilesets are bound for Lorelei, Blue, Agatha, Lance, and Green.
- Binary transport/reconstruction is reproducible in CI.
- Lorelei / Blue / Agatha / Lance first-clear and rematch trainer parties are encoded and statically checked against the currently synchronized level curves.
- Blue occupies the vanilla Bruno physical slot.
- Blue Fire / Water / Electric specialist branches are wired to the documented starter-slot contract.
- Blue player-facing identity, dialogue, overworld fallback, and battle-art fallback are wired.
- Lorelei locked first-clear dialogue is installed.
- Lorelei / Blue / Agatha / Lance / Champion rematch selection uses `FLAG_SYS_GAME_CLEAR`, not the vanilla RS-link flag.
- Existing Hall-of-Fame reset script still clears the four per-run Elite Four defeated flags.
- Static regression checks enforce room bindings, rematch gates, state reset, E4 species/levels, Blue branch IDs, and two-Full-Restore records.

## CURRENT

Green Champion exact integration:
- exact starter-dependent Champion parties;
- trainer records and branch routing;
- first-clear/rematch levels and title-challenge framing;
- fixed trainer construction requirements (nature, ability, EV/per-stat IV support);
- exact Hidden Power requirements;
- Green-specific dialogue/identity integration.

Do not silently substitute for locked Green held items or mechanics that depend on not-yet-integrated resources.

## NEXT

1. Re-read the newest Green specialist authority and reconcile it against live source.
2. Implement as much of Green's exact Champion branch data/script/dialogue as current source and locked authorities permit without inventing canon.
3. Add/extend static validation for Green and rerun CI.
4. Recover/install exact Agatha and Lance first-clear dialogue and Lorelei/Agatha/Lance rematch wording if present in authoritative Drive records; do not invent missing text.
5. Implement final paired opening/defeat League battle-sprite presentation for all five characters, using approved source assets/registries only.
6. Verify stock AI/healing/switch behavior against locked League prose and live engine behavior.
7. Run full League progression/state regression, including first clear, Hall of Fame, rematch selection, per-run defeated-state reset, save/reload reconstruction, room progression, and Champion flow.
8. Produce a coherent test-build candidate and concise human gameplay/visual QA checklist.

## BLOCKERS / DECISIONS NEEDED

No user decision is currently required.

Known integration dependencies that must be resolved from source/authority rather than guessed:
- Adaptive Gene is allocated on a separate Sam resource-constants branch but is not yet present on `sam-edition-dev`; do not silently replace it with another held item.
- Blue Electric Manectric's exact Hidden Power Grass requires deterministic stat support before it can be guaranteed.
- Sam starter trio itself is still vanilla on `sam-edition-dev`; League currently uses the documented intended starter-slot contract. Do not rewrite unrelated starter-system work unless necessary and authority-supported.
- Exact Agatha/Lance first-clear and Lorelei/Agatha/Lance rematch dialogue must come from authoritative project records or explicit user approval if not recoverable.
- Final paired opening/defeat battle-sprite assets/hooks must use approved project assets; do not invent final character art.

## DO NOT REDO

- Do not recreate or replace the five locked Phase 4 room payloads.
- Do not collapse the five custom League rooms back into the single vanilla shared Pokémon League secondary tileset.
- Do not restore `FLAG_SYS_CAN_LINK_WITH_RS` as the League rematch gate.
- Do not change the locked E4 order: Lorelei -> Blue -> Agatha -> Lance -> Green.
- Do not restore Bruno as the second Elite Four member.
- Do not overwrite Blue with a Champion package from any other project.
- Do not use Pokémon Weather content or any separate FireRed hack as Sam authority.
- Do not merge PR #12 during unattended work.
- Do not treat current Blue battle/overworld fallbacks as final paired-sprite presentation.
- Do not claim binary-final/runtime QA merely from compile success.

## RECOVERY PROCEDURE

Every continuation run must:
1. Read this file.
2. Inspect the actual branch head, recent changes, draft PR, and latest CI.
3. Reconcile this checkpoint to durable repository state.
4. Continue only genuinely unfinished work.
5. Commit safe progress to the working branch.
6. Build/validate and repair ordinary failures autonomously.
7. Update this checkpoint LAST.
