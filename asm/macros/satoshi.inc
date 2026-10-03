	.ifndef SATOSHI_ROUTER_MACROS
	.set SATOSHI_ROUTER_MACROS, 1

	@ Shared Satoshi interaction router.
	@ Priority is intentionally fixed by canon:
	@   1. first-Hall-of-Fame / postgame
	@   2. Gym Leader already defeated
	@   3. this Gym's Satoshi practice already won
	@   4. initial practice offer (fall-through)
	@
	@ The caller owns all player-facing text, trainer records, and battle hooks.
	@ This macro only centralizes branch precedence so Gym scripts cannot drift.
	.macro satoshi_route_by_state postgame_target:req, leader_flag:req, leader_target:req, practice_flag:req, practice_target:req
	goto_if_set FLAG_SYS_GAME_CLEAR, \postgame_target
	goto_if_set \leader_flag, \leader_target
	goto_if_set \practice_flag, \practice_target
	.endm

	.endif
