#include "global.h"
#include "gflib.h"
#include "apricorn.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "item.h"
#include "script.h"
#include "constants/apricorn.h"
#include "constants/event_objects.h"
#include "constants/flags.h"
#include "constants/items.h"

// DEP-015 owns this clock. SHARED-001 consumes it and never creates a second clock.
extern u32 WeatherTime_GetMinuteIndex(void);

struct ApricornTreeData
{
    u16 itemId;
    u8 readyGraphicsId;
};

static const struct ApricornTreeData sApricornTreeData[APRICORN_TREE_COUNT] =
{
    [APRICORN_TREE_ROUTE2_YELLOW - 1]          = {ITEM_YELLOW_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_YELLOW},
    [APRICORN_TREE_ROUTE3_BLACK - 1]           = {ITEM_BLACK_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_BLACK},
    [APRICORN_TREE_VIRIDIAN_FOREST_GREEN - 1] = {ITEM_GREEN_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_GREEN},
    [APRICORN_TREE_ROUTE4_BLUE - 1]            = {ITEM_BLUE_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_BLUE},
    [APRICORN_TREE_ROUTE6_GREEN - 1]           = {ITEM_GREEN_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_GREEN},
    [APRICORN_TREE_ROUTE11_YELLOW - 1]         = {ITEM_YELLOW_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_YELLOW},
    [APRICORN_TREE_ROUTE10_BLACK - 1]          = {ITEM_BLACK_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_BLACK},
    [APRICORN_TREE_ROUTE8_ORANGE - 1]          = {ITEM_ORANGE_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_ORANGE},
    [APRICORN_TREE_ROUTE12_BLUE - 1]           = {ITEM_BLUE_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_BLUE},
    [APRICORN_TREE_ROUTE15_VIOLET - 1]         = {ITEM_VIOLET_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_VIOLET},
    [APRICORN_TREE_ROUTE21_NORTH_RED - 1]      = {ITEM_RED_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_RED},
    [APRICORN_TREE_ROUTE11_WHITE - 1]          = {ITEM_WHITE_APRICORN, OBJ_EVENT_GFX_APRICORN_TREE_READY_WHITE},
};

static bool8 IsApricornTreeObject(const struct ObjectEvent *objectEvent)
{
    return objectEvent->active
        && objectEvent->graphicsId >= OBJ_EVENT_GFX_APRICORN_TREE_READY_WHITE
        && objectEvent->graphicsId <= OBJ_EVENT_GFX_APRICORN_TREE_EMPTY
        && objectEvent->trainerRange_berryTreeId > APRICORN_TREE_NONE
        && objectEvent->trainerRange_berryTreeId <= APRICORN_TREE_COUNT;
}

static bool8 IsWhiteTree(u8 treeId)
{
    return treeId == APRICORN_TREE_ROUTE11_WHITE;
}

static bool8 IsWhiteTreeUnlocked(void)
{
    return FlagGet(FLAG_WEATHER_ANOMALY_TOXIC_SMOG_RESOLVED);
}

static bool8 EnsureWhiteInitialGrowthStarted(u8 treeId, u32 now)
{
    if (!IsWhiteTree(treeId) || !IsWhiteTreeUnlocked())
        return FALSE;

    if (!ApricornTree_HasWhiteFirstHarvested() && ApricornTree_GetNextReadyMinute(treeId) == 0)
    {
        ApricornTree_SetNextReadyMinute(treeId, now + APRICORN_TREE_REGROWTH_MINUTES);
        return TRUE;
    }

    return FALSE;
}

static bool8 IsTreeReady(u8 treeId, u32 now)
{
    u32 readyMinute;

    if (IsWhiteTree(treeId))
    {
        if (!IsWhiteTreeUnlocked())
            return FALSE;

        if (EnsureWhiteInitialGrowthStarted(treeId, now))
            return FALSE;
    }

    readyMinute = ApricornTree_GetNextReadyMinute(treeId);
    return readyMinute == 0 || readyMinute <= now;
}

static u8 GetTreeGraphicsId(u8 treeId, u32 now)
{
    if (!IsTreeReady(treeId, now))
        return OBJ_EVENT_GFX_APRICORN_TREE_EMPTY;

    return sApricornTreeData[treeId - 1].readyGraphicsId;
}

static void ReconcileObjectGraphics(struct ObjectEvent *objectEvent, u32 now)
{
    u8 treeId;
    u8 graphicsId;

    if (!IsApricornTreeObject(objectEvent))
        return;

    treeId = objectEvent->trainerRange_berryTreeId;
    graphicsId = GetTreeGraphicsId(treeId, now);
    if (objectEvent->graphicsId != graphicsId)
        ObjectEventSetGraphicsId(objectEvent, graphicsId);
}

void ApricornTree_OnObjectSpawn(struct ObjectEvent *objectEvent)
{
    if (IsApricornTreeObject(objectEvent))
        ReconcileObjectGraphics(objectEvent, WeatherTime_GetMinuteIndex());
}

void ApricornTrees_ReconcileCurrentMap(void)
{
    u8 i;
    u32 now = WeatherTime_GetMinuteIndex();

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
        ReconcileObjectGraphics(&gObjectEvents[i], now);
}

void ApricornTrees_OnMinuteTick(void)
{
    // DEP-015 should call this once whenever the canonical minute index increments.
    ApricornTrees_ReconcileCurrentMap();
}

u16 ApricornTree_PrepareInteraction(void)
{
    struct ObjectEvent *objectEvent;
    u8 treeId;
    u32 now;
    u32 readyMinute;

    if (gSelectedObjectEvent >= OBJECT_EVENTS_COUNT)
        return APRICORN_TREE_INTERACT_EMPTY;

    objectEvent = &gObjectEvents[gSelectedObjectEvent];
    if (!IsApricornTreeObject(objectEvent))
        return APRICORN_TREE_INTERACT_EMPTY;

    treeId = objectEvent->trainerRange_berryTreeId;
    gSpecialVar_0x8004 = sApricornTreeData[treeId - 1].itemId;
    now = WeatherTime_GetMinuteIndex();

    if (IsWhiteTree(treeId) && !IsWhiteTreeUnlocked())
    {
        ReconcileObjectGraphics(objectEvent, now);
        return APRICORN_TREE_INTERACT_WHITE_BLOCKED;
    }

    if (IsWhiteTree(treeId)
     && !ApricornTree_HasWhiteFirstHarvested()
     && ApricornTree_GetNextReadyMinute(treeId) == 0)
    {
        ApricornTree_SetNextReadyMinute(treeId, now + APRICORN_TREE_REGROWTH_MINUTES);
        ReconcileObjectGraphics(objectEvent, now);
        return APRICORN_TREE_INTERACT_WHITE_RECOVERING;
    }

    readyMinute = ApricornTree_GetNextReadyMinute(treeId);
    if (readyMinute != 0 && readyMinute > now)
    {
        ReconcileObjectGraphics(objectEvent, now);
        if (IsWhiteTree(treeId) && !ApricornTree_HasWhiteFirstHarvested())
            return APRICORN_TREE_INTERACT_WHITE_RECOVERING;
        return APRICORN_TREE_INTERACT_EMPTY;
    }

    ReconcileObjectGraphics(objectEvent, now);
    if (IsWhiteTree(treeId) && !ApricornTree_HasWhiteFirstHarvested())
        return APRICORN_TREE_INTERACT_WHITE_FIRST_READY;

    return APRICORN_TREE_INTERACT_READY;
}

u16 ApricornTree_Harvest(void)
{
    struct ObjectEvent *objectEvent;
    u8 treeId;
    u16 itemId;
    u32 now;

    if (gSelectedObjectEvent >= OBJECT_EVENTS_COUNT)
        return FALSE;

    objectEvent = &gObjectEvents[gSelectedObjectEvent];
    if (!IsApricornTreeObject(objectEvent))
        return FALSE;

    treeId = objectEvent->trainerRange_berryTreeId;
    now = WeatherTime_GetMinuteIndex();
    if (!IsTreeReady(treeId, now))
        return FALSE;

    itemId = sApricornTreeData[treeId - 1].itemId;
    gSpecialVar_0x8004 = itemId;

    if (!CheckBagHasSpace(itemId, 1))
        return FALSE;

    if (!AddBagItem(itemId, 1))
        return FALSE;

    ApricornTree_SetNextReadyMinute(treeId, now + APRICORN_TREE_REGROWTH_MINUTES);
    if (IsWhiteTree(treeId) && !ApricornTree_HasWhiteFirstHarvested())
        ApricornTree_SetWhiteFirstHarvested();

    ObjectEventSetGraphicsId(objectEvent, OBJ_EVENT_GFX_APRICORN_TREE_EMPTY);
    return TRUE;
}
