PewterCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PewterCity_Gym_OnResume
	map_script MAP_SCRIPT_ON_LOAD, PewterCity_Gym_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PewterCity_Gym_OnFrame
	.byte 0

PewterCity_Gym_OnResume::
	setstepcallback STEP_CB_GYM1_ICE
	end

PewterCity_Gym_OnLoad::
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_OnLoad_PostVictory
	end

PewterCity_Gym_OnLoad_PostVictory::
	setobjectxy 1, 10, 4
	end

PewterCity_Gym_OnFrame::
	map_script_2 VAR_TEMP_1, 1, PewterCity_Gym_EventScript_FallReset
	.2byte 0

PewterCity_Gym_EventScript_FallReset::
	lockall
	setvar VAR_TEMP_1, 0
	playse SE_FALL
	delay 30
	warp MAP_PEWTER_CITY_GYM, 9, 21
	waitstate
	releaseall
	end

PewterCity_Gym_EventScript_ReturnWarp::
	lockall
	warp MAP_PEWTER_CITY_GYM, 9, 21
	waitstate
	releaseall
	end

PewterCity_Gym_EventScript_Cliff::
	trainerbattle_single TRAINER_HIKER_CLIFF_PEWTER, PewterCity_Gym_Text_CliffPre, PewterCity_Gym_Text_CliffDefeat
	msgbox PewterCity_Gym_Text_CliffAfter, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_Miles::
	trainerbattle_single TRAINER_HIKER_MILES_PEWTER, PewterCity_Gym_Text_MilesPre, PewterCity_Gym_Text_MilesDefeat
	msgbox PewterCity_Gym_Text_MilesAfter, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_Boreal::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, PewterCity_Gym_EventScript_BorealFirst
	goto_if_unset FLAG_GYM1_TM55_RECEIVED, PewterCity_Gym_EventScript_GiveTM55
	goto_if_set FLAG_SYS_GAME_CLEAR, PewterCity_Gym_EventScript_BorealRematch
	msgbox PewterCity_Gym_Text_BorealRepeat
	release
	end

PewterCity_Gym_EventScript_BorealFirst::
	trainerbattle_single TRAINER_LEADER_BOREAL_PEWTER, PewterCity_Gym_Text_BorealPre, PewterCity_Gym_Text_BorealDefeat, PewterCity_Gym_EventScript_DefeatedBoreal, NO_MUSIC
	end

PewterCity_Gym_EventScript_DefeatedBoreal::
	msgbox PewterCity_Gym_Text_BorealBadge
	setflag FLAG_BADGE01_GET
	setflag FLAG_DEFEATED_BROCK
	setvar VAR_MAP_SCENE_PEWTER_CITY, 1
	set_gym_trainers 1
	setobjectxyperm 1, 10, 4
	setobjectxy 1, 10, 4
	msgbox PewterCity_Gym_Text_BorealBadgeFollowup
	goto PewterCity_Gym_EventScript_GiveTM55
	end

PewterCity_Gym_EventScript_GiveTM55::
	checkitemspace ITEM_TM55_ICY_WIND
	goto_if_eq VAR_RESULT, FALSE, PewterCity_Gym_EventScript_NoRoomForTM55
	giveitem_msg PewterCity_Gym_Text_ReceivedTM55, ITEM_TM55_ICY_WIND
	setflag FLAG_GYM1_TM55_RECEIVED
	msgbox PewterCity_Gym_Text_BorealTM55
	msgbox PewterCity_Gym_Text_BorealFinal
	release
	end

PewterCity_Gym_EventScript_NoRoomForTM55::
	msgbox PewterCity_Gym_Text_NoRoomForTM55
	release
	end

PewterCity_Gym_EventScript_BorealRematch::
	cleartrainerflag TRAINER_LEADER_BOREAL_REMATCH_PEWTER
	trainerbattle_single TRAINER_LEADER_BOREAL_REMATCH_PEWTER, PewterCity_Gym_Text_BorealRematchPre, PewterCity_Gym_Text_BorealRematchDefeat, PewterCity_Gym_EventScript_BorealRematchWon, NO_MUSIC
	end

PewterCity_Gym_EventScript_BorealRematchWon::
	msgbox PewterCity_Gym_Text_BorealRematchAfter
	release
	end

PewterCity_Gym_EventScript_Satoshi::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_EventScript_SatoshiAfterBoreal
	goto_if_set FLAG_SATOSHI_PEWTER_PRACTICE_WON, PewterCity_Gym_EventScript_SatoshiBeforeBoreal
	msgbox PewterCity_Gym_Text_SatoshiFirst, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_Gym_EventScript_SatoshiPractice
	msgbox PewterCity_Gym_Text_SatoshiDecline
	release
	end

PewterCity_Gym_EventScript_SatoshiPractice::
	trainerbattle_single TRAINER_SATOSHI_PEWTER_PRACTICE, PewterCity_Gym_Text_SatoshiYes, PewterCity_Gym_Text_SatoshiLose, PewterCity_Gym_EventScript_SatoshiPracticeWon, NO_MUSIC
	end

PewterCity_Gym_EventScript_SatoshiPracticeWon::
	setflag FLAG_SATOSHI_PEWTER_PRACTICE_WON
	msgbox PewterCity_Gym_Text_SatoshiWin
	release
	end

PewterCity_Gym_EventScript_SatoshiBeforeBoreal::
	msgbox PewterCity_Gym_Text_SatoshiBeforeBoreal
	release
	end

PewterCity_Gym_EventScript_SatoshiAfterBoreal::
	goto_if_set FLAG_SATOSHI_PEWTER_PRACTICE_WON, PewterCity_Gym_EventScript_SatoshiAfterComplete
	msgbox PewterCity_Gym_Text_SatoshiAfterSkipped
	release
	end

PewterCity_Gym_EventScript_SatoshiAfterComplete::
	msgbox PewterCity_Gym_Text_SatoshiAfterComplete
	release
	end

PewterCity_Gym_EventScript_MainSign::
	msgbox PewterCity_Gym_Text_MainSign
	end

PewterCity_Gym_EventScript_ThinIceSign::
	msgbox PewterCity_Gym_Text_ThinIceSign
	end
