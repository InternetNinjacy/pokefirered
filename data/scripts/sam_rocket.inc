@ Ordinary field text pages. Acquisition is independent of evidence storage:
@ operations cleared before Viridian can record approved pages for later reading.
EventScript_Sam_RocketDossier::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	goto_if_eq VAR_SAM_ROCKET_EVIDENCE, 0, SamRocket_EventScript_NoEvidence
	setvar VAR_0x8004, ROCKET_EVIDENCE_DELIVERY_01
	callnative Script_SamRocketCheckEvidence
	call_if_eq VAR_RESULT, TRUE, SamRocket_EventScript_ReadDelivery01
	setvar VAR_0x8004, ROCKET_EVIDENCE_DELIVERY_03
	callnative Script_SamRocketCheckEvidence
	call_if_eq VAR_RESULT, TRUE, SamRocket_EventScript_ReadDelivery03
	setvar VAR_0x8004, ROCKET_EVIDENCE_DELIVERY_04
	callnative Script_SamRocketCheckEvidence
	call_if_eq VAR_RESULT, TRUE, SamRocket_EventScript_ReadDelivery04
	releaseall
	end

SamRocket_EventScript_ReadDelivery01::
	msgbox SamRocket_Text_Delivery01
	return

SamRocket_EventScript_ReadDelivery03::
	msgbox SamRocket_Text_Delivery03
	return

SamRocket_EventScript_ReadDelivery04::
	msgbox SamRocket_Text_Delivery04
	return

SamRocket_Text_Delivery01:
	.string "DELIVERY 01\n"
	.string "VIRIDIAN COLLECTION - RECEIVED\p"
	.string "NORTHBOUND MATERIAL - PENDING\n"
	.string "PEWTER / MT. MOON$"

SamRocket_Text_Delivery03:
	.string "DELIVERY 03\n"
	.string "CERULEAN RECOVERY - FAILED\p"
	.string "TRAINING GOODS - LOST\n"
	.string "LOCAL ACQUISITION CREW\l"
	.string "COMPROMISED$"

SamRocket_Text_Delivery04:
	.string "DELIVERY 04\n"
	.string "CERULEAN RECRUITMENT - FAILED\p"
	.string "SUBJECT: RED\n"
	.string "STATUS - HOSTILE / CAPABLE\p"
	.string "IDENTITY CIRCULATED$"

SamRocket_EventScript_NoEvidence::
	msgbox SamRocket_Text_NoEvidence
	releaseall
	end

SamRocket_Text_NoEvidence:
	.string "No evidence recorded.$"
