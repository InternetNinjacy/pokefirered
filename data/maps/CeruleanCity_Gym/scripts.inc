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

@ Cerulean Gym runtime: flame-state puzzle, trainer/Leader flow, TM39,
@ Satoshi state routing, and postgame rematches.

CeruleanCity_Gym_EventScript_Leilani::
	goto_if_set FLAG_SYS_GAME_CLEAR, CeruleanCity_Gym_EventScript_LeilaniPostgame
	trainerbattle_single TRAINER_LEADER_LEILANI, CeruleanCity_Gym_Text_LeilaniIntro, CeruleanCity_Gym_Text_LeilaniDefeat, CeruleanCity_Gym_EventScript_LeilaniDefeated, NO_MUSIC
	goto_if_unset FLAG_GOT_TM39_FROM_LEILANI, CeruleanCity_Gym_EventScript_GiveTM39
	msgbox CeruleanCity_Gym_Text_LeilaniBadge
	release
	end

CeruleanCity_Gym_EventScript_LeilaniDefeated::
	setflag FLAG_DEFEATED_LEILANI
	setflag FLAG_BADGE02_GET
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	set_gym_trainers 2
	setvar VAR_SAM_CERULEAN_GYM_FLAME_STATE, 3
	call CeruleanCity_Gym_EventScript_ApplyFlameState
	special DrawWholeMapView
	msgbox CeruleanCity_Gym_Text_LeilaniBadge
	goto CeruleanCity_Gym_EventScript_GiveTM39
	end

CeruleanCity_Gym_EventScript_LeilaniPostgame::
	goto_if_unset FLAG_GOT_TM39_FROM_LEILANI, CeruleanCity_Gym_EventScript_GiveTM39
	@ Dedicated rematch dialogue is not yet locked; reuse approved battle lines
	@ rather than inventing new player-facing canon.
	cleartrainerflag TRAINER_LEADER_LEILANI_REMATCH
	trainerbattle_single TRAINER_LEADER_LEILANI_REMATCH, CeruleanCity_Gym_Text_LeilaniIntro, CeruleanCity_Gym_Text_LeilaniDefeat, CeruleanCity_Gym_EventScript_LeilaniRematchDefeated, NO_MUSIC
	release
	end

CeruleanCity_Gym_EventScript_LeilaniRematchDefeated::
	release
	end

CeruleanCity_Gym_EventScript_GiveTM39::
	msgbox CeruleanCity_Gym_Text_LeilaniTM39
	checkitemspace ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_NoRoomForTM39
	giveitem ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_NoRoomForTM39
	setflag FLAG_GOT_TM39_FROM_LEILANI
	release
	end

CeruleanCity_Gym_EventScript_NoRoomForTM39::
	msgbox CeruleanCity_Gym_Text_LeilaniNoRoomForTM39
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
	goto_if_set FLAG_SYS_GAME_CLEAR, CeruleanCity_Gym_EventScript_SatoshiPostgameRematch
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_Gym_EventScript_SatoshiPostBadge
	goto_if_set FLAG_SATOSHI_CERULEAN_PRACTICE_WON, CeruleanCity_Gym_EventScript_SatoshiRepeatHint
	checktrainerflag TRAINER_SATOSHI_CERULEAN_PRACTICE
	goto_if_eq VAR_RESULT, TRUE, CeruleanCity_Gym_EventScript_SatoshiRetryOffer
	msgbox CeruleanCity_Gym_Text_SatoshiFirstApproach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CeruleanCity_Gym_EventScript_SatoshiAccept
	goto CeruleanCity_Gym_EventScript_SatoshiDecline
	end

CeruleanCity_Gym_EventScript_SatoshiAccept::
	msgbox CeruleanCity_Gym_Text_SatoshiAccept
	cleartrainerflag TRAINER_SATOSHI_CERULEAN_PRACTICE
	trainerbattle_earlyrival TRAINER_SATOSHI_CERULEAN_PRACTICE, RIVAL_BATTLE_HEAL_AFTER, CeruleanCity_Gym_Text_SatoshiWin, CeruleanCity_Gym_Text_SatoshiLoss
	goto_if_eq VAR_RESULT, TRUE, CeruleanCity_Gym_EventScript_SatoshiRetryOffer
	setflag FLAG_SATOSHI_CERULEAN_PRACTICE_WON
	msgbox CeruleanCity_Gym_Text_SatoshiBeforeLeilani
	release
	end

CeruleanCity_Gym_EventScript_SatoshiRetryOffer::
	msgbox CeruleanCity_Gym_Text_SatoshiRetryOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CeruleanCity_Gym_EventScript_SatoshiRetryYes
	goto CeruleanCity_Gym_EventScript_SatoshiRetryNo
	end

CeruleanCity_Gym_EventScript_SatoshiRetryYes::
	msgbox CeruleanCity_Gym_Text_SatoshiRetryYes
	cleartrainerflag TRAINER_SATOSHI_CERULEAN_PRACTICE
	trainerbattle_earlyrival TRAINER_SATOSHI_CERULEAN_PRACTICE, RIVAL_BATTLE_HEAL_AFTER, CeruleanCity_Gym_Text_SatoshiWin, CeruleanCity_Gym_Text_SatoshiLoss
	goto_if_eq VAR_RESULT, TRUE, CeruleanCity_Gym_EventScript_SatoshiRetryOffer
	setflag FLAG_SATOSHI_CERULEAN_PRACTICE_WON
	msgbox CeruleanCity_Gym_Text_SatoshiBeforeLeilani
	release
	end

CeruleanCity_Gym_EventScript_SatoshiRetryNo::
	msgbox CeruleanCity_Gym_Text_SatoshiRetryNo
	release
	end

CeruleanCity_Gym_EventScript_SatoshiDecline::
	msgbox CeruleanCity_Gym_Text_SatoshiDecline
	release
	end

CeruleanCity_Gym_EventScript_SatoshiRepeatHint::
	msgbox CeruleanCity_Gym_Text_SatoshiRepeatHint
	release
	end

CeruleanCity_Gym_EventScript_SatoshiPostgameRematch::
	@ Hall of Fame routing supersedes the original practice state.
	@ Dedicated rematch dialogue is not yet locked, so reuse approved Cerulean
	@ battle lines rather than inventing new dialogue.
	cleartrainerflag TRAINER_SATOSHI_CERULEAN_REMATCH
	trainerbattle_single TRAINER_SATOSHI_CERULEAN_REMATCH, CeruleanCity_Gym_Text_SatoshiAccept, CeruleanCity_Gym_Text_SatoshiWin
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
