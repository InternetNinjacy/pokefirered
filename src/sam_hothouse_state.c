#include "global.h"
#include "event_data.h"
#include "constants/flags.h"
#include "constants/vars.h"

#define HOTHOUSE_UNLOCK_IRRIGATION  (1 << 0)
#define HOTHOUSE_UNLOCK_SUNLIGHT    (1 << 1)
#define HOTHOUSE_UNLOCK_TEMPERATURE (1 << 2)
#define HOTHOUSE_UNLOCK_SOIL        (1 << 3)
#define HOTHOUSE_UNLOCK_MASK        (HOTHOUSE_UNLOCK_IRRIGATION \
                                   | HOTHOUSE_UNLOCK_SUNLIGHT \
                                   | HOTHOUSE_UNLOCK_TEMPERATURE \
                                   | HOTHOUSE_UNLOCK_SOIL)

// gSpecialVar_0x8004 supplies exactly one of the four registered Hothouse bits.
// The bitfield, not trainer flags, is the permanent control-unlock authority.
void SamHothouseUnlockControl(void)
{
    u16 bit = gSpecialVar_0x8004 & HOTHOUSE_UNLOCK_MASK;
    u16 state = VarGet(VAR_SAM_HOTHOUSE_STATE) & HOTHOUSE_UNLOCK_MASK;

    if (bit == HOTHOUSE_UNLOCK_IRRIGATION
     || bit == HOTHOUSE_UNLOCK_SUNLIGHT
     || bit == HOTHOUSE_UNLOCK_TEMPERATURE
     || bit == HOTHOUSE_UNLOCK_SOIL)
        VarSet(VAR_SAM_HOTHOUSE_STATE, state | bit);
}

// Returns TRUE through VAR_RESULT when the requested control is permanently
// unlocked in VAR_SAM_HOTHOUSE_STATE.
void SamHothouseIsControlUnlocked(void)
{
    u16 bit = gSpecialVar_0x8004 & HOTHOUSE_UNLOCK_MASK;
    u16 state = VarGet(VAR_SAM_HOTHOUSE_STATE) & HOTHOUSE_UNLOCK_MASK;

    gSpecialVar_Result = (bit != 0 && (state & bit) == bit);
}

// The exact solve is Medium / Full / Warm / Rich = 1 / 2 / 1 / 2.
// Once solved, access is permanent even if the controls are changed afterward.
// VAR_RESULT is TRUE only on the first transition into the solved state so the
// chamber flourish/dialogue cannot replay on later control changes.
void SamHothouseCheckSolution(void)
{
    if (FlagGet(FLAG_SAM_HOTHOUSE_SOLVED))
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    if (VarGet(VAR_SAM_HOTHOUSE_IRRIGATION) == 1
     && VarGet(VAR_SAM_HOTHOUSE_SUNLIGHT) == 2
     && VarGet(VAR_SAM_HOTHOUSE_TEMPERATURE) == 1
     && VarGet(VAR_SAM_HOTHOUSE_SOIL) == 2)
    {
        FlagSet(FLAG_SAM_HOTHOUSE_SOLVED);
        gSpecialVar_Result = TRUE;
        return;
    }

    gSpecialVar_Result = FALSE;
}
