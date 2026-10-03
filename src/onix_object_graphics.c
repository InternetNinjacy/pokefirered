#include "global.h"
#include "gflib.h"
#include "event_object_movement.h"
#include "constants/event_objects.h"

#define OBJ_EVENT_PAL_TAG_RHYHORN 0x111D
#define OBJ_EVENT_PAL_TAG_NONE 0x11FF
#define ONIX_FRAME_SIZE 128

extern const struct OamData gObjectEventBaseOam_16x16;
extern const struct SubspriteTable gObjectEventSpriteOamTables_16x16[];

const u16 gObjectEventPic_Onix[] = INCBIN_U16("graphics/object_events/pics/pokemon/onix.4bpp");

#define ONIX_FRAME(n) { .data = (const u8 *)gObjectEventPic_Onix + (ONIX_FRAME_SIZE * (n)), .size = ONIX_FRAME_SIZE }

static const struct SpriteFrameImage sPicTable_Onix[] = {
    ONIX_FRAME(0), ONIX_FRAME(1), ONIX_FRAME(2),
    ONIX_FRAME(3), ONIX_FRAME(4), ONIX_FRAME(5),
    ONIX_FRAME(6), ONIX_FRAME(7), ONIX_FRAME(8),
};

static const union AnimCmd sAnim_OnixFaceSouth[] = { ANIMCMD_FRAME(0, 16), ANIMCMD_JUMP(0) };
static const union AnimCmd sAnim_OnixFaceNorth[] = { ANIMCMD_FRAME(1, 16), ANIMCMD_JUMP(0) };
static const union AnimCmd sAnim_OnixFaceWest[] = { ANIMCMD_FRAME(2, 16), ANIMCMD_JUMP(0) };
static const union AnimCmd sAnim_OnixFaceEast[] = { ANIMCMD_FRAME(2, 16, .hFlip = TRUE), ANIMCMD_JUMP(0) };

static const union AnimCmd sAnim_OnixGoSouth[] = {
    ANIMCMD_FRAME(3, 8), ANIMCMD_FRAME(0, 8), ANIMCMD_FRAME(4, 8), ANIMCMD_FRAME(0, 8), ANIMCMD_JUMP(0)
};
static const union AnimCmd sAnim_OnixGoNorth[] = {
    ANIMCMD_FRAME(5, 8), ANIMCMD_FRAME(1, 8), ANIMCMD_FRAME(6, 8), ANIMCMD_FRAME(1, 8), ANIMCMD_JUMP(0)
};
static const union AnimCmd sAnim_OnixGoWest[] = {
    ANIMCMD_FRAME(7, 8), ANIMCMD_FRAME(2, 8), ANIMCMD_FRAME(8, 8), ANIMCMD_FRAME(2, 8), ANIMCMD_JUMP(0)
};
static const union AnimCmd sAnim_OnixGoEast[] = {
    ANIMCMD_FRAME(7, 8, .hFlip = TRUE), ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8, .hFlip = TRUE), ANIMCMD_FRAME(2, 8, .hFlip = TRUE), ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sAnimTable_Onix[] = {
    sAnim_OnixFaceSouth, sAnim_OnixFaceNorth, sAnim_OnixFaceWest, sAnim_OnixFaceEast,
    sAnim_OnixGoSouth, sAnim_OnixGoNorth, sAnim_OnixGoWest, sAnim_OnixGoEast,
    sAnim_OnixGoSouth, sAnim_OnixGoNorth, sAnim_OnixGoWest, sAnim_OnixGoEast,
    sAnim_OnixGoSouth, sAnim_OnixGoNorth, sAnim_OnixGoWest, sAnim_OnixGoEast,
    sAnim_OnixGoSouth, sAnim_OnixGoNorth, sAnim_OnixGoWest, sAnim_OnixGoEast,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Onix = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_RHYHORN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = ONIX_FRAME_SIZE,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Onix,
    .images = sPicTable_Onix,
    .affineAnims = gDummySpriteAffineAnimTable,
};
