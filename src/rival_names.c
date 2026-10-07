#include "global.h"
#include "rival_names.h"
#include "string_util.h"

const u8 *GetSamBlueName(void)
{
    return gSaveBlock1Ptr->rivalName;
}

const u8 *GetSamGreenName(void)
{
    return gSaveBlock1Ptr->samEdition.greenName;
}

void SetSamBlueName(const u8 *name)
{
    StringCopy_PlayerName(gSaveBlock1Ptr->rivalName, name);
}

void SetSamGreenName(const u8 *name)
{
    StringCopy_PlayerName(gSaveBlock1Ptr->samEdition.greenName, name);
}

void BufferSamBlueName(u8 *dest)
{
    StringCopy_PlayerName(dest, GetSamBlueName());
}

void BufferSamGreenName(u8 *dest)
{
    StringCopy_PlayerName(dest, GetSamGreenName());
}
