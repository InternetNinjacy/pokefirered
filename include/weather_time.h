#ifndef GUARD_WEATHER_TIME_H
#define GUARD_WEATHER_TIME_H

#include "global.h"

#define WEATHER_TIME_FRAMES_PER_MINUTE 600
#define WEATHER_TIME_MINUTES_PER_DAY 1440

void WeatherTime_Reset(void);
void WeatherTime_Update(void);
u32 WeatherTime_GetMinuteIndex(void);
u32 WeatherTime_GetDayIndex(void);

#endif // GUARD_WEATHER_TIME_H
