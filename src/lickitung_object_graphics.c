#include "global.h"
#include "event_object_movement.h"
#include "constants/event_object_movement_constants.h"
#include "constants/event_objects.h"

static const u32 sPic_Lickitung[] = INCBIN_U32("graphics/object_events/pics/pokemon/lickitung.4bpp.lz");

static const struct SpriteFrameImage sImages_Lickitung[] = {
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
    overworld_frame(sPic_Lickitung, 4, 1, 4),
};

// The dedicated Lickitung silhouette uses the established NPC-pink overworld
// palette route, matching the lightweight standalone static-object pattern used
// by the later ENC-002 species packages.
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lickitung = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_PINK,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventBaseSubspriteTables_16x16,
    .anims = gObjectEventGraphicsInfo_BigSnorlax.anims,
    .images = sImages_Lickitung,
    .affineAnims = gDummySpriteAffineAnimTable,
};
