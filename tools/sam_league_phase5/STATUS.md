# Sam Edition League integration status

Working branch: `sam/league-phase5-integration`  
Draft PR: #12  
Base: `sam-edition-dev`

## Implemented on this branch

- Locked Phase 4 map/tile payloads for Lorelei, Blue, Agatha, Lance, and Green reconstruct in CI.
- Each League room has its own derivative Pokémon League secondary tileset.
- League room payload and both standard/modern FireRed builds were proven green before battle-data integration.
- First-clear and rematch teams are encoded for Lorelei, Blue, Agatha, and Lance using current Design Bible level curves.
- Blue occupies the physical vanilla Bruno slot and has Fire/Water/Electric specialist branches.
- Blue branch selection contract: `VAR_STARTER_MON` 0=Eevee -> Water, 1=Pichu -> Fire, 2=Ditto -> Electric.
- Blue player-facing name, room dialogue, overworld fallback, and battle-art fallback are wired.
- Lorelei's locked first-clear dialogue is installed.
- League rematch selection uses `FLAG_SYS_GAME_CLEAR`, not the vanilla RS-link flag, in Lorelei/Blue/Agatha/Lance/Champion scripts.
- Per-run Elite Four defeated flags remain reset by the existing Hall-of-Fame reset script.
- Static League regression checks run in CI.

## Canon-sensitive work still pending

- Green Champion exact branch parties, trainer records, dialogue, and postgame title-challenge framing.
- Advanced fixed trainer construction needed by Green (natures, abilities, EVs/per-stat IVs) and exact Hidden Power types.
- Adaptive Gene exists in the resource-allocation branch but is not yet integrated into `sam-edition-dev`; do not silently substitute a different held item.
- Blue Electric Manectric's Hidden Power Grass needs fixed-stat support before it can be guaranteed.
- Sam starter trio is still vanilla in `sam-edition-dev`; League currently documents the intended slot contract rather than rewriting the starter system here.
- Final paired League opening/defeat battle sprites for all five characters still require source insertion/presentation hooks. Current Blue visuals are fallbacks only.
- Exact Agatha/Lance first-clear dialogue and Lorelei/Agatha/Lance rematch wording were not recoverable verbatim from the current indexed authorities. Do not invent replacements; retain implementation placeholders until an exact source is found or Tom explicitly authors/approves text.
- Stock AI flags are strengthened, but exact healing-threshold/switch behavior must be verified against engine behavior before claiming full parity with design prose.

## Safety / integration rule

Do not merge PR #12 into `sam-edition-dev` until CI is green after the latest League changes and the remaining Champion/presentation work has either been completed or explicitly split into tracked follow-up work.
