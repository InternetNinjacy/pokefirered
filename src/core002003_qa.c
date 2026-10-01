#include "global.h"
#include "daycare.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/vars.h"

#define CORE_QA_STAGE 0xC3
#define CORE_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define CORE_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern void MarkSamOriginalStarter(void);
extern void BoxMonAtToMon(u8 boxId, u8 boxPosition, struct Pokemon *dst);
extern void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon *src);

static void CoreQaLog(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        CORE_QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    CORE_QA_MGBA_DEBUG_STRING[i] = '\0';
    *CORE_QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    CoreQaLog(text);
    for (;;);
}

static void SetHp(struct Pokemon *mon, u16 hp)
{
    SetMonData(mon, MON_DATA_HP, &hp);
}

static void RunFreshStateTests(void)
{
    bool8 trueValue = TRUE;
    u16 species;

    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));
    ZeroPlayerPartyMons();

    VarSet(VAR_SAM_GAME_MODE, 1);

    CreateMon(&gPlayerParty[0], SPECIES_BULBASAUR, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 1;
    MarkSamOriginalStarter();

    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORE002003 FAIL starter marker not set");

    CreateMon(&gPlayerParty[1], SPECIES_BULBASAUR, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 2;
    if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORE002003 FAIL same species protected");

    SetHp(&gPlayerParty[1], 0);
    TryMarkMonPermanentDead(&gPlayerParty[1]);
    if (!GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL ordinary faint not marked");

    SetHp(&gPlayerParty[0], 0);
    TryMarkMonPermanentDead(&gPlayerParty[0]);
    if (GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL starter marked dead");

    SetBoxMonAt(0, 0, &gPlayerParty[1].box);
    SetBoxMonAt(0, 1, &gPlayerParty[0].box);
    ZeroMonData(&gPlayerParty[0]);
    ZeroMonData(&gPlayerParty[1]);
    BoxMonAtToMon(0, 1, &gPlayerParty[0]);
    BoxMonAtToMon(0, 0, &gPlayerParty[1]);

    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER)
     || !GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL party PC party persistence");

    species = SPECIES_IVYSAUR;
    SetMonData(&gPlayerParty[0], MON_DATA_SPECIES, &species);
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORE002003 FAIL evolution lost starter marker");

    CreateEgg(&gPlayerParty[2], SPECIES_BULBASAUR, FALSE);
    if (GetMonData(&gPlayerParty[2], MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(&gPlayerParty[2], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL egg inherited Sam state");

    CreateMon(&gPlayerParty[3], SPECIES_RATTATA, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    VarSet(VAR_SAM_GAME_MODE, 0);
    SetHp(&gPlayerParty[3], 0);
    TryMarkMonPermanentDead(&gPlayerParty[3]);
    if (GetMonData(&gPlayerParty[3], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL Standard Mode changed");

    VarSet(VAR_SAM_GAME_MODE, 1);
    gSaveBlock1Ptr->samEdition.futureExpansion[2] = CORE_QA_STAGE;
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("CORE002003 FAIL save");

    CoreQaLog("CORE002003 PHASE1 PASS state saved");
    for (;;);
}

static void RunReloadTests(void)
{
    if (VarGet(VAR_SAM_GAME_MODE) != 1)
        Fail("CORE002003 FAIL mode persistence");
    if (gSaveBlock1Ptr->samEdition.futureExpansion[2] != CORE_QA_STAGE)
        Fail("CORE002003 FAIL stage persistence");
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORE002003 FAIL starter save reload");
    if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORE002003 FAIL same species reload protection");
    if (!GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL dead save reload");
    if (GetMonData(&gPlayerParty[2], MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(&gPlayerParty[2], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL egg reload state");
    if (!GetBoxMonData(GetBoxedMonPtr(0, 0), MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORE002003 FAIL boxed dead reload");
    if (!GetBoxMonData(GetBoxedMonPtr(0, 1), MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORE002003 FAIL boxed starter reload");
    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_IVYSAUR)
        Fail("CORE002003 FAIL evolved species reload");

    CoreQaLog("CORE002003 PASS runtime persistence storage evolution species egg standard");
    for (;;);
}

void Core002003_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);

    if (loadStatus != SAVE_STATUS_OK)
        RunFreshStateTests();

    RunReloadTests();
}
