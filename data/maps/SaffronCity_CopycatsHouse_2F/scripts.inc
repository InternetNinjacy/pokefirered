@ QUEST-010 persistent state model.
@ Reuses the centrally allocated Saffron quest variable and completion flag.
@ Bits 0-2 independently record submitted species so submission order is arbitrary.
@ Bit 3 records that the quest has started. Bit 4 records reward-pending state.
@ Completion is FLAG_SQ_SAFFRON_COMPLETE; no additional persistent storage is allocated.
.set VAR_SQ_SAFFRON_STATE,              VAR_SQ_SAFFRON_COUNT
.set SQ_SAFFRON_SUBMITTED_PIDGEY,       0x0001
.set SQ_SAFFRON_SUBMITTED_RATTATA,      0x0002
.set SQ_SAFFRON_SUBMITTED_ODDISH,       0x0004
.set SQ_SAFFRON_SUBMISSION_MASK,        0x0007
.set SQ_SAFFRON_STARTED_BIT,            0x0008
.set SQ_SAFFRON_REWARD_PENDING_BIT,     0x0010
.set SQ_SAFFRON_STATE_NOT_STARTED,      0x0000
.set SQ_SAFFRON_STATE_STARTED,          0x0008
.set SQ_SAFFRON_STATE_PIDGEY,           0x0009
.set SQ_SAFFRON_STATE_RATTATA,          0x000A
.set SQ_SAFFRON_STATE_PIDGEY_RATTATA,   0x000B
.set SQ_SAFFRON_STATE_ODDISH,           0x000C
.set SQ_SAFFRON_STATE_PIDGEY_ODDISH,    0x000D
.set SQ_SAFFRON_STATE_RATTATA_ODDISH,   0x000E
.set SQ_SAFFRON_STATE_ALL_SUBMITTED,    0x000F
.set SQ_SAFFRON_STATE_REWARD_PENDING,   0x001F

SaffronCity_CopycatsHouse_2F_MapScripts::
	.byte 0

SaffronCity_CopycatsHouse_2F_EventScript_Doduo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DODUO, CRY_MODE_NORMAL
	msgbox SaffronCity_CopycatsHouse_2F_Text_Doduo
	waitmoncry
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Doll::
	lock
	msgbox SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Copycat::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	checkitem ITEM_POKE_DOLL
	goto_if_eq VAR_RESULT, TRUE, EventScript_MimicTutor
	checkplayergender
	call_if_eq VAR_RESULT, MALE, SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerMale
	call_if_eq VAR_RESULT, FEMALE, SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerFemale
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerMale::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyMale
	return

SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerFemale::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyFemale
	return

SaffronCity_CopycatsHouse_2F_EventScript_Computer::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MySecrets, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_EventScript_Game::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket, MSGBOX_SIGN
	end
