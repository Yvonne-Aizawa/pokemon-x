/*
 * Preliminary decompilation of DllDendouDemo.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 1 named symbol `nnroControlObject_` at 0x39b8
 *   - import table: 202 anonymous entries from |static| at 0x5a5c
 *   - ~41 function boundaries identified by ARM push/pop prologues
 *   - ~209 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *   - Heavy VFP usage confirmed (vmov.f32 / vstmia / vldr.f32)
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export trick at 0x39b8 (mid-function vfp-offset)
 *
 * Module summary: Hall of Fame record/playback demo (post-game demo
 * recording viewer).
 */

#include <stdint.h>

typedef struct DendouDemoProc DendouDemoProc;

/* Inferred from repeated [r4, #N] / [r5, #N] accesses across the state
 * machine and constructors. */
struct DendouDemoProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 */
    void *field_1c;        /* 0x1c */
    uint8_t state;         /* 0x24 (signed - accessed via ldrsb) */
    uint8_t sub_state;     /* 0x25 */
    uint16_t parameter;    /* 0x26 */
    int32_t timer;         /* 0x28 */
    uint8_t reserved2c[0x2c]; /* 0x2c..0x57 */
    void *field_58;        /* 0x58 */
    void *field_5c;        /* 0x5c */
    void *field_74;        /* 0x74 (vtable + 0x44, set by ctor) */
    void *field_7c;        /* 0x7c */
};

/* CRO 0x798..0x7b4. Two-register leaf: bl thunk 0x198 with r0=self->field_04,
 * r1=0; writes 1 to self->state (+0x24). */
static void dendou_demo_advance_state(DendouDemoProc *self);

/* CRO 0x7b4..0x9c0. Five-register constructor (push {r4-r7,lr}). */
/* CRO 0x9c0..0xc24. Seven-register + dummy frame constructor (push
 * {r3,r4-r9,lr}). Reads self->state, calls multiple thunks. */
/* CRO 0xc24..0x113c. Ten-register constructor (push {r4-r10,fp,lr}).
 *   Reads self->field_10, allocates 0x80-byte child object via thunk 0x1a0;
 *   attaches via thunks 0x1a8..0x1d8 sequence; populates vtable-derived
 *   +0x44 offset into self->field_74. */
/* CRO 0x113c..0x1330. Five-register + dummy frame helper. */
/* CRO 0x1330..0x144c. Three-register helper. */
/* CRO 0x144c..0x1468. Two-register helper. */
/* CRO 0x1468..0x15bc. Ten-register + ip helper (push {r4-r10,fp,ip,lr}). */
/* CRO 0x15bc..0x1774. Three-register helper. */
/* CRO 0x1774..0x18d0. Six-register helper. */
/* CRO 0x18d0..0x19d8. Five-register helper. */
/* CRO 0x19d8..0x1a6c. Five-register helper. */
/* CRO 0x1a6c..0x1be0. Ten-register + ip helper. */
/* CRO 0x1be0..0x1cc8. Four-register helper. */
/* CRO 0x1cc8..0x1d9c. Seven-register helper. */
/* CRO 0x1d9c..0x20b8. Four-register helper. */
/* CRO 0x20b8..0x2254. Three-register helper. */
/* CRO 0x2254..0x22cc. Four-register + dummy frame helper. */
/* CRO 0x22cc..0x2378. Three-register helper. */
/* CRO 0x2378..0x24dc. Four-register helper. */
/* CRO 0x24dc..0x25e8. Five-register helper. */
/* CRO 0x25e8..0x275c. Four-register helper. */
/* CRO 0x275c..0x286c. Four-register helper. */
/* CRO 0x286c..0x2ae0. Ten-register + fp helper (push {r4-r10,fp,lr}). */
/* CRO 0x2ae0..0x2e80. Seven-register helper. */
/* CRO 0x2e80..0x3040. Ten-register + fp helper. */
/* CRO 0x3040..0x3208. Three-register helper. */
/* CRO 0x3208..0x3454. Five-register helper. */
/* CRO 0x3454..0x34e0. Two-register helper. */
/* CRO 0x34e0..0x3534. Two-register helper. */
/* CRO 0x3534..0x35ac. Five-register + dummy frame helper. */
/* CRO 0x35ac..0x3614. Two-register helper. */
/* CRO 0x3614..0x367c. Two-register helper. */
/* CRO 0x367c..0x3780. Three-register helper. */
/* CRO 0x3780..0x3890. Three-register helper. */
/* CRO 0x3890..0x38c8. Two-register helper. */
/* CRO 0x38c8..0x3904. Two-register helper. */
/* CRO 0x3904..0x393c. Two-register helper. */
/* CRO 0x393c..0x3978. Two-register helper. */
/* CRO 0x3978..0x3b40. Two-register helper. */

/* --- nnroControlObject_ entry --- */

/* CRO 0x3994..0x3b40. Vector initialiser with VFP constants.
 *   - The exported symbol `nnroControlObject_` lands at 0x39b8 which is
 *     `vldr s17, [pc, #344]@0x3b18` -- the symbol is therefore a mid-function
 *     offset inside this vfp constant-loading frame; the frame likely
 *     bootstraps a default 4x3 transform table at runtime. */
static void *dendou_demo_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}