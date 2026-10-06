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

