#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/vars.h"

#define CORE004_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define CORE004_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static void Core004Log(const char *text)
{
    u32 i = 0;

    while (text[i] != '\0' && i < 255)
    {
        CORE004_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    CORE004_MGBA_DEBUG_STRING[i] = '\0';
    *CORE004_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    Core004Log(text);
    for (;;);
}

static void SetHp(struct Pokemon *mon, u16 hp)
{
    SetMonData(mon, MON_DATA_HP, &hp);
}

static void SetPermanentDead(struct Pokemon *mon, bool8 value)
{
    SetMonData(mon, MON_DATA_SAM_PERMANENT_DEAD, &value);
}

void Core004_RunRuntimeQa(void)
{
    bool8 trueValue = TRUE;
    u16 maxHp;
    u16 hp;

    MgbaOpen();
    ClearSav2();
    ClearSav1();
    ZeroPlayerPartyMons();

    VarSet(VAR_SAM_GAME_MODE, 1);

    CreateMon(&gPlayerParty[0], SPECIES_RATTATA, 10, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    CreateMon(&gPlayerParty[1], SPECIES_PIDGEY, 10, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 2;

    SetHp(&gPlayerParty[0], 0);
    SetPermanentDead(&gPlayerParty[0], trueValue);
    SetHp(&gPlayerParty[1], 1);

    HealPlayerParty();

    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != 0)
        Fail("CORE004 FAIL center healed permanent-dead mon");

    maxHp = GetMonData(&gPlayerParty[1], MON_DATA_MAX_HP);
    if (GetMonData(&gPlayerParty[1], MON_DATA_HP) != maxHp)
        Fail("CORE004 FAIL center did not heal living mon");

    if (!ExecuteTableBasedItemEffect(&gPlayerParty[0], ITEM_REVIVE, 0, 0))
        Fail("CORE004 FAIL Revive reported effect");
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != 0)
        Fail("CORE004 FAIL Revive restored permanent-dead mon");

    if (!ExecuteTableBasedItemEffect(&gPlayerParty[0], ITEM_MAX_REVIVE, 0, 0))
        Fail("CORE004 FAIL Max Revive reported effect");
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != 0)
        Fail("CORE004 FAIL Max Revive restored permanent-dead mon");

    if (!ExecuteTableBasedItemEffect(&gPlayerParty[0], ITEM_SACRED_ASH, 0, 0))
        Fail("CORE004 FAIL Sacred Ash reported effect");
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != 0)
        Fail("CORE004 FAIL Sacred Ash restored permanent-dead mon");

    if (!PokemonItemUseNoEffect(&gPlayerParty[0], ITEM_REVIVE, 0, 0))
        Fail("CORE004 FAIL Revive no-effect check allowed use");
    if (!PokemonItemUseNoEffect(&gPlayerParty[0], ITEM_MAX_REVIVE, 0, 0))
        Fail("CORE004 FAIL Max Revive no-effect check allowed use");
    if (!PokemonItemUseNoEffect(&gPlayerParty[0], ITEM_SACRED_ASH, 0, 0))
        Fail("CORE004 FAIL Sacred Ash no-effect check allowed use");

    VarSet(VAR_SAM_GAME_MODE, 0);

    if (ExecuteTableBasedItemEffect(&gPlayerParty[0], ITEM_REVIVE, 0, 0))
        Fail("CORE004 FAIL Standard Revive blocked");
    hp = GetMonData(&gPlayerParty[0], MON_DATA_HP);
    if (hp == 0)
        Fail("CORE004 FAIL Standard Revive did not restore HP");

    SetHp(&gPlayerParty[0], 0);
    HealPlayerParty();
    maxHp = GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP);
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != maxHp)
        Fail("CORE004 FAIL Standard center healing changed");

    Core004Log("CORE004 PASS center revive maxrevive sacredash standard");
    for (;;);
}
