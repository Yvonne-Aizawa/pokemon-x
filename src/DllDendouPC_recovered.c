/*
 * Preliminary decompilation of DllDendouPC.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 1 named symbol `nnroControlObject_` at 0x3170
 *   - import table: 176 anonymous entries from |static| at 0x5938
 *   - ~42 function boundaries identified by ARM push/pop prologues
 *   - ~185 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export trick at 0x3170 (mid-function vstr)
 *
 * Module summary: Hall of Fame "PC" view (post-game Hall-of-Fame data
 * rendered via a PC-like interface).
 */

#include <stdint.h>

typedef struct DendouPCProc DendouPCProc;

/* Inferred from repeated [r4, #N] / [r5, #N] accesses. */
struct DendouPCProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c (parent pointer, accessed many places) */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 */
    void *field_1c;        /* 0x1c */
    uint8_t state;         /* 0x24 */
    uint8_t sub_state;     /* 0x25 */
    uint16_t parameter;    /* 0x26 */
    int32_t timer;         /* 0x28 */
    uint8_t reserved2c[0x30c]; /* 0x2c..0x337 */
    uint8_t byte_337;      /* 0x337 (write target in nnro region) */
};

/* CRO 0x650..0x66c. Two-register leaf: bl thunk 0x198 with r0=self->field_04,
 * r1=0; writes 1 to self->state. */
/* CRO 0x66c..0x7cc. Five-register constructor (push {r4-r7,lr}). */
/* CRO 0x7cc..0xa3c. Six-register constructor. */
/* CRO 0xa3c..0xc88. Eight-register constructor. */
/* CRO 0xc88..0xdac. Ten-register + fp constructor. */
/* CRO 0xdac..0xe4c. Two-register helper. */
/* CRO 0xe4c..0x10a8. Six-register helper. */
/* CRO 0x10a8..0x1170. Three-register helper. */
/* CRO 0x1170..0x11b0. Two-register helper. */
/* CRO 0x11b0..0x1290. Three-register helper. */
/* CRO 0x1290..0x13a4. Eleven-register + ip + fp helper. */
/* CRO 0x13a4..0x15dc. Four-register helper. */
/* CRO 0x15dc..0x17c4. Five-register helper. */
/* CRO 0x17c4..0x19c4. Ten-register + fp helper. */
/* CRO 0x19c4..0x1a70. Five-register + dummy frame helper. */
/* CRO 0x1a70..0x1b28. Five-register helper. */
/* CRO 0x1b28..0x1be4. Five-register helper. */
/* CRO 0x1be4..0x1cc0. Three-register helper. */
/* CRO 0x1cc0..0x1de0. Six-register helper. */
/* CRO 0x1de0..0x1f68. Five-register + dummy frame helper. */
/* CRO 0x1f68..0x208c. Three-register helper. */
/* CRO 0x208c..0x21b0. Five-register helper. */
/* CRO 0x21b0..0x2480. Six-register helper. */
/* CRO 0x2480..0x27e0. Ten-register + fp helper. */
/* CRO 0x27e0..0x2a18. Seven-register helper. */
/* CRO 0x2a18..0x2b30. Three-register helper. */
/* CRO 0x2b30..0x2c1c. Three-register helper. */
/* CRO 0x2c1c..0x2d54. Three-register helper. */
/* CRO 0x2d54..0x2ddc. Three-register helper. */
/* CRO 0x2ddc..0x2e20. Two-register helper. */
/* CRO 0x2e20..0x2e94. Five-register + dummy frame helper. */
/* CRO 0x2e94..0x2efc. Two-register helper. */
/* CRO 0x2efc..0x2f84. Two-register helper. */
/* CRO 0x2f84..0x2fc0. Two-register helper. */
/* CRO 0x2fc0..0x2fd4. Two-register helper. */
/* CRO 0x2fd4..0x30d8. Three-register helper. */
/* CRO 0x30d8..0x31b4. Three-register helper. */
/* CRO 0x31b4..0x31ec. Two-register helper. */
/* CRO 0x31ec..0x3228. Two-register helper. */
/* CRO 0x3228..0x3260. Two-register helper. */
/* CRO 0x3260..0x32f8. Two-register helper. */
/* CRO 0x32f8..0x3300. Two-register helper (likely nnro tail). */

/* --- nnroControlObject_ entry --- */

/* CRO 0x3150..0x31a0. The exported symbol `nnroControlObject_` lands at
 * 0x3170 which is `vstr s0, [r0, #588]@0x24c` -- the symbol is therefore
 * a mid-function offset inside this frame. The frame sets three VFP
 * registers (s0/s1/s2) to zero-initialised values, writes them to
 * child->field_24c..field_254, then writes r5 (=0) to child->byte_337
 * and dispatches on r4->byte_10 into thunk 0x328 (likely an external
 * state-notify callback). */
static void *dendou_pc_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}

/* CRO 0x31b0..0x31e8. Two-register constructor: loads [pc,#48]@0x31e8 as
 * vtable, stores into self->vtable; calls thunk 0x610 with r0=self->field_14;
 * if non-zero calls thunk 0x618; tail-calls 0x278. */
/* CRO 0x31ec..0x3218. Two-register constructor alt. */