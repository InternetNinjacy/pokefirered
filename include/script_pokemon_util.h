#ifndef GUARD_SCRIPT_POKEMON_UTIL_H
#define GUARD_SCRIPT_POKEMON_UTIL_H

bool8 ScriptGiveMon(u16 species, u8 level, u16 item, u32 otName, u32 otId, u8 otGender);
bool8 ScriptGiveSamStarter(u16 species);
void GiveSamStarterFamilyGift(void);
void GetSamBlueStarterSpecies(void);
void GetSamGreenStarterSpecies(void);
void GetSamBlueStarterEndpointSpecies(void);
void GetSamGreenStarterEndpointSpecies(void);
bool8 ScriptGiveEgg(u16 species);
void ScriptSetMonMoveSlot(u8 partyIdx, u16 move, u8 slot);
void HealPlayerParty(void);
void ReducePlayerPartyToThree(void);
void CreateScriptedWildMon(u16 species, u8 level, u16 item);

#endif //GUARD_SCRIPT_POKEMON_UTIL_H
