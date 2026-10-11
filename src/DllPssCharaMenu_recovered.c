/*
 * Preliminary decompilation of DllPssCharaMenu.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 2 named symbols
 *       nnroControlObject_                                @ 0x3090
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb         @ 0x2f88
 *   - import table: 156 anonymous entries from |static| at 0x5854
 *   - ~43 function boundaries identified by ARM push/pop prologues
 *   - ~161 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export tricks at 0x2f88 / 0x3090
 *
 * Module summary: PSS (Pokemon Summary Screen) character menu -- the
 * submenu inside the PSS that lets the player view moves, EVs/IVs, etc.
 */

#include <stdint.h>

typedef struct PssCharaMenuProc PssCharaMenuProc;

/* Inferred from repeated [r4, #N] / [r5, #N] / [r6, #N] accesses. */
struct PssCharaMenuProc {
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

/* CRO 0x5f8..0x790. Six-register helper. */
/* CRO 0x790..0xa68. Four-register helper. */
/* CRO 0xa68..0xab8. Three-register helper. */
/* CRO 0xab8..0xb70. Three-register helper. */
/* CRO 0xb70..0xc34. Three-register helper. */
/* CRO 0xc34..0xca0. Two-register helper. */
/* CRO 0xca0..0xd14. Two-register helper. */
/* CRO 0xd14..0xd70. Two-register helper. */
/* CRO 0xd70..0xe20. Three-register helper. */
/* CRO 0xe20..0xe7c. Two-register helper. */
/* CRO 0xe7c..0xf70. Three-register helper. */
/* CRO 0xf70..0xf98. Two-register helper. */
/* CRO 0xf98..0xfc4. Two-register helper. */
/* CRO 0xfc4..0x1184. Five-register helper. */
/* CRO 0x1184..0x1384. Five-register helper. */
/* CRO 0x1384..0x14b0. Three-register helper. */
/* CRO 0x14b0..0x15a4. Four-register helper. */
/* CRO 0x15a4..0x15cc. Two-register helper. */
/* CRO 0x15cc..0x1738. Three-register helper. */
/* CRO 0x1738..0x178c. lr-only helper (push {lr}). */
/* CRO 0x178c..0x1914. Six-register helper. */
/* CRO 0x1914..0x1e20. Ten-register + fp helper -- main update of the
 *   character menu. Reads self->state, calls thunks 0x190..0x1d8 in
 *   a long sequence that drives the menu navigation logic. */
/* CRO 0x1e20..0x1ed4. Five-register helper. */
/* CRO 0x1ed4..0x1f58. Three-register helper. */
/* CRO 0x1f58..0x1fc0. Three-register helper. */
/* CRO 0x1fc0..0x209c. Three-register helper. */
/* CRO 0x209c..0x2198. Three-register helper. */
/* CRO 0x2198..0x2288. Five-register helper. */
/* CRO 0x2288..0x23e8. Three-register helper. */
/* CRO 0x23e8..0x2704. Five-register helper. */
/* CRO 0x2704..0x283c. Three-register helper. */
/* CRO 0x283c..0x2cdc. 12-register full-context helper -- heavy VFP
 *   draw routine. */
/* CRO 0x2cdc..0x2d9c. Three-register helper. */
/* CRO 0x2d9c..0x2e4c. Three-register helper. */
/* CRO 0x2e4c..0x2e94. Three-register helper. */
/* CRO 0x2e94..0x2ecc. Two-register helper. */
/* CRO 0x2ecc..0x2f40. Two-register helper. */
/* CRO 0x2f40..0x3028. Five-register + dummy frame helper. */
/* CRO 0x3028..0x3060. Two-register helper. */
/* CRO 0x3060..0x309c. Two-register helper. */
/* CRO 0x309c..0x30d4. Two-register helper. */
/* CRO 0x30d4..0x3218. Two-register helper. */

/* --- C++ mangled export --- */

/* CRO 0x2f20..0x2f88. The exported symbol
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` lands at 0x2f88 -- the
 * symbol is therefore a mid-function offset. The frame stores the flag
 * value via thunk 0x1b0, then advances the state machine. */
static void pss_chara_menu_set_is_call_draw(PssCharaMenuProc *self, int flag);

/* --- nnroControlObject_ entry --- */

/* CRO 0x3058..0x30e0. The exported symbol `nnroControlObject_` lands
 * at 0x3090 -- the symbol is therefore a mid-function offset. The
 * frame stores the vtable pointer and clears self->field_14, then
 * tail-calls into the constructor glue. */
static void *pss_chara_menu_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}