/*
 * Preliminary decompilation of DllUSBigFourWater.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: only `nnroControlObject_` at 0x1188 (mid-function
 *     instruction `add r0, r0, #0x18c` inside the 0x1130..0x11fc frame).
 *   - import table: 42 anonymous slots from |static|, 17 from DllField
 *   - 12 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses (the
 *     owning struct spans at least +0x4f8+0x4 = +0x4fc; a 0x18c base
 *     and a 0x2e4 base suggest two distinct sub-objects)
 *
 * Not recovered:
 *   - the vtable layout for any imported service
 *   - the meaning of the imported relocation slots
 *   - the precise role of the +0x18c, +0x2e4 sub-tables (water anim data?)
 */

#include <stdint.h>

typedef struct BigFourWaterProc BigFourWaterProc;

/* Offsets inferred from `[r4, #N]` accesses across the
 * 0x3bc, 0x484, 0x1130 frames. */
struct BigFourWaterProc {
    void *vtable;           /* 0x00 */
    void *field_04;
    void *rng_or_state;      /* 0x08 */
    void *child;            /* 0x0c */
    void *child2;           /* 0x10 */
    uint8_t reserved14[0x10];
    void *script_ctx;       /* 0x1c */
    void *subobj_24[9];     /* 0x24..0x48 */
    void *anim_table_48[18]; /* 0x48..0x90 */
    uint8_t reserved90[0x04];
    uint32_t byte_94;
    uint8_t reserved98[0xf48]; /* 0x98..0xfdf */
    void *water_table_18c[5]; /* 0x18c..0x1af (loop 0x117c..0x118c) */
    void *water_table_2e4[1]; /* 0x2e4..0x2e7 (loop 0x1190..0x11a4) */
    void *reserved_remainder[0x10c];
    uint32_t field_4f8;     /* 0x4f8 (set to 1 at 0x11ac) */
    uint8_t byte_4fc;       /* 0x4fc (zeroed at 0x11b0) */
};

/* CRO 0x34c. 4-register helper. */
static int big4_water_run_x4(BigFourWaterProc *self);

/* CRO 0x3bc. 6-register reset helper. */
static int big4_water_reset(BigFourWaterProc *self);

/* CRO 0x484..0xb38. 7-register + VFP (vpush d8) main update. */
static int big4_water_update(BigFourWaterProc *self);

/* CRO 0xc40..0xcb8. 4-register + VFP (d8) helper. */
/* CRO 0xcc8..0xd6c. 3-register + VFP (d8) helper. */
/* CRO 0xd84..0xdcc. 4-register helper. */
/* CRO 0xdd0..0xe0c. 4-register helper. */
/* CRO 0xe5c..0xf5c. 8-register + VFP (d8) helper. */
/* CRO 0xf68..0x1014. 6-register helper. */
/* CRO 0x1018..0x1110. 6-register helper. */
/* CRO 0x1130..0x11fc. 5-register constructor.
 *   Hosts the exported `nnroControlObject_` symbol at 0x1188; the loader
 *   entry is therefore a mid-function offset (an `add r0, r0, #0x18c`
 *   computing a sub-table base for an outer sub-call). */
static void *big4_water_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x1218..0x1260. 2-register helper. */
/* CRO 0x1278..0x12c8. 2-register helper. */
/* CRO 0x1310..0x1370. 2-register helper. */