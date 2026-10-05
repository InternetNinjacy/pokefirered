Route24_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route24_OnLoad
	.byte 0

Route24_OnLoad::
	call EventScript_ThomasSyncVisibility
	end

Route24_EventScript_Rocket::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 1, Route24_EventScript_RocketPostBattle
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 2, Route24_EventScript_ThomasRetry
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNugget
	call Route24_EventScript_BattleRocket
	release
	end

Route24_EventScript_NoRoomForNugget::
	msgbox Route24_Text_YouDontHaveAnyRoom
	release
	end

Route24_EventScript_RocketPostBattle::
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	release
	end

Route24_EventScript_ThomasRetry::
	call Route24_EventScript_ThomasBattle
	release
	end

Route24_EventScript_Thomas::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 2, Route24_EventScript_ThomasObjectBattle
	msgbox Thomas_Text_NuggetIntro
	release
	end

Route24_EventScript_ThomasObjectBattle::
	call Route24_EventScript_ThomasBattle
	release
	end

Route24_EventScript_RocketTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 2, Route24_EventScript_ThomasRetryTrigger
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketApproachPlayer
	call_if_eq VAR_TEMP_1, 1, Route24_EventScript_RocketMotionToPlayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNuggetTrigger
	call Route24_EventScript_BattleRocket
	releaseall
	end

Route24_EventScript_ThomasRetryTrigger::
	call Route24_EventScript_ThomasBattle
	releaseall
	end

Route24_EventScript_BattleRocket::
	giveitem_msg Route24_Text_ReceivedNuggetFromMysteryTrainer, ITEM_NUGGET
	setvar VAR_MAP_SCENE_ROUTE24, 2
	message Route24_Text_JoinTeamRocket
	waitmessage
	playbgm MUS_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	call Route24_EventScript_ThomasBattle
	return

Route24_EventScript_ThomasBattle::
	call Thomas_EventScript_NuggetPreBattle
	setvar VAR_LAST_TALKED, LOCALID_ROUTE24_THOMAS
	trainerbattle_no_intro TRAINER_THOMAS_NUGGET_BRIDGE, Thomas_Text_NuggetDefeat
	call EventScript_ThomasSetRecruited
	removeobject LOCALID_ROUTE24_THOMAS
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	setvar VAR_MAP_SCENE_ROUTE24, 1
	return

Route24_EventScript_RocketApproachPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketApproachPlayer
	waitmovement 0
	return

Route24_EventScript_RocketMotionToPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route24_EventScript_NoRoomForNuggetTrigger::
	msgbox Route24_Text_YouDontHaveAnyRoom
	closemessage
	applymovement LOCALID_PLAYER, Route24_Movement_WalkDown
	waitmovement 0
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketWalkBackToPos
	release
	end

Route24_EventScript_RocketWalkBackToPos::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketWalkBackToPos
	waitmovement 0
	return

Route24_Movement_RocketApproachPlayer::
	walk_left
	step_end

Route24_Movement_RocketWalkBackToPos::
	walk_right
	walk_in_place_faster_left
	step_end

Route24_Movement_WalkDown::
	walk_down
	step_end

Route24_EventScript_StaticAbra::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	checkitemspace ITEM_TWISTED_SPOON
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_StaticAbraNoRoom
	setwildbattle SPECIES_ABRA, 10, ITEM_TWISTED_SPOON
	setvar VAR_0x8004, MOVE_CONFUSION
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_ABRA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route24_EventScript_DefeatedStaticAbra
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route24_EventScript_CompleteStaticAbra
	release
	end

Route24_EventScript_DefeatedStaticAbra::
	giveitem ITEM_TWISTED_SPOON
	goto Route24_EventScript_CompleteStaticAbra
	end

Route24_EventScript_CompleteStaticAbra::
	setflag FLAG_STATIC_ROUTE24_ABRA_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end

Route24_EventScript_StaticAbraNoRoom::
	msgbox Route24_Text_YouDontHaveAnyRoom
	release
	end

EventScript_ThomasSyncVisibility::
	setflag FLAG_HIDE_THOMAS_ROUTE24
	setflag FLAG_HIDE_THOMAS_CELADON
	setflag FLAG_HIDE_THOMAS_LAVENDER
	setflag FLAG_HIDE_THOMAS_SILPH
	setflag FLAG_HIDE_THOMAS_CINNABAR
	setflag FLAG_HIDE_THOMAS_VIRIDIAN
	setflag FLAG_HIDE_THOMAS_MARA
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_UNSEEN, EventScript_ThomasShowRoute24
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_RECRUITED, EventScript_ThomasShowCeladon
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_CELADON_CLEARED, EventScript_ThomasShowLavender
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_LAVENDER_CLEARED, EventScript_ThomasShowSilph
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_SILPH_CLEARED, EventScript_ThomasShowCinnabar
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_CINNABAR_CLEARED, EventScript_ThomasShowViridian
	goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_QUIT_ROCKET, EventScript_ThomasShowMara
	return

EventScript_ThomasShowRoute24::
	clearflag FLAG_HIDE_THOMAS_ROUTE24
	return

EventScript_ThomasShowCeladon::
	clearflag FLAG_HIDE_THOMAS_CELADON
	return

EventScript_ThomasShowLavender::
	clearflag FLAG_HIDE_THOMAS_LAVENDER
	return

EventScript_ThomasShowSilph::
	clearflag FLAG_HIDE_THOMAS_SILPH
	return

EventScript_ThomasShowCinnabar::
	clearflag FLAG_HIDE_THOMAS_CINNABAR
	return

EventScript_ThomasShowViridian::
	clearflag FLAG_HIDE_THOMAS_VIRIDIAN
	return

EventScript_ThomasShowMara::
	clearflag FLAG_HIDE_THOMAS_MARA
	return

EventScript_ThomasSetRecruited::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_RECRUITED
	call EventScript_ThomasSyncVisibility
	return

EventScript_ThomasSetCeladonCleared::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_CELADON_CLEARED
	call EventScript_ThomasSyncVisibility
	return

EventScript_ThomasSetLavenderCleared::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_LAVENDER_CLEARED
	call EventScript_ThomasSyncVisibility
	return

EventScript_ThomasSetSilphCleared::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_SILPH_CLEARED
	call EventScript_ThomasSyncVisibility
	return

EventScript_ThomasSetCinnabarCleared::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_CINNABAR_CLEARED
	call EventScript_ThomasSyncVisibility
	return

EventScript_ThomasSetQuitRocket::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_QUIT_ROCKET
	setflag FLAG_THOMAS_QUIT_ROCKET
	setflag FLAG_THOMAS_MARA_AVAILABLE
	call EventScript_ThomasSyncVisibility
	return

EventScript_ThomasSetEpilogueComplete::
	setvar VAR_THOMAS_ARC_STAGE, THOMAS_ARC_EPILOGUE_COMPLETE
	call EventScript_ThomasSyncVisibility
	return

	.include "data/maps/Route24/thomas_event_chain.inc"
