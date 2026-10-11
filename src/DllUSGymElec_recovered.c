/*
 * Preliminary decompilation of DllUSGymElec.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x16e0 (mid-function
 *     instruction `add r0, r0, #24` inside the 0x16cc..0x1748 frame;
 *     the surrounding body sets up a 24-byte sub-object at offset +0x18).
 *   - import table: 21 anonymous slots from |static|, 9 from DllField
 *   - ~17 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the many short 2-register helpers
 *
 * Note on name: this is the Electric-type gym scene (Lumiose City's
 * Clemont in X/Y); the gym battle uses VFP for the 3D gym geometry.
 */

#include <stdint.h>

typedef struct USGymElecProc USGymElecProc;

/* Offsets inferred from `[r4, #N]` accesses across the
 * 0x324, 0x430, 0xaf0, 0x16cc frames. */
struct USGymElecProc {
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

/* CRO 0x2b8. 2-register leaf helper. */
/* CRO 0x324..0x414. 5-register + VFP (d8) helper. */
/* CRO 0x430..0x964. 11-register + VFP (d8-d9) main update. */
static int us_gym_elec_update(USGymElecProc *self);

/* CRO 0x970..0x990. 2-register helper. */
/* CRO 0x994..0x9b4. 2-register helper. */
/* CRO 0x9b8..0xa28/0xa38. 3-register helper with two return paths. */
/* CRO 0xa48..0xa9c. 2-register helper. */
/* CRO 0xaa8..0xac8. 2-register helper. */
/* CRO 0xacc..0xaec. 2-register helper. */
/* CRO 0xaf0..0xbec. 8-register + VFP (d8) helper. */
/* CRO 0xc00..0xc20. 2-register helper. */
/* CRO 0xc24..0xc78. 2-register helper. */
/* CRO 0xc84..0xce8. 2-register + VFP (d8) helper. */
/* CRO 0xd00..0xde8/0xdf0. 4-register helper with two return paths. */
/* CRO 0xdf4..0xf1c. 4-register helper. */
/* CRO 0x1498..0x14f0. 2-register helper. */
/* CRO 0x14fc..0x1624. 4-register + VFP (d8) helper. */
/* CRO 0x1630..0x1650. 2-register helper. */
/* CRO 0x1654..0x16c0. 2-register helper. */
/* CRO 0x16cc..0x1748. 4-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x16e0; the loader
 *   entry is therefore a mid-function offset (`add r0, r0, #24`,
 *   computing a sub-object base). */
static void *us_gym_elec_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x1754..0x17b8. 2-register helper. */
/* CRO 0x17c8..0x182c. 2-register helper. */
/* CRO 0x1868..0x18c8. 2-register helper. */