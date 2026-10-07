FuchsiaCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_OnTransition
	.byte 0

FuchsiaCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FUCHSIA_CITY
	call_if_set FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_SetOmanyteGfx
	call_if_unset FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_SetKabutoGfx
	call FuchsiaCity_EventScript_UpdateGreen
	end

FuchsiaCity_EventScript_SetOmanyteGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OMANYTE
	return

FuchsiaCity_EventScript_SetKabutoGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_KABUTO
	return

FuchsiaCity_EventScript_LittleBoy::
	msgbox FuchsiaCity_Text_DidYouTrySafariGame, MSGBOX_NPC
	end

FuchsiaCity_EventScript_OldMan::
	msgbox FuchsiaCity_Text_SafariZoneZooInFront, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Erik::
	msgbox FuchsiaCity_Text_WheresSara, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_ItemBallInThere, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Lass::
	lock
	faceplayer
	famechecker FAMECHECKER_KOGA, 3
	msgbox FuchsiaCity_Text_MyFatherIsGymLeader
	release
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_CitySign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZoneSign::
	msgbox FuchsiaCity_Text_SafariZoneSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariGameSign::
	msgbox FuchsiaCity_Text_SafariGameSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_WardensHomeSign::
	msgbox FuchsiaCity_Text_WardensHomeSign, MSGBOX_SIGN
	end

@ Unused
FuchsiaCity_EventScript_SafariZoneOfficeSign::
	msgbox FuchsiaCity_Text_SafariZoneOfficeSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_KOGA, 0
	msgbox FuchsiaCity_Text_GymSign
	releaseall
	end

FuchsiaCity_EventScript_ChanseySign::
	lockall
	setvar VAR_0x8004, SPECIES_CHANSEY
	special SetSeenMon
	showmonpic SPECIES_CHANSEY, 10, 3
	msgbox FuchsiaCity_Text_ChanseySign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_VoltorbSign::
	lockall
	setvar VAR_0x8004, SPECIES_VOLTORB
	special SetSeenMon
	showmonpic SPECIES_VOLTORB, 10, 3
	msgbox FuchsiaCity_Text_VoltorbSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_KangaskhanSign::
	lockall
	setvar VAR_0x8004, SPECIES_KANGASKHAN
	special SetSeenMon
	showmonpic SPECIES_KANGASKHAN, 10, 3
	msgbox FuchsiaCity_Text_KangaskhanSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_SlowpokeSign::
	lockall
	setvar VAR_0x8004, SPECIES_SLOWPOKE
	special SetSeenMon
	showmonpic SPECIES_SLOWPOKE, 10, 3
	msgbox FuchsiaCity_Text_SlowpokeSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_LaprasSign::
	lockall
	setvar VAR_0x8004, SPECIES_LAPRAS
	special SetSeenMon
	showmonpic SPECIES_LAPRAS, 10, 3
	msgbox FuchsiaCity_Text_LaprasSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_FossilMonSign::
	lockall
	goto_if_set FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_OmanyteSign
	setvar VAR_0x8004, SPECIES_KABUTO
	special SetSeenMon
	showmonpic SPECIES_KABUTO, 10, 3
	msgbox FuchsiaCity_Text_KabutoSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_OmanyteSign::
	setvar VAR_0x8004, SPECIES_OMANYTE
	special SetSeenMon
	showmonpic SPECIES_OMANYTE, 10, 3
	msgbox FuchsiaCity_Text_OmanyteSign
	hidemonpic
	releaseall
	end

@ Pokémon: Sam Edition — Green rival checkpoint.
FuchsiaCity_EventScript_UpdateGreen::
	setflag FLAG_TEMP_11
	goto_if_defeated TRAINER_GREEN_CELADON_DITTO, FuchsiaCity_EventScript_ShowGreen
	goto_if_defeated TRAINER_GREEN_CELADON_ESPEON, FuchsiaCity_EventScript_ShowGreen
	goto_if_defeated TRAINER_GREEN_CELADON_RAICHU, FuchsiaCity_EventScript_ShowGreen
	return

FuchsiaCity_EventScript_ShowGreen::
	goto_if_defeated TRAINER_GREEN_FUCHSIA_DITTO, EventScript_Return
	goto_if_defeated TRAINER_GREEN_FUCHSIA_ESPEON, EventScript_Return
	goto_if_defeated TRAINER_GREEN_FUCHSIA_RAICHU, EventScript_Return
	clearflag FLAG_TEMP_11
	return

FuchsiaCity_EventScript_Green::
	lock
	faceplayer
	setvar VAR_LAST_TALKED, LOCALID_FUCHSIA_GREEN
	playbgm MUS_ENCOUNTER_RIVAL, 0
	goto_if_eq VAR_STARTER_MON, 0, FuchsiaCity_EventScript_GreenRaichu
	goto_if_eq VAR_STARTER_MON, 1, FuchsiaCity_EventScript_GreenDitto
	goto FuchsiaCity_EventScript_GreenEspeon
FuchsiaCity_EventScript_GreenDitto::
	trainerbattle_no_intro TRAINER_GREEN_FUCHSIA_DITTO, FuchsiaCity_Text_GreenDefeat
	goto FuchsiaCity_EventScript_GreenWon
FuchsiaCity_EventScript_GreenEspeon::
	trainerbattle_no_intro TRAINER_GREEN_FUCHSIA_ESPEON, FuchsiaCity_Text_GreenDefeat
	goto FuchsiaCity_EventScript_GreenWon
FuchsiaCity_EventScript_GreenRaichu::
	trainerbattle_no_intro TRAINER_GREEN_FUCHSIA_RAICHU, FuchsiaCity_Text_GreenDefeat
	goto FuchsiaCity_EventScript_GreenWon
FuchsiaCity_EventScript_GreenWon::
	@ Opening/post prose is descriptive rather than verbatim in Green Decision Record v1.0.
	@ Do not invent final dialogue; resolve the mandatory battle state only.
	setflag FLAG_TEMP_11
	removeobject LOCALID_FUCHSIA_GREEN
	fadedefaultbgm
	release
	end

FuchsiaCity_Text_GreenDefeat::
	.string "Yep. You caught me.$"
