SSAnne_2F_Corridor_MapScripts::
	.byte 0

SSAnne_2F_Corridor_EventScript_RivalTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto SSAnne_2F_Corridor_EventScript_RivalTrigger
	end

SSAnne_2F_Corridor_EventScript_RivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	goto SSAnne_2F_Corridor_EventScript_RivalTrigger
	end

SSAnne_2F_Corridor_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	goto SSAnne_2F_Corridor_EventScript_RivalTrigger
	end

SSAnne_2F_Corridor_EventScript_RivalTrigger::
	textcolor NPC_TEXT_COLOR_FEMALE
	playse SE_EXIT
	delay 5
	playbgm MUS_ENCOUNTER_RIVAL, 0
	addobject LOCALID_SS_ANNE_RIVAL
	delay 10
	applymovement LOCALID_SS_ANNE_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 20
	call_if_eq VAR_TEMP_1, 0, SSAnne_2F_Corridor_EventScript_RivalApproachLeft
	call_if_eq VAR_TEMP_1, 1, SSAnne_2F_Corridor_EventScript_RivalApproachMid
	call_if_eq VAR_TEMP_1, 2, SSAnne_2F_Corridor_EventScript_RivalApproachRight
	msgbox SSAnne_2F_Corridor_Text_GreenIntro
	setvar VAR_LAST_TALKED, LOCALID_SS_ANNE_RIVAL
	call_if_eq VAR_STARTER_MON, 2, SSAnne_2F_Corridor_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, SSAnne_2F_Corridor_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, SSAnne_2F_Corridor_EventScript_RivalCharmander
	msgbox SSAnne_2F_Corridor_Text_GreenPostBattle
	closemessage
	delay 10
	playbgm MUS_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, SSAnne_2F_Corridor_EventScript_RivalExitLeft
	call_if_eq VAR_TEMP_1, 1, SSAnne_2F_Corridor_EventScript_RivalExitMid
	call_if_eq VAR_TEMP_1, 2, SSAnne_2F_Corridor_EventScript_RivalExitRight
	fadedefaultbgm
	removeobject LOCALID_SS_ANNE_RIVAL
	setvar VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR, 1
	releaseall
	end

SSAnne_2F_Corridor_EventScript_RivalApproachLeft::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalApproachLeft
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalApproachMid::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalApproachMid
	applymovement LOCALID_PLAYER, SSAnne_2F_Corridor_Movement_PlayerFaceRivalMid
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalApproachRight::
	applymovement LOCALID_PLAYER, SSAnne_2F_Corridor_Movement_PlayerFaceRivalRight
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalApproachRight
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_GREEN_SS_ANNE_ESPEON, SSAnne_2F_Corridor_Text_GreenDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_GREEN_SS_ANNE_DITTO, SSAnne_2F_Corridor_Text_GreenDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_GREEN_SS_ANNE_RAICHU, SSAnne_2F_Corridor_Text_GreenDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalExitLeft::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalExitLeft
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalExitMid::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalExitMid
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalExitRight::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalExitRight
	waitmovement 0
	return

SSAnne_2F_Corridor_Movement_PlayerFaceRivalRight::
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SSAnne_2F_Corridor_Movement_PlayerFaceRivalMid::
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SSAnne_2F_Corridor_Movement_RivalApproachLeft::
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_Movement_RivalApproachMid::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

SSAnne_2F_Corridor_Movement_RivalApproachRight::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	delay_4
	step_end

SSAnne_2F_Corridor_Movement_RivalExitLeft::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_Movement_RivalExitMid::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_Movement_RivalExitRight::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_EventScript_Sailor::
	msgbox SSAnne_2F_Corridor_Text_ThisShipIsLuxuryLiner, MSGBOX_NPC
	end

@ Pokémon: Sam Edition — locked Green S.S. Anne dialogue.
SSAnne_2F_Corridor_Text_GreenIntro::
	.string "{PLAYER}! I was wondering if you made it\n"
	.string "onto the ship. There are TRAINERS\l"
	.string "everywhere in here.\p"
	.string "I've been testing different\n"
	.string "combinations against them.\p"
	.string "Three POKéMON feels a lot better\n"
	.string "than two. You can actually cover\l"
	.string "each other's bad matchups.\p"
	.string "Come on. I want to see if I built\n"
	.string "this right!$"

SSAnne_2F_Corridor_Text_GreenDefeat::
	.string "Huh. Okay, that exposed something.$"

SSAnne_2F_Corridor_Text_GreenPostBattle::
	.string "That was good. I thought I had\n"
	.string "every angle covered, but you found\l"
	.string "one I didn't.\p"
	.string "That's the fun part, though. If a\n"
	.string "team has a weakness, you fix it.\p"
	.string "I'm going to change a few things\n"
	.string "before next time.\p"
	.string "The CAPTAIN's up ahead. Apparently\n"
	.string "he's having a rough trip.$"
