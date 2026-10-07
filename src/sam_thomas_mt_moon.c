#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "pokemon.h"
#include "sam_thomas.h"
#include "constants/pokemon.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/vars.h"

u8 CountThomasUsablePlayerMons(void)
{
    u8 i, count = 0;
    for (i = 0; i < PARTY_SIZE; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_HP)
         && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
         && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
         && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
            count++;
    return count;
}

void Script_CountThomasUsablePlayerMons(void)
{
    gSpecialVar_Result = CountThomasUsablePlayerMons();
}

bool8 IsThomasOneMonDoubleBattle(void)
{
    return gTrainerBattleOpponent_A == TRAINER_THOMAS_MT_MOON
        && (gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE)) == (BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE)
        && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_MULTI))
        && CountThomasUsablePlayerMons() == 1;
}

void ApplyThomasMtMoonStarterBranch(struct Pokemon *party, u16 trainerNum)
{
    struct Pokemon *mon;
    u16 species, heldItem, moves[MAX_MON_MOVES];
    u32 personality, otId;
    u8 abilityNum = 0;
    u8 i;

    if (trainerNum != TRAINER_THOMAS_MT_MOON)
        return;
    mon = &party[1];
    switch (VarGet(VAR_STARTER_MON))
    {
    case 1: // Pichu -> Cubone, Lightning Rod.
        species = SPECIES_CUBONE;
        heldItem = ITEM_THICK_CLUB;
        moves[0] = MOVE_BONE_CLUB; moves[1] = MOVE_HEADBUTT;
        moves[2] = MOVE_GROWL; moves[3] = MOVE_TAIL_WHIP;
        abilityNum = 1;
        break;
    case 2: // Ditto -> Dratini, Shed Skin.
        species = SPECIES_DRATINI;
        heldItem = ITEM_DRAGON_FANG;
        moves[0] = MOVE_TWISTER; moves[1] = MOVE_THUNDER_WAVE;
        moves[2] = MOVE_WRAP; moves[3] = MOVE_LEER;
        break;
    default: // Eevee -> the table's Chansey; keep stock generated identity.
        return;
    }
    personality = GetMonData(mon, MON_DATA_PERSONALITY);
    otId = GetMonData(mon, MON_DATA_OT_ID);
    CreateMon(mon, species, 15, 0, TRUE, personality, OT_ID_PRESET, otId);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, moves[i], i);
}


void ApplyThomasCinnabarFossilBranch(struct Pokemon *party, u16 trainerNum)
{
    struct Pokemon *mon;
    u16 species, heldItem = ITEM_MYSTIC_WATER;
    u16 moves[MAX_MON_MOVES];
    u32 personality, otId;
    u8 i;

    if (trainerNum != TRAINER_THOMAS_CINNABAR_MANSION)
        return;

    switch (VarGet(VAR_MAP_SCENE_MT_MOON_B2F))
    {
    case 3: // Thomas stole the Dome Fossil.
        species = SPECIES_KABUTOPS;
        moves[0] = MOVE_ROCK_SLIDE;
        moves[1] = MOVE_BRICK_BREAK;
        moves[2] = MOVE_WATER_PULSE;
        moves[3] = MOVE_PROTECT;
        break;
    case 4: // Thomas stole the Helix Fossil.
        species = SPECIES_OMASTAR;
        moves[0] = MOVE_SURF;
        moves[1] = MOVE_ICE_BEAM;
        moves[2] = MOVE_ANCIENT_POWER;
        moves[3] = MOVE_PROTECT;
        break;
    default:
        // The normal story path always arrives here with theft state 3 or 4.
        // Keep the protected baseline slot intact for invalid/debug states.
        return;
    }

    mon = &party[3]; // Cinnabar-only replacement for Thomas's Seadra slot.
    personality = GetMonData(mon, MON_DATA_PERSONALITY);
    otId = GetMonData(mon, MON_DATA_OT_ID);

    // Retain the replaced slot's IV tier (24) while applying the locked fossil
    // level, held item, and moves. No fossil-specific nature/ability is authored.
    CreateMon(mon, species, 45, 24, TRUE, personality, OT_ID_PRESET, otId);
    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, moves[i], i);
}
