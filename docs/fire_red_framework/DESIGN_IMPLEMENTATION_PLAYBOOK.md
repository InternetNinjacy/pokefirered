# FireRed Design-to-Implementation Playbook

This playbook records reusable methods learned while building Pokémon: Sam Edition. It is intentionally project-agnostic.

The purpose is not to copy Sam Edition choices into another ROM hack. The purpose is to preserve the process for making comparable changes safely and consistently.

## Core rule: capability is reusable, decisions are not

A future project may decide to change no Gyms, all Gyms, one Elite Four member, every trainer portrait, breeding, New Game+, or none of those things.

The framework should know how to implement each class of change without assuming the project wants it.

Examples:

- Reusable capability: replace an Elite Four member, including room presentation, trainer record, party, pre-battle dialogue, defeat dialogue, post-battle routing, first-clear/rematch routing, and graphics.
- Project-specific decision: Blue replaces Lance.
- Reusable capability: rebuild a Gym around a new specialty.
- Project-specific decision: Vermilion becomes Water-themed.
- Reusable capability: add a postgame New Game+ loop.
- Project-specific decision: exactly what carries into New Game+.

## 1. The design-to-implementation stack

Treat a major content change as a stack of surfaces instead of one edit.

1. Authority
   - What is actually decided?
   - What remains optional or open?
   - What vanilla behavior must remain?
2. Mechanical content
   - Trainer parties, moves, held items, AI, rewards, flags, vars, save state.
3. World/map content
   - Layout, collision, warps, object events, triggers, puzzle state, access gates.
4. Presentation
   - Trainer class/name, front sprite, overworld sprite, palettes, room art, signs, dialogue.
5. Progression integration
   - Entry conditions, victory state, retries, rewards, rematches, postgame behavior.
6. Project indexes
   - Record source surfaces, resource allocations, branch/PR provenance, and current status.

A change is not fully understood until all affected layers have been considered, even when only one or two layers require actual edits.

## 2. Theme consistency model

A location or boss should not be considered "themed" merely because its Pokémon type changed.

Use three theme channels:

### A. Visual theme

Possible surfaces:
- room layout and shape;
- tiles, floor markings, walls, props, statues, water, lava, plants, machines, memorials, etc.;
- NPC placement and facing;
- overworld character sprites;
- leader/major-trainer battle portraits;
- palettes;
- signs and room labels.

### B. Mechanical theme

Possible surfaces:
- species selection;
- move selection;
- held items;
- battle format (single/double);
- AI level;
- environmental or puzzle mechanic;
- reward TM/item;
- rematch identity.

### C. Narrative theme

Possible surfaces:
- trainer names or titles;
- pre-battle dialogue;
- defeat dialogue;
- leader speech;
- badge/reward language;
- NPC advice;
- town/world references to the location.

### Minimum theme-density rule

For a major redesigned location, intentionally review all three channels. A project may choose a restrained theme, but the omission should be deliberate.

A useful rule of thumb:
- at least one clear visual signal;
- at least one clear mechanical signal beyond merely changing the leader's party;
- at least one clear narrative signal.

For a full redesign, aim for several coordinated signals in each channel.

## 3. Gym reconstruction workflow

A Gym can range from a roster-only edit to a complete rebuild. Before editing, classify the intended scope.

### Gym scope levels

- Level 0 - Vanilla presentation, only balance/party changes.
- Level 1 - New leader and trainer battle data, same map/puzzle.
- Level 2 - New theme presentation using mostly existing map geometry.
- Level 3 - Puzzle and room reconstruction while preserving the Gym's broad progression role.
- Level 4 - Full custom Gym experience with new art, events, puzzle runtime, and presentation.

Do not automatically escalate scope.

### Gym rebuild checklist

#### Authority packet
Record:
- specialty/type or concept;
- leader identity;
- badge name;
- reward TM/item;
- trainer count;
- trainer themes/naming rules;
- puzzle concept;
- battle format expectations;
- Satoshi/guide/tutorial role if the project has one;
- rematch expectations;
- art requirements.

#### Map and puzzle
Review:
- `data/maps/<Gym>/map.json`;
- `data/maps/<Gym>/scripts.inc`;
- `data/maps/<Gym>/text.inc`;
- referenced layouts under `data/layouts/`;
- tileset or metatile assets if presentation changes;
- object-event IDs and coordinates;
- warp destinations;
- collision and impassable tiles;
- trigger and coordinate events;
- persistent puzzle flags/vars.

When rebuilding a puzzle, preserve a clear entry-to-leader path and explicitly define:
- initial state;
- valid player actions;
- state transitions;
- fail/reset behavior;
- what persists after leaving the map;
- what changes after leader victory.

#### Gym trainers
For every trainer confirm:
- trainer ID and record;
- map object binding;
- class;
- name;
- front sprite;
- party;
- moves/items policy;
- AI;
- single/double format;
- pre-battle text;
- defeat text;
- whether the trainer blocks movement before defeat.

#### Leader
Confirm:
- first-clear party;
- rematch party if applicable;
- portrait/front sprite;
- overworld sprite;
- class/title;
- intro dialogue;
- defeat dialogue;
- badge grant;
- TM/item grant;
- Bag-full/retry behavior when relevant;
- badge/progression flags;
- post-victory dialogue;
- exit/door/puzzle state.

#### Presentation consistency
Before calling the Gym package complete, compare the theme against:
- room visuals;
- trainer names and dialogue;
- leader roster and signature move;
- badge/reward wording;
- tutorial/guide advice;
- any rematch presentation.

## 4. Trainer presentation and sprite workflow

A trainer change may involve more than a party table.

### Battle presentation surfaces

A trainer record can reference:
- trainer class;
- trainer name;
- trainer front sprite/picture;
- encounter music/gender metadata;
- party flags and party table;
- AI flags;
- trainer items.

Primary source areas include:
- `src/data/trainers.h`;
- `src/data/trainer_parties.h`;
- `include/constants/trainers.h` and related trainer constants;
- `src/data/trainer_graphics/`;
- `graphics/` trainer assets;
- `include/trainer_front_sprites.h` and trainer sprite tables.

### Overworld presentation

The character seen on the map is independent from the battle front sprite.

When changing identity, check:
- object event graphics ID in the map JSON;
- overworld sprite sheet and palette;
- movement type;
- facing direction;
- object visibility flags;
- whether a different overworld appearance is needed before versus after an event.

### Start-of-battle versus after-battle presentation

Do not assume one visual state must serve the whole event.

A project may deliberately use different states such as:
- disguised/civilian overworld appearance before battle;
- trainer battle portrait during battle;
- defeated/civilian/changed overworld appearance after battle;
- departure animation or despawn after dialogue.

Implement this with normal event state tools:
- flags;
- vars;
- object visibility routing;
- `setobjectxy`, `setobjectmovementtype`, movement scripts, or object replacement where appropriate;
- separate graphics IDs when a true visual change is required.

Only allocate a new sprite if the project actually needs one. Reuse existing sprites when they meet the design.

## 5. Dialogue state model for trainers and bosses

For any important battle, separate at least these dialogue states:

1. pre-battle;
2. battle defeat text shown by the battle engine;
3. immediate post-victory conversation if used;
4. post-clear repeat interaction;
5. loss/retry behavior;
6. rematch dialogue if the trainer returns later.

Optional states:
- declined optional battle;
- insufficient party requirement;
- reward pending because inventory is full;
- alternate dialogue after related story flags;
- postgame dialogue.

Do not overload one text string for unrelated states merely to save labels.

## 6. Elite Four / League room assembly

League rooms are boss rooms plus progression gates. Treat them as a coordinated chain.

### Room assembly surfaces

Check:
- room map/layout;
- entrance and exit warps;
- door/barrier state;
- boss object placement;
- boss overworld sprite;
- trainer battle record and party;
- trainer front sprite;
- pre-battle/defeat/post-battle text;
- victory flag/state;
- first-clear versus rematch routing;
- script that opens the next room;
- Hall of Fame/Champion chain assumptions.

### Replacing an Elite Four member without forcing the replacement

The reusable operation is:

1. identify the room's existing progression script;
2. preserve the door/advance state machine unless redesign is required;
3. replace or route the trainer battle record;
4. bind the desired front and overworld presentation;
5. replace pre-/post-battle dialogue;
6. route first-clear and rematch parties as the project specifies;
7. verify the next-room transition and League-clear chain remain intact.

A future project may leave the original member untouched. The framework should still know this replacement process.

### Themed Elite Four rooms

If rebuilding the room visually, use the same three-channel theme model as Gyms:
- visual room identity;
- battle identity;
- narrative identity.

Do not let new art accidentally alter critical warps, collision, object coordinates, or door scripting.

## 7. Day Care and early breeding / baby access

FireRed's stock facilities can be extended or repurposed. Do not assume a project wants early breeding.

### Questions to settle first

- Where is the breeding facility?
- When can the player reach it?
- One deposited Pokémon or two?
- Standard Gen III compatibility rules or custom rules?
- Can genderless Pokémon breed with Ditto?
- Are special species allowed?
- How many pending Eggs may exist?
- What happens when the party is full?
- Does withdrawing a parent cancel a pending Egg?
- Are there custom shiny odds?
- Are there game-mode restrictions on deposit/withdrawal?

### Early-breeding pattern learned from Sam Edition

A reusable pattern is to convert an early one-Pokémon Day Care into a two-Pokémon breeding facility while leaving the later Four Island facility independent.

That requires more than changing dialogue:
- a second persistent `DaycareMon` slot;
- deposit/withdrawal UI and fee handling for both parents;
- compatibility calculation;
- Egg-generation state;
- persistent pending Egg data;
- Egg pickup with full-party preservation;
- save-allocation review and compile-time size protection;
- any project-specific deposit guards.

Do not copy Sam Edition's save offsets or shiny rate into another project. Re-audit that project's available save space and desired rules.

### "Babies right off the bat"

If a project wants breeding available at the first reachable Day Care, the framework should support it by:
- enabling the two-parent flow at that early facility;
- making Egg generation active there immediately when compatible parents are deposited;
- ensuring Egg pickup is not gated by a later story flag unless the project explicitly wants that gate;
- keeping compatibility and baby-species logic consistent with the project's species data.

This is an optional capability, not a default project rule.

## 8. New Game+ as an optional framework capability

New Game+ should be represented as an optional advanced system, never as an assumed requirement.

### Design questions

A project choosing NG+ should explicitly decide:
- unlock condition;
- title-screen/menu presentation;
- whether Trainer ID carries over;
- whether party Pokémon carry over;
- whether boxed Pokémon carry over;
- whether items carry over;
- whether money carries over;
- whether Pokédex data carries over;
- when carried Pokémon become accessible;
- badge/HM behavior;
- story flags reset versus carryover;
- Hall of Fame behavior;
- recursion (NG+ from NG+);
- save-capacity edge cases.

### Technical surfaces

Likely surfaces include:
- title-screen/main-menu logic;
- completed-game flag;
- new-game initialization path;
- SaveBlock1/SaveBlock2 data;
- Pokémon storage serialization;
- party-to-PC migration;
- bag encryption/re-keying;
- PC access gating;
- Hall of Fame and game-clear state;
- save-capacity handling.

The framework records the architecture and checklist. Each project supplies its own carryover contract.

## 9. Optional feature implementation pattern

Any optional feature should use this structure:

- **Capability:** what the engine/framework knows how to do.
- **Decision questions:** what the project creator must choose.
- **Source surfaces:** where implementation normally lives.
- **Dependencies:** what must exist first.
- **Common failure modes:** what to protect against.
- **Project record:** exact chosen behavior for this game.

This avoids accidentally turning one project's design into a universal template.

## 10. Theme review checklist

Before finishing a redesigned major location, ask:

- Can a player tell the theme from the room itself?
- Do the trainers reinforce it?
- Does the leader/boss reinforce it?
- Does the puzzle or interaction reinforce it?
- Does the dialogue reinforce it?
- Does the reward make sense for it?
- Are names/titles consistent with it?
- Do the overworld and battle sprites fit the intended identity?
- Is there enough variety that the theme does not feel like one repeated prop/species?
- Is anything strongly contradicting the intended theme?

The answer does not always need to be "yes" to every item. It does need to be deliberate.

## 11. Safe reuse rule

When applying this playbook to a new project:

1. load the project's authority first;
2. ask which categories are actually changing;
3. inherit only the relevant implementation method;
4. verify the new project's baseline source surfaces;
5. record project-specific decisions separately;
6. never import Sam Edition species, characters, Gym specialties, dialogue, names, rewards, or progression choices unless the new project explicitly adopts them.
