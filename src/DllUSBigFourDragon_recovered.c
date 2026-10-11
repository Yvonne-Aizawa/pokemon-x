/*
 * Preliminary decompilation of DllUSBigFourDragon.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x16e4 (mid-function
 *     instruction `bl 0x2c0` inside the 0x1520..0x1664 frame).
 *   - import table: 33 anonymous slots from |static|, 17 from DllField
 *   - 14 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses (the
 *     owning struct is large: see offsets up to +0x10ec)
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the +0x48, +0xc00+0x2f4 (+0xef4), +0xff0,
 *     +0x1000+0xec (+0x10ec) sub-tables (3D camera / dragon anim data?)
 */

#include <stdint.h>

typedef struct BigFourDragonProc BigFourDragonProc;

/* Offsets inferred from `[r4, #N]` / `[r5, #N]` accesses across the
 * 0x380, 0x47c, 0x1520 frames. The full struct spans at least 0x1100
 * bytes (the +0x10ec access appears inside 0x1520). */
struct BigFourDragonProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 (passed to bl 0x180 RNG) */
    void *child[3];         /* 0x0c (pointer; bl 0x190/0x198 in 0x458) */
    void *script_ctx;       /* 0x1c (used as r1 at 0x49c) */
    void *subobj_24[9];     /* 0x24..0x48 (9 pointer table, loop at 0x3a4..0x3cc) */
    void *anim_table_48[18]; /* 0x48..0x90 (18 entries, loop 0x3d4..0x3ec) */
    void *reserved90[0x40]; /* 0x90..0xcf */
    uint32_t byte_94;       /* 0x94 (zeroed at 0x3a0) */
    uint8_t reserved98[0xff8]; /* 0x98..0xfef */
    void *dragon_anim_ff0[8]; /* 0xff0..0x100f (loop 0x418..0x430) */
    void *dragon_sub_10ec[8]; /* 0x10ec..0x110b (loop 0x438..0x454) */
};

/* CRO 0x308. 4-register "run x4 vtable slots" helper.
 *   if self->field_10 == 4: loop 4 times calling self->vtable[0x38]/[0x3c]/
 *   [0x40] with self and a counter. Else: fall through and return. */
static int big4_dragon_run_x4(BigFourDragonProc *self);

/* CRO 0x380. 6-register reset helper. Wipes subobj_24[0..9] (calls each
 *   vtable[1] / virtual dtor), then clears anim_table_48[0..18] and the
 *   three dragon sub-tables (offsets +0xef4, +0xff0, +0x10ec; 8 entries
 *   each). Calls imported 0x190 then 0x198 on self->child (+0x0c). */
static int big4_dragon_reset(BigFourDragonProc *self);

/* CRO 0x47c..0xf68. 11-register + VFP (vpush d8) main update.
 *   Sub_sp is 0x3c (large local frame). Uses imported services at 0x180,
 *   0x188, 0x190, 0x198, 0x1a0, 0x1a8, 0x1b0, 0x1b8, 0x1c0, 0x1c8, 0x1d0,
 *   0x1d8, 0x1e0, 0x1e8, 0x1f0, 0x1f8. */
static int big4_dragon_update(BigFourDragonProc *self);

/* CRO 0xf7c..0xff4. 4-register + VFP helper. */
/* CRO 0x1004..0x10a8. 3-register + VFP helper. */
/* CRO 0x10c0..0x1108. 4-register helper. */
/* CRO 0x110c..0x1148. 4-register helper. */
/* CRO 0x1198..0x13ec. 8-register + VFP helper. */
/* CRO 0x1400..0x14f8. 6-register helper. */
/* CRO 0x1520..0x1664. 5-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x16e4; the
 *   loader entry is therefore the `bl 0x2c0` (slot 22) call inside
 *   this frame. */
static void *big4_dragon_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x1680..0x1744. 2-register helper. */
/* CRO 0x175c..0x1824. 2-register helper. */
/* CRO 0x186c..0x18cc. 2-register helper. */