#include "global.h"
#include "event_data.h"
#include "mail_data.h"
#include "pokemon.h"
#include "script.h"
#include "constants/flags.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/vars.h"

#define SQ_SAFFRON_SUBMITTED_PIDGEY   0x0001
#define SQ_SAFFRON_SUBMITTED_RATTATA  0x0002
#define SQ_SAFFRON_STARTED_BIT        0x0008

static EWRAM_DATA u8 sQuest010PidgeySlot = PARTY_SIZE;
static EWRAM_DATA u32 sQuest010PidgeyPersonality = 0;
static EWRAM_DATA u32 sQuest010PidgeyOtId = 0;
static EWRAM_DATA u8 sQuest010RattataSlot = PARTY_SIZE;
static EWRAM_DATA u32 sQuest010RattataPersonality = 0;
static EWRAM_DATA u32 sQuest010RattataOtId = 0;

static bool8 HasUsablePartyMonOtherThan(u8 excludedSlot)
{
    u8 i;
    u8 partyCount = CalculatePlayerPartyCount();

    for (i = 0; i < partyCount; i++)
    {
        if (i == excludedSlot)
            continue;
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            continue;
        if (GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG, NULL))
            continue;
        if (GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) == 0)
            continue;
        return TRUE;
    }

    return FALSE;
}

void SamQuest010PreparePidgeySubmission(void)
{
    u8 slot = gSpecialVar_0x8004;
    u8 partyCount = CalculatePlayerPartyCount();
    u16 state = VarGet(VAR_SQ_SAFFRON_COUNT);

    gSpecialVar_Result = FALSE;
    sQuest010PidgeySlot = PARTY_SIZE;

    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        return;
    if (state & SQ_SAFFRON_SUBMITTED_PIDGEY)
        return;
    if (slot >= partyCount)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_IS_EGG, NULL))
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES, NULL) != SPECIES_PIDGEY)
        return;
    if (MonHasMail(&gPlayerParty[slot]))
        return;
    if (!HasUsablePartyMonOtherThan(slot))
        return;

    sQuest010PidgeySlot = slot;
    sQuest010PidgeyPersonality = GetMonData(&gPlayerParty[slot], MON_DATA_PERSONALITY, NULL);
    sQuest010PidgeyOtId = GetMonData(&gPlayerParty[slot], MON_DATA_OT_ID, NULL);
    gSpecialVar_Result = TRUE;
}

void SamQuest010CommitPidgeySubmission(void)
{
    u8 i;
    u8 slot = sQuest010PidgeySlot;
    u8 partyCount = CalculatePlayerPartyCount();
    u16 state = VarGet(VAR_SQ_SAFFRON_COUNT);

    gSpecialVar_Result = FALSE;

    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        return;
    if (state & SQ_SAFFRON_SUBMITTED_PIDGEY)
        return;
    if (slot >= partyCount)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES, NULL) != SPECIES_PIDGEY)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_PERSONALITY, NULL) != sQuest010PidgeyPersonality)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_OT_ID, NULL) != sQuest010PidgeyOtId)
        return;
    if (MonHasMail(&gPlayerParty[slot]))
        return;
    if (!HasUsablePartyMonOtherThan(slot))
        return;

    for (i = slot; i + 1 < partyCount; i++)
        CopyMon(&gPlayerParty[i], &gPlayerParty[i + 1], sizeof(struct Pokemon));
    ZeroMonData(&gPlayerParty[partyCount - 1]);
    gPlayerPartyCount = CalculatePlayerPartyCount();

    state |= SQ_SAFFRON_STARTED_BIT | SQ_SAFFRON_SUBMITTED_PIDGEY;
    VarSet(VAR_SQ_SAFFRON_COUNT, state);

    sQuest010PidgeySlot = PARTY_SIZE;
    gSpecialVar_Result = TRUE;
}

void SamQuest010PrepareRattataSubmission(void)
{
    u8 slot = gSpecialVar_0x8004;
    u8 partyCount = CalculatePlayerPartyCount();
    u16 state = VarGet(VAR_SQ_SAFFRON_COUNT);

    gSpecialVar_Result = FALSE;
    sQuest010RattataSlot = PARTY_SIZE;

    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        return;
    if (state & SQ_SAFFRON_SUBMITTED_RATTATA)
        return;
    if (slot >= partyCount)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_IS_EGG, NULL))
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES, NULL) != SPECIES_RATTATA)
        return;
    if (MonHasMail(&gPlayerParty[slot]))
        return;
    if (!HasUsablePartyMonOtherThan(slot))
        return;

    sQuest010RattataSlot = slot;
    sQuest010RattataPersonality = GetMonData(&gPlayerParty[slot], MON_DATA_PERSONALITY, NULL);
    sQuest010RattataOtId = GetMonData(&gPlayerParty[slot], MON_DATA_OT_ID, NULL);
    gSpecialVar_Result = TRUE;
}

void SamQuest010CommitRattataSubmission(void)
{
    u8 i;
    u8 slot = sQuest010RattataSlot;
    u8 partyCount = CalculatePlayerPartyCount();
    u16 state = VarGet(VAR_SQ_SAFFRON_COUNT);

    gSpecialVar_Result = FALSE;

    if (FlagGet(FLAG_SQ_SAFFRON_COMPLETE))
        return;
    if (state & SQ_SAFFRON_SUBMITTED_RATTATA)
        return;
    if (slot >= partyCount)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES, NULL) != SPECIES_RATTATA)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_PERSONALITY, NULL) != sQuest010RattataPersonality)
        return;
    if (GetMonData(&gPlayerParty[slot], MON_DATA_OT_ID, NULL) != sQuest010RattataOtId)
        return;
    if (MonHasMail(&gPlayerParty[slot]))
        return;
    if (!HasUsablePartyMonOtherThan(slot))
        return;

    for (i = slot; i + 1 < partyCount; i++)
        CopyMon(&gPlayerParty[i], &gPlayerParty[i + 1], sizeof(struct Pokemon));
    ZeroMonData(&gPlayerParty[partyCount - 1]);
    gPlayerPartyCount = CalculatePlayerPartyCount();

    state |= SQ_SAFFRON_STARTED_BIT | SQ_SAFFRON_SUBMITTED_RATTATA;
    VarSet(VAR_SQ_SAFFRON_COUNT, state);

    sQuest010RattataSlot = PARTY_SIZE;
    gSpecialVar_Result = TRUE;
}
