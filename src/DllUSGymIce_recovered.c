/*
 * Preliminary decompilation of DllUSGymIce.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x1820 (mid-function
 *     instruction `mov r2, #8` inside the 0x176c..0x1844 frame).
 *   - import table: 19 anonymous slots from |static|, 12 from DllField
 *   - 17 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the VFP d8-only helpers (0x1146 and 0x11fc) and
 *     the two near-duplicate 4-register helpers (0x12ec, 0x1474)
 *
 * Note on name: this is the Ice-type gym scene (Snowpoint City's
 * Candice in X/Y); uses VFP d8 and d8-d9 for the 3D gym geometry.
 */

#include <stdint.h>

typedef struct USGymIceProc USGymIceProc;

/* Offsets inferred from `[r4, #N]` accesses across the
 * 0x288, 0x354, 0x48c, 0x176c frames. */
struct USGymIceProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c */
    uint8_t reserved10[0x14];
    void *subobj_24[9];     /* 0x24..0x48 */
    void *anim_table_48[18]; /* 0x48..0x90 */
    uint8_t reserved90[0x04];
    uint32_t byte_94;
    uint8_t reserved98[0x1000]; /* struct extends well past +0x1000 */
};

/* CRO 0x288..0x350. 6-register helper. */
/* CRO 0x354..0x480. 11-register + VFP (d8) helper (with tail-call pop). */
/* CRO 0x48c..0x1090. 11-register + VFP (d8-d9) main update. */
static int us_gym_ice_update(USGymIceProc *self);

/* CRO 0x1094..0x11c4/0x11e0. 3-register + VFP (d8) helper with two
 *   return paths. */
/* CRO 0x11fc..0x1270. 2-register + VFP (d8) helper. */
/* CRO 0x127c..0x12d4. 4-register helper. */
/* CRO 0x12ec..0x1428. 2-register + VFP (d8-d9) helper. */
/* CRO 0x1474..0x14c0. 2-register helper. */
/* CRO 0x14c8..0x151c. 2-register helper. */
/* CRO 0x1568..0x1660. 5-register helper. */
/* CRO 0x1664..0x1744. 4-register helper. */
/* CRO 0x176c..0x1844. 4-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x1820; the loader
 *   entry is therefore a mid-function offset (`mov r2, #8`, an argument
 *   setup for a sub-call). */
static void *us_gym_ice_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x185c..0x18d4. 2-register helper. */