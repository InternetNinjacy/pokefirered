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
#define SQ_STARTED            0x0008
#define SQ_PIDGEY             0x0001
#define SQ_RATTATA            0x0002
#define SQ_ODDISH             0x0004
#define SQ_ALL_SUBMITTED      0x000F

void SamQuest010PreparePidgeySubmission(void);
void SamQuest010CommitPidgeySubmission(void);
void SamQuest010PrepareRattataSubmission(void);
void SamQuest010CommitRattataSubmission(void);
void SamQuest010PrepareOddishSubmission(void);
void SamQuest010CommitOddishSubmission(void);

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

static u8 FindSpeciesSlot(u16 species)
{
    u8 i;
    u8 count = CalculatePlayerPartyCount();
    for (i = 0; i < count; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == species)
            return i;
    }
    return PARTY_SIZE;
}

static u16 BitForSpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_PIDGEY:
        return SQ_PIDGEY;
    case SPECIES_RATTATA:
        return SQ_RATTATA;
    case SPECIES_ODDISH:
        return SQ_ODDISH;
    default:
        return 0;
    }
}

static void SubmitSpecies(u16 species)
{
    u8 slot = FindSpeciesSlot(species);
    if (slot >= PARTY_SIZE)
        Fail("QUEST010F QA FAIL requested species missing");

    gSpecialVar_0x8004 = slot;
    switch (species)
    {
    case SPECIES_PIDGEY:
        SamQuest010PreparePidgeySubmission();
        if (gSpecialVar_Result != TRUE)
            Fail("QUEST010F QA FAIL Pidgey prepare");
        SamQuest010CommitPidgeySubmission();
        break;
    case SPECIES_RATTATA:
        SamQuest010PrepareRattataSubmission();
        if (gSpecialVar_Result != TRUE)
            Fail("QUEST010F QA FAIL Rattata prepare");
        SamQuest010CommitRattataSubmission();
        break;
    case SPECIES_ODDISH:
        SamQuest010PrepareOddishSubmission();
        if (gSpecialVar_Result != TRUE)
            Fail("QUEST010F QA FAIL Oddish prepare");
        SamQuest010CommitOddishSubmission();
        break;
    default:
        Fail("QUEST010F QA FAIL bad species");
    }

    if (gSpecialVar_Result != TRUE)
        Fail("QUEST010F QA FAIL commit");
}

static void RunPermutation(u16 first, u16 second, u16 third)
{
    u16 expected = SQ_STARTED;

    ResetState();
    CreateQaMon(0, SPECIES_PIDGEY, 0x11111111);
    CreateQaMon(1, SPECIES_RATTATA, 0x22222222);
    CreateQaMon(2, SPECIES_ODDISH, 0x33333333);
    CreateQaMon(3, SPECIES_PIKACHU, 0x44444444);

    SubmitSpecies(first);
    expected |= BitForSpecies(first);
    if (VarGet(VAR_SQ_SAFFRON_COUNT) != expected)
        Fail("QUEST010F QA FAIL first-step state");
    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        Fail("QUEST010F QA FAIL completion after first");

    SubmitSpecies(second);
    expected |= BitForSpecies(second);
    if (VarGet(VAR_SQ_SAFFRON_COUNT) != expected)
        Fail("QUEST010F QA FAIL second-step state");
    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        Fail("QUEST010F QA FAIL completion after second");

    SubmitSpecies(third);
    expected |= BitForSpecies(third);
    if (expected != SQ_ALL_SUBMITTED || VarGet(VAR_SQ_SAFFRON_COUNT) != SQ_ALL_SUBMITTED)
        Fail("QUEST010F QA FAIL all-submitted state");
    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        Fail("QUEST010F QA FAIL premature completion at all-submitted");
    if (CalculatePlayerPartyCount() != 1)
        Fail("QUEST010F QA FAIL final party count");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL) != SPECIES_PIKACHU)
        Fail("QUEST010F QA FAIL helper mon changed");
}

static void RunFresh(void)
{
    RunPermutation(SPECIES_PIDGEY,  SPECIES_RATTATA, SPECIES_ODDISH);
    RunPermutation(SPECIES_PIDGEY,  SPECIES_ODDISH,  SPECIES_RATTATA);
    RunPermutation(SPECIES_RATTATA, SPECIES_PIDGEY,  SPECIES_ODDISH);
    RunPermutation(SPECIES_RATTATA, SPECIES_ODDISH,  SPECIES_PIDGEY);
    RunPermutation(SPECIES_ODDISH,  SPECIES_PIDGEY,  SPECIES_RATTATA);
    RunPermutation(SPECIES_ODDISH,  SPECIES_RATTATA, SPECIES_PIDGEY);

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("QUEST010F QA FAIL save");
    Log("QUEST010F QA PHASE1 PASS all six submission orders");
    for (;;);
}

static void RunReload(void)
{
    if (VarGet(VAR_SQ_SAFFRON_COUNT) != SQ_ALL_SUBMITTED)
        Fail("QUEST010F QA FAIL reload all-submitted state");
    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        Fail("QUEST010F QA FAIL reload premature completion");
    if (CalculatePlayerPartyCount() != 1)
        Fail("QUEST010F QA FAIL reload party count");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL) != SPECIES_PIKACHU)
        Fail("QUEST010F QA FAIL reload helper mon");

    Log("QUEST010F QA PASS all-order persistence");
    for (;;);
}

void Quest010fQa_RunRuntimeQa(void)
{
    u8 loadStatus;
    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
