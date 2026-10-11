/*
 * Preliminary decompilation of DllUSBigFourFire.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x1780 (mid-function
 *     instruction inside the 0x1600..0x171c frame; the surrounding code
 *     is a memset-like loop with `mov r3, #9; mov r2, #0x94`).
 *   - import table: 44 anonymous slots from |static|, 18 from DllField
 *   - 14 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses (the
 *     owning struct spans at least +0xc00+0x2ec+0x94)
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the +0x420, +0xc00+0x2ec (=+0xeec) and
 *     +0xff0-ish sub-tables (fire VFX / particle data?)
 */

#include <stdint.h>

typedef struct BigFourFireProc BigFourFireProc;

/* Offsets inferred from `[r4, #N]` / `[r5, #N]` accesses across the
 * 0x3cc, 0x4a4, 0x1600 frames. */
struct BigFourFireProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c */
    uint8_t reserved10[0x10]; /* 0x10..0x1f */
    void *script_ctx;       /* 0x1c */
    void *subobj_24[9];     /* 0x24..0x48 */
    void *anim_table_48[18]; /* 0x48..0x90 */
    void *reserved90[0x04];
    uint32_t byte_94;       /* 0x94 (zeroed at 0x3a0 style code) */
    uint8_t reserved98[0xff8]; /* 0x98..0xfef */
    void *fire_vfx_eec[9];   /* 0xeec..0xf0f (initialized 0x1770..0x1780) */
    uint8_t reserved_remainder[0x110];
};

/* CRO 0x354. 4-register "run x4 vtable slots" helper. Mirrors Dragon. */
static int big4_fire_run_x4(BigFourFireProc *self);

/* CRO 0x3cc. 6-register reset helper. Clears subobj_24[0..9] then
 *   anim_table_48[0..18], then three fire sub-tables at offsets
 *   +0xef4/+0xff0/+0x1100 (8 entries each). */
static int big4_fire_reset(BigFourFireProc *self);

/* CRO 0x4a4..0xf50. 11-register + VFP (vpush d8-d9) main update. */
static int big4_fire_update(BigFourFireProc *self);

/* CRO 0xf7c..0xfe0. 4-register + VFP (d8-d9) helper. */
/* CRO 0xfec..0x1064. 4-register + VFP (d8) helper. */
/* CRO 0x1074..0x1118. 3-register + VFP (d8) helper. */
/* CRO 0x1130..0x1178. 4-register helper. */
/* CRO 0x117c..0x11b8. 4-register helper. */
/* CRO 0x1208..0x14d4. 8-register + VFP (d8) helper. */
/* CRO 0x14e4..0x15d8. 6-register helper. */
/* CRO 0x1600..0x171c. 5-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x1780; the loader
 *   entry is therefore a mid-function offset, not a function entry. */
static void *big4_fire_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x173c..0x17ec. 2-register helper. */
/* CRO 0x1808..0x18bc. 2-register helper. */
/* CRO 0x1908..0x1968. 2-register helper. */