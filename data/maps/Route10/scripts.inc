Route10_MapScripts::
	.byte 0

Route10_EventScript_Unused::
	end

Route10_EventScript_NorthRockTunnelSign::
	msgbox Route10_Text_RockTunnelDetourToLavender, MSGBOX_SIGN
	end

Route10_EventScript_SouthRockTunnelSign::
	msgbox Route10_Text_RockTunnel, MSGBOX_SIGN
	end

Route10_EventScript_PowerPlantSign::
	msgbox Route10_Text_PowerPlant, MSGBOX_SIGN
	end

// Batch 5: the sole settled Route 10 approach trainer is a Double Battle.
Route10_EventScript_HeidiBatch5::
	trainerbattle_double TRAINER_PICNICKER_HEIDI, Route10_Text_HeidiIntro, Route10_Text_HeidiDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route10_EventScript_HeidiBatch5Rematch
	msgbox Route10_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
	end

Route10_EventScript_HeidiBatch5Rematch::
	trainerbattle_rematch_double TRAINER_PICNICKER_HEIDI, Route10_Text_HeidiRematchIntro, Route10_Text_HeidiDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route10_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
	end

