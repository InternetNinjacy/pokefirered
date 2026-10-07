CeruleanCity_House2_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeruleanCity_House2_OnFrame
	.byte 0

CeruleanCity_House2_OnFrame::
@ Cerulean Rocket transaction: 1 = goods recovered, 2 = TM08 owed, 3 = complete.
	map_script_2 VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1, CeruleanCity_House2_EventScript_ReturnStolenGoods
	.2byte 0

CeruleanCity_House2_EventScript_ReturnStolenGoods::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_House2_Text_ReturnedStolenGoods
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 2
	call CeruleanCity_House2_EventScript_TryReward
	releaseall
	end

CeruleanCity_House2_EventScript_TryReward::
	checkitemspace ITEM_TM08
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House2_EventScript_BagFull
	giveitem_msg CeruleanCity_House2_Text_ReceivedTM08, ITEM_TM08
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House2_EventScript_BagFull
	setflag FLAG_GOT_TM28_FROM_ROCKET
	setvar VAR_0x8004, ROCKET_OPERATION_CERULEAN
	callnative Script_SamRocketCompleteOperation
	setvar VAR_0x8004, ROCKET_EVIDENCE_DELIVERY_03
	callnative Script_SamRocketRecordEvidence
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 3
	msgbox CeruleanCity_House2_Text_PostClearThanks
	return

CeruleanCity_House2_EventScript_BagFull::
	msgbox Text_BagIsFull
	return

CeruleanCity_House2_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM28_FROM_ROCKET, CeruleanCity_House2_EventScript_HikerComplete
	goto_if_eq VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 2, CeruleanCity_House2_EventScript_HikerRewardOwed
	msgbox CeruleanCity_House2_Text_RocketsStoleProperty
	release
	end

CeruleanCity_House2_EventScript_HikerRewardOwed::
	call CeruleanCity_House2_EventScript_TryReward
	release
	end

CeruleanCity_House2_EventScript_HikerComplete::
	msgbox CeruleanCity_House2_Text_PostClearThanks
	release
	end

CeruleanCity_House2_EventScript_Lass::
	goto_if_set FLAG_GOT_TM28_FROM_ROCKET, CeruleanCity_House2_EventScript_LassComplete
	msgbox CeruleanCity_House2_Text_RocketTookProperty, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_LassComplete::
	msgbox CeruleanCity_House2_Text_LassThanks, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_WallHole::
	msgbox CeruleanCity_House2_Text_TeamRocketLeftWayOut, MSGBOX_SIGN
	end
