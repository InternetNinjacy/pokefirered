#include "global.h"
#include "event_data.h"
#include "constants/vars.h"
#include "constants/sam_rocket.h"

// Scripts pass one registered bit in VAR_0x8004. Reject unknown and combined
// requests instead of silently completing unrelated operations or evidence.
static bool8 IsRegisteredBit(u16 bit, u16 mask)
{
    return bit != 0 && (bit & mask) == bit && (bit & (bit - 1)) == 0;
}

static void SetRegisteredBit(u16 var, u16 mask)
{
    u16 bit = gSpecialVar_0x8004;
    gSpecialVar_Result = IsRegisteredBit(bit, mask);
    if (gSpecialVar_Result)
        VarSet(var, VarGet(var) | bit);
}

static void CheckRegisteredBit(u16 var, u16 mask)
{
    u16 bit = gSpecialVar_0x8004;
    gSpecialVar_Result = IsRegisteredBit(bit, mask) && (VarGet(var) & bit) != 0;
}

void Script_SamRocketCompleteOperation(void)
{
    SetRegisteredBit(VAR_SAM_ROCKET_OPERATIONS, ROCKET_OPERATION_MASK);
}

void Script_SamRocketCheckOperation(void)
{
    CheckRegisteredBit(VAR_SAM_ROCKET_OPERATIONS, ROCKET_OPERATION_MASK);
}

void Script_SamRocketRecordEvidence(void)
{
    SetRegisteredBit(VAR_SAM_ROCKET_EVIDENCE, ROCKET_EVIDENCE_BOUND_MASK);
}

void Script_SamRocketCheckEvidence(void)
{
    CheckRegisteredBit(VAR_SAM_ROCKET_EVIDENCE, ROCKET_EVIDENCE_BOUND_MASK);
}
