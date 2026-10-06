#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "sam_special_acquisition.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/sam_gift_ots.h"

// Gen III stores only PLAYER_NAME_LENGTH (7) OT characters. Hawthorne's
// canonical event-facing name remains HAWTHORNE; HAWTHRN is the deterministic
// engine-safe OT display paired with the unique Hawthorne OT ID.
static const u8 sSamHawthorneOtName[] = _("HAWTHRN");

void GiveSamHothouseTropius(void)
{
    struct Pokemon *mon;
    u32 personality;
    u16 nationalDexNum;
    u16 heldItem = ITEM_MIRACLE_SEED;
    u8 abilityNum = 0;
    u8 otGender = MALE;
    u8 result;

    do
    {
        personality = Random32();
    } while ((personality % NUM_NATURES) != NATURE_SASSY
          || GetGenderFromSpeciesAndPersonality(SPECIES_TROPIUS, personality) != MON_FEMALE);

    mon = AllocZeroed(sizeof(*mon));
    if (mon == NULL)
    {
        gSpecialVar_Result = MON_CANT_GIVE;
        return;
    }

    CreateMon(mon, SPECIES_TROPIUS, 30, USE_RANDOM_IVS, TRUE, personality, OT_ID_PRESET, OTID_GIFT_HAWTHORNE);
    SetMonData(mon, MON_DATA_OT_NAME, sSamHawthorneOtName);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    SetMonMoveSlot(mon, MOVE_RAZOR_LEAF, 0);
    SetMonMoveSlot(mon, MOVE_WING_ATTACK, 1);
    SetMonMoveSlot(mon, MOVE_STOMP, 2);
    SetMonMoveSlot(mon, MOVE_SYNTHESIS, 3);

    result = GivePreOwnedMonToPlayer(mon);
    if (result == MON_GIVEN_TO_PARTY || result == MON_GIVEN_TO_PC)
    {
        nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_TROPIUS);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
    }

    Free(mon);
    gSpecialVar_Result = result;
}
