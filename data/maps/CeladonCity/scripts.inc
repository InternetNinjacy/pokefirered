CeladonCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_OnTransition
	.byte 0

CeladonCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CELADON_CITY
	call CeladonCity_EventScript_UpdateGreen
	end

CeladonCity_EventScript_LittleGirl::
	msgbox CeladonCity_Text_GotMyKoffingInCinnabar, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan1::
	lock
	msgbox CeladonCity_Text_GymIsGreatFullOfWomen
	release
	end

CeladonCity_EventScript_Woman::
	msgbox CeladonCity_Text_GameCornerIsBadForCitysImage, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan2::
	msgbox CeladonCity_Text_BlewItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_EventScript_SoftboiledTutor::
	goto EventScript_SoftboiledTutor
	end

CeladonCity_EventScript_FatMan::
	lock
	faceplayer
	msgbox CeladonCity_Text_MyTrustedPalPoliwrath
	closemessage
	applymovement LOCALID_CELADON_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_Poliwrath::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	msgbox CeladonCity_Text_Poliwrath
	closemessage
	waitmoncry
	applymovement LOCALID_CELADON_POLIWRATH, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_RocketGrunt1::
	msgbox CeladonCity_Text_KeepOutOfTeamRocketsWay, MSGBOX_NPC
	end

CeladonCity_EventScript_RocketGrunt2::
	msgbox CeladonCity_Text_GetLostOrIllPunchYou, MSGBOX_NPC
	end

CeladonCity_EventScript_Boy::
	msgbox CeladonCity_Text_ScaldedTongueOnTea, MSGBOX_NPC
	end

CeladonCity_EventScript_SilphCoScientist::
	msgbox CeladonCity_Text_SomeoneStoleSilphScope, MSGBOX_NPC
	end

CeladonCity_EventScript_TrainerTips1::
	msgbox CeladonCity_Text_ExplainXAccuracyDireHit, MSGBOX_SIGN
	end

CeladonCity_EventScript_CitySign::
	msgbox CeladonCity_Text_CitySign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_ERIKA, 0
	msgbox CeladonCity_Text_GymSign
	releaseall
	end

CeladonCity_EventScript_MansionSign::
	msgbox CeladonCity_Text_MansionSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_DeptStoreSign::
	msgbox CeladonCity_Text_DeptStoreSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_TrainerTips2::
	msgbox CeladonCity_Text_GuardSpecProtectsFromStatus, MSGBOX_SIGN
	end

CeladonCity_EventScript_PrizeExchangeSign::
	msgbox CeladonCity_Text_PrizeExchangeSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GameCornerSign::
	msgbox CeladonCity_Text_GameCornerSign, MSGBOX_SIGN
	end

@ Pokémon: Sam Edition — Green Celadon checkpoint.
CeladonCity_EventScript_UpdateGreen::
	setvar VAR_TEMP_1, 0
	setflag FLAG_TEMP_11
	goto_if_unset FLAG_DEFEATED_ERIKA, EventScript_Return
	goto_if_defeated TRAINER_GREEN_SS_ANNE_DITTO, CeladonCity_EventScript_GreenPriorDone
	goto_if_defeated TRAINER_GREEN_SS_ANNE_ESPEON, CeladonCity_EventScript_GreenPriorDone
	goto_if_defeated TRAINER_GREEN_SS_ANNE_RAICHU, CeladonCity_EventScript_GreenPriorDone
	return

CeladonCity_EventScript_GreenPriorDone::
	goto_if_defeated TRAINER_GREEN_CELADON_DITTO, EventScript_Return
	goto_if_defeated TRAINER_GREEN_CELADON_ESPEON, EventScript_Return
	goto_if_defeated TRAINER_GREEN_CELADON_RAICHU, EventScript_Return
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_1, 1
	return

CeladonCity_EventScript_GreenExitTrigger::
	goto CeladonCity_EventScript_Green

CeladonCity_EventScript_Green::
	lockall
	applymovement LOCALID_CELADON_GREEN, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_LAST_TALKED, LOCALID_CELADON_GREEN
	playbgm MUS_ENCOUNTER_RIVAL, 0
	goto_if_eq VAR_STARTER_MON, 0, CeladonCity_EventScript_GreenRaichu
	goto_if_eq VAR_STARTER_MON, 1, CeladonCity_EventScript_GreenDitto
	goto CeladonCity_EventScript_GreenEspeon
CeladonCity_EventScript_GreenDitto::
	trainerbattle_no_intro TRAINER_GREEN_CELADON_DITTO, CeladonCity_Text_GreenDefeat
	goto CeladonCity_EventScript_GreenWon
CeladonCity_EventScript_GreenEspeon::
	trainerbattle_no_intro TRAINER_GREEN_CELADON_ESPEON, CeladonCity_Text_GreenDefeat
	goto CeladonCity_EventScript_GreenWon
CeladonCity_EventScript_GreenRaichu::
	trainerbattle_no_intro TRAINER_GREEN_CELADON_RAICHU, CeladonCity_Text_GreenDefeat
	goto CeladonCity_EventScript_GreenWon
CeladonCity_EventScript_GreenWon::
	msgbox CeladonCity_Text_GreenPost
	closemessage
	setvar VAR_TEMP_1, 0
	setflag FLAG_TEMP_11
	removeobject LOCALID_CELADON_GREEN
	fadedefaultbgm
	release
	end

CeladonCity_Text_GreenDefeat::
	.string "Okay. Better... but not finished.$"
CeladonCity_Text_GreenPost::
	.string "The new moves worked. The items\n"
	.string "worked too. But you still found\l"
	.string "openings.\p"
	.string "That means the team isn't balanced\n"
	.string "yet. Good. Now I know what I need\l"
	.string "to fix.$"
