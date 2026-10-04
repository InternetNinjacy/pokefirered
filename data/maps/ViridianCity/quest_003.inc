@ QUEST-003 — Viridian City: The Runaway Nidoran
@ Persistent state contract:
@   0 inactive
@   1 active / Nidoran missing / Spearow unresolved
@   2 Spearow resolved / reunion pending
@   3 reward pending
@   4 complete

ViridianCity_EventScript_UpdateRunawayNidoran::
	removeobject LOCALID_VIRIDIAN_RUNAWAY_NIDORAN
	call_if_eq VAR_SQ_VIRIDIAN_STATE, 2, ViridianCity_EventScript_ShowReturnedNidoran
	call_if_eq VAR_SQ_VIRIDIAN_STATE, 3, ViridianCity_EventScript_ShowReturnedNidoran
	call_if_eq VAR_SQ_VIRIDIAN_STATE, 4, ViridianCity_EventScript_ShowReturnedNidoran
	return

ViridianCity_EventScript_ShowReturnedNidoran::
	addobject LOCALID_VIRIDIAN_RUNAWAY_NIDORAN
	return

ViridianCity_EventScript_NidoranTrainer::
	lock
	faceplayer
	goto_if_set FLAG_SQ_VIRIDIAN_COMPLETE, ViridianCity_EventScript_NidoranTrainerComplete
	goto_if_unset FLAG_SYS_POKEDEX_GET, ViridianCity_EventScript_NidoranTrainerBeforePokedex
	goto_if_eq VAR_SQ_VIRIDIAN_STATE, 0, ViridianCity_EventScript_NidoranTrainerStart
	goto_if_eq VAR_SQ_VIRIDIAN_STATE, 1, ViridianCity_EventScript_NidoranTrainerReminder
	goto_if_eq VAR_SQ_VIRIDIAN_STATE, 2, ViridianCity_EventScript_NidoranTrainerReunion
	goto_if_eq VAR_SQ_VIRIDIAN_STATE, 3, ViridianCity_EventScript_NidoranTrainerReward
	goto ViridianCity_EventScript_NidoranTrainerComplete
	end

ViridianCity_EventScript_NidoranTrainerBeforePokedex::
	msgbox ViridianCity_Text_NidoranTrainerBeforePokedex
	release
	end

ViridianCity_EventScript_NidoranTrainerStart::
	msgbox ViridianCity_Text_NidoranTrainerStart
	setvar VAR_SQ_VIRIDIAN_STATE, 1
	release
	end

ViridianCity_EventScript_NidoranTrainerReminder::
	msgbox ViridianCity_Text_NidoranTrainerReminder
	release
	end

ViridianCity_EventScript_NidoranTrainerReunion::
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	waitmoncry
	msgbox ViridianCity_Text_NidoranTrainerReunion
	setvar VAR_SQ_VIRIDIAN_STATE, 3
	goto ViridianCity_EventScript_NidoranTrainerReward
	end

ViridianCity_EventScript_NidoranTrainerReward::
	checkitemspace ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_EventScript_NidoranTrainerNoRoom
	msgbox ViridianCity_Text_NidoranTrainerReward
	giveitem ITEM_POKE_BALL, 5
	setvar VAR_SQ_VIRIDIAN_STATE, 4
	setflag FLAG_SQ_VIRIDIAN_COMPLETE
	msgbox ViridianCity_Text_NidoranTrainerThanks
	release
	end

ViridianCity_EventScript_NidoranTrainerNoRoom::
	msgbox ViridianCity_Text_NidoranTrainerNoRoom
	release
	end

ViridianCity_EventScript_NidoranTrainerComplete::
	msgbox ViridianCity_Text_NidoranTrainerComplete
	release
	end

ViridianCity_EventScript_ReturnedNidoran::
	lock
	faceplayer
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	waitmoncry
	msgbox ViridianCity_Text_ReturnedNidoran
	release
	end

ViridianCity_EventScript_DisturbedGrass::
	goto_if_ne VAR_SQ_VIRIDIAN_STATE, 1, ViridianCity_EventScript_DisturbedGrassInactive
	msgbox ViridianCity_Text_DisturbedGrass, MSGBOX_SIGN
	end

ViridianCity_EventScript_DisturbedGrassInactive::
	msgbox ViridianCity_Text_DisturbedGrassInactive, MSGBOX_SIGN
	end

ViridianCity_Text_NidoranTrainerBeforePokedex::
	.string "My NIDORAN♀ likes to wander, but\n"
	.string "she always stays close to me.$"

ViridianCity_Text_NidoranTrainerStart::
	.string "Please help! My NIDORAN♀ got\n"
	.string "frightened and ran toward ROUTE 22!\p"
	.string "I saw the grass shake near the west\n"
	.string "edge of town.$"

ViridianCity_Text_NidoranTrainerReminder::
	.string "My NIDORAN♀ is still missing.\n"
	.string "She ran west toward ROUTE 22.$"

ViridianCity_Text_NidoranTrainerReunion::
	.string "NIDORAN♀! You're safe!\p"
	.string "Thank you for bringing her back.$"

ViridianCity_Text_NidoranTrainerReward::
	.string "Please take these. They may help\n"
	.string "the next POKéMON you find.$"

ViridianCity_Text_NidoranTrainerNoRoom::
	.string "You can't carry all five POKé BALLS\n"
	.string "right now. I'll keep them for you.$"

ViridianCity_Text_NidoranTrainerThanks::
	.string "Thank you again. I'll keep a closer\n"
	.string "eye on NIDORAN♀ from now on.$"

ViridianCity_Text_NidoranTrainerComplete::
	.string "NIDORAN♀ is much calmer now.\n"
	.string "We're staying together.$"

ViridianCity_Text_ReturnedNidoran::
	.string "NIDORAN♀ stays close beside her\n"
	.string "TRAINER.$"

ViridianCity_Text_DisturbedGrass::
	.string "The grass is bent and scattered.\n"
	.string "Something small ran west from here.$"

ViridianCity_Text_DisturbedGrassInactive::
	.string "The grass here looks recently\n"
	.string "disturbed.$"
