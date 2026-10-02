#include "global.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "random.h"
#include "constants/items.h"
#include "constants/maps.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern u8 Enc001QaChooseWaterIndex(void);
extern u8 Enc001QaChooseFishingIndex(u8 rod);

static void QaLog(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    QA_MGBA_DEBUG_STRING[i] = '\0';
    *QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    QaLog(text);
    for (;;);
}

static bool8 Near(u32 count, u32 expected, u32 tolerance)
{
    return count >= expected - tolerance && count <= expected + tolerance;
}

static void SetMap(u16 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

static void CheckRoute6Selectors(void)
{
    u32 water[5] = {0};
    u32 good[10] = {0};
    u32 super[10] = {0};
    u32 i;

    SetMap(MAP_ROUTE6);

    SeedRng(0x1234);
    for (i = 0; i < 50000; i++)
    {
        u8 slot = Enc001QaChooseWaterIndex();
        if (slot >= 5)
            Fail("ENC001 FINAL FAIL Route6 water index");
        water[slot]++;
    }

    if (!Near(water[0], 25000, 900)
     || !Near(water[1], 15000, 900)
     || !Near(water[2], 10000, 900)
     || water[3] != 0
     || water[4] != 0)
        Fail("ENC001 FINAL FAIL Route6 Surf distribution");

    SeedRng(0x2345);
    for (i = 0; i < 50000; i++)
    {
        u8 slot = Enc001QaChooseFishingIndex(GOOD_ROD);
        if (slot >= 10)
            Fail("ENC001 FINAL FAIL Route6 Good index");
        good[slot]++;
    }

    if (!Near(good[2], 15000, 900)
     || !Near(good[3], 10000, 900)
     || !Near(good[4], 5000, 700)
     || !Near(good[5], 20000, 900))
        Fail("ENC001 FINAL FAIL Route6 Good distribution");
    for (i = 0; i < 10; i++)
        if (i != 2 && i != 3 && i != 4 && i != 5 && good[i] != 0)
            Fail("ENC001 FINAL FAIL Route6 Good stray slot");

    SeedRng(0x3456);
    for (i = 0; i < 50000; i++)
    {
        u8 slot = Enc001QaChooseFishingIndex(SUPER_ROD);
        if (slot >= 10)
            Fail("ENC001 FINAL FAIL Route6 Super index");
        super[slot]++;
    }

    if (!Near(super[5], 20000, 900)
     || !Near(super[6], 10000, 900)
     || !Near(super[7], 10000, 900)
     || !Near(super[8], 5000, 700)
     || !Near(super[9], 5000, 700))
        Fail("ENC001 FINAL FAIL Route6 Super distribution");
    for (i = 0; i < 5; i++)
        if (super[i] != 0)
            Fail("ENC001 FINAL FAIL Route6 Super stray slot");
}

static void CheckGenericSelectorsUnaffected(void)
{
    u32 water[5] = {0};
    u32 good[10] = {0};
    u32 i;

    SetMap(MAP_ROUTE5);

    SeedRng(0x4567);
    for (i = 0; i < 50000; i++)
    {
        u8 slot = Enc001QaChooseWaterIndex();
        if (slot >= 5)
            Fail("ENC001 FINAL FAIL generic water index");
        water[slot]++;
    }

    if (!Near(water[0], 30000, 900)
     || !Near(water[1], 15000, 900)
     || !Near(water[2], 2500, 500)
     || !Near(water[3], 2000, 500)
     || !Near(water[4], 500, 250))
        Fail("ENC001 FINAL FAIL generic water weights");

    SeedRng(0x5678);
    for (i = 0; i < 50000; i++)
    {
        u8 slot = Enc001QaChooseFishingIndex(GOOD_ROD);
        if (slot >= 10)
            Fail("ENC001 FINAL FAIL generic Good index");
        good[slot]++;
    }

    if (!Near(good[2], 30000, 900)
     || !Near(good[3], 10000, 900)
     || !Near(good[4], 10000, 900))
        Fail("ENC001 FINAL FAIL generic Good weights");
    for (i = 0; i < 10; i++)
        if (i != 2 && i != 3 && i != 4 && good[i] != 0)
            Fail("ENC001 FINAL FAIL generic Good stray slot");
}

void Enc001Final_RunRuntimeQa(void)
{
    MgbaOpen();
    SetSaveBlocksPointers();

    CheckRoute6Selectors();
    CheckGenericSelectorsUnaffected();

    QaLog("ENC001 FINAL RUNTIME PASS Route6 exact selectors generic weights preserved");
    for (;;);
}
