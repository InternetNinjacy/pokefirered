#ifndef GUARD_CONSTANTS_TRADE_H
#define GUARD_CONSTANTS_TRADE_H

// TODO: document trade.c and trade_scene.c with corresponding macros
// and examine if these are correct

#define TRADE_PLAYER  0
#define TRADE_PARTNER 1

#define LINK_TRADE_TIMEOUT 300

// Sam Edition in-game Trade IDs, ordered by progression.
#define INGAME_TRADE_JOULE   0
#define INGAME_TRADE_KITSUNE 1
#define INGAME_TRADE_SCORIA  2
#define INGAME_TRADE_IMUGI   3
#define INGAME_TRADE_TALUS   4
#define INGAME_TRADE_BRINE   5
#define INGAME_TRADE_MATRON  6
#define INGAME_TRADE_STRATA  7
#define INGAME_TRADE_SELKIE  8

// Pokémon Original Trainer IDs for the nine standard Sam Edition NPC trades.
// These are monster OT IDs, not TRAINER_* battle-table IDs.
#define OTID_NPC_TRADE_MARA   51001
#define OTID_NPC_TRADE_REINA  51002
#define OTID_NPC_TRADE_DEXTER 51003
#define OTID_NPC_TRADE_MIN    51004
#define OTID_NPC_TRADE_CLAY   51005
#define OTID_NPC_TRADE_MARIS  51006
#define OTID_NPC_TRADE_HELEN  51007
#define OTID_NPC_TRADE_GEOFF  51008
#define OTID_NPC_TRADE_INGRID 51009

// Return values for CanTradeSelectedMon and CanSpinTradeMon
#define CAN_TRADE_MON              0
#define CANT_TRADE_LAST_MON        1
#define CANT_TRADE_NATIONAL        2
#define CANT_TRADE_EGG_YET         3
#define CANT_TRADE_INVALID_MON     4
#define CANT_TRADE_PARTNER_EGG_YET 5

// Return values for CheckValidityOfTradeMons
#define PLAYER_MON_INVALID   0
#define BOTH_MONS_VALID      1
#define PARTNER_MON_INVALID  2

// Return values for GetGameProgressForLinkTrade
#define TRADE_BOTH_PLAYERS_READY      0
#define TRADE_PLAYER_NOT_READY        1
#define TRADE_PARTNER_NOT_READY       2

// Message indexes for sUnionRoomTradeMessages
#define UR_TRADE_MSG_NONE                         0
#define UR_TRADE_MSG_NOT_MON_PARTNER_WANTS        1
#define UR_TRADE_MSG_NOT_EGG                      2
#define UR_TRADE_MSG_MON_CANT_BE_TRADED_1         3
#define UR_TRADE_MSG_MON_CANT_BE_TRADED_2         4
#define UR_TRADE_MSG_PARTNERS_MON_CANT_BE_TRADED  5
#define UR_TRADE_MSG_EGG_CANT_BE_TRADED           6
#define UR_TRADE_MSG_PARTNER_CANT_ACCEPT_MON      7
#define UR_TRADE_MSG_CANT_TRADE_WITH_PARTNER_1    8
#define UR_TRADE_MSG_CANT_TRADE_WITH_PARTNER_2    9

// Return values for CanRegisterMonForTradingBoard
#define CAN_REGISTER_MON   0
#define CANT_REGISTER_MON  1
#define CANT_REGISTER_EGG  2

#endif // GUARD_CONSTANTS_TRADE_H
