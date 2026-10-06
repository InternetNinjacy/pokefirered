#ifndef GUARD_DATA_SAM_GYM2_CERULEAN_OBJECT_GRAPHICS_H
#define GUARD_DATA_SAM_GYM2_CERULEAN_OBJECT_GRAPHICS_H

const u32 gObjectEventPic_Leilani[] = INCBIN_U32("graphics/object_events/pics/people/leilani.4bpp");
const u16 gObjectEventPal_Leilani[] = INCBIN_U16("graphics/object_events/palettes/leilani.gbapal");
const u32 gObjectEventPic_Lehua[] = INCBIN_U32("graphics/object_events/pics/people/lehua.4bpp");
const u16 gObjectEventPal_Lehua[] = INCBIN_U16("graphics/object_events/palettes/lehua.gbapal");
const u32 gObjectEventPic_Keahi[] = INCBIN_U32("graphics/object_events/pics/people/keahi.4bpp");
const u16 gObjectEventPal_Keahi[] = INCBIN_U16("graphics/object_events/palettes/keahi.gbapal");

static const struct SpriteFrameImage sPicTable_Leilani[] = {
    overworld_frame(gObjectEventPic_Leilani, 2, 4, 0),
    overworld_frame(gObjectEventPic_Leilani, 2, 4, 1),
    overworld_frame(gObjectEventPic_Leilani, 2, 4, 2),
    overworld_frame(gObjectEventPic_Leilani, 2, 4, 3),
};
static const struct SpriteFrameImage sPicTable_Lehua[] = {
    overworld_frame(gObjectEventPic_Lehua, 2, 4, 0),
    overworld_frame(gObjectEventPic_Lehua, 2, 4, 1),
    overworld_frame(gObjectEventPic_Lehua, 2, 4, 2),
    overworld_frame(gObjectEventPic_Lehua, 2, 4, 3),
};
static const struct SpriteFrameImage sPicTable_Keahi[] = {
    overworld_frame(gObjectEventPic_Keahi, 2, 4, 0),
    overworld_frame(gObjectEventPic_Keahi, 2, 4, 1),
    overworld_frame(gObjectEventPic_Keahi, 2, 4, 2),
    overworld_frame(gObjectEventPic_Keahi, 2, 4, 3),
};

static const union AnimCmd sAnim_Stationary4FacingSouth[] = {ANIMCMD_FRAME(0, 16), ANIMCMD_JUMP(0)};
static const union AnimCmd sAnim_Stationary4FacingNorth[] = {ANIMCMD_FRAME(1, 16), ANIMCMD_JUMP(0)};
static const union AnimCmd sAnim_Stationary4FacingWest[]  = {ANIMCMD_FRAME(2, 16), ANIMCMD_JUMP(0)};
static const union AnimCmd sAnim_Stationary4FacingEast[]  = {ANIMCMD_FRAME(3, 16), ANIMCMD_JUMP(0)};
static const union AnimCmd *const sAnimTable_Stationary4Facing[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_Stationary4FacingSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_Stationary4FacingNorth,
    [ANIM_STD_FACE_WEST] = sAnim_Stationary4FacingWest,
    [ANIM_STD_FACE_EAST] = sAnim_Stationary4FacingEast,
    [ANIM_STD_GO_SOUTH] = sAnim_Stationary4FacingSouth,
    [ANIM_STD_GO_NORTH] = sAnim_Stationary4FacingNorth,
    [ANIM_STD_GO_WEST] = sAnim_Stationary4FacingWest,
    [ANIM_STD_GO_EAST] = sAnim_Stationary4FacingEast,
};

#define SAM_GYM2_OBJECT_INFO(name, palTag, picTable) \
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_##name = { \
    .tileTag = TAG_NONE, .paletteTag = palTag, .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE, \
    .size = 256, .width = 16, .height = 32, .paletteSlot = PALSLOT_NPC_4, \
    .shadowSize = SHADOW_SIZE_M, .inanimate = FALSE, .disableReflectionPaletteLoad = FALSE, \
    .tracks = TRACKS_FOOT, .oam = &gObjectEventBaseOam_16x32, \
    .subspriteTables = gObjectEventSpriteOamTables_16x32, .anims = sAnimTable_Stationary4Facing, \
    .images = picTable, .affineAnims = gDummySpriteAffineAnimTable, \
}

SAM_GYM2_OBJECT_INFO(Leilani, OBJ_EVENT_PAL_TAG_LEILANI, sPicTable_Leilani);
SAM_GYM2_OBJECT_INFO(Lehua, OBJ_EVENT_PAL_TAG_LEHUA, sPicTable_Lehua);
SAM_GYM2_OBJECT_INFO(Keahi, OBJ_EVENT_PAL_TAG_KEAHI, sPicTable_Keahi);
#undef SAM_GYM2_OBJECT_INFO

#endif
