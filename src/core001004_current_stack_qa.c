#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "trade_scene.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "constants/vars.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

#define QA_STAGE_STANDARD_SAVED  0x41
#define QA_STAGE_PERMANENT_SAVED 0x42
#define QA_STAGE_INDEX 3

extern void MarkSamOriginalStarter(void);
extern void BoxMonAtToMon(u8 boxId, u8 boxPosition, struct Pokemon *dst);
extern void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon *src);

static const u8 sPlayerName[] = _("SAM");
static const u8 sImugi[] = _("IMUGI");
static const u8 sMin[] = _("MIN");

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

static void ResetParty(void)
{
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;
}

static void SetHp(struct Pokemon *mon, u16 hp)
{
    SetMonData(mon, MON_DATA_HP, &hp);
}

static void SetPermanentDead(struct Pokemon *mon, bool8 value)
{
    SetMonData(mon, MON_DATA_SAM_PERMANENT_DEAD, &value);
}

static void CheckStarterMode(u16 species, u16 expectedItem, u16 mode)
{
    bool8 marked;
    u16 evolvedSpecies;

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, mode);

    if (ScriptGiveSamStarter(species) != MON_GIVEN_TO_PARTY)
        Fail("CORECURRENT FAIL starter grant");
    MarkSamOriginalStarter();

    marked = GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER);
    if ((mode == 1 && !marked) || (mode == 0 && marked))
        Fail("CORECURRENT FAIL starter protection mode");

    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != expectedItem)
        Fail("CORECURRENT FAIL starter held item");

    if (species == SPECIES_EEVEE && GetMonGender(&gPlayerParty[0]) != MON_MALE)
        Fail("CORECURRENT FAIL Eevee gender");

    SetHp(&gPlayerParty[0], 0);
    TryMarkMonPermanentDead(&gPlayerParty[0]);
    if (GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL starter death");

    CreateMon(&gPlayerParty[1], species, 5, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 2;
    if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORECURRENT FAIL same species protected");

    SetHp(&gPlayerParty[1], 0);
    TryMarkMonPermanentDead(&gPlayerParty[1]);
    if (mode == 1 && !GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL permanent nonstarter");
    if (mode == 0 && GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL standard nonstarter");

    if (mode == 1)
    {
        if (species == SPECIES_EEVEE)
            evolvedSpecies = SPECIES_VAPOREON;
        else if (species == SPECIES_PICHU)
            evolvedSpecies = SPECIES_PIKACHU;
        else
            evolvedSpecies = SPECIES_DITTO;

        SetMonData(&gPlayerParty[0], MON_DATA_SPECIES, &evolvedSpecies);
        if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER))
            Fail("CORECURRENT FAIL evolution protection");
    }
}

static void CheckStandardHealingRegression(void)
{
    bool8 dead = TRUE;
    u16 maxHp;

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, 0);
    CreateMon(&gPlayerParty[0], SPECIES_RATTATA, 10, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 1;

    SetHp(&gPlayerParty[0], 0);
    TryMarkMonPermanentDead(&gPlayerParty[0]);
    if (GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL standard death marker");

    // A stale marker must not change Standard Mode behavior.
    SetPermanentDead(&gPlayerParty[0], dead);
    if (ExecuteTableBasedItemEffect(&gPlayerParty[0], ITEM_REVIVE, 0, 0))
        Fail("CORECURRENT FAIL standard Revive blocked");
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) == 0)
        Fail("CORECURRENT FAIL standard Revive no HP");

    SetHp(&gPlayerParty[0], 0);
    HealPlayerParty();
    maxHp = GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP);
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != maxHp)
        Fail("CORECURRENT FAIL standard center healing");
}

static void CheckPermanentHealing(void)
{
    u16 maxHp;

    // slot 0 = protected starter, slot 1 = permanent-dead ordinary mon
    SetHp(&gPlayerParty[0], 1);
    SetHp(&gPlayerParty[1], 0);

    HealPlayerParty();
    maxHp = GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP);
    if (GetMonData(&gPlayerParty[0], MON_DATA_HP) != maxHp)
        Fail("CORECURRENT FAIL protected starter center heal");
    if (GetMonData(&gPlayerParty[1], MON_DATA_HP) != 0)
        Fail("CORECURRENT FAIL center healed dead mon");

    if (!ExecuteTableBasedItemEffect(&gPlayerParty[1], ITEM_REVIVE, 1, 0))
        Fail("CORECURRENT FAIL Revive reported effect");
    if (!ExecuteTableBasedItemEffect(&gPlayerParty[1], ITEM_MAX_REVIVE, 1, 0))
        Fail("CORECURRENT FAIL Max Revive reported effect");
    if (!ExecuteTableBasedItemEffect(&gPlayerParty[1], ITEM_SACRED_ASH, 1, 0))
        Fail("CORECURRENT FAIL Sacred Ash reported effect");

    if (GetMonData(&gPlayerParty[1], MON_DATA_HP) != 0)
        Fail("CORECURRENT FAIL revival restored dead mon");

    if (!PokemonItemUseNoEffect(&gPlayerParty[1], ITEM_REVIVE, 1, 0)
     || !PokemonItemUseNoEffect(&gPlayerParty[1], ITEM_MAX_REVIVE, 1, 0)
     || !PokemonItemUseNoEffect(&gPlayerParty[1], ITEM_SACRED_ASH, 1, 0))
        Fail("CORECURRENT FAIL no-effect check allowed revive");
}

static void CheckImugi(struct Pokemon *mon)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 otName[PLAYER_NAME_LENGTH + 1];

    if (GetMonData(mon, MON_DATA_SANITY_IS_BAD_EGG))
        Fail("CORECURRENT FAIL IMUGI bad egg");
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_BAGON
     || GetMonData(mon, MON_DATA_LEVEL) != 20
     || GetMonGender(mon) != MON_MALE
     || GetNature(mon) != NATURE_JOLLY
     || GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_DRAGON_FANG
     || GetMonData(mon, MON_DATA_OT_ID) != OTID_NPC_TRADE_MIN)
        Fail("CORECURRENT FAIL IMUGI package");

    if (GetMonData(mon, MON_DATA_MOVE1) != MOVE_BITE
     || GetMonData(mon, MON_DATA_MOVE2) != MOVE_HEADBUTT
     || GetMonData(mon, MON_DATA_MOVE3) != MOVE_FOCUS_ENERGY
     || GetMonData(mon, MON_DATA_MOVE4) != MOVE_DRAGON_BREATH)
        Fail("CORECURRENT FAIL IMUGI moves");

    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    GetMonData(mon, MON_DATA_OT_NAME, otName);
    if (StringCompare(nickname, sImugi) || StringCompare(otName, sMin))
        Fail("CORECURRENT FAIL IMUGI names");
    if (!IsTradedMon(mon))
        Fail("CORECURRENT FAIL IMUGI ownership");
    if (GetMonData(mon, MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(mon, MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL trade inherited Sam state");
}

static void CreateImugiInSlot2(void)
{
    CreateMon(&gPlayerParty[2], SPECIES_EKANS, 10, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 3;
    CpuFill16(0, gEnemyParty, sizeof(gEnemyParty));

    gSpecialVar_0x8004 = INGAME_TRADE_IMUGI;
    gSpecialVar_0x8005 = 2;
    CreateInGameTradePokemon();
    CheckImugi(&gEnemyParty[0]);
    CopyMon(&gPlayerParty[2], &gEnemyParty[0], sizeof(struct Pokemon));
    CheckImugi(&gPlayerParty[2]);
}

static void CheckPcRoundTrip(void)
{
    SetBoxMonAt(0, 0, &gPlayerParty[0].box);
    SetBoxMonAt(0, 1, &gPlayerParty[1].box);
    SetBoxMonAt(0, 2, &gPlayerParty[2].box);

    ZeroMonData(&gPlayerParty[0]);
    ZeroMonData(&gPlayerParty[1]);
    ZeroMonData(&gPlayerParty[2]);

    BoxMonAtToMon(0, 0, &gPlayerParty[0]);
    BoxMonAtToMon(0, 1, &gPlayerParty[1]);
    BoxMonAtToMon(0, 2, &gPlayerParty[2]);

    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL starter PC roundtrip");
    if (GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER)
     || !GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL dead PC roundtrip");
    CheckImugi(&gPlayerParty[2]);
}

static void RunPhase1Fresh(void)
{
    ClearSav2();
    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));

    CheckStarterMode(SPECIES_EEVEE, ITEM_NONE, 0);
    CheckStarterMode(SPECIES_PICHU, ITEM_NONE, 0);
    CheckStarterMode(SPECIES_DITTO, ITEM_ADAPTIVE_GENE, 0);
    CheckStarterMode(SPECIES_EEVEE, ITEM_NONE, 1);
    CheckStarterMode(SPECIES_PICHU, ITEM_NONE, 1);
    CheckStarterMode(SPECIES_DITTO, ITEM_ADAPTIVE_GENE, 1);

    CheckStandardHealingRegression();

    ResetParty();
    VarSet(VAR_SAM_GAME_MODE, 0);
    gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] = QA_STAGE_STANDARD_SAVED;

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("CORECURRENT FAIL standard save");

    QaLog("CORECURRENT PHASE1 PASS six starter-mode paths standard saved");
    for (;;);
}

static void RunPhase2StandardReloadThenPermanentSave(void)
{
    bool8 dead = TRUE;

    if (VarGet(VAR_SAM_GAME_MODE) != 0
     || gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] != QA_STAGE_STANDARD_SAVED)
        Fail("CORECURRENT FAIL standard reload");

    CheckStandardHealingRegression();

    ClearSav1();
    CpuFill16(0, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));
    ResetParty();

    StringCopy(gSaveBlock2Ptr->playerName, sPlayerName);
    gSaveBlock2Ptr->playerTrainerId[0] = 0x11;
    gSaveBlock2Ptr->playerTrainerId[1] = 0x22;
    gSaveBlock2Ptr->playerTrainerId[2] = 0x33;
    gSaveBlock2Ptr->playerTrainerId[3] = 0x44;

    VarSet(VAR_SAM_GAME_MODE, 1);

    if (ScriptGiveSamStarter(SPECIES_DITTO) != MON_GIVEN_TO_PARTY)
        Fail("CORECURRENT FAIL permanent starter grant");
    MarkSamOriginalStarter();
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != ITEM_ADAPTIVE_GENE)
        Fail("CORECURRENT FAIL permanent starter state");

    CreateMon(&gPlayerParty[1], SPECIES_DITTO, 8, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
    gPlayerPartyCount = 2;
    SetHp(&gPlayerParty[1], 0);
    TryMarkMonPermanentDead(&gPlayerParty[1]);
    if (!GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD)
     || GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER))
        Fail("CORECURRENT FAIL exact individual death");

    // Ensure the marker remains ordinary unencrypted BoxPokemon state.
    SetPermanentDead(&gPlayerParty[1], dead);

    CreateImugiInSlot2();
    CheckPermanentHealing();
    CheckPcRoundTrip();

    gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] = QA_STAGE_PERMANENT_SAVED;
    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("CORECURRENT FAIL permanent save");

    QaLog("CORECURRENT PHASE2 PASS standard reload permanent healing trade storage saved");
    for (;;);
}

static void RunPhase3PermanentReload(void)
{
    if (VarGet(VAR_SAM_GAME_MODE) != 1
     || gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] != QA_STAGE_PERMANENT_SAVED)
        Fail("CORECURRENT FAIL permanent mode reload");
    if (gPlayerPartyCount != 3)
        Fail("CORECURRENT FAIL party count reload");

    if (GetMonData(&gPlayerParty[0], MON_DATA_SPECIES) != SPECIES_DITTO
     || !GetMonData(&gPlayerParty[0], MON_DATA_SAM_ORIGINAL_STARTER)
     || GetMonData(&gPlayerParty[0], MON_DATA_SAM_PERMANENT_DEAD)
     || GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) != ITEM_ADAPTIVE_GENE)
        Fail("CORECURRENT FAIL starter reload");

    if (GetMonData(&gPlayerParty[1], MON_DATA_SPECIES) != SPECIES_DITTO
     || GetMonData(&gPlayerParty[1], MON_DATA_SAM_ORIGINAL_STARTER)
     || !GetMonData(&gPlayerParty[1], MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL dead reload");

    CheckImugi(&gPlayerParty[2]);

    if (!GetBoxMonData(GetBoxedMonPtr(0, 0), MON_DATA_SAM_ORIGINAL_STARTER)
     || !GetBoxMonData(GetBoxedMonPtr(0, 1), MON_DATA_SAM_PERMANENT_DEAD))
        Fail("CORECURRENT FAIL boxed markers reload");
    if (GetBoxMonData(GetBoxedMonPtr(0, 2), MON_DATA_SANITY_IS_BAD_EGG))
        Fail("CORECURRENT FAIL boxed trade corruption");

    CheckPermanentHealing();

    QaLog("CORECURRENT PASS permanent reload starter death healing trade storage");
    for (;;);
}

void Core001004CurrentStack_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);

    if (loadStatus != SAVE_STATUS_OK)
        RunPhase1Fresh();

    if (gSaveBlock1Ptr->samEdition.futureExpansion[QA_STAGE_INDEX] == QA_STAGE_STANDARD_SAVED)
        RunPhase2StandardReloadThenPermanentSave();

    RunPhase3PermanentReload();
}
