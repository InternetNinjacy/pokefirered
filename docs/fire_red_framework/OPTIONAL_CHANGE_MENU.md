# Pokémon FireRed Hack - Menu of Possible Changes

This is a plain-language menu for people who want to change Pokémon FireRed but may not know what is possible yet.

Nothing on this list is required. Pick only the ideas that fit your game.

## 1. Pokémon and Pokédex

You can:
- change which Pokémon are in the game;
- add or remove wild Pokémon from an area;
- change encounter rates and levels;
- add new gift Pokémon;
- add new static Pokémon you can find on the map;
- change evolution methods;
- make trade evolutions work by level or item instead;
- change types, stats, abilities, moves, or TM compatibility;
- change Pokédex text and ordering;
- add special rules for rare Pokémon.

## 2. Starters

You can:
- replace the three starter choices;
- offer more or fewer choices;
- change starter levels or moves;
- change which rival Pokémon is picked;
- add preset player or rival names;
- make starter choice affect later battles or story events.

## 3. Wild Encounters

You can:
- change land, water, fishing, and Rock Smash encounters;
- make rare Pokémon appear in normal areas;
- make areas feel different by changing species groups;
- change encounter levels;
- change encounter rates;
- add special one-time encounters.

## 4. Trainers

You can:
- change trainer teams;
- change levels and moves;
- change held items;
- change battle AI;
- change Singles into Doubles;
- change trainer names and classes;
- change trainer battle pictures;
- change the overworld sprite shown before and after a battle;
- change pre-battle, defeat, and post-battle dialogue;
- add new recurring rivals.

## 5. Gyms

You can make a small Gym change or rebuild the whole Gym.

Possible changes include:
- new Gym type or theme;
- new Gym Leader;
- new badge name;
- new TM reward;
- new trainer teams;
- new trainer names and dialogue;
- new leader sprite or portrait;
- new room art;
- new trainer placement;
- new puzzle;
- new battle format;
- new guide/tutorial character;
- new rematch team.

A good Gym theme should show up in more than one place. The room, trainers, battles, dialogue, puzzle, and reward can all help sell the idea.

## 6. Elite Four and Pokémon League

You can:
- change Elite Four teams;
- replace one or more League members;
- change trainer portraits and overworld sprites;
- change their room art and layout;
- change pre-battle and post-battle dialogue;
- change first-clear and rematch teams;
- change the Champion;
- keep the normal door and room progression while changing only the people and battles.

## 7. Maps and Towns

You can:
- move NPCs;
- add or remove NPCs;
- change buildings;
- reuse unused rooms;
- change signs;
- move item balls;
- add small puzzles;
- add hidden areas;
- change warps and entrances;
- change how a town looks.

Map changes should always protect important warps, collision, story triggers, and required paths.

## 8. Side Quests

You can add quests such as:
- find missing items;
- solve a puzzle;
- fight a special trainer;
- defeat a wild Pokémon;
- bring a Pokémon to an NPC;
- choose whether to return or keep an item;
- collect several clues;
- complete a small town story.

Good quests need safe state tracking so they can be started, stopped, resumed, and finished without giving duplicate rewards.

## 9. Gifts and Special Pokémon

You can:
- give Pokémon from NPCs;
- give Pokémon with a special OT name and ID;
- set level, moves, gender, nature, held item, and other traits;
- send the Pokémon to the PC if the party is full;
- keep the reward available if both party and storage are full;
- make one-time rewards safe after save/load.

## 10. Day Care, Breeding, and Eggs

You can:
- make an early Day Care accept two Pokémon;
- allow breeding as soon as the first Day Care is reached;
- keep the later Four Island Day Care separate;
- use normal Gen III breeding rules or custom rules;
- allow genderless Pokémon to breed with Ditto when appropriate;
- change Egg or shiny odds;
- add special Egg rewards;
- control what happens when the party is full.

Making an early one-Pokémon Day Care into a real breeding center needs save space for the second parent and Egg state. It is not just a dialogue change.

## 11. Items, TMs, and Shops

You can:
- change TM moves;
- add or move TM rewards;
- change shop stock;
- add evolution items;
- change prices;
- add key items;
- change held items;
- make TMs reusable if the project wants that;
- expand the number of TMs, with extra engine work if needed.

## 12. Story and Dialogue

You can:
- rewrite NPC dialogue;
- add new rivals;
- change Team Rocket scenes;
- add optional choices;
- change who appears in a scene;
- make characters use different dialogue before and after battles;
- add postgame dialogue;
- use flags and variables to make dialogue react to what the player has done.

## 13. Sprites and Visuals

You can:
- change trainer battle portraits;
- change overworld sprites;
- give a character one look before a battle and another after it;
- add new palettes;
- change room tiles and decorations;
- add custom Pokémon graphics;
- replace badge or item art.

Battle portraits and overworld sprites are separate systems. Changing one does not automatically change the other.

## 14. Battle Rules and Difficulty

You can:
- change trainer AI;
- change trainer items;
- change Singles to Doubles;
- make some bosses stronger than normal trainers;
- create special boss rules;
- change type matchups or Pokémon types;
- create different rules for ordinary trainers, Gym trainers, rivals, and bosses.

## 15. Save Data and Persistent Systems

You can add systems that remember new information, but save space must be planned carefully.

Examples:
- new quest states;
- new rival names;
- permanent character states;
- extra Day Care data;
- special mode settings;
- New Game+ carryover information.

Do not place new save data in unused-looking space until that space is checked and formally assigned.

## 16. New Game+

New Game+ is optional.

A project can choose to:
- unlock it after beating the game;
- show it on the title menu;
- keep the same Trainer ID;
- carry Pokémon into a new run;
- carry items into a new run;
- keep carried Pokémon in the PC until the new starter is received;
- allow repeated New Game+ runs;
- choose which story flags, badges, Pokédex data, money, or other progress reset.

The important part is to decide the carryover rules first. The framework can support the system without requiring every game to use it.

## 17. Postgame and Rematches

You can:
- add stronger Gym rematches;
- add Elite Four rematches;
- add new rival battles;
- add postgame gifts;
- add new quests;
- change Sevii Island content;
- add special battles after certain Pokédex goals.

## 18. Quality and Consistency Questions

Before finishing a feature, ask:
- Does it fit the game's theme?
- Does the map match the idea?
- Do the trainers match the idea?
- Does the dialogue match the idea?
- Do the sprites match the character?
- Does the reward make sense?
- Can the player get stuck?
- Can the player get the reward twice by accident?
- Does leaving and coming back work?
- Does saving and loading keep the right state?

## 19. How to Use This Menu

Start by choosing a category and describing what you want in plain language.

For example:
- "I want to turn one Gym into a Ghost Gym."
- "I want breeding at the first Day Care."
- "I want a rival to have a different sprite after I beat them."
- "I want to replace one Elite Four member."
- "I want New Game+ but only Pokémon should carry over."

The framework should then find the right FireRed systems, list the choices that still need to be made, and implement only the changes you actually chose.
