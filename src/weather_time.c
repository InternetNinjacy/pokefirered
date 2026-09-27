#include "global.h"
#include "apricorn.h"
#include "weather_time.h"

void WeatherTime_Reset(void)
{
    gSaveBlock2Ptr->weatherTimeMinuteIndex = 0;
    gSaveBlock2Ptr->weatherTimeFramePhase = 0;
}

void WeatherTime_Update(void)
{
    gSaveBlock2Ptr->weatherTimeFramePhase++;

    if (gSaveBlock2Ptr->weatherTimeFramePhase >= WEATHER_TIME_FRAMES_PER_MINUTE)
    {
        gSaveBlock2Ptr->weatherTimeFramePhase = 0;

        if (gSaveBlock2Ptr->weatherTimeMinuteIndex != 0xFFFFFFFF)
            gSaveBlock2Ptr->weatherTimeMinuteIndex++;

        // Current consumers reconcile only when a canonical in-game minute
        // actually advances. Future TOM-SYS-003 consumers can join here.
        ApricornTrees_OnMinuteTick();
    }
}

u32 WeatherTime_GetMinuteIndex(void)
{
    return gSaveBlock2Ptr->weatherTimeMinuteIndex;
}

u32 WeatherTime_GetDayIndex(void)
{
    return gSaveBlock2Ptr->weatherTimeMinuteIndex / WEATHER_TIME_MINUTES_PER_DAY;
}
