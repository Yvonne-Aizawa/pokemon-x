/*
 * Preliminary decompilation of DllPromotion.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x13244,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x13060.
 *   - 185 ARM prologues, 40 Thumb prologues.
 *   - 356 anonymous |static| imports, 424 external patches.
 *   - 0x3b0 bytes of data; 0xfc bytes of BSS.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0x13244 */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0x13060 */

/* Loader / control object table reference. */
extern uint32_t DllPromotionControlTable[4];

/* The promotion proc is a typical xy_system state machine. Inferred layout
 * (matches the field-access pattern seen at +0x04..+0x2c): */
struct PromotionProc {
    void *vtable;             /* 0x00 */
    void *owner;              /* 0x04 */
    uint8_t reserved08[0x1c]; /* 0x08..0x23 */
    uint8_t state;            /* 0x24 */
    uint8_t sub_state;        /* 0x25 */
    uint16_t parameter;       /* 0x26 */
    int32_t timer;            /* 0x28 */
    uint8_t reserved2c[0x50]; /* 0x2c..0x7b */
    void *anim_state;         /* 0x7c */
};

/* CRO 0x129c4..0x12ad4 region: ARM prologues for the seven principal
 * promotion lifecycle hooks (construct / init / run-step / animate /
 * draw-step / idle / shutdown). Names below are provisional. */
static void promotion_construct(struct PromotionProc *self) { /* TODO: not yet decoded */ }
static void promotion_init(struct PromotionProc *self) { /* TODO: not yet decoded */ }
static void promotion_run(struct PromotionProc *self) { /* TODO: not yet decoded */ }
static void promotion_anim(struct PromotionProc *self) { /* TODO: not yet decoded */ }
static void promotion_draw(struct PromotionProc *self) { /* TODO: not yet decoded */ }
static void promotion_idle(struct PromotionProc *self) { /* TODO: not yet decoded */ }
static void promotion_shutdown(struct PromotionProc *self) { /* TODO: not yet decoded */ }

/* CRO 0x61de..0x6276: two smaller Thumb prologues — likely event
 * listener helpers used when a battle finishes and the promotion screen
 * is invoked. */
static void promotion_event_in(void *self) { /* TODO: not yet decoded */ }
static void promotion_event_out(void *self) { /* TODO: not yet decoded */ }

/* CRO 0xa7f4: a small Thumb helper, `push {r2, r3, r6}` — fast inline
 * state-set used by promotion_run's switch table (single store, no calls). */
static void promotion_set_substate(struct PromotionProc *self, uint8_t s) {
    /* TODO: not yet decoded — body is one STR + return. */
    (void)self; (void)s;
}
