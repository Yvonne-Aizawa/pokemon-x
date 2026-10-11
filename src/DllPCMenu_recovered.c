/*
 * Preliminary decompilation of DllPCMenu.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 2 named symbols
 *       nnroControlObject_                                @ 0x320c
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb         @ 0x3124
 *   - import table: 128 anonymous entries from |static| at 0x56f4
 *   - ~49 function boundaries identified by ARM push/pop prologues
 *   - ~132 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export tricks at 0x3124 / 0x320c
 *
 * Module summary: PC (Pokemon Centre) menu UI -- the menu rendered
 * inside any Pokemon Centre for healing, shopping, the Global Terminal,
 * etc.
 */

#include <stdint.h>

typedef struct PCMenuProc PCMenuProc;

/* Inferred from repeated [r4, #N] / [r5, #N] / [r6, #N] accesses. */
struct PCMenuProc {
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
    void *field_7c;        /* 0x7c */
};

/* CRO 0x554..0x6b8. Five-register + dummy frame helper. */
/* CRO 0x6b8..0x6d4. Two-register helper. */
/* CRO 0x6d4..0xb94. Eleven-register + dummy frame helper -- main
 *   constructor (allocates 0x80-byte child object via thunk 0x1a0,
 *   attaches via thunks 0x1a8..0x1d8, populates vtable-derived +0x44
 *   into self->field_74). */
/* CRO 0xb94..0x1114. Five-register + dummy frame helper. */
/* CRO 0x1114..0x1390. Six-register helper. */
/* CRO 0x1390..0x14f8. Five-register + dummy frame helper. */
/* CRO 0x14f8..0x155c. Five-register helper. */
/* CRO 0x155c..0x1624. Three-register helper. */
/* CRO 0x1624..0x1684. Three-register helper. */
/* CRO 0x1684..0x16c4. Three-register helper. */
/* CRO 0x16c4..0x1728. Two-register helper. */
/* CRO 0x1728..0x1818. Four-register helper. */
/* CRO 0x1818..0x1928. Three-register helper. */
/* CRO 0x1928..0x194c. Two-register helper. */
/* CRO 0x194c..0x19a4. Three-register helper. */
/* CRO 0x19a4..0x1a1c. Three-register helper. */
/* CRO 0x1a1c..0x1b60. Seven-register + dummy frame helper. */
/* CRO 0x1b60..0x1c20. Five-register helper. */
/* CRO 0x1c20..0x1ce0. Five-register + dummy frame helper. */
/* CRO 0x1ce0..0x1d5c. Four-register + dummy frame helper. */
/* CRO 0x1d5c..0x1ebc. Six-register helper. */
/* CRO 0x1ebc..0x1f24. Five-register helper. */
/* CRO 0x1f24..0x1fdc. Ten-register + fp + dummy frame helper. */
/* CRO 0x1fdc..0x2018. Three-register helper. */
/* CRO 0x2018..0x2128. Three-register helper. */
/* CRO 0x2128..0x21b0. Three-register helper. */
/* CRO 0x21b0..0x2390. Six-register helper. */
/* CRO 0x2390..0x259c. Ten-register + fp + dummy frame helper. */
/* CRO 0x259c..0x26ac. Three-register helper. */
/* CRO 0x26ac..0x26f0. Two-register helper. */
/* CRO 0x26f0..0x2728. Three-register helper. */
/* CRO 0x2728..0x2814. Three-register helper. */
/* CRO 0x2814..0x2840. Two-register helper. */
/* CRO 0x2840..0x2920. Three-register helper. */
/* CRO 0x2920..0x296c. Two-register helper. */
/* CRO 0x296c..0x2b70. 11-register with r0/r1 saved helper. */
/* CRO 0x2b70..0x2c18. Two-register helper. */
/* CRO 0x2c18..0x2cc0. Two-register helper. */
/* CRO 0x2cc0..0x2dec. 12-register full-context helper. */
/* CRO 0x2dec..0x2f58. Five-register helper. */
/* CRO 0x2f58..0x2fb4. Two-register helper. */
/* CRO 0x2fb4..0x3078. Three-register helper. */
/* CRO 0x3078..0x30f8. Five-register + dummy frame helper. */
/* CRO 0x30f8..0x3160. Two-register helper. */
/* CRO 0x3160..0x31dc. Two-register helper. */
/* CRO 0x31dc..0x3238. Two-register helper. */
/* CRO 0x3238..0x3270. Two-register helper. */
/* CRO 0x3270..0x3394. Two-register helper. */

/* --- C++ mangled export --- */

/* CRO 0x30e8..0x3124. The exported symbol
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` lands at 0x3124 -- the
 * symbol is therefore a mid-function offset. The frame writes the
 * flag value to the background-system control structure. */
static void pcmenu_set_is_call_draw(PCMenuProc *self, int flag);

/* --- nnroControlObject_ entry --- */

/* CRO 0x31d4..0x3254. The exported symbol `nnroControlObject_` lands
 * at 0x320c -- the symbol is therefore a mid-function offset. The
 * frame sets up a child vtable and tail-calls into the constructor
 * glue at 0x3388. */
static void *pcmenu_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}