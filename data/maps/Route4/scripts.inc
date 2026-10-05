Route4_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_OnTransition
	.byte 0

Route4_OnTransition::
	setvar VAR_TEMP_1, 0
	call_if_eq VAR_STARTER_MON, 0, Route4_EventScript_CheckWater
	call_if_eq VAR_STARTER_MON, 1, Route4_EventScript_CheckFire
	call_if_eq VAR_STARTER_MON, 2, Route4_EventScript_CheckElectric
	goto_if_eq VAR_TEMP_1, 1, Route4_EventScript_ShowBlueGreen
	goto Route4_EventScript_HideBlueGreen
	end

Route4_EventScript_CheckWater::
	checktrainerflag TRAINER_RIVAL_CERULEAN_SQUIRTLE
	goto_if TRUE, Route4_EventScript_CheckDone
	setvar VAR_TEMP_1, 1
	return

Route4_EventScript_CheckFire::
	checktrainerflag TRAINER_RIVAL_CERULEAN_CHARMANDER
	goto_if TRUE, Route4_EventScript_CheckDone
	setvar VAR_TEMP_1, 1
	return

Route4_EventScript_CheckElectric::
	checktrainerflag TRAINER_RIVAL_CERULEAN_BULBASAUR
	goto_if TRUE, Route4_EventScript_CheckDone
	setvar VAR_TEMP_1, 1
	return

Route4_EventScript_CheckDone::
	return

Route4_EventScript_ShowBlueGreen::
	showobjectat 8, MAP_ROUTE4
	showobjectat 9, MAP_ROUTE4
	end

Route4_EventScript_HideBlueGreen::
	hideobjectat 8, MAP_ROUTE4
	hideobjectat 9, MAP_ROUTE4
	end

Route4_EventScript_BlueGreenTrigger::
	setvar VAR_LAST_TALKED, 8
	goto Route4_EventScript_BlueGreen
	end

Route4_EventScript_BlueGreen::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_ENCOUNTER_RIVAL, 0
	faceplayer
	msgbox Route4_Text_BlueArrival
	call_if_eq VAR_STARTER_MON, 0, Route4_EventScript_BlueWaterIntro
	call_if_eq VAR_STARTER_MON, 1, Route4_EventScript_BlueFireIntro
	call_if_eq VAR_STARTER_MON, 2, Route4_EventScript_BlueElectricIntro
	msgbox Route4_Text_BlueCallsGreen
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenReply
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, Route4_EventScript_NotEnoughMons
	goto Route4_EventScript_StartBattle
	end

Route4_EventScript_BlueWaterIntro::
	msgbox Route4_Text_BlueWaterIntro
	return

Route4_EventScript_BlueFireIntro::
	msgbox Route4_Text_BlueFireIntro
	return

Route4_EventScript_BlueElectricIntro::
	msgbox Route4_Text_BlueElectricIntro
	return

Route4_EventScript_StartBattle::
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenReady
	call_if_eq VAR_STARTER_MON, 0, Route4_EventScript_BattleWater
	call_if_eq VAR_STARTER_MON, 1, Route4_EventScript_BattleFire
	call_if_eq VAR_STARTER_MON, 2, Route4_EventScript_BattleElectric
	goto_if_eq VAR_RESULT, TRUE, Route4_EventScript_LostBattle
	goto Route4_EventScript_WonBattle
	end

Route4_EventScript_BattleWater::
	trainerbattle_earlyrival TRAINER_RIVAL_CERULEAN_SQUIRTLE, RIVAL_BATTLE_HEAL_AFTER, Route4_Text_BlueGreenDefeat, Route4_Text_BlueGreenVictory
	return

Route4_EventScript_BattleFire::
	trainerbattle_earlyrival TRAINER_RIVAL_CERULEAN_CHARMANDER, RIVAL_BATTLE_HEAL_AFTER, Route4_Text_BlueGreenDefeat, Route4_Text_BlueGreenVictory
	return

Route4_EventScript_BattleElectric::
	trainerbattle_earlyrival TRAINER_RIVAL_CERULEAN_BULBASAUR, RIVAL_BATTLE_HEAL_AFTER, Route4_Text_BlueGreenDefeat, Route4_Text_BlueGreenVictory
	return

Route4_EventScript_LostBattle::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueRetry
	goto Route4_EventScript_StartBattle
	end

Route4_EventScript_WonBattle::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BluePostBattle
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenPostBattle
	closemessage
	fadedefaultbgm
	hideobjectat 8, MAP_ROUTE4
	hideobjectat 9, MAP_ROUTE4
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route4_EventScript_NotEnoughMons::
	msgbox Route4_Text_NeedTwoPokemon
	releaseall
	end

Route4_EventScript_Unused::
	end

Route4_EventScript_Woman::
	msgbox Route4_Text_TrippedOverGeodude, MSGBOX_NPC
	end

Route4_EventScript_MtMoonSign::
	msgbox Route4_Text_MtMoonEntrance, MSGBOX_SIGN
	end

Route4_EventScript_RouteSign::
	msgbox Route4_Text_RouteSign, MSGBOX_SIGN
	end
