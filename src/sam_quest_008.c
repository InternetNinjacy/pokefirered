#include "global.h"
#include "gflib.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "constants/items.h"
#include "constants/pokemon.h"

#define OTID_GIFT_CELADON_EEVEE 0xA9B2BF37

static const u8 sQuest008CeladonOt[] = _("CELADON");

void GiveSamQuest008Eevee(void)
{
    struct Pokemon *mon;
    u32 personality;
    u16 nationalDexNum;
    u16 heldItem = ITEM_NONE;
    u8 otGender = MALE;
    u8 sentToPc;

    do
    {
        personality = Random32();
    } while (GetGenderFromSpeciesAndPersonality(SPECIES_EEVEE, personality) != MON_FEMALE);

    mon = AllocZeroed(sizeof(*mon));
    CreateMon(mon, SPECIES_EEVEE, 5, USE_RANDOM_IVS, TRUE, personality, OT_ID_PRESET, OTID_GIFT_CELADON_EEVEE);
    SetMonData(mon, MON_DATA_OT_NAME, sQuest008CeladonOt);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);

    sentToPc = GivePreOwnedMonToPlayer(mon);
    if (sentToPc == MON_GIVEN_TO_PARTY || sentToPc == MON_GIVEN_TO_PC)
    {
        nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_EEVEE);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
    }

    Free(mon);
    gSpecialVar_Result = sentToPc;
}
