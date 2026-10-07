SSAnne_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SSAnne_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAnne_Exterior_OnFrame
	.byte 0

SSAnne_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SSANNE_EXTERIOR
	setflag FLAG_HIDE_SS_ANNE_TRUCK_MEW
	call_if_set FLAG_MEW_TRUCK_MOVED, SSAnne_Exterior_EventScript_ShowTruckMew
	call_if_set FLAG_MEW_TRUCK_RESOLVED, SSAnne_Exterior_EventScript_HideTruckMew
	end

SSAnne_Exterior_EventScript_ShowTruckMew::
	clearflag FLAG_HIDE_SS_ANNE_TRUCK_MEW
	return

SSAnne_Exterior_EventScript_HideTruckMew::
	setflag FLAG_HIDE_SS_ANNE_TRUCK_MEW
	return

SSAnne_Exterior_OnFrame::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 1, SSAnne_Exterior_ExitSSAnne
	.2byte 0

SSAnne_Exterior_ExitSSAnne::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_le VAR_0x8005, 6, SSAnne_Exterior_WalkDown
	call_if_ge VAR_0x8005, 7, SSAnne_Exterior_WalkInPlaceDown
	fadenewbgm MUS_SURF
	delay 50
	special DoSSAnneDepartureCutscene
	waitstate
	removeobject LOCALID_SS_ANNE
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_Exit
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 2
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	warp MAP_VERMILION_CITY, 23, 34
	waitstate
	releaseall
	end

SSAnne_Exterior_WalkDown::
	applymovement LOCALID_PLAYER, SSAnne_Exterior_Movement_WalkDown
	waitmovement 0
	return

SSAnne_Exterior_WalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SSAnne_Exterior_Movement_Exit::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SSAnne_Exterior_Movement_WalkDown::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end


@ MEW-001: classic truck secret. The truck's map art remains the landmark; the
@ persistent moved state reveals Mew beside it after a Strength interaction.
SSAnne_Exterior_EventScript_Truck::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_ne VAR_MAP_SCENE_VERMILION_CITY, 3, SSAnne_Exterior_EventScript_TruckDormant
	goto_if_set FLAG_MEW_TRUCK_MOVED, SSAnne_Exterior_EventScript_TruckAlreadyMoved
	goto_if_unset FLAG_BADGE04_GET, SSAnne_Exterior_EventScript_TruckNeedsStrength
	checkpartymove MOVE_STRENGTH
	goto_if_eq VAR_RESULT, PARTY_SIZE, SSAnne_Exterior_EventScript_TruckNeedsStrength
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	msgbox SSAnne_Exterior_Text_MoveTruck, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSAnne_Exterior_EventScript_TruckCancel
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	setflag FLAG_SYS_USE_STRENGTH
	setflag FLAG_MEW_TRUCK_MOVED
	clearflag FLAG_HIDE_SS_ANNE_TRUCK_MEW
	addobject LOCALID_SS_ANNE_TRUCK_MEW
	msgbox SSAnne_Exterior_Text_TruckShifted, MSGBOX_SIGN
	releaseall
	end

SSAnne_Exterior_EventScript_TruckDormant::
	msgbox SSAnne_Exterior_Text_OldTruck, MSGBOX_SIGN
	releaseall
	end

SSAnne_Exterior_EventScript_TruckNeedsStrength::
	msgbox SSAnne_Exterior_Text_TruckNeedsStrength, MSGBOX_SIGN
	releaseall
	end

SSAnne_Exterior_EventScript_TruckAlreadyMoved::
	msgbox SSAnne_Exterior_Text_TruckAlreadyMoved, MSGBOX_SIGN
	releaseall
	end

SSAnne_Exterior_EventScript_TruckCancel::
	closemessage
	releaseall
	end

SSAnne_Exterior_EventScript_TruckMew::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	setwildbattle SPECIES_MEW, 50
	waitse
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	setflag FLAG_MEW_TRUCK_RESOLVED
	setflag FLAG_HIDE_SS_ANNE_TRUCK_MEW
	removeobject LOCALID_SS_ANNE_TRUCK_MEW
	release
	end

SSAnne_Exterior_Text_OldTruck::
	.string "It's an old truck.\\p"
	.string "It hasn't moved in years.$"

SSAnne_Exterior_Text_TruckNeedsStrength::
	.string "The old truck looks like it might\\n"
	.string "shift with enough STRENGTH.$"

SSAnne_Exterior_Text_MoveTruck::
	.string "The old truck looks movable.\\p"
	.string "Use STRENGTH to push it aside?$"

SSAnne_Exterior_Text_TruckShifted::
	.string "{STR_VAR_1} used STRENGTH!\\p"
	.string "The truck shifted!\\n"
	.string "Something was hiding beside it…$"

SSAnne_Exterior_Text_TruckAlreadyMoved::
	.string "The old truck has been pushed\\n"
	.string "aside.$"
