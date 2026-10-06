#include "global.h"
#include "event_data.h"
#include "constants/vars.h"

#define LAVENDER_MEMORIAL_COUNT 3
#define LAVENDER_OFFERING_MASK  3
#define LAVENDER_SOLUTION       0x39

static u16 GetMemorialOffering(u16 state, u8 memorial)
{
    return (state >> (memorial * 2)) & LAVENDER_OFFERING_MASK;
}

static u16 SetMemorialOffering(u16 state, u8 memorial, u16 offering)
{
    u16 shift = memorial * 2;

    state &= ~(LAVENDER_OFFERING_MASK << shift);
    state |= (offering & LAVENDER_OFFERING_MASK) << shift;
    return state;
}

void SetLavenderMemorialOffering(void)
{
    u8 memorial = gSpecialVar_0x8004;
    u16 offering = gSpecialVar_0x8005;
    u16 state;
    u16 oldOffering;
    u8 i;

    gSpecialVar_Result = FALSE;

    if (memorial >= LAVENDER_MEMORIAL_COUNT || offering > LAVENDER_OFFERING_MASK)
        return;

    state = VarGet(VAR_SQ_LAVENDER_OFFERINGS);
    oldOffering = GetMemorialOffering(state, memorial);

    if (offering != 0)
    {
        for (i = 0; i < LAVENDER_MEMORIAL_COUNT; i++)
        {
            if (i != memorial && GetMemorialOffering(state, i) == offering)
            {
                state = SetMemorialOffering(state, i, oldOffering);
                break;
            }
        }
    }

    state = SetMemorialOffering(state, memorial, offering);
    VarSet(VAR_SQ_LAVENDER_OFFERINGS, state);

    if ((state & 0x3F) == LAVENDER_SOLUTION)
        gSpecialVar_Result = TRUE;
}
