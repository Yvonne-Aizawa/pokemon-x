/*
 * Preliminary decompilation of DllConfig.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 1 named symbol `nnroControlObject_` at 0x3ce4
 *   - import table: 144 anonymous entries from |static| at 0x57ac
 *   - ~47 function boundaries identified by ARM push/pop prologues
 *   - ~152 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *     (the state byte is at +0x2c, large work area extends past +0x1b0)
 *   - VFP register usage is heavy (vmov.f32 / vstmia / vldr.f32)
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots (likely heap, log,
 *     resource loader, config-storage helpers)
 *   - the in-function export trick at 0x3ce4 (vfp vector initialiser)
 */

#include <stdint.h>

typedef struct ConfigProc ConfigProc;
typedef struct ConfigWork ConfigWork;

/* Inferred from repeated [r4, #N] / [r5, #N] accesses across the state
 * machine and constructors. */
struct ConfigProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 (work ptr, loaded as r4 in many helpers) */
    void *field_1c;        /* 0x1c */
    uint8_t state;         /* 0x2c (byte, dispatched in 0x5b8) */
    uint8_t reserved2d[3];
    uint8_t reserved30[0x10]; /* 0x30..0x3f */
    uint16_t field_40;     /* 0x40 (mask check in 0x414) */
    uint8_t reserved42[0x1a6]; /* 0x42..0x1e7 */
    void *child_1a8;       /* 0x1a8 (read in 0x620) */
    void *child_1ac;       /* 0x1ac (read in 0x610, 0x62c) */
    uint8_t reserved1b0[0x10]; /* 0x1b0..0x1bf */
    void *field_1c0;
    void *field_1c4;
};

/* CRO 0x5b8..0x5ec. Primary state machine update (3-register frame).
 *   - reads self->state (+0x2c) and dispatches:
 *       == 0 -> init branch 0x5f0 (calls thunks 0x188, 0x190, 0x198, 0x1a0,
 *               populating child_1a8/child_1ac with r2=0x49 / 0x0a immediates)
 *       == 1 -> branch 0x664 (continues state-1 work)
 *       default -> branch 0x5d8: calls thunk 0x180 with r0=r1=r2=0,
 *                 returns 1
 */
static int config_update(ConfigProc *self);

/* CRO 0x6d4..0xfac. Heavy 10-register + VFP constructor.
 *   - Sets up r4 = self, r5..r10 = parameter registers
 *   - Pushes 10 registers and a large stack frame
 *   - Calls multiple thunks to populate fields and child objects
 *   - Uses VFP math (vpush d8-d12, vldr/vmov, vstmia) for projection
 *     matrices / camera transforms typical of a settings UI */

/* CRO 0x1434..0x1578. Three-register helper (pop {r4-r6,pc}). */
/* CRO 0x1578..0x15e8. Two-register helper. */
/* CRO 0x15e8..0x164c. Two-register helper. */
/* CRO 0x164c..0x1778. Three-register helper. */
/* CRO 0x1778..0x18fc. Six-register helper. */
/* CRO 0x18fc..0x1a44. Seven-register + dummy frame helper. */
/* CRO 0x1a44..0x1ce8. 11-register with r0-r2 saved + VFP helper. */
/* CRO 0x1ce8..0x1d0c. Two-register helper. */
/* CRO 0x1d0c..0x1ddc. Five-register + dummy frame helper. */
/* CRO 0x1ddc..0x1f7c. Seven-register + dummy frame helper. */
/* CRO 0x1f7c..0x1fe8. Two-register helper. */
/* CRO 0x1fe8..0x20b0. Three-register helper. */
/* CRO 0x20b0..0x2230. Five-register + dummy frame helper. */
/* CRO 0x2230..0x2304. Three-register helper. */
/* CRO 0x2304..0x2888. Eight-register + VFP helper. */
/* CRO 0x2888..0x2a88. Four-register + dummy frame helper (heavy VFP). */
/* CRO 0x2a88..0x2a98. Two-register helper. */
/* CRO 0x2a98..0x2bd4. Five-register helper. */
/* CRO 0x2bd4..0x2d9c. Four-register helper. */
/* CRO 0x2d9c..0x2ef8. Seven-register + dummy frame helper. */
/* CRO 0x2ef8..0x2f50. Five-register + dummy frame helper. */
/* CRO 0x2f50..0x30cc. Seven-register + VFP helper. */
/* CRO 0x30cc..0x313c. Two-register helper. */
/* CRO 0x313c..0x31d8. Two-register helper. */
/* CRO 0x31d8..0x3264. Two-register helper. */
/* CRO 0x3264..0x32ec. Two-register helper. */
/* CRO 0x32ec..0x33fc. Two-register helper. */
/* CRO 0x33fc..0x3678. Five-register helper. */
/* CRO 0x3678..0x3788. Three-register helper. */
/* CRO 0x3788..0x37d0. Two-register helper. */
/* CRO 0x37d0..0x3934. Four-register + dummy frame helper. */
/* CRO 0x3934..0x398c. Two-register helper. */
/* CRO 0x398c..0x39cc. Two-register helper. */
/* CRO 0x39cc..0x3a08. Two-register helper. */
/* CRO 0x3a08..0x3a40. Two-register helper. */
/* CRO 0x3a40..0x3a80. Two-register helper. */
/* CRO 0x3a80..0x3ae8. Two-register helper. */
/* CRO 0x3ae8..0x3b48. Two-register helper. */
/* CRO 0x3b48..0x3b84. Two-register helper. */
/* CRO 0x3b84..0x3bc0. Two-register helper. */
/* CRO 0x3bc0..0x3c34. Two-register helper. */
/* CRO 0x3c34..0x3ca0. Two-register helper. */
/* CRO 0x3ca0..0x3ce0. Two-register helper. */

/* --- nnroControlObject_ entry --- */

/* CRO 0x2cb0..0x3d20. Vector initialiser with VFP constants.
 *   - vmov.f32 s0..s2, then vstmia [r0, #0x2c] {s0-s2} (writes a 12-byte
 *     transformation block at r0+0x2c).
 *   - The exported symbol `nnroControlObject_` lands at 0x3ce4 which is
 *     `ldr r1, [pc, #356]@0x3e50` -- the symbol is therefore a mid-function
 *     offset inside this vector-init/const-fold frame; the frame likely
 *     bootstraps a default 4x3 transform table at runtime. */
static void *config_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}

/* CRO 0x3e6c..0x3f48. Two-register tail helper (post-nnro glue). */