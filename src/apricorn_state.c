#include "global.h"
#include "apricorn.h"
#include "constants/apricorn.h"

static bool8 IsApricornTreeIdValid(u8 treeId)
{
    return treeId > APRICORN_TREE_NONE && treeId <= APRICORN_TREE_COUNT;
}

u32 ApricornTree_GetNextReadyMinute(u8 treeId)
{
    if (!IsApricornTreeIdValid(treeId))
        return 0;

    return gSaveBlock2Ptr->apricornTreeNextReadyMinute[treeId - 1];
}

void ApricornTree_SetNextReadyMinute(u8 treeId, u32 minute)
{
    if (!IsApricornTreeIdValid(treeId))
        return;

    gSaveBlock2Ptr->apricornTreeNextReadyMinute[treeId - 1] = minute;
}

bool8 ApricornTree_HasWhiteFirstHarvested(void)
{
    return (gSaveBlock2Ptr->apricornFlags & APRICORN_FLAG_WHITE_FIRST_HARVESTED) != 0;
}

void ApricornTree_SetWhiteFirstHarvested(void)
{
    gSaveBlock2Ptr->apricornFlags |= APRICORN_FLAG_WHITE_FIRST_HARVESTED;
}

u8 BallMaster_GetState(void)
{
    return gSaveBlock2Ptr->ballMasterState;
}

void BallMaster_SetState(u8 state)
{
    if (state <= BALL_MASTER_STATE_COMPLETE)
        gSaveBlock2Ptr->ballMasterState = state;
}

bool8 BallMaster_HasMetPlayer(void)
{
    return (gSaveBlock2Ptr->ballMasterFlags & BALL_MASTER_FLAG_MET) != 0;
}

void BallMaster_SetMetPlayer(void)
{
    gSaveBlock2Ptr->ballMasterFlags |= BALL_MASTER_FLAG_MET;
}

u16 BallMaster_GetOrderQuantity(u8 color)
{
    if (color >= APRICORN_COLOR_COUNT)
        return 0;

    return gSaveBlock2Ptr->ballMasterOrderQty[color];
}

void BallMaster_SetOrderQuantity(u8 color, u16 quantity)
{
    if (color >= APRICORN_COLOR_COUNT)
        return;

    gSaveBlock2Ptr->ballMasterOrderQty[color] = quantity;
}

u16 BallMaster_GetOrderTotal(void)
{
    u32 total = 0;
    u8 i;

    for (i = 0; i < APRICORN_COLOR_COUNT; i++)
        total += gSaveBlock2Ptr->ballMasterOrderQty[i];

    // The legal maximum is 8 * 999, which fits in u16.
    return total;
}

void BallMaster_ClearOrder(void)
{
    u8 i;

    for (i = 0; i < APRICORN_COLOR_COUNT; i++)
        gSaveBlock2Ptr->ballMasterOrderQty[i] = 0;

    gSaveBlock2Ptr->ballMasterCompletionMinute = 0;
}

u32 BallMaster_GetCompletionMinute(void)
{
    return gSaveBlock2Ptr->ballMasterCompletionMinute;
}

void BallMaster_SetCompletionMinute(u32 minute)
{
    gSaveBlock2Ptr->ballMasterCompletionMinute = minute;
}
