Route9_MapScripts::
	.byte 0

Route9_EventScript_RouteSign::
	msgbox Route9_Text_RouteSign, MSGBOX_SIGN
	end

// Batch 5 local wrappers preserve the existing trainer IDs/dialogue/rematch flow
// while applying the settled Double Battle formats.
Route9_EventScript_JeremyBatch5::
	trainerbattle_double TRAINER_HIKER_JEREMY, Route9_Text_JeremyIntro, Route9_Text_JeremyDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route9_EventScript_JeremyBatch5Rematch
	msgbox Route9_Text_JeremyPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_JeremyBatch5Rematch::
	trainerbattle_rematch_double TRAINER_HIKER_JEREMY, Route9_Text_JeremyRematchIntro, Route9_Text_JeremyDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route9_Text_JeremyPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_AlanBatch5::
	trainerbattle_double TRAINER_HIKER_ALAN, Route9_Text_AlanIntro, Route9_Text_AlanDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route9_EventScript_AlanBatch5Rematch
	msgbox Route9_Text_AlanPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_AlanBatch5Rematch::
	trainerbattle_rematch_double TRAINER_HIKER_ALAN, Route9_Text_AlanRematchIntro, Route9_Text_AlanDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route9_Text_AlanPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_DrewBatch5::
	trainerbattle_double TRAINER_CAMPER_DREW, Route9_Text_DrewIntro, Route9_Text_DrewDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route9_EventScript_DrewBatch5Rematch
	msgbox Route9_Text_DrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_DrewBatch5Rematch::
	trainerbattle_rematch_double TRAINER_CAMPER_DREW, Route9_Text_DrewRematchIntro, Route9_Text_DrewDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route9_Text_DrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_StaticMagneton::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	checkitemspace ITEM_METAL_COAT
	goto_if_eq VAR_RESULT, FALSE, Route9_EventScript_StaticMagnetonNoRoom
	setwildbattle SPECIES_MAGNETON, 27, ITEM_METAL_COAT
	special SetEnemyEventMonMagnetonHiddenPowerIVs
	setvar VAR_0x8004, MOVE_SPARK
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_THUNDER_WAVE
	setvar VAR_0x8005, 1
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_SONIC_BOOM
	setvar VAR_0x8005, 2
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_HIDDEN_POWER
	setvar VAR_0x8005, 3
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_MAGNETON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route9_EventScript_DefeatedStaticMagneton
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route9_EventScript_CompleteStaticMagneton
	release
	end

Route9_EventScript_DefeatedStaticMagneton::
	giveitem ITEM_METAL_COAT
	goto Route9_EventScript_CompleteStaticMagneton
	end

Route9_EventScript_CompleteStaticMagneton::
	setflag FLAG_STATIC_ROUTE9_MAGNETON_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end

Route9_EventScript_StaticMagnetonNoRoom::
	msgbox Route9_Text_NoRoomForMetalCoat
	release
	end
