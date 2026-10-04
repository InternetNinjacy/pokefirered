#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "save.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/vars.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)
#define SQ_SAFFRON_STATE_PIDGEY 0x0009

void SamQuest010PreparePidgeySubmission(void);
void SamQuest010CommitPidgeySubmission(void);

static const u8 sQaPlayerName[] = _("SAM");

static void Log(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    QA_MGBA_DEBUG_STRING[i] = '\0';
    *QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    Log(text);
    for (;;);
}

static void ResetState(void)
{
    ClearSav2();
    ClearSav1();
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
    StringCopy(gSaveBlock2Ptr->playerName, sQaPlayerName);
    gSaveBlock2Ptr->playerGender = MALE;
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;
}

static void CreateQaMon(u8 slot, u16 species, u32 personality)
{
    CreateMon(&gPlayerParty[slot], species, 10, USE_RANDOM_IVS, TRUE, personality, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = CalculatePlayerPartyCount();
}

static void SwapPartyMons(u8 a, u8 b)
{
    struct Pokemon temp;
    CopyMon(&temp, &gPlayerParty[a], sizeof(struct Pokemon));
    CopyMon(&gPlayerParty[a], &gPlayerParty[b], sizeof(struct Pokemon));
    CopyMon(&gPlayerParty[b], &temp, sizeof(struct Pokemon));
}

static void CheckUnsafeRemovalGuard(void)
{
    u16 hp = 0;

    ResetState();
    CreateQaMon(0, SPECIES_PIDGEY, 0x11112222);
    CreateQaMon(1, SPECIES_RATTATA, 0x33334444);
    SetMonData(&gPlayerParty[1], MON_DATA_HP, &hp);
    gSpecialVar_0x8004 = 0;
    SamQuest010PreparePidgeySubmission();
    if (gSpecialVar_Result != FALSE)
        Fail("QUEST010C QA FAIL unsafe last usable allowed");
    if (CalculatePlayerPartyCount() != 2 || VarGet(VAR_SQ_SAFFRON_COUNT) != 0)
        Fail("QUEST010C QA FAIL unsafe guard mutated state");
}

static void RunFresh(void)
{
    u32 personality;

    CheckUnsafeRemovalGuard();
    ResetState();
    CreateQaMon(0, SPECIES_RATTATA, 0x11111111);
    CreateQaMon(1, SPECIES_PIDGEY, 0x22222222);
    CreateQaMon(2, SPECIES_PIDGEY, 0x33333333);

    gSpecialVar_0x8004 = 0;
    SamQuest010PreparePidgeySubmission();
    if (gSpecialVar_Result != FALSE || CalculatePlayerPartyCount() != 3)
        Fail("QUEST010C QA FAIL wrong species selection");

    gSpecialVar_0x8004 = 1;
    SamQuest010PreparePidgeySubmission();
    if (gSpecialVar_Result != TRUE)
        Fail("QUEST010C QA FAIL prepare selected Pidgey");

    SwapPartyMons(1, 2);
    SamQuest010CommitPidgeySubmission();
    if (gSpecialVar_Result != FALSE || CalculatePlayerPartyCount() != 3 || VarGet(VAR_SQ_SAFFRON_COUNT) != 0)
        Fail("QUEST010C QA FAIL reorder changed wrong mon");

    gSpecialVar_0x8004 = 2;
    SamQuest010PreparePidgeySubmission();
    if (gSpecialVar_Result != TRUE)
        Fail("QUEST010C QA FAIL reprepare exact mon");
    SamQuest010CommitPidgeySubmission();
    if (gSpecialVar_Result != TRUE)
        Fail("QUEST010C QA FAIL commit selected Pidgey");
    if (CalculatePlayerPartyCount() != 2 || VarGet(VAR_SQ_SAFFRON_COUNT) != SQ_SAFFRON_STATE_PIDGEY)
        Fail("QUEST010C QA FAIL commit state");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL) != SPECIES_RATTATA)
        Fail("QUEST010C QA FAIL unrelated mon changed");
    if (GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL) != SPECIES_PIDGEY)
        Fail("QUEST010C QA FAIL remaining Pidgey missing");
    personality = GetMonData(&gPlayerParty[1], MON_DATA_PERSONALITY, NULL);
    if (personality != 0x33333333)
        Fail("QUEST010C QA FAIL wrong Pidgey removed");

    gSpecialVar_0x8004 = 1;
    SamQuest010PreparePidgeySubmission();
    if (gSpecialVar_Result != FALSE)
        Fail("QUEST010C QA FAIL repeat submission prepared");
    if (CalculatePlayerPartyCount() != 2)
        Fail("QUEST010C QA FAIL repeat removed mon");

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("QUEST010C QA FAIL save");
    Log("QUEST010C QA PHASE1 PASS exact removal reorder repeat save");
    for (;;);
}

static void RunReload(void)
{
    u32 personality;

    if (VarGet(VAR_SQ_SAFFRON_COUNT) != SQ_SAFFRON_STATE_PIDGEY)
        Fail("QUEST010C QA FAIL reload state");
    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        Fail("QUEST010C QA FAIL premature completion");
    if (CalculatePlayerPartyCount() != 2)
        Fail("QUEST010C QA FAIL reload party count");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL) != SPECIES_RATTATA
     || GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL) != SPECIES_PIDGEY)
        Fail("QUEST010C QA FAIL reload party identity");
    personality = GetMonData(&gPlayerParty[1], MON_DATA_PERSONALITY, NULL);
    if (personality != 0x33333333)
        Fail("QUEST010C QA FAIL reload exact Pidgey");

    Log("QUEST010C QA PASS persistence exact selected individual");
    for (;;);
}

void Quest010cQa_RunRuntimeQa(void)
{
    u8 loadStatus;
    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
