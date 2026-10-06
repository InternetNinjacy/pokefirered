#include "global.h"
#include "gflib.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/trade.h"

// Gen III stores PLAYER_NAME_LENGTH (7) OT characters in BoxPokemon data.
// Keep the canonical source identity literal here; SetMonData applies the
// engine's existing storage width rather than inventing a separate OT identity.
static const u8 sSamHawthorneOtName[] = _("HAWTHORNE");

void GiveSamHothouseTropius(void)
{
    struct Pokemon *mon;
    u32 personality;
    u16 nationalDexNum;
    u16 heldItem = ITEM_MIRACLE_SEED;
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
    SetMonMoveSlot(mon, MOVE_RAZOR_LEAF, 0);
    SetMonMoveSlot(mon, MOVE_WING_ATTACK, 1);
    SetMonMoveSlot(mon, MOVE_STOMP, 2);
    SetMonMoveSlot(mon, MOVE_SYNTHESIS, 3);

    // This is the shared Sam Edition pre-owned Gift delivery path. It preserves
    // outsider Gift EXP/obedience behavior and safely routes to party or PC.
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
