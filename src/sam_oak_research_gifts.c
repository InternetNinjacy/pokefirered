#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/trade.h"

static const u8 sOakGiftOtName[] = _("OAK");

enum
{
    OAK_RESEARCH_GIFT_CHANSEY,
    OAK_RESEARCH_GIFT_DRATINI,
};

void GiveSamOakResearchGift(void)
{
    struct Pokemon *mon;
    u16 species;
    u8 level;
    u16 heldItem;
    u16 moves[MAX_MON_MOVES];
    u32 personality;
    u8 otGender = MALE;
    u16 nationalDexNum;
    u8 sentToPc;
    u8 i;

    switch (gSpecialVar_0x8004)
    {
    case OAK_RESEARCH_GIFT_CHANSEY:
        species = SPECIES_CHANSEY;
        level = 30;
        heldItem = ITEM_LUCKY_EGG;
        moves[0] = MOVE_SOFT_BOILED;
        moves[1] = MOVE_SING;
        moves[2] = MOVE_MINIMIZE;
        moves[3] = MOVE_SEISMIC_TOSS;
        do
        {
            personality = Random32();
        } while (GetGenderFromSpeciesAndPersonality(species, personality) != MON_FEMALE);
        break;
    case OAK_RESEARCH_GIFT_DRATINI:
        species = SPECIES_DRATINI;
        level = 29;
        heldItem = ITEM_DRAGON_FANG;
        moves[0] = MOVE_THUNDER_WAVE;
        moves[1] = MOVE_TWISTER;
        moves[2] = MOVE_DRAGON_RAGE;
        moves[3] = MOVE_SLAM;
        personality = Random32();
        break;
    default:
        gSpecialVar_Result = MON_CANT_GIVE;
        return;
    }

    mon = AllocZeroed(sizeof(*mon));
    CreateMon(mon, species, level, USE_RANDOM_IVS, TRUE, personality, OT_ID_PRESET, OTID_GIFT_OAK);
    SetMonData(mon, MON_DATA_OT_NAME, sOakGiftOtName);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, moves[i], i);

    sentToPc = GivePreOwnedMonToPlayer(mon);
    if (sentToPc == MON_GIVEN_TO_PARTY || sentToPc == MON_GIVEN_TO_PC)
    {
        nationalDexNum = SpeciesToNationalPokedexNum(species);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
    }

    Free(mon);
    gSpecialVar_Result = sentToPc;
}
