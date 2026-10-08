#!/usr/bin/env python3
"""Regression for the locked Sam starter-to-rivals Oak Lab contract."""
from pathlib import Path
import re

root=Path(__file__).resolve().parents[1]
script=(root/"data/maps/PalletTown_ProfessorOaksLab/scripts.inc").read_text()
text=(root/"data/maps/PalletTown_ProfessorOaksLab/text.inc").read_text()
expected=[
 ("BulbasaurBall",0,"EEVEE","DITTO","LOCALID_CHARMANDER_BALL","OakChoosingBulbasaur"),
 ("SquirtleBall",1,"PICHU","EEVEE","LOCALID_BULBASAUR_BALL","OakChoosingSquirtle"),
 ("CharmanderBall",2,"DITTO","PICHU","LOCALID_SQUIRTLE_BALL","OakChoosingCharmander"),
]
for label,slot,player,blue,blueball,dialogue in expected:
    start=script.index("PalletTown_ProfessorOaksLab_EventScript_"+label+"::")
    block=script[start:script.index("\n\n",start)]
    assert f"setvar PLAYER_STARTER_NUM, {slot}" in block
    assert f"setvar PLAYER_STARTER_SPECIES, SPECIES_{player}" in block
    assert f"setvar RIVAL_STARTER_SPECIES, SPECIES_{blue}" in block
    assert f"setvar RIVAL_STARTER_ID, {blueball}" in block
    tag="PalletTown_ProfessorOaksLab_Text_"+dialogue+"::"
    start=text.index(tag)
    content=text[start:text.index("\n\n",start)]
    assert player in content and all(old not in content for old in ("BULBASAUR","SQUIRTLE","CHARMANDER"))
assert "givemon PLAYER_STARTER_SPECIES, 5" in script
assert "special MarkSamOriginalStarter" in script
assert "copyvar VAR_STARTER_MON, PLAYER_STARTER_NUM" in script
for slot,green in ((0,"Raichu"),(1,"Ditto"),(2,"Espeon")):
    assert "PalletTown_ProfessorOaksLab_EventScript_GreenOak"+green+"::" in script
print("PASS: starter award, Blue/Green mapping indices, confirmation text, and identity mark")
