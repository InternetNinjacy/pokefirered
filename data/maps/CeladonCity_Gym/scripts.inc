CeladonCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CeladonCity_Gym_OnLoad
	.byte 0

CeladonCity_Gym_OnLoad::
	call_if_set FLAG_GYM4_FIELD_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_RestoreFieldPuzzle
	call_if_set FLAG_GYM4_LAB_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_RestoreLabPuzzle
	end

CeladonCity_Gym_EventScript_RestoreFieldPuzzle::
	setmetatile 2, 7, 0x132, 0
	setobjectxy 7, 7, 8
	return

CeladonCity_Gym_EventScript_RestoreLabPuzzle::
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

CeladonCity_Gym_EventScript_GymRouteInfo::
	msgbox CeladonCity_Gym_Text_GymRouteInfo, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_FieldRouteSign::
	msgbox CeladonCity_Gym_Text_FieldRouteSign, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_LabRouteSign::
	msgbox CeladonCity_Gym_Text_LabRouteSign, MSGBOX_SIGN
	end

CeladonCity_Gym_EventScript_PinsirSubject::
	msgbox CeladonCity_Gym_Text_PinsirSubject
	end

CeladonCity_Gym_EventScript_VenomothSubject::
	msgbox CeladonCity_Gym_Text_VenomothSubject
	end

CeladonCity_Gym_EventScript_FieldSelector1::
	lockall
	msgbox CeladonCity_Gym_Text_FieldNote1
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_1, 0, CeladonCity_Gym_EventScript_FieldSelector1On
	setvar VAR_GYM4_FIELD_SELECTOR_1, 0
	msgbox CeladonCity_Gym_Text_FieldSelector1Off
	releaseall
	end
CeladonCity_Gym_EventScript_FieldSelector1On::
	setvar VAR_GYM4_FIELD_SELECTOR_1, 1
	msgbox CeladonCity_Gym_Text_FieldSelector1On
	releaseall
	end

CeladonCity_Gym_EventScript_FieldSelector2::
	lockall
	msgbox CeladonCity_Gym_Text_FieldNote2
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_2, 0, CeladonCity_Gym_EventScript_FieldSelector2On
	setvar VAR_GYM4_FIELD_SELECTOR_2, 0
	msgbox CeladonCity_Gym_Text_FieldSelector2Off
	releaseall
	end
CeladonCity_Gym_EventScript_FieldSelector2On::
	setvar VAR_GYM4_FIELD_SELECTOR_2, 1
	msgbox CeladonCity_Gym_Text_FieldSelector2On
	releaseall
	end

CeladonCity_Gym_EventScript_FieldSelector3::
	lockall
	msgbox CeladonCity_Gym_Text_FieldNote3
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_3, 0, CeladonCity_Gym_EventScript_FieldSelector3On
	setvar VAR_GYM4_FIELD_SELECTOR_3, 0
	msgbox CeladonCity_Gym_Text_FieldSelector3Off
	releaseall
	end
CeladonCity_Gym_EventScript_FieldSelector3On::
	setvar VAR_GYM4_FIELD_SELECTOR_3, 1
	msgbox CeladonCity_Gym_Text_FieldSelector3On
	releaseall
	end

CeladonCity_Gym_EventScript_LabSelector1::
	lockall
	msgbox CeladonCity_Gym_Text_LabNote1
	goto_if_eq VAR_GYM4_LAB_SELECTOR_1, 0, CeladonCity_Gym_EventScript_LabSelector1On
	setvar VAR_GYM4_LAB_SELECTOR_1, 0
	msgbox CeladonCity_Gym_Text_LabSelector1Off
	releaseall
	end
CeladonCity_Gym_EventScript_LabSelector1On::
	setvar VAR_GYM4_LAB_SELECTOR_1, 1
	msgbox CeladonCity_Gym_Text_LabSelector1On
	releaseall
	end

CeladonCity_Gym_EventScript_LabSelector2::
	lockall
	msgbox CeladonCity_Gym_Text_LabNote2
	goto_if_eq VAR_GYM4_LAB_SELECTOR_2, 0, CeladonCity_Gym_EventScript_LabSelector2On
	setvar VAR_GYM4_LAB_SELECTOR_2, 0
	msgbox CeladonCity_Gym_Text_LabSelector2Off
	releaseall
	end
CeladonCity_Gym_EventScript_LabSelector2On::
	setvar VAR_GYM4_LAB_SELECTOR_2, 1
	msgbox CeladonCity_Gym_Text_LabSelector2On
	releaseall
	end

CeladonCity_Gym_EventScript_LabSelector3::
	lockall
	msgbox CeladonCity_Gym_Text_LabNote3
	goto_if_eq VAR_GYM4_LAB_SELECTOR_3, 0, CeladonCity_Gym_EventScript_LabSelector3On
	setvar VAR_GYM4_LAB_SELECTOR_3, 0
	msgbox CeladonCity_Gym_Text_LabSelector3Off
	releaseall
	end
CeladonCity_Gym_EventScript_LabSelector3On::
	setvar VAR_GYM4_LAB_SELECTOR_3, 1
	msgbox CeladonCity_Gym_Text_LabSelector3On
	releaseall
	end

CeladonCity_Gym_EventScript_FieldObserve::
	lockall
	goto_if_set FLAG_GYM4_FIELD_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_FieldAlreadyComplete
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_1, 0, CeladonCity_Gym_EventScript_FieldFail1
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_2, 0, CeladonCity_Gym_EventScript_FieldFail2
	goto_if_eq VAR_GYM4_FIELD_SELECTOR_3, 0, CeladonCity_Gym_EventScript_FieldFail3
	playmoncry SPECIES_PINSIR, CRY_MODE_NORMAL
	waitmoncry
	setobjectxy 7, 7, 15
	delay 4
	setobjectxy 7, 7, 14
	delay 4
	setobjectxy 7, 7, 13
	delay 4
	setobjectxy 7, 7, 12
	delay 4
	setobjectxy 7, 7, 11
	delay 4
	setobjectxy 7, 7, 10
	delay 4
	setobjectxy 7, 7, 9
	delay 4
	setobjectxy 7, 7, 8
	delay 4
	setflag FLAG_GYM4_FIELD_PUZZLE_COMPLETE
	setmetatile 2, 7, 0x132, 0
	special DrawWholeMapView
	msgbox CeladonCity_Gym_Text_FieldSuccess
	msgbox CeladonCity_Gym_Text_FieldAccessOpened
	releaseall
	end
CeladonCity_Gym_EventScript_FieldAlreadyComplete::
	msgbox CeladonCity_Gym_Text_ObservationComplete
	releaseall
	end
CeladonCity_Gym_EventScript_FieldFail1::
	setobjectxy 7, 7, 15
	delay 4
	setobjectxy 7, 7, 16
	delay 4
	msgbox CeladonCity_Gym_Text_FieldFailure
	releaseall
	end
CeladonCity_Gym_EventScript_FieldFail2::
	setobjectxy 7, 7, 15
	delay 4
	setobjectxy 7, 7, 14
	delay 4
	setobjectxy 7, 7, 13
	delay 4
	setobjectxy 7, 7, 12
	delay 4
	setobjectxy 7, 7, 13
	delay 4
	setobjectxy 7, 7, 14
	delay 4
	setobjectxy 7, 7, 15
	delay 4
	setobjectxy 7, 7, 16
	delay 4
	msgbox CeladonCity_Gym_Text_FieldFailure
	releaseall
	end
CeladonCity_Gym_EventScript_FieldFail3::
	setobjectxy 7, 7, 15
	delay 4
	setobjectxy 7, 7, 14
	delay 4
	setobjectxy 7, 7, 13
	delay 4
	setobjectxy 7, 7, 12
	delay 4
	setobjectxy 7, 7, 11
	delay 4
	setobjectxy 7, 7, 10
	delay 4
	setobjectxy 7, 7, 9
	delay 4
	setobjectxy 7, 7, 10
	delay 4
	setobjectxy 7, 7, 11
	delay 4
	setobjectxy 7, 7, 12
	delay 4
	setobjectxy 7, 7, 13
	delay 4
	setobjectxy 7, 7, 14
	delay 4
	setobjectxy 7, 7, 15
	delay 4
	setobjectxy 7, 7, 16
	delay 4
	msgbox CeladonCity_Gym_Text_FieldFailure
	releaseall
	end

CeladonCity_Gym_EventScript_LabObserve::
	lockall
	goto_if_set FLAG_GYM4_LAB_PUZZLE_COMPLETE, CeladonCity_Gym_EventScript_LabAlreadyComplete
	goto_if_eq VAR_GYM4_LAB_SELECTOR_1, 0, CeladonCity_Gym_EventScript_LabFail1
	goto_if_eq VAR_GYM4_LAB_SELECTOR_2, 0, CeladonCity_Gym_EventScript_LabFail2
	goto_if_eq VAR_GYM4_LAB_SELECTOR_3, 0, CeladonCity_Gym_EventScript_LabFail3
	playmoncry SPECIES_VENOMOTH, CRY_MODE_NORMAL
	waitmoncry
	setobjectxy 8, 25, 15
	delay 4
	setobjectxy 8, 25, 14
	delay 4
	setobjectxy 8, 25, 13
	delay 4
	setobjectxy 8, 25, 12
	delay 4
	setobjectxy 8, 25, 11
	delay 4
	setobjectxy 8, 25, 10
	delay 4
	setobjectxy 8, 25, 9
	delay 4
	setobjectxy 8, 25, 8
	delay 4
	setflag FLAG_GYM4_LAB_PUZZLE_COMPLETE
	setmetatile 30, 7, 0x132, 0
	special DrawWholeMapView
	msgbox CeladonCity_Gym_Text_LabSuccess
	msgbox CeladonCity_Gym_Text_LabAccessOpened
	releaseall
	end
CeladonCity_Gym_EventScript_LabAlreadyComplete::
	msgbox CeladonCity_Gym_Text_ObservationComplete
	releaseall
	end
CeladonCity_Gym_EventScript_LabFail1::
	setobjectxy 8, 25, 15
	delay 4
	setobjectxy 8, 25, 16
	delay 4
	msgbox CeladonCity_Gym_Text_LabFailure
	releaseall
	end
CeladonCity_Gym_EventScript_LabFail2::
	setobjectxy 8, 25, 15
	delay 4
	setobjectxy 8, 25, 14
	delay 4
	setobjectxy 8, 25, 13
	delay 4
	setobjectxy 8, 25, 12
	delay 4
	setobjectxy 8, 25, 13
	delay 4
	setobjectxy 8, 25, 14
	delay 4
	setobjectxy 8, 25, 15
	delay 4
	setobjectxy 8, 25, 16
	delay 4
	msgbox CeladonCity_Gym_Text_LabFailure
	releaseall
	end
CeladonCity_Gym_EventScript_LabFail3::
	setobjectxy 8, 25, 15
	delay 4
	setobjectxy 8, 25, 14
	delay 4
	setobjectxy 8, 25, 13
	delay 4
	setobjectxy 8, 25, 12
	delay 4
	setobjectxy 8, 25, 11
	delay 4
	setobjectxy 8, 25, 10
	delay 4
	setobjectxy 8, 25, 9
	delay 4
	setobjectxy 8, 25, 10
	delay 4
	setobjectxy 8, 25, 11
	delay 4
	setobjectxy 8, 25, 12
	delay 4
	setobjectxy 8, 25, 13
	delay 4
	setobjectxy 8, 25, 14
	delay 4
	setobjectxy 8, 25, 15
	delay 4
	setobjectxy 8, 25, 16
	delay 4
	msgbox CeladonCity_Gym_Text_LabFailure
	releaseall
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
