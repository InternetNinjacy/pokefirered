#include "global.h"
#include "characters.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "new_game.h"
#include "save.h"
#include "constants/vars.h"

#define ARCH002_STAGE_A 0xA1
#define ARCH002_STAGE_B 0xB2

static bool8 BytesAreZero(const u8 *data, u32 size)
{
    u32 i;
    for (i = 0; i < size; i++)
    {
        if (data[i] != 0)
            return FALSE;
    }
    return TRUE;
}

static bool8 CheckStateA(void)
{
    u8 *beforeSam = (u8 *)&gSaveBlock1Ptr->samEdition - 1;
    u8 *ramScript = (u8 *)&gSaveBlock1Ptr->ramScript;

    if (gSaveBlock1Ptr->pos.x != 0x1234 || gSaveBlock1Ptr->pos.y != 0x2345)
        return FALSE;
    if (gSaveBlock1Ptr->registeredItem != 0x3456)
        return FALSE;
    if (gSaveBlock1Ptr->flags[0] != 0x5A)
        return FALSE;
    if (gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] != 1)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.greenName[0] != 'G'
     || gSaveBlock1Ptr->samEdition.greenName[1] != 'R'
     || gSaveBlock1Ptr->samEdition.greenName[2] != 'E'
     || gSaveBlock1Ptr->samEdition.greenName[3] != 'E'
     || gSaveBlock1Ptr->samEdition.greenName[4] != 'N')
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.coreMetadata[0] != 0x11)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.globalMechanicAux[0] != 0x22)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.rivalRocketAux[0] != 0x33)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.gymSatoshiPostgameAux[0] != 0x44)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.futureExpansion[1] != 0x55)
        return FALSE;
    if (*beforeSam != 0x66)
        return FALSE;
    if (*ramScript != 0x77)
        return FALSE;
    return TRUE;
}

static bool8 CheckStateB(void)
{
    u8 *beforeSam = (u8 *)&gSaveBlock1Ptr->samEdition - 1;
    u8 *ramScript = (u8 *)&gSaveBlock1Ptr->ramScript;

    if (gSaveBlock1Ptr->pos.x != 0x4321 || gSaveBlock1Ptr->pos.y != 0x5432)
        return FALSE;
    if (gSaveBlock1Ptr->registeredItem != 0x6543)
        return FALSE;
    if (gSaveBlock1Ptr->flags[0] != 0xA5)
        return FALSE;
    if (gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] != 0)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.greenName[0] != 'B'
     || gSaveBlock1Ptr->samEdition.greenName[1] != 'L'
     || gSaveBlock1Ptr->samEdition.greenName[2] != 'U'
     || gSaveBlock1Ptr->samEdition.greenName[3] != 'E')
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.coreMetadata[0] != 0x91)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.globalMechanicAux[0] != 0x82)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.rivalRocketAux[0] != 0x73)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.gymSatoshiPostgameAux[0] != 0x64)
        return FALSE;
    if (gSaveBlock1Ptr->samEdition.futureExpansion[1] != 0x55)
        return FALSE;
    if (*beforeSam != 0x46)
        return FALSE;
    if (*ramScript != 0x37)
        return FALSE;
    return TRUE;
}

static void SetStateA(void)
{
    u8 *beforeSam = (u8 *)&gSaveBlock1Ptr->samEdition - 1;
    u8 *ramScript = (u8 *)&gSaveBlock1Ptr->ramScript;

    gSaveBlock1Ptr->pos.x = 0x1234;
    gSaveBlock1Ptr->pos.y = 0x2345;
    gSaveBlock1Ptr->registeredItem = 0x3456;
    gSaveBlock1Ptr->flags[0] = 0x5A;
    gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] = 1;

    gSaveBlock1Ptr->samEdition.greenName[0] = 'G';
    gSaveBlock1Ptr->samEdition.greenName[1] = 'R';
    gSaveBlock1Ptr->samEdition.greenName[2] = 'E';
    gSaveBlock1Ptr->samEdition.greenName[3] = 'E';
    gSaveBlock1Ptr->samEdition.greenName[4] = 'N';
    gSaveBlock1Ptr->samEdition.greenName[5] = EOS;
    gSaveBlock1Ptr->samEdition.coreMetadata[0] = 0x11;
    gSaveBlock1Ptr->samEdition.globalMechanicAux[0] = 0x22;
    gSaveBlock1Ptr->samEdition.rivalRocketAux[0] = 0x33;
    gSaveBlock1Ptr->samEdition.gymSatoshiPostgameAux[0] = 0x44;
    gSaveBlock1Ptr->samEdition.futureExpansion[0] = ARCH002_STAGE_A;
    gSaveBlock1Ptr->samEdition.futureExpansion[1] = 0x55;
    *beforeSam = 0x66;
    *ramScript = 0x77;
}

static void SetStateB(void)
{
    u8 *beforeSam = (u8 *)&gSaveBlock1Ptr->samEdition - 1;
    u8 *ramScript = (u8 *)&gSaveBlock1Ptr->ramScript;

    gSaveBlock1Ptr->pos.x = 0x4321;
    gSaveBlock1Ptr->pos.y = 0x5432;
    gSaveBlock1Ptr->registeredItem = 0x6543;
    gSaveBlock1Ptr->flags[0] = 0xA5;
    gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] = 0;

    gSaveBlock1Ptr->samEdition.greenName[0] = 'B';
    gSaveBlock1Ptr->samEdition.greenName[1] = 'L';
    gSaveBlock1Ptr->samEdition.greenName[2] = 'U';
    gSaveBlock1Ptr->samEdition.greenName[3] = 'E';
    gSaveBlock1Ptr->samEdition.greenName[4] = EOS;
    gSaveBlock1Ptr->samEdition.coreMetadata[0] = 0x91;
    gSaveBlock1Ptr->samEdition.globalMechanicAux[0] = 0x82;
    gSaveBlock1Ptr->samEdition.rivalRocketAux[0] = 0x73;
    gSaveBlock1Ptr->samEdition.gymSatoshiPostgameAux[0] = 0x64;
    gSaveBlock1Ptr->samEdition.futureExpansion[0] = ARCH002_STAGE_B;
    *beforeSam = 0x46;
    *ramScript = 0x37;
}

void Arch002_RunRuntimeQa(void)
{
    u8 loadStatus;
    u8 saveStatus;
    u8 *samBytes;

    MgbaOpen();
    SetSaveBlocksPointers();

    loadStatus = LoadGameSave(SAVE_NORMAL);

    if (loadStatus != SAVE_STATUS_OK)
    {
        MgbaPrintf(MGBA_LOG_INFO, "ARCH002 PHASE1 fresh save start");
        ClearSav2();
        ClearSav1();

        samBytes = (u8 *)&gSaveBlock1Ptr->samEdition;
        if (!BytesAreZero(samBytes, sizeof(struct SamEditionSaveData)))
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL fresh SamEditionSaveData not zero");
            for (;;);
        }

        gSaveBlock1Ptr->samEdition.greenName[0] = 'G';
        gSaveBlock1Ptr->samEdition.greenName[1] = 'R';
        gSaveBlock1Ptr->samEdition.greenName[2] = 'E';
        gSaveBlock1Ptr->samEdition.greenName[3] = 'E';
        gSaveBlock1Ptr->samEdition.greenName[4] = 'N';
        gSaveBlock1Ptr->samEdition.greenName[5] = EOS;
        gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] = 1;

        NewGameInitData();

        if (gSaveBlock1Ptr->samEdition.greenName[0] != 'G'
         || gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] != 1)
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL NewGameInitData preservation");
            for (;;);
        }

        SetStateA();
        saveStatus = TrySavingData(SAVE_NORMAL);
        if (saveStatus != SAVE_STATUS_OK)
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL phase1 save");
            for (;;);
        }

        MgbaPrintf(MGBA_LOG_INFO, "ARCH002 PHASE1 PASS state A saved");
        for (;;);
    }

    if (gSaveBlock1Ptr->samEdition.futureExpansion[0] == ARCH002_STAGE_A)
    {
        MgbaPrintf(MGBA_LOG_INFO, "ARCH002 PHASE2 loaded state A");
        if (!CheckStateA())
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL state A persistence");
            for (;;);
        }

        SetStateB();
        saveStatus = TrySavingData(SAVE_NORMAL);
        if (saveStatus != SAVE_STATUS_OK)
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL phase2 save");
            for (;;);
        }

        MgbaPrintf(MGBA_LOG_INFO, "ARCH002 PHASE2 PASS state B saved");
        for (;;);
    }

    if (gSaveBlock1Ptr->samEdition.futureExpansion[0] == ARCH002_STAGE_B)
    {
        MgbaPrintf(MGBA_LOG_INFO, "ARCH002 PHASE3 loaded state B");
        if (!CheckStateB())
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL state B persistence");
            for (;;);
        }

        ClearSaveData();
        ClearSav2();
        ClearSav1();

        samBytes = (u8 *)&gSaveBlock1Ptr->samEdition;
        if (!BytesAreZero(samBytes, sizeof(struct SamEditionSaveData)))
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL fresh regression clear");
            for (;;);
        }

        NewGameInitData();
        if (!BytesAreZero((u8 *)&gSaveBlock1Ptr->samEdition, sizeof(struct SamEditionSaveData)))
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL fresh regression NewGameInitData");
            for (;;);
        }
        if (gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] != 0)
        {
            MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL fresh regression game mode");
            for (;;);
        }

        MgbaPrintf(MGBA_LOG_INFO, "ARCH002 PASS runtime save load repeated-cycle fresh-regression");
        for (;;);
    }

    MgbaPrintf(MGBA_LOG_FATAL, "ARCH002 FAIL unknown persisted stage");
    for (;;);
}
