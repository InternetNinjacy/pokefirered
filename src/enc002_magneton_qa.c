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
extern void SetEnemyEventMonMagnetonHiddenPowerIVs(void);

static void Log(const char *text){u32 i=0;while(text[i]&&i<255){QA_MGBA_DEBUG_STRING[i]=text[i];i++;}QA_MGBA_DEBUG_STRING[i]='\0';*QA_MGBA_DEBUG_FLAGS=MGBA_LOG_INFO|0x100;}
static void Fail(const char *text){Log(text);for(;;);}

static void SetMove(u16 move, u16 slot)
{
    gSpecialVar_0x8004=move;
    gSpecialVar_0x8005=slot;
    SetEnemyEventMonMoveSlot();
}

static void CheckMagnetonPackage(void)
{
    CreateScriptedWildMon(SPECIES_MAGNETON, 27, ITEM_METAL_COAT);
    SetEnemyEventMonMagnetonHiddenPowerIVs();
    SetMove(MOVE_SPARK, 0);
    SetMove(MOVE_THUNDER_WAVE, 1);
    SetMove(MOVE_SONIC_BOOM, 2);
    SetMove(MOVE_HIDDEN_POWER, 3);

    if (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL)!=SPECIES_MAGNETON
     || GetMonData(&gEnemyParty[0], MON_DATA_LEVEL, NULL)!=27
     || GetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, NULL)!=ITEM_METAL_COAT
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE1, NULL)!=MOVE_SPARK
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE2, NULL)!=MOVE_THUNDER_WAVE
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE3, NULL)!=MOVE_SONIC_BOOM
     || GetMonData(&gEnemyParty[0], MON_DATA_MOVE4, NULL)!=MOVE_HIDDEN_POWER)
        Fail("ENC002 MAGNETON QA FAIL package");

    if (GetMonData(&gEnemyParty[0], MON_DATA_HP_IV, NULL)!=28
     || GetMonData(&gEnemyParty[0], MON_DATA_ATK_IV, NULL)!=28
     || GetMonData(&gEnemyParty[0], MON_DATA_DEF_IV, NULL)!=29
     || GetMonData(&gEnemyParty[0], MON_DATA_SPEED_IV, NULL)!=29
     || GetMonData(&gEnemyParty[0], MON_DATA_SPATK_IV, NULL)!=30
     || GetMonData(&gEnemyParty[0], MON_DATA_SPDEF_IV, NULL)!=31)
        Fail("ENC002 MAGNETON QA FAIL Hidden Power IVs");
}

static void RunFresh(void)
{
    ClearSav2(); ClearSav1(); CheckMagnetonPackage();
    if (FlagGet(FLAG_STATIC_ROUTE9_MAGNETON_COMPLETE)) Fail("ENC002 MAGNETON QA FAIL dirty flag");
    FlagSet(FLAG_STATIC_ROUTE9_MAGNETON_COMPLETE);
    if (!FlagGet(FLAG_STATIC_ROUTE9_MAGNETON_COMPLETE)) Fail("ENC002 MAGNETON QA FAIL set flag");
    if (TrySavingData(SAVE_NORMAL)!=SAVE_STATUS_OK) Fail("ENC002 MAGNETON QA FAIL save");
    Log("ENC002 MAGNETON QA PHASE1 PASS package Grass60 flag save"); for(;;);
}

static void RunReload(void)
{
    if (!FlagGet(FLAG_STATIC_ROUTE9_MAGNETON_COMPLETE)) Fail("ENC002 MAGNETON QA FAIL reload flag");
    CheckMagnetonPackage(); Log("ENC002 MAGNETON QA PASS save reload package Grass60"); for(;;);
}

// Name retained to reuse the proven evidence-only Abra QA bootstrap main.c blob.
void Enc002AbraQa_RunRuntimeQa(void)
{
    u8 loadStatus; MgbaOpen(); SetSaveBlocksPointers(); loadStatus=LoadGameSave(SAVE_NORMAL);
    if (loadStatus!=SAVE_STATUS_OK) RunFresh(); RunReload();
}
