PokedexRating_EventScript_RateInPerson::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	goto_if_set FLAG_JOEY_RESUMMON_PENDING, PokedexRating_EventScript_OakJoeyResummon
	goto_if_set FLAG_JOEY_DEFEATED_THIS_CYCLE, PokedexRating_EventScript_OakJoeyReturnedHome
	setvar VAR_0x800C, 0
	call PokedexRating_EventScript_TryOakMilestoneRewards
	goto_if_eq VAR_0x800C, 1, PokedexRating_EventScript_Return
	call_if_set FLAG_OAK_SAW_DEX_COMPLETION, PokedexRating_EventScript_DexCompleteIntro
	call_if_unset FLAG_OAK_SAW_DEX_COMPLETION, PokedexRating_EventScript_NormalIntro
	call PokedexRating_EventScript_Rate
	return

PokedexRating_EventScript_OakJoeyResummon::
	msgbox PokedexRating_Text_OakJoeyResummon
	closemessage
	removeobject LOCALID_OAKS_LAB_JOEY
	setobjectxyperm LOCALID_OAKS_LAB_JOEY, 6, 11
	setobjectmovementtype LOCALID_OAKS_LAB_JOEY, MOVEMENT_TYPE_FACE_UP
	addobject LOCALID_OAKS_LAB_JOEY
	applymovement LOCALID_OAKS_LAB_JOEY, PokedexRating_Movement_JoeyEnter
	waitmovement LOCALID_OAKS_LAB_JOEY
	clearflag FLAG_JOEY_RESUMMON_PENDING
	goto EventScript_ReleaseEnd
	end

PokedexRating_EventScript_OakJoeyReturnedHome::
	msgbox PokedexRating_Text_OakJoeyReturnedHome
	goto EventScript_ReleaseEnd
	end

PokedexRating_EventScript_TryOakMilestoneRewards::
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetPokedexCount
	copyvar VAR_0x800B, VAR_0x8006
	call_if_unset FLAG_OAK_REWARD_30_CLAIMED, PokedexRating_EventScript_TryOakReward30
	call_if_unset FLAG_OAK_REWARD_50_CLAIMED, PokedexRating_EventScript_TryOakReward50
	call_if_unset FLAG_OAK_REWARD_75_CLAIMED, PokedexRating_EventScript_TryOakReward75
	call_if_unset FLAG_OAK_REWARD_100_CLAIMED, PokedexRating_EventScript_TryOakReward100
	call_if_unset FLAG_OAK_REWARD_125_CLAIMED, PokedexRating_EventScript_TryOakReward125
	call_if_unset FLAG_JOEY_UNLOCKED, PokedexRating_EventScript_TryUnlockJoey
	return

PokedexRating_EventScript_TryOakReward30::
	goto_if_lt VAR_0x800B, 30, PokedexRating_EventScript_Return
	checkitemspace ITEM_EXP_SHARE, 1
	goto_if_eq VAR_RESULT, FALSE, PokedexRating_EventScript_Return
	msgbox PokedexRating_Text_OakReward30
	giveitem_msg PokedexRating_Text_ReceivedExpShareFromOak, ITEM_EXP_SHARE, 1
	setflag FLAG_OAK_REWARD_30_CLAIMED
	return

PokedexRating_EventScript_TryOakReward50::
	goto_if_lt VAR_0x800B, 50, PokedexRating_EventScript_Return
	checkitemspace ITEM_TM54_PSYCHIC, 1
	goto_if_eq VAR_RESULT, FALSE, PokedexRating_EventScript_Return
	msgbox PokedexRating_Text_OakReward50
	giveitem_msg PokedexRating_Text_ReceivedTM54FromOak, ITEM_TM54_PSYCHIC, 1
	setflag FLAG_OAK_REWARD_50_CLAIMED
	return

PokedexRating_EventScript_TryOakReward75::
	goto_if_lt VAR_0x800B, 75, PokedexRating_EventScript_Return
	msgbox PokedexRating_Text_OakReward75
	setvar VAR_0x8004, 0
	callnative GiveSamOakResearchGift
	goto_if_eq VAR_RESULT, 2, PokedexRating_EventScript_OakGiftNoRoom
	setflag FLAG_OAK_REWARD_75_CLAIMED
	msgbox PokedexRating_Text_ReceivedChanseyFromOak
	return

PokedexRating_EventScript_TryOakReward100::
	goto_if_lt VAR_0x800B, 100, PokedexRating_EventScript_Return
	checkitemspace ITEM_TM17_EARTHQUAKE, 1
	goto_if_eq VAR_RESULT, FALSE, PokedexRating_EventScript_Return
	msgbox PokedexRating_Text_OakReward100
	giveitem_msg PokedexRating_Text_ReceivedTM17FromOak, ITEM_TM17_EARTHQUAKE, 1
	setflag FLAG_OAK_REWARD_100_CLAIMED
	return

PokedexRating_EventScript_TryOakReward125::
	goto_if_lt VAR_0x800B, 125, PokedexRating_EventScript_Return
	msgbox PokedexRating_Text_OakReward125
	setvar VAR_0x8004, 1
	callnative GiveSamOakResearchGift
	goto_if_eq VAR_RESULT, 2, PokedexRating_EventScript_OakGiftNoRoom
	setflag FLAG_OAK_REWARD_125_CLAIMED
	msgbox PokedexRating_Text_ReceivedDratiniFromOak
	return

PokedexRating_EventScript_TryUnlockJoey::
	goto_if_lt VAR_0x800B, 151, PokedexRating_EventScript_Return
	clearflag FLAG_JOEY_DEFEATED_THIS_CYCLE
	clearflag FLAG_JOEY_RESUMMON_PENDING
	msgbox PokedexRating_Text_OakJoeyUnlockIntro
	msgbox PokedexRating_Text_OakCallJoey
	closemessage
	removeobject LOCALID_OAKS_LAB_JOEY
	setobjectxyperm LOCALID_OAKS_LAB_JOEY, 6, 11
	setobjectmovementtype LOCALID_OAKS_LAB_JOEY, MOVEMENT_TYPE_FACE_UP
	addobject LOCALID_OAKS_LAB_JOEY
	applymovement LOCALID_OAKS_LAB_JOEY, PokedexRating_Movement_JoeyEnter
	waitmovement LOCALID_OAKS_LAB_JOEY
	setflag FLAG_JOEY_UNLOCKED
	setflag FLAG_JOEY_INTRO_SEEN
	msgbox PokedexRating_Text_OakIntroduceJoey
	msgbox PokedexRating_Text_JoeyFirstChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PokedexRating_EventScript_JoeyAcceptBattle
	msgbox PokedexRating_Text_JoeyDecline
	setvar VAR_0x800C, 1
	return

PokedexRating_EventScript_JoeyAcceptBattle::
	trainerbattle_no_intro TRAINER_YOUNGSTER_JOEY, PokedexRating_Text_JoeyPlayerWin
	call PokedexRating_EventScript_JoeyVictoryLifecycle
	goto EventScript_ReleaseEnd
	end

PokedexRating_EventScript_JoeyDirectChallenge::
	lock
	faceplayer
	msgbox PokedexRating_Text_JoeyShortChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PokedexRating_EventScript_JoeyDirectAcceptBattle
	msgbox PokedexRating_Text_JoeyDecline
	release
	end

PokedexRating_EventScript_JoeyDirectAcceptBattle::
	trainerbattle_no_intro TRAINER_YOUNGSTER_JOEY, PokedexRating_Text_JoeyPlayerWin
	call PokedexRating_EventScript_JoeyVictoryLifecycle
	goto EventScript_ReleaseEnd
	end

PokedexRating_EventScript_JoeyVictoryLifecycle::
	msgbox PokedexRating_Text_JoeyLemonadeStand
	msgbox PokedexRating_Text_OakJoeyVictory
	closemessage
	lockall
	applymovement LOCALID_OAKS_LAB_JOEY, PokedexRating_Movement_JoeyExit
	waitmovement LOCALID_OAKS_LAB_JOEY
	removeobject LOCALID_OAKS_LAB_JOEY
	setflag FLAG_JOEY_DEFEATED_THIS_CYCLE
	clearflag FLAG_JOEY_RESUMMON_PENDING
	return

PokedexRating_Movement_JoeyEnter::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

PokedexRating_Movement_JoeyExit::
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PokedexRating_EventScript_OakGiftNoRoom::
	msgbox PokedexRating_Text_OakGiftNoRoom
	return

PokedexRating_EventScript_Return::
	return

PokedexRating_EventScript_DexCompleteIntro::
	msgbox PokedexRating_Text_LoveSeeingYourPokedex
	return

PokedexRating_EventScript_NormalIntro::
	msgbox PokedexRating_Text_HowIsPokedexComingAlong
	return

PokedexRating_EventScript_ShowRatingMsg::
	copyvar VAR_0x8004, VAR_0x8009
	special GetProfOaksRatingMessage
	waitmessage
	call_if_eq VAR_RESULT, FALSE, PokedexRating_EventScript_NormalFanfare
	call_if_eq VAR_RESULT, TRUE, PokedexRating_EventScript_DexCompleteFanfare
	waitfanfare
	waitbuttonpress
	return

PokedexRating_EventScript_NormalFanfare::
	playfanfare MUS_DEX_RATING
	return

PokedexRating_EventScript_DexCompleteFanfare::
	playfanfare MUS_EVOLVED
	return

PokedexRating_EventScript_Rate::
	setvar VAR_0x8004, HELPCONTEXT_PC_MISC
	special BackupHelpContext
	special Script_SetHelpContext
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008 @ Num Kanto Seen
	buffernumberstring STR_VAR_2, VAR_0x8009 @ Num Kanto Caught
	msgbox PokedexRating_Text_SeenXOwnedY
	call_if_unset FLAG_OAKS_RATING_IS_VIA_PC, PokedexRating_EventScript_SetTextColor
	call PokedexRating_EventScript_ShowRatingMsg
	goto_if_eq VAR_0x800A, FALSE, PokedexRating_EventScript_EndRating  @ National Dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008 @ Num National Seen
	buffernumberstring STR_VAR_2, VAR_0x8009 @ Num National Caught
	msgbox PokedexRating_Text_NationalDexSeenXOwnedY
	specialvar VAR_RESULT, HasAllMons
	goto_if_eq VAR_RESULT, FALSE, PokedexRating_EventScript_DexIncomplete
	goto_if_eq VAR_RESULT, TRUE, PokedexRating_EventScript_DexComplete
	end

PokedexRating_EventScript_SetTextColor::
	textcolor NPC_TEXT_COLOR_MALE
	return

PokedexRating_EventScript_DexIncomplete::
	msgbox PokedexRating_Text_LookForwardToFilledNationalDex
	goto PokedexRating_EventScript_EndRating
	end

PokedexRating_EventScript_DexComplete::
	setflag FLAG_OAK_SAW_DEX_COMPLETION
	msgbox PokedexRating_Text_YouveCompletedDex
	goto PokedexRating_EventScript_EndRating
	end

PokedexRating_EventScript_EndRating::
	special RestoreHelpContext
	return