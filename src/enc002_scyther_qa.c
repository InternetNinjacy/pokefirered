#include "global.h"
#include "event_data.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "pokemon.h"
#include "save.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

extern void SetEnemyEventMonMoveSlot(void);

static void Log(const char *text){u32 i=0;while(text[i]&&i<255){QA_MGBA_DEBUG_STRING[i]=text[i];i++;}QA_MGBA_DEBUG_STRING[i]='\0';*QA_MGBA_DEBUG_FLAGS=MGBA_LOG_INFO|0x100;}
static void Fail(const char *text){Log(text);for(;;);}

static void CheckScytherPackage(void)
{
    CreateScriptedWildMon(SPECIES_SCYTHER, 11, ITEM_SILVER_POWDER);
    gSpecialVar_0x8004=MOVE_QUICK_ATTACK; gSpecialVar_0x8005=0; SetEnemyEventMonMoveSlot();
    gSpecialVar_0x8004=MOVE_LEER; gSpecialVar_0x8005=1; SetEnemyEventMonMoveSlot();
    gSpecialVar_0x8004=MOVE_FOCUS_ENERGY; gSpecialVar_0x8005=2; SetEnemyEventMonMoveSlot();
    gSpecialVar_0x8004=MOVE_FURY_CUTTER; gSpecialVar_0x8005=3; SetEnemyEventMonMoveSlot();
    if (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL)!=SPECIES_SCYTHER
     || GetMonData(&gEnemyParty[0], MON_DATA_LEVEL, NULL)!=11
     || GetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, NULL)!=ITEM_SILVER_POWDER
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE1, NULL)!=MOVE_QUICK_ATTACK
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE2, NULL)!=MOVE_LEER
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE3, NULL)!=MOVE_FOCUS_ENERGY
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE4, NULL)!=MOVE_FURY_CUTTER)
        Fail("ENC002 SCYTHER QA FAIL package");
}
static void RunFresh(void)
{
    ClearSav2(); ClearSav1(); CheckScytherPackage();
    if (FlagGet(FLAG_STATIC_VIRIDIAN_FOREST_SCYTHER_COMPLETE)) Fail("ENC002 SCYTHER QA FAIL dirty flag");
    FlagSet(FLAG_STATIC_VIRIDIAN_FOREST_SCYTHER_COMPLETE);
    if (!FlagGet(FLAG_STATIC_VIRIDIAN_FOREST_SCYTHER_COMPLETE)) Fail("ENC002 SCYTHER QA FAIL set flag");
    if (TrySavingData(SAVE_NORMAL)!=SAVE_STATUS_OK) Fail("ENC002 SCYTHER QA FAIL save");
    Log("ENC002 SCYTHER QA PHASE1 PASS package flag save"); for(;;);
}
static void RunReload(void)
{
    if (!FlagGet(FLAG_STATIC_VIRIDIAN_FOREST_SCYTHER_COMPLETE)) Fail("ENC002 SCYTHER QA FAIL reload flag");
    CheckScytherPackage(); Log("ENC002 SCYTHER QA PASS save reload package"); for(;;);
}
void Enc002ScytherQa_RunRuntimeQa(void)
{
    u8 loadStatus; MgbaOpen(); SetSaveBlocksPointers(); loadStatus=LoadGameSave(SAVE_NORMAL);
    if (loadStatus!=SAVE_STATUS_OK) RunFresh(); RunReload();
}
