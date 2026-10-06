#define SAM_THOMAS_TRAINER_TRAITS_C

#include "global.h"
#include "pokemon.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/vars.h"
#include "constants/battle.h"
#include "constants/opponents.h"
#include "constants/pokemon.h"

extern u32 gBattleTypeFlags;
extern u16 gTrainerBattleOpponent_A;

static bool8 IsThomasTrainer(u16 trainerNum)
{
    return trainerNum == TRAINER_THOMAS_MT_MOON
        || (trainerNum >= TRAINER_THOMAS_NUGGET_BRIDGE
         && trainerNum <= TRAINER_THOMAS_VIRIDIAN_GYM);
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


void ApplyThomasMtMoonStarterBranch(struct Pokemon *party, u16 trainerNum)
{
    struct Pokemon *mon;
    u16 species;
    u16 heldItem;
    u16 moves[MAX_MON_MOVES];
    u8 abilityNum = 0;

    if (trainerNum != TRAINER_THOMAS_MT_MOON)
        return;

    mon = &party[1];

    // VAR_STARTER_MON follows the current Sam starter routing:
    // 0 = Eevee, 1 = Pichu, 2 = Ditto.
    switch (VarGet(VAR_STARTER_MON))
    {
    case 1:
        species = SPECIES_CUBONE;
        heldItem = ITEM_THICK_CLUB;
        moves[0] = MOVE_BONE_CLUB;
        moves[1] = MOVE_HEADBUTT;
        moves[2] = MOVE_GROWL;
        moves[3] = MOVE_TAIL_WHIP;
        abilityNum = 1; // Lightning Rod.
        break;
    case 2:
        species = SPECIES_DRATINI;
        heldItem = ITEM_DRAGON_FANG;
        moves[0] = MOVE_TWISTER;
        moves[1] = MOVE_THUNDER_WAVE;
        moves[2] = MOVE_WRAP;
        moves[3] = MOVE_LEER;
        break;
    case 0:
    default:
        species = SPECIES_CHANSEY;
        heldItem = ITEM_SITRUS_BERRY;
        moves[0] = MOVE_SEISMIC_TOSS;
        moves[1] = MOVE_SOFT_BOILED;
        moves[2] = MOVE_THUNDER_WAVE;
        moves[3] = MOVE_LIGHT_SCREEN;
        break;
    }

    CreateMon(mon, species, 15, 0, FALSE, 0, OT_ID_RANDOM_NO_SHINY, 0);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    SetMonMoveSlot(mon, moves[0], 0);
    SetMonMoveSlot(mon, moves[1], 1);
    SetMonMoveSlot(mon, moves[2], 2);
    SetMonMoveSlot(mon, moves[3], 3);
}
