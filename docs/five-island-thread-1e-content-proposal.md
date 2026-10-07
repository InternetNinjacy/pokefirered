# Thread 1E: Five Island exact-content closure proposal

Status: ACCEPTED by the user on October 7, 2026 ("Yes Approved"). This is the bounded Thread 1E exact-content closure authority; implementation status is tracked separately.

Source baseline: production `5dca0d7c412ef5d6fe12598c38fe22faeffd934e`; draft PR #295 at `3165bcccb16e174a1d58b44774515bae08d824a9`. Current Rocket Decision Record and Implementation Addendum supply the locked constraints. The user's latest request authorizes developing the missing content; the user selected short scripted demonstrations rather than additional battles.

## Preserve the approved core

Thomas ordered the program, receives the Admins' reports remotely, and used its results to advance within Rocket. Thomas is absent from the warehouse. No redemption, arrest, extra Thomas encounter, or obsolete Victory Road material is added.

Keep the two approved Admin teams, levels, first-four base-line moves, existing IVs, late AI, empty bags and no held items from PR #295. Preserve every existing warp, pickup, hidden item, arrow puzzle, cage interaction, external Sevii unlock and Gideon/Sapphire encounter. Gideon remains a separate scientist; he is not one of the two forced-growth showcase trainers.

## Exact ordinary trainer packages

The existing three Grunts are reused. Their ordinary supporting Pokémon retain normal generated moves. Only the final ace follows the forced-growth rule. Each battle is Single; no held items or bag healing. Retain Grunts' IV 0 and CHECK_BAD_MOVE AI. New Scientists use the same IV/AI policy, stock Scientist art and class, and the displayed trainer name SCIENTIST.

| Actor | Supporting Pokémon, in order | Final forced-growth ace | Ace moves |
| --- | --- | --- | --- |
| Existing Grunt 1, trainer 42 | Houndour 49, Houndour 49 | Graveler 51 | Tackle, Defense Curl, Mud Sport, Rock Throw |
| Existing Grunt 2, trainer 47 | Machop 48, Machop 48 | Machoke 52 | Low Kick, Leer, Focus Energy, Karate Chop |
| Existing Grunt 3, trainer 48 | Hypno 49, Hypno 49 | Lairon 53 | Tackle, Harden, Mud Slap, Headbutt |
| New Scientist 1 | Magnemite 50, Voltorb 50 | Seadra 53 | Bubble, Smokescreen, Leer, Water Gun |
| New Scientist 2 | Drowzee 51, Abra 51 | Kadabra 54 | Teleport, NONE, NONE, NONE |

Keep Grunts' existing positions. Proposed new Scientist positions are (14,12) and (18,13), respectively, using passable floor tiles in the existing left-hand warehouse section, with elevation 3. The implementation must verify accessible interaction tiles and the arrow traversal before finalizing those positions. No layout edits are authorized by this proposal. Use new named local IDs, append object events, and the existing FLAG_HIDE_FIVE_ISLAND_ROCKETS visibility flag. Allocate two trainer IDs from Rocket's reserved 900–939 block only after a fresh Symbol Registry and active-PR collision check. This document does not allocate them.

Do not add an all-trainers-defeated gate to the stock maze. The ordinary trainers remain trainer encounters along its routes. The two demonstrations are mandatory in Admin 1's first-victory callback, before the stock shortcut opens; they do not add battles.

## Exact trainer dialogue

Text below is the proposed complete wording. Implementation may split text into ordinary two-line pages without changing words.

### Grunt 1

Before: "Why wait years for power? We can turn a little GEODUDE into a GRAVELER in one session. Watch what you're buying!"

Defeat: "All that weight... Still the same little tricks!"

After: "It grew a tougher body. Nobody taught it how to use that body. That part wasn't in the sales pitch."

### Grunt 2

Before: "This MACHOKE didn't need years of training. We gave it muscle overnight! Let's see you stand in its way!"

Defeat: "The muscle's there! Where's the technique?"

After: "It knows the same moves it knew as a MACHOP. More muscle doesn't tell it when to strike."

### Grunt 3

Before: "An ARON's little shell becomes LAIRON armor. Faster growth, faster profit. That's how we do business!"

Defeat: "Armor can't cover every mistake!"

After: "It still fights like the little ARON we brought in. The armor changed. Its training didn't."

### Scientist 1

Before: "Our process turns HORSEA into SEADRA ahead of schedule. Physical power, delivered immediately! Observe the result."

Defeat: "The body developed. Its control did not."

After: "The growth is real. So are the missing skills. We cannot replace practice with another exposure."

### Scientist 2

Before: "ABRA becomes KADABRA without the wait. An evolved body is proof of success. Surely you can see that!"

Defeat: "TELEPORT... That's all it learned!"

After: "We skipped its development. The report calls that a saving. The battle calls it something else."

### Admin 1

Before: "THOMAS ordered this program. We send him results, not excuses. Stronger bodies in less time. That's what put him on the way up. You want to challenge those results?"

Defeat: "We accelerated their growth... Not their training."

First-victory response, before demonstrations: "You beat the finished stock. Look at the tests before you call this a success."

After both demonstrations, before opening the existing shortcut: "I'll open the way back. Rest if you need to. The ADMIN ahead of me runs this warehouse. He still thinks power will settle everything."

Repeat interaction: "The way back is open. The ADMIN ahead runs this warehouse."

### Admin 2

Before: "THOMAS gave the order. We built the operation. Our reports helped him rise through TEAM ROCKET. Don't mistake unfinished training for a failure of power. I'll show you what these results can do!"

Defeat: "The bodies grew... The skills never caught up!"

Shutdown: "Enough. Shut down the apparatus. Open the pens. This warehouse is finished. We'll report the failure to THOMAS ourselves. We're leaving."

The shutdown removes the Admins and operation staff using the stock completion/visibility state. No later Admin appearances or arrest scene are added. Their removal from Rocket remains off-screen, as the existing authority specifies. Gideon remains for the Sapphire encounter.

## Mandatory short demonstrations

Run these sequentially in Admin 1's first-victory callback. Existing trainer defeat state supplies one-time routing; repeat Admin interaction does not invoke the callback again. No new persistent showcase flag or shared Rocket variable is needed. On loss, the callback is not entered. Leaving, blackout and re-entry preserve the stock battle/shortcut rules.

### Machoke: development test

Display a MACHOKE portrait and its cry. These are a Rocket specimen presentation, not an entry in either battle party or the player's collection.

Admin 1: "Controlled test. MACHOKE, strike on my count. One..."

Narrator: "MACHOKE swings before the count. Its blow is powerful, but badly timed."

Admin 1: "Again. Wait for the count."

Narrator: "MACHOKE hesitates, then repeats the same early swing."

Admin 1: "A stronger body. The same unfinished training."

Close the portrait. No damage, HP changes, battle or item use occurs. The demonstration establishes the failure through text and cries; it does not require new dummy or specimen overworld art.

### Seadra: successful growth, poor obedience

Display a HORSEA portrait and cry.

Admin 1: "Next subject. HORSEA. Start the forced-growth apparatus."

Close the HORSEA portrait, use the existing screen fade and electrical sound, then display SEADRA and its cry. This is a fixed HORSEA-to-SEADRA visual sequence. It does not call player evolution, generate a Pokémon, or alter a saved Pokémon record.

Narrator: "HORSEA has become SEADRA!"

Admin 1: "SEADRA, face the target. Use WATER GUN."

Narrator: "SEADRA turns away. It ignores the order and sprays the floor."

Admin 1: "The evolution worked. The control did not."

Close the portrait and return to the normal map presentation. Continue the existing Admin 1 shortcut movement and arrows.

This is poor obedience by a Rocket-owned test subject. It does not change player obedience rules, simulate a player evolution failure, or claim that all ordinary evolved Pokémon become disobedient.

## Evidence and aftermath text

Computer, before shutdown:

"FORCED-GROWTH PROGRAM. Ordered by THOMAS. Warehouse ADMIN reports. Physical evolution: successful. Learned techniques: unchanged. Control tests: incomplete. Faster bodies. No replacement for training."

Computer, after shutdown:

"FORCED-GROWTH PROGRAM: CLOSED. The apparatus is off. The report still records THOMAS's order, accelerated growth, and failed control tests."

Cage, before shutdown:

"POKéMON are locked in the pens. The warehouse's forced-growth subjects are being held here."

Cage, after shutdown:

"The pens are unlocked. The POKéMON have fled. The forced-growth apparatus is silent."

Use FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE for the computer/cage aftermath, preserving the stock persistent completion model. No new item, Pokémon gift, reward, recovery record or competing evidence progression is added. If another thread supplies a merged shared dossier interface, integrate this operation through that interface after reconciliation; do not create a replacement state model here.

## Implementation and acceptance boundary

After content acceptance, implement only these additions on draft #295 against fresh production. Audit all active Rocket/Thomas PRs and Registry allocations again. Preserve Gideon's dialogue, battle and Sapphire handoff verbatim. Retain existing Admin battle callbacks, loss behavior and shortcut handling; add demonstrations within the first-victory path and extra staff removals within final cleanup. Name the existing Grunt 1 object so final cleanup explicitly removes it too.

Check map-object coordinates, collision, interactions, local IDs, trainer IDs and constants; validate the fixed five-ace mapping and explicit four-slot moves; compile/link using CI; verify completion/re-entry and no unrelated event loss. No player Pokémon record is ever read or written by the demonstrations, so fainted/dead status, starters, held items, personality, OT/ID, moves, level, experience, party/storage capacity and custom species evolution eligibility are outside their execution path.

The new supporting parties, levels, dialogue and exact presentation are newly authored choices. User acceptance closed the content gate. This package is the bounded Thread 1E closure authority, subject to the established hierarchy. It must not silently supersede unrelated Rocket or Thomas records.
