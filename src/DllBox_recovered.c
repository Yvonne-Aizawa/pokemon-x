/*
 * Preliminary decompilation of DllBox.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x1f4a4,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x1f374.
 *   - 293 |static| imports, 297 external patches.
 *   - 288 ARM prologues, 50 Thumb prologues, 32 Thumb epilogues.
 *   - Module coordinates PC-Box storage: viewing, sorting, jumping
 *     between boxes, releasing Pokémon.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0x1f4a4 */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0x1f374 */

/* Loader / control object table reference. */
extern uint32_t DllBoxControlTable[4];

/* Box proc layout — inferred from disassembly accesses at +0x04, +0x18,
 * +0x24..+0x28, +0x3c, +0x80..+0x94. */
struct BoxProc {
    void *vtable;             /* 0x00 */
    void *owner;              /* 0x04 */
    void *pokemon_data;       /* 0x08 (active box buffer) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;            /* 0x24 */
    uint8_t sub_state;        /* 0x25 */
    uint16_t parameter;       /* 0x26 */
    int32_t timer;            /* 0x28 */
    uint8_t reserved2c[0x14]; /* 0x2c..0x3f */
    uint8_t box_index;        /* 0x40 */
    uint8_t reserved41[0x3f]; /* 0x41..0x7f */
    void *cursor_pos;         /* 0x80 */
};

/* Standard 6-hook lifecycle. */
static void box_construct(struct BoxProc *self) { /* TODO: not yet decoded */ }
static void box_init(struct BoxProc *self) { /* TODO: not yet decoded */ }
static void box_run(struct BoxProc *self) { /* TODO: not yet decoded */ }
static void box_animate(struct BoxProc *self) { /* TODO: not yet decoded */ }
static void box_draw(struct BoxProc *self) { /* TODO: not yet decoded */ }
static void box_shutdown(struct BoxProc *self) { /* TODO: not yet decoded */ }

/* Box-specific helpers — names derived from the suspected user-visible
 * flow: jump to a different box, scroll within the current box, sort
 * the box contents. The hot patches cluster around +0xc..+0x1c and
 * +0x40..+0x80 ranges. */
static void box_jump_to_box(struct BoxProc *self, int32_t box_idx) {
    /* TODO: not yet decoded */
    (void)self; (void)box_idx;
}
static void box_scroll_within(struct BoxProc *self, int32_t rows) {
    /* TODO: not yet decoded */
    (void)self; (void)rows;
}
static void box_sort_contents(struct BoxProc *self, int32_t mode) {
    /* TODO: not yet decoded */
    (void)self; (void)mode;
}
static void box_release_pokemon(struct BoxProc *self, int32_t slot) {
    /* TODO: not yet decoded */
    (void)self; (void)slot;
}
