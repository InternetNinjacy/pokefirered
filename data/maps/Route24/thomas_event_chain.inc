@ Pokémon: Sam Edition — Thomas recurring-rival event-chain hooks.
@ These labels hold the locked narrative beats and persistent stage transitions.
@ Map-object placement and trainerbattle bindings are wired separately so RIV-011
@ trainer records can land without duplicating dialogue/state logic.

Thomas_EventScript_NuggetPreBattle::
	msgbox Thomas_Text_NuggetIntro
	msgbox Thomas_Text_NuggetRecruitment
	return

Thomas_EventScript_NuggetPostBattle::
	msgbox Thomas_Text_NuggetDefeat
	call EventScript_ThomasSetRecruited
	return

Thomas_EventScript_CeladonPreBattle::
	msgbox Thomas_Text_CeladonIntro
	return

Thomas_EventScript_CeladonPostBattle::
	msgbox Thomas_Text_CeladonDefeat
	call EventScript_ThomasSetCeladonCleared
	return

Thomas_EventScript_LavenderPreBattle::
	msgbox Thomas_Text_LavenderIntro
	return

Thomas_EventScript_LavenderPostBattle::
	msgbox Thomas_Text_LavenderDefeat
	call EventScript_ThomasSetLavenderCleared
	return

Thomas_EventScript_SilphPreBattle::
	msgbox Thomas_Text_SilphOwenScene
	msgbox Thomas_Text_SilphIntro
	return

Thomas_EventScript_SilphPostBattle::
	msgbox Thomas_Text_SilphDefeat
	call EventScript_ThomasSetSilphCleared
	return

Thomas_EventScript_CinnabarPreBattle::
	msgbox Thomas_Text_CinnabarOrders
	msgbox Thomas_Text_CinnabarIntro
	return

Thomas_EventScript_CinnabarPostBattle::
	msgbox Thomas_Text_CinnabarDefeat
	call EventScript_ThomasSetCinnabarCleared
	return

Thomas_EventScript_ViridianPreBattle::
	msgbox Thomas_Text_ViridianIntro
	return

Thomas_EventScript_ViridianPostBattle::
	msgbox Thomas_Text_ViridianDefeat
	call EventScript_ThomasSetQuitRocket
	return

Thomas_Text_NuggetIntro::
	.string "You cleared all five? Nice.\n"
	.string "I'm THOMAS.$"

Thomas_Text_NuggetRecruitment::
	.string "Does it pay?\p"
	.string "...How steady?\p"
	.string "Then I'm in.\p"
	.string "Sorry, RED. Someone back home is\n"
	.string "counting on me. I need this.$"

Thomas_Text_NuggetDefeat::
	.string "...Damn. You didn't do anything\n"
	.string "wrong. I really needed this job.\p"
	.string "No hard feelings, RED.$"

Thomas_Text_CeladonIntro::
	.string "...RED? Guess I should've known\n"
	.string "you'd end up here.\p"
	.string "Yeah. I took the job.\p"
	.string "They pay me. Regularly. Turns out\n"
	.string "that matters more than pride.\p"
	.string "Someone back home is really sick.\n"
	.string "Treatment costs money.\p"
	.string "ROCKET pays better than battling\n"
	.string "strangers on bridges.\p"
	.string "I'm working right now. If you want\n"
	.string "through, you go through me.$"

Thomas_Text_CeladonDefeat::
	.string "...Again. You're becoming a real\n"
	.string "problem for me, RED.\p"
	.string "But I still get paid. That's the\n"
	.string "difference.\p"
	.string "Maybe I'm making a mistake. But\n"
	.string "the bills are getting paid.$"

Thomas_Text_LavenderIntro::
	.string "RED. Of course it's you.\p"
	.string "Don't. I know what you're thinking.\p"
	.string "FUJI had POKéMON. ROCKET needed\n"
	.string "one. I took it.\p"
	.string "You want to know why I'm still\n"
	.string "doing this? It's my little sister.\p"
	.string "She's sick. Really sick. Every\n"
	.string "treatment costs more money than my\n"
	.string "family has ever seen.\p"
	.string "If stealing one POKéMON buys\n"
	.string "another week of treatment, then\n"
	.string "yeah. I'll steal the POKéMON.\p"
	.string "Move, RED. Or battle me.$"

Thomas_Text_LavenderDefeat::
	.string "...Damn it.\p"
	.string "You get to travel, battle, collect\n"
	.string "BADGES. If you lose, you try again\n"
	.string "tomorrow.\p"
	.string "When I lose, somebody at home still\n"
	.string "needs medicine.\p"
	.string "Go be the hero. Just don't pretend\n"
	.string "everybody gets to live like you do.$"

Thomas_Text_SilphOwenScene::
	.string "OWEN: Please... MAGNEMITE has been\n"
	.string "with me for years.\p"
	.string "THOMAS: Hand over the BALL.\p"
	.string "OWEN: ...\p"
	.string "THOMAS: Now.$"

Thomas_Text_SilphIntro::
	.string "...You've got incredible timing.\p"
	.string "Yeah. It was his. Now it's mine.\p"
	.string "My sister has cancer. She's been\n"
	.string "getting chemotherapy for months.\p"
	.string "Do you know what that costs? My\n"
	.string "family barely had money to keep the\n"
	.string "lights on.\p"
	.string "But she's still getting treatment\n"
	.string "because I'm here.\p"
	.string "She keeps asking where the money\n"
	.string "comes from. I think she knows.\p"
	.string "And no, I'm not stopping because\n"
	.string "she might hate me. Being angry\n"
	.string "requires being alive.\p"
	.string "You want through? Earn it.$"

Thomas_Text_SilphDefeat::
	.string "...Again. Every time.\p"
	.string "Fine. Maybe I can't beat you yet.\p"
	.string "But I can get stronger a lot faster\n"
	.string "than you think.\p"
	.string "Go play hero. I've got work to do.$"

Thomas_Text_CinnabarOrders::
	.string "Notes first. Storage media gets\n"
	.string "packed. Chemicals only if they're\n"
	.string "sealed.\p"
	.string "GIOVANNI wants useful material, not\n"
	.string "broken glass.$"

Thomas_Text_CinnabarIntro::
	.string "...Of course. If there's a locked\n"
	.string "door anywhere in KANTO, eventually\n"
	.string "you come through it.\p"
	.string "You want the good news? My sister\n"
	.string "lived. The treatment worked.\p"
	.string "She's going to be okay. She knows\n"
	.string "about ROCKET now. About what I've\n"
	.string "done. She won't speak to me.\p"
	.string "And I'd do it again. She can hate\n"
	.string "me for sixty years if it means she\n"
	.string "gets those sixty years.\p"
	.string "That part was worth it.\p"
	.string "You kept beating me, so I stopped\n"
	.string "waiting to get stronger the slow\n"
	.string "way.\p"
	.string "The scientists warned me. They told\n"
	.string "me accelerating it would hurt.\p"
	.string "I told them to finish.\p"
	.string "Almost strong enough gets you\n"
	.string "nothing.\p"
	.string "Come on, RED. Let's see if it was\n"
	.string "enough.$"

Thomas_Text_CinnabarDefeat::
	.string "...How? After everything... how am\n"
	.string "I still losing to you?\p"
	.string "She won't even talk to me. I saved\n"
	.string "her, and she won't even look at me.\p"
	.string "No. Doesn't matter.\p"
	.string "GIOVANNI still trusts me. I'm good\n"
	.string "at this.\p"
	.string "Next time, RED. Next time I don't\n"
	.string "lose.$"

Thomas_Text_ViridianIntro::
	.string "Knew you'd make it here eventually.\p"
	.string "GIOVANNI's ahead. And yeah-he's the\n"
	.string "GYM LEADER too. TEAM ROCKET's boss\n"
	.string "and VIRIDIAN's LEADER. Same man.\p"
	.string "But you're not getting to him yet.\n"
	.string "You and me have something to finish.\p"
	.string "My sister lived. That was all I\n"
	.string "wanted.\p"
	.string "I fought for money because she\n"
	.string "needed treatment. I joined ROCKET\n"
	.string "because I couldn't make enough any\n"
	.string "other way.\p"
	.string "And somehow you were always there.\n"
	.string "NUGGET BRIDGE. CELADON. LAVENDER.\n"
	.string "SILPH. CINNABAR.\p"
	.string "I kept my sister alive. And now she\n"
	.string "won't even speak to me.\p"
	.string "She thinks I became a monster.\n"
	.string "Maybe you do too.\p"
	.string "Fine. She's alive enough to hate me.\n"
	.string "I'd make that trade again.\p"
	.string "You want GIOVANNI? You go through\n"
	.string "me.$"

Thomas_Text_ViridianDefeat::
	.string "...No. Not again.\p"
	.string "I did everything. I got stronger. I\n"
	.string "got money. I did whatever ROCKET\n"
	.string "asked.\p"
	.string "I took POKéMON. Hurt people. I even\n"
	.string "did that to SALAMENCE...\p"
	.string "But she was already safe. She was\n"
	.string "already getting better. And I kept\n"
	.string "going.\p"
	.string "Joining ROCKET... I can still tell\n"
	.string "myself I did that for her.\p"
	.string "But everything after? That wasn't\n"
	.string "for her. That was me.\p"
	.string "GIOVANNI's still in there. ROCKET's\n"
	.string "still here. None of that changes\n"
	.string "because I lost.\p"
	.string "But I'm done. I'm not a ROCKET\n"
	.string "anymore.\p"
	.string "I'm turning myself in. Whatever\n"
	.string "happens after that... I earned it.$"
