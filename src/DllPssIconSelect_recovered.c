/*
 * Preliminary decompilation of DllPssIconSelect.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 2 named symbols
 *       nnroControlObject_                                @ 0x2f18
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb         @ 0x2d58
 *   - import table: 134 anonymous entries from |static| at 0x575c
 *   - ~41 function boundaries identified by ARM push/pop prologues
 *   - ~140 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export tricks at 0x2d58 / 0x2f18
 *
 * Module summary: PSS (Pokemon Summary Screen) icon selector -- the
 * UI control that lets the player pick a Pokemon in the party from an
 * icon grid.
 */

#include <stdint.h>

typedef struct PssIconSelectProc PssIconSelectProc;

/* Inferred from repeated [r4, #N] / [r5, #N] / [r6, #N] accesses. */
struct PssIconSelectProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 */
    void *field_1c;        /* 0x1c */
    uint8_t state;         /* 0x24 */
    uint8_t sub_state;     /* 0x25 */
    uint16_t parameter;    /* 0x26 */
    int32_t timer;         /* 0x28 */
    uint8_t reserved2c[0x2c]; /* 0x2c..0x57 */
    void *field_58;        /* 0x58 */
    void *field_5c;        /* 0x5c */
    void *field_74;        /* 0x74 */
    void *field_7c;         /* 0x7c */
};

/* CRO 0x55c..0x598. Three-register helper. */
/* CRO 0x598..0x64c. Five-register helper. */
/* CRO 0x64c..0x6e0. Two-register helper. */
/* CRO 0x6e0..0x7f8. Five-register helper. */
/* CRO 0x7f8..0x9b8. Five-register helper. */
/* CRO 0x9b8..0xc00. Six-register helper. */
/* CRO 0xc00..0xe28. Eleven-register + ip + fp helper -- main constructor
 *   for the icon-selector (allocates 0x80-byte child via thunk 0x1a0,
 *   attaches via thunks 0x1a8..0x1d8). */
/* CRO 0xe28..0xeec. Five-register helper. */
/* CRO 0xeec..0xf98. Two-register helper. */
/* CRO 0xf98..0xfcc. Two-register helper. */
/* CRO 0xfcc..0x1004. Two-register helper. */
/* CRO 0x1004..0x10a0. Three-register helper. */
/* CRO 0x10a0..0x11b8. Five-register helper. */
/* CRO 0x11b8..0x13ac. Ten-register + fp helper. */
/* CRO 0x13ac..0x14bc. Five-register + dummy frame helper. */
/* CRO 0x14bc..0x1768. Five-register + dummy frame helper -- large
 *   state-machine update; reads self->state (+0x24), calls thunks
 *   0x1c0/0x1c8/0x1d0 in the body. */
/* CRO 0x1768..0x17ec. Three-register helper. */
/* CRO 0x17ec..0x18b8. Three-register helper. */
/* CRO 0x18b8..0x1cfc. Five-register + dummy frame helper -- large
 *   draw/input worker. */
/* CRO 0x1cfc..0x1d88. Two-register helper. */
/* CRO 0x1d88..0x1e40. Four-register helper. */
/* CRO 0x1e40..0x1ed4. Two-register helper. */
/* CRO 0x1ed4..0x2218. Seven-register helper. */
/* CRO 0x2218..0x2228. Two-register helper. */
/* CRO 0x2228..0x230c. Five-register helper. */
/* CRO 0x230c..0x2400. Three-register helper. */
/* CRO 0x2400..0x250c. Two-register helper. */
/* CRO 0x250c..0x25e0. Eleven-register + ip + fp helper -- VFP draw
 *   routine. */
/* CRO 0x25e0..0x296c. Ten-register + fp helper -- large VFP draw. */
/* CRO 0x296c..0x2a7c. Eleven-register + ip + fp helper. */
/* CRO 0x2a7c..0x2b80. Five-register helper. */
/* CRO 0x2b80..0x2bc8. Three-register helper. */
/* CRO 0x2bc8..0x2c00. Two-register helper. */
/* CRO 0x2c00..0x2c58. Two-register helper. */
/* CRO 0x2c58..0x2d10. Five-register + dummy frame helper. */
/* CRO 0x2d10..0x2d48. Two-register helper. */
/* CRO 0x2d48..0x2e6c. Two-register helper. */
/* CRO 0x2e6c..0x2ea4. Two-register helper. */
/* CRO 0x2ea4..0x2f08. Two-register helper. */
/* CRO 0x2f08..0x30a0. Three-register helper. */
/* CRO 0x30a0..0x30e0. Two-register helper. */

/* --- C++ mangled export --- */

/* CRO 0x2d28..0x2d58. The exported symbol
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` lands at 0x2d58 -- the
 * symbol is therefore a mid-function offset. The frame writes the
 * flag value to the background-system control structure. */
static void pss_icon_select_set_is_call_draw(PssIconSelectProc *self, int flag);

/* --- nnroControlObject_ entry --- */

/* CRO 0x2ee0..0x2f50. The exported symbol `nnroControlObject_` lands
 * at 0x2f18 -- the symbol is therefore a mid-function offset. The
 * frame stores the vtable pointer and clears self->field_14. */
static void *pss_icon_select_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}