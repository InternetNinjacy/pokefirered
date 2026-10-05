CinnabarIsland_Text_DoorIsLocked::
    .string "The door is locked…$"

CinnabarIsland_Text_BlaineLivedHereSinceBeforeLab::
    .string "CINNABAR GYM's BLAINE is quite the\n"
    .string "odd fellow.\p"
    .string "He's lived on the island since way\n"
    .string "before the LAB was built.$"

CinnabarIsland_Text_ScientistsExperimentInMansion::
    .string "Scientists conduct experiments \n"
    .string "in the burned-out building.\p"
    .string "You know, the one they call the\n"
    .string "POKéMON MANSION.$"

CinnabarIsland_Text_FieldResearchFoundSampleCase::
    .string "Wedged against the rock is a battered\n"
    .string "SAMPLE CASE.\p"
    .string "You recovered the SAMPLE CASE!$"

CinnabarIsland_Text_FieldResearchFoundNotebook::
    .string "A soaked FIELD NOTEBOOK is caught\n"
    .string "between the rocks.\p"
    .string "You recovered the FIELD NOTEBOOK!$"

CinnabarIsland_Text_FieldResearchTentacruelAppears::
    .string "The GEOLOGY KIT is visible beneath\n"
    .string "the water…\p"
    .string "A TENTACRUEL surges up beside it!$"

CinnabarIsland_Text_FieldResearchTentacruelCleared::
    .string "TENTACRUEL has cleared away from\n"
    .string "the equipment.$"

CinnabarIsland_Text_FieldResearchFoundGeologyKit::
    .string "You pull the GEOLOGY KIT free from\n"
    .string "the rocks.\p"
    .string "You recovered the GEOLOGY KIT!$"

CinnabarIsland_Text_FieldResearchAllRecovered::
    .string "That's all three pieces of field\n"
    .string "equipment.\p"
    .string "Return them to the geology student\n"
    .string "at the POKéMON LAB.$"

CinnabarIsland_Text_FieldResearchInactiveSpot::
    .string "Sea spray breaks against the rock.\n"
    .string "Nothing here concerns you yet.$"

CinnabarIsland_Text_FieldResearchEmptySpot::
    .string "You've already searched this spot.\n"
    .string "There's nothing else here.$"

CinnabarIsland_Text_IslandSign::
    .string "CINNABAR ISLAND\n"
    .string "The Fiery Town of Burning Desire$"

CinnabarIsland_Text_PokemonLab::
    .string "POKéMON LAB$"

CinnabarIsland_Text_GymSign::
    .string "CINNABAR ISLAND POKéMON GYM\n"
    .string "LEADER: BLAINE\l"
    .string "The Hotheaded Quiz Master!$"

CinnabarIsland_Text_HeyIfItIsntPlayer::
    .string "Huh?\n"
    .string "Hey, if it isn't {PLAYER}!$"

CinnabarIsland_Text_ComeWithMeToOneIsland::
    .string "Look, it's me, BILL.\n"
    .string "Long time no see!\p"
    .string "I hope you're still using my\n"
    .string "PC system.\p"
    .string "Well, listen, since we met up here,\n"
    .string "how about spending time with me?\p"
    .string "There's this little island in the far\n"
    .string "south called ONE ISLAND.\p"
    .string "A friend invited me, so I'm on my\n"
    .string "way out there.\p"
    .string "How about it?\n"
    .string "Do you feel like coming with me?$"

CinnabarIsland_Text_AllRightLetsGo::
    .string "All right, then.\n"
    .string "Let's go!$"

CinnabarIsland_Text_IllBeWaitingInPokeCenter::
    .string "What, are you too busy?\p"
    .string "Well, all right.\n"
    .string "The boat hasn't arrived yet anyway.\p"
    .string "I'll be waiting at the POKéMON\n"
    .string "CENTER over there.\p"
    .string "Come see me when you're done with\n"
    .string "your business here.$"

CinnabarIsland_Text_MyPalsBoatArrived::
    .string "Looks like my pal's boat arrived,\n"
    .string "too.\p"
    .string "He sent it specially here to\n"
    .string "CINNABAR to pick me up.$"

CinnabarIsland_Text_IfYouHaveTriPassYouCanGoAgain::
    .string "Hey, wasn't that a long cruise?\p"
    .string "My buddy CELIO seemed to enjoy\n"
    .string "your company.\p"
    .string "I'm sure he'd welcome you if you\n"
    .string "were to visit him again.\p"
    .string "If you have a TRI-PASS, you can\n"
    .string "always take a ferry there from\l"
    .string "VERMILION PORT.\p"
    .string "All right, thanks for your company!$"

CinnabarIsland_Text_BlueIntro::
    .string "{RIVAL}: {PLAYER}!\p"
    .string "DUDE! CINNABAR!\p"
    .string "There's a volcano! There's a giant\n"
    .string "creepy mansion!\p"
    .string "There's a LAB where they bring\n"
    .string "fossils back to life!\p"
    .string "This island is RADICAL!\p"
    .string "Oh! And my team's gotten CRAZY\n"
    .string "strong.\p"
    .string "You HAVE to battle me.\p"
    .string "LET'S GOOOOOO!$"

CinnabarIsland_Text_BlueDefeat::
    .string "HAHAHA!\p"
    .string "YES!\p"
    .string "THAT was a battle!$"

CinnabarIsland_Text_BlueVictory::
    .string "LET'S GOOOOOO!\p"
    .string "Dude, that was AWESOME!\p"
    .string "We're getting SO strong!$"

CinnabarIsland_Text_BluePostBattle::
    .string "Man... every time I think I've\n"
    .string "caught up, you do THAT.\p"
    .string "This is great.\p"
    .string "Now I've gotta get even stronger!$"

CinnabarIsland_EventScript_BlueTrigger::
    lockall
    setvar VAR_TEMP_3, 0
    call_if_eq VAR_STARTER_MON, 0, CinnabarIsland_EventScript_CheckBlueWater
    call_if_eq VAR_STARTER_MON, 1, CinnabarIsland_EventScript_CheckBlueFire
    call_if_eq VAR_STARTER_MON, 2, CinnabarIsland_EventScript_CheckBlueElectric
    goto_if_eq VAR_TEMP_3, 1, CinnabarIsland_EventScript_BlueBegin
    releaseall
    end

CinnabarIsland_EventScript_CheckBlueWater::
    checktrainerflag TRAINER_BLUE_ROUTE10_WATER
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_RIVAL_SILPH_SQUIRTLE
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_BLUE_CINNABAR_WATER
    goto_if TRUE, CinnabarIsland_EventScript_BlueCheckDone
    setvar VAR_TEMP_3, 1
CinnabarIsland_EventScript_BlueCheckDone::
    return

CinnabarIsland_EventScript_CheckBlueElectric::
    checktrainerflag TRAINER_BLUE_ROUTE10_ELECTRIC
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_RIVAL_SILPH_BULBASAUR
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_BLUE_CINNABAR_ELECTRIC
    goto_if TRUE, CinnabarIsland_EventScript_BlueCheckDone
    setvar VAR_TEMP_3, 1
    return

CinnabarIsland_EventScript_CheckBlueFire::
    checktrainerflag TRAINER_BLUE_ROUTE10_FIRE
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_RIVAL_SILPH_CHARMANDER
    goto_if FALSE, CinnabarIsland_EventScript_BlueCheckDone
    checktrainerflag TRAINER_BLUE_CINNABAR_FIRE
    goto_if TRUE, CinnabarIsland_EventScript_BlueCheckDone
    setvar VAR_TEMP_3, 1
    return

CinnabarIsland_EventScript_BlueBegin::
    addobject LOCALID_CINNABAR_BLUE
    setvar VAR_LAST_TALKED, LOCALID_CINNABAR_BLUE
    textcolor NPC_TEXT_COLOR_MALE
    playbgm MUS_ENCOUNTER_RIVAL, 0
    faceplayer
    msgbox CinnabarIsland_Text_BlueIntro
    call_if_eq VAR_STARTER_MON, 0, CinnabarIsland_EventScript_BlueWater
    call_if_eq VAR_STARTER_MON, 1, CinnabarIsland_EventScript_BlueFire
    call_if_eq VAR_STARTER_MON, 2, CinnabarIsland_EventScript_BlueElectric
    msgbox CinnabarIsland_Text_BluePostBattle
    closemessage
    fadedefaultbgm
    removeobject LOCALID_CINNABAR_BLUE
    setvar VAR_TEMP_3, 2
    releaseall
    end

CinnabarIsland_EventScript_BlueWater::
    trainerbattle_no_intro TRAINER_BLUE_CINNABAR_WATER, CinnabarIsland_Text_BlueDefeat
    return

CinnabarIsland_EventScript_BlueElectric::
    trainerbattle_no_intro TRAINER_BLUE_CINNABAR_ELECTRIC, CinnabarIsland_Text_BlueDefeat
    return

CinnabarIsland_EventScript_BlueFire::
    trainerbattle_no_intro TRAINER_BLUE_CINNABAR_FIRE, CinnabarIsland_Text_BlueDefeat
    return

