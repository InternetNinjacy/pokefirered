@ QA-only compiled one-time starter-family Gift claim path.
GiftStarterFamilyQa_EventScript_ClaimFern::
	setvar VAR_0x8000, 0
	goto_if_set FLAG_GIFT_FERN_BULBASAUR_CLAIMED, GiftStarterFamilyQa_EventScript_AlreadyClaimed
	setvar VAR_0x8004, 0
	special GiveSamStarterFamilyGift
	goto_if_eq VAR_RESULT, 2, GiftStarterFamilyQa_EventScript_NoRoom
	setflag FLAG_GIFT_FERN_BULBASAUR_CLAIMED
	setvar VAR_0x8000, 1
	end

GiftStarterFamilyQa_EventScript_AlreadyClaimed::
	setvar VAR_0x8000, 2
	end

GiftStarterFamilyQa_EventScript_NoRoom::
	setvar VAR_0x8000, 3
	end
