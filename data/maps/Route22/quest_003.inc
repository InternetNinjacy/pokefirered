@ QUEST-003 — Route 22 portion of The Runaway Nidoran

Route22_OnTransition_Quest003::
	removeobject LOCALID_ROUTE22_RUNAWAY_NIDORAN
	call_if_eq VAR_SQ_VIRIDIAN_STATE, 1, Route22_EventScript_ShowRunawayNidoran
	return

Route22_EventScript_ShowRunawayNidoran::
	addobject LOCALID_ROUTE22_RUNAWAY_NIDORAN
	return

Route22_EventScript_NidoranTracks::
	goto_if_ne VAR_SQ_VIRIDIAN_STATE, 1, Route22_EventScript_NidoranTracksInactive
	msgbox Route22_Text_NidoranTracks, MSGBOX_SIGN
	end

Route22_EventScript_NidoranTracksInactive::
	msgbox Route22_Text_NidoranTracksInactive, MSGBOX_SIGN
	end

Route22_EventScript_SpearowFeathers::
	goto_if_ne VAR_SQ_VIRIDIAN_STATE, 1, Route22_EventScript_SpearowFeathersInactive
	msgbox Route22_Text_SpearowFeathers, MSGBOX_SIGN
	end

Route22_EventScript_SpearowFeathersInactive::
	msgbox Route22_Text_SpearowFeathersInactive, MSGBOX_SIGN
	end

Route22_EventScript_RunawayNidoran::
	lock
	faceplayer
	goto_if_ne VAR_SQ_VIRIDIAN_STATE, 1, Route22_EventScript_RunawayNidoranInactive
	goto_if_questlog EventScript_ReleaseEnd
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	waitmoncry
	msgbox Route22_Text_RunawayNidoranCornered
	setwildbattle SPECIES_SPEAROW, 6
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route22_EventScript_RunawayNidoranRescued
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route22_EventScript_RunawayNidoranRescued
	msgbox Route22_Text_SpearowRetry
	release
	end

Route22_EventScript_RunawayNidoranRescued::
	setvar VAR_SQ_VIRIDIAN_STATE, 2
	removeobject LOCALID_ROUTE22_RUNAWAY_NIDORAN
	msgbox Route22_Text_RunawayNidoranSafe
	release
	end

Route22_EventScript_RunawayNidoranInactive::
	msgbox Route22_Text_RunawayNidoranInactive
	release
	end

Route22_Text_NidoranTracks::
	.string "Tiny tracks lead west from VIRIDIAN.\n"
	.string "They look fresh.$"

Route22_Text_NidoranTracksInactive::
	.string "There are a few tiny tracks in the\n"
	.string "dirt.$"

Route22_Text_SpearowFeathers::
	.string "Several SPEAROW feathers lie here.\n"
	.string "The tiny tracks stop nearby.$"

Route22_Text_SpearowFeathersInactive::
	.string "A few bird feathers are caught in\n"
	.string "the grass.$"

Route22_Text_RunawayNidoranCornered::
	.string "NIDORAN♀ cries out!\p"
	.string "A SPEAROW swoops down and blocks\n"
	.string "her escape!$"

Route22_Text_SpearowRetry::
	.string "The SPEAROW still circles nearby.\n"
	.string "NIDORAN♀ needs help.$"

Route22_Text_RunawayNidoranSafe::
	.string "The SPEAROW is driven off!\p"
	.string "NIDORAN♀ calms down, then hurries\n"
	.string "back toward VIRIDIAN CITY.$"

Route22_Text_RunawayNidoranInactive::
	.string "NIDORAN♀ watches you cautiously.$"
