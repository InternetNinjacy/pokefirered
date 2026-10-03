#include "global.h"
#include "gflib.h"
#include "event_object_movement.h"
#include "constants/event_objects.h"

#define OBJ_EVENT_PAL_TAG_NPC_BLUE 0x1103
#define MAGNETON_FRAME_SIZE 128

extern const struct OamData gObjectEventBaseOam_16x16;
extern const struct SubspriteTable *const gObjectEventSpriteOamTables_16x16[];

const u16 gObjectEventPic_Magneton[] = INCBIN_U16("graphics/object_events/pics/pokemon/magneton.4bpp");

#define MAGNETON_FRAME(n) { .data = (const u8 *)gObjectEventPic_Magneton + (MAGNETON_FRAME_SIZE * (n)), .size = MAGNETON_FRAME_SIZE }

static const struct SpriteFrameImage sPicTable_Magneton[] = {
    MAGNETON_FRAME(0),
    MAGNETON_FRAME(1),
    MAGNETON_FRAME(2),
    MAGNETON_FRAME(3),
    MAGNETON_FRAME(4),
    MAGNETON_FRAME(5),
    MAGNETON_FRAME(6),
    MAGNETON_FRAME(7),
    MAGNETON_FRAME(8),
};

static const union AnimCmd sAnim_MagnetonFaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonFaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonFaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonFaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoSouth[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoNorth[] = {
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoWest[] = {
    ANIMCMD_FRAME(7, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(8, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoEast[] = {
    ANIMCMD_FRAME(7, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastNorth[] = {
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastWest[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastEast[] = {
    ANIMCMD_FRAME(7, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFasterSouth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFasterNorth[] = {
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFasterWest[] = {
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFasterEast[] = {
    ANIMCMD_FRAME(7, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastestSouth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastestNorth[] = {
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastestWest[] = {
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MagnetonGoFastestEast[] = {
    ANIMCMD_FRAME(7, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Magneton[] = {
    sAnim_MagnetonFaceSouth,
    sAnim_MagnetonFaceNorth,
    sAnim_MagnetonFaceWest,
    sAnim_MagnetonFaceEast,
    sAnim_MagnetonGoSouth,
    sAnim_MagnetonGoNorth,
    sAnim_MagnetonGoWest,
    sAnim_MagnetonGoEast,
    sAnim_MagnetonGoFastSouth,
    sAnim_MagnetonGoFastNorth,
    sAnim_MagnetonGoFastWest,
    sAnim_MagnetonGoFastEast,
    sAnim_MagnetonGoFasterSouth,
    sAnim_MagnetonGoFasterNorth,
    sAnim_MagnetonGoFasterWest,
    sAnim_MagnetonGoFasterEast,
    sAnim_MagnetonGoFastestSouth,
    sAnim_MagnetonGoFastestNorth,
    sAnim_MagnetonGoFastestWest,
    sAnim_MagnetonGoFastestEast,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Magneton = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = MAGNETON_FRAME_SIZE,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Magneton,
    .images = sPicTable_Magneton,
    .affineAnims = gDummySpriteAffineAnimTable,
};
