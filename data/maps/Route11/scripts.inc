Route11_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route11_OnTransition
	.byte 0

Route11_OnTransition::
	setvar VAR_TEMP_1, 0
	goto_if_unset FLAG_BADGE03_GET, Route11_EventScript_HideBlue
	call_if_eq VAR_STARTER_MON, 0, Route11_EventScript_CheckBlueWater
	call_if_eq VAR_STARTER_MON, 1, Route11_EventScript_CheckBlueFire
	call_if_eq VAR_STARTER_MON, 2, Route11_EventScript_CheckBlueElectric
	goto_if_eq VAR_TEMP_1, 1, Route11_EventScript_ShowBlue
	goto Route11_EventScript_HideBlue
	end

Route11_EventScript_CheckBlueWater::
	checktrainerflag TRAINER_BLUE_ROUTE11_WATER
	goto_if TRUE, Route11_EventScript_CheckBlueDone
	setvar VAR_TEMP_1, 1
Route11_EventScript_CheckBlueDone::
	return

Route11_EventScript_CheckBlueElectric::
	checktrainerflag TRAINER_BLUE_ROUTE11_ELECTRIC
	goto_if TRUE, Route11_EventScript_CheckBlueDone
	setvar VAR_TEMP_1, 1
	return

Route11_EventScript_CheckBlueFire::
	checktrainerflag TRAINER_BLUE_ROUTE11_FIRE
	goto_if TRUE, Route11_EventScript_CheckBlueDone
	setvar VAR_TEMP_1, 1
	return

Route11_EventScript_ShowBlue::
	showobjectat LOCALID_ROUTE11_BLUE, MAP_ROUTE11
	end

Route11_EventScript_HideBlue::
	hideobjectat LOCALID_ROUTE11_BLUE, MAP_ROUTE11
	end

Route11_EventScript_BlueTrigger::
	lockall
	goto Route11_EventScript_Blue
	end

Route11_EventScript_Blue::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_ENCOUNTER_RIVAL, 0
	faceplayer
	call_if_eq VAR_STARTER_MON, 0, Route11_EventScript_BlueWater
	call_if_eq VAR_STARTER_MON, 1, Route11_EventScript_BlueFire
	call_if_eq VAR_STARTER_MON, 2, Route11_EventScript_BlueElectric
	msgbox Route11_Text_BluePostBattle
	closemessage
	fadedefaultbgm
	hideobjectat LOCALID_ROUTE11_BLUE, MAP_ROUTE11
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route11_EventScript_BlueWater::
	msgbox Route11_Text_BlueIntroWater
	trainerbattle_no_intro TRAINER_BLUE_ROUTE11_WATER, Route11_Text_BlueDefeat
	return

Route11_EventScript_BlueElectric::
	msgbox Route11_Text_BlueIntroElectric
	trainerbattle_no_intro TRAINER_BLUE_ROUTE11_ELECTRIC, Route11_Text_BlueDefeat
	return

Route11_EventScript_BlueFire::
	msgbox Route11_Text_BlueIntroFire
	trainerbattle_no_intro TRAINER_BLUE_ROUTE11_FIRE, Route11_Text_BlueDefeat
	return

Route11_EventScript_DiglettsCaveSign::
	msgbox Route11_Text_DiglettsCave, MSGBOX_SIGN
	end

Route11_EventScript_StaticOnix::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	setwildbattle SPECIES_ONIX, 24, ITEM_SOFT_SAND
	setvar VAR_0x8004, MOVE_ROCK_THROW
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_SANDSTORM
	setvar VAR_0x8005, 1
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_SAND_TOMB
	setvar VAR_0x8005, 2
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_ROCK_TOMB
	setvar VAR_0x8005, 3
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_ONIX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route11_EventScript_CompleteStaticOnix
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route11_EventScript_CompleteStaticOnix
	release
	end

Route11_EventScript_CompleteStaticOnix::
	setflag FLAG_STATIC_ROUTE11_ONIX_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end
