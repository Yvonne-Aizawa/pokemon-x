/*
 * Preliminary decompilation of DllBag.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x13864,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x13734.
 *   - 376 anonymous |static| imports, 384 external patches.
 *   - 220 ARM push prologues, 45 Thumb push prologues detected in the
 *     local disassembly (the high ARM count includes data-interpreting
 *     false positives; sanity-check against pop epilogues narrows this).
 *   - Data segment 0x14 bytes (almost certainly vtables plus RTTI info).
 *   - BSS 0x5c bytes — small per-process work buffer.
 */

#include <stdint.h>

/* Forward declarations for the two named exports. */
extern void nnroControlObject_(void);                         /* CRO 0x13864 */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag);   /* CRO 0x13734 */

/* Loader / control object table at CRO 0x13864 (named export
 * `nnroControlObject_`). Inferred: small interworking thunk table consumed
 * by the nn-modules loader. Exact layout is the standard 4-word pattern. */
extern uint32_t DllBagControlTable[4];

/* BagScreen instance layout. The patch density around the segment 0
 * region 0x800..0xc00 implies field accesses at +0x18, +0x24, +0x28,
 * +0x40, +0x7c. Total instance size exceeds 0x100 but is not yet known. */
struct BagScreen {
    void *vtable;              /* 0x00 */
    void *parent;              /* 0x04 */
    void *bag_storage;         /* 0x08 (pointer to item-storage buffer) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;             /* 0x24 */
    uint8_t sub_state;         /* 0x25 */
    uint16_t parameter;        /* 0x26 */
    int32_t timer;             /* 0x28 */
    uint8_t reserved2c[0x14]; /* 0x2c..0x3f */
    void *item_grid;           /* 0x40 (item grid view handle) */
    uint8_t reserved44[0x38]; /* 0x44..0x7b */
    void *cursor_pos;          /* 0x7c (cursor slot handle) */
};

/* CRO 0x13734 — demangled C++ method xy_system::bg::System::SetIsCallDraw.
 * ARM prologue observed. Body forwards the flag to a peer module helper. */
void xy_system_bg_System_SetIsCallDraw(int32_t flag) {
    /* TODO: not yet decoded — body calls a |static| helper. */
    (void)flag;
}

/* CRO 0x12b98 — Thumb prologue `push {r2, r3, r4, r5, r6, lr}`. Likely a
 * main bag-screen state-dispatch handler. */
static void bag_12b98(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* CRO 0x12bc4 — Thumb prologue `push {r0, r1, r2, r3, r5, r6, lr}`. */
static void bag_12bc4(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* CRO 0x12c10 — Thumb prologue `push {r1, r2, r3, r4, r6, lr}`. */
static void bag_12c10(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* CRO 0x12c20 — Thumb prologue `push {r4, r5, r6, lr}`. */
static void bag_12c20(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* CRO 0x12d34 — Thumb prologue `push {r0, r2, r5, r6, r7, lr}`. */
static void bag_12d34(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* CRO 0x12de8 — Thumb prologue `push {r3, r4, r5, r7, lr}`. */
static void bag_12de8(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* CRO 0x12fa0 — Thumb prologue `push {r1, r3, r6, lr}`. */
static void bag_12fa0(struct BagScreen *self) {
    (void)self; /* TODO: not yet decoded */
}
/* All of the above are documented at their start offset; bodies are
 * TODO until the call graph is resolved from the .crs symbol map.
 */
