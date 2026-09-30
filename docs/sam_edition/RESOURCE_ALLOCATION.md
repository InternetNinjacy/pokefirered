# Pokémon: Sam Edition — Resource Allocation Plan

Baseline: `pret/pokefirered@c75f352304d529f6ba92d4f74b9cf8b5c3810788`

Status: **central pre-implementation allocation authority for the code repository**. Project design authorities remain authoritative for gameplay behavior. These allocations are intended to prevent cross-system numeric collisions.

## Guiding rules

- Preserve all stock IDs unless there is a strong implementation reason not to.
- Prefer appending tables or consuming verified placeholder ranges over renumbering stock content.
- Keep numeric ownership centralized in this document / the project Programming Readiness Registry.
- Exact gameplay data is not defined here.
- Any new resource not covered here must receive an allocation before implementation.

## Species

Stock real species remain unchanged through Chimecho (`SPECIES_CHIMECHO = 411`).

Allocate immediately before `SPECIES_EGG`:
- `SPECIES_LEAFEON = 412`
- `SPECIES_ECTOCEON = 413`
- `SPECIES_RHYPERIOR = 414`
- `SPECIES_EGG = 415`
- `NUM_SPECIES = SPECIES_EGG`

Future Sam Edition species append after Rhyperior and before Egg so the three locked IDs above never move.

Do **not** reuse `SPECIES_OLD_UNOWN_B..Z` (252–276). Audit found active Old-Unown assumptions in cry conversion, menu logic, Pokédex order data, icons, learnsets, and graphics tables. Reusing those IDs would require special-case cleanup and is not the low-risk path.

With only the three current additions, `DEX_FLAGS_NO` remains 52 bytes, so this allocation does not enlarge the owned/seen bit arrays.

Final player-facing Sam Edition Pokédex numbering remains deferred to roster closure and is separate from these internal species IDs.

## Moves

Stock move IDs remain unchanged through `MOVE_PSYCHO_BOOST = 354`.

Allocate:
- `MOVE_BOULDER_BASH = 355`
- `MOVE_GHOSTLY_WAIL = 356`
- `MOVE_SEED_STRIKE = 357`
- `MOVE_NIGHT_TERROR = 358`
- `MOVES_COUNT = 359`

Existing modified moves keep stock IDs:
- Signal Beam = 324; Sam Edition changes its damage-class handling only.
- Shadow Punch = 325; Sam Edition changes its power/effect only.

Future custom moves append from 359 upward. Do not insert them into the stock range.

## Items and TM engine items

Verified placeholder item block: IDs 226–253 (`ITEM_0E2..ITEM_0FD`). Preserve every stock item ID outside this block.

Allocate:
- 226–243: engine item records for logical TM51–TM68
- 244: `ITEM_BRICK`
- 245: `ITEM_ADAPTIVE_GENE`
- 246: `ITEM_PROTECTOR`
- 247–253: reserved Sam Edition custom-item expansion

TM01–TM50 retain stock item IDs 289–338. HM01–HM08 retain stock item IDs 339–346.

Because logical TM51–TM68 are intentionally stored in the verified placeholder block rather than by renumbering stock HMs/items, the TM Case must become table-driven:
- logical TM number -> item ID
- logical TM number -> move ID
- item ID -> logical TM number

Do not rely on the vanilla assumption that every TM/HM item is one single contiguous arithmetic range.

## Abilities

Stock abilities remain 0–77.

Allocate:
- `ABILITY_SOUL_ROT = 78`
- `ABILITIES_COUNT = 79`

Future approved custom abilities append from 79 upward. Do not allocate speculative abilities that are not current canon.

## Trainer IDs

Baseline:
- `NUM_TRAINERS = 743`
- `MAX_TRAINERS_COUNT = 768`

The baseline source explicitly notes only 25 additional Trainer IDs fit before trainer-flag space overflows. Sam Edition requires a centralized expansion.

Set architectural capacity:
- `MAX_TRAINERS_COUNT = 1024`
- stock Trainer IDs 0–742 remain unchanged
- Sam Edition new Trainer IDs: 743–1023

Allocation blocks:
- 743–799: Gyms, Gym staff requiring new records, Satoshi
- 800–879: Blue / Green / recurring rivals
- 880–959: Team Rocket, recurring Rocket rival/admins, story/side-quest special trainers
- 960–1023: project-wide overflow / future expansion

Existing vanilla trainers that are true one-for-one replacements may reuse their existing IDs when doing so is cleaner; otherwise use the Sam block. All new IDs must be entered in the central registry.

`NUM_TRAINERS` should track the highest actually-defined trainer + 1; do not create hundreds of empty trainer records merely to reserve the namespace.

## Trainer classes

Baseline class IDs run 0–106.

Reserve:
- 107–122: Sam Edition custom Trainer classes

Reuse stock classes such as Hiker, Scientist, Leader, Boss, etc. whenever the desired battle label/economy fits. Only consume this block for genuinely new classes.

## Trainer front-picture IDs

Baseline front-picture IDs run 0–147.

Reserve:
- 148–223: Sam Edition custom Trainer battle portraits
- 224–255: leave unallocated for future/engine headroom

Player back-picture replacements should reuse the existing player slots unless a later system specifically requires an additional back-picture ID.

## Overworld object graphics

Baseline static object graphics: 0–151.
Dynamic variable-backed graphics: 240–255.

Reserve:
- 152–223: Sam Edition static overworld object graphics
- 224–239: leave unallocated headroom
- 240–255: preserve as the existing dynamic object-gfx range

Per-map local object IDs remain local map resources; do not allocate them globally. Respect the special local IDs defined by the engine.

## Persistent event flags

Verified baseline unused block:
- 0x300–0x3D7 is labeled unused in `flags.h`; representative reference searches found no consumers outside the constant declarations.

Reserve the first 128 flags for Sam Edition:
- `FLAG_SAM_START = 0x300`
- `FLAG_SAM_END = 0x37F`

Leave 0x380–0x3D7 untouched as additional upstream/future headroom.

Subsystems must allocate named flags sequentially inside 0x300–0x37F through the central registry; no thread may choose ad hoc values.

Trainer defeat flags are separate and handled by the trainer-capacity expansion below.

## Persistent variables

Verified unlabeled block:
- 0x408C–0x40A9

Reserve:
- `VAR_SAM_START = 0x408C`
- `VAR_SAM_END = 0x40A9`
- 30 u16 variables total

This block ends immediately before the Quest Log backup variables at 0x40AA.

Use these only for script-visible scalar state. Larger/structured data belongs in Sam Edition save data.

## Trainer flags and save layout

Baseline trainer defeat flags:
- event flags 0x000–0x4FF
- trainer flags begin at 0x500
- baseline max 768 trainer flags -> end 0x7FF
- system flags begin at 0x800
- `FLAGS_COUNT = 0x900` -> 288 flag bytes

With `MAX_TRAINERS_COUNT = 1024`:
- trainer flags become 0x500–0x8FF
- system flags move to 0x900–0x9FF
- `FLAGS_COUNT = 0xA00` -> 320 flag bytes

This adds 32 bytes to the main flag array and 32 bytes to each of the four Quest Log scene flag snapshots: +160 bytes total inside SaveBlock1.

To keep the overall SaveBlock1 size at the stock 0x3D68 and preserve the start of `ramScript` and later fields, repurpose the verified-unused 400-byte `unused_348C` region:
- after the earlier fields grow by 160 bytes, its logical start moves from 0x348C to 0x352C;
- replace it with a 240-byte `struct SamEditionSaveData`;
- 0x352C + 0xF0 = 0x361C, preserving the original `ramScript` start at 0x361C and preserving the final SaveBlock1 size.

Reserve the 240-byte Sam data structure as:
- 0x00–0x0F: version/header/core-mode metadata
- 0x10–0x4F: global mechanic auxiliary state
- 0x50–0x8F: rival / Rocket auxiliary state
- 0x90–0xBF: Gym / Satoshi / postgame auxiliary state
- 0xC0–0xEF: future expansion

Ordinary boolean/script state should still use `FLAG_SAM_*`; ordinary u16 script state should use `VAR_SAM_*`. Use `SamEditionSaveData` only when those scalar systems are unsuitable.

Because trainer/system flag offsets and several SaveBlock1 field offsets change, vanilla save-file compatibility is **not guaranteed**. Sam Edition should version its save data and treat save migration as a separate explicit feature if desired.

## Maps

Do not allocate a speculative global numeric map block.

Policy:
- Rebuilt/rethemed existing locations reuse their existing symbolic map IDs wherever possible.
- Example: Gym 1 remains `PewterCity_Gym`.
- New interiors/areas are appended to the relevant existing map group with descriptive `MAP_* ` symbols.
- A new Sam-specific map group is created only if actual group pressure or architecture makes it useful.
- Never depend on a raw numeric map group/map number in project design documentation; use generated symbols.

## Scripts

Scripts are symbol-first, not number-first.

Use project namespaces such as:
- `EventScript_Sam_*`
- `SamEdition_*`
- system-specific prefixes documented by the applicable implementation authority.

Raw addresses are linker/build outputs and are not hand-reserved.

## Pokédex IDs

Internal species IDs above are implementation allocations, not final Sam Edition Pokédex numbering.

Final custom player-facing sequential numbering remains deferred until roster closure. Code should not assume the internal species ID equals final Sam Dex number for the added species.

## Clean-build gate

No gameplay code should be committed until the untouched `sam-baseline` branch has been built with the selected toolchain and the produced `pokefirered.gba` verifies as SHA-1:
`41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc`.

Documentation/allocation commits are allowed before that build gate because they do not modify game behavior.
