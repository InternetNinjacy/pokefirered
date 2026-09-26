CeruleanCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CeruleanCity_Gym_OnLoad
	.byte 0

CeruleanCity_Gym_OnLoad::
	call CeruleanCity_Gym_EventScript_ApplyGateAState
	end

@ Step 2 / S1 only.
@ Until later puzzle steps are implemented, state 0 means Gate A lit/blocked
@ and state 1 means Gate A extinguished/passable.
CeruleanCity_Gym_EventScript_ApplyGateAState::
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 1, CeruleanCity_Gym_EventScript_GateAOpen
	setmetatile 13, 14, METATILE_CeruleanGym_FlameGate_Lit, 1
	return

CeruleanCity_Gym_EventScript_GateAOpen::
	setmetatile 13, 14, METATILE_CeruleanGym_Floor, 0
	return

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
	end

CeruleanCity_Gym_EventScript_Switch1::
	lockall
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 0, CeruleanCity_Gym_EventScript_Switch1Activate
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch1Activate::
	setvar VAR_SAM_CERULEAN_GYM_FLAME_STATE, 1
	call CeruleanCity_Gym_EventScript_ApplyGateAState
	special DrawWholeMapView
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch2::
CeruleanCity_Gym_EventScript_Switch3::
	end
