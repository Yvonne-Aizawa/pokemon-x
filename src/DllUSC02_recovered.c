/*
 * Preliminary decompilation of DllUSC02.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x1bbc (mid-function
 *     instruction `str r8, [sp, #0x3c]` inside the 0x1ab0..0x1af8 frame;
 *     the surrounding body is a 12-register prologue with very large
 *     stack frame `sub sp, sp, #0x58`-ish).
 *   - import table: 40 anonymous slots from |static|, 19 from DllField
 *   - ~20 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the many short 2-register helpers
 *     (they look like virtual-call thunks)
 *
 * Note on name: the "C02" suffix matches the Champion Room 2 (or
 * Champion's second encounter) scene; the module has the highest
 * function count of the 12 modules processed here.
 */

#include <stdint.h>

typedef struct USC02Proc USC02Proc;

/* Offsets inferred from `[r4, #N]` accesses across the
 * 0x368, 0x75c, 0x98c, 0xe00, 0x1240, 0x180c frames. */
struct USC02Proc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c */
    uint8_t reserved10[0x14];
    void *subobj_24[9];     /* 0x24..0x48 */
    void *anim_table_48[18]; /* 0x48..0x90 */
    uint8_t reserved90[0x08];
    uint32_t byte_94;
    uint8_t reserved98[0x1000]; /* struct extends at least 0x1100 bytes */
};

/* CRO 0x348. 2-register leaf helper. */
/* CRO 0x368..0x52c. 4-register helper. */
/* CRO 0x538..0x610/0x634. 4-register helper with two return paths. */
/* CRO 0x6a4..0x6c4. 2-register helper. */
/* CRO 0x6d4..0x6fc. 2-register helper. */
/* CRO 0x71c..0x750. 2-register helper. */
/* CRO 0x75c..0x88c. 6-register helper. */
/* CRO 0x8c0..0x8d0. 2-register helper. */
/* CRO 0x8d4..0x948/0x980. 4-register helper. */
/* CRO 0x98c..0xd6c. 8-register helper. */
/* CRO 0xe00..0x1084. 11-register helper. */
/* CRO 0x108c..0x1234. 6-register + VFP (d8-d9) helper. */
/* CRO 0x1240..0x1478. 11-register + VFP (d8) helper. */
/* CRO 0x1488..0x1494. 2-register helper. */
/* CRO 0x149c..0x14a8. 2-register helper. */
/* CRO 0x14b0..0x14bc. 2-register helper. */
/* CRO 0x14c4..0x14d0. 2-register helper. */
/* CRO 0x14d4..0x1594. 6-register helper. */
/* CRO 0x15a8..0x1668. 6-register helper. */
/* CRO 0x167c..0x1690. 2-register helper. */
/* CRO 0x16b0..0x179c. 6-register helper. */
/* CRO 0x17d8..0x17ec. 2-register helper. */
/* CRO 0x180c..0x1aa0. 12-register constructor (push {r4-r12, lr}).
 *   Hosts the exported `nnroControlObject_` symbol at 0x1bbc; the loader
 *   entry is therefore a mid-function offset. */
static void *usc02_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x1ab0..0x1af8. 7-register helper (possibly a sub-constructor). */
/* CRO 0x1d44..0x1da4. 2-register helper. */