Route11_MapScripts::
	.byte 0

Route11_EventScript_DiglettsCaveSign::
	msgbox Route11_Text_DiglettsCave, MSGBOX_SIGN
	end


// Batch 4 ordinary-trainer Double Battle entry points. These preserve the
// existing trainer IDs, text, rematch text, and Vs. Seeker behavior while
// applying the settled Route 11 battle formats.
Route11_EventScript_HugoBatch4::
	trainerbattle_double TRAINER_GAMER_HUGO, Route11_Text_HugoIntro, Route11_Text_HugoDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route11_EventScript_HugoBatch4Rematch
	msgbox Route11_Text_HugoPostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_HugoBatch4Rematch::
	trainerbattle_rematch_double TRAINER_GAMER_HUGO, Route11_Text_HugoRematchIntro, Route11_Text_HugoDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route11_Text_HugoPostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_BernieBatch4::
	trainerbattle_double TRAINER_ENGINEER_BERNIE, Route11_Text_BernieIntro, Route11_Text_BernieDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route11_EventScript_BernieBatch4Rematch
	msgbox Route11_Text_BerniePostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_BernieBatch4Rematch::
	trainerbattle_rematch_double TRAINER_ENGINEER_BERNIE, Route11_Text_BernieRematchIntro, Route11_Text_BernieDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route11_Text_BerniePostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_DillonBatch4::
	trainerbattle_double TRAINER_YOUNGSTER_DILLON, Route11_Text_DillonIntro, Route11_Text_DillonDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route11_EventScript_DillonBatch4Rematch
	msgbox Route11_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_DillonBatch4Rematch::
	trainerbattle_rematch_double TRAINER_YOUNGSTER_DILLON, Route11_Text_DillonRematchIntro, Route11_Text_DillonDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route11_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_DirkBatch4::
	trainerbattle_double TRAINER_GAMER_DIRK, Route11_Text_DirkIntro, Route11_Text_DirkDefeat, MtMoon_1F_Text_KentNotEnoughMons
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route11_EventScript_DirkBatch4Rematch
	msgbox Route11_Text_DirkPostBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_DirkBatch4Rematch::
	trainerbattle_rematch_double TRAINER_GAMER_DIRK, Route11_Text_DirkRematchIntro, Route11_Text_DirkDefeat, MtMoon_1F_Text_KentNotEnoughMons
	msgbox Route11_Text_DirkPostBattle, MSGBOX_AUTOCLOSE
	end
