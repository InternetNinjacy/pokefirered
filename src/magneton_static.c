#include "global.h"
#include "pokemon.h"

// IV package chosen so Gen III Hidden Power resolves to Grass at exactly 60 BP.
// HP/Atk/Def/Spd/SpAtk/SpDef = 28/28/29/29/30/31.
void SetEnemyEventMonMagnetonHiddenPowerIVs(void)
{
    u32 iv;

    iv = 28;
    SetMonData(&gEnemyParty[0], MON_DATA_HP_IV, &iv);
    SetMonData(&gEnemyParty[0], MON_DATA_ATK_IV, &iv);
    iv = 29;
    SetMonData(&gEnemyParty[0], MON_DATA_DEF_IV, &iv);
    SetMonData(&gEnemyParty[0], MON_DATA_SPEED_IV, &iv);
    iv = 30;
    SetMonData(&gEnemyParty[0], MON_DATA_SPATK_IV, &iv);
    iv = 31;
    SetMonData(&gEnemyParty[0], MON_DATA_SPDEF_IV, &iv);
}
