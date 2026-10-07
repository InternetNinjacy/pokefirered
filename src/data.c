#include "global.h"
#include "gflib.h"
#include "battle.h"
#include "data.h"
#include "graphics.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/battle_ai.h"
#include "constants/trainers.h"

#define BATTLER_OFFSET(i) (gHeap + 0x8000 + MON_PIC_SIZE * (i))

const struct SpriteFrameImage gBattlerPicTable_PlayerLeft[] =
{
    BATTLER_OFFSET(0), MON_PIC_SIZE,
    BATTLER_OFFSET(1), MON_PIC_SIZE,
    BATTLER_OFFSET(2), MON_PIC_SIZE,
    BATTLER_OFFSET(3), MON_PIC_SIZE,
};

const struct SpriteFrameImage gBattlerPicTable_OpponentLeft[] =
{
    BATTLER_OFFSET(4), MON_PIC_SIZE,
    BATTLER_OFFSET(5), MON_PIC_SIZE,
    BATTLER_OFFSET(6), MON_PIC_SIZE,
    BATTLER_OFFSET(7), MON_PIC_SIZE,
};

const struct SpriteFrameImage gBattlerPicTable_PlayerRight[] =
{
    BATTLER_OFFSET(8),  MON_PIC_SIZE,
    BATTLER_OFFSET(9),  MON_PIC_SIZE,
    BATTLER_OFFSET(10), MON_PIC_SIZE,
    BATTLER_OFFSET(11), MON_PIC_SIZE,
};

const struct SpriteFrameImage gBattlerPicTable_OpponentRight[] =
{
    BATTLER_OFFSET(12), MON_PIC_SIZE,
    BATTLER_OFFSET(13), MON_PIC_SIZE,
    BATTLER_OFFSET(14), MON_PIC_SIZE,
    BATTLER_OFFSET(15), MON_PIC_SIZE,
};

const struct SpriteFrameImage gTrainerBackPicTable_Red[] =
{
    gTrainerBackPic_Red, 0x0800,
    gTrainerBackPic_Red + 0x0800, 0x0800,
    gTrainerBackPic_Red + 0x1000, 0x0800,
    gTrainerBackPic_Red + 0x1800, 0x0800,
    gTrainerBackPic_Red + 0x2000, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_Leaf[] =
{
    gTrainerBackPic_Leaf, 0x0800,
    gTrainerBackPic_Leaf + 0x0800, 0x0800,
    gTrainerBackPic_Leaf + 0x1000, 0x0800,
    gTrainerBackPic_Leaf + 0x1800, 0x0800,
    gTrainerBackPic_Leaf + 0x2000, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_Pokedude[] =
{
    gTrainerBackPic_Pokedude, 0x0800,
    gTrainerBackPic_Pokedude + 0x0800, 0x0800,
    gTrainerBackPic_Pokedude + 0x1000, 0x0800,
    gTrainerBackPic_Pokedude + 0x1800, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_OldMan[] =
{
    gTrainerBackPic_OldMan, 0x0800,
    gTrainerBackPic_OldMan + 0x0800, 0x0800,
    gTrainerBackPic_OldMan + 0x1000, 0x0800,
    gTrainerBackPic_OldMan + 0x1800, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_RSBrendan[] =
{
    gTrainerBackPic_RSBrendan, 0x0800,
    gTrainerBackPic_RSBrendan + 0x0800, 0x0800,
    gTrainerBackPic_RSBrendan + 0x1000, 0x0800,
    gTrainerBackPic_RSBrendan + 0x1800, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_RSMay[] =
{
    gTrainerBackPic_RSMay, 0x0800,
    gTrainerBackPic_RSMay + 0x0800, 0x0800,
    gTrainerBackPic_RSMay + 0x1000, 0x0800,
    gTrainerBackPic_RSMay + 0x1800, 0x0800,
};

static const union AnimCmd sAnim_GeneralFrame0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_GeneralFrame3[] =
{
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_END,
};

// Many of these affine anims seem to go unused, and
// instead SetSpriteRotScale is used to manipulate
// the battler sprites directly (for instance, in AnimTask_SwitchOutShrinkMon).
// Those with explicit indexes are referenced elsewhere.

static const union AffineAnimCmd sAffineAnim_Battler_Normal[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Flipped[] =
{
    AFFINEANIMCMD_FRAME(-0x100, 0x0100, 0, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Emerge[] =
{
    AFFINEANIMCMD_FRAME(0x28, 0x28, 0, 0),
    AFFINEANIMCMD_FRAME(0x12, 0x12, 0, 12),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Return[] =
{
    AFFINEANIMCMD_FRAME(-0x2, -0x2, 0, 18),
    AFFINEANIMCMD_FRAME(-0x10, -0x10, 0, 15),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_HorizontalSquishLoop[] =
{
    AFFINEANIMCMD_FRAME(0xA0, 0x100, 0, 0),
    AFFINEANIMCMD_FRAME( 0x4,   0x0, 0, 8),
    AFFINEANIMCMD_FRAME(-0x4,   0x0, 0, 8),
    AFFINEANIMCMD_JUMP(1),
};

static const union AffineAnimCmd sAffineAnim_Battler_Grow[] =
{
    AFFINEANIMCMD_FRAME(0x2, 0x2, 0, 20),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Shrink[] =
{
    AFFINEANIMCMD_FRAME(-0x2, -0x2, 0, 20),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_BigToSmall[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_FRAME(-0x10, -0x10, 0, 9),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_GrowLarge[] =
{
    AFFINEANIMCMD_FRAME(0x4, 0x4, 0, 63),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_TipRight[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -3, 5),
    AFFINEANIMCMD_FRAME(0x0, 0x0,  3, 5),
    AFFINEANIMCMD_END,
};

const union AffineAnimCmd *const gAffineAnims_BattleSpritePlayerSide[] =
{
    [BATTLER_AFFINE_NORMAL] = sAffineAnim_Battler_Normal,
    [BATTLER_AFFINE_EMERGE] = sAffineAnim_Battler_Emerge,
    [BATTLER_AFFINE_RETURN] = sAffineAnim_Battler_Return,
    sAffineAnim_Battler_HorizontalSquishLoop,
    sAffineAnim_Battler_Grow,
    sAffineAnim_Battler_Shrink,
    sAffineAnim_Battler_GrowLarge,
    sAffineAnim_Battler_TipRight,
    sAffineAnim_Battler_BigToSmall,
};

static const union AffineAnimCmd sAffineAnim_Battler_SpinShrink[] =
{
    AFFINEANIMCMD_FRAME(-0x4, -0x4, 4, 63),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_TipLeft[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0,  3, 5),
    AFFINEANIMCMD_FRAME(0x0, 0x0, -3, 5),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_RotateUpAndBack[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -5, 20),
    AFFINEANIMCMD_FRAME(0x0, 0x0,  0, 20),
    AFFINEANIMCMD_FRAME(0x0, 0x0,  5, 20),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Spin[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 9, 110),
    AFFINEANIMCMD_END,
};

const union AffineAnimCmd *const gAffineAnims_BattleSpriteOpponentSide[] =
{
    [BATTLER_AFFINE_NORMAL] = sAffineAnim_Battler_Normal,
    [BATTLER_AFFINE_EMERGE] = sAffineAnim_Battler_Emerge,
    [BATTLER_AFFINE_RETURN] = sAffineAnim_Battler_Return,
    sAffineAnim_Battler_HorizontalSquishLoop,
    sAffineAnim_Battler_Grow,
    sAffineAnim_Battler_Shrink,
    sAffineAnim_Battler_SpinShrink,
    sAffineAnim_Battler_TipLeft,
    sAffineAnim_Battler_RotateUpAndBack,
    sAffineAnim_Battler_BigToSmall,
    sAffineAnim_Battler_Spin,
};

const union AffineAnimCmd *const gAffineAnims_BattleSpriteContest[] =
{
    [BATTLER_AFFINE_NORMAL] = sAffineAnim_Battler_Flipped,
    [BATTLER_AFFINE_EMERGE] = sAffineAnim_Battler_Emerge,
    [BATTLER_AFFINE_RETURN] = sAffineAnim_Battler_Return,
    sAffineAnim_Battler_HorizontalSquishLoop,
    sAffineAnim_Battler_Grow,
    sAffineAnim_Battler_Shrink,
    sAffineAnim_Battler_SpinShrink,
    sAffineAnim_Battler_TipLeft,
    sAffineAnim_Battler_RotateUpAndBack,
    sAffineAnim_Battler_BigToSmall,
    sAffineAnim_Battler_Spin,
};

static const union AnimCmd sAnim_MonPic_0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MonPic_1[] =
{
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MonPic_2[] =
{
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MonPic_3[] =
{
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_END,
};

const union AnimCmd *const gAnims_MonPic[] =
{
    sAnim_MonPic_0,
    sAnim_MonPic_1,
    sAnim_MonPic_2,
    sAnim_MonPic_3,
};

#define SPECIES_SPRITE(species, sprite) [SPECIES_##species] = {sprite, 0x800, SPECIES_##species}
#define SPECIES_PAL(species, pal) [SPECIES_##species] = {pal, SPECIES_##species}
#define SPECIES_SHINY_PAL(species, pal) [SPECIES_##species] = {pal, SPECIES_##species + SPECIES_SHINY_TAG}

#define TRAINER_SPRITE(trainerPic, sprite, size) [TRAINER_PIC_##trainerPic] = {sprite, size, TRAINER_PIC_##trainerPic}
#define TRAINER_PAL(trainerPic, pal) [TRAINER_PIC_##trainerPic] = {pal, TRAINER_PIC_##trainerPic}

#include "data/pokemon_graphics/front_pic_coordinates.h"
#include "data/pokemon_graphics/front_pic_table.h"
#include "data/pokemon_graphics/back_pic_coordinates.h"
#include "data/pokemon_graphics/back_pic_table.h"
#include "data/pokemon_graphics/palette_table.h"
#include "data/pokemon_graphics/shiny_palette_table.h"

#include "data/trainer_graphics/front_pic_anims.h"
#include "data/trainer_graphics/front_pic_tables.h"
#include "data/trainer_graphics/back_pic_anims.h"
#include "data/trainer_graphics/back_pic_tables.h"

#include "data/pokemon_graphics/enemy_mon_elevation.h"

#include "data/trainer_parties.h"
#include "data/sam_satoshi_trainer_parties.h"
#include "data/sam_green_trainer_parties.h"
#include "data/sam_route3_trainer_parties.h"
#include "data/sam_route24_trainer_parties.h"
#include "data/sam_hothouse_trainer_parties.h"
#include "data/text/trainer_class_names.h"

// The Hothouse reuses five otherwise-dormant Ruby/Sapphire trainer slots.
// Redirect only those party pointers; all ordinary FireRed trainer data remains
// untouched.
#define SAM_HOTHOUSE_CAT_INNER(a, b) a##b
#define SAM_HOTHOUSE_CAT(a, b) SAM_HOTHOUSE_CAT_INNER(a, b)
#define SAM_HOTHOUSE_SECOND(a, b, ...) b
#define SAM_HOTHOUSE_IS_PROBE(...) SAM_HOTHOUSE_SECOND(__VA_ARGS__, 0)
#define SAM_HOTHOUSE_PROBE() ~, 1

#define SAM_HOTHOUSE_GARDENER_sParty_RSAromaLady SAM_HOTHOUSE_PROBE()
#define SAM_HOTHOUSE_GARDENER_sParty_RSLady SAM_HOTHOUSE_PROBE()
#define SAM_HOTHOUSE_GARDENER_sParty_RSBeauty SAM_HOTHOUSE_PROBE()
#define SAM_HOTHOUSE_GARDENER_sParty_RSPkmnBreederM SAM_HOTHOUSE_PROBE()
#define SAM_HOTHOUSE_HAWTHORNE_sParty_RSCooltrainerM SAM_HOTHOUSE_PROBE()

#define SAM_HOTHOUSE_IS_GARDENER(party) SAM_HOTHOUSE_IS_PROBE(SAM_HOTHOUSE_CAT(SAM_HOTHOUSE_GARDENER_, party))
#define SAM_HOTHOUSE_IS_HAWTHORNE(party) SAM_HOTHOUSE_IS_PROBE(SAM_HOTHOUSE_CAT(SAM_HOTHOUSE_HAWTHORNE_, party))

#define SAM_HOTHOUSE_GARDENER_PARTY_sParty_RSAromaLady sParty_SamHothouseIrrigation
#define SAM_HOTHOUSE_GARDENER_PARTY_sParty_RSLady sParty_SamHothouseSun
#define SAM_HOTHOUSE_GARDENER_PARTY_sParty_RSBeauty sParty_SamHothouseClimate
#define SAM_HOTHOUSE_GARDENER_PARTY_sParty_RSPkmnBreederM sParty_SamHothouseSoil
#define SAM_HOTHOUSE_GARDENER_PARTY(party) SAM_HOTHOUSE_CAT(SAM_HOTHOUSE_GARDENER_PARTY_, party)

#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_NORMAL(party) \
    { .NoItemDefaultMoves = party }, .partySize = ARRAY_COUNT(party), .partyFlags = 0
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER(party) \
    { .NoItemCustomMoves = SAM_HOTHOUSE_GARDENER_PARTY(party) }, \
    .partySize = ARRAY_COUNT(SAM_HOTHOUSE_GARDENER_PARTY(party)), \
    .partyFlags = F_TRAINER_PARTY_CUSTOM_MOVESET
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE(party) \
    { .ItemCustomMoves = sParty_SamHothouseHawthorne }, \
    .partySize = ARRAY_COUNT(sParty_SamHothouseHawthorne), \
    .partyFlags = F_TRAINER_PARTY_CUSTOM_MOVESET | F_TRAINER_PARTY_HELD_ITEM

#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER_SELECT_0(party) SAM_HOTHOUSE_NO_ITEM_DEFAULT_NORMAL(party)
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER_SELECT_1(party) SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER(party)
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER_SELECT(flag, party) \
    SAM_HOTHOUSE_CAT(SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER_SELECT_, flag)(party)
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE_SELECT_0(party) \
    SAM_HOTHOUSE_NO_ITEM_DEFAULT_GARDENER_SELECT(SAM_HOTHOUSE_IS_GARDENER(party), party)
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE_SELECT_1(party) SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE(party)
#define SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE_SELECT(flag, party) \
    SAM_HOTHOUSE_CAT(SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE_SELECT_, flag)(party)

#undef NO_ITEM_DEFAULT_MOVES
#define NO_ITEM_DEFAULT_MOVES(party) \
    SAM_HOTHOUSE_NO_ITEM_DEFAULT_HAWTHORNE_SELECT(SAM_HOTHOUSE_IS_HAWTHORNE(party), party)

#include "data/trainers.h"

#undef NO_ITEM_DEFAULT_MOVES
#define NO_ITEM_DEFAULT_MOVES(party) { .NoItemDefaultMoves = party }, .partySize = ARRAY_COUNT(party), .partyFlags = 0

#include "data/text/species_names.h"
#include "data/text/move_names.h"
