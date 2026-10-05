#define SAM_THOMAS_TRAINER_TRAITS_C

#include "global.h"
#include "pokemon.h"
#include "constants/battle.h"
#include "constants/opponents.h"
#include "constants/pokemon.h"

extern u32 gBattleTypeFlags;
extern u16 gTrainerBattleOpponent_A;

static bool8 IsThomasTrainer(u16 trainerNum)
{
    return trainerNum >= TRAINER_THOMAS_NUGGET_BRIDGE
        && trainerNum <= TRAINER_THOMAS_VIRIDIAN_GYM;
}

static bool8 IsEnemyPartySlot(struct Pokemon *mon)
{
    s32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (mon == &gEnemyParty[i])
            return TRUE;
    }

    return FALSE;
}

static u32 GetThomasTrainerMonPersonality(u16 species, u32 fallbackPersonality)
{
    switch (species)
    {
    case SPECIES_HORSEA:
    case SPECIES_SEADRA:
    case SPECIES_KINGDRA:
        return 0x00000AFF; // Modest, male; persistent Horsea-line identity.
    case SPECIES_MACHOP:
    case SPECIES_MACHOKE:
    case SPECIES_MACHAMP:
        return 0x000008FF; // Adamant, male; persistent Machop-line identity.
    case SPECIES_HOUNDOUR:
    case SPECIES_HOUNDOOM:
        return 0x000005FF; // Timid, male, ability slot 1: Flash Fire.
    case SPECIES_BALTOY:
    case SPECIES_CLAYDOL:
        return 0x0000000F; // Modest; genderless Levitate line.
    case SPECIES_MAGNEMITE:
    case SPECIES_MAGNETON:
        return 0x00000028; // Modest, genderless, ability slot 0: Magnet Pull.
    case SPECIES_BAGON:
    case SPECIES_SALAMENCE:
        return 0x000021FF; // Adamant, male; persistent Bagon-line identity.
    default:
        return fallbackPersonality;
    }
}

void CreateMonWithThomasTrainerTraits(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId)
{
    bool8 applyThomasTraits = FALSE;
    u8 friendship;

    if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER)
     && IsThomasTrainer(gTrainerBattleOpponent_A)
     && IsEnemyPartySlot(mon)
     && hasFixedPersonality
     && otIdType == OT_ID_RANDOM_NO_SHINY)
    {
        applyThomasTraits = TRUE;
        fixedPersonality = GetThomasTrainerMonPersonality(species, fixedPersonality);
    }

    CreateMon(mon, species, level, fixedIV, hasFixedPersonality, fixedPersonality, otIdType, fixedOtId);

    if (applyThomasTraits && species == SPECIES_SALAMENCE)
    {
        friendship = 0;
        SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    }
}
