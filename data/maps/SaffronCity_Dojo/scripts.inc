.include "data/maps/SaffronCity_Dojo/hothouse_reward_text.inc"

SaffronCity_Dojo_MapScripts::
	.byte 0

@ Reserved SYS-HOT bindings from the Symbol Registry:
@ FLAG_0x32C = FLAG_SAM_HOTHOUSE_STARTED
@ FLAG_0x32D = FLAG_SAM_HOTHOUSE_SOLVED
@ FLAG_0x32E = FLAG_SAM_HOTHOUSE_HAWTHORNE_DEFEATED
@ FLAG_0x32F = FLAG_SAM_HOTHOUSE_TROPIUS_CLAIMED
@ VAR_0x409B = VAR_SAM_HOTHOUSE_IRRIGATION
@ VAR_0x409C = VAR_SAM_HOTHOUSE_SUNLIGHT
@ VAR_0x409D = VAR_SAM_HOTHOUSE_TEMPERATURE
@ VAR_0x409E = VAR_SAM_HOTHOUSE_SOIL
@ VAR_0x409F = VAR_SAM_HOTHOUSE_STATE
@
@ Dormant Ruby/Sapphire dummy trainer IDs are used for the five Hothouse
@ battles. Their trainer flags are otherwise unused in FireRed, so the four
@ gardener flags also provide persistent control unlock state.

EventScript_Sam_Hothouse_EntryPlaque::
	msgbox SaffronCity_Dojo_Text_HothousePlaque, MSGBOX_SIGN
	end

EventScript_Sam_Hothouse_Hawthorne::
	lock
	faceplayer
	goto_if_set FLAG_0x32F, EventScript_Sam_Hothouse_HawthorneCompleted
	goto_if_set FLAG_0x32E, EventScript_Sam_Hothouse_HawthorneRewardPending
	goto_if_unset FLAG_0x32C, EventScript_Sam_Hothouse_HawthorneNotStarted
	goto_if_unset FLAG_0x32D, EventScript_Sam_Hothouse_HawthornePuzzleActive
	trainerbattle_single TRAINER_RS_COOLTRAINER_M, SaffronCity_Dojo_Text_HawthorneBattleStart, SaffronCity_Dojo_Text_HawthorneDefeat, EventScript_Sam_Hothouse_HawthorneWon
	msgbox SaffronCity_Dojo_Text_HawthorneRetry, MSGBOX_AUTOCLOSE
	release
	end

EventScript_Sam_Hothouse_HawthorneNotStarted::
	goto_if_unset FLAG_GOT_TEA, EventScript_Sam_Hothouse_HawthornePreReferral
	msgbox SaffronCity_Dojo_Text_HawthorneIntroduction, MSGBOX_DEFAULT
	setflag FLAG_0x32C
	setvar VAR_0x409B, 0
	setvar VAR_0x409C, 0
	setvar VAR_0x409D, 0
	setvar VAR_0x409E, 0
	setvar VAR_0x409F, 1
	release
	end

EventScript_Sam_Hothouse_HawthornePreReferral::
	msgbox SaffronCity_Dojo_Text_HawthornePreReferral, MSGBOX_DEFAULT
	release
	end

EventScript_Sam_Hothouse_HawthornePuzzleActive::
	msgbox SaffronCity_Dojo_Text_HawthornePuzzleRepeat, MSGBOX_DEFAULT
	release
	end

EventScript_Sam_Hothouse_HawthorneWon::
	setflag FLAG_0x32E
	setvar VAR_0x409F, 3
	msgbox SaffronCity_Dojo_Text_HawthorneAfterBattle, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_HawthorneRewardPending

EventScript_Sam_Hothouse_HawthorneRewardPending::
	msgbox SaffronCity_Dojo_Text_TropiusChoice, MSGBOX_DEFAULT
	callnative GiveSamHothouseTropius
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, EventScript_Sam_Hothouse_TropiusNoRoom
	setflag FLAG_0x32F
	setvar VAR_0x409F, 4
	msgbox SaffronCity_Dojo_Text_TropiusReceived, MSGBOX_DEFAULT
	release
	end

EventScript_Sam_Hothouse_TropiusNoRoom::
	msgbox SaffronCity_Dojo_Text_TropiusNoRoom, MSGBOX_DEFAULT
	release
	end

EventScript_Sam_Hothouse_HawthorneCompleted::
	msgbox SaffronCity_Dojo_Text_HawthorneCompleted, MSGBOX_DEFAULT
	release
	end

EventScript_Sam_Hothouse_IrrigationGardener::
	goto_if_unset FLAG_0x32C, EventScript_Sam_Hothouse_WorkAreaLocked
	trainerbattle_single TRAINER_RS_AROMA_LADY, SaffronCity_Dojo_Text_IrrigationIntro, SaffronCity_Dojo_Text_IrrigationDefeat
	msgbox SaffronCity_Dojo_Text_IrrigationClue, MSGBOX_AUTOCLOSE
	end

EventScript_Sam_Hothouse_SunGardener::
	goto_if_unset FLAG_0x32C, EventScript_Sam_Hothouse_WorkAreaLocked
	trainerbattle_single TRAINER_RS_LADY, SaffronCity_Dojo_Text_SunIntro, SaffronCity_Dojo_Text_SunDefeat
	msgbox SaffronCity_Dojo_Text_SunClue, MSGBOX_AUTOCLOSE
	end

EventScript_Sam_Hothouse_ClimateGardener::
	goto_if_unset FLAG_0x32C, EventScript_Sam_Hothouse_WorkAreaLocked
	trainerbattle_single TRAINER_RS_BEAUTY, SaffronCity_Dojo_Text_ClimateIntro, SaffronCity_Dojo_Text_ClimateDefeat
	msgbox SaffronCity_Dojo_Text_ClimateClue, MSGBOX_AUTOCLOSE
	end

EventScript_Sam_Hothouse_SoilGardener::
	goto_if_unset FLAG_0x32C, EventScript_Sam_Hothouse_WorkAreaLocked
	trainerbattle_single TRAINER_RS_PKMN_BREEDER_M, SaffronCity_Dojo_Text_SoilIntro, SaffronCity_Dojo_Text_SoilDefeat
	msgbox SaffronCity_Dojo_Text_SoilClue, MSGBOX_AUTOCLOSE
	end

EventScript_Sam_Hothouse_WorkAreaLocked::
	msgbox SaffronCity_Dojo_Text_WorkAreaLocked, MSGBOX_DEFAULT
	end

EventScript_Sam_Hothouse_IrrigationControl::
	lock
	checktrainerflag TRAINER_RS_AROMA_LADY
	goto_if_eq VAR_RESULT, 0, EventScript_Sam_Hothouse_ControlLocked
	goto_if_eq VAR_0x409B, 0, EventScript_Sam_Hothouse_IrrigationSetMedium
	goto_if_eq VAR_0x409B, 1, EventScript_Sam_Hothouse_IrrigationSetHigh
	setvar VAR_0x409B, 0
	msgbox SaffronCity_Dojo_Text_IrrigationLow, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_IrrigationSetMedium::
	setvar VAR_0x409B, 1
	msgbox SaffronCity_Dojo_Text_IrrigationMedium, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_IrrigationSetHigh::
	setvar VAR_0x409B, 2
	msgbox SaffronCity_Dojo_Text_IrrigationHigh, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution

EventScript_Sam_Hothouse_SunlightControl::
	lock
	checktrainerflag TRAINER_RS_LADY
	goto_if_eq VAR_RESULT, 0, EventScript_Sam_Hothouse_ControlLocked
	goto_if_eq VAR_0x409C, 0, EventScript_Sam_Hothouse_SunSetPartial
	goto_if_eq VAR_0x409C, 1, EventScript_Sam_Hothouse_SunSetFull
	setvar VAR_0x409C, 0
	msgbox SaffronCity_Dojo_Text_SunShade, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_SunSetPartial::
	setvar VAR_0x409C, 1
	msgbox SaffronCity_Dojo_Text_SunPartial, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_SunSetFull::
	setvar VAR_0x409C, 2
	msgbox SaffronCity_Dojo_Text_SunFull, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution

EventScript_Sam_Hothouse_TemperatureControl::
	lock
	checktrainerflag TRAINER_RS_BEAUTY
	goto_if_eq VAR_RESULT, 0, EventScript_Sam_Hothouse_ControlLocked
	goto_if_eq VAR_0x409D, 0, EventScript_Sam_Hothouse_TempSetWarm
	goto_if_eq VAR_0x409D, 1, EventScript_Sam_Hothouse_TempSetHot
	setvar VAR_0x409D, 0
	msgbox SaffronCity_Dojo_Text_TempCool, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_TempSetWarm::
	setvar VAR_0x409D, 1
	msgbox SaffronCity_Dojo_Text_TempWarm, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_TempSetHot::
	setvar VAR_0x409D, 2
	msgbox SaffronCity_Dojo_Text_TempHot, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution

EventScript_Sam_Hothouse_SoilControl::
	lock
	checktrainerflag TRAINER_RS_PKMN_BREEDER_M
	goto_if_eq VAR_RESULT, 0, EventScript_Sam_Hothouse_ControlLocked
	goto_if_eq VAR_0x409E, 0, EventScript_Sam_Hothouse_SoilSetBalanced
	goto_if_eq VAR_0x409E, 1, EventScript_Sam_Hothouse_SoilSetRich
	setvar VAR_0x409E, 0
	msgbox SaffronCity_Dojo_Text_SoilDry, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_SoilSetBalanced::
	setvar VAR_0x409E, 1
	msgbox SaffronCity_Dojo_Text_SoilBalanced, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution
EventScript_Sam_Hothouse_SoilSetRich::
	setvar VAR_0x409E, 2
	msgbox SaffronCity_Dojo_Text_SoilRich, MSGBOX_DEFAULT
	goto EventScript_Sam_Hothouse_CheckSolution

EventScript_Sam_Hothouse_ControlLocked::
	msgbox SaffronCity_Dojo_Text_ControlLocked, MSGBOX_DEFAULT
	release
	end

EventScript_Sam_Hothouse_CheckSolution::
	goto_if_set FLAG_0x32D, EventScript_Sam_Hothouse_ControlEnd
	goto_if_ne VAR_0x409B, 1, EventScript_Sam_Hothouse_ControlEnd
	goto_if_ne VAR_0x409C, 2, EventScript_Sam_Hothouse_ControlEnd
	goto_if_ne VAR_0x409D, 1, EventScript_Sam_Hothouse_ControlEnd
	goto_if_ne VAR_0x409E, 2, EventScript_Sam_Hothouse_ControlEnd
	setflag FLAG_0x32D
	setvar VAR_0x409F, 2
	msgbox SaffronCity_Dojo_Text_HothouseSolved, MSGBOX_DEFAULT
EventScript_Sam_Hothouse_ControlEnd::
	release
	end
