#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "sam_special_acquisition.h"
#include "constants/pokemon.h"
#include "constants/vars.h"

u8 GivePreOwnedMonToPlayer(struct Pokemon *mon)
{
    s32 i;
    s32 boxNo;
    s32 boxPos;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            break;
    }

    if (i < PARTY_SIZE)
    {
        CopyMon(&gPlayerParty[i], mon, sizeof(*mon));
        gPlayerPartyCount = i + 1;
        return MON_GIVEN_TO_PARTY;
    }

    boxNo = StorageGetCurrentBox();
    do
    {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
        {
            struct BoxPokemon *boxedMon = GetBoxedMonPtr(boxNo, boxPos);

            if (GetBoxMonData(boxedMon, MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            {
                MonRestorePP(mon);
                CopyMon(boxedMon, &mon->box, sizeof(mon->box));
                gSpecialVar_MonBoxId = boxNo;
                gSpecialVar_MonBoxPos = boxPos;
                VarSet(VAR_PC_BOX_TO_SEND_MON, boxNo);
                return MON_GIVEN_TO_PC;
            }
        }

        boxNo++;
        if (boxNo == TOTAL_BOXES_COUNT)
            boxNo = 0;
    } while (boxNo != StorageGetCurrentBox());

    return MON_CANT_GIVE;
}
