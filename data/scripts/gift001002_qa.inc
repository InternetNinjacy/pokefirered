@ QA-only compiled event script for GIFT-002 end-to-end persistence coverage.
@ Uses a real persistent flag and the production givepreownedmononce macro.

Gift001002Qa_EventScript_ClaimBulbasaur::
	setvar VAR_0x8000, 0
	givepreownedmononce SPECIES_BULBASAUR, 10, Gift001002Qa_Text_FernOtName, 52001, FEMALE, FLAG_GOT_LAPRAS_FROM_SILPH, Gift001002Qa_EventScript_AlreadyClaimed, Gift001002Qa_EventScript_NoRoom, ITEM_MIRACLE_SEED
	setvar VAR_0x8000, 1
	end

Gift001002Qa_EventScript_AlreadyClaimed::
	setvar VAR_0x8000, 2
	end

Gift001002Qa_EventScript_NoRoom::
	setvar VAR_0x8000, 3
	end

Gift001002Qa_Text_FernOtName::
	.string "FERN$"
