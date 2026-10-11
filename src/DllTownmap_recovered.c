/*
 * Preliminary decompilation of DllTownmap.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 1 named symbol `nnroControlObject_` at 0x34bc
 *   - import table: 101 anonymous entries from |static| at 0x5608
 *   - ~60 function boundaries identified by ARM push/pop prologues
 *   - ~117 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *   - Heavy VFP usage confirmed (vldr.f32 / vstmia / vmov.f32 /
 *     vcmp / vmrs APSR)
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export trick at 0x34bc (mid-function mov)
 *
 * Module summary: Townmap -- the region map UI that lets the player
 * teleport / fly to discovered cities.
 */

#include <stdint.h>

typedef struct TownmapProc TownmapProc;

/* Inferred from repeated [r4, #N] / [r5, #N] / [r6, #N] accesses. */
struct TownmapProc {
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

/* CRO 0x46c..0x488. Two-register helper. */
/* CRO 0x488..0x498. Two-register helper. */
/* CRO 0x498..0x4fc. Three-register helper. */
/* CRO 0x4fc..0x5ac. Five-register helper. */
/* CRO 0x5ac..0x600. Three-register helper. */
/* CRO 0x600..0x970. Six-register helper -- large body. */
/* CRO 0x970..0xa34. Three-register helper. */
/* CRO 0xa34..0xaa4. Three-register helper. */
/* CRO 0xaa4..0xb2c. Three-register helper. */
/* CRO 0xb2c..0xbb0. Two-register helper. */
/* CRO 0xbb0..0xc9c. Five-register helper. */
/* CRO 0xc9c..0xd98. Two-register helper. */
/* CRO 0xd98..0x1000. Five-register helper. */
/* CRO 0x1000..0x10bc. Three-register helper. */
/* CRO 0x10bc..0x1168. Three-register helper. */
/* CRO 0x1168..0x1240. Three-register helper. */
/* CRO 0x1240..0x1260. Two-register helper. */
/* CRO 0x1260..0x1324. Five-register helper. */
/* CRO 0x1324..0x135c. Three-register helper. */
/* CRO 0x135c..0x13c0. Three-register helper. */
/* CRO 0x13c0..0x142c. Three-register helper. */
/* CRO 0x142c..0x1498. Three-register helper. */
/* CRO 0x1498..0x1554. Three-register helper. */
/* CRO 0x1554..0x1630. Four-register helper. */
/* CRO 0x1630..0x1684. Five-register + dummy frame helper. */
/* CRO 0x1684..0x16d0. Two-register helper. */
/* CRO 0x16d0..0x1800. Ten-register + fp helper -- main constructor for
 *   the townmap (allocates a 0x80-byte child via thunk 0x1a0, attaches
 *   via thunks 0x1a8..0x1d8). */
/* CRO 0x1800..0x191c. Two-register helper. */
/* CRO 0x191c..0x1b5c. Five-register helper. */
/* CRO 0x1b5c..0x1c30. Seven-register + dummy frame helper. */
/* CRO 0x1c30..0x1ecc. Ten-register + fp helper -- main update state
 *   machine; reads self->state, calls thunks 0x1d0..0x1f8. */
/* CRO 0x1ecc..0x1f94. Three-register helper. */
/* CRO 0x1f94..0x212c. Seven-register + dummy frame helper. */
/* CRO 0x212c..0x2174. Two-register helper. */
/* CRO 0x2174..0x21fc. Two-register helper. */
/* CRO 0x21fc..0x2374. Two-register helper. */
/* CRO 0x2374..0x23ec. Two-register helper. */
/* CRO 0x23ec..0x24e4. Three-register helper. */
/* CRO 0x24e4..0x2534. Four-register + dummy frame helper. */
/* CRO 0x2534..0x26d0. Four-register helper. */
/* CRO 0x26d0..0x28f0. Five-register helper. */
/* CRO 0x28f0..0x2930. Four-register + dummy frame helper. */
/* CRO 0x2930..0x2958. Three-register helper. */
/* CRO 0x2958..0x2998. Two-register helper. */
/* CRO 0x2998..0x2b08. Three-register helper. */
/* CRO 0x2b08..0x2dd4. Ten-register + fp helper -- large VFP draw
 *   routine. */
/* CRO 0x2dd4..0x2e6c. Three-register helper. */
/* CRO 0x2e6c..0x2ec8. Five-register helper. */
/* CRO 0x2ec8..0x2eec. Two-register helper. */
/* CRO 0x2eec..0x3014. Two-register helper. */
/* CRO 0x3014..0x3174. Five-register helper. */
/* CRO 0x3174..0x31a0. Two-register helper. */
/* CRO 0x31a0..0x31d4. Two-register helper. */
/* CRO 0x31d4..0x320c. Two-register helper. */
/* CRO 0x320c..0x3350. Two-register helper. */
/* CRO 0x3350..0x3398. Three-register helper. */
/* CRO 0x3398..0x3464. Two-register helper. */
/* CRO 0x3464..0x3570. Three-register helper. */
/* CRO 0x3570..0x3644. Two-register helper. */
/* CRO 0x3644..0x3680. Two-register helper. */

/* --- nnroControlObject_ entry --- */

/* CRO 0x349c..0x3550. The exported symbol `nnroControlObject_` lands
 * at 0x34bc which is `mov r0, r5` -- the symbol is therefore a mid-
 * function offset. The frame is the scroll/zoom update of the map:
 * it polls thunk 0x3d8 (a flags callback), branches on flags & 1/2/4/8
 * to negate or move VFP regs (vnegne.f32 / vmovne.f32), compares
 * s16/s18 against s19 with vcmp + vmrs APSR, and on a match calls
 * thunk 0x1800 (likely a position-update or repaint helper). */
static void *townmap_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}