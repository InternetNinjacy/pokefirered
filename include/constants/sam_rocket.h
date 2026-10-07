#ifndef GUARD_CONSTANTS_SAM_ROCKET_H
#define GUARD_CONSTANTS_SAM_ROCKET_H

// Independent parallel operations; vanilla progression and Thomas stages are
// owned by their existing scripts. Future hooks must use the current authority.
#define ROCKET_OPERATION_VIRIDIAN_THEFT     (1 << 0)
#define ROCKET_OPERATION_MT_MOON            (1 << 1)
#define ROCKET_OPERATION_CERULEAN           (1 << 2)
#define ROCKET_OPERATION_VERMILION          (1 << 3)
#define ROCKET_OPERATION_LAVENDER           (1 << 4)
#define ROCKET_OPERATION_CELADON            (1 << 5)
#define ROCKET_OPERATION_FUCHSIA            (1 << 6)
#define ROCKET_OPERATION_SAFFRON            (1 << 7)
#define ROCKET_OPERATION_CINNABAR           (1 << 8)
#define ROCKET_OPERATION_VIRIDIAN_CLEANUP   (1 << 9)
#define ROCKET_OPERATION_FIVE_ISLAND        (1 << 10)
#define ROCKET_OPERATION_MASK              0x07FF

#define ROCKET_EVIDENCE_DELIVERY_01         (1 << 0)
#define ROCKET_EVIDENCE_DELIVERY_02         (1 << 1)
#define ROCKET_EVIDENCE_DELIVERY_03         (1 << 2)
#define ROCKET_EVIDENCE_DELIVERY_04         (1 << 3)
#define ROCKET_EVIDENCE_BOUND_MASK          0x000F

#define ROCKET_VIRIDIAN_PENDING             0
#define ROCKET_VIRIDIAN_GOODS_RECOVERED     1
#define ROCKET_VIRIDIAN_BALLS_OWED          2
#define ROCKET_VIRIDIAN_DOSSIER_OWED        3
#define ROCKET_VIRIDIAN_COMPLETE            4

#endif
