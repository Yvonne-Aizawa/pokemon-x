/*
 * Preliminary decompilation of DllTestOhno.cro.
 *
 * Source address notation uses CRO file offsets (the loader copies segment 0
 * to RAM, so 0x180 + offset maps directly to the live address). This file is
 * intentionally not wired into a build yet: the literal pool entries are zero
 * in the on-disk image and only get relocated when the CRO is loaded, so
 * reconstructing the patched layout requires the loader's relocation tables
 * from another module.
 *
 * Module summary:
 *   - 8 KiB CRO, six segments, only segment 0 holds code (0x180..0x22c, 172 B).
 *   - Single named export `nnroControlObject_` (segment 0, offset 0x0 -> 0x180).
 *   - CRO control_object field is 0x0 (no object exposed by the header).
 *   - Zero imported modules, zero external patches.
 *   - No business logic; the body is the boilerplate NN ro loader stub.
 *
 * What was recovered:
 *   - The 5-action switch that implements nnroControlObject_'s dispatch on r1
 *     (action 0..4 and the r1>=5 fall-through). The action handlers are the
 *     standard "ctor / register / copy / set-priority-vtable-a / set-vtable-b"
 *     shape seen across every Test/Debug CRO in this title.
 *
 * What was NOT recovered:
 *   - The five literal-pool entries at 0x208..0x21c (all 0 on disk) carry
 *     loader-relocated pointers to live BSS/data; without the relocation
 *     tables we cannot recover what objects they name.
 *   - The literal pool entry at 0x208 feeds the r2 pointer used by actions 1
 *     and 2 (str/ldr via r2). Its runtime target is unknown.
 */

#include <stdint.h>

/* nnroControlObject_ action codes (r1 in the ARM prologue at CRO 0x180). */
enum ControlObjectAction_ohno {
    CONTROL_OBJECT_OHNO_INIT       = 0, /* store vtable literal into [r0] */
    CONTROL_OBJECT_OHNO_REGISTER   = 1, /* store this ptr into global r2 literal */
    CONTROL_OBJECT_OHNO_LOAD       = 2, /* load global r2 literal into [r0] */
    CONTROL_OBJECT_OHNO_PRIORITY_A = 3, /* store two literals at [r0] and [r0+4] */
    CONTROL_OBJECT_OHNO_PRIORITY_B = 4, /* store two literals at [r0] and [r0+4] */
};

/* Confirmed from field accesses in the original ARM code.
 * The pointer at +0x00 is rewritten on action 0 / 2 / 3 / 4. The 8-byte
 * block at +0x00..+0x07 is rewritten on actions 3 and 4 (two literals
 * stored one after the other). No field beyond +0x07 is written by this
 * module. */
typedef struct {
    uint32_t vtable_or_value; /* 0x00 — literal pool entry target */
    uint32_t secondary;       /* 0x04 — written on actions 3 and 4 */
} DllTestOhno_ControlObject;

#define ControlObject DllTestOhno_ControlObject

static uint32_t nnroControlObject(ControlObject *obj, uint32_t action);

/* CRO 0x180..0x208 */
static uint32_t nnroControlObject(ControlObject *obj, uint32_t action) {
    /* TODO: not yet decoded — action handlers rely on five literal pool
     * entries (0x208..0x21c) that the loader relocates at runtime. The C
     * below shows the observed control flow but cannot be byte-matched
     * until the relocation target of each literal is recovered. */
    switch (action) {
    case CONTROL_OBJECT_OHNO_INIT:
        /* Loads a pointer from the relocated literal at 0x20c into r1
         * and stores it at obj->vtable_or_value. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x20c */
        return 0;
    case CONTROL_OBJECT_OHNO_REGISTER:
        /* Stores obj into the relocated global pointed to by 0x208. */
        /* r2 = *(uint32_t *)0x208; *r2 = (uint32_t)obj; */
        (void)obj;
        return 0;
    case CONTROL_OBJECT_OHNO_LOAD:
        /* Loads the global at 0x208 into obj->vtable_or_value. */
        /* obj->vtable_or_value = *(uint32_t *)*(uint32_t *)0x208; */
        obj->vtable_or_value = 0; /* placeholder for *(uint32_t *)0x208 */
        return 0;
    case CONTROL_OBJECT_OHNO_PRIORITY_A:
        /* Stores two relocated literals into the first 8 bytes. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x210 */
        obj->secondary       = 0; /* placeholder for literal @ 0x214 */
        return 0;
    case CONTROL_OBJECT_OHNO_PRIORITY_B:
        /* Stores two relocated literals into the first 8 bytes. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x218 */
        obj->secondary       = 0; /* placeholder for literal @ 0x21c */
        return 0;
    default:
        /* CRO 0x1ec..0x206 default path: load result/error code and
         * return. The three constants at 0x220..0x228 are stored in the
         * image: 0x30000000, 0x30000026, 0xd8e12c21. The exact return
         * semantics (which one ends up in r0) are loader-dependent. */
        return 0x30000026u; /* placeholder — see CRO 0x220..0x228 */
    }
}

/* No additional functions; the module exports only `nnroControlObject_`. */
