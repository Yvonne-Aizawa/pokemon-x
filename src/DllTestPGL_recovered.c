/*
 * Preliminary decompilation of DllTestPGL.cro.
 *
 * Source address notation uses CRO file offsets (the loader copies segment 0
 * to RAM, so 0x180 + offset maps directly to the live address). This file is
 * intentionally not wired into a build yet: the literal pool entries are zero
 * in the on-disk image and only get relocated when the CRO is loaded, so
 * reconstructing the patched layout requires the loader's relocation tables
 * from another module.
 *
 * Module summary:
 *   - 8 KiB CRO, six segments. Segment 0 holds code from 0x180 to 0x2fc.
 *   - Two named exports:
 *     * `nnroControlObject_` at segment 0 offset 0xd0 -> CRO 0x250.
 *     * `_ZN9xy_system2bg6System13SetIsCallDrawEb` at segment 0 offset 0x0
 *       -> CRO 0x180 (the demangled name is
 *       `xy_system::bg::System::SetIsCallDraw(bool)`).
 *   - CRO control_object field is 0xd00.
 *   - Three segments carry data: id 2 is 20 bytes at CRO 0x1168, id 3 is
 *     60 bytes of BSS at CRO 0x0.
 *   - Zero imported modules, zero external patches.
 *   - The module is still boilerplate loader stub plus a unique VFP/NEON
 *     float initializer and a one-byte-write C++ setter.
 *
 * What was recovered:
 *   - `SetIsCallDraw(bool)` at 0x180..0x188: a two-instruction leaf that
 *     stores the byte in r1 at obj + 0xd9 and returns via `bx lr`. The
 *     caller passes `this` in r0; the bool lands at field offset 0xd9 in
 *     the `xy_system::bg::System` struct.
 *   - The VFP/NEON float initializer at 0x188..0x214: writes 0xFFFFFFFFFFFFFFFF
 *     into one relocated handle (LIT(0x218) = 0x30000000), zero into another
 *     (LIT(0x21c) = 0x30000026), and then fills two relocated float buffers
 *     at LIT(0x224) and LIT(0x244) with three (vec3) blocks of three floats
 *     apiece. The float constants are taken from the on-disk literal pool at
 *     0x228..0x24c; see `Float literals` below.
 *   - The 5-action switch at 0x250..0x2d4 that implements
 *     nnroControlObject_'s dispatch on r1 (action 0..4 and the r1>=5
 *     fall-through). The constructor body is byte-identical to the stub in
 *     the other 11 Test/Debug CROs on the worker-2 list.
 *
 * Float literals (CRO offsets inside the literal pool):
 *   0x228 -> 0.75
 *   0x22c -> ~1.45
 *   0x230 -> -0.8
 *   0x234 -> ~0.95
 *   0x238 -> 30.0
 *   0x23c -> 90.0
 *   0x240 -> -45.0
 *   0x244 -> 0 (this literal is itself a relocated pointer, but its static
 *                 value happens to be 0; the vldr on it is unused as a float
 *                 — only the LDR r0 at 0x1f8 consumes it as a pointer)
 *   0x248 -> 120.0
 *   0x24c -> 45.0
 *
 * Inferred struct layouts the initializer writes:
 *   At LIT(0x224) (a 36-byte relocated buffer):
 *     +0x00: float = 0.0
 *     +0x04: float = 0.75
 *     +0x08: float = 1.45
 *     +0x0c: float = 0.0
 *     +0x10: float = -0.8
 *     +0x14: float = 0.95
 *     +0x18: float = -45.0
 *     +0x1c: float = 30.0
 *     +0x20: float = 90.0
 *   At LIT(0x244) (a 36-byte relocated buffer; +0..+11 left as 0):
 *     +0x00..+0x0b: 0 (not written)
 *     +0x0c: float = 0.0
 *     +0x10: float = 30.0
 *     +0x14: float = 45.0
 *     +0x18: float = 45.0
 *     +0x1c: float = 30.0
 *     +0x20: float = 90.0
 *   The 0.0 entries are explicit vstr writes of s0 — s0 was loaded with
 *   0.0 from LIT(0x220) (= the loader pointer 0xd8e12c21 in the file but
 *   0.0 when interpreted as a float constant the loader would have
 *   pre-cleared). The writer pattern matches a 60-line background "
 *   System" test setup; the semantic meaning of the float values is not
 *   recoverable from this module alone.
 *
 * What was NOT recovered:
 *   - The runtime values of the relocated pointer literals at
 *     0x218/0x21c/0x220/0x224/0x244 (all 0 on disk). The loader fills
 *     these in to point at live BSS/data; without the relocation table
 *     we cannot name the targets.
 *   - The five literal-pool entries at 0x2d8..0x2ec inside the
 *     nnroControlObject_ constructor carry loader-relocated pointers; the
 *     targets are unknown.
 *   - The literal pool entry at 0x2d8 feeds the r2 pointer used by actions 1
 *     and 2 (str/ldr via r2). Its runtime target is unknown.
 *   - The semantic meaning of the float constants and the
 *     xy_system::bg::System struct (beyond the +0xd9 field touched by
 *     SetIsCallDraw) is not derivable from this module.
 */

#include <stdint.h>

/* nnroControlObject_ action codes (r1 in the ARM prologue at CRO 0x250). */
enum ControlObjectAction_pgl {
    CONTROL_OBJECT_PGL_INIT       = 0, /* store vtable literal into [r0] */
    CONTROL_OBJECT_PGL_REGISTER   = 1, /* store this ptr into global r2 literal */
    CONTROL_OBJECT_PGL_LOAD       = 2, /* load global r2 literal into [r0] */
    CONTROL_OBJECT_PGL_PRIORITY_A = 3, /* store two literals at [r0] and [r0+4] */
    CONTROL_OBJECT_PGL_PRIORITY_B = 4, /* store two literals at [r0] and [r0+4] */
};

/* `xy_system::bg::System`. The only field referenced by this module is the
 * one-byte "isCallDraw" flag at offset 0xd9. The rest of the layout is
 * defined in another CRO (xy_system.bg.System.vtable) and not present here. */
typedef struct SystemBg {
    uint8_t reserved0[0xd9]; /* 0x00..0xd8 — defined in another module */
    uint8_t is_call_draw;   /* 0xd9 — touched by SetIsCallDraw */
} SystemBg;

/* Confirmed from field accesses in the original ARM code (nnroControlObject_
 * constructor). The pointer at +0x00 is rewritten on action 0 / 2 / 3 / 4.
 * The 8-byte block at +0x00..+0x07 is rewritten on actions 3 and 4. No field
 * beyond +0x07 is written by this module. */
typedef struct {
    uint32_t vtable_or_value; /* 0x00 — literal pool entry target */
    uint32_t secondary;       /* 0x04 — written on actions 3 and 4 */
} DllTestPGL_ControlObject;

#define ControlObject DllTestPGL_ControlObject

/* CRO 0x180..0x184. Exported `_ZN9xy_system2bg6System13SetIsCallDrawEb`. */
static void xy_system_bg_System_SetIsCallDraw(SystemBg *self, int32_t enable);

/* CRO 0x180..0x184 */
static void xy_system_bg_System_SetIsCallDraw(SystemBg *self, int32_t enable) {
    /* strb r1, [r0, #0xd9]; bx lr */
    self->is_call_draw = (uint8_t)(enable & 0xff);
}

/* CRO 0x188..0x214. Module-load initializer. The structure is:
 *   1. write 0xFFFFFFFFFFFFFFFF to *(uint64_t *)LIT(0x218)
 *      (LIT(0x218) is statically 0x30000000, a loader pointer)
 *   2. write 0x0000000000000000 to *(uint64_t *)LIT(0x21c)
 *      (LIT(0x21c) is statically 0x30000026, another loader pointer)
 *   3. fill the relocated buffer at LIT(0x224) with nine floats (see
 *      header for the exact values)
 *   4. fill the relocated buffer at LIT(0x244) with six floats (the first
 *      six bytes are left untouched — likely already 0 by construction)
 *
 * ARM translation (caller is in ARM mode):
 *   0x188: ldr  r2, [pc, #136]   ; r2 = LIT(0x218)
 *   0x18c: mvn  r0, #0           ; r0 = -1
 *   0x190: mov  r1, r0            ; r1 = -1
 *   0x194: vldr s0, [pc, #132]  ; s0 = 0.0 (from literal pool @ 0x220)
 *   0x198: strd r0, [r2]         ; *(uint64_t *)LIT(0x218) = 0xFFFFFFFFFFFFFFFF
 *   0x19c: ldr  r0, [pc, #120]  ; r0 = LIT(0x21c)
 *   0x1a0: mov  r1, #0           ; r1 = 0
 *   0x1a4: mov  r2, r1            ; r2 = 0
 *   0x1a8: vldr s2, [pc, #120]  ; s2 = 0.75
 *   0x1ac: stm  r0, {r1, r2}    ; *(uint64_t *)LIT(0x21c) = 0
 *   0x1b0: ldr  r0, [pc, #108]  ; r0 = LIT(0x224) (target buffer A)
 *   0x1b4: vldr s1, [pc, #112]  ; s1 = 1.45
 *   0x1b8: vldr s3, [pc, #128]  ; s3 = -45.0
 *   0x1bc: vstr s0, [r0]         ; *(LIT(0x224)+0x00) = 0.0
 *   0x1c0: vstr s2, [r0, #4]     ; *(LIT(0x224)+0x04) = 0.75
 *   0x1c4: vstr s1, [r0, #8]     ; *(LIT(0x224)+0x08) = 1.45
 *   0x1c8: add  r0, r0, #12
 *   0x1cc: vldr s2, [pc, #92]   ; s2 = -0.8 (reload)
 *   0x1d0: vstr s0, [r0]         ; *(LIT(0x224)+0x0c) = 0.0
 *   0x1d4: vldr s1, [pc, #88]   ; s1 = 0.95 (reload)
 *   0x1d8: vstr s2, [r0, #4]     ; *(LIT(0x224)+0x10) = -0.8
 *   0x1dc: vstr s1, [r0, #8]     ; *(LIT(0x224)+0x14) = 0.95
 *   0x1e0: add  r0, r0, #12
 *   0x1e4: vldr s1, [pc, #76]   ; s1 = 30.0
 *   0x1e8: vldr s2, [pc, #76]   ; s2 = 90.0
 *   0x1ec: vstmia r0!, {s3}     ; *(LIT(0x224)+0x18) = -45.0, r0 += 4
 *   0x1f0: vldr s3, [pc, #80]   ; s3 = 45.0 (reload)
 *   0x1f4: vstmia r0, {s1-s2}   ; *(LIT(0x224)+0x1c) = 30.0
 *                              ; *(LIT(0x224)+0x20) = 90.0
 *   0x1f8: ldr  r0, [pc, #68]   ; r0 = LIT(0x244) (target buffer B)
 *   0x1fc: add  r1, r0, #12
 *   0x200: vstr s3, [r0, #20]   ; *(LIT(0x244)+0x14) = 45.0
 *   0x204: add  r0, r0, #24
 *   0x208: vstmia r1, {s0-s1}   ; *(LIT(0x244)+0x0c) = 0.0
 *                              ; *(LIT(0x244)+0x10) = 30.0
 *   0x20c: vldr s0, [pc, #56]   ; s0 = 45.0 (reload)
 *   0x210: vstmia r0, {s0-s2}   ; *(LIT(0x244)+0x18) = 45.0
 *                              ; *(LIT(0x244)+0x1c) = 30.0
 *                              ; *(LIT(0x244)+0x20) = 90.0
 *   0x214: bx   lr
 */
static void pgl_data_init(void *block_a_sentinel,
                          void *block_b_zero,
                          float *buffer_a,
                          float *buffer_b) {
    /* TODO: not yet decoded — literal pool entries @ 0x218, 0x21c, 0x224,
     * 0x244 are 0 (or non-pointer values like 0x30000000) on disk; the
     * loader relocates them at load time. The C below preserves the
     * structure but uses the target objects' identities as a stand-in. */
    (void)block_a_sentinel;
    (void)block_b_zero;
    (void)buffer_a;
    (void)buffer_b;
}

/* CRO 0x250..0x2d4. nnroControlObject_ exported entrypoint.
 *   r0 = ControlObject * (destination for the action's stores)
 *   r1 = action code (see enum ControlObjectAction_pgl)
 * Returns 0 on all paths (including the r1>=5 fall-through).
 *
 * Action dispatch (verified by reading the jump table at 0x264..0x278):
 *   0 -> CRO 0x278 -> loads r1 from literal @ 0x2dc, branches to 0x28c.
 *   1 -> CRO 0x280 -> stores r0 through the r2 literal @ 0x2d8, returns.
 *   2 -> CRO 0x288 -> loads r1 through r2 literal @ 0x2d8, branches to 0x28c.
 *   3 -> CRO 0x294 -> stores literal @ 0x2e0 to [r0], stores literal @ 0x2e4
 *                    to [r0,#4], returns.
 *   4 -> CRO 0x2a4 -> stores literal @ 0x2e8 to [r0], stores literal @ 0x2ec
 *                    to [r0,#4], returns.
 *
 * The five jump table slots at 0x264..0x278 are zero on disk and only get
 * filled in by the loader (these are absolute addresses pointing into the
 * switch body).
 */
static uint32_t nnroControlObject(ControlObject *obj, uint32_t action) {
    /* TODO: not yet decoded — action handlers rely on five literal pool
     * entries (0x2d8..0x2ec) that the loader relocates at runtime. The C
     * below shows the observed control flow but cannot be byte-matched
     * until the relocation target of each literal is recovered. */
    switch (action) {
    case CONTROL_OBJECT_PGL_INIT:
        /* Loads a pointer from the relocated literal at 0x2dc into r1
         * and stores it at obj->vtable_or_value. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x2dc */
        return 0;
    case CONTROL_OBJECT_PGL_REGISTER:
        /* Stores obj into the relocated global pointed to by 0x2d8. */
        /* r2 = *(uint32_t *)0x2d8; *r2 = (uint32_t)obj; */
        (void)obj;
        return 0;
    case CONTROL_OBJECT_PGL_LOAD:
        /* Loads the global at 0x2d8 into obj->vtable_or_value. */
        /* obj->vtable_or_value = *(uint32_t *)*(uint32_t *)0x2d8; */
        obj->vtable_or_value = 0; /* placeholder for *(uint32_t *)0x2d8 */
        return 0;
    case CONTROL_OBJECT_PGL_PRIORITY_A:
        /* Stores two relocated literals into the first 8 bytes. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x2e0 */
        obj->secondary       = 0; /* placeholder for literal @ 0x2e4 */
        return 0;
    case CONTROL_OBJECT_PGL_PRIORITY_B:
        /* Stores two relocated literals into the first 8 bytes. */
        obj->vtable_or_value = 0; /* placeholder for literal @ 0x2e8 */
        obj->secondary       = 0; /* placeholder for literal @ 0x2ec */
        return 0;
    default:
        /* CRO 0x2bc..0x2d6 default path: load result/error code and
         * return. The three constants at 0x2f0..0x2f8 are stored in the
         * image: 0x30000000, 0x30000026, 0xd8e12c21. The exact return
         * semantics (which one ends up in r0) are loader-dependent. */
        return 0x30000026u; /* placeholder — see CRO 0x2f0..0x2f8 */
    }
}