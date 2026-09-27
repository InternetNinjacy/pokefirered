@ SHARED-001 Apricorn Tree interaction.
@ Result codes mirror enum ApricornTreeInteractionState.
.set APRICORN_TREE_INTERACT_EMPTY, 0
.set APRICORN_TREE_INTERACT_READY, 1
.set APRICORN_TREE_INTERACT_WHITE_BLOCKED, 2
.set APRICORN_TREE_INTERACT_WHITE_RECOVERING, 3
.set APRICORN_TREE_INTERACT_WHITE_FIRST_READY, 4

EventScript_ApricornTree::
	lock
	specialvar VAR_RESULT, ApricornTree_PrepareInteraction
	goto_if_eq VAR_RESULT, APRICORN_TREE_INTERACT_WHITE_BLOCKED, EventScript_ApricornTree_WhiteBlocked
	goto_if_eq VAR_RESULT, APRICORN_TREE_INTERACT_WHITE_RECOVERING, EventScript_ApricornTree_WhiteRecovering
	goto_if_eq VAR_RESULT, APRICORN_TREE_INTERACT_EMPTY, EventScript_ApricornTree_Empty
	goto_if_eq VAR_RESULT, APRICORN_TREE_INTERACT_WHITE_FIRST_READY, EventScript_ApricornTree_WhiteFirstReady
	goto EventScript_ApricornTree_Harvest

EventScript_ApricornTree_WhiteBlocked::
	msgbox Text_ApricornTree_WhiteBlocked
	release
	end

EventScript_ApricornTree_WhiteRecovering::
	msgbox Text_ApricornTree_WhiteRecovering
	release
	end

EventScript_ApricornTree_Empty::
	msgbox Text_ApricornTree_Empty
	release
	end

EventScript_ApricornTree_WhiteFirstReady::
	msgbox Text_ApricornTree_WhiteFirstReady

EventScript_ApricornTree_Harvest::
	applymovement VAR_LAST_TALKED, Movement_ApricornTree_Shake
	waitmovement VAR_LAST_TALKED
	specialvar VAR_RESULT, ApricornTree_Harvest
	goto_if_eq VAR_RESULT, FALSE, EventScript_ApricornTree_BagFull
	bufferitemname STR_VAR_1, VAR_0x8004
	playse SE_SUCCESS
	msgbox Text_ApricornTree_Picked
	release
	end

EventScript_ApricornTree_BagFull::
	msgbox Text_TooBadBagFull
	release
	end

Movement_ApricornTree_Shake::
	jump_in_place_down
	step_end

Text_ApricornTree_Empty::
	.string "There are no APRICORNS growing yet.$"

Text_ApricornTree_WhiteBlocked::
	.string "The tree looks sickly.\p"
	.string "The TOXIC SMOG is keeping anything\n"
	.string "from growing here.$"

Text_ApricornTree_WhiteRecovering::
	.string "The air is clear now.\p"
	.string "The tree looks healthier, but nothing\n"
	.string "has grown yet.$"

Text_ApricornTree_WhiteFirstReady::
	.string "A WHITE APRICORN is growing on the\n"
	.string "tree!$"

Text_ApricornTree_Picked::
	.string "You picked a {STR_VAR_1}!$"
