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
	showobjectat LOCALID_ROUTE4_BLUE, MAP_ROUTE4
	showobjectat LOCALID_ROUTE4_GREEN, MAP_ROUTE4
	end
Route4_EventScript_HideBlueGreen::
	hideobjectat LOCALID_ROUTE4_BLUE, MAP_ROUTE4
	hideobjectat LOCALID_ROUTE4_GREEN, MAP_ROUTE4
	end

Route4_EventScript_BlueGreenTrigger::
	setvar VAR_LAST_TALKED, LOCALID_ROUTE4_BLUE
	goto Route4_EventScript_BlueGreen
	end

Route4_EventScript_BlueGreen::
	lockall
	playbgm MUS_ENCOUNTER_RIVAL, 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BluePlayer
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenPerfect
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueBattlePlayer
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenSoWasI
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueTakeTurns
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenNotDoThat
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueTwoAgainstOne
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenCanHandleIt
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueMoreFun
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenHealFirst
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueNoExcuses
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, Route4_EventScript_NotEnoughMons
	goto Route4_EventScript_StartBattle
	end

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
	call_if_eq VAR_STARTER_MON, 0, Route4_EventScript_ClearWaterBattleFlag
	call_if_eq VAR_STARTER_MON, 1, Route4_EventScript_ClearFireBattleFlag
	call_if_eq VAR_STARTER_MON, 2, Route4_EventScript_ClearElectricBattleFlag
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenLoss
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueRetry
	goto Route4_EventScript_StartBattle
	end
Route4_EventScript_ClearWaterBattleFlag::
	cleartrainerflag TRAINER_RIVAL_CERULEAN_SQUIRTLE
	return
Route4_EventScript_ClearFireBattleFlag::
	cleartrainerflag TRAINER_RIVAL_CERULEAN_CHARMANDER
	return
Route4_EventScript_ClearElectricBattleFlag::
	cleartrainerflag TRAINER_RIVAL_CERULEAN_BULBASAUR
	return

Route4_EventScript_WonBattle::
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenWin
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueRematch
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Route4_Text_GreenPostBattle
	textcolor NPC_TEXT_COLOR_MALE
	msgbox Route4_Text_BlueHey
	closemessage
	fadedefaultbgm
	hideobjectat LOCALID_ROUTE4_BLUE, MAP_ROUTE4
	hideobjectat LOCALID_ROUTE4_GREEN, MAP_ROUTE4
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
