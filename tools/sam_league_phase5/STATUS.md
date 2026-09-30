# Sam Edition League integration status

Working branch: `sam/league-phase5-integration`  
Draft PR: #12  
Base: `sam-edition-dev`

## Implemented on this branch

- Locked Phase 4 map/tile payloads for Lorelei, Blue, Agatha, Lance, and Green reconstruct reproducibly in CI.
- Each League room has its own derivative Pokémon League secondary tileset.
- Lorelei / Blue / Agatha / Lance first-clear and rematch trainer parties are encoded and statically checked.
- Blue occupies the physical vanilla Bruno slot and has Fire / Water / Electric specialist branches.
- Blue branch selection contract: `VAR_STARTER_MON` 0=Eevee -> Water, 1=Pichu -> Fire, 2=Ditto -> Electric.
- Lorelei's locked first-clear dialogue is installed.
- Agatha and Lance locked first-clear dialogue is installed from the later approved Elite Four closure conversation.
- Lorelei / Agatha / Lance locked rematch pre-battle, defeat, and post-battle dialogue is installed with distinct rematch script paths.
- League rematch selection uses `FLAG_SYS_GAME_CLEAR`, not the vanilla RS-link flag.
- Per-run Elite Four defeated flags remain reset by the existing Hall-of-Fame reset script.
- Green's three first-clear Champion branches and three +10 postgame title-challenge branches are wired with exact species, order, items, moves, natures, abilities, IVs, EVs, and two Full Restores.
- Green uses dedicated persistent naming and battle-name routing with canonical GREEN fallback.
- Green first-clear uses the CHAMPION label; the postgame title challenge uses PKMN TRAINER while retaining the existing Champion battle theme.
- Adaptive Gene is reconciled to authoritative item ID 245 for League use. Original-species Ditto receives the 1.20x standard damaging-move multiplier even after Transform.
- Green's trainer-owned held items cannot be permanently farmed through player-side Thief/Covet or Trick during her League battles.
- Raichu's locked IVs resolve to Hidden Power Ice 70; Machamp's resolve to Hidden Power Ghost 70 in the live Gen III Hidden Power calculation.
- Sam save reserve / trainer-flag capacity required by the League integration is centrally allocated and compile-time asserted.
- Static League regression checks cover Green naming, competitive construction, Adaptive Gene identity/runtime hooks, anti-farming hooks, labels/music, branch routing, and key League state.
- Current source passes static validation, standard FireRed compilation, and modern compilation.

## Canon-sensitive work still pending

- Final paired League opening/defeat battle sprites for all five characters still require presentation hooks and approved source assets.
- Stock AI flags are strengthened, but exact healing-threshold/switch behavior still needs runtime verification before claiming full parity with design prose.
- The Sam starter trio itself is still vanilla in `sam-edition-dev`; League routing follows the locked intended starter-slot contract without rewriting unrelated starter work.
- Full player-facing Adaptive Gene item presentation/acquisition belongs to the global starter/resource implementation. The League-side item identity and battle behavior are closed here.

## Safety / integration rule

Do not merge PR #12 into `sam-edition-dev` until the remaining League closure blocks are completed or explicitly split into tracked follow-up work and final CI is green.
