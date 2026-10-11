# Pokémon: Sam Edition — Trainer Construction Rules

This file records the current explicit trainer-data authority applied to production. It does not reopen already-authored major battles, Gym scripts, trainer IDs, maps, flags, or dialogue packages.

## Ordinary trainers
- Build coherent Pokémon for their level from level-up moves.
- No TM or HM moves.
- No held items unless a later specific package deliberately preserves a species-natural held item.
- Useful earlier level-up moves may be retained when a hand-built set is warranted; the default production baseline is the engine's level-up move construction.

## Cooltrainers
- Follow the ordinary baseline.
- They may use HM moves that are reasonable for the player's current point in progression when deliberately authored.
- Non-Gym Cooltrainers use intentionally over-stylized / “tragedeigh” spellings of recognizable human names.

## Gym trainers
- Preserve existing trainer IDs, party bindings, scripts, flags, dialogue, and map choreography.
- A Gym trainer may use that Gym's awarded TM on a compatible Pokémon.
- Gym trainer display names are puns related to the Gym's current specialty.
- Gym Cooltrainers use the type-pun rule first and may use trendy spelling.

## Scientists
- Scientist Pokémon tend to hold evolution items. Production uses evolution stones on two of each three Scientist party slots as a consistent tendency rather than a universal mandate.
- Their moves otherwise follow the ordinary level-up baseline.

## Dialogue
- Preserve ordinary trainer dialogue by default.
- Rewrite ordinary trainer dialogue only when that trainer's overworld sprite/presentation changed and the old text no longer fits.
- Preserve already-authored Gym trainer dialogue; a display-name change alone does not reopen Gym dialogue.
- Major/story-character dialogue remains controlled by that character's specialist authority.

## Major / specialist battles
Rivals, Gym Leaders, Elite Four, Team Rocket/Aqua/Magma story opponents, Satoshi, Thomas, the Fighting Dojo package, Trainer Tower packages, and other explicitly authored specialist encounters are not normalized by the ordinary-trainer cleanup.
