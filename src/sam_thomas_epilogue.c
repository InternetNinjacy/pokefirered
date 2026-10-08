#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

#define THOMAS_MARA_TAUROS_OT_ID 24116

static const u8 sThomasMaraOtName[] = _("MARA");

void GiveThomasMaraTauros(void)
{
    struct Pokemon *mon;
    u32 personality;
    u16 nationalDexNum;
    u16 heldItem = ITEM_SITRUS_BERRY;
    u8 friendship = 70;
    u8 otGender = FEMALE;
    u8 sentToPc;

    do
    {
        personality = Random32();
    } while ((personality % NUM_NATURES) != NATURE_ADAMANT
          || GetGenderFromSpeciesAndPersonality(SPECIES_TAUROS, personality) != MON_MALE);

    mon = AllocZeroed(sizeof(*mon));
    if (mon == NULL)
    {
        gSpecialVar_Result = MON_CANT_GIVE;
        return;
    }

    CreateMon(mon, SPECIES_TAUROS, 45, 20, TRUE, personality, OT_ID_PRESET, THOMAS_MARA_TAUROS_OT_ID);
    SetMonData(mon, MON_DATA_OT_NAME, sThomasMaraOtName);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    SetMonMoveSlot(mon, MOVE_BODY_SLAM, 0);
    SetMonMoveSlot(mon, MOVE_EARTHQUAKE, 1);
    SetMonMoveSlot(mon, MOVE_REST, 2);
    SetMonMoveSlot(mon, MOVE_PURSUIT, 3);

    sentToPc = GivePreOwnedMonToPlayer(mon);
    if (sentToPc == MON_GIVEN_TO_PARTY || sentToPc == MON_GIVEN_TO_PC)
    {
        nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_TAUROS);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
    }

    gSpecialVar_Result = sentToPc;
    Free(mon);
}

void GiveThomasSilphPorygon(void)
{
    static const u8 otName[] = _("SILPH");
    struct Pokemon *mon = AllocZeroed(sizeof(*mon));
    u8 otGender = MALE;
    u8 result;
    u16 dex = SpeciesToNationalPokedexNum(SPECIES_PORYGON);

    if (mon == NULL)
    {
        gSpecialVar_Result = MON_CANT_GIVE;
        return;
    }
    CreateMon(mon, SPECIES_PORYGON, 25, USE_RANDOM_IVS, FALSE, 0, OT_ID_PRESET, 52007);
    SetMonData(mon, MON_DATA_OT_NAME, otName);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    result = GivePreOwnedMonToPlayer(mon);
    if (result != MON_CANT_GIVE)
    {
        GetSetPokedexFlag(dex, FLAG_SET_SEEN);
        GetSetPokedexFlag(dex, FLAG_SET_CAUGHT);
    }
    gSpecialVar_Result = result;
    Free(mon);
}
