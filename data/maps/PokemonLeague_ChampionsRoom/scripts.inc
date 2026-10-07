PokemonLeague_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_ChampionsRoom_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_ChampionsRoom_OnFrame
	.byte 0

PokemonLeague_ChampionsRoom_OnResume::
	setvar VAR_0x8004, 4
	call PokemonLeague_EventScript_DoLightingEffect
	call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerCharmander
	end

PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerSquirtle::
	goto_if_defeated TRAINER_CHAMPION_FIRST_SQUIRTLE, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	goto_if_defeated TRAINER_CHAMPION_REMATCH_SQUIRTLE, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	return

PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerBulbasaur::
	goto_if_defeated TRAINER_CHAMPION_FIRST_BULBASAUR, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	goto_if_defeated TRAINER_CHAMPION_REMATCH_BULBASAUR, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	return

PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerCharmander::
	goto_if_defeated TRAINER_CHAMPION_FIRST_CHARMANDER, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	goto_if_defeated TRAINER_CHAMPION_REMATCH_CHARMANDER, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	return

PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger::
	setvar VAR_TEMP_1, 1
	return

PokemonLeague_ChampionsRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_ChampionsRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_ChampionsRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_ChampionsRoom_OnFrame::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

PokemonLeague_ChampionsRoom_EventScript_EnterRoom::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	setflag FLAG_TEMP_2
	applymovement LOCALID_PLAYER, PokemonLeague_ChampionsRoom_Movement_PlayerEnter
	waitmovement 0
	delay 20
	call_if_unset FLAG_SYS_GAME_CLEAR, PokemonLeague_ChampionsRoom_EventScript_Intro
	call_if_set FLAG_SYS_GAME_CLEAR, PokemonLeague_ChampionsRoom_EventScript_RematchIntro
	goto_if_questlog PokemonLeague_ChampionsRoom_EventScript_QuestLogEnd
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	savebgm MUS_VICTORY_GYM_LEADER
	call_if_unset FLAG_SYS_CAN_LINK_WITH_RS, PokemonLeague_ChampionsRoom_EventScript_Battle
	call_if_set FLAG_SYS_CAN_LINK_WITH_RS, PokemonLeague_ChampionsRoom_EventScript_Rematch
	setflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	setflag FLAG_DEFEATED_CHAMP
	setflag FLAG_TEMP_4
	msgbox PokemonLeague_ChampionsRoom_Text_PostBattle
	playbgm MUS_SLOW_PALLET, 0
	addobject LOCALID_CHAMPIONS_ROOM_PROF_OAK
	msgbox PokemonLeague_ChampionsRoom_Text_OakPlayer
	closemessage
	applymovement LOCALID_PLAYER, PokemonLeague_ChampionsRoom_Movement_PlayerWatchOakEnter
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, PokemonLeague_ChampionsRoom_Movement_RivalWatchOakEnter
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, PokemonLeague_ChampionsRoom_Movement_OakEnter
	waitmovement 0
	delay 25
	specialvar VAR_RESULT, GetStarterSpecies
	bufferspeciesname STR_VAR_1, VAR_RESULT
	msgbox PokemonLeague_ChampionsRoom_Text_OakCongratulations
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_OakImDisappointedRival
	closemessage
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 20
	msgbox PokemonLeague_ChampionsRoom_Text_OakPlayerComeWithMe
	closemessage
	delay 13
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, PokemonLeague_ChampionsRoom_Movement_OakExit
	applymovement LOCALID_PLAYER, PokemonLeague_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setvar VAR_TEMP_1, 1
	warp MAP_POKEMON_LEAGUE_HALL_OF_FAME, 5, 12
	waitstate
	releaseall
	end

PokemonLeague_ChampionsRoom_EventScript_QuestLogEnd::
	call PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	releaseall
	end

PokemonLeague_ChampionsRoom_EventScript_Battle::
	call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_BattleSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_BattleBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_BattleCharmander
	return

PokemonLeague_ChampionsRoom_EventScript_Rematch::
	call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_RematchSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_RematchBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_RematchCharmander
	return

PokemonLeague_ChampionsRoom_EventScript_Intro::
	msgbox PokemonLeague_ChampionsRoom_Text_Intro
	return

PokemonLeague_ChampionsRoom_EventScript_RematchIntro::
	msgbox PokemonLeague_ChampionsRoom_Text_RematchIntro
	return

PokemonLeague_ChampionsRoom_EventScript_BattleSquirtle::
	trainerbattle_no_intro TRAINER_CHAMPION_FIRST_SQUIRTLE, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_BattleBulbasaur::
	trainerbattle_no_intro TRAINER_CHAMPION_FIRST_BULBASAUR, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_BattleCharmander::
	trainerbattle_no_intro TRAINER_CHAMPION_FIRST_CHARMANDER, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_RematchSquirtle::
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_SQUIRTLE, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_RematchBulbasaur::
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_BULBASAUR, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_RematchCharmander::
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_CHARMANDER, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_Movement_PlayerEnter::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_ChampionsRoom_Movement_PlayerExit::
	delay_16
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

PokemonLeague_ChampionsRoom_Movement_PlayerWatchOakEnter::
	delay_8
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PokemonLeague_ChampionsRoom_Movement_OakEnter::
	delay_16
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_in_place_faster_down
	delay_16
	step_end

PokemonLeague_ChampionsRoom_Movement_OakExit::
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

PokemonLeague_ChampionsRoom_Movement_RivalWatchOakEnter::
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

@ Pokémon: Sam Edition — Green Champion-owned package.
@ League room/order integration is intentionally left to the League placement chunk.
PokemonLeague_ChampionsRoom_EventScript_GreenFirstBattle::
	goto_if_set FLAG_GREEN_CHAMPION_REVEALED, PokemonLeague_ChampionsRoom_EventScript_GreenRepeatBattle
	setflag FLAG_GREEN_CHAMPION_REVEALED
	playbgm MUS_VS_CHAMPION, 0
	msgbox PokemonLeague_ChampionsRoom_Text_GreenReveal
	goto PokemonLeague_ChampionsRoom_EventScript_GreenChampionBranch

PokemonLeague_ChampionsRoom_EventScript_GreenRepeatBattle::
	playbgm MUS_VS_CHAMPION, 0
	msgbox PokemonLeague_ChampionsRoom_Text_GreenRepeat
	goto PokemonLeague_ChampionsRoom_EventScript_GreenChampionBranch

PokemonLeague_ChampionsRoom_EventScript_GreenChampionBranch::
	goto_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_GreenChampionRaichu
	goto_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_GreenChampionDitto
	goto PokemonLeague_ChampionsRoom_EventScript_GreenChampionEspeon

PokemonLeague_ChampionsRoom_EventScript_GreenChampionDitto::
	trainerbattle_no_intro TRAINER_GREEN_CHAMPION_DITTO, PokemonLeague_ChampionsRoom_Text_GreenDefeat
	goto PokemonLeague_ChampionsRoom_EventScript_GreenChampionWon
PokemonLeague_ChampionsRoom_EventScript_GreenChampionEspeon::
	trainerbattle_no_intro TRAINER_GREEN_CHAMPION_ESPEON, PokemonLeague_ChampionsRoom_Text_GreenDefeat
	goto PokemonLeague_ChampionsRoom_EventScript_GreenChampionWon
PokemonLeague_ChampionsRoom_EventScript_GreenChampionRaichu::
	trainerbattle_no_intro TRAINER_GREEN_CHAMPION_RAICHU, PokemonLeague_ChampionsRoom_Text_GreenDefeat
	goto PokemonLeague_ChampionsRoom_EventScript_GreenChampionWon

PokemonLeague_ChampionsRoom_EventScript_GreenChampionWon::
	msgbox PokemonLeague_ChampionsRoom_Text_GreenPost
	msgbox PokemonLeague_ChampionsRoom_Text_GreenFinal
	return

PokemonLeague_ChampionsRoom_EventScript_GreenTitleChallenge::
	playbgm MUS_VS_CHAMPION, 0
	goto_if_set FLAG_GREEN_TITLE_CHALLENGE_SEEN, PokemonLeague_ChampionsRoom_EventScript_GreenTitleRepeat
	setflag FLAG_GREEN_TITLE_CHALLENGE_SEEN
	msgbox PokemonLeague_ChampionsRoom_Text_GreenTitleFirst
	goto PokemonLeague_ChampionsRoom_EventScript_GreenTitleBranch
PokemonLeague_ChampionsRoom_EventScript_GreenTitleRepeat::
	msgbox PokemonLeague_ChampionsRoom_Text_GreenTitleRepeat
PokemonLeague_ChampionsRoom_EventScript_GreenTitleBranch::
	goto_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_GreenTitleRaichu
	goto_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_GreenTitleDitto
	goto PokemonLeague_ChampionsRoom_EventScript_GreenTitleEspeon
PokemonLeague_ChampionsRoom_EventScript_GreenTitleDitto::
	trainerbattle_no_intro TRAINER_GREEN_POSTGAME_DITTO, PokemonLeague_ChampionsRoom_Text_GreenTitleDefeat
	return
PokemonLeague_ChampionsRoom_EventScript_GreenTitleEspeon::
	trainerbattle_no_intro TRAINER_GREEN_POSTGAME_ESPEON, PokemonLeague_ChampionsRoom_Text_GreenTitleDefeat
	return
PokemonLeague_ChampionsRoom_EventScript_GreenTitleRaichu::
	trainerbattle_no_intro TRAINER_GREEN_POSTGAME_RAICHU, PokemonLeague_ChampionsRoom_Text_GreenTitleDefeat
	return

PokemonLeague_ChampionsRoom_Text_GreenReveal::
	.string "{PLAYER}?\p"
	.string "You made it.\p"
	.string "...Good. I was really hoping you\n"
	.string "would.\p"
	.string "I couldn't tell you what I was\n"
	.string "doing. {RIVAL} couldn't either.\p"
	.string "You've been helping me build this\n"
	.string "team almost the whole way here,\l"
	.string "whether you knew it or not.\p"
	.string "Every time you found a weakness, I\n"
	.string "fixed it. Every time you surprised\l"
	.string "me, I learned something.\p"
	.string "Eventually I stopped looking for\n"
	.string "different POKéMON. I had the right\l"
	.string "six. I just needed to get better\l"
	.string "at using them.\p"
	.string "And I got here first.\p"
	.string "So if you want to be CHAMPION...\n"
	.string "you have to beat the team you\l"
	.string "helped me build.\p"
	.string "No more tests, {PLAYER}.\p"
	.string "This one counts.$"

PokemonLeague_ChampionsRoom_Text_GreenRepeat::
	.string "Back again. Good. Neither of us\n"
	.string "needs another speech. Show me what\l"
	.string "you changed.$"

PokemonLeague_ChampionsRoom_Text_GreenDefeat::
	.string "...You did it.$"

PokemonLeague_ChampionsRoom_Text_GreenPost::
	.string "I kept trying to build a team with\n"
	.string "no weak points.\p"
	.string "But there's always another decision.\n"
	.string "Another switch. Another move you\l"
	.string "could have made instead.\p"
	.string "Today, you made the better ones.\p"
	.string "And after everything we've thrown\n"
	.string "at each other...\p"
	.string "I think this is exactly how it\n"
	.string "should end.\p"
	.string "Congratulations, {PLAYER}.\p"
	.string "You're the CHAMPION.$"

PokemonLeague_ChampionsRoom_Text_GreenFinal::
	.string "Go on. You earned this.$"

PokemonLeague_ChampionsRoom_Text_GreenTitleFirst::
	.string "There you are.\p"
	.string "I was hoping you'd make another run\n"
	.string "through the LEAGUE.\p"
	.string "You're still the CHAMPION. I haven't\n"
	.string "forgotten.\p"
	.string "But I've had a lot of time to think\n"
	.string "about our last battle.\p"
	.string "And now that I finally caught you\n"
	.string "here...\p"
	.string "I want another shot at the title.\p"
	.string "CHAMPION versus challenger.\p"
	.string "Ready, {PLAYER}?$"

PokemonLeague_ChampionsRoom_Text_GreenTitleRepeat::
	.string "Back again? Good.\p"
	.string "You know what I want.\p"
	.string "Put the title on the line.$"

PokemonLeague_ChampionsRoom_Text_GreenTitleDefeat::
	.string "Still yours.\p"
	.string "...I'm getting closer, though.$"
