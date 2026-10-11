/*
 * Preliminary decompilation of DllSubScreenTutorial.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180
 * is segment 0 / 0). This file is intentionally not wired into a build
 * yet: imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table (1 named symbol: nnroControlObject_)
 *   - import table (73 anonymous entries from |static|)
 *   - ~22 function boundaries identified by ARM push/pop prologues
 *   - a few struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - vtable layouts for any imported class
 *   - exact control-object layout produced by nnroControlObject_
 *   - imported service identities (only the relocation offsets are known)
 */

#include <stdint.h>

typedef struct SubScreenTutorialProc SubScreenTutorialProc;
typedef struct SubScreenTutorialWork SubScreenTutorialWork;

/* Inferred from repeated `ldr r0, [r4, #N]` patterns in the state machine.
 * Only the offsets that appear multiple times are pinned. */
struct SubScreenTutorialProc {
    void *vtable;          /* 0x00 */
    int32_t state;         /* 0x04 */
    uint8_t reserved08[0x1c]; /* 0x08..0x23 */
    uint32_t field_24;     /* 0x24 */
    void *child;           /* 0x38 */
    void *param_ptr;       /* 0x3c */
};

/* Called from 0x358 (state-machine update). */
static int subscreen_tutorial_can_run(void) { return 1; }

/* CRO 0x358. Six-way state machine driven by `self->state` (+0x04).
 * Switch arms (offsets derived from the in-function jump table near 0x370):
 *   case 0  -> 0x388 (init: load s0/s1 constants, call import 0x180 + 0x188,
 *                    advance state, poll import 0x190)
 *   case 1  -> 0x3d8 (poll import 0x190; on success call internal 0xeb8 and
 *                    write byte 1 to self->child+0x84, advance state)
 *   case 2  -> 0x400 (gate on self->child->field_7c and child->field_80 & 1,
 *                    plus child->field_84; on success call internal 0x198,
 *                    then imported 0x1a0)
 *   case 3  -> 0x460 (init: reset a 3-arg call to imported 0x1a8)
 *   default -> tail-call self->child->vtable[8] (ldr r1, [r1, #0x20]; blx r1)
 */
static int subscreen_tutorial_update(SubScreenTutorialProc *self);

/* CRO 0x4cc. Three-state teardown.
 *   case 0 -> set self->state = 1, fall through
 *   case 1 -> if self->child: blx child->vtable[6] (+0x18); self->child = 0;
 *             advance state
 *   case 2 -> self->state = 0; return 1
 */
static int subscreen_tutorial_shutdown(SubScreenTutorialProc *self);

/* CRO 0x538. Leaf helper: returns self->child->vtable[9].
 * Spilled through r0/r1; bx r1 at 0x544. */
static int subscreen_tutorial_call_draw(SubScreenTutorialProc *self) {
    /* vtable slot +0x24 = virtual index 9 (draw / render) */
    extern int __vtable_call_draw(SubScreenTutorialProc *);
    /* The original is a 4-instruction tail call; do not unspool here. */
    return 0; /* TODO: not yet decoded */
}

/* CRO 0x548. Heavy constructor: allocates self->child (160-byte object) via
 * imported 0x1c0 and calls imported 0x1b0/0x1b8 to populate 2 sub-fields,
 * then dispatches on self->param_ptr->byte_0 (+0x3c):
 *   == 0 -> no extra init
 *   == 1 -> imported 0x1c8 with arg set 0/0/0
 *   else -> (handled by tail fall-through)
 */
static int subscreen_tutorial_construct(SubScreenTutorialProc *self);

/* CRO 0x68c..0x6d4. 6-register helper. */
/* CRO 0x6e4..0x724. 2-register helper. */
/* CRO 0x734..0x77c. 2-register helper. */
/* CRO 0x788..0x814. 4-register helper. */
/* CRO 0x81c..0x878. 2-register helper. */
/* CRO 0x880..0x8e4. 8-register helper. */
/* CRO 0x95c..0xae8. Large body (push {r4,r5,lr}). */
/* CRO 0xaf4..0xc58. Very large body (push {r3,r4,r5,lr}). */
/* CRO 0xc60..0xd50. 3-register helper. */
/* CRO 0xd58..0xe80. 3-register helper with tail-call pattern. */
/* CRO 0xeb8..0xf28. 4-register helper. */
/* CRO 0xf30..0xf54. 2-register helper. */
/* CRO 0xf5c..0xfd8. 2-register helper. */
/* CRO 0xfe0..0x11c4. Very large body (push {r4,r5,r6,r7,lr}). */
/* CRO 0x11ec..0x1238. 2-register helper. */
/* CRO 0x1248..0x1294. 2-register helper. */
/* CRO 0x12cc..0x12f8. 2-register helper. */
/* CRO 0x1304..0x1330. 2-register helper. */

/* CRO 0x1340. Hosts the exported symbol `nnroControlObject_` at 0x1360.
 * Pattern: alloc helper (imported 0x210/0x218) followed by an indirect call
 * to imported 0x220 (likely the loader-init glue). The export is therefore
 * a mid-function offset; the surrounding 0x1340..0x13cc frame is the real
 * control-object constructor. */
static void *subscreen_tutorial_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    return 0;
}

/* CRO 0x13d4..0x1438. 8-register helper, switch on r4 (loop counter 0..2)
 * comparing r5 against an entry from [r8, r4*0x1c + 0x68]. */
/* CRO 0x14e8..0x1548. 2-register helper. */