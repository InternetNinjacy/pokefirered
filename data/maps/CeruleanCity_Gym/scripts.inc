CeruleanCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CeruleanCity_Gym_OnLoad
	.byte 0

CeruleanCity_Gym_OnLoad::
	call CeruleanCity_Gym_EventScript_ApplyFlameState
	end

@ Flame-gate state machine.
@ 0 = A/B/C lit; 1 = A open; 2 = B open with A relit;
@ 3 = A/B/C open permanently.
CeruleanCity_Gym_EventScript_ApplyFlameState::
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 1, CeruleanCity_Gym_EventScript_ApplyFlameState1
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 2, CeruleanCity_Gym_EventScript_ApplyFlameState2
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 3, CeruleanCity_Gym_EventScript_ApplyFlameState3
	goto CeruleanCity_Gym_EventScript_ApplyFlameState0

CeruleanCity_Gym_EventScript_ApplyFlameState0::
	setmetatile 13, 14, METATILE_CeruleanGym_FlameGate_Lit, 1
	setmetatile 13, 11, METATILE_CeruleanGym_FlameGate_Lit, 1
	setmetatile 13,  6, METATILE_CeruleanGym_FlameGate_Lit, 1
	return

CeruleanCity_Gym_EventScript_ApplyFlameState1::
	setmetatile 13, 14, METATILE_CeruleanGym_Floor, 0
	setmetatile 13, 11, METATILE_CeruleanGym_FlameGate_Lit, 1
	setmetatile 13,  6, METATILE_CeruleanGym_FlameGate_Lit, 1
	return

CeruleanCity_Gym_EventScript_ApplyFlameState2::
	setmetatile 13, 14, METATILE_CeruleanGym_FlameGate_Lit, 1
	setmetatile 13, 11, METATILE_CeruleanGym_Floor, 0
	setmetatile 13,  6, METATILE_CeruleanGym_FlameGate_Lit, 1
	return

CeruleanCity_Gym_EventScript_ApplyFlameState3::
	setmetatile 13, 14, METATILE_CeruleanGym_Floor, 0
	setmetatile 13, 11, METATILE_CeruleanGym_Floor, 0
	setmetatile 13,  6, METATILE_CeruleanGym_Floor, 0
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

CeruleanCity_Gym_EventScript_Reset::
	lockall
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 3, CeruleanCity_Gym_EventScript_ResetInert
	setvar VAR_SAM_CERULEAN_GYM_FLAME_STATE, 0
	call CeruleanCity_Gym_EventScript_ApplyFlameState
	special DrawWholeMapView
	releaseall
	end

CeruleanCity_Gym_EventScript_ResetInert::
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch1::
	lockall
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 0, CeruleanCity_Gym_EventScript_Switch1Activate
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch1Activate::
	setvar VAR_SAM_CERULEAN_GYM_FLAME_STATE, 1
	call CeruleanCity_Gym_EventScript_ApplyFlameState
	special DrawWholeMapView
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch2::
	lockall
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 1, CeruleanCity_Gym_EventScript_Switch2Activate
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch2Activate::
	setvar VAR_SAM_CERULEAN_GYM_FLAME_STATE, 2
	call CeruleanCity_Gym_EventScript_ApplyFlameState
	special DrawWholeMapView
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch3::
	lockall
	goto_if_eq VAR_SAM_CERULEAN_GYM_FLAME_STATE, 2, CeruleanCity_Gym_EventScript_Switch3Activate
	releaseall
	end

CeruleanCity_Gym_EventScript_Switch3Activate::
	setvar VAR_SAM_CERULEAN_GYM_FLAME_STATE, 3
	call CeruleanCity_Gym_EventScript_ApplyFlameState
	special DrawWholeMapView
	releaseall
	end
