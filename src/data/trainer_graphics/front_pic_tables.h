static const u32 gTrainerFrontPic_Satoshi[] = INCBIN_U32("graphics/trainers/front_pics/satoshi.4bpp.lz");
static const u32 gTrainerPalette_Satoshi[] = INCBIN_U32("graphics/trainers/palettes/satoshi.gbapal.lz");

#undef TRAINER_SPRITE
#undef TRAINER_PAL

#define TRAINER_SPRITE(trainerPic, sprite, size) \
    [TRAINER_PIC_##trainerPic] = { \
        (TRAINER_PIC_##trainerPic == TRAINER_PIC_SATOSHI) ? gTrainerFrontPic_Satoshi : (sprite), \
        size, \
        TRAINER_PIC_##trainerPic \
    }
#define TRAINER_PAL(trainerPic, pal) \
    [TRAINER_PIC_##trainerPic] = { \
        (TRAINER_PIC_##trainerPic == TRAINER_PIC_SATOSHI) ? gTrainerPalette_Satoshi : (pal), \
        TRAINER_PIC_##trainerPic \
    }

#include "front_pic_tables_arch006_base.h"

#undef TRAINER_SPRITE
#undef TRAINER_PAL

#define TRAINER_SPRITE(trainerPic, sprite, size) [TRAINER_PIC_##trainerPic] = {sprite, size, TRAINER_PIC_##trainerPic}
#define TRAINER_PAL(trainerPic, pal) [TRAINER_PIC_##trainerPic] = {pal, TRAINER_PIC_##trainerPic}
