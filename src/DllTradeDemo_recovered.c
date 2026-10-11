/*
 * Preliminary decompilation of DllTradeDemo.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet.
 *
 * Recovered:
 *   - export table: `nnroControlObject_` at 0x1924 plus a C++ mangled
 *     symbol `_ZN9xy_system2bg6System13SetIsCallDrawEb` at 0x18e8 (mid-
 *     function offset inside the 0x15b4..0x18f0 setup).
 *   - import table: 121 anonymous slots from |static|, 11 from DllSequence
 *   - ~17 function boundaries identified by ARM push/pop prologues
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout for xy_system::bg::System
 *   - the meaning of the imported relocation slots
 *   - any constants (the only embedded constants in this module are PC-
 *     relative floats at 0x738/0x73c which feed VFP math)
 */

#include <stdint.h>

typedef struct TradeDemoProc TradeDemoProc;
typedef struct TradeDemoChild TradeDemoChild;

/* Confirmed via repeated [r4, #N] accesses in the 0x56c and 0x6bc frames.
 * Size is at least 0x34; the 0x15b4 frame extends well beyond. */
struct TradeDemoProc {
    void *vtable;          /* 0x00 */
    void *field_04;
    void *field_08;
    void *field_0c;
    void *field_10;
    uint8_t reserved14[0x04]; /* 0x14..0x17 */
    void *field_18;
    void *field_1c;
    void *field_20;
    uint8_t reserved24[0x14]; /* 0x24..0x37 */
    uint8_t byte_38;        /* 0x38 (compared to 1 in 0x644) */
};

/* CRO 0x550. 2-register helper.
 *   bl import[0] (0x180); if non-zero return self->field_14, else return 3.
 */
static int trade_demo_query_flag(TradeDemoProc *self) {
    /* The original is: bl 0x180; cmp r0, #0; ldrne r0, [r4, #0x14];
     *                   moveq r0, #3; pop {r4, pc}. */
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x56c. 3-register constructor.
 *   - calls imported 0x188 (heap alloc) to set up self->field_1c
 *   - calls imported 0x190 (lookup-by-key) twice with keys 8 and 20 to
 *     populate self->field_18 and a local object
 *   - if that local object is non-null, fills it via imported 0x198, 0x1a0,
 *     0x1a8, 0x1b0 (slot indices 0..16)
 *   - calls imported 0x190 again with key 80 to obtain another object, then
 *     calls internal 0x15b4 with (self, &self->field_1c, self->vtable)
 */
static int trade_demo_construct(TradeDemoProc *self);

/* CRO 0x644. Leaf helper (4 instructions):
 *   ldr r1, [r0, #0x18]; ldr r1, [r1]; ldrb r1, [r1, #0x38];
 *   cmp r1, #1; moveq r1, #5; streq r1, [r0, #0x10]; moveq r0, #2;
 *   movne r0, #4; bx lr.
 * Selects a return code based on child->byte_38. */
static int trade_demo_poll_child_state(TradeDemoProc *self) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x668. Cleanup helper.
 *   if self->field_18->field_00 != NULL: bl internal 0x1004; bl import[14] (0x1b8)
 *   if self->field_18->field_04 != NULL: bl import[14] (0x1b8)
 *   bl import[14] (0x1b8) on self->field_18
 *   self->field_18 = NULL; bl import[15] (0x1c0) on &self->field_1c
 *   return self->field_10
 */
static void *trade_demo_shutdown(TradeDemoProc *self);

/* CRO 0x6bc. 3-register state transition.
 *   - calls imported 0x1c8 with self->field_18->field_00->field_18
 *   - on success, calls imported 0x1d0 then sets up VFP s0/s1 constants
 *     (0x3f800000 / 0x3f800000) and calls imported 0x1d8 (3-arg),
 *     then imported 0x1e0 (2-arg). */
static int trade_demo_update(TradeDemoProc *self);

/* CRO 0x740..0x808. 4-register helper. */
/* CRO 0x818..0x9e0. 11-register helper. */
/* CRO 0xc04..0xe08. 6-register helper. */
/* CRO 0xe10..0xff8. 8-register helper. */
/* CRO 0x1004..0x116c. 4-register helper. */
/* CRO 0x1170..0x1280. 7-register helper. */
/* CRO 0x1288..0x1388. 5-register helper (push {r3,r4,r5,r6,r7,lr}). */
/* CRO 0x13ec..0x1594. 4-register helper. */
/* CRO 0x15b4..0x18f0. 7-register constructor.
 *   Hosts the exported C++ symbol `_ZN9xy_system2bg6System13SetIsCallDrawEb`
 *   at 0x18e8 (`str r0, [r4, #0x24]`); the symbol is therefore a body
 *   offset, not a function entry. */

/* CRO 0x18f4..0x1924. 7-register tail (the export `nnroControlObject_` lands
 * at 0x1924, the `bl 0x1b8` cleanup call). The surrounding frame is the
 * real control-object cleanup; the loader calls into it at the offset of
 * that cleanup. */
static void *trade_demo_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}