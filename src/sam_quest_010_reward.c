#include "global.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trade.h"

static const u8 sQuest010CopycatOtName[] = _("COPYCAT");

void SamQuest010GiveMrMimeReward(void)
{
    gSpecialVar_Result = ScriptGiveMon(
        SPECIES_MR_MIME,
        30,
        ITEM_NONE,
        (u32)sQuest010CopycatOtName,
        OTID_GIFT_COPYCAT,
        FEMALE);
}
