Route9_MapScripts::
	.byte 0

Route9_EventScript_RouteSign::
	msgbox Route9_Text_RouteSign, MSGBOX_SIGN
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
