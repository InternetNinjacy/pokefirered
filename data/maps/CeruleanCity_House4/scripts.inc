.set REWARD_TYPE, VAR_0x8004
.set REWARD_ITEM, VAR_0x8008

CeruleanCity_House4_MapScripts::
	.byte 0

CeruleanCity_House4_EventScript_WaterworksWorker::
	lock
	faceplayer
	goto_if_set FLAG_SQ_CERULEAN_COMPLETE, CeruleanCity_House4_EventScript_WaterworksComplete
	goto_if_eq VAR_SQ_CERULEAN_STATE, 0, CeruleanCity_House4_EventScript_WaterworksOffer
	goto_if_eq VAR_SQ_CERULEAN_STATE, 1, CeruleanCity_House4_EventScript_WaterworksReturn
	goto_if_eq VAR_SQ_CERULEAN_STATE, 2, CeruleanCity_House4_EventScript_WaterworksReward
	goto CeruleanCity_House4_EventScript_WaterworksComplete
	end

CeruleanCity_House4_EventScript_WaterworksOffer::
	msgbox CeruleanCity_House4_Text_WaterworksOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CeruleanCity_House4_EventScript_WaterworksDecline
	setvar VAR_SQ_CERULEAN_STATE, 1
	setvar VAR_SQ_CERULEAN_VALVES, 5
	msgbox CeruleanCity_House4_Text_WaterworksStart
	warp MAP_ROUTE6_UNUSED_HOUSE, 6, 7
	waitstate
	release
	end

CeruleanCity_House4_EventScript_WaterworksDecline::
	msgbox CeruleanCity_House4_Text_WaterworksDecline
	release
	end

CeruleanCity_House4_EventScript_WaterworksReturn::
	msgbox CeruleanCity_House4_Text_WaterworksReturn
	warp MAP_ROUTE6_UNUSED_HOUSE, 6, 7
	waitstate
	release
	end

CeruleanCity_House4_EventScript_WaterworksReward::
	msgbox CeruleanCity_House4_Text_WaterworksReward
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_WaterworksNoRoom
	setvar VAR_SQ_CERULEAN_STATE, 3
	setflag FLAG_SQ_CERULEAN_COMPLETE
	msgbox CeruleanCity_House4_Text_WaterworksRewardSuccess
	release
	end

CeruleanCity_House4_EventScript_WaterworksNoRoom::
	msgbox CeruleanCity_House4_Text_WaterworksNoRoom
	release
	end

CeruleanCity_House4_EventScript_WaterworksComplete::
	msgbox CeruleanCity_House4_Text_WaterworksComplete
	release
	end

CeruleanCity_House4_EventScript_WonderNewsBerryMan::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	specialvar REWARD_TYPE, WonderNews_GetRewardInfo
	copyvar REWARD_ITEM, VAR_RESULT
	goto_if_eq REWARD_TYPE, NEWS_REWARD_NONE,       CeruleanCity_House4_EventScript_NoNews
	goto_if_eq REWARD_TYPE, NEWS_REWARD_RECV_SMALL, CeruleanCity_House4_EventScript_Reward_RecvSmall
	goto_if_eq REWARD_TYPE, NEWS_REWARD_RECV_BIG,   CeruleanCity_House4_EventScript_Reward_RecvBig
	goto_if_eq REWARD_TYPE, NEWS_REWARD_WAITING,    CeruleanCity_House4_EventScript_Waiting
	goto_if_eq REWARD_TYPE, NEWS_REWARD_SENT_SMALL, CeruleanCity_House4_EventScript_Reward_SentSmall
	goto_if_eq REWARD_TYPE, NEWS_REWARD_SENT_BIG,   CeruleanCity_House4_EventScript_Reward_SentBig
	goto_if_eq REWARD_TYPE, NEWS_REWARD_AT_MAX,     CeruleanCity_House4_EventScript_AtMax
	end

@ Mystery Gift is not enabled, or the player has no saved Wonder News
CeruleanCity_House4_EventScript_NoNews::
	msgbox CeruleanCity_House4_Text_NothingEntertaining
	release
	end

@ Small reward for receiving Wonder News from friend
CeruleanCity_House4_EventScript_Reward_RecvSmall::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_NewNewsInformativeHaveThis
	giveitem REWARD_ITEM
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Big reward for receiving Wonder News from non-friend source
CeruleanCity_House4_EventScript_Reward_RecvBig::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_IncredibleNewsHaveBerries
	giveitem REWARD_ITEM, 4
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Player has not recently sent Wonder News
CeruleanCity_House4_EventScript_Waiting::
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CeruleanCity_House4_Text_WishCouldShareNewsWithOthers
	release
	end

@ Small reward for sending Wonder News every 1-3 times
CeruleanCity_House4_EventScript_Reward_SentSmall::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_ThanksForSpreadingNewsTakeThis
	giveitem REWARD_ITEM
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Big reward for sending Wonder News every 4th time
CeruleanCity_House4_EventScript_Reward_SentBig::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_MagnificentNewsSpreadHaveBerries
	giveitem REWARD_ITEM, 4
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Player has hit reward limit and must wait to receive new rewards
CeruleanCity_House4_EventScript_AtMax::
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CeruleanCity_House4_Text_EnjoyingMyselfWithAllSortsOfNews
	release
	end

CeruleanCity_House4_EventScript_MovementReactionToNews::
	playse SE_PIN
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_Delay48
	waitmovement 0
	return

CeruleanCity_House4_EventScript_NoRoomForBerries::
	msgbox CeruleanCity_House4_Text_YourBerryPouchIsFull
	release
	end
