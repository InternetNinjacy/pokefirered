#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "script_pokemon_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/trade.h"

// script_pokemon_util.h intentionally aliases the existing implementation to
// GiveSamPreOwnedMonBase. The script-special symbol remains GiveSamPreOwnedMon
// and is supplied here as a narrow dispatcher for fixed authored Gift profiles.
#undef GiveSamPreOwnedMon

// Gen III BoxPokemon storage reserves PLAYER_NAME_LENGTH (7) bytes for OT names.
// Hawthorne's canonical event-facing name remains HAWTHORNE; HAWTHRN preserves
// the engine-safe spelling established by the historical Hothouse source work.
static const u8 sSamGiftOtHawthorne[] = _("HAWTHRN");

static u8 GiveSamHawthorneTropius(void)
{
    struct Pokemon *mon;
    u32 personality;
    u16 nationalDexNum;
    u16 heldItem = ITEM_MIRACLE_SEED;
    u8 otGender = MALE;
    u8 abilityNum = 0; // Tropius slot 0 is Chlorophyll under current species authority.
    u8 sentToPc;

    if (FlagGet(FLAG_SAM_HOTHOUSE_TROPIUS_CLAIMED))
        return MON_CANT_GIVE;

    do
    {
        personality = Random32();
    } while ((personality % NUM_NATURES) != NATURE_SASSY
          || GetGenderFromSpeciesAndPersonality(SPECIES_TROPIUS, personality) != MON_FEMALE);

    mon = AllocZeroed(sizeof(*mon));
    if (mon == NULL)
        return MON_CANT_GIVE;

    CreateMon(mon, SPECIES_TROPIUS, 30, USE_RANDOM_IVS, TRUE, personality, OT_ID_PRESET, OTID_GIFT_HAWTHORNE);
    SetMonData(mon, MON_DATA_OT_NAME, sSamGiftOtHawthorne);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
    SetMonMoveSlot(mon, MOVE_RAZOR_LEAF, 0);
    SetMonMoveSlot(mon, MOVE_WING_ATTACK, 1);
    SetMonMoveSlot(mon, MOVE_STOMP, 2);
    SetMonMoveSlot(mon, MOVE_SYNTHESIS, 3);

    sentToPc = GivePreOwnedMonToPlayer(mon);
    if (sentToPc == MON_GIVEN_TO_PARTY || sentToPc == MON_GIVEN_TO_PC)
    {
        nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_TROPIUS);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        FlagSet(FLAG_SAM_HOTHOUSE_TROPIUS_CLAIMED);
    }

    Free(mon);
    return sentToPc;
}

void GiveSamPreOwnedMon(void)
{
    if (gSpecialVar_0x8006 == SAM_PREOWNED_OT_HAWTHORNE)
    {
        gSpecialVar_Result = GiveSamHawthorneTropius();
        return;
    }

    GiveSamPreOwnedMonBase();
}
