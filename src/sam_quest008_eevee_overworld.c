#include "global.h"
#include "gflib.h"
#include "event_object_movement.h"
#include "constants/event_objects.h"

#define OBJ_EVENT_PAL_TAG_NPC_WHITE 0x1106
#define OBJ_EVENT_PAL_TAG_NONE      0x11FF

static const u32 sEeveeTiles[] = {
    // South
    0x00000000, 0x000FF000, 0x0004F000, 0xFFF44F00, 0x555F0F00, 0x55F5F000, 0xA555F000, 0x155F0000,
    0x00000000, 0x000FF000, 0x000F4000, 0x00F44FFF, 0x00F0F555, 0x000F5F55, 0x000F555A, 0x0000F551,
    0xF1F10000, 0x101F0000, 0x44F00000, 0x44F00000, 0x44F00000, 0x44000000, 0x04F00000, 0x0F000000,
    0x000001F1, 0x005FF010, 0x0F50FF44, 0x00F50F44, 0x0000FF44, 0x00000044, 0x00000F40, 0x000000F0,

    // North
    0x00000000, 0x000FF000, 0x0004F000, 0xFFF44F00, 0x555F0000, 0x555F0000, 0x555F0000, 0xFFF00000,
    0x00000000, 0x000FF000, 0x000F4000, 0x00F44FFF, 0x0000F555, 0x0000F555, 0x0000F555, 0x00000FFF,
    0x111F0000, 0x44F00000, 0x44F00000, 0x44F00000, 0x44F00000, 0x44F00000, 0x04000000, 0x0F000000,
    0x001FF111, 0x0F10FF44, 0x00F10F44, 0x0000FF44, 0x00000F44, 0x00000F44, 0x00000040, 0x000000F0,

    // West
    0x00000000, 0x00FF0000, 0xF04F0000, 0x4F44F000, 0xF555F000, 0xF5555F00, 0xFA5F5F00, 0x0F15F000,
    0x00000000, 0x00000000, 0x0000000F, 0x0000000F, 0x0000000F, 0x00000000, 0x00000000, 0x00000000,
    0xF11F0000, 0x111F0000, 0x444F0000, 0x444F0000, 0x444F0000, 0x444F0000, 0x00400000, 0x00F00000,
    0x005F0000, 0x0F50F00F, 0x00050F44, 0x000F5F44, 0x00000F44, 0x00000F44, 0x00000004, 0x0000000F,

    // East
    0x00000000, 0x00000000, 0xF0000000, 0xF0000000, 0xF0000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x0000FF00, 0x0000F40F, 0x000F44F4, 0x000F555F, 0x00F5555F, 0x00F5F5AF, 0x000F51F0,
    0x0000F500, 0xF00F05F0, 0x44F05000, 0x44F5F000, 0x44F00000, 0x44F00000, 0x40000000, 0xF0000000,
    0x0000F11F, 0x0000F111, 0x0000F444, 0x0000F444, 0x0000F444, 0x0000F444, 0x00000400, 0x00000F00,
};

static const struct SpriteFrameImage sEeveeImages[] = {
    { .data = (const u8 *)sEeveeTiles + 0 * 128, .size = 128 },
    { .data = (const u8 *)sEeveeTiles + 1 * 128, .size = 128 },
    { .data = (const u8 *)sEeveeTiles + 2 * 128, .size = 128 },
    { .data = (const u8 *)sEeveeTiles + 3 * 128, .size = 128 },
};

static const union AnimCmd sEeveeFaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sEeveeFaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sEeveeFaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sEeveeFaceEast[] = {
    ANIMCMD_FRAME(3, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sEeveeAnims[] = {
    sEeveeFaceSouth,
    sEeveeFaceNorth,
    sEeveeFaceWest,
    sEeveeFaceEast,
};

static const struct OamData sEeveeOam = {
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 2,
};

static const struct Subsprite sEeveeSubsprite[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2,
    },
};

static const struct SubspriteTable sEeveeSubspriteTables[] = {
    {0, NULL},
    {1, sEeveeSubsprite},
    {1, sEeveeSubsprite},
    {1, sEeveeSubsprite},
    {1, sEeveeSubsprite},
    {1, sEeveeSubsprite},
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Eevee = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &sEeveeOam,
    .subspriteTables = sEeveeSubspriteTables,
    .anims = sEeveeAnims,
    .images = sEeveeImages,
    .affineAnims = gDummySpriteAffineAnimTable,
};
