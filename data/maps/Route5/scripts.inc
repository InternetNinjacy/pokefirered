Route5_MapScripts::
	.byte 0

Route5_EventScript_UndergroundPathSign::
	msgbox Route5_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route5_EventScript_StaticMiltank::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	setwildbattle SPECIES_MILTANK, 18, ITEM_SILK_SCARF
	setvar VAR_0x8004, MOVE_TACKLE
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_ROLLOUT
	setvar VAR_0x8005, 1
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_DEFENSE_CURL
	setvar VAR_0x8005, 2
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_STOMP
	setvar VAR_0x8005, 3
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route5_EventScript_CompleteStaticMiltank
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route5_EventScript_CompleteStaticMiltank
	release
	end

Route5_EventScript_CompleteStaticMiltank::
	setflag FLAG_STATIC_ROUTE5_MILTANK_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end
