ViridianCity_Mart_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, ViridianCity_Mart_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ViridianCity_Mart_OnFrame
	.byte 0

ViridianCity_Mart_OnLoad::
	goto_if_unset FLAG_SYS_POKEDEX_GET, ViridianCity_Mart_EventScript_HideQuestionnaire
	end

ViridianCity_Mart_EventScript_HideQuestionnaire::
	setmetatile 1, 3, METATILE_Mart_CounterMid_Top, 1
	setmetatile 1, 4, METATILE_Mart_CounterMid_Bottom, 1
	end

ViridianCity_Mart_OnFrame::
	map_script_2 VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_GOODS_RECOVERED, ViridianCity_Mart_EventScript_ReturnRocketGoods
	map_script_2 VAR_MAP_SCENE_VIRIDIAN_CITY_MART, 0, ViridianCity_Mart_EventScript_ParcelScene
	.2byte 0

ViridianCity_Mart_EventScript_ParcelScene::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_VIRIDIAN_MART_CLERK, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox ViridianCity_Mart_Text_YouCameFromPallet
	closemessage
	applymovement LOCALID_VIRIDIAN_MART_CLERK, ViridianCity_Mart_Movement_FacePlayer
	applymovement LOCALID_PLAYER, ViridianCity_Mart_Movement_ApproachCounter
	waitmovement 0
	msgbox ViridianCity_Mart_Text_TakeThisToProfOak
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_MART, 1
	giveitem_msg ViridianCity_Mart_Text_ReceivedOaksParcelFromClerk, ITEM_OAKS_PARCEL, 1, MUS_OBTAIN_KEY_ITEM
	setvar VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 5
	releaseall
	end

ViridianCity_Mart_Movement_ApproachCounter::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

ViridianCity_Mart_Movement_FacePlayer::
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

ViridianCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_MART, 1, ViridianCity_Mart_EventScript_SayHiToOak
	goto_if_questlog EventScript_ReleaseEnd
	goto_if_eq VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_COMPLETE, ViridianCity_Mart_EventScript_RocketThanks
	goto_if_ge VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_GOODS_RECOVERED, ViridianCity_Mart_EventScript_ReturnRocketGoods
ViridianCity_Mart_EventScript_OpenShop::
	message Text_MayIHelpYou
	waitmessage
	pokemart ViridianCity_Mart_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
ViridianCity_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_NONE
	release
	end

ViridianCity_Mart_EventScript_SayHiToOak::
	msgbox ViridianCity_Mart_Text_SayHiToOakForMe
	release
	end

ViridianCity_Mart_EventScript_Woman::
	msgbox ViridianCity_Mart_Text_ShopDoesGoodBusinessInAntidotes, MSGBOX_NPC
	end

ViridianCity_Mart_EventScript_Youngster::
	msgbox ViridianCity_Mart_Text_GotToBuySomePotions, MSGBOX_NPC
	end

ViridianCity_Mart_EventScript_ReturnRocketGoods::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_VIRIDIAN_MART_CLERK, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto_if_ge VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_BALLS_OWED, ViridianCity_Mart_EventScript_RocketRewards
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox ViridianCity_Mart_Text_ReturnRocketGoods
@ The recovered-goods event state is consumed automatically; no keep choice.
	setvar VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_BALLS_OWED
ViridianCity_Mart_EventScript_RocketRewards::
	goto_if_eq VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_DOSSIER_OWED, ViridianCity_Mart_EventScript_RocketDossier
	checkitemspace ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Mart_EventScript_RocketBagFull
	giveitem ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Mart_EventScript_RocketBagFull
	setvar VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_DOSSIER_OWED
ViridianCity_Mart_EventScript_RocketDossier::
@ NG+ carries Key Items but resets run evidence and operation state.
	checkitem ITEM_ROCKET_DOSSIER, 1
	goto_if_eq VAR_RESULT, TRUE, ViridianCity_Mart_EventScript_RocketComplete
	checkitemspace ITEM_ROCKET_DOSSIER, 1
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Mart_EventScript_RocketBagFull
	msgbox ViridianCity_Mart_Text_LoosePaper
	giveitem ITEM_ROCKET_DOSSIER, 1
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Mart_EventScript_RocketBagFull
ViridianCity_Mart_EventScript_RocketComplete::
	setvar VAR_0x8004, ROCKET_EVIDENCE_DELIVERY_01
	callnative Script_SamRocketRecordEvidence
	setvar VAR_0x8004, ROCKET_OPERATION_VIRIDIAN_THEFT
	callnative Script_SamRocketCompleteOperation
	setvar VAR_SAM_ROCKET_VIRIDIAN, ROCKET_VIRIDIAN_COMPLETE
	releaseall
	end

ViridianCity_Mart_EventScript_RocketBagFull::
	msgbox Text_BagIsFull
@ Frame hook only runs for GOODS_RECOVERED. Stages 2/3 retry by talking to the
@ clerk, so a full Bag cannot trap the player in a repeated automatic scene.
	releaseall
	end

ViridianCity_Mart_EventScript_RocketThanks::
	msgbox ViridianCity_Mart_Text_RocketThanks
	goto ViridianCity_Mart_EventScript_OpenShop
