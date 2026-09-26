CeruleanCity_Gym_MapScripts::
	.byte 0

@ Step 1: replace the surviving vanilla Cerulean trainer/leader/guide script layer.
@ Flame-state runtime, full Satoshi battle flow, TM39 handoff, and rematch routing
@ are intentionally completed in later Gym 2 implementation steps.

CeruleanCity_Gym_EventScript_Leilani::
	trainerbattle_single TRAINER_LEADER_LEILANI, CeruleanCity_Gym_Text_LeilaniIntro, CeruleanCity_Gym_Text_LeilaniDefeat, CeruleanCity_Gym_EventScript_LeilaniDefeated, NO_MUSIC
	msgbox CeruleanCity_Gym_Text_LeilaniBadge
	release
	end

CeruleanCity_Gym_EventScript_LeilaniDefeated::
	setflag FLAG_DEFEATED_LEILANI
	setflag FLAG_BADGE02_GET
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	msgbox CeruleanCity_Gym_Text_LeilaniBadge
	release
	end

CeruleanCity_Gym_EventScript_Lehua::
	trainerbattle_single TRAINER_FIRE_DANCER_LEHUA, CeruleanCity_Gym_Text_LehuaIntro, CeruleanCity_Gym_Text_LehuaDefeat
	msgbox CeruleanCity_Gym_Text_LehuaPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_LehuaCheckpoint::
	goto_if_defeated TRAINER_FIRE_DANCER_LEHUA, CeruleanCity_Gym_EventScript_LehuaCheckpointDone
	goto CeruleanCity_Gym_EventScript_Lehua
	end

CeruleanCity_Gym_EventScript_LehuaCheckpointDone::
	end

CeruleanCity_Gym_EventScript_Keahi::
	trainerbattle_single TRAINER_FIRE_DANCER_KEAHI, CeruleanCity_Gym_Text_KeahiIntro, CeruleanCity_Gym_Text_KeahiDefeat
	msgbox CeruleanCity_Gym_Text_KeahiPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_KeahiCheckpoint::
	goto_if_defeated TRAINER_FIRE_DANCER_KEAHI, CeruleanCity_Gym_EventScript_KeahiCheckpointDone
	goto CeruleanCity_Gym_EventScript_Keahi
	end

CeruleanCity_Gym_EventScript_KeahiCheckpointDone::
	end

CeruleanCity_Gym_EventScript_Satoshi::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_Gym_EventScript_SatoshiPostBadge
	goto_if_set FLAG_SATOSHI_CERULEAN_PRACTICE_WON, CeruleanCity_Gym_EventScript_SatoshiBeforeLeilani
	msgbox CeruleanCity_Gym_Text_SatoshiRepeatHint
	release
	end

CeruleanCity_Gym_EventScript_SatoshiBeforeLeilani::
	msgbox CeruleanCity_Gym_Text_SatoshiBeforeLeilani
	release
	end

CeruleanCity_Gym_EventScript_SatoshiPostBadge::
	goto_if_set FLAG_SATOSHI_CERULEAN_PRACTICE_WON, CeruleanCity_Gym_EventScript_SatoshiPostBadgePracticed
	msgbox CeruleanCity_Gym_Text_SatoshiPostBadgeSkipped
	release
	end

CeruleanCity_Gym_EventScript_SatoshiPostBadgePracticed::
	msgbox CeruleanCity_Gym_Text_SatoshiPostBadgePracticed
	release
	end

CeruleanCity_Gym_EventScript_GymStatue::
	lockall
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	lockall
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

@ Temporary no-op entry points so the already-authored map can resolve its puzzle
@ event labels before the flame-state implementation steps are completed.
CeruleanCity_Gym_EventScript_Reset::
CeruleanCity_Gym_EventScript_Switch1::
CeruleanCity_Gym_EventScript_Switch2::
CeruleanCity_Gym_EventScript_Switch3::
	end
