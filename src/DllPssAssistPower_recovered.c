/*
 * Preliminary decompilation of DllPssAssistPower.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 1 named symbol `nnroControlObject_` at 0x2eac
 *   - import table: 126 anonymous entries from |static| at 0x5730
 *   - ~45 function boundaries identified by ARM push/pop prologues
 *   - ~141 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *     (the player state struct is large: extends past +0x19e)
 *   - the function at 0x180 is the very first code after the header
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export trick at 0x2eac (mid-function offset)
 *
 * Module summary: PSS (Pokemon Summary Screen) Assist Power selector
 * -- the option to use an ability in battle via the new "Assist Power"
 * feature (only usable on certain special stages).
 */

#include <stdint.h>

typedef struct PssAssistPowerProc PssAssistPowerProc;

/* Inferred from repeated [r4, #N] / [r5, #N] accesses. The struct has
 * a player-state byte at +0x19c, an ability-id byte at +0x19d, and
 * a target pointer at +0x9c. */
struct PssAssistPowerProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 */
    void *field_1c;        /* 0x1c */
    void *field_20;        /* 0x20 */
    uint8_t state;         /* 0x24 */
    uint8_t sub_state;     /* 0x25 */
    uint16_t parameter;    /* 0x26 */
    int32_t timer;         /* 0x28 */
    uint8_t reserved2c[0x60]; /* 0x2c..0x8b */
    void *field_8c;        /* 0x8c */
    uint8_t reserved90[0xc]; /* 0x90..0x9b */
    void *target_9c;       /* 0x9c (target pointer, read/written in nnro region) */
    uint8_t reserveda0[0xfc]; /* 0xa0..0x19b */
    uint8_t player_state;  /* 0x19c (read in 0x2ee4) */
    uint8_t ability_id;    /* 0x19d (read in 0x2efc, +1 then mask 0xff) */
    uint8_t byte_19e;      /* 0x19e (cleared to 0 in nnro region) */
};

/* CRO 0x180..0x650. Three-register helper -- first code after the header.
 *   Calls thunks 0x188/0x190/0x198..0x1a8. Note: this function has
 *   access to the jump table thunks directly without going through the
 *   nnro control object. */
/* CRO 0x650..0x7f8. Three-register helper. */
/* CRO 0x7f8..0x940. Five-register helper. */
/* CRO 0x940..0x9a4. Two-register helper. */
/* CRO 0x9a4..0xaa0. Five-register helper. */
/* CRO 0xaa0..0xb54. Three-register helper. */
/* CRO 0xb54..0xb8c. Two-register helper. */
/* CRO 0xb8c..0xbc0. Two-register helper. */
/* CRO 0xbc0..0xbf0. Three-register helper. */
/* CRO 0xbf0..0xc48. Two-register helper. */
/* CRO 0xc48..0xd18. Three-register helper. */
/* CRO 0xd18..0xd6c. Four-register + dummy frame helper. */
/* CRO 0xd6c..0xda4. Two-register helper. */
/* CRO 0xda4..0xdd8. Two-register helper. */
/* CRO 0xdd8..0xdec. Two-register helper. */
/* CRO 0xdec..0xe4c. Two-register helper. */
/* CRO 0xe4c..0xe94. Two-register helper. */
/* CRO 0xe94..0xf1c. Three-register helper. */
/* CRO 0xf1c..0x106c. Three-register helper. */
/* CRO 0x106c..0x11f4. Five-register helper. */
/* CRO 0x11f4..0x16c4. Ten-register + fp helper (push {r4-r10,fp,lr}) --
 *   main update of the Assist-Power selector. */
/* CRO 0x16c4..0x1824. Five-register helper. */
/* CRO 0x1824..0x190c. Three-register helper. */
/* CRO 0x190c..0x1a24. Four-register helper. */
/* CRO 0x1a24..0x1bb4. Seven-register helper. */
/* CRO 0x1bb4..0x1ca8. Four-register + dummy frame helper. */
/* CRO 0x1ca8..0x1df8. Three-register helper. */
/* CRO 0x1df8..0x1fe0. Ten-register + fp helper. */
/* CRO 0x1fe0..0x20b4. Three-register helper. */
/* CRO 0x20b4..0x2140. Two-register helper. */
/* CRO 0x2140..0x225c. Five-register helper. */
/* CRO 0x225c..0x2388. Seven-register + dummy frame helper. */
/* CRO 0x2388..0x2524. Three-register helper. */
/* CRO 0x2524..0x2694. Three-register helper. */
/* CRO 0x2694..0x2afc. Ten-register + fp helper. */
/* CRO 0x2afc..0x2b94. Three-register helper. */
/* CRO 0x2b94..0x2c30. Three-register helper. */
/* CRO 0x2c30..0x2c68. Two-register helper. */
/* CRO 0x2c68..0x2cc4. Two-register helper. */
/* CRO 0x2cc4..0x2d24. Two-register helper. */
/* CRO 0x2d24..0x2d7c. Two-register helper. */
/* CRO 0x2d7c..0x2dfc. Two-register helper. */
/* CRO 0x2dfc..0x2ed0. Three-register helper. */
/* CRO 0x2ed0..0x3034. Five-register helper -- the ability-applier
 *   helper at the bottom of the module. Reads r3 (cmn r3, #1 -- check
 *   for the "no target" sentinel), then r4-0x7c / r5-r4, calls thunks
 *   0x468/0x490/0x418 to apply the ability, returns. */
/* CRO 0x3034..0x30e0. Two-register helper. */

/* --- nnroControlObject_ entry --- */

/* CRO 0x2e88..0x2ec4. The exported symbol `nnroControlObject_` lands
 * at 0x2eac which is `beq 0x2ec4` -- the symbol is therefore a mid-
 * function offset. The frame reads self->target_9c, dispatches on
 * (target == 0); if non-zero calls thunks 0x388/0x380 and clears
 * target; then clears self->byte_19e and tail-branches to 0x2e58. */
static void *pss_assist_power_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}