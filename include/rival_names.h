#ifndef GUARD_RIVAL_NAMES_H
#define GUARD_RIVAL_NAMES_H

#include "global.h"

const u8 *GetSamBlueName(void);
const u8 *GetSamGreenName(void);
void SetSamBlueName(const u8 *name);
void SetSamGreenName(const u8 *name);
void BufferSamBlueName(u8 *dest);
void BufferSamGreenName(u8 *dest);

#endif // GUARD_RIVAL_NAMES_H
