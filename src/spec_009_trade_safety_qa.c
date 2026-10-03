#include "global.h"
#include "gba/isagbprint.h"
#include "link.h"
#include "link_rfu.h"
#include "pokemon.h"
#include "trade.h"
#include "constants/game_version.h"
#include "constants/species.h"
#include "constants/trade.h"

#define QA_MGBA_DEBUG_ENABLE ((vu16 *)0x4FFF780)
#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static void Log(const char *text)
{
    u32 i = 0;

    *QA_MGBA_DEBUG_ENABLE = 0xC0DE;
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
    Log(text);
    for (;;);
}

static bool32 MonsEqual(const struct Pokemon *a, const struct Pokemon *b)
{
    const u8 *aa = (const u8 *)a;
    const u8 *bb = (const u8 *)b;
    u32 i;

    for (i = 0; i < sizeof(*a); i++)
    {
        if (aa[i] != bb[i])
            return FALSE;
    }
    return TRUE;
}

static void SetOnlyPartyMon(u16 species)
{
    CpuFill16(0, gPlayerParty, sizeof(gPlayerParty));
    CreateMon(&gPlayerParty[0], species, 20, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static void SetCablePartner(bool8 samCompatible)
{
    CpuFill16(0, gLinkPlayers, sizeof(gLinkPlayers));
    gWirelessCommType = 0;
    gLinkStatus = 0;
    gReceivedRemoteLinkPlayers = TRUE;
    gLinkPlayers[1].version = VERSION_FIRE_RED;
    gLinkPlayers[1].neverRead = samCompatible;
}

static struct RfuGameCompatibilityData MakeRfuPeer(bool8 samCompatible)
{
    struct RfuGameCompatibilityData peer = {0};

    peer.version = VERSION_FIRE_RED;
    peer.hasNationalDex = TRUE;
    peer.canLinkNationally = TRUE;
    peer.gameClear = TRUE;
    peer.unknown = samCompatible;
    return peer;
}

static void CheckCableGate(u16 species)
{
    struct Pokemon before;

    SetOnlyPartyMon(species);
    before = gPlayerParty[0];

    SetCablePartner(FALSE);
    if (GetGameProgressForLinkTrade() != TRADE_PLAYER_NOT_READY)
        Fail("SPEC009TRADE QA FAIL legacy cable allowed");
    if (!MonsEqual(&before, &gPlayerParty[0]))
        Fail("SPEC009TRADE QA FAIL legacy gate mutated mon");

    SetCablePartner(TRUE);
    if (GetGameProgressForLinkTrade() != TRADE_BOTH_PLAYERS_READY)
        Fail("SPEC009TRADE QA FAIL Sam cable blocked");
    if (!MonsEqual(&before, &gPlayerParty[0]))
        Fail("SPEC009TRADE QA FAIL Sam gate mutated mon");
}

static void CheckUnionRoomGate(u16 species)
{
    struct RfuGameCompatibilityData local = MakeRfuPeer(TRUE);
    struct RfuGameCompatibilityData legacy = MakeRfuPeer(FALSE);
    struct RfuGameCompatibilityData sam = MakeRfuPeer(TRUE);
    u8 requestedType = gSpeciesInfo[species].types[0];

    if (GetUnionRoomTradeMessageId(local, legacy, species, SPECIES_PIKACHU,
                                   requestedType, species, TRUE)
        != UR_TRADE_MSG_MON_CANT_BE_TRADED_2)
        Fail("SPEC009TRADE QA FAIL legacy RFU allowed");

    if (GetUnionRoomTradeMessageId(local, sam, species, SPECIES_PIKACHU,
                                   requestedType, species, TRUE)
        != UR_TRADE_MSG_NONE)
        Fail("SPEC009TRADE QA FAIL Sam RFU blocked");

    if (GetUnionRoomTradeMessageId(local, legacy, SPECIES_PIKACHU, species,
                                   TYPE_ELECTRIC, SPECIES_PIKACHU, TRUE)
        != UR_TRADE_MSG_PARTNERS_MON_CANT_BE_TRADED)
        Fail("SPEC009TRADE QA FAIL legacy inbound custom");

    if (GetUnionRoomTradeMessageId(local, sam, SPECIES_PIKACHU, species,
                                   TYPE_ELECTRIC, SPECIES_PIKACHU, TRUE)
        != UR_TRADE_MSG_NONE)
        Fail("SPEC009TRADE QA FAIL Sam inbound custom");

    if (CanRegisterMonForTradingBoard(local, species, species, TRUE) != CANT_REGISTER_MON)
        Fail("SPEC009TRADE QA FAIL board advertised custom");
}

static void CheckStockUnaffected(void)
{
    struct RfuGameCompatibilityData local = MakeRfuPeer(TRUE);
    struct RfuGameCompatibilityData legacy = MakeRfuPeer(FALSE);

    SetOnlyPartyMon(SPECIES_PIKACHU);
    SetCablePartner(FALSE);
    if (GetGameProgressForLinkTrade() != TRADE_BOTH_PLAYERS_READY)
        Fail("SPEC009TRADE QA FAIL stock cable changed");

    if (GetUnionRoomTradeMessageId(local, legacy, SPECIES_PIKACHU, SPECIES_RATTATA,
                                   TYPE_ELECTRIC, SPECIES_PIKACHU, TRUE)
        != UR_TRADE_MSG_NONE)
        Fail("SPEC009TRADE QA FAIL stock RFU changed");

    if (CanRegisterMonForTradingBoard(local, SPECIES_PIKACHU, SPECIES_PIKACHU, TRUE)
        != CAN_REGISTER_MON)
        Fail("SPEC009TRADE QA FAIL stock board changed");
}

static void CheckSpeciesIds(void)
{
    struct Pokemon copy;
    const u16 species[] = {SPECIES_LEAFEON, SPECIES_ECTOCEON, SPECIES_RHYPERIOR};
    u32 i;

    if (SPECIES_LEAFEON != 412 || SPECIES_ECTOCEON != 413
     || SPECIES_RHYPERIOR != 414 || SPECIES_EGG != 415)
        Fail("SPEC009TRADE QA FAIL species IDs changed");

    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        SetOnlyPartyMon(species[i]);
        copy = gPlayerParty[0];
        if (GetMonData(&copy, MON_DATA_SPECIES) != species[i])
            Fail("SPEC009TRADE QA FAIL species truncation");
    }
}

void Spec009TradeSafetyQa_RunRuntimeQa(void)
{
    CheckSpeciesIds();
    CheckCableGate(SPECIES_LEAFEON);
    CheckCableGate(SPECIES_ECTOCEON);
    CheckCableGate(SPECIES_RHYPERIOR);
    CheckUnionRoomGate(SPECIES_LEAFEON);
    CheckUnionRoomGate(SPECIES_ECTOCEON);
    CheckUnionRoomGate(SPECIES_RHYPERIOR);
    CheckStockUnaffected();

    Log("SPEC009TRADE QA PASS cable RFU custom safety stock unchanged");
    for (;;);
}
