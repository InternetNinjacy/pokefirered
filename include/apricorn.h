#ifndef GUARD_APRICORN_H
#define GUARD_APRICORN_H

#include "global.h"

u32 ApricornTree_GetNextReadyMinute(u8 treeId);
void ApricornTree_SetNextReadyMinute(u8 treeId, u32 minute);

u8 BallMaster_GetState(void);
void BallMaster_SetState(u8 state);

bool8 BallMaster_HasMetPlayer(void);
void BallMaster_SetMetPlayer(void);

u16 BallMaster_GetOrderQuantity(u8 color);
void BallMaster_SetOrderQuantity(u8 color, u16 quantity);
u16 BallMaster_GetOrderTotal(void);
void BallMaster_ClearOrder(void);

u32 BallMaster_GetCompletionMinute(void);
void BallMaster_SetCompletionMinute(u32 minute);

#endif // GUARD_APRICORN_H
