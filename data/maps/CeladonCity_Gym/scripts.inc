CeladonCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, CeladonCity_Gym_OnLoad
	.byte 0

CeladonCity_Gym_OnTransition::
	call_if_unset FLAG_GYM4_FIELD_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_ResetFieldSelectors
	call_if_unset FLAG_GYM4_LAB_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_ResetLabSelectors
	end

CeladonCity_Gym_EventScript_ResetFieldSelectors::
	setvar VAR_GYM4_FIELD_SELECTOR_1, 0
	setvar VAR_GYM4_FIELD_SELECTOR_2, 0
	setvar VAR_GYM4_FIELD_SELECTOR_3, 0
	return

CeladonCity_Gym_EventScript_ResetLabSelectors::
	setvar VAR_GYM4_LAB_SELECTOR_1, 0
	setvar VAR_GYM4_LAB_SELECTOR_2, 0
	setvar VAR_GYM4_LAB_SELECTOR_3, 0
	return

CeladonCity_Gym_OnLoad::
	call_if_set FLAG_GYM4_FIELD_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_RestoreFieldSuccess
	call_if_set FLAG_GYM4_LAB_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_RestoreLabSuccess
	end

CeladonCity_Gym_EventScript_RestoreFieldSuccess::
	setmetatile 2, 7, 0x132, 0
	setobjectxy 7, 7, 8
	return

CeladonCity_Gym_EventScript_RestoreLabSuccess::
	setmetatile 30, 7, 0x132, 0
	setobjectxy 8, 25, 8
	return

CeladonCity_Gym_EventScript_Erika::
	famechecker FAMECHECKER_ERIKA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	goto_if_set FLAG_SYS_GAME_CLEAR, CeladonCity_Gym_EventScript_ErikaRematch
	trainerbattle_single TRAINER_LEADER_ERIKA, CeladonCity_Gym_Text_ErikaIntro, CeladonCity_Gym_Text_ErikaDefeat, CeladonCity_Gym_EventScript_DefeatedErika, NO_MUSIC
	goto_if_unset FLAG_GOT_TM26_FROM_ERIKA, CeladonCity_Gym_EventScript_GiveTM26
	famechecker FAMECHECKER_ERIKA, 4
	msgbox CeladonCity_Gym_Text_ErikaFinal
	release
	end

CeladonCity_Gym_EventScript_DefeatedErika::
	famechecker FAMECHECKER_ERIKA, 1
	clearflag FLAG_HIDE_FAME_CHECKER_ERIKA_JOURNALS
	setflag FLAG_DEFEATED_ERIKA
	setflag FLAG_BADGE04_GET
	set_gym_trainers 4
	msgbox CeladonCity_Gym_Text_CocoonBadge
	goto CeladonCity_Gym_EventScript_GiveTM26
	end

CeladonCity_Gym_EventScript_GiveTM26::
	msgbox CeladonCity_Gym_Text_TM26Handoff
	checkitemspace ITEM_TM26_SIGNAL_BEAM
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Gym_EventScript_NoRoomForTM26
	giveitem_msg CeladonCity_Gym_Text_ReceivedTM26FromErika, ITEM_TM26_SIGNAL_BEAM
	setflag FLAG_GOT_TM26_FROM_ERIKA
	msgbox CeladonCity_Gym_Text_ErikaFinal
	release
	end

CeladonCity_Gym_EventScript_NoRoomForTM26::
	msgbox CeladonCity_Gym_Text_ShouldMakeRoomForThis
	release
	end

CeladonCity_Gym_EventScript_ErikaRematch::
	cleartrainerflag TRAINER_LEADER_ERIKA_REMATCH
	trainerbattle_single TRAINER_LEADER_ERIKA_REMATCH, CeladonCity_Gym_Text_ErikaIntro, CeladonCity_Gym_Text_ErikaDefeat, CeladonCity_Gym_EventScript_ErikaRematchWon, NO_MUSIC
	end

CeladonCity_Gym_EventScript_ErikaRematchWon::
	msgbox CeladonCity_Gym_Text_ErikaFinal
	release
	end


CeladonCity_Gym_EventScript_Owen::
	trainerbattle_single TRAINER_BUG_CATCHER_OWEN_CELADON, CeladonCity_Gym_Text_OwenIntro, CeladonCity_Gym_Text_OwenDefeat
	msgbox CeladonCity_Gym_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Maya::
	trainerbattle_single TRAINER_BUG_CATCHER_MAYA_CELADON, CeladonCity_Gym_Text_MayaIntro, CeladonCity_Gym_Text_MayaDefeat
	msgbox CeladonCity_Gym_Text_MayaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Elias::
	trainerbattle_single TRAINER_SCIENTIST_ELIAS_CELADON, CeladonCity_Gym_Text_EliasIntro, CeladonCity_Gym_Text_EliasDefeat
	msgbox CeladonCity_Gym_Text_EliasPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Nora::
	trainerbattle_single TRAINER_SCIENTIST_NORA_CELADON, CeladonCity_Gym_Text_NoraIntro, CeladonCity_Gym_Text_NoraDefeat
	msgbox CeladonCity_Gym_Text_NoraPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Satoshi::
	lock
	faceplayer
	satoshi_route_by_state CeladonCity_Gym_EventScript_SatoshiPostgameOffer, FLAG_BADGE04_GET, CeladonCity_Gym_EventScript_SatoshiPostBadge, FLAG_SATOSHI_CELADON_PRACTICE_WON, CeladonCity_Gym_EventScript_SatoshiRepeatHint
	checktrainerflag TRAINER_SATOSHI_CELADON_PRACTICE
	goto_if_eq VAR_RESULT, TRUE, CeladonCity_Gym_EventScript_SatoshiRetryOffer
	msgbox CeladonCity_Gym_Text_SatoshiFirst, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CeladonCity_Gym_EventScript_SatoshiAccept
	msgbox CeladonCity_Gym_Text_SatoshiDecline
	release
	end

CeladonCity_Gym_EventScript_SatoshiAccept::
	msgbox CeladonCity_Gym_Text_SatoshiYes
	cleartrainerflag TRAINER_SATOSHI_CELADON_PRACTICE
	trainerbattle_earlyrival TRAINER_SATOSHI_CELADON_PRACTICE, RIVAL_BATTLE_HEAL_AFTER, CeladonCity_Gym_Text_SatoshiBattleDefeatEmpty, CeladonCity_Gym_Text_SatoshiLoss
	goto_if_eq VAR_RESULT, TRUE, CeladonCity_Gym_EventScript_SatoshiRetryOffer
	setflag FLAG_SATOSHI_CELADON_PRACTICE_WON
	msgbox CeladonCity_Gym_Text_SatoshiWin
	release
	end

CeladonCity_Gym_EventScript_SatoshiRetryOffer::
	msgbox CeladonCity_Gym_Text_SatoshiRetry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CeladonCity_Gym_EventScript_SatoshiRetryYes
	msgbox CeladonCity_Gym_Text_SatoshiRetryNo
	release
	end

CeladonCity_Gym_EventScript_SatoshiRetryYes::
	msgbox CeladonCity_Gym_Text_SatoshiRetryYes
	cleartrainerflag TRAINER_SATOSHI_CELADON_PRACTICE
	trainerbattle_earlyrival TRAINER_SATOSHI_CELADON_PRACTICE, RIVAL_BATTLE_HEAL_AFTER, CeladonCity_Gym_Text_SatoshiBattleDefeatEmpty, CeladonCity_Gym_Text_SatoshiLoss
	goto_if_eq VAR_RESULT, TRUE, CeladonCity_Gym_EventScript_SatoshiRetryOffer
	setflag FLAG_SATOSHI_CELADON_PRACTICE_WON
	msgbox CeladonCity_Gym_Text_SatoshiWin
	release
	end

CeladonCity_Gym_EventScript_SatoshiRepeatHint::
	msgbox CeladonCity_Gym_Text_SatoshiRepeat
	release
	end

CeladonCity_Gym_EventScript_SatoshiPostBadge::
	goto_if_set FLAG_SATOSHI_CELADON_PRACTICE_WON, CeladonCity_Gym_EventScript_SatoshiPostBadgePracticed
	msgbox CeladonCity_Gym_Text_SatoshiAfterSkipped
	release
	end

CeladonCity_Gym_EventScript_SatoshiPostBadgePracticed::
	msgbox CeladonCity_Gym_Text_SatoshiAfterPracticed
	release
	end

CeladonCity_Gym_EventScript_SatoshiPostgameOffer::
	msgbox CeladonCity_Gym_Text_SatoshiRematchOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CeladonCity_Gym_EventScript_SatoshiRematch
	msgbox CeladonCity_Gym_Text_SatoshiRematchDecline
	release
	end

CeladonCity_Gym_EventScript_SatoshiRematch::
	cleartrainerflag TRAINER_SATOSHI_CELADON_REMATCH
	trainerbattle_single TRAINER_SATOSHI_CELADON_REMATCH, CeladonCity_Gym_Text_SatoshiRematchStart, CeladonCity_Gym_Text_SatoshiRematchDefeat
	msgbox CeladonCity_Gym_Text_SatoshiRematchAfter
	release
	end



CeladonCity_Gym_EventScript_FieldRouteInfo::
	msgbox CeladonCity_Gym_Text_FieldRouteInfo, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_LabRouteInfo::
	msgbox CeladonCity_Gym_Text_LabRouteInfo, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_FieldMarker::
	msgbox CeladonCity_Gym_Text_FieldMarker, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_LabMarker::
	msgbox CeladonCity_Gym_Text_LabMarker, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_PinsirSubject::
	msgbox CeladonCity_Gym_Text_PinsirSubject, MSGBOX_NPC
	end

CeladonCity_Gym_EventScript_VenomothSubject::
	msgbox CeladonCity_Gym_Text_VenomothSubject, MSGBOX_NPC
	end

CeladonCity_Gym_EventScript_FieldSelector1::
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_1, 0, CeladonCity_Gym_EventScript_FieldSelector1SetSap
	setvar VAR_GYM4_FIELD_SELECTOR_1, 0
	msgbox CeladonCity_Gym_Text_FieldSelector1Flowers, MSGBOX_SIGN
	end
CeladonCity_Gym_EventScript_FieldSelector1SetSap::
	setvar VAR_GYM4_FIELD_SELECTOR_1, 1
	msgbox CeladonCity_Gym_Text_FieldSelector1Sap, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_FieldSelector2::
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_2, 0, CeladonCity_Gym_EventScript_FieldSelector2SetLog
	setvar VAR_GYM4_FIELD_SELECTOR_2, 0
	msgbox CeladonCity_Gym_Text_FieldSelector2Clearing, MSGBOX_SIGN
	end
CeladonCity_Gym_EventScript_FieldSelector2SetLog::
	setvar VAR_GYM4_FIELD_SELECTOR_2, 1
	msgbox CeladonCity_Gym_Text_FieldSelector2Log, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_FieldSelector3::
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_3, 0, CeladonCity_Gym_EventScript_FieldSelector3SetShade
	setvar VAR_GYM4_FIELD_SELECTOR_3, 0
	msgbox CeladonCity_Gym_Text_FieldSelector3Lamp, MSGBOX_SIGN
	end
CeladonCity_Gym_EventScript_FieldSelector3SetShade::
	setvar VAR_GYM4_FIELD_SELECTOR_3, 1
	msgbox CeladonCity_Gym_Text_FieldSelector3Shade, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_LabSelector1::
	goto_if_eq VAR_GYM4_LAB_SELECTOR_1, 0, CeladonCity_Gym_EventScript_LabSelector1SetLamp
	setvar VAR_GYM4_LAB_SELECTOR_1, 0
	msgbox CeladonCity_Gym_Text_LabSelector1Dark, MSGBOX_SIGN
	end
CeladonCity_Gym_EventScript_LabSelector1SetLamp::
	setvar VAR_GYM4_LAB_SELECTOR_1, 1
	msgbox CeladonCity_Gym_Text_LabSelector1Lamp, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_LabSelector2::
	goto_if_eq VAR_GYM4_LAB_SELECTOR_2, 0, CeladonCity_Gym_EventScript_LabSelector2SetFlowers
	setvar VAR_GYM4_LAB_SELECTOR_2, 0
	msgbox CeladonCity_Gym_Text_LabSelector2Soil, MSGBOX_SIGN
	end
CeladonCity_Gym_EventScript_LabSelector2SetFlowers::
	setvar VAR_GYM4_LAB_SELECTOR_2, 1
	msgbox CeladonCity_Gym_Text_LabSelector2Flowers, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_LabSelector3::
	goto_if_eq VAR_GYM4_LAB_SELECTOR_3, 0, CeladonCity_Gym_EventScript_LabSelector3SetVent
	setvar VAR_GYM4_LAB_SELECTOR_3, 0
	msgbox CeladonCity_Gym_Text_LabSelector3Sealed, MSGBOX_SIGN
	end
CeladonCity_Gym_EventScript_LabSelector3SetVent::
	setvar VAR_GYM4_LAB_SELECTOR_3, 1
	msgbox CeladonCity_Gym_Text_LabSelector3Vent, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_FieldObserve::
	lockall
	goto_if_set FLAG_GYM4_FIELD_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_FieldAlreadyComplete
	goto_if_ne VAR_GYM4_FIELD_SELECTOR_1, 1, CeladonCity_Gym_EventScript_FieldFail1
	goto_if_ne VAR_GYM4_FIELD_SELECTOR_2, 1, CeladonCity_Gym_EventScript_FieldFail2
	goto_if_ne VAR_GYM4_FIELD_SELECTOR_3, 1, CeladonCity_Gym_EventScript_FieldFail3
	call CeladonCity_Gym_EventScript_OpenFieldSpine
	applymovement 7, CeladonCity_Gym_Movement_SubjectSuccess
	waitmovement 7
	call CeladonCity_Gym_EventScript_CloseFieldSpine
	setflag FLAG_GYM4_FIELD_PUZZLE_COMPLETE
	setmetatile 2, 7, 0x132, 0
	special DrawWholeMapView
	msgbox CeladonCity_Gym_Text_FieldSuccess
	msgbox CeladonCity_Gym_Text_FieldAccessOpen
	releaseall
	end

CeladonCity_Gym_EventScript_FieldAlreadyComplete::
	msgbox CeladonCity_Gym_Text_AlreadyComplete
	releaseall
	end

CeladonCity_Gym_EventScript_FieldFail1::
	call CeladonCity_Gym_EventScript_OpenFieldSpine
	applymovement 7, CeladonCity_Gym_Movement_Fail1
	waitmovement 7
	call CeladonCity_Gym_EventScript_CloseFieldSpine
	msgbox CeladonCity_Gym_Text_FieldFailure
	releaseall
	end

CeladonCity_Gym_EventScript_FieldFail2::
	call CeladonCity_Gym_EventScript_OpenFieldSpine
	applymovement 7, CeladonCity_Gym_Movement_Fail2
	waitmovement 7
	call CeladonCity_Gym_EventScript_CloseFieldSpine
	msgbox CeladonCity_Gym_Text_FieldFailure
	releaseall
	end

CeladonCity_Gym_EventScript_FieldFail3::
	call CeladonCity_Gym_EventScript_OpenFieldSpine
	applymovement 7, CeladonCity_Gym_Movement_Fail3
	waitmovement 7
	call CeladonCity_Gym_EventScript_CloseFieldSpine
	msgbox CeladonCity_Gym_Text_FieldFailure
	releaseall
	end

CeladonCity_Gym_EventScript_LabObserve::
	lockall
	goto_if_set FLAG_GYM4_LAB_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_LabAlreadyComplete
	goto_if_ne VAR_GYM4_LAB_SELECTOR_1, 1, CeladonCity_Gym_EventScript_LabFail1
	goto_if_ne VAR_GYM4_LAB_SELECTOR_2, 1, CeladonCity_Gym_EventScript_LabFail2
	goto_if_ne VAR_GYM4_LAB_SELECTOR_3, 1, CeladonCity_Gym_EventScript_LabFail3
	call CeladonCity_Gym_EventScript_OpenLabSpine
	applymovement 8, CeladonCity_Gym_Movement_SubjectSuccess
	waitmovement 8
	call CeladonCity_Gym_EventScript_CloseLabSpine
	setflag FLAG_GYM4_LAB_PUZZLE_COMPLETE
	setmetatile 30, 7, 0x132, 0
	special DrawWholeMapView
	msgbox CeladonCity_Gym_Text_LabSuccess
	msgbox CeladonCity_Gym_Text_LabAccessOpen
	releaseall
	end

CeladonCity_Gym_EventScript_LabAlreadyComplete::
	msgbox CeladonCity_Gym_Text_AlreadyComplete
	releaseall
	end

CeladonCity_Gym_EventScript_LabFail1::
	call CeladonCity_Gym_EventScript_OpenLabSpine
	applymovement 8, CeladonCity_Gym_Movement_Fail1
	waitmovement 8
	call CeladonCity_Gym_EventScript_CloseLabSpine
	msgbox CeladonCity_Gym_Text_LabFailure
	releaseall
	end

CeladonCity_Gym_EventScript_LabFail2::
	call CeladonCity_Gym_EventScript_OpenLabSpine
	applymovement 8, CeladonCity_Gym_Movement_Fail2
	waitmovement 8
	call CeladonCity_Gym_EventScript_CloseLabSpine
	msgbox CeladonCity_Gym_Text_LabFailure
	releaseall
	end

CeladonCity_Gym_EventScript_LabFail3::
	call CeladonCity_Gym_EventScript_OpenLabSpine
	applymovement 8, CeladonCity_Gym_Movement_Fail3
	waitmovement 8
	call CeladonCity_Gym_EventScript_CloseLabSpine
	msgbox CeladonCity_Gym_Text_LabFailure
	releaseall
	end

CeladonCity_Gym_EventScript_OpenFieldSpine::
	setmetatile 7, 9, 0x132, 0
	setmetatile 7, 10, 0x132, 0
	setmetatile 7, 11, 0x132, 0
	setmetatile 7, 12, 0x132, 0
	setmetatile 7, 13, 0x132, 0
	setmetatile 7, 14, 0x132, 0
	setmetatile 7, 15, 0x132, 0
	special DrawWholeMapView
	return

CeladonCity_Gym_EventScript_CloseFieldSpine::
	setmetatile 7, 9, 0x106, 1
	setmetatile 7, 10, 0x106, 1
	setmetatile 7, 11, 0x106, 1
	setmetatile 7, 12, 0x106, 1
	setmetatile 7, 13, 0x106, 1
	setmetatile 7, 14, 0x106, 1
	setmetatile 7, 15, 0x106, 1
	special DrawWholeMapView
	return

CeladonCity_Gym_EventScript_OpenLabSpine::
	setmetatile 25, 9, 0x132, 0
	setmetatile 25, 10, 0x132, 0
	setmetatile 25, 11, 0x132, 0
	setmetatile 25, 12, 0x132, 0
	setmetatile 25, 13, 0x132, 0
	setmetatile 25, 14, 0x132, 0
	setmetatile 25, 15, 0x132, 0
	special DrawWholeMapView
	return

CeladonCity_Gym_EventScript_CloseLabSpine::
	setmetatile 25, 9, 0x106, 1
	setmetatile 25, 10, 0x106, 1
	setmetatile 25, 11, 0x106, 1
	setmetatile 25, 12, 0x106, 1
	setmetatile 25, 13, 0x106, 1
	setmetatile 25, 14, 0x106, 1
	setmetatile 25, 15, 0x106, 1
	special DrawWholeMapView
	return

CeladonCity_Gym_Movement_SubjectSuccess::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeladonCity_Gym_Movement_Fail1::
	walk_up
	walk_down
	step_end

CeladonCity_Gym_Movement_Fail2::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeladonCity_Gym_Movement_Fail3::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeladonCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, CeladonCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeladonCity_Gym_Text_GymStatue
	releaseall
	end

CeladonCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeladonCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end
