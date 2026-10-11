/*
 * Preliminary decompilation of DllSparring.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Single named export: `nnroControlObject_` at CRO 0x17264.
 *   - Imports DllTrainingAppManager (via a single anonymous entrypoint).
 *   - 255 |static| imports, 283 ARM prologues and 34 Thumb prologues.
 *   - 278 external patches.
 *   - Substantial data segment (0x280) and BSS (0xd4) — typical training/
 *     sparring save-state layout.
 */

#include <stdint.h>

/* Named export. */
extern void nnroControlObject_(void);  /* CRO 0x17264 */

/* Loader / control object table reference. */
extern uint32_t DllSparringControlTable[4];

/* The imported module DllTrainingAppManager provides one entry point.
 * Signature inferred from the single BL into the unnamed stub near
 * +0xad..+0xb0 (call site: receiver == r0, one arg in r1).
 */
extern void *DllTrainingAppManager_op0(void *arg0, uint32_t arg1);

/* Sparring instance layout (inferred from field accesses at +0x18, +0x24,
 * +0x38, +0x5c, +0x84). */
struct SparringWork {
    void *vtable;               /* 0x00 */
    void *parent;               /* 0x04 */
    void *app_manager;          /* 0x08 */
    uint8_t reserved0c[0x14];   /* 0x0c..0x1f */
    uint8_t state;              /* 0x20 */
    uint8_t sub_state;          /* 0x21 */
    uint16_t parameter;         /* 0x22 */
    int32_t timer;              /* 0x24 */
    uint8_t reserved28[0x14];   /* 0x28..0x3b */
    uint32_t scores[4];         /* 0x3c..0x4b (4 entries, 4 bytes each) */
    uint8_t reserved4c[0x40];   /* 0x4c..0x8b */
    uint32_t partner_id;        /* 0x8c */
};

/* Sparring proc lifecycle (typical 6-hook structure). */
static void sparring_construct(struct SparringWork *self) { /* TODO: not yet decoded */ }
static void sparring_init(struct SparringWork *self) { /* TODO: not yet decoded */ }
static void sparring_run(struct SparringWork *self) { /* TODO: not yet decoded */ }
static void sparring_animate(struct SparringWork *self) { /* TODO: not yet decoded */ }
static void sparring_draw(struct SparringWork *self) { /* TODO: not yet decoded */ }
static void sparring_shutdown(struct SparringWork *self) { /* TODO: not yet decoded */ }

/* Smaller Thumb prologue near +0x? in segment 0 — event listener that
 * wraps a sub-state advance and forwards the result to the parent. */
static void sparring_event_handler(void *self, int32_t evt) {
    /* TODO: not yet decoded — body uses one or two static-import calls. */
    (void)self; (void)evt;
}
