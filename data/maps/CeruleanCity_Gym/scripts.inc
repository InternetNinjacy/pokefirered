.equ LOCALID_FROSTFALL_MARA,      1
.equ LOCALID_FROSTFALL_HOLT,      2
.equ LOCALID_FROSTFALL_KUKIK,     3
.equ LOCALID_FROSTFALL_GYM_GUIDE, 4
.equ LOCALID_FROSTFALL_TAVI,      5

CeruleanCity_Gym_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CeruleanCity_Gym_OnLoad
    .byte 0

CeruleanCity_Gym_OnLoad::
    checktrainerflag TRAINER_COOLTRAINER_MARA
    call_if_eq TRUE, CeruleanCity_Gym_EventScript_SetMaraDefeatedPosition
    checktrainerflag TRAINER_HIKER_HOLT
    call_if_eq TRUE, CeruleanCity_Gym_EventScript_SetHoltDefeatedPosition
    checktrainerflag TRAINER_SNOWBOARDER_TAVI
    call_if_eq TRUE, CeruleanCity_Gym_EventScript_SetTaviDefeatedPosition
    end

CeruleanCity_Gym_EventScript_SetMaraDefeatedPosition::
    setobjectxyperm LOCALID_FROSTFALL_MARA, 7, 14
    return

CeruleanCity_Gym_EventScript_SetHoltDefeatedPosition::
    setobjectxyperm LOCALID_FROSTFALL_HOLT, 9, 11
    return

CeruleanCity_Gym_EventScript_SetTaviDefeatedPosition::
    setobjectxyperm LOCALID_FROSTFALL_TAVI, 7, 8
    return

@ Legacy label retained for source compatibility.
CeruleanCity_Gym_EventScript_Misty::
CeruleanCity_Gym_EventScript_Kukik::
    trainerbattle_single TRAINER_LEADER_KUKIK, CeruleanCity_Gym_Text_KukikIntro, CeruleanCity_Gym_Text_KukikDefeat, CeruleanCity_Gym_EventScript_KukikDefeated, NO_MUSIC
    goto CeruleanCity_Gym_EventScript_KukikPostClear
    end

CeruleanCity_Gym_EventScript_KukikDefeated::
    setflag FLAG_DEFEATED_KUKIK
    setflag FLAG_BADGE02_ENDURANCE
    setrespawn HEAL_LOCATION_CERULEAN_CITY
    set_gym_trainers 3
    msgbox CeruleanCity_Gym_Text_KukikBadgeReward
    playfanfare MUS_OBTAIN_BADGE
    waitfanfare
    @ TM26 Icy Wind delivery is intentionally deferred until the Weather TM
    @ item-numbering/teaching expansion is merged. FLAG_GOT_TM26_FROM_KUKIK
    @ is reserved separately so Badge ownership can never duplicate.
    msgbox CeruleanCity_Gym_Text_KukikFirstClearFinal
    release
    end

CeruleanCity_Gym_EventScript_KukikPostClear::
    msgbox CeruleanCity_Gym_Text_KukikPostClear
    release
    end

@ Legacy label retained for source compatibility.
CeruleanCity_Gym_EventScript_Diana::
CeruleanCity_Gym_EventScript_Mara::
    trainerbattle_single TRAINER_COOLTRAINER_MARA, CeruleanCity_Gym_Text_MaraIntro, CeruleanCity_Gym_Text_MaraDefeat, CeruleanCity_Gym_EventScript_MaraDefeated
    msgbox CeruleanCity_Gym_Text_MaraPost, MSGBOX_AUTOCLOSE
    end

CeruleanCity_Gym_EventScript_MaraDefeated::
    applymovement LOCALID_FROSTFALL_MARA, CeruleanCity_Gym_Movement_MaraStepAside
    waitmovement 0
    copyobjectxytoperm LOCALID_FROSTFALL_MARA
    msgbox CeruleanCity_Gym_Text_MaraPost, MSGBOX_AUTOCLOSE
    end

CeruleanCity_Gym_Movement_MaraStepAside::
    walk_left
    step_end

@ Legacy label retained for source compatibility.
CeruleanCity_Gym_EventScript_Luis::
CeruleanCity_Gym_EventScript_Holt::
    trainerbattle_single TRAINER_HIKER_HOLT, CeruleanCity_Gym_Text_HoltIntro, CeruleanCity_Gym_Text_HoltDefeat, CeruleanCity_Gym_EventScript_HoltDefeated
    msgbox CeruleanCity_Gym_Text_HoltPost, MSGBOX_AUTOCLOSE
    end

CeruleanCity_Gym_EventScript_HoltDefeated::
    applymovement LOCALID_FROSTFALL_HOLT, CeruleanCity_Gym_Movement_HoltStepAside
    waitmovement 0
    copyobjectxytoperm LOCALID_FROSTFALL_HOLT
    msgbox CeruleanCity_Gym_Text_HoltPost, MSGBOX_AUTOCLOSE
    end

CeruleanCity_Gym_Movement_HoltStepAside::
    walk_right
    step_end

CeruleanCity_Gym_EventScript_Tavi::
    trainerbattle_single TRAINER_SNOWBOARDER_TAVI, CeruleanCity_Gym_Text_TaviIntro, CeruleanCity_Gym_Text_TaviDefeat, CeruleanCity_Gym_EventScript_TaviDefeated
    msgbox CeruleanCity_Gym_Text_TaviPost, MSGBOX_AUTOCLOSE
    end

CeruleanCity_Gym_EventScript_TaviDefeated::
    applymovement LOCALID_FROSTFALL_TAVI, CeruleanCity_Gym_Movement_TaviStepAside
    waitmovement 0
    copyobjectxytoperm LOCALID_FROSTFALL_TAVI
    msgbox CeruleanCity_Gym_Text_TaviPost, MSGBOX_AUTOCLOSE
    end

CeruleanCity_Gym_Movement_TaviStepAside::
    walk_left
    step_end

CeruleanCity_Gym_EventScript_GymGuy::
    lock
    faceplayer
    goto_if_set FLAG_DEFEATED_KUKIK, CeruleanCity_Gym_EventScript_GymGuyPostVictory
    msgbox CeruleanCity_Gym_Text_GymGuidePre
    release
    end

CeruleanCity_Gym_EventScript_GymGuyPostVictory::
    msgbox CeruleanCity_Gym_Text_GymGuidePost
    release
    end

CeruleanCity_Gym_EventScript_GymStatue::
CeruleanCity_Gym_EventScript_GymSign::
    lockall
    msgbox CeruleanCity_Gym_Text_GymSign
    releaseall
    end
