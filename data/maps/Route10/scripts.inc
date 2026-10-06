Route10_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_OnTransition
	.byte 0

Route10_OnTransition::
	setvar VAR_TEMP_1, 0
	call_if_eq VAR_STARTER_MON, 0, Route10_EventScript_CheckBlueWater
	call_if_eq VAR_STARTER_MON, 1, Route10_EventScript_CheckBlueFire
	call_if_eq VAR_STARTER_MON, 2, Route10_EventScript_CheckBlueElectric
	goto_if_eq VAR_TEMP_1, 1, Route10_EventScript_ShowBlue
	goto Route10_EventScript_HideBlue
	end

Route10_EventScript_CheckBlueWater::
	checktrainerflag TRAINER_BLUE_ROUTE11_WATER
	goto_if FALSE, Route10_EventScript_CheckBlueDone
	checktrainerflag TRAINER_BLUE_ROUTE10_WATER
	goto_if TRUE, Route10_EventScript_CheckBlueDone
	setvar VAR_TEMP_1, 1
Route10_EventScript_CheckBlueDone::
	return

Route10_EventScript_CheckBlueElectric::
	checktrainerflag TRAINER_BLUE_ROUTE11_ELECTRIC
	goto_if FALSE, Route10_EventScript_CheckBlueDone
	checktrainerflag TRAINER_BLUE_ROUTE10_ELECTRIC
	goto_if TRUE, Route10_EventScript_CheckBlueDone
	setvar VAR_TEMP_1, 1
	return

Route10_EventScript_CheckBlueFire::
	checktrainerflag TRAINER_BLUE_ROUTE11_FIRE
	goto_if FALSE, Route10_EventScript_CheckBlueDone
	checktrainerflag TRAINER_BLUE_ROUTE10_FIRE
	goto_if TRUE, Route10_EventScript_CheckBlueDone
	setvar VAR_TEMP_1, 1
	return

Route10_EventScript_ShowBlue::
	showobjectat LOCALID_ROUTE10_BLUE, MAP_ROUTE10
	end

Route10_EventScript_HideBlue::
	hideobjectat LOCALID_ROUTE10_BLUE, MAP_ROUTE10
	end

Route10_EventScript_BlueTrigger::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_ROUTE10_BLUE
	goto Route10_EventScript_Blue
	end

Route10_EventScript_Blue::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_ENCOUNTER_RIVAL, 0
	faceplayer
	call_if_eq VAR_STARTER_MON, 0, Route10_EventScript_BlueWater
	call_if_eq VAR_STARTER_MON, 1, Route10_EventScript_BlueFire
	call_if_eq VAR_STARTER_MON, 2, Route10_EventScript_BlueElectric
	msgbox Route10_Text_BluePostBattle
	closemessage
	fadedefaultbgm
	hideobjectat LOCALID_ROUTE10_BLUE, MAP_ROUTE10
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route10_EventScript_BlueWater::
	msgbox Route10_Text_BlueIntroWater
	trainerbattle_no_intro TRAINER_BLUE_ROUTE10_WATER, Route10_Text_BlueDefeat
	return

Route10_EventScript_BlueElectric::
	msgbox Route10_Text_BlueIntroElectric
	trainerbattle_no_intro TRAINER_BLUE_ROUTE10_ELECTRIC, Route10_Text_BlueDefeat
	return

Route10_EventScript_BlueFire::
	msgbox Route10_Text_BlueIntroFire
	trainerbattle_no_intro TRAINER_BLUE_ROUTE10_FIRE, Route10_Text_BlueDefeat
	return

// Batch 5: the sole settled Route 10 approach trainer is a Double Battle.
Route10_EventScript_HeidiBatch5::
	trainerbattle_double TRAINER_PICNICKER_HEIDI, Route10_Text_HeidiIntro, Route10_Text_HeidiDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route10_EventScript_HeidiBatch5Rematch
	msgbox Route10_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
	end

Route10_EventScript_HeidiBatch5Rematch::
	trainerbattle_rematch_double TRAINER_PICNICKER_HEIDI, Route10_Text_HeidiRematchIntro, Route10_Text_HeidiDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route10_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
	end

Route10_EventScript_ItemHM05Flash::
	finditem ITEM_HM05
	end

Route10_EventScript_Unused::
	end

Route10_EventScript_NorthRockTunnelSign::
	msgbox Route10_Text_RockTunnelDetourToLavender, MSGBOX_SIGN
	end

Route10_EventScript_SouthRockTunnelSign::
	msgbox Route10_Text_RockTunnel, MSGBOX_SIGN
	end

Route10_EventScript_PowerPlantSign::
	msgbox Route10_Text_PowerPlant, MSGBOX_SIGN
	end
