/*
 * Preliminary decompilation of DllUSBadgeCheckGate.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: Badge-check "gate" building. The NPC inside inspects the
 * player's badge count and opens/closes the gate accordingly.  Smaller than
 * the gym modules but with the same lifecycle pattern.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x570 (constructor entry point).
 *   - 14 static-module imports + 9 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x6f0..0x7c4.
 *
 * Recovered:
 *   - 10 function boundaries (see stubs below).
 *   - Object layout:
 *       +0x00 vtable
 *       +0x04 parent
 *       +0x08 gameplay world ptr (the field obj)
 *       +0x0c field sub-obj
 *       +0x1c child (the gate NPC)
 *       +0x20 child frame slot
 *       +0x24 child cell
 *       +0x28 child view (5 entries at +0x2c..+0x44)
 *       +0x30 child view #2
 *   - Three small "lifecycle" helpers return 0 (bx-lr/mov r0, #0).
 *   - The 0x244 worker is the main per-frame update; reads field offsets
 *     +0x1c/+0x28/+0x2c and dispatches via slot 0x1a8 with 7 args.
 *   - The 0x298 worker is the badge-check state machine (4 states), uses
 *     float registers (vpush {d8}) and calls vtable+0x40/0x48/0xf0 on the
 *     gate child.
 *
 * Not yet decoded:
 *   - The 0x4e0/0x524/0x54c/0x608/0x660/0x690/0x6f8 helpers -- mostly small
 *     lifecycle stubs whose semantics are not yet labeled.
 *   - The literal pool constants at 0x4c8..0x4d4 (four float constants).
 *   - The 0x198 setter function (called from 0x298 to set a 32-bit word
 *     on a child view).
 */

#include <stdint.h>

typedef struct BadgeGateProc BadgeGateProc;

/* Confirmed from field accesses in the original ARM code. */
struct BadgeGateProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *world;           /* 0x08 */
    void *field;           /* 0x0c */
    uint8_t reserved10[0xc];
    void *child;           /* 0x1c - gate NPC child */
    void *frame;           /* 0x20 */
    void *cell;            /* 0x24 */
    void *view[5];         /* 0x28..0x44 - 5 layout entries */
    void *view2;           /* 0x30 - alternate view */
    uint8_t reserved48[8];
    void *field_obj2;      /* 0x50 - sub-cell */
};

/* --- Lifecycle stubs (return 0/1). --- */

/* CRO 0x180..0x1c8: import jump table. */

/* CRO 0x1d0..0x1e8: lifecycle helpers. */
static int badgegate_can_run(void) { return 1; }
static int badgegate_can_stop(void) { return 1; }
static int badgegate_can_draw(void) { return 0; }
static int badgegate_can_other(void) { return 0; }
static void badgegate_release_noop(void);
static void badgegate_release_noop2(void);
static void badgegate_release_noop3(void);

/* --- Per-frame update. CRO 0x244. --- */
/* Reads field at +0x14 (self->world->field24->c4) and dispatches via slot
 * 0x1a8 with 7 args.  Updates self->frame at +0x20 and self->cell at +0x24. */
static int badgegate_update_a(BadgeGateProc *self);

/* --- Badge-check state machine. CRO 0x298. --- */
/* 4-state machine over the gate NPC child at +0x1c.  Reads parent->field50
 * (gameplay world), iterates 0x13000+0x148+0x1d0 to verify the badge mask.
 * Calls vtable+0x40 / 0x48 / 0xf0 on the gate child, plus the imported
 * slot 0x1b0 to draw the result.  Uses float registers for cell timing. */
static int badgegate_run(BadgeGateProc *self);

/* --- Helper. CRO 0x4e0. --- */
static void badgegate_helper_a(BadgeGateProc *self);

/* --- Helper. CRO 0x524. --- */
static void badgegate_helper_b(BadgeGateProc *self);

/* --- Helper. CRO 0x54c. --- */
static void badgegate_helper_c(BadgeGateProc *self);

/* --- Helper. CRO 0x608. --- */
/* 4-arg function (push {r4, r5, r6, lr}) - looks up a vtable slot and
 * emits an event. */
static int badgegate_helper_d(BadgeGateProc *self, int arg1, int arg2);

/* --- Helper. CRO 0x660. --- */
static void badgegate_helper_e(BadgeGateProc *self);

/* --- Helper. CRO 0x690. --- */
static void badgegate_helper_f(BadgeGateProc *self);

/* --- Helper. CRO 0x6f8. --- */
static void badgegate_helper_g(BadgeGateProc *self);

/* --- Standard NN loader infrastructure --- */

/* CRO 0x6f0. Init for the module's BSS -- sets two error-counter slots to -1. */
static void badgegate_bss_init(void);

/* CRO 0x71c. Loader vtable dispatcher (slot 0..5). */
static int badgegate_loader_dispatch(void *obj, int slot);