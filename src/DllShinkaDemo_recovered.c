/*
 * Preliminary decompilation of DllShinkaDemo.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 2 named symbols
 *       nnroControlObject_                                @ 0x3a1c
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb         @ 0x3944
 *   - import table:
 *       194 anonymous entries from |static| at 0x5b7c
 *       13 anonymous entries from DllBattle  at 0x618c
 *       14 anonymous entries from DllSequence at 0x61f4
 *   - ~44 function boundaries identified by ARM push/pop prologues
 *   - ~225 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *     (the player state struct has +0x14 as a child pointer, +0x28
 *     accessed in nnro region; VFP usage confirmed)
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export tricks at 0x3944 / 0x3a1c
 *
 * Module summary: Evolution demo -- the cutscene played when a Pokemon
 * evolves.  Imports from DllBattle (battle state) and DllSequence
 * (scripted animation sequencer) tie this into the battle engine.
 */

#include <stdint.h>

typedef struct ShinkaDemoProc ShinkaDemoProc;

/* Inferred from repeated [r4, #N] / [r5, #N] accesses. */
struct ShinkaDemoProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c */
    void *field_10;        /* 0x10 */
    void *field_18;        /* 0x18 */
    void *field_1c;        /* 0x1c */
    void *field_20;        /* 0x20 */
    void *field_24;        /* 0x24 */
    void *field_28;        /* 0x28 (read in nnro region) */
    uint8_t state;         /* 0x2c */
    uint8_t sub_state;     /* 0x2d */
    uint16_t parameter;    /* 0x2e */
    int32_t timer;         /* 0x30 */
};

/* CRO 0x808..0x8e8. Two-register helper. */
/* CRO 0x8e8..0x964. Two-register helper. */
/* CRO 0x964..0xad8. Seven-register + dummy frame helper -- large body
 *   that builds the initial child object via thunks 0x1a0..0x1c8. */
/* CRO 0xad8..0xb14. Three-register helper. */
/* CRO 0xb14..0xb4c. Two-register helper. */
/* CRO 0xb4c..0xb80. Two-register helper. */
/* CRO 0xb80..0xcac. Six-register helper. */
/* CRO 0xcac..0xe68. Four-register helper. */
/* CRO 0xe68..0xff4. Three-register helper. */
/* CRO 0xff4..0x1058. Two-register helper. */
/* CRO 0x1058..0x11fc. Six-register helper. */
/* CRO 0x11fc..0x143c. Three-register helper. */
/* CRO 0x143c..0x1688. Five-register helper. */
/* CRO 0x1688..0x1790. Seven-register helper. */
/* CRO 0x1790..0x17a0. Two-register helper. */
/* CRO 0x17a0..0x19b0. Two-register helper. */
/* CRO 0x19b0..0x1bec. Five-register + dummy frame helper. */
/* CRO 0x1bec..0x1fe8. Six-register helper. */
/* CRO 0x1fe8..0x2038. Two-register helper. */
/* CRO 0x2038..0x2224. Ten-register + fp helper -- large VFP draw
 *   routine (vmov.f32, vstmia, vldr.f32 heavily used). */
/* CRO 0x2224..0x22a0. Three-register helper. */
/* CRO 0x22a0..0x2594. Seven-register helper. */
/* CRO 0x2594..0x2728. Three-register helper. */
/* CRO 0x2728..0x27a0. Three-register helper. */
/* CRO 0x27a0..0x28a0. Five-register helper. */
/* CRO 0x28a0..0x29c0. Seven-register helper. */
/* CRO 0x29c0..0x2a54. Three-register helper. */
/* CRO 0x2a54..0x2b54. Five-register helper. */
/* CRO 0x2b54..0x2be8. Two-register helper. */
/* CRO 0x2be8..0x2c74. Two-register helper. */
/* CRO 0x2c74..0x2ea0. Seven-register + dummy frame helper. */
/* CRO 0x2ea0..0x2f04. Two-register helper. */
/* CRO 0x2f04..0x2f84. Three-register helper. */
/* CRO 0x2f84..0x31f8. Ten-register + fp helper -- main constructor. */
/* CRO 0x31f8..0x33a8. Five-register helper. */
/* CRO 0x33a8..0x3464. Five-register helper. */
/* CRO 0x3464..0x34e8. Two-register helper. */
/* CRO 0x34e8..0x3620. Five-register helper. */
/* CRO 0x3620..0x3688. Three-register helper. */
/* CRO 0x3688..0x3870. Seven-register helper. */
/* CRO 0x3870..0x3a58. Three-register helper. */
/* CRO 0x3a58..0x3a90. Two-register helper. */
/* CRO 0x3a90..0x3ba4. Two-register helper. */

/* --- C++ mangled export --- */

/* CRO 0x3910..0x3944. The exported symbol
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` lands at 0x3944 -- the
 * symbol is therefore a mid-function offset. */
static void shinka_demo_set_is_call_draw(ShinkaDemoProc *self, int flag);

/* --- nnroControlObject_ entry --- */

/* CRO 0x39f8..0x3a4c. The exported symbol `nnroControlObject_` lands
 * at 0x3a1c which is `ldrh r2, [r2, #8]` -- the symbol is therefore
 * a mid-function offset. The frame reads r5->field_08 (counter),
 * ldrh [r4+8]/[r4+0x1c] then dispatches to thunk 0x800 (likely
 * sequence-step). */
static void *shinka_demo_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}