#include "global.h"
#include "gflib.h"
#include "main.h"
#include "new_game.h"
#include "random.h"
#include "overworld.h"
#include "constants/maps.h"
#include "load_save.h"
#include "item_menu.h"
#include "tm_case.h"
#include "berry_pouch.h"
#include "quest_log.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "mail_data.h"
#include "play_time.h"
#include "money.h"
#include "battle_records.h"
#include "pokemon_size_record.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "item.h"
#include "player_pc.h"
#include "berry.h"
#include "easy_chat.h"
#include "union_room_chat.h"
#include "mystery_gift.h"
#include "renewable_hidden_items.h"
#include "trainer_tower.h"
#include "script.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "event_scripts.h"

struct NewGamePlusCarryover
{
    u8 trainerId[TRAINER_ID_LENGTH];
    u32 encryptionKey;
    u16 registeredItem;
    struct ItemSlot pcItems[PC_ITEMS_COUNT];
    struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    struct ItemSlot bagPocket_Berries[BAG_BERRIES_COUNT];
    struct PokemonStorage pokemonStorage;
};

// this file's functions
static void ResetMiniGamesResults(void);
static struct NewGamePlusCarryover *CreateNewGamePlusCarryover(void);
static void RestoreNewGamePlusCarryover(struct NewGamePlusCarryover *carryover);
static bool8 MigrateNewGamePlusPartyToStorage(struct NewGamePlusCarryover *carryover);
static bool8 HasNewGamePlusCarryoverCapacity(void);

// EWRAM vars
EWRAM_DATA bool8 gDifferentSaveFile = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < 4; i++)
        dst[i] = src[i];
}

// Title-menu eligibility is governed by Hall-of-Fame completion. Capacity is
// enforced again at the destructive boundary so an overfull collection can
// never turn NEW GAME+ into an ordinary save reset.
bool8 CanStartNewGamePlus(void)
{
    return TRUE;
}

static bool8 HasNewGamePlusCarryoverCapacity(void)
{
    u16 freeStorageSlots = 0;
    u8 box;
    u8 slot;

    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (slot = 0; slot < IN_BOX_COUNT; slot++)
        {
            if (GetBoxMonData(&gPokemonStoragePtr->boxes[box][slot], MON_DATA_SPECIES) == SPECIES_NONE)
                freeStorageSlots++;
        }
    }

    if (gPokemonStoragePtr->ngPlusStorageMagic == NG_PLUS_STORAGE_MAGIC)
    {
        for (slot = 0; slot < NG_PLUS_STORAGE_COUNT; slot++)
        {
            if (GetBoxMonData(&gPokemonStoragePtr->ngPlusStorage[slot], MON_DATA_SPECIES) == SPECIES_NONE)
                freeStorageSlots++;
        }
    }
    else
    {
        freeStorageSlots += NG_PLUS_STORAGE_COUNT;
    }

    return gSaveBlock1Ptr->playerPartyCount <= freeStorageSlots;
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_MID;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_HELP;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

static void ClearBattleTower(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->battleTower, sizeof(gSaveBlock2Ptr->battleTower));
}

static void WarpToPlayersRoom(void)
{
    SetWarpDestination(MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}

static bool8 MigrateNewGamePlusPartyToStorage(struct NewGamePlusCarryover *carryover)
{
    u8 partyIndex;
    u8 box;
    u8 slot;
    u8 reserveSlot;

    InitNewGamePlusStorageReserve(&carryover->pokemonStorage);

    for (partyIndex = 0; partyIndex < gSaveBlock1Ptr->playerPartyCount; partyIndex++)
    {
        bool8 placed = FALSE;

        for (box = 0; box < TOTAL_BOXES_COUNT && !placed; box++)
        {
            for (slot = 0; slot < IN_BOX_COUNT; slot++)
            {
                if (GetBoxMonData(&carryover->pokemonStorage.boxes[box][slot], MON_DATA_SPECIES) == SPECIES_NONE)
                {
                    carryover->pokemonStorage.boxes[box][slot] = gSaveBlock1Ptr->playerParty[partyIndex].box;
                    placed = TRUE;
                    break;
                }
            }
        }

        if (!placed)
        {
            for (reserveSlot = 0; reserveSlot < NG_PLUS_STORAGE_COUNT; reserveSlot++)
            {
                if (GetBoxMonData(&carryover->pokemonStorage.ngPlusStorage[reserveSlot], MON_DATA_SPECIES) == SPECIES_NONE)
                {
                    carryover->pokemonStorage.ngPlusStorage[reserveSlot] = gSaveBlock1Ptr->playerParty[partyIndex].box;
                    placed = TRUE;
                    break;
                }
            }
        }

        if (!placed)
            return FALSE;
    }

    return TRUE;
}

static struct NewGamePlusCarryover *CreateNewGamePlusCarryover(void)
{
    struct NewGamePlusCarryover *carryover;

    if (!HasNewGamePlusCarryoverCapacity())
        return NULL;

    carryover = Alloc(sizeof(*carryover));
    if (carryover == NULL)
        return NULL;

    CopyTrainerId(carryover->trainerId, gSaveBlock2Ptr->playerTrainerId);
    carryover->encryptionKey = gSaveBlock2Ptr->encryptionKey;
    carryover->registeredItem = gSaveBlock1Ptr->registeredItem;
    memcpy(carryover->pcItems, gSaveBlock1Ptr->pcItems, sizeof(carryover->pcItems));
    memcpy(carryover->bagPocket_Items, gSaveBlock1Ptr->bagPocket_Items, sizeof(carryover->bagPocket_Items));
    memcpy(carryover->bagPocket_KeyItems, gSaveBlock1Ptr->bagPocket_KeyItems, sizeof(carryover->bagPocket_KeyItems));
    memcpy(carryover->bagPocket_PokeBalls, gSaveBlock1Ptr->bagPocket_PokeBalls, sizeof(carryover->bagPocket_PokeBalls));
    memcpy(carryover->bagPocket_TMHM, gSaveBlock1Ptr->bagPocket_TMHM, sizeof(carryover->bagPocket_TMHM));
    memcpy(carryover->bagPocket_Berries, gSaveBlock1Ptr->bagPocket_Berries, sizeof(carryover->bagPocket_Berries));
    carryover->pokemonStorage = *gPokemonStoragePtr;

    if (!MigrateNewGamePlusPartyToStorage(carryover))
    {
        Free(carryover);
        return NULL;
    }

    return carryover;
}

static void RestoreNewGamePlusCarryover(struct NewGamePlusCarryover *carryover)
{
    CopyTrainerId(gSaveBlock2Ptr->playerTrainerId, carryover->trainerId);
    gSaveBlock1Ptr->registeredItem = carryover->registeredItem;
    memcpy(gSaveBlock1Ptr->pcItems, carryover->pcItems, sizeof(carryover->pcItems));
    memcpy(gSaveBlock1Ptr->bagPocket_Items, carryover->bagPocket_Items, sizeof(carryover->bagPocket_Items));
    memcpy(gSaveBlock1Ptr->bagPocket_KeyItems, carryover->bagPocket_KeyItems, sizeof(carryover->bagPocket_KeyItems));
    memcpy(gSaveBlock1Ptr->bagPocket_PokeBalls, carryover->bagPocket_PokeBalls, sizeof(carryover->bagPocket_PokeBalls));
    memcpy(gSaveBlock1Ptr->bagPocket_TMHM, carryover->bagPocket_TMHM, sizeof(carryover->bagPocket_TMHM));
    memcpy(gSaveBlock1Ptr->bagPocket_Berries, carryover->bagPocket_Berries, sizeof(carryover->bagPocket_Berries));
    *gPokemonStoragePtr = carryover->pokemonStorage;

    // Bag quantities are encrypted with the source save's key. The normal
    // new-game path uses key 0 until the save blocks are moved later, so
    // re-key the restored quantities to 0 without disturbing the freshly
    // initialized money, game stats, or other encrypted new-run fields.
    gSaveBlock2Ptr->encryptionKey = carryover->encryptionKey;
    ApplyNewEncryptionKeyToBagItems_(0);
    gSaveBlock2Ptr->encryptionKey = 0;
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagCursorPositions();
    ResetTMCaseCursorPos();
    BerryPouch_CursorResetToTop();
    ResetQuestLog();
    SeedWildEncounterRng(Random());
    ResetSpecialVars();
}

void NewGameInitData(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];
    u8 greenName[PLAYER_NAME_LENGTH + 1];
    u16 samGameMode = gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START];
    struct NewGamePlusCarryover *newGamePlusCarryover = NULL;

    if (gNewGamePlusRequested)
    {
        newGamePlusCarryover = CreateNewGamePlusCarryover();
        if (newGamePlusCarryover == NULL)
        {
            // Capacity/allocation failure must never degrade into an ordinary
            // new-game reset, because that would destroy the completed save.
            gNewGamePlusRequested = FALSE;
            DoSoftReset();
            return;
        }
    }

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    StringCopy(greenName, gSaveBlock1Ptr->samEdition.greenName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ClearBattleTower();
    ClearSav1();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->unkFlag1 = TRUE;
    gSaveBlock2Ptr->unkFlag2 = FALSE;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    if (gNewGamePlusRequested)
        FlagClear(FLAG_SYS_GAME_CLEAR);
    ResetFameChecker();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    ResetGameStats();
    ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    EnableNationalPokedex_RSE();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();
    NewGameInitPCItems();
    ClearEnigmaBerries();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    UnionRoomChat_InitializeRegisteredTexts();
    ResetMiniGamesResults();
    ClearMysteryGift();
    SetAllRenewableItemFlags();
    WarpToPlayersRoom();
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    StringCopy(gSaveBlock1Ptr->samEdition.greenName, greenName);
    gSaveBlock1Ptr->vars[VAR_SAM_GAME_MODE - VARS_START] = samGameMode;
    ResetTrainerTowerResults();

    if (newGamePlusCarryover != NULL)
    {
        RestoreNewGamePlusCarryover(newGamePlusCarryover);
        FlagSet(FLAG_0x33B);
        Free(newGamePlusCarryover);
    }
    gNewGamePlusRequested = FALSE;
}

static void ResetMiniGamesResults(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}
