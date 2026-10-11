/*
 * Preliminary decompilation of DllUSGymEsper.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x16fc. The export lands
 *     directly on a `push {r4,r5,r6,r7,lr}` prologue, so for once the
 *     nnroControlObject_ really is a function entry (unlike the rest of
 *     the 12-module batch).
 *   - import table: 32 anonymous slots from |static|, 21 from DllField
 *   - ~17 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the many short helpers and the two VFP-using
 *     sub-routines (one at 0x5f8 saves/restores d8 only, one at 0xde0
 *     uses d8-d9 and ends with an `lr`-restoring pop, suggesting a
 *     tail-call continuation rather than a true return)
 *
 * Note on name: this is the Psychic-type gym scene (Lumiose City's
 * Olympia in X/Y); Esper is the local codename for the Psychic type.
 */

#include <stdint.h>

typedef struct USGymEsperProc USGymEsperProc;

/* Offsets inferred from `[r4, #N]` accesses across the
 * 0x33c, 0x498, 0x5f8, 0x11f4, 0x16fc frames. */
struct USGymEsperProc {
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

/* CRO 0x33c. 3-register helper. */
/* CRO 0x498..0x52c. 6-register helper. */
/* CRO 0x530..0x5f0. 3-register helper. */
/* CRO 0x5f8..0xad0. 6-register + VFP (d8) main update. */
static int us_gym_esper_update(USGymEsperProc *self);

/* CRO 0xaf0..0xc9c. 4-register + VFP (d8) helper. */
/* CRO 0xc9c..0xdd0. 4-register + VFP (d8) helper (re-uses the same
 *   vpop/vpush pattern, possibly a sibling helper). */
/* CRO 0xde0..0xe80. 6-register + VFP (d8-d9) helper with tail-call pop. */
/* CRO 0xebc..0xf48. 6-register + VFP (d8) helper with tail-call pop. */
/* CRO 0xf54..0x11e0. 4-register helper. */
/* CRO 0x11f4..0x1424/0x1458. 11-register + VFP (d8) helper with two
 *   return paths. */
/* CRO 0x1464..0x1518. 2-register + VFP (d8-d9) helper. */
/* CRO 0x1534..0x15d4. 4-register + VFP (d8) helper. */
/* CRO 0x15d4..0x15ec. 4-register + VFP (d8) helper (tail pop. branch). */
/* CRO 0x15f4..0x16dc. 4-register helper. */

/* CRO 0x16fc..0x17d8. 5-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x16fc — for this
 *   module the export is a real function entry (prologue). */
static void *us_gym_esper_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x17ec..0x180c. 2-register helper. */