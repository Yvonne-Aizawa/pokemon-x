/*
 * Preliminary decompilation of DllUSGymInsect.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0xf70 (mid-function
 *     instruction `str r6, [r0, #32]` inside the 0xf4c..0x1004 frame;
 *     the surrounding body zeros offsets +0x0c..+0x24 before populating
 *     them via imported lookups).
 *   - import table: 52 anonymous slots from |static|, 4 from DllField
 *   - 16 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the +0x28, +0x6c, +0x3a8, +0x400 sub-objects
 *     (insect gym uses a heavy 3D scene with bee/butterfly VFX)
 *
 * Note on name: this is the Bug-type gym scene (Santalune City's
 * Viola in X/Y); uses VFP d8 for the 3D camera math.
 */

#include <stdint.h>

typedef struct USGymInsectProc USGymInsectProc;

/* Offsets inferred from `[r0, #N]` / `[r4, #N]` accesses across the
 * 0x318, 0x364, 0x4e4, 0xc48, 0xf4c frames. */
struct USGymInsectProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c (zeroed at 0xf58) */
    void *child2;           /* 0x10 (zeroed at 0xf5c) */
    void *child3;           /* 0x14 (zeroed at 0xf60) */
    void *child4;           /* 0x18 (zeroed at 0xf64) */
    void *child5;           /* 0x1c (zeroed at 0xf6c) */
    void *child6;           /* 0x20 (zeroed at 0xf70) */
    void *child7;           /* 0x24 (zeroed at 0xf74) */
    void *insect_table_28[0x40];/* 0x28..0x6b (length 26 from the 0xf88 loop) */
    uint8_t reserved_remainder[0x1000]; /* struct extends well past +0x1000 */
};

/* CRO 0x318..0x33c. 1-register (just lr) leaf helper. */
/* CRO 0x364..0x4c8. 11-register + VFP (d8) helper. */
/* CRO 0x4e4..0x59c. 6-register helper. */
/* CRO 0x5a4..0x8d0. 11-register + VFP (d8) helper. */
/* CRO 0x8ec..0x9d4/0x9fc. 7-register helper with two return paths. */
/* CRO 0xa04..0xb44/0xb50. 4-register helper with two return paths. */
/* CRO 0xb60..0xbf4. 2-register + VFP (d8) helper. */
/* CRO 0xbfc..0xc44. 2-register helper. */
/* CRO 0xc48..0xf28/0xf34/0xf40. 11-register + VFP (d8) helper with three
 *   return paths. */
static int us_gym_insect_update(USGymInsectProc *self);

/* CRO 0xf4c..0x1004. 7-register constructor (push {r3,r4,r5,r6,r7,lr}).
 *   Hosts the exported `nnroControlObject_` symbol at 0xf70; the loader
 *   entry is therefore a mid-function offset (`str r6, [r0, #32]`,
 *   zeroing child6 during init). */
static void *us_gym_insect_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x1014..0x1054. 2-register helper. */
/* CRO 0x1068..0x10b8. 2-register helper. */
/* CRO 0x10f8..0x1158. 2-register helper. */