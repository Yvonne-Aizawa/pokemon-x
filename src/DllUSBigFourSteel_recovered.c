/*
 * Preliminary decompilation of DllUSBigFourSteel.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x158c (mid-function
 *     instruction `add r0, r0, #40` inside the 0x1530..0x15ec frame).
 *   - import table: 34 anonymous slots from |static|, 17 from DllField
 *   - 13 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses (the
 *     owning struct spans at least +0x800, with sub-tables at +0x828,
 *     +0x828+0x4c, +0x5d8, +0x388, +0x1cc, etc.)
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the multiple sub-tables (steel anim data?)
 */

#include <stdint.h>

typedef struct BigFourSteelProc BigFourSteelProc;

/* Offsets inferred from `[r4, #N]` accesses across the
 * 0x388, 0x464, 0x1530 frames. */
struct BigFourSteelProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c */
    uint8_t reserved10[0x14]; /* 0x10..0x23 */
    void *subobj_24[9];     /* 0x24..0x48 (vtable loops via ldr [r6, #0x24]) */
    void *anim_table_48[18]; /* 0x48..0x90 */
    uint8_t reserved90[0x08];
    uint32_t byte_94;
    uint8_t reserved98[0xf48]; /* 0x98..0xfdf */
    void *steel_table_1cc[3]; /* 0x1cc..0x1df (loop 0x15c0..0x15d0) */
    void *steel_table_388[4]; /* 0x388..0x3a7 (loop 0x15b4..0x15c0) */
    void *steel_table_5d8[4]; /* 0x5d8..0x5f7 (loop 0x159c..0x15b4) */
    void *steel_table_828[3]; /* 0x828..0x83f (loop 0x1558..0x1578) */
};

/* CRO 0x310. 4-register "run x4 vtable slots" helper. */
static int big4_steel_run_x4(BigFourSteelProc *self);

/* CRO 0x388. 6-register reset helper. */
static int big4_steel_reset(BigFourSteelProc *self);

/* CRO 0x464..0xe48. 11-register + VFP (vpush d8) main update. */
static int big4_steel_update(BigFourSteelProc *self);

/* CRO 0xe58..0xed0. 4-register + VFP (d8) helper. */
/* CRO 0xee0..0xf84. 3-register + VFP (d8) helper. */
/* CRO 0xf9c..0xfe4. 4-register helper. */
/* CRO 0xfe8..0x1024. 4-register helper. */
/* CRO 0x1074..0x12bc. 8-register + VFP (d8) helper. */
/* CRO 0x12d0..0x13c8. 6-register helper. */
/* CRO 0x13e8..0x1514. 6-register helper. */
/* CRO 0x1530..0x15ec. 2-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x158c; the loader
 *   entry is therefore a mid-function offset (an `add r0, r0, #40`
 *   computing a sub-table base address for an outer sub-call). */
static void *big4_steel_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x1604..0x16cc. 2-register helper. */
/* CRO 0x1714..0x1774. 2-register helper. */