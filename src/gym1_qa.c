#include "global.h"
#include "battle.h"
#include "data.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "save.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trainers.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static void Log(const char *text)
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
    Log(text);
    for (;;);
}

static void CheckNoItemMon(const struct TrainerMonNoItemCustomMoves *m, u16 species, u8 level,
                           u16 m1, u16 m2, u16 m3, u16 m4)
{
    if (m->species != species || m->lvl != level
     || m->moves[0] != m1 || m->moves[1] != m2
     || m->moves[2] != m3 || m->moves[3] != m4)
        Fail("GYM1 QA FAIL no-item party");
}

static void CheckItemMon(const struct TrainerMonItemCustomMoves *m, u16 species, u8 level, u16 item,
                         u16 m1, u16 m2, u16 m3, u16 m4)
{
    if (m->species != species || m->lvl != level || m->heldItem != item
     || m->moves[0] != m1 || m->moves[1] != m2
     || m->moves[2] != m3 || m->moves[3] != m4)
        Fail("GYM1 QA FAIL item party");
}

static void CheckTrainerData(void)
{
    const struct Trainer *t;
    const struct TrainerMonNoItemCustomMoves *n;
    const struct TrainerMonItemCustomMoves *i;

    t = &gTrainers[TRAINER_SATOSHI_PEWTER_PRACTICE];
    if (t->partySize != 1 || t->trainerPic != TRAINER_PIC_SATOSHI)
        Fail("GYM1 QA FAIL Satoshi practice record");
    n = t->party.NoItemCustomMoves;
    CheckNoItemMon(&n[0], SPECIES_SEEL, 9, MOVE_HEADBUTT, MOVE_GROWL, MOVE_NONE, MOVE_NONE);

    t = &gTrainers[TRAINER_HIKER_CLIFF_PEWTER];
    if (t->partySize != 2 || t->trainerClass != TRAINER_CLASS_HIKER)
        Fail("GYM1 QA FAIL Cliff record");
    n = t->party.NoItemCustomMoves;
    CheckNoItemMon(&n[0], SPECIES_SHELLDER, 10, MOVE_TACKLE, MOVE_WITHDRAW, MOVE_SUPERSONIC, MOVE_ICICLE_SPEAR);
    CheckNoItemMon(&n[1], SPECIES_SEEL, 11, MOVE_HEADBUTT, MOVE_GROWL, MOVE_ICY_WIND, MOVE_NONE);

    t = &gTrainers[TRAINER_HIKER_MILES_PEWTER];
    if (t->partySize != 2 || t->trainerClass != TRAINER_CLASS_HIKER)
        Fail("GYM1 QA FAIL Miles record");
    n = t->party.NoItemCustomMoves;
    CheckNoItemMon(&n[0], SPECIES_SMOOCHUM, 11, MOVE_POUND, MOVE_LICK, MOVE_SWEET_KISS, MOVE_POWDER_SNOW);
    CheckNoItemMon(&n[1], SPECIES_SHELLDER, 12, MOVE_ICICLE_SPEAR, MOVE_SUPERSONIC, MOVE_WITHDRAW, MOVE_WATER_GUN);

    t = &gTrainers[TRAINER_LEADER_BOREAL_PEWTER];
    if (t->partySize != 3 || t->trainerPic != TRAINER_PIC_BOREAL || t->trainerClass != TRAINER_CLASS_LEADER)
        Fail("GYM1 QA FAIL Boreal record");
    n = t->party.NoItemCustomMoves;
    CheckNoItemMon(&n[0], SPECIES_SMOOCHUM, 12, MOVE_ICY_WIND, MOVE_POUND, MOVE_LICK, MOVE_SWEET_KISS);
    CheckNoItemMon(&n[1], SPECIES_SEEL, 13, MOVE_ICY_WIND, MOVE_HEADBUTT, MOVE_GROWL, MOVE_NONE);
    CheckNoItemMon(&n[2], SPECIES_SPHEAL, 14, MOVE_ICE_BALL, MOVE_WATER_GUN, MOVE_ENCORE, MOVE_DEFENSE_CURL);

    t = &gTrainers[TRAINER_LEADER_BOREAL_REMATCH_PEWTER];
    if (t->partySize != 6 || t->trainerPic != TRAINER_PIC_BOREAL)
        Fail("GYM1 QA FAIL Boreal rematch record");
    i = t->party.ItemCustomMoves;
    CheckItemMon(&i[0], SPECIES_DEWGONG, 58, ITEM_NEVER_MELT_ICE, MOVE_ICY_WIND, MOVE_SURF, MOVE_ICE_BEAM, MOVE_REST);
    CheckItemMon(&i[1], SPECIES_JYNX, 59, ITEM_TWISTED_SPOON, MOVE_ICE_BEAM, MOVE_PSYCHIC, MOVE_LOVELY_KISS, MOVE_CALM_MIND);
    CheckItemMon(&i[2], SPECIES_CLOYSTER, 60, ITEM_MYSTIC_WATER, MOVE_ICE_BEAM, MOVE_SURF, MOVE_SPIKES, MOVE_PROTECT);
    CheckItemMon(&i[3], SPECIES_SNORLAX, 61, ITEM_CHESTO_BERRY, MOVE_BODY_SLAM, MOVE_EARTHQUAKE, MOVE_SHADOW_BALL, MOVE_REST);
    CheckItemMon(&i[4], SPECIES_LAPRAS, 62, ITEM_MAGNET, MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_CONFUSE_RAY);
    CheckItemMon(&i[5], SPECIES_WALREIN, 64, ITEM_LEFTOVERS, MOVE_SURF, MOVE_ICE_BEAM, MOVE_ENCORE, MOVE_REST);

    t = &gTrainers[TRAINER_SATOSHI_PEWTER_REMATCH];
    if (t->partySize != 6 || t->items[0] != ITEM_FULL_RESTORE)
        Fail("GYM1 QA FAIL Satoshi rematch record");
    i = t->party.ItemCustomMoves;
    CheckItemMon(&i[0], SPECIES_GOLDUCK, 55, ITEM_MYSTIC_WATER, MOVE_SURF, MOVE_ICE_BEAM, MOVE_PSYCHIC, MOVE_CALM_MIND);
    CheckItemMon(&i[5], SPECIES_DEWGONG, 60, ITEM_SHELL_BELL, MOVE_SURF, MOVE_ICE_BEAM, MOVE_BODY_SLAM, MOVE_ENCORE);

    if (gTrainerFrontPicTable[TRAINER_PIC_BOREAL].data != gTrainerFrontPic_Boreal
     || gTrainerFrontPicPaletteTable[TRAINER_PIC_BOREAL].data != gTrainerPalette_Boreal)
        Fail("GYM1 QA FAIL Boreal portrait route");
}

static void RunFresh(void)
{
    ClearSav2();
    ClearSav1();
    CheckTrainerData();

    if (FlagGet(FLAG_GYM1_TM55_RECEIVED) || FlagGet(FLAG_BADGE01_GET)
     || FlagGet(FLAG_SATOSHI_PEWTER_PRACTICE_WON))
        Fail("GYM1 QA FAIL dirty state");

    FlagSet(FLAG_GYM1_TM55_RECEIVED);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_SATOSHI_PEWTER_PRACTICE_WON);

    if (TrySavingData(SAVE_NORMAL) != SAVE_STATUS_OK)
        Fail("GYM1 QA FAIL save");

    Log("GYM1 QA PHASE1 PASS data flags save");
    for (;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_GYM1_TM55_RECEIVED) || !FlagGet(FLAG_BADGE01_GET)
     || !FlagGet(FLAG_SATOSHI_PEWTER_PRACTICE_WON))
        Fail("GYM1 QA FAIL reload flags");

    CheckTrainerData();
    Log("GYM1 QA PASS reload trainer data");
    for (;;);
}

void Gym1Qa_RunRuntimeQa(void)
{
    u8 loadStatus;

    MgbaOpen();
    SetSaveBlocksPointers();
    loadStatus = LoadGameSave(SAVE_NORMAL);
    if (loadStatus != SAVE_STATUS_OK)
        RunFresh();
    RunReload();
}
