/*
 * Preliminary decompilation of DllReport.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 2 named symbols
 *       nnroControlObject_                                @ 0x2ff4
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb         @ 0x2f1c
 *   - import table: 193 anonymous entries from |static| at 0x5a0c
 *   - ~47 function boundaries identified by ARM push/pop prologues
 *   - ~198 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export tricks at 0x2f1c / 0x2ff4
 *
 * Module summary: Report screen -- the post-battle / pokedex report UI
 * ("Pokemon Report", an end-of-area summary that shows caught Pokemon,
 * number of steps, etc.).
 */

#include <stdint.h>

typedef struct ReportProc ReportProc;

/* Inferred from repeated [r4, #N] / [r5, #N] / [r6, #N] accesses. */
struct ReportProc {
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

/* CRO 0x728..0x744. Two-register helper. */
/* CRO 0x744..0x80c. Three-register helper. */
/* CRO 0x80c..0x954. Five-register helper. */
/* CRO 0x954..0xabc. Three-register helper. */
/* CRO 0xabc..0xcec. Six-register helper. */
/* CRO 0xcec..0xd00. Two-register helper. */
/* CRO 0xd00..0xecc. Seven-register + dummy frame helper -- large
 *   constructor. */
/* CRO 0xecc..0xf74. Five-register + dummy frame helper. */
/* CRO 0xf74..0xfec. Two-register helper. */
/* CRO 0xfec..0x1070. Four-register + dummy frame helper. */
/* CRO 0x1070..0x1264. Six-register helper. */
/* CRO 0x1264..0x12f8. Two-register helper. */
/* CRO 0x12f8..0x1390. Five-register + dummy frame helper. */
/* CRO 0x1390..0x145c. Five-register + dummy frame helper. */
/* CRO 0x145c..0x15ec. Ten-register + fp helper -- main constructor for
 *   the report (allocates 0x80-byte child via thunk 0x1a0, attaches
 *   via thunks 0x1a8..0x1d8). */
/* CRO 0x15ec..0x17ec. Five-register helper. */
/* CRO 0x17ec..0x1978. Three-register helper. */
/* CRO 0x1978..0x19f8. Three-register helper. */
/* CRO 0x19f8..0x1aec. Ten-register + fp helper -- main update state
 *   machine; reads self->state, calls thunks 0x1d0..0x1f8. */
/* CRO 0x1aec..0x1cc0. Five-register helper. */
/* CRO 0x1cc0..0x1dbc. Three-register helper. */
/* CRO 0x1dbc..0x1f70. Five-register + dummy frame helper. */
/* CRO 0x1f70..0x20c4. Ten-register + fp helper. */
/* CRO 0x20c4..0x21a0. Four-register + dummy frame helper. */
/* CRO 0x21a0..0x2240. Five-register helper. */
/* CRO 0x2240..0x2288. Four-register + dummy frame helper. */
/* CRO 0x2288..0x2308. Three-register helper. */
/* CRO 0x2308..0x2394. Three-register helper. */
/* CRO 0x2394..0x23f8. Two-register helper. */
/* CRO 0x23f8..0x24c8. Two-register helper. */
/* CRO 0x24c8..0x24f0. Two-register helper. */
/* CRO 0x24f0..0x251c. Two-register helper. */
/* CRO 0x251c..0x29cc. Ten-register + fp helper -- large VFP draw
 *   routine. */
/* CRO 0x29cc..0x2a28. Two-register helper. */
/* CRO 0x2a28..0x2a64. Two-register helper. */
/* CRO 0x2a64..0x2c30. Ten-register + fp helper. */
/* CRO 0x2c30..0x2c80. Two-register helper. */
/* CRO 0x2c80..0x2cd0. Two-register helper. */
/* CRO 0x2cd0..0x2d70. Three-register helper. */
/* CRO 0x2d70..0x2e4c. Six-register helper. */
/* CRO 0x2e4c..0x2f10. Two-register helper. */
/* CRO 0x2f10..0x2f50. Three-register helper. */
/* CRO 0x2f50..0x2fb0. Two-register helper. */
/* CRO 0x2fb0..0x300c. Two-register helper. */
/* CRO 0x300c..0x3044. Two-register helper. */
/* CRO 0x3044..0x317c. Two-register helper. */

/* --- C++ mangled export --- */

/* CRO 0x2ee0..0x2f1c. The exported symbol
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` lands at 0x2f1c -- the
 * symbol is therefore a mid-function offset. */
static void report_set_is_call_draw(ReportProc *self, int flag);

/* --- nnroControlObject_ entry --- */

/* CRO 0x2fd0..0x3050. The exported symbol `nnroControlObject_` lands
 * at 0x2ff4 -- the symbol is therefore a mid-function offset. The
 * frame stores the vtable pointer and clears self->field_14. */
static void *report_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}