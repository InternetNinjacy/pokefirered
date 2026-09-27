#include "global.h"
#include "apricorn.h"
#include "event_data.h"
#include "weather_anomaly.h"
#include "constants/flags.h"

bool8 IsToxicSmogWeezingResolved(void)
{
    return FlagGet(FLAG_WEATHER_ANOMALY_TOXIC_SMOG_RESOLVED);
}

void WeatherAnomaly_ResolveToxicSmogWeezing(void)
{
    if (IsToxicSmogWeezingResolved())
        return;

    FlagSet(FLAG_WEATHER_ANOMALY_TOXIC_SMOG_RESOLVED);

    // SHARED-001 must start White Apricorn's first 12-hour growth at the
    // resolution transaction itself, not on the player's next tree visit.
    ApricornTree_OnToxicSmogResolved();
}
