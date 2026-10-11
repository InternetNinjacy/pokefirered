SSAnne_Kitchen_MapScripts::
	.byte 0

SSAnne_Kitchen_EventScript_Chef1::
	msgbox SSAnne_Kitchen_Text_BusyOutOfTheWay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef2::
	msgbox SSAnne_Kitchen_Text_SawOddBerryInTrash, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef3::
	msgbox SSAnne_Kitchen_Text_SoBusyImDizzy, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef4::
	lock
	faceplayer
	msgbox SSAnne_Kitchen_Text_IAmLeChefMainCourseIs
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, SSAnne_Kitchen_EventScript_SalmonDuSalad
	call_if_eq VAR_0x8008, 1, SSAnne_Kitchen_EventScript_EelsAuBarbecue
	call_if_eq VAR_0x8008, 2, SSAnne_Kitchen_EventScript_PrimeBeefsteak
	release
	end

SSAnne_Kitchen_EventScript_SalmonDuSalad::
	msgbox SSAnne_Kitchen_Text_SalmonDuSalad
	return

SSAnne_Kitchen_EventScript_EelsAuBarbecue::
	msgbox SSAnne_Kitchen_Text_EelsAuBarbecue
	return

SSAnne_Kitchen_EventScript_PrimeBeefsteak::
	msgbox SSAnne_Kitchen_Text_PrimeBeefsteak
	return

SSAnne_Kitchen_EventScript_Chef5::
	msgbox SSAnne_Kitchen_Text_PeelSpudsEveryDay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef6::
	msgbox SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef7::
	msgbox SSAnne_Kitchen_Text_OnlyGetToPeelOnions, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_StaticLickitung::
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	setwildbattle SPECIES_LICKITUNG, 29, ITEM_LEFTOVERS
	setvar VAR_0x8004, MOVE_SLAM
	setvar VAR_0x8005, 0
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_DISABLE
	setvar VAR_0x8005, 1
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_DEFENSE_CURL
	setvar VAR_0x8005, 2
	special SetEnemyEventMonMoveSlot
	setvar VAR_0x8004, MOVE_ROLLOUT
	setvar VAR_0x8005, 3
	special SetEnemyEventMonMoveSlot
	waitse
	playmoncry SPECIES_LICKITUNG, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special QuestLog_CutRecording
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SSAnne_Kitchen_EventScript_CompleteStaticLickitung
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SSAnne_Kitchen_EventScript_CompleteStaticLickitung
	release
	end

SSAnne_Kitchen_EventScript_CompleteStaticLickitung::
	setflag FLAG_STATIC_SS_ANNE_LICKITUNG_COMPLETE
	removeobject VAR_LAST_TALKED
	release
	end
