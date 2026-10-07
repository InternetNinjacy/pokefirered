SaffronCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_OnTransition
	.byte 0

SaffronCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SAFFRON_CITY
	call_if_unset FLAG_RESCUED_MR_FUJI, SaffronCity_EventScript_MoveDoorGuardGrunt
	call SaffronCity_EventScript_UpdateGreen
	end

SaffronCity_EventScript_MoveDoorGuardGrunt::
	setobjectxyperm LOCALID_SAFFRON_DOOR_GUARD_GRUNT, 33, 31
	return

SaffronCity_EventScript_RocketGrunt1::
	msgbox SaffronCity_Text_WhatDoYouWantGetLost, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt2::
	msgbox SaffronCity_Text_BossTakeTownForTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt3::
	msgbox SaffronCity_Text_DontGetDefiantOrIllHurtYou, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt4::
	msgbox SaffronCity_Text_SaffronBelongsToTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt5::
	msgbox SaffronCity_Text_CriminalLifeMakesMeFeelAlive, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt6::
	msgbox SaffronCity_Text_WatchWhereYoureWalking, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt7::
	msgbox SaffronCity_Text_WeCanExploitMonsAroundWorld, MSGBOX_NPC
	end

SaffronCity_EventScript_DoorGuardGrunt::
	lock
	goto_if_set FLAG_RESCUED_MR_FUJI, SaffronCity_EventScript_DoorGuardAsleep
	applymovement LOCALID_SAFFRON_DOOR_GUARD_GRUNT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SaffronCity_Text_ImASecurityGuard
	release
	end

SaffronCity_EventScript_DoorGuardAsleep::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox SaffronCity_Text_HesTakingASnooze
	release
	end

SaffronCity_EventScript_WorkerM::
	msgbox SaffronCity_Text_YouBeatTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster::
	msgbox SaffronCity_Text_SafeToGoOutAgain, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass::
	msgbox SaffronCity_Text_PeopleComingBackToSaffron, MSGBOX_NPC
	end

SaffronCity_EventScript_Boy::
	msgbox SaffronCity_Text_FlewHereOnPidgeot, MSGBOX_NPC
	end

SaffronCity_EventScript_Pidgeot::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEOT, CRY_MODE_NORMAL
	msgbox SaffronCity_Text_Pidgeot
	waitmoncry
	release
	end

SaffronCity_EventScript_Man::
	msgbox SaffronCity_Text_SawRocketBossEscaping, MSGBOX_NPC
	end

SaffronCity_EventScript_CitySign::
	msgbox SaffronCity_Text_CitySign, MSGBOX_SIGN
	end

SaffronCity_EventScript_DojoSign::
	msgbox SaffronCity_Text_FightingDojo, MSGBOX_SIGN
	end

SaffronCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_SABRINA, 0
	msgbox SaffronCity_Text_GymSign
	releaseall
	end

SaffronCity_EventScript_TrainerTips1::
	msgbox SaffronCity_Text_FullHealCuresStatus, MSGBOX_SIGN
	end

SaffronCity_EventScript_TrainerTips2::
	msgbox SaffronCity_Text_GreatBallImprovedCatchRate, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphCoSign::
	msgbox SaffronCity_Text_SilphCoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MrPsychicsHouseSign::
	msgbox SaffronCity_Text_MrPsychicsHouse, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphProductSign::
	msgbox SaffronCity_Text_SilphsLatestProduct, MSGBOX_SIGN
	end

SaffronCity_EventScript_TrainerFanClubSign::
	msgbox SaffronCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

@ Pokémon: Sam Edition — Green rival checkpoint.
SaffronCity_EventScript_UpdateGreen::
	setflag FLAG_TEMP_11
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_EventScript_ShowGreen
	return

SaffronCity_EventScript_ShowGreen::
	goto_if_defeated TRAINER_GREEN_SAFFRON_DITTO, EventScript_Return
	goto_if_defeated TRAINER_GREEN_SAFFRON_ESPEON, EventScript_Return
	goto_if_defeated TRAINER_GREEN_SAFFRON_RAICHU, EventScript_Return
	clearflag FLAG_TEMP_11
	return

SaffronCity_EventScript_Green::
	lock
	faceplayer
	setvar VAR_LAST_TALKED, LOCALID_SAFFRON_GREEN
	playbgm MUS_ENCOUNTER_RIVAL, 0
	goto_if_eq VAR_STARTER_MON, 0, SaffronCity_EventScript_GreenRaichu
	goto_if_eq VAR_STARTER_MON, 1, SaffronCity_EventScript_GreenDitto
	goto SaffronCity_EventScript_GreenEspeon
SaffronCity_EventScript_GreenDitto::
	trainerbattle_no_intro TRAINER_GREEN_SAFFRON_DITTO, SaffronCity_Text_GreenDefeat
	goto SaffronCity_EventScript_GreenWon
SaffronCity_EventScript_GreenEspeon::
	trainerbattle_no_intro TRAINER_GREEN_SAFFRON_ESPEON, SaffronCity_Text_GreenDefeat
	goto SaffronCity_EventScript_GreenWon
SaffronCity_EventScript_GreenRaichu::
	trainerbattle_no_intro TRAINER_GREEN_SAFFRON_RAICHU, SaffronCity_Text_GreenDefeat
	goto SaffronCity_EventScript_GreenWon
SaffronCity_EventScript_GreenWon::
	msgbox SaffronCity_Text_GreenPost
	closemessage
	setflag FLAG_TEMP_11
	removeobject LOCALID_SAFFRON_GREEN
	fadedefaultbgm
	release
	end

SaffronCity_Text_GreenDefeat::
	.string "There it is.$"
SaffronCity_Text_GreenPost::
	.string "I'm not filling that sixth slot\n"
	.string "until I'm sure.$"
