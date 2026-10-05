#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "pokemon.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
#include "constants/species.h"

void StartVermilionPollutionBattle(void)
{
    ZeroEnemyPartyMons();
    CreateMon(&gEnemyParty[0], SPECIES_GRIMER, 20, USE_RANDOM_IVS, FALSE, 0, OT_ID_RANDOM_NO_SHINY, 0);
    CreateMon(&gEnemyParty[1], SPECIES_MUK, 22, USE_RANDOM_IVS, FALSE, 0, OT_ID_RANDOM_NO_SHINY, 0);

    StartScriptedWildBattle();
    gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
}
