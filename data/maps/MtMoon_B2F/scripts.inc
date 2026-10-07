MtMoon_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_B2F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MtMoon_B2F_OnFrame
	.byte 0

MtMoon_B2F_OnFrame::
	map_script_2 VAR_MAP_SCENE_MT_MOON_B2F, 2, MtMoon_B2F_EventScript_ThomasRetry
	.2byte 0

MtMoon_B2F_OnTransition::
	setflag FLAG_HIDE_THOMAS_MT_MOON
	setflag FLAG_HIDE_ROCKET_MT_MOON_ACCOMPLICE
	call_if_eq VAR_MAP_SCENE_MT_MOON_B2F, 2, MtMoon_B2F_EventScript_ShowPendingTheft
	call_if_unset FLAG_GOT_FOSSIL_FROM_MT_MOON, MtMoon_B2F_EventScript_ShowFossils
	end

MtMoon_B2F_EventScript_ShowPendingTheft::
	clearflag FLAG_HIDE_THOMAS_MT_MOON
	clearflag FLAG_HIDE_ROCKET_MT_MOON_ACCOMPLICE
	return

MtMoon_B2F_EventScript_ShowFossils::
	clearflag FLAG_HIDE_DOME_FOSSIL
	clearflag FLAG_HIDE_HELIX_FOSSIL
	return

MtMoon_B2F_EventScript_MiguelTrigger::
	lockall
	applymovement LOCALID_MIGUEL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call MtMoon_B2F_EventScript_BattleMiguel
	releaseall
	end

MtMoon_B2F_EventScript_Miguel::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_MT_MOON_B2F, 3, MtMoon_B2F_EventScript_MiguelAfterTheft
	goto_if_set FLAG_GOT_FOSSIL_FROM_MT_MOON, MtMoon_B2F_EventScript_MiguelFossilPicked
	goto_if_defeated TRAINER_SUPER_NERD_MIGUEL, MtMoon_B2F_EventScript_MiguelGoPickFossil
	call MtMoon_B2F_EventScript_BattleMiguel
	release
	end

MtMoon_B2F_EventScript_BattleMiguel::
	textcolor NPC_TEXT_COLOR_MALE
	message MtMoon_B2F_Text_MiguelIntro
	waitmessage
	playbgm MUS_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_MIGUEL
	trainerbattle_no_intro TRAINER_SUPER_NERD_MIGUEL, MtMoon_B2F_Text_MiguelDefeat
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 1
	msgbox MtMoon_B2F_Text_WellEachTakeAFossil
	return

MtMoon_B2F_EventScript_MiguelAfterTheft::
	msgbox MtMoon_B2F_Text_MiguelAfterTheft
	release
	end

MtMoon_B2F_EventScript_MiguelFossilPicked::
	msgbox MtMoon_B2F_Text_LabOnCinnabarRegeneratesFossils
	release
	end

MtMoon_B2F_EventScript_MiguelGoPickFossil::
	msgbox MtMoon_B2F_Text_WellEachTakeAFossil
	release
	end

MtMoon_B2F_EventScript_DomeFossil::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	faceplayer
	msgbox MtMoon_B2F_Text_YouWantDomeFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtMoon_B2F_EventScript_DontTakeFossil
	checkitemspace ITEM_DOME_FOSSIL, 1
	goto_if_eq VAR_RESULT, FALSE, MtMoon_B2F_EventScript_FossilBagFull
	giveitem_msg MtMoon_B2F_Text_ObtainedDomeFossil, ITEM_DOME_FOSSIL, 1, MUS_OBTAIN_KEY_ITEM
	goto_if_eq VAR_RESULT, FALSE, MtMoon_B2F_EventScript_DontTakeFossil
	closemessage
	special QuestLog_CutRecording
	removeobject LOCALID_DOME_FOSSIL
	setflag FLAG_HIDE_DOME_FOSSIL
	setflag FLAG_GOT_DOME_FOSSIL
	setflag FLAG_GOT_FOSSIL_FROM_MT_MOON
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 2
	goto MtMoon_B2F_EventScript_ThomasArrival

MtMoon_B2F_EventScript_HelixFossil::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	faceplayer
	msgbox MtMoon_B2F_Text_YouWantHelixFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtMoon_B2F_EventScript_DontTakeFossil
	checkitemspace ITEM_HELIX_FOSSIL, 1
	goto_if_eq VAR_RESULT, FALSE, MtMoon_B2F_EventScript_FossilBagFull
	giveitem_msg MtMoon_B2F_Text_ObtainedHelixFossil, ITEM_HELIX_FOSSIL, 1, MUS_OBTAIN_KEY_ITEM
	goto_if_eq VAR_RESULT, FALSE, MtMoon_B2F_EventScript_DontTakeFossil
	closemessage
	special QuestLog_CutRecording
	removeobject LOCALID_HELIX_FOSSIL
	setflag FLAG_HIDE_HELIX_FOSSIL
	setflag FLAG_GOT_HELIX_FOSSIL
	setflag FLAG_GOT_FOSSIL_FROM_MT_MOON
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 2
	goto MtMoon_B2F_EventScript_ThomasArrival

MtMoon_B2F_EventScript_DontTakeFossil::
	releaseall
	end

MtMoon_B2F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT, MtMoon_B2F_Text_Grunt1Intro, MtMoon_B2F_Text_Grunt1Defeat
	msgbox MtMoon_B2F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_2, MtMoon_B2F_Text_Grunt2Intro, MtMoon_B2F_Text_Grunt2Defeat
	msgbox MtMoon_B2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_3, MtMoon_B2F_Text_Grunt3Intro, MtMoon_B2F_Text_Grunt3Defeat
	msgbox MtMoon_B2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_4, MtMoon_B2F_Text_Grunt4Intro, MtMoon_B2F_Text_Grunt4Defeat
	msgbox MtMoon_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_StaticRhyhorn::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	setwildbattle SPECIES_RHYHORN, 16, ITEM_HARD_STONE
	setvar VAR_0x8004, MOVE_ROCK_THROW
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_HORN_ATTACK
	setvar VAR_0x8005, 1
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_STOMP
	setvar VAR_0x8005, 2
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_TAIL_WHIP
	setvar VAR_0x8005, 3
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_RHYHORN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtMoon_B2F_EventScript_CompleteStaticRhyhorn
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtMoon_B2F_EventScript_CompleteStaticRhyhorn
	release
	end

MtMoon_B2F_EventScript_CompleteStaticRhyhorn::
	setflag FLAG_STATIC_MT_MOON_RHYHORN_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end

@ Scene 2 is pending theft; 3 = Rocket stole Dome; 4 = Rocket stole Helix.
@ The ordinary fossil-choice flags remain the sole original-choice authority.
MtMoon_B2F_EventScript_FossilBagFull::
	msgbox Text_BagIsFull
	releaseall
	end

MtMoon_B2F_EventScript_ThomasRetry::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_ne VAR_MAP_SCENE_MT_MOON_B2F, 2, EventScript_ReleaseEnd
@ A loss resumes at the healer, not inside this locked scene. On re-entry,
@ stage the retry in the fossil room before the player can bypass the operation.
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 14, MtMoon_B2F_EventScript_StageRetry
	goto_if_ne VAR_0x8005, 11, MtMoon_B2F_EventScript_StageRetry
MtMoon_B2F_EventScript_ThomasArrival::
	clearflag FLAG_HIDE_THOMAS_MT_MOON
	clearflag FLAG_HIDE_ROCKET_MT_MOON_ACCOMPLICE
	addobject LOCALID_THOMAS_MT_MOON
	addobject LOCALID_ROCKET_MT_MOON_ACCOMPLICE
	applymovement LOCALID_THOMAS_MT_MOON, MtMoon_B2F_Movement_RocketArrival
	applymovement LOCALID_ROCKET_MT_MOON_ACCOMPLICE, MtMoon_B2F_Movement_RocketArrival
	waitmovement 0
	msgbox MtMoon_B2F_Text_ThomasArrival
	msgbox MtMoon_B2F_Text_MiguelStayBack
	msgbox MtMoon_B2F_Text_ThomasOneIsOurs
	msgbox MtMoon_B2F_Text_MiguelWontLetRocket
	msgbox MtMoon_B2F_Text_ThomasIntroduction
	callnative Script_CountThomasUsablePlayerMons
	goto_if_eq VAR_RESULT, 0, MtMoon_B2F_EventScript_NoUsableMons
	setvar VAR_LAST_TALKED, LOCALID_THOMAS_MT_MOON
@ The trainer's doubleBattle data starts a Double; no stock two-mon gate.
	trainerbattle_no_intro TRAINER_THOMAS_MT_MOON, MtMoon_B2F_Text_ThomasDefeat
@ Normal loss/blackout never returns here and leaves scene 2 pending.
	goto_if_set FLAG_GOT_HELIX_FOSSIL, MtMoon_B2F_EventScript_StealDome
	applymovement LOCALID_ROCKET_MT_MOON_ACCOMPLICE, MtMoon_B2F_Movement_TakeHelix
	waitmovement 0
	removeobject LOCALID_HELIX_FOSSIL
	setflag FLAG_HIDE_HELIX_FOSSIL
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 4
	goto MtMoon_B2F_EventScript_TheftComplete

MtMoon_B2F_EventScript_StealDome::
	applymovement LOCALID_ROCKET_MT_MOON_ACCOMPLICE, MtMoon_B2F_Movement_TakeDome
	waitmovement 0
	removeobject LOCALID_DOME_FOSSIL
	setflag FLAG_HIDE_DOME_FOSSIL
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 3
MtMoon_B2F_EventScript_TheftComplete::
	setvar VAR_0x8004, ROCKET_OPERATION_MT_MOON
	callnative Script_SamRocketCompleteOperation
	setvar VAR_0x8004, ROCKET_EVIDENCE_DELIVERY_02
	callnative Script_SamRocketRecordEvidence
	msgbox MtMoon_B2F_Text_GruntGotFossil
	msgbox MtMoon_B2F_Text_ThomasThereWeAre
	msgbox MtMoon_B2F_Text_MiguelNo
	msgbox MtMoon_B2F_Text_ThomasEscape
	applymovement LOCALID_THOMAS_MT_MOON, MtMoon_B2F_Movement_RocketEscape
	applymovement LOCALID_ROCKET_MT_MOON_ACCOMPLICE, MtMoon_B2F_Movement_RocketEscape
	waitmovement 0
	setflag FLAG_HIDE_THOMAS_MT_MOON
	setflag FLAG_HIDE_ROCKET_MT_MOON_ACCOMPLICE
	removeobject LOCALID_THOMAS_MT_MOON
	removeobject LOCALID_ROCKET_MT_MOON_ACCOMPLICE
	msgbox MtMoon_B2F_Text_MiguelAfterTheft
	releaseall
	end

MtMoon_B2F_EventScript_StageRetry::
	warp MAP_MT_MOON_B2F, 14, 11
	waitstate
	end

MtMoon_B2F_EventScript_NoUsableMons::
	special SetCB2WhiteOut
	waitstate
	end

MtMoon_B2F_Movement_RocketArrival::
	walk_up
	step_end
MtMoon_B2F_Movement_TakeDome::
	walk_left
	walk_left
	walk_up
	step_end
MtMoon_B2F_Movement_TakeHelix::
	walk_left
	walk_up
	step_end
MtMoon_B2F_Movement_RocketEscape::
	walk_down
	walk_down
	step_end
