/*
 * Preliminary decompilation of DllUSGymFighting.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x1088 (mid-function
 *     instruction `bl 0x258` inside the 0x102c..0x10e8 frame).
 *   - import table: 22 anonymous slots from |static|, 13 from DllField
 *   - 17 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *     (offsets +0x18, +0x0c, +0x170 and the +0x34/+0x84 sub-tables show
 *     up across multiple frames)
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the two 7-entry reset loops in 0x102c and 0x10f8
 *     (they are nearly identical, differing only in the vtable pointer
 *     constant loaded from the embedded pool at 0x10ec/0x11b4)
 *
 * Note on name: this is the Fighting-type gym scene (Shalour City's
 * Korrina in X/Y); uses VFP d8 for the 3D camera math.
 */

#include <stdint.h>

typedef struct USGymFightingProc USGymFightingProc;

/* Offsets inferred from `[r6, #N]` accesses across the
 * 0x298, 0x410, 0x4c8, 0x59c, 0xd68, 0x102c frames. */
struct USGymFightingProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c (released in 0x102c if non-NULL) */
    uint8_t reserved10[0x14];
    void *subobj_24[7];     /* 0x18..0x34 (loop counter 0..7) */
    void *anim_table_48[18]; /* 0x48..0x90 (seen in update frames) */
    uint8_t reserved90[0x04];
    uint32_t byte_94;
    uint8_t reserved98[0xf48]; /* 0x98..0xfdf */
    void *fighting_table_160[5]; /* 0x160..0x174 (loop 0x10a4..0x10b4) */
    void *fighting_table_34[5];  /* 0x34..0x48 (loop 0x10d0..0x10dc) */
};

/* CRO 0x298..0x3c8. 6-register helper. */
/* CRO 0x410..0x4bc. 6-register + VFP (d8) helper. */
/* CRO 0x4c8..0x584/0x594. 6-register + VFP (d8) helper. */
/* CRO 0x59c..0xd58. 11-register + VFP (d8-d9) main update. */
static int us_gym_fighting_update(USGymFightingProc *self);

/* CRO 0xd68..0xdb0. 2-register helper. */
/* CRO 0xdb8..0xdd8. 2-register helper. */
/* CRO 0xddc..0xe68. 7-register + VFP (d8) helper. */
/* CRO 0xe70..0xf54/0xf5c. 4-register helper with two return paths. */
/* CRO 0xf60..0x1018. 4-register helper. */
/* CRO 0x102c..0x10e8. 6-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x1088; the loader
 *   entry is therefore a mid-function offset (`bl 0x258`, a call into
 *   the imported lookup-by-key helper). */
static void *us_gym_fighting_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x10f8..0x11b0. 6-register constructor (twin of 0x102c). */
/* CRO 0x1210..0x1270. 2-register helper. */