from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
macro = (ROOT / "asm/macros.inc").read_text()
pewter = (ROOT / "data/maps/PewterCity_Gym/scripts.inc").read_text()


def pos(text: str, needle: str) -> int:
    p = text.find(needle)
    assert p >= 0, f"missing required source fragment: {needle}"
    return p

# Shared router precedence is canonical and must not drift.
post = pos(macro, "goto_if_set FLAG_SYS_GAME_CLEAR")
leader = pos(macro, "goto_if_set \\leader_flag")
practice = pos(macro, "goto_if_set \\practice_flag")
assert post < leader < practice, "Satoshi router precedence drifted"

# Pewter must consume the shared router rather than open-code a different order.
router_call = "satoshi_route_by_state PewterCity_Gym_EventScript_SatoshiPostgameTextPending, FLAG_BADGE01_GET, PewterCity_Gym_EventScript_SatoshiAfterBoreal, FLAG_SATOSHI_PEWTER_PRACTICE_WON, PewterCity_Gym_EventScript_SatoshiBeforeBoreal"
pos(pewter, router_call)

# Main-story practice completion must mutate only the intended Satoshi bit.
practice_start = pos(pewter, "PewterCity_Gym_EventScript_SatoshiPracticeBattle::")
practice_end = pos(pewter[practice_start:], "PewterCity_Gym_EventScript_SatoshiPracticeLost::") + practice_start
practice_block = pewter[practice_start:practice_end]
assert "setflag FLAG_SATOSHI_PEWTER_PRACTICE_WON" in practice_block
assert practice_block.count("setflag FLAG_SATOSHI_") == 1

# Leader-cleared routing must retain practiced vs skipped distinction.
after_start = pos(pewter, "PewterCity_Gym_EventScript_SatoshiAfterBoreal::")
after_end = pos(pewter[after_start:], "PewterCity_Gym_EventScript_MainSign::") + after_start
after_block = pewter[after_start:after_end]
assert "goto_if_set FLAG_SATOSHI_PEWTER_PRACTICE_WON, PewterCity_Gym_EventScript_SatoshiAfterComplete" in after_block
assert "PewterCity_Gym_Text_SatoshiAfterSkipped" in after_block
assert "PewterCity_Gym_Text_SatoshiAfterComplete" in after_block

# Until literal approved Pewter rematch text is mapped, postgame must supersede
# main-story state but fail safely: no placeholder battle, no flag mutation.
fallback_start = pos(pewter, "PewterCity_Gym_EventScript_SatoshiPostgameTextPending::")
fallback_end = pos(pewter[fallback_start:], "PewterCity_Gym_EventScript_SatoshiPractice::") + fallback_start
fallback = pewter[fallback_start:fallback_end]
assert "trainerbattle" not in fallback
assert "setflag" not in fallback
assert "clearflag" not in fallback
assert "release" in fallback and "end" in fallback

# No Satoshi-specific rematch-complete state is introduced by this packet.
assert "SATOSHI_PEWTER_REMATCH_WON" not in pewter
assert "SATOSHI_PEWTER_REMATCH_COMPLETE" not in pewter

print("Satoshi shared-router focused QA: PASS")
