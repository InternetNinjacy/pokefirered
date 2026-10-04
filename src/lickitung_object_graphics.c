#include "global.h"
#include "gflib.h"
#include "event_object_movement.h"
#include "constants/event_objects.h"

#define OBJ_EVENT_PAL_TAG_NPC_PINK 0x1104
#define OBJ_EVENT_PAL_TAG_NONE 0x11FF
#define LICKITUNG_FRAME_SIZE 128

extern const struct OamData gObjectEventBaseOam_16x16;
extern const struct SubspriteTable gObjectEventSpriteOamTables_16x16[];

const u16 gObjectEventPic_Lickitung[] = INCBIN_U16("graphics/object_events/pics/pokemon/lickitung.4bpp");

#define LICKITUNG_FRAME(n) { .data = (const u8 *)gObjectEventPic_Lickitung + (LICKITUNG_FRAME_SIZE * (n)), .size = LICKITUNG_FRAME_SIZE }

static const struct SpriteFrameImage sPicTable_Lickitung[] = {
    LICKITUNG_FRAME(0), LICKITUNG_FRAME(1), LICKITUNG_FRAME(2),
    LICKITUNG_FRAME(3), LICKITUNG_FRAME(4), LICKITUNG_FRAME(5),
    LICKITUNG_FRAME(6), LICKITUNG_FRAME(7), LICKITUNG_FRAME(8),
};

static const union AnimCmd sAnim_LickitungFaceSouth[] = { ANIMCMD_FRAME(0, 16), ANIMCMD_JUMP(0) };
static const union AnimCmd sAnim_LickitungFaceNorth[] = { ANIMCMD_FRAME(1, 16), ANIMCMD_JUMP(0) };
static const union AnimCmd sAnim_LickitungFaceWest[] = { ANIMCMD_FRAME(2, 16), ANIMCMD_JUMP(0) };
static const union AnimCmd sAnim_LickitungFaceEast[] = { ANIMCMD_FRAME(2, 16, .hFlip = TRUE), ANIMCMD_JUMP(0) };

static const union AnimCmd sAnim_LickitungGoSouth[] = {
    ANIMCMD_FRAME(3, 8), ANIMCMD_FRAME(0, 8), ANIMCMD_FRAME(4, 8), ANIMCMD_FRAME(0, 8), ANIMCMD_JUMP(0)
};
static const union AnimCmd sAnim_LickitungGoNorth[] = {
    ANIMCMD_FRAME(5, 8), ANIMCMD_FRAME(1, 8), ANIMCMD_FRAME(6, 8), ANIMCMD_FRAME(1, 8), ANIMCMD_JUMP(0)
};
static const union AnimCmd sAnim_LickitungGoWest[] = {
    ANIMCMD_FRAME(7, 8), ANIMCMD_FRAME(2, 8), ANIMCMD_FRAME(8, 8), ANIMCMD_FRAME(2, 8), ANIMCMD_JUMP(0)
};
static const union AnimCmd sAnim_LickitungGoEast[] = {
    ANIMCMD_FRAME(7, 8, .hFlip = TRUE), ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8, .hFlip = TRUE), ANIMCMD_FRAME(2, 8, .hFlip = TRUE), ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sAnimTable_Lickitung[] = {
    sAnim_LickitungFaceSouth, sAnim_LickitungFaceNorth, sAnim_LickitungFaceWest, sAnim_LickitungFaceEast,
    sAnim_LickitungGoSouth, sAnim_LickitungGoNorth, sAnim_LickitungGoWest, sAnim_LickitungGoEast,
    sAnim_LickitungGoSouth, sAnim_LickitungGoNorth, sAnim_LickitungGoWest, sAnim_LickitungGoEast,
    sAnim_LickitungGoSouth, sAnim_LickitungGoNorth, sAnim_LickitungGoWest, sAnim_LickitungGoEast,
    sAnim_LickitungGoSouth, sAnim_LickitungGoNorth, sAnim_LickitungGoWest, sAnim_LickitungGoEast,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lickitung = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = LICKITUNG_FRAME_SIZE,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Lickitung,
    .images = sPicTable_Lickitung,
    .affineAnims = gDummySpriteAffineAnimTable,
};
