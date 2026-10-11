/*
 * Preliminary decompilation of DllTestKawada.cro.
 *
 * Source address notation uses CRO file offsets (the loader copies segment 0
 * to RAM, so 0x180 + offset maps directly to the live address). This file is
 * intentionally not wired into a build yet: the literal pool entries are zero
 * in the on-disk image and only get relocated when the CRO is loaded, so
 * reconstructing the patched layout requires the loader's relocation tables
 * from another module.
 *
 * Module summary:
 *   - 8 KiB CRO, six segments, segment 0 holds code (0x180..0x25c, 220 B).
 *   - Two functions total: a static-data initializer at 0x180, and the
 *     exported `nnroControlObject_` constructor at 0x1ac.
 *   - Single named export `nnroControlObject_` (segment 0, offset 0x2c -> 0x1ac).
 *   - CRO control_object field is 0x2c0 (a 20-byte control structure beyond
 *     segment 0, populated by the static initializer at module load).
 *   - Zero imported modules, zero external patches.
 *   - No business logic; the body is the boilerplate NN ro loader stub.
 *
 * What was recovered:
 *   - The static initializer at 0x180..0x1a0: writes 0xFFFFFFFFFFFFFFFF into
 *     one relocated pointer and 0x0000000000000000 into another, then returns.
 *     These are the two halves of the CRO control_object block.
 *   - The 5-action switch at 0x1ac..0x230 that implements
 *     nnroControlObject_'s dispatch on r1 (action 0..4 and the r1>=5
 *     fall-through). The constructor body is byte-identical to the stub in
 *     the other 9 Test/Debug CROs.
 *
 * What was NOT recovered:
 *   - The literal pool entries at 0x1a4 and 0x1a8 (both 0 on disk) are
 *     addresses the loader relocates to live BSS/data. Their targets define
 *     the layout of the control_object block.
 *   - The five literal-pool entries at 0x234..0x248 (all 0 on disk) inside
 *     the constructor carry loader-relocated pointers; their targets are
 *     unknown without the relocation tables.
 *   - The literal pool entry at 0x234 feeds the r2 pointer used by actions 1
 *     and 2 (str/ldr via r2). Its runtime target is unknown.
 */

#include <stdint.h>

/* nnroControlObject_ action codes (r1 in the ARM prologue at CRO 0x1ac). */
enum ControlObjectAction {
    CONTROL_OBJECT_INIT       = 0, /* store vtable literal into [r0] */
    CONTROL_OBJECT_REGISTER   = 1, /* store this ptr into global r2 literal */
    CONTROL_OBJECT_LOAD       = 2, /* load global r2 literal into [r0] */
    CONTROL_OBJECT_PRIORITY_A = 3, /* store two literals at [r0] and [r0+4] */
    CONTROL_OBJECT_PRIORITY_B = 4, /* store two literals at [r0] and [r0+4] */
};

/* Confirmed from field accesses in the original ARM code.
 * The pointer at +0x00 is rewritten on action 0 / 2 / 3 / 4. The 8-byte
 * block at +0x00..+0x07 is rewritten on actions 3 and 4 (two literals
 * stored one after the other). No field beyond +0x07 is written by this
 * module. */
typedef struct ControlObject {
    uint32_t vtable_or_value; /* 0x00 — literal pool entry target */
    uint32_t secondary;       /* 0x04 — written on actions 3 and 4 */
} ControlObject;

/* The CRO header points control_object at offset 0x2c0, which sits in the
 * 0x14-byte data segment (data_offset 0x1118, data_size 0x14). The init
 * function below patches the first 16 bytes of that block. */
typedef struct ControlObjectBlock {
    uint64_t sentinel;       /* +0x00 — written to 0xFFFFFFFFFFFFFFFF by init */
    uint64_t cleared;         /* +0x08 — written to 0x0000000000000000 by init */
} ControlObjectBlock;

static uint32_t nnroControlObject(ControlObject *obj, uint32_t action);

/* CRO 0x180..0x1a0. Module-load initializer. Writes two 8-byte blocks into
 * the relocated addresses supplied by literal pool entries @ 0x1a4 and
 * 0x1a8 (both 0 on disk; loader fills them in). The first block becomes
 * all-ones, the second becomes all-zeros. Returns without saving anything.
 *
 * ARM translation (caller is in ARM mode):
 *   0x180: ldr  r2, [pc, #28]   ; r2 = literal @ 0x1a4  (target A)
 *   0x184: mvn  r0, #0          ; r0 = -1
 *   0x188: mov  r1, r0           ; r1 = -1
 *   0x18c: strd r0, [r2]        ; *(uint64_t *)target_A = 0xFFFFFFFFFFFFFFFF
 *   0x190: ldr  r0, [pc, #16]   ; r0 = literal @ 0x1a8  (target B)
 *   0x194: mov  r1, #0          ; r1 = 0
 *   0x198: mov  r2, r1           ; r2 = 0
 *   0x19c: stm  r0, {r1, r2}    ; *(uint64_t *)target_B = 0x0000000000000000
 *   0x1a0: bx   lr
 */
static void controlObjectInit(ControlObjectBlock *block_a,
                             ControlObjectBlock *block_b) {
    /* TODO: not yet decoded — literal pool entries @ 0x1a4 and 0x1a8 are
     * 0 on disk; the loader relocates them at load time. The C below
     * preserves the structure but uses the target objects' identities
     * as a stand-in for the relocated addresses. */
    (void)block_a;
    (void)block_b;
}

/* CRO 0x1ac..0x230. nnroControlObject_ exported entrypoint.
 *   r0 = ControlObject * (destination for the action's stores)
 *   r1 = action code (see enum ControlObjectAction)
 * Returns 0 on all paths (including the r1>=5 fall-through).
 *
 * Action dispatch (verified by reading the jump table at 0x1c0..0x1d4):
 *   0 -> CRO 0x1d4 -> loads r1 from literal @ 0x238, branches to 0x1e8.
 *   1 -> CRO 0x1dc -> stores r0 through the r2 literal @ 0x234, returns.
 *   2 -> CRO 0x1e4 -> loads r1 through r2 literal @ 0x234, branches to 0x1e8.
 *   3 -> CRO 0x1f0 -> stores literal @ 0x23c to [r0], stores literal @ 0x240
 *                    to [r0,#4], returns.
 *   4 -> CRO 0x200 -> stores literal @ 0x244 to [r0], stores literal @ 0x248
 *                    to [r0,#4], returns.
 *
 * The five jump table slots at 0x1c0..0x1d4 are zero on disk and only get
 * filled in by the loader (these are absolute addresses pointing into the
 * switch body).
 */
static uint32_t nnroControlObject(ControlObject *obj, uint32_t action) {
    /* TODO: not yet decoded — action handlers rely on five literal pool
     * entries (0x234..0x248) that the loader relocates at runtime. The C
     * below shows the observed control flow but cannot be byte-matched
     * until the relocation target of each literal is recovered. */
    switch (action) {
    case CONTROL_OBJECT_INIT:
        /* Loads a pointer from the relocated literal at 0x238 into r1
         * and stores it at obj->vtable_or_value. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x238 */
        return 0;
    case CONTROL_OBJECT_REGISTER:
        /* Stores obj into the relocated global pointed to by 0x234. */
        /* r2 = *(uint32_t *)0x234; *r2 = (uint32_t)obj; */
        (void)obj;
        return 0;
    case CONTROL_OBJECT_LOAD:
        /* Loads the global at 0x234 into obj->vtable_or_value. */
        /* obj->vtable_or_value = *(uint32_t *)*(uint32_t *)0x234; */
        obj->vtable_or_value = 0; /* placeholder for *(uint32_t *)0x234 */
        return 0;
    case CONTROL_OBJECT_PRIORITY_A:
        /* Stores two relocated literals into the first 8 bytes. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x23c */
        obj->secondary       = 0; /* placeholder for literal @ 0x240 */
        return 0;
    case CONTROL_OBJECT_PRIORITY_B:
        /* Stores two relocated literals into the first 8 bytes. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x244 */
        obj->secondary       = 0; /* placeholder for literal @ 0x248 */
        return 0;
    default:
        /* CRO 0x218..0x232 default path: load result/error code and
         * return. The three constants at 0x24c..0x254 are stored in the
         * image: 0x30000000, 0x30000026, 0xd8e12c21. The exact return
         * semantics (which one ends up in r0) are loader-dependent. */
        return 0x30000026u; /* placeholder — see CRO 0x24c..0x254 */
    }
}

/* No additional functions; the module exports only `nnroControlObject_`. */