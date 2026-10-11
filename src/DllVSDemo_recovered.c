/*
 * Preliminary decompilation of DllVSDemo.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 1 named symbol `nnroControlObject_` at 0x2a3c
 *   - import table: 91 anonymous entries from |static| at 0x453c
 *   - ~49 function boundaries identified by ARM push/pop prologues
 *   - ~100 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *   - identified the lifecycle stubs, the primary state-update function
 *     and the vtable-bound constructor / destructor pair
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export trick at 0x2a3c (mid-function offset)
 */

#include <stdint.h>

typedef struct VSDemoProc VSDemoProc;

/* Confirmed from field accesses in the original ARM code.
 * The constructor at 0x4d8 writes the vtable at +0x00, the
 * vtable-derived +0x44 at +0x74, and 0 at +0x7c; the worker at
 * 0x414 reads +0x24/+0x25/+0x28. */
struct VSDemoProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c (used as a 12-byte parameter block) */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 */
    void *field_1c;        /* 0x1c */
    void *field_20;        /* 0x20 */
    int8_t state;          /* 0x24 (ldrsb: signed dispatch) */
    uint8_t sub_state;     /* 0x25 */
    uint16_t parameter;    /* 0x26 */
    int32_t timer;         /* 0x28 */
    uint8_t reserved2c[0x2c]; /* 0x2c..0x57 */
    void *field_58;        /* 0x58 (write target in 0x618) */
    void *field_5c;        /* 0x5c (read in 0x29c4) */
    uint8_t reserved60[0x14]; /* 0x60..0x73 */
    void *field_74;        /* 0x74 (vtable + 0x44, set by 0x4d8) */
    void *field_78;        /* 0x78 */
    void *field_7c;        /* 0x7c (cleared to 0 by 0x4d8; read in 0x2a20) */
};

/* --- Lifecycle stubs (3 + 4 alternates at 0x3e0..0x410) --- */

/* CRO 0x3e0 */
static int vs_demo_can_run(void) { return 1; }
/* CRO 0x3e8 */
static int vs_demo_can_stop(void) { return 1; }
/* CRO 0x3f0 */
static int vs_demo_can_draw(void) { return 1; }
/* CRO 0x3f8 */
static int vs_demo_can_run_alt(void) { return 1; }
/* CRO 0x400 */
static int vs_demo_can_yes(void) { return 1; }
/* CRO 0x408 */
static void vs_demo_noop_a(void) {}
/* CRO 0x40c */
static void vs_demo_noop_b(void) {}
/* CRO 0x410 */
static void vs_demo_noop_c(void) {}

/* --- Primary state-machine update. --- */

/* CRO 0x414..0x4b4. Three-register + r5-r6 spilled state machine.
 *   - calls thunks 0x180, 0x188 (then 0x180, 0x190) to check readiness;
 *     accumulates r5 = (any-non-zero ? 1 : 0)
 *   - reads self->state (+0x24, signed) and self->sub_state (+0x25)
 *   - if state == 0 and r5 == 0: returns 2 (idle)
 *   - if sub_state != 0 OR r5 != 0: writes r5 to self->timer[0] (+0x28),
 *     then tail-calls thunk 0x19cc (lifecycle dispatcher) and returns 3
 *   - otherwise clears sub_state (+0x25 = 0), reads [self->timer][1],
 *     dispatches on (==1 OR ==3) into branch 0x480: clears state, calls
 *     thunk 0x18f4 then 0x19cc and returns 1
 */
static int vs_demo_update(VSDemoProc *self) {
    int ready = 0;
    /* TODO: not yet decoded */
    return ready ? 1 : 2;
}

/* --- Helper stubs. --- */

/* CRO 0x4b8. Two-register leaf: bl thunk 0x198 with r0=self->field_04,
 * r1=0; writes 1 to self->state (+0x24). */
static void vs_demo_advance_state(VSDemoProc *self);

/* CRO 0x4d8..0x594. Eight-register constructor (push {r4-r9,sl,lr}).
 *   - reads self->field_10, calls thunk 0x1a0 with r0=0x80 (likely
 *     allocating a 0x80-byte child object) -- r0 holds the result
 *   - on NULL return, branches to 0x594 (failure path)
 *   - calls thunk 0x1a8 with r1=&self->field_0c, r2=0, r3=0 (attach?)
 *   - stores the result in r4, loads vtable-relative constant via
 *     [pc, #248]@0x610 into r0, computes r2 = r4+0x74 (vtable slot),
 *     r1 = r0 + 0x44
 *   - writes r0 into r4->vtable, stm r4+0x74 = {r1=0x44-offset, r7=0},
 *     writes 0 into r4->field_7c
 *   - calls thunk 0x1b0 with r1 = [self->field_10+8], r0 = [self->field_10+4]
 *     (the two fields of the parameter area)
 *   - calls thunk 0x1b8 with r0=r4, r1=&self->field_0c, r2=1
 *   - sets up lr = sp+0x14, r8 = sp+0x18, then thunk 0x230..0x268 sequence
 *     populating the child fields. */
static VSDemoProc *vs_demo_construct(VSDemoProc *self);

/* CRO 0x618. Three-register leaf: bl thunk 0x180 then 0x1a0; writes r5
 * to [r0 + 0x58]. */
/* CRO 0x6fc. Four-register helper (push {r4-r7,lr}). */
/* CRO 0x7e4..0x96c. Five-register large body with dummy-frame (push
 * {r3,r4-r7,lr}); dispatches on self->state, calls thunks 0x198..0x1c8. */
/* CRO 0x96c. Three-register thunk caller. */
/* CRO 0xa04. Three-register + VFP (vpush {d8}). */
/* CRO 0xa98..0xd2c. Ten-register + VFP (vpush d8-d9) draw routine. */

/* --- nnroControlObject_ entry. --- */

/* CRO 0x29c4..0x29f0. Four-register loader vtable initializer.
 *   - calls thunk 0x3a0 (returns r5), then thunk 0x3a8 with r0=self->field_5c
 *   - loads [pc, #16]@0x29f4 into r0 (a flag pointer)
 *   - calls thunk 0x3b0 with r0=r5, r1=[r0], r2=1 (likely "flag set").
 */

/* CRO 0x2a14..0x2a3c. Two-register release helper.
 *   - calls thunk 0x3b8
 *   - reads self->field_7c into r0; if non-zero, dispatches vtable[0x38] (+0x38)
 *     and tail-calls the result
 *   - The exported symbol `nnroControlObject_` lands at 0x2a3c which is the
 *     `pop {r4, pc}` inside this 0x2a14 frame -- the export therefore
 *     re-enters at the cleanup-pop tail. The frame preceding it (0x2a14)
 *     is the surrounding "release vtable + cleanup" wrapper. */
static void *vs_demo_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}

/* CRO 0x2a44..0x2a78. Two-register constructor variant A:
 *   loads [pc, #48]@0x2a78 into r1 (vtable ptr), writes r1 to self->vtable
 *   and r1+0x44 to self->field_74; calls thunks 0x3c0/0x3c8/0x3d0 then b 0x1f8
 *   (the actual ctor entry). */
/* CRO 0x2a7c..0x2ab4. Two-register constructor variant B:
 *   loads [pc, #40]@0x2ab4 into r0 (vtable ptr), writes r0 to self->vtable
 *   and r0+0x44 to self->field_74; tail-calls 0x3c0/0x3c8/0x3d0 then b 0x3d8. */
/* CRO 0x2abc..0x2af0. Two-register destructor:
 *   loads [pc, #36]@0x2af0 into r1 (vtable ptr), writes r1 to self->vtable;
 *   reads self->field_14 into r0; if non-zero calls thunk 0x398 and
 *   clears self->field_14; tail-calls 0x1f8. */
/* CRO 0x2af4..0x2b24. Two-register destructor alt:
 *   same pattern as 0x2abc but with a different [pc,#28]@0x2b24 vtable. */
/* CRO 0x2b28..0x2b8c. Four two-instruction tail-call helpers:
 *   thunk-call if self->field_08 (or field_74 in 0x2b30) != 0; else return 1
 *   via bx lr. These are the vtable dispatcher slots (vtable +0x00/+0x08/+0x18). */
/* CRO 0x2b90..0x2bb8. nnro_bss_init:
 *   writes 0xFFFFFFFF to [pc,#28]@0x2bb4 + 8/+8 (two error counters),
 *   then writes 0/0 to [pc,#16]@0x2bb8 + 0/+4 (two flag slots). */
/* CRO 0x2bc4..0x2c40. nnro_loader_dispatch:
 *   push {r4,lr}; cmp r1, #5; ldrcc pc, [pc, r1, lsl #2]; (switch table 0..5)
 *   The dispatcher uses 5 slots: cases 0/1/2/3/4 call thunks 0x2be4/0x2bec/
 *   0x2bf4/0x2c08/0x2c18, default branches to 0x2c28. */