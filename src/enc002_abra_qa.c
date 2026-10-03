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

static void CheckAbraPackage(void)
{
    CreateScriptedWildMon(SPECIES_ABRA, 10, ITEM_TWISTED_SPOON);
    gSpecialVar_0x8004=MOVE_CONFUSION; gSpecialVar_0x8005=0; SetEnemyEventMonMoveSlot();
    if (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL)!=SPECIES_ABRA
     || GetMonData(&gEnemyParty[0], MON_DATA_LEVEL, NULL)!=10
     || GetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, NULL)!=ITEM_TWISTED_SPOON
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE1, NULL)!=MOVE_CONFUSION)
        Fail("ENC002 ABRA QA FAIL package");
}

static void RunFresh(void)
{
    ClearSav2(); ClearSav1(); CheckAbraPackage();
    if (FlagGet(FLAG_STATIC_ROUTE24_ABRA_COMPLETE)) Fail("ENC002 ABRA QA FAIL dirty flag");
    FlagSet(FLAG_STATIC_ROUTE24_ABRA_COMPLETE);
    if (!FlagGet(FLAG_STATIC_ROUTE24_ABRA_COMPLETE)) Fail("ENC002 ABRA QA FAIL set flag");
    if (TrySavingData(SAVE_NORMAL)!=SAVE_STATUS_OK) Fail("ENC002 ABRA QA FAIL save");
    Log("ENC002 ABRA QA PHASE1 PASS package flag save"); for(;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_STATIC_ROUTE24_ABRA_COMPLETE)) Fail("ENC002 ABRA QA FAIL reload flag");
    CheckAbraPackage(); Log("ENC002 ABRA QA PASS save reload package"); for(;;);
}

void Enc002AbraQa_RunRuntimeQa(void)
{
    u8 loadStatus; MgbaOpen(); SetSaveBlocksPointers(); loadStatus=LoadGameSave(SAVE_NORMAL);
    if (loadStatus!=SAVE_STATUS_OK) RunFresh(); RunReload();
}
