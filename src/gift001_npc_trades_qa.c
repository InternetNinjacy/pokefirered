#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "save.h"
#include "string_util.h"
#include "trade_scene.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trade.h"

#define NPC_TRADE_QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define NPC_TRADE_QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

struct NpcTradeQaExpected
{
    u16 requestedSpecies;
    u16 receivedSpecies;
    u8 level;
    u8 gender;
    u8 nature;
    u16 heldItem;
    u32 otId;
    const u8 *nickname;
    const u8 *otName;
    u16 moves[MAX_MON_MOVES];
};

static const u8 sPlayerName[] = _("SAM");
static const u8 sJoule[] = _("JOULE");
static const u8 sMara[] = _("MARA");
static const u8 sKitsune[] = _("KITSUNE");
static const u8 sReina[] = _("REINA");
static const u8 sScoria[] = _("SCORIA");
static const u8 sDexter[] = _("DEXTER");
static const u8 sImugi[] = _("IMUGI");
static const u8 sMin[] = _("MIN");
static const u8 sTalus[] = _("TALUS");
static const u8 sClay[] = _("CLAY");
static const u8 sBrine[] = _("BRINE");
static const u8 sMaris[] = _("MARIS");
static const u8 sMatron[] = _("MATRON");
static const u8 sHelen[] = _("HELEN");
static const u8 sStrata[] = _("STRATA");
static const u8 sGeoff[] = _("GEOFF");
static const u8 sSelkie[] = _("SELKIE");
static const u8 sIngrid[] = _("INGRID");

static const u16 sTradeFlags[] =
{
    FLAG_DID_MIMIEN_TRADE,
    FLAG_DID_ZYNX_TRADE,
    FLAG_DID_MS_NIDO_TRADE,
    FLAG_DID_CH_DING_TRADE,
    FLAG_DID_NINA_TRADE,
    FLAG_DID_MARC_TRADE,
    FLAG_DID_ESPHERE_TRADE,
    FLAG_DID_TANGENY_TRADE,
    FLAG_DID_SEELOR_TRADE,
};

static const struct NpcTradeQaExpected sExpected[] =
{
    {
        SPECIES_CLEFAIRY, SPECIES_ELECTABUZZ, 20, MON_MALE, NATURE_HASTY,
        ITEM_NONE, OTID_NPC_TRADE_MARA, sJoule, sMara,
        {MOVE_THUNDER_SHOCK, MOVE_QUICK_ATTACK, MOVE_LEER, MOVE_SWIFT},
    },
    {
        SPECIES_CLEFABLE, SPECIES_NINETALES, 24, MON_FEMALE, NATURE_TIMID,
        ITEM_CHARCOAL, OTID_NPC_TRADE_REINA, sKitsune, sReina,
        {MOVE_EMBER, MOVE_QUICK_ATTACK, MOVE_CONFUSE_RAY, MOVE_WILL_O_WISP},
    },
    {
        SPECIES_PIKACHU, SPECIES_MAGMAR, 22, MON_MALE, NATURE_TIMID,
        ITEM_NONE, OTID_NPC_TRADE_DEXTER, sScoria, sDexter,
        {MOVE_FIRE_PUNCH, MOVE_SMOG, MOVE_LEER, MOVE_EMBER},
    },
    {
        SPECIES_EKANS, SPECIES_BAGON, 20, MON_MALE, NATURE_JOLLY,
        ITEM_DRAGON_FANG, OTID_NPC_TRADE_MIN, sImugi, sMin,
        {MOVE_BITE, MOVE_HEADBUTT, MOVE_FOCUS_ENERGY, MOVE_DRAGON_BREATH},
    },
    {
        SPECIES_PARASECT, SPECIES_GRAVELER, 25, MON_MALE, NATURE_ADAMANT,
        ITEM_QUICK_CLAW, OTID_NPC_TRADE_CLAY, sTalus, sClay,
        {MOVE_ROCK_THROW, MOVE_MAGNITUDE, MOVE_BRICK_BREAK, MOVE_DEFENSE_CURL},
    },
    {
        SPECIES_RAPIDASH, SPECIES_CLOYSTER, 32, MON_FEMALE, NATURE_IMPISH,
        ITEM_NEVER_MELT_ICE, OTID_NPC_TRADE_MARIS, sBrine, sMaris,
        {MOVE_AURORA_BEAM, MOVE_CLAMP, MOVE_SUPERSONIC, MOVE_PROTECT},
    },
    {
        SPECIES_MAGNETON, SPECIES_KANGASKHAN, 35, MON_FEMALE, NATURE_ADAMANT,
        ITEM_SILK_SCARF, OTID_NPC_TRADE_HELEN, sMatron, sHelen,
        {MOVE_MEGA_PUNCH, MOVE_BITE, MOVE_FAKE_OUT, MOVE_BRICK_BREAK},
    },
    {
        SPECIES_SEADRA, SPECIES_RHYDON, 36, MON_MALE, NATURE_BRAVE,
        ITEM_SOFT_SAND, OTID_NPC_TRADE_GEOFF, sStrata, sGeoff,
        {MOVE_ROCK_SLIDE, MOVE_DIG, MOVE_STOMP, MOVE_SCARY_FACE},
    },
    {
        SPECIES_WEEZING, SPECIES_DEWGONG, 37, MON_FEMALE, NATURE_CALM,
        ITEM_CHESTO_BERRY, OTID_NPC_TRADE_INGRID, sSelkie, sIngrid,
        {MOVE_AURORA_BEAM, MOVE_BUBBLE_BEAM, MOVE_ENCORE, MOVE_REST},
    },
};

static void NpcTradeQaLog(const char *text)
{
    u32 i = 0;

    while (text[i] != '\0' && i < 255)
    {
        NPC_TRADE_QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    NPC_TRADE_QA_MGBA_DEBUG_STRING[i] = '\0';
    *NPC_TRADE_QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void NpcTradeQaFail(const char *text)
{
    NpcTradeQaLog(text);
    for (;;);
}

static void ResetState(void)
{
    ClearSav2();
    ClearSav1();
    ZeroPlayerPartyMons();
    CpuFill16(0, gEnemyParty, sizeof(gEnemyParty));
    gPlayerPartyCount = 0;

    StringCopy(gSaveBlock2Ptr->playerName, sPlayerName);
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;
}

static void CheckMon(struct Pokemon *mon, const struct NpcTradeQaExpected *expected)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u8 i;

    if (GetMonData(mon, MON_DATA_SPECIES) != expected->receivedSpecies)
        NpcTradeQaFail("NPC TRADE QA FAIL received species");
    NpcTradeQaLog("NPC TRADE QA FIELD species PASS");
    if (GetMonData(mon, MON_DATA_LEVEL) != expected->level)
        NpcTradeQaFail("NPC TRADE QA FAIL fixed level");
    NpcTradeQaLog("NPC TRADE QA FIELD level PASS");
    if (GetMonGender(mon) != expected->gender)
        NpcTradeQaFail("NPC TRADE QA FAIL gender");
    NpcTradeQaLog("NPC TRADE QA FIELD gender PASS");
    if (GetNature(mon) != expected->nature)
        NpcTradeQaFail("NPC TRADE QA FAIL nature");
    NpcTradeQaLog("NPC TRADE QA FIELD nature PASS");
    if (GetMonData(mon, MON_DATA_HELD_ITEM) != expected->heldItem)
        NpcTradeQaFail("NPC TRADE QA FAIL held item");
    NpcTradeQaLog("NPC TRADE QA FIELD item PASS");
    if (GetMonData(mon, MON_DATA_OT_ID) != expected->otId)
        NpcTradeQaFail("NPC TRADE QA FAIL OT ID");
    NpcTradeQaLog("NPC TRADE QA FIELD otid PASS");

    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    if (StringCompare(nickname, expected->nickname))
        NpcTradeQaFail("NPC TRADE QA FAIL nickname");
    NpcTradeQaLog("NPC TRADE QA FIELD nickname PASS");
    GetMonData(mon, MON_DATA_OT_NAME, otName);
    if (StringCompare(otName, expected->otName))
        NpcTradeQaFail("NPC TRADE QA FAIL OT name");
    NpcTradeQaLog("NPC TRADE QA FIELD otname PASS");

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMonData(mon, MON_DATA_MOVE1 + i) != expected->moves[i])
            NpcTradeQaFail("NPC TRADE QA FAIL moves");
    }
    NpcTradeQaLog("NPC TRADE QA FIELD moves PASS");

    if (!IsTradedMon(mon))
        NpcTradeQaFail("NPC TRADE QA FAIL outsider ownership");
    NpcTradeQaLog("NPC TRADE QA FIELD outsider PASS");
}

static void LogTradePass(u8 tradeId)
{
    switch (tradeId)
    {
    case INGAME_TRADE_JOULE:   NpcTradeQaLog("NPC TRADE QA JOULE PASS"); break;
    case INGAME_TRADE_KITSUNE: NpcTradeQaLog("NPC TRADE QA KITSUNE PASS"); break;
    case INGAME_TRADE_SCORIA:  NpcTradeQaLog("NPC TRADE QA SCORIA PASS"); break;
    case INGAME_TRADE_IMUGI:   NpcTradeQaLog("NPC TRADE QA IMUGI PASS"); break;
    case INGAME_TRADE_TALUS:   NpcTradeQaLog("NPC TRADE QA TALUS PASS"); break;
    case INGAME_TRADE_BRINE:   NpcTradeQaLog("NPC TRADE QA BRINE PASS"); break;
    case INGAME_TRADE_MATRON:  NpcTradeQaLog("NPC TRADE QA MATRON PASS"); break;
    case INGAME_TRADE_STRATA:  NpcTradeQaLog("NPC TRADE QA STRATA PASS"); break;
    case INGAME_TRADE_SELKIE:  NpcTradeQaLog("NPC TRADE QA SELKIE PASS"); break;
    }
}

extern void Gift001NpcTradesQaSwap(u8 playerPartyIdx);

static void CheckRejectedSelections(void)
{
    u8 i;
    bool8 isEgg = TRUE;

    for (i = 0; i < ARRAY_COUNT(sExpected); i++)
    {
        ResetState();
        CreateMon(&gPlayerParty[0], SPECIES_BULBASAUR, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
        gPlayerPartyCount = 1;
        gSpecialVar_0x8004 = i;
        gSpecialVar_0x8005 = 0;
        if (GetTradeSpecies() == GetInGameTradeSpeciesInfo())
            NpcTradeQaFail("NPC TRADE QA FAIL wrong species accepted");

        ResetState();
        CreateMon(&gPlayerParty[0], sExpected[i].requestedSpecies, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
        SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &isEgg);
        gPlayerPartyCount = 1;
        gSpecialVar_0x8004 = i;
        gSpecialVar_0x8005 = 0;
        if (GetTradeSpecies() != SPECIES_NONE)
            NpcTradeQaFail("NPC TRADE QA FAIL egg accepted");

        ResetState();
        gSpecialVar_0x8004 = i;
        gSpecialVar_0x8005 = 0;
        if (GetTradeSpecies() != SPECIES_NONE)
            NpcTradeQaFail("NPC TRADE QA FAIL empty selection accepted");
    }

    NpcTradeQaLog("NPC TRADE QA REJECTION PASS wrong egg empty");
}

static void CheckFullPartyTrade(void)
{
    const struct NpcTradeQaExpected *expected = &sExpected[INGAME_TRADE_JOULE];
    u8 i;

    ResetState();
    for (i = 0; i < PARTY_SIZE - 1; i++)
        CreateMon(&gPlayerParty[i], SPECIES_RATTATA, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    CreateMon(&gPlayerParty[PARTY_SIZE - 1], expected->requestedSpecies, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = PARTY_SIZE;

    gSpecialVar_0x8004 = INGAME_TRADE_JOULE;
    gSpecialVar_0x8005 = PARTY_SIZE - 1;

    if (GetTradeSpecies() != GetInGameTradeSpeciesInfo())
        NpcTradeQaFail("NPC TRADE QA FAIL full party requested species");
    CreateInGameTradePokemon();
    CheckMon(&gEnemyParty[0], expected);
    Gift001NpcTradesQaSwap(PARTY_SIZE - 1);

    if (gPlayerPartyCount != PARTY_SIZE)
        NpcTradeQaFail("NPC TRADE QA FAIL full party count");
    CheckMon(&gPlayerParty[PARTY_SIZE - 1], expected);
    for (i = 0; i < PARTY_SIZE - 1; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_RATTATA)
            NpcTradeQaFail("NPC TRADE QA FAIL full party neighbor changed");
    }

    NpcTradeQaLog("NPC TRADE QA FULL PARTY PASS swap slot5 no overflow");
}

static void SetAndCheckTradeFlags(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sTradeFlags); i++)
    {
        FlagClear(sTradeFlags[i]);
        if (FlagGet(sTradeFlags[i]))
            NpcTradeQaFail("NPC TRADE QA FAIL trade flag clear");
        FlagSet(sTradeFlags[i]);
        if (!FlagGet(sTradeFlags[i]))
            NpcTradeQaFail("NPC TRADE QA FAIL trade flag set");
    }
    NpcTradeQaLog("NPC TRADE QA FLAGS PASS all nine set");
}

static void CheckTradeFlagsPersisted(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sTradeFlags); i++)
    {
        if (!FlagGet(sTradeFlags[i]))
            NpcTradeQaFail("NPC TRADE QA FAIL trade flag reload");
    }
    NpcTradeQaLog("NPC TRADE QA FLAGS RELOAD PASS all nine");
}

static void CreateAndCheckTrade(u8 tradeId)
{
    const struct NpcTradeQaExpected *expected = &sExpected[tradeId];

    ResetState();
    CreateMon(&gPlayerParty[0], expected->requestedSpecies, 3, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 1;

    gSpecialVar_0x8004 = tradeId;
    gSpecialVar_0x8005 = 0;

    NpcTradeQaLog("NPC TRADE QA CREATE start");
    if (GetInGameTradeSpeciesInfo() != expected->requestedSpecies)
        NpcTradeQaFail("NPC TRADE QA FAIL requested species");
    NpcTradeQaLog("NPC TRADE QA CREATE requested PASS");

    CreateInGameTradePokemon();
    NpcTradeQaLog("NPC TRADE QA CREATE generated PASS");
    DebugPrintf("NPC TRADE QA VALUES trade=%u expectedSpecies=%u actualSpecies=%u level=%u", tradeId, expected->receivedSpecies, GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), GetMonData(&gEnemyParty[0], MON_DATA_LEVEL));
    CheckMon(&gEnemyParty[0], expected);
    LogTradePass(tradeId);
}

static void RunFresh(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sExpected); i++)
        CreateAndCheckTrade(i);

    CheckRejectedSelections();
    CheckFullPartyTrade();

    // Persist one representative authored trade plus every one-time trade
    // completion flag through a real flash save.
    CreateAndCheckTrade(INGAME_TRADE_IMUGI);
    CopyMon(&gPlayerParty[0], &gEnemyParty[0], sizeof(struct Pokemon));
    gPlayerPartyCount = 1;
    SetAndCheckTradeFlags();

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        NpcTradeQaFail("NPC TRADE QA FAIL save");

    NpcTradeQaLog("NPC TRADE QA PHASE1 PASS nine packages gating fullparty flags save");
    for (;;);
}

static void RunReload(void)
{
    u16 species;

    if (gPlayerPartyCount != 1)
        NpcTradeQaFail("NPC TRADE QA FAIL reload party");
    CheckMon(&gPlayerParty[0], &sExpected[INGAME_TRADE_IMUGI]);
    CheckTradeFlagsPersisted();

    // Ownership behavior must survive species evolution because it is stored
    // in authored OT metadata, not in the species.
    species = SPECIES_SHELGON;
    SetMonData(&gPlayerParty[0], MON_DATA_SPECIES, &species);
    if (!IsTradedMon(&gPlayerParty[0]))
        NpcTradeQaFail("NPC TRADE QA FAIL outsider lost at Shelgon");
    species = SPECIES_SALAMENCE;
    SetMonData(&gPlayerParty[0], MON_DATA_SPECIES, &species);
    if (!IsTradedMon(&gPlayerParty[0]))
        NpcTradeQaFail("NPC TRADE QA FAIL outsider lost at Salamence");

    NpcTradeQaLog("NPC TRADE QA PASS nine packages flags reload evolution ownership");
    for (;;);
}

void Gift001NpcTrades_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
