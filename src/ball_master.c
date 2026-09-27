#include "global.h"
#include "apricorn.h"
#include "item.h"
#include "script.h"
#include "constants/apricorn.h"
#include "constants/items.h"

// DEP-015 owns this clock. SHARED-001 consumes it and never creates a second clock.
extern u32 WeatherTime_GetMinuteIndex(void);

static const u16 sApricornItemIds[APRICORN_COLOR_COUNT] =
{
    [APRICORN_COLOR_WHITE]  = ITEM_WHITE_APRICORN,
    [APRICORN_COLOR_RED]    = ITEM_RED_APRICORN,
    [APRICORN_COLOR_ORANGE] = ITEM_ORANGE_APRICORN,
    [APRICORN_COLOR_YELLOW] = ITEM_YELLOW_APRICORN,
    [APRICORN_COLOR_GREEN]  = ITEM_GREEN_APRICORN,
    [APRICORN_COLOR_BLUE]   = ITEM_BLUE_APRICORN,
    [APRICORN_COLOR_VIOLET] = ITEM_VIOLET_APRICORN,
    [APRICORN_COLOR_BLACK]  = ITEM_BLACK_APRICORN,
};

static void ReconcileBallMasterState(void)
{
    if (BallMaster_GetState() == BALL_MASTER_STATE_WORKING
     && BallMaster_GetCompletionMinute() <= WeatherTime_GetMinuteIndex())
        BallMaster_SetState(BALL_MASTER_STATE_COMPLETE);
}

u16 BallMaster_PrepareInteraction(void)
{
    ReconcileBallMasterState();
    return BallMaster_GetState();
}

u16 BallMaster_GetBagApricornQuantity(void)
{
    u16 color = gSpecialVar_0x8004;

    if (color >= APRICORN_COLOR_COUNT)
        return 0;

    return BagGetQuantityByItemId(sApricornItemIds[color]);
}

u16 BallMaster_GetBagApricornTotal(void)
{
    u32 total = 0;
    u8 color;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
        total += BagGetQuantityByItemId(sApricornItemIds[color]);

    return total;
}

u16 BallMaster_StartBatch(void)
{
    u16 quantities[APRICORN_COLOR_COUNT];
    u16 total = 0;
    u8 color;
    u8 removedCount = 0;

    if (BallMaster_GetState() != BALL_MASTER_STATE_AVAILABLE)
        return FALSE;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        quantities[color] = BagGetQuantityByItemId(sApricornItemIds[color]);
        total += quantities[color];
    }

    if (total < 2)
        return FALSE;

    // Verify the complete transaction before removing anything.
    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        if (quantities[color] != 0
         && !CheckBagHasItem(sApricornItemIds[color], quantities[color]))
            return FALSE;
    }

    BallMaster_ClearOrder();

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        if (quantities[color] == 0)
            continue;

        if (!RemoveBagItem(sApricornItemIds[color], quantities[color]))
        {
            u8 rollbackColor;

            // Defensive rollback. Removing a previously verified stack should
            // not fail, but a failed transaction must never lose Apricorns.
            for (rollbackColor = 0; rollbackColor < removedCount; rollbackColor++)
            {
                if (quantities[rollbackColor] != 0)
                    AddBagItem(sApricornItemIds[rollbackColor], quantities[rollbackColor]);
            }
            BallMaster_ClearOrder();
            return FALSE;
        }

        BallMaster_SetOrderQuantity(color, quantities[color]);
        removedCount = color + 1;
    }

    BallMaster_SetCompletionMinute(WeatherTime_GetMinuteIndex() + BALL_MASTER_BATCH_MINUTES);
    BallMaster_SetState(BALL_MASTER_STATE_WORKING);
    return total;
}

u16 BallMaster_GetWorkingTimeBranch(void)
{
    u32 now;
    u32 completionMinute;
    u32 remainingMinutes;

    ReconcileBallMasterState();
    if (BallMaster_GetState() == BALL_MASTER_STATE_COMPLETE)
        return BALL_MASTER_TIME_COMPLETE;

    if (BallMaster_GetState() != BALL_MASTER_STATE_WORKING)
        return BALL_MASTER_TIME_NOT_WORKING;

    now = WeatherTime_GetMinuteIndex();
    completionMinute = BallMaster_GetCompletionMinute();
    remainingMinutes = completionMinute - now;

    // VAR_0x8004 is used by the <=12h dialogue branch.
    gSpecialVar_0x8004 = (remainingMinutes + 59) / 60;

    if (remainingMinutes > 48 * 60)
        return BALL_MASTER_TIME_ABOUT_3_DAYS;
    if (remainingMinutes > 24 * 60)
        return BALL_MASTER_TIME_ABOUT_2_DAYS;
    if (remainingMinutes > 12 * 60)
        return BALL_MASTER_TIME_ABOUT_1_DAY;

    return BALL_MASTER_TIME_HOURS;
}
