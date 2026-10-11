/*
 * Preliminary decompilation of DllSequence.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x1121c,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0xc48.
 *   - 343 ARM prologues detected. Thumb prologues absent (the control object
 *     and SetIsCallDraw thunk look ARM-resident).
 *   - 327 anonymous |static| imports, 457 external patches.
 *   - 4 large hot-patch regions (+0xc..+0x18 imports the sequence manager;
 *     the rest are sequence step functions).
 */

#include <stdint.h>

/* Named exports */
extern void nnroControlObject_(void);             /* CRO 0x1121c */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0xc48  */

/* Forward declarations for the four large named-import users. */
extern void DllSequence_dispatch_step(void *self);      /* CRO ~0x? */
extern void DllSequence_enqueue(void *self, int32_t evt); /* TODO */

/* Static-import function-pointer aliases used by the recovered code below. */
typedef int32_t (*SequenceStepFn)(void *self, int32_t evt);

/* SequenceProc instance layout — most-touched offsets cluster around
 * +0x04, +0x18, +0x24..+0x28, +0x40, +0x80, +0xc0. */
struct SequenceProc {
    void *vtable;              /* 0x00 */
    void *parent;              /* 0x04 */
    void *step_table;          /* 0x08 (handler array) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;             /* 0x24 */
    uint8_t sub_state;         /* 0x25 */
    uint16_t parameter;        /* 0x26 */
    int32_t timer;             /* 0x28 */
    uint8_t reserved2c[0x18]; /* 0x2c..0x43 */
    void *seq_data;            /* 0x44 */
    uint8_t reserved48[0x38]; /* 0x48..0x7f */
    void *queue;               /* 0x80 (in-flight sequence events) */
    uint8_t reserved84[0x44]; /* 0x84..0xc7 */
    uint32_t step_index;       /* 0xc8 */
};

/* Loader / control object table reference (segment 0, offset 0x1121c area).
 * Inferred layout: 4-word stub.
 */
extern uint32_t DllSequenceControlTable[4];

/* CRO 0xc48: demangled C++ method xy_system::bg::System::SetIsCallDraw(bool).
 * ARM prologue at the same offset stores the flag at `self + 0x4c` (offset
 * inferred from the single STR shown in the disassembly) and returns.
 */
void xy_system_bg_System_SetIsCallDraw(int32_t flag) {
    /* TODO: not yet decoded — body is one branch + store + bx lr. */
    (void)flag;
}

/* CRO 0x0..0x? — sequence object constructor (locates the imported helper
 * at +0x4..+0x18 via the loader stubs). ARM prologue visible near the start.
 */
static void sequence_construct(struct SequenceProc *self) {
    /* TODO: not yet decoded. */
    (void)self;
}

/* CRO 0x? — sequence runner dispatch loop. Heavily-imported: every step
 * function in the static module has an indirect call through here.
 */
static void sequence_step_dispatch(struct SequenceProc *self) {
    /* TODO: not yet decoded. */
    (void)self;
}
