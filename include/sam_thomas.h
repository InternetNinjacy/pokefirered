#ifndef GUARD_SAM_THOMAS_H
#define GUARD_SAM_THOMAS_H

void ApplyThomasMtMoonStarterBranch(struct Pokemon *party, u16 trainerNum);
void ApplyThomasCinnabarFossilBranch(struct Pokemon *party, u16 trainerNum);
void ApplyThomasViridianFossilBranch(struct Pokemon *party, u16 trainerNum);
u8 CountThomasUsablePlayerMons(void);
void Script_CountThomasUsablePlayerMons(void);
bool8 IsThomasOneMonDoubleBattle(void);

#endif
