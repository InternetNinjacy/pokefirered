Route11_MapScripts::
	.byte 0

Route11_EventScript_DiglettsCaveSign::
	msgbox Route11_Text_DiglettsCave, MSGBOX_SIGN
	end

Route11_EventScript_StaticOnix::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	setwildbattle SPECIES_ONIX, 24, ITEM_SOFT_SAND
	setvar VAR_0x8004, MOVE_ROCK_THROW
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_SANDSTORM
	setvar VAR_0x8005, 1
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_SAND_TOMB
	setvar VAR_0x8005, 2
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_ROCK_TOMB
	setvar VAR_0x8005, 3
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_ONIX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route11_EventScript_CompleteStaticOnix
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route11_EventScript_CompleteStaticOnix
	release
	end

Route11_EventScript_CompleteStaticOnix::
	setflag FLAG_STATIC_ROUTE11_ONIX_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end
