.equ VERMILION_FLOW_A,        FLAG_TEMP_1
.equ VERMILION_CURRENT_B,     FLAG_TEMP_2
.equ VERMILION_DOCK_B,        FLAG_TEMP_3
.equ VERMILION_VALVE_LEFT,    FLAG_TEMP_4
.equ VERMILION_VALVE_RIGHT,   FLAG_TEMP_5

VermilionCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VermilionCity_Gym_OnLoad
	.byte 0

VermilionCity_Gym_OnLoad::
	call VermilionCity_Gym_EventScript_DrawClosedChannels
	call_if_set VERMILION_FLOW_A, VermilionCity_Gym_EventScript_OpenBypassA
	call_if_set VERMILION_DOCK_B, VermilionCity_Gym_EventScript_OpenBypassB
	call_if_set VERMILION_VALVE_LEFT, VermilionCity_Gym_EventScript_TryOpenFinalBypass
	end

VermilionCity_Gym_EventScript_DrawClosedChannels::
	// Section A: direct crossing x2, optional bypass x8.
	setmetatile 1, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 2, 14, METATILE_VermilionGym_Floor, 0
	setmetatile 3, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 4, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 5, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 6, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 7, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 8, 14, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 9, 14, METATILE_VermilionGym_Beam_MidTop, 1

	// Section B: optional bypass x2, direct crossing x8.
	setmetatile 1, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 2, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 3, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 4, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 5, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 6, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 7, 10, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 8, 10, METATILE_VermilionGym_Floor, 0
	setmetatile 9, 10, METATILE_VermilionGym_Beam_MidTop, 1

	// Section C: direct family trigger x5, optional bypass x8.
	setmetatile 1, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 2, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 3, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 5, 6, METATILE_VermilionGym_Floor, 0
	setmetatile 6, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 7, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 8, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 9, 6, METATILE_VermilionGym_Beam_MidTop, 1
	return

VermilionCity_Gym_EventScript_OpenBypassA::
	setmetatile 8, 14, METATILE_VermilionGym_Floor, 0
	return

VermilionCity_Gym_EventScript_OpenBypassB::
	setmetatile 2, 10, METATILE_VermilionGym_Floor, 0
	return

VermilionCity_Gym_EventScript_OpenFinalBypass::
	setmetatile 8, 6, METATILE_VermilionGym_Floor, 0
	return

VermilionCity_Gym_EventScript_FlowLeverA::
	lockall
	goto_if_set VERMILION_FLOW_A, VermilionCity_Gym_EventScript_ControlAlreadySet
	setflag VERMILION_FLOW_A
	call VermilionCity_Gym_EventScript_OpenBypassA
	special DrawWholeMapView
	playse SE_UNLOCK
	waitse
	releaseall
	end

VermilionCity_Gym_EventScript_CurrentSwitchB::
	lockall
	goto_if_set VERMILION_CURRENT_B, VermilionCity_Gym_EventScript_ControlAlreadySet
	setflag VERMILION_CURRENT_B
	playse SE_PIN
	waitse
	releaseall
	end

VermilionCity_Gym_EventScript_DockReleaseB::
	lockall
	goto_if_set VERMILION_DOCK_B, VermilionCity_Gym_EventScript_ControlAlreadySet
	goto_if_unset VERMILION_CURRENT_B, VermilionCity_Gym_EventScript_ControlUnavailable
	setflag VERMILION_DOCK_B
	call VermilionCity_Gym_EventScript_OpenBypassB
	special DrawWholeMapView
	playse SE_UNLOCK
	waitse
	releaseall
	end

VermilionCity_Gym_EventScript_FinalValveLeft::
	lockall
	goto_if_set VERMILION_VALVE_LEFT, VermilionCity_Gym_EventScript_ControlAlreadySet
	setflag VERMILION_VALVE_LEFT
	playse SE_PIN
	waitse
	call VermilionCity_Gym_EventScript_TryOpenFinalBypass
	special DrawWholeMapView
	releaseall
	end

VermilionCity_Gym_EventScript_FinalValveRight::
	lockall
	goto_if_set VERMILION_VALVE_RIGHT, VermilionCity_Gym_EventScript_ControlAlreadySet
	setflag VERMILION_VALVE_RIGHT
	playse SE_PIN
	waitse
	call VermilionCity_Gym_EventScript_TryOpenFinalBypass
	special DrawWholeMapView
	releaseall
	end

VermilionCity_Gym_EventScript_TryOpenFinalBypass::
	goto_if_unset VERMILION_VALVE_LEFT, EventScript_Return
	goto_if_unset VERMILION_VALVE_RIGHT, EventScript_Return
	call VermilionCity_Gym_EventScript_OpenFinalBypass
	playse SE_UNLOCK
	waitse
	return

VermilionCity_Gym_EventScript_ControlAlreadySet::
	releaseall
	end

VermilionCity_Gym_EventScript_ControlUnavailable::
	releaseall
	end

VermilionCity_Gym_EventScript_FamilyTrigger::
	goto VermilionCity_Gym_EventScript_Tucker
	end

VermilionCity_Gym_EventScript_LtSurge::
	famechecker FAMECHECKER_LTSURGE, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_SURGE_VERMILION, VermilionCity_Gym_Text_LtSurgeIntro, VermilionCity_Gym_Text_LtSurgeDefeat, VermilionCity_Gym_EventScript_DefeatedLtSurge, NO_MUSIC
	goto_if_unset FLAG_GOT_TM34_FROM_SURGE, VermilionCity_Gym_EventScript_GiveTM40
	msgbox VermilionCity_Gym_Text_LtSurgePostBattle
	release
	end

VermilionCity_Gym_EventScript_DefeatedLtSurge::
	famechecker FAMECHECKER_LTSURGE, 1
	call_if_unset FLAG_GOT_HM05, VermilionCity_Gym_EventScript_ShowOaksAide
	clearflag FLAG_HIDE_FAME_CHECKER_LT_SURGE_JOURNAL
	setflag FLAG_DEFEATED_LT_SURGE
	setflag FLAG_BADGE03_GET
	set_gym_trainers 3
	goto VermilionCity_Gym_EventScript_GiveTM40
	end

VermilionCity_Gym_EventScript_ShowOaksAide::
	clearflag FLAG_HIDE_VERMILION_CITY_OAKS_AIDE
	return

VermilionCity_Gym_EventScript_GiveTM40::
	msgbox VermilionCity_Gym_Text_ExplainThunderBadgeTakeThis
	checkitemspace ITEM_TM40_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_Gym_EventScript_NoRoomForTM40
	giveitem_msg VermilionCity_Gym_Text_ReceivedTM34FromLtSurge, ITEM_TM40_WATER_PULSE
	@ Preserve the vanilla Surge reward-state save slot as a compatibility alias.
	setflag FLAG_GOT_TM34_FROM_SURGE
	msgbox VermilionCity_Gym_Text_ExplainTM34
	release
	end

VermilionCity_Gym_EventScript_NoRoomForTM40::
	msgbox VermilionCity_Gym_Text_MakeRoomInYourBag
	release
	end

VermilionCity_Gym_EventScript_Dwayne::
	trainerbattle_single TRAINER_LIFEGUARD_TYLER_VERMILION, VermilionCity_Gym_Text_DwayneIntro, VermilionCity_Gym_Text_DwayneDefeat
	famechecker FAMECHECKER_LTSURGE, 4
	msgbox VermilionCity_Gym_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

VermilionCity_Gym_EventScript_Baily::
	trainerbattle_single TRAINER_SURFER_CODY_VERMILION, VermilionCity_Gym_Text_BailyIntro, VermilionCity_Gym_Text_BailyDefeat
	msgbox VermilionCity_Gym_Text_BailyPostBattle, MSGBOX_AUTOCLOSE
	end

VermilionCity_Gym_EventScript_Tucker::
	trainerbattle_single TRAINER_BEACH_FAMILY_LISA_BEN_VERMILION, VermilionCity_Gym_Text_TuckerIntro, VermilionCity_Gym_Text_TuckerDefeat, VermilionCity_Gym_EventScript_DefeatedTucker
	famechecker FAMECHECKER_LTSURGE, 3
	msgbox VermilionCity_Gym_Text_TuckerPostBattle, MSGBOX_AUTOCLOSE
	end

VermilionCity_Gym_EventScript_DefeatedTucker::
	famechecker FAMECHECKER_LTSURGE, 2
	release
	end

VermilionCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LT_SURGE, VermilionCity_Gym_EventScript_GymGuyPostVictory
	msgbox VermilionCity_Gym_Text_GymGuyAdvice
	release
	end

VermilionCity_Gym_EventScript_GymGuyPostVictory::
	msgbox VermilionCity_Gym_Text_GymGuyPostVictory
	release
	end

VermilionCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, VermilionCity_Gym_EventScript_GymStatuePostVictory
	msgbox VermilionCity_Gym_Text_GymStatue
	releaseall
	end

VermilionCity_Gym_EventScript_GymStatuePostVictory::
	msgbox VermilionCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end
