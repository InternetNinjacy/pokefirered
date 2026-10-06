#ifndef GUARD_SAM_SPECIAL_ACQUISITION_H
#define GUARD_SAM_SPECIAL_ACQUISITION_H

#include "global.h"
#include "pokemon.h"

// Delivers an already-authored Pokemon without replacing its OT identity.
// Uses party-first / PC-fallback semantics and fails cleanly if both are full.
u8 GivePreOwnedMonToPlayer(struct Pokemon *mon);

#endif // GUARD_SAM_SPECIAL_ACQUISITION_H
