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

static const u16 sBallMasterOutputItemIds[APRICORN_COLOR_COUNT] =
{
    [APRICORN_COLOR_WHITE]  = ITEM_EGG_BALL,
    [APRICORN_COLOR_RED]    = ITEM_CRITICAL_BALL,
    [APRICORN_COLOR_ORANGE] = ITEM_GENDER_BALL,
    [APRICORN_COLOR_YELLOW] = ITEM_FAST_BALL,
    [APRICORN_COLOR_GREEN]  = ITEM_FRIEND_BALL,
    [APRICORN_COLOR_BLUE]   = ITEM_NET_BALL,
    [APRICORN_COLOR_VIOLET] = ITEM_AFFLICTION_BALL,
    [APRICORN_COLOR_BLACK]  = ITEM_HEAVY_BALL,
};

static u16 GetPCItemQuantityById(u16 itemId)
{
    u8 i;

    for (i = 0; i < PC_ITEMS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pcItems[i].itemId == itemId)
            return GetPcItemQuantity(&gSaveBlock1Ptr->pcItems[i].quantity);
    }

    return 0;
}

static u8 CountEmptyPCItemSlots(void)
{
    u8 i;
    u8 count = 0;

    for (i = 0; i < PC_ITEMS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pcItems[i].itemId == ITEM_NONE)
            count++;
    }

    return count;
}

static u8 CountEmptyBallPocketSlots(void)
{
    u8 i;
    u8 count = 0;
    struct BagPocket *pocket = &gBagPockets[POCKET_POKE_BALLS - 1];

    for (i = 0; i < pocket->capacity; i++)
    {
        if (pocket->itemSlots[i].itemId == ITEM_NONE)
            count++;
    }

    return count;
}

static bool8 PreflightBallDelivery(const u16 quantities[APRICORN_COLOR_COUNT], bool8 *usedPc)
{
    u8 color;
    u8 emptyBagSlots = CountEmptyBallPocketSlots();
    u8 emptyPcSlots = CountEmptyPCItemSlots();

    *usedPc = FALSE;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        u16 itemId = sBallMasterOutputItemIds[color];
        u16 remaining = quantities[color];
        u16 bagQuantity;
        u16 pcQuantity;
        u16 capacity;

        if (remaining == 0)
            continue;

        bagQuantity = BagGetQuantityByItemId(itemId);
        if (bagQuantity != 0)
        {
            capacity = 999 - bagQuantity;
            if (remaining <= capacity)
                continue;

            remaining -= capacity;
        }
        else if (emptyBagSlots != 0)
        {
            emptyBagSlots--;
            capacity = 999;
            if (remaining <= capacity)
                continue;

            remaining -= capacity;
        }

        *usedPc = TRUE;
        pcQuantity = GetPCItemQuantityById(itemId);
        if (pcQuantity != 0)
        {
            capacity = 999 - pcQuantity;
            if (remaining <= capacity)
                continue;

            remaining -= capacity;
        }
        else if (emptyPcSlots != 0)
        {
            emptyPcSlots--;
            capacity = 999;
            if (remaining <= capacity)
                continue;

            remaining -= capacity;
        }

        if (remaining != 0)
            return FALSE;
    }

    return TRUE;
}

static bool8 DeliverBalls(const u16 quantities[APRICORN_COLOR_COUNT], bool8 *usedPc)
{
    u8 color;

    if (!PreflightBallDelivery(quantities, usedPc))
        return FALSE;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        u16 itemId = sBallMasterOutputItemIds[color];
        u16 remaining = quantities[color];
        u16 bagQuantity;
        u16 bagCapacity;
        u16 bagAmount;

        if (remaining == 0)
            continue;

        bagQuantity = BagGetQuantityByItemId(itemId);
        if (bagQuantity != 0)
            bagCapacity = 999 - bagQuantity;
        else if (CountEmptyBallPocketSlots() != 0)
            bagCapacity = 999;
        else
            bagCapacity = 0;

        bagAmount = remaining;
        if (bagAmount > bagCapacity)
            bagAmount = bagCapacity;

        if (bagAmount != 0)
        {
            if (!AddBagItem(itemId, bagAmount))
                return FALSE;
            remaining -= bagAmount;
        }

        if (remaining != 0)
        {
            if (!AddPCItem(itemId, remaining))
                return FALSE;
        }
    }

    return TRUE;
}

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


u16 BallMaster_ConvertSingle(void)
{
    u16 quantities[APRICORN_COLOR_COUNT] = {0};
    u16 total = 0;
    u8 color;
    bool8 usedPc;

    if (BallMaster_GetState() != BALL_MASTER_STATE_AVAILABLE)
        return BALL_MASTER_DELIVERY_FAILED;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        quantities[color] = BagGetQuantityByItemId(sApricornItemIds[color]);
        total += quantities[color];
    }

    if (total != 1)
        return BALL_MASTER_DELIVERY_FAILED;

    if (!PreflightBallDelivery(quantities, &usedPc))
        return BALL_MASTER_DELIVERY_FAILED;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
    {
        if (quantities[color] != 0)
        {
            gSpecialVar_0x8004 = sBallMasterOutputItemIds[color];

            // Capacity is verified before the Apricorn is removed. If the
            // impossible delivery failure occurs, restore the input item.
            if (!RemoveBagItem(sApricornItemIds[color], 1))
                return BALL_MASTER_DELIVERY_FAILED;

            if (!DeliverBalls(quantities, &usedPc))
            {
                AddBagItem(sApricornItemIds[color], 1);
                return BALL_MASTER_DELIVERY_FAILED;
            }

            return usedPc ? BALL_MASTER_DELIVERY_PC_OVERFLOW : BALL_MASTER_DELIVERY_BAG_ONLY;
        }
    }

    return BALL_MASTER_DELIVERY_FAILED;
}

u16 BallMaster_CollectOrder(void)
{
    u16 quantities[APRICORN_COLOR_COUNT];
    u8 color;
    bool8 usedPc;

    ReconcileBallMasterState();
    if (BallMaster_GetState() != BALL_MASTER_STATE_COMPLETE)
        return BALL_MASTER_DELIVERY_FAILED;

    for (color = 0; color < APRICORN_COLOR_COUNT; color++)
        quantities[color] = BallMaster_GetOrderQuantity(color);

    if (BallMaster_GetOrderTotal() == 0)
        return BALL_MASTER_DELIVERY_FAILED;

    if (!DeliverBalls(quantities, &usedPc))
        return BALL_MASTER_DELIVERY_FAILED;

    BallMaster_ClearOrder();
    BallMaster_SetState(BALL_MASTER_STATE_AVAILABLE);

    return usedPc ? BALL_MASTER_DELIVERY_PC_OVERFLOW : BALL_MASTER_DELIVERY_BAG_ONLY;
}

u16 BallMaster_GetScriptOrderQuantity(void)
{
    u16 color = gSpecialVar_0x8004;

    if (color >= APRICORN_COLOR_COUNT)
        return 0;

    return BallMaster_GetOrderQuantity(color);
}

u16 BallMaster_GetOutputItemForColor(void)
{
    u16 color = gSpecialVar_0x8004;

    if (color >= APRICORN_COLOR_COUNT)
        return ITEM_NONE;

    return sBallMasterOutputItemIds[color];
}
