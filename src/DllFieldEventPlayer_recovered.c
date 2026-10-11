/*
 * Preliminary decompilation of DllFieldEventPlayer.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 is
 * segment 0 / 0). This file is intentionally not wired into a build yet:
 * imported services, the ROM/heap layout, and the exact CRO linker
 * relocations still need to be recovered.
 *
 * Recovered:
 *   - export table: 2 named symbols
 *       nnroControlObject_                                @ 0x3b50
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb         @ 0x3a80
 *   - import table: 71 anonymous entries from |static| at 0x5710,
 *                    30 anonymous entries from DllField at 0x5948
 *   - ~44 function boundaries identified by ARM push/pop prologues
 *   - ~132 external patch entries (relocations applied at load time)
 *   - struct field offsets inferred from ldr/str base+disp accesses
 *
 * Not recovered:
 *   - the vtable layout produced by nnroControlObject_
 *   - the meaning of the imported relocation slots
 *   - the in-function export tricks at 0x3a80 / 0x3b50
 *
 * Module summary: Field event player -- drives scripted field events
 * (camera/actor control during cutscenes and trigger-based sequences).
 */

#include <stdint.h>

typedef struct FieldEventPlayerProc FieldEventPlayerProc;

/* Inferred from repeated [r4, #N] / [r5, #N] / [r6, #N] accesses. */
struct FieldEventPlayerProc {
    void *vtable;          /* 0x00 */
    void *field_04;        /* 0x04 */
    void *field_08;        /* 0x08 */
    void *field_0c;        /* 0x0c */
    void *field_10;        /* 0x10 */
    void *field_14;        /* 0x14 */
    void *field_18;        /* 0x18 (work / counter incremented in 0x3b98/0x3bbc) */
    void *field_1c;        /* 0x1c (state struct, accessed heavily) */
    uint8_t reserved20[4]; /* 0x20..0x23 */
    void *field_24;        /* 0x24 */
    uint8_t reserved28[4]; /* 0x28..0x2b */
    uint8_t state;         /* 0x2c */
    uint8_t reserved2d[3];
};

/* CRO 0x4ac..0x504. Four-register + dummy frame helper (push {r3,r4,r5,lr}). */
/* CRO 0x504..0x610. Three-register helper. */
/* CRO 0x610..0x63c. Two-register helper. */
/* CRO 0x63c..0x738. Three-register helper. */
/* CRO 0x738..0x74c. Two-register helper. */
/* CRO 0x74c..0x78c. Three-register helper. */
/* CRO 0x78c..0x888. Three-register helper. */
/* CRO 0x888..0x8b8. Two-register helper. */
/* CRO 0x8b8..0x940. Two-register helper. */
/* CRO 0x940..0x990. Two-register helper. */
/* CRO 0x990..0xb34. Six-register helper. */
/* CRO 0xb34..0xb48. Two-register helper. */
/* CRO 0xb48..0xb88. Three-register helper. */
/* CRO 0xb88..0xc64. Five-register helper. */
/* CRO 0xc64..0xc94. Two-register helper. */
/* CRO 0xc94..0xf38. Five-register helper. */
/* CRO 0xf38..0xf64. Two-register helper. */
/* CRO 0xf64..0x1088. Three-register helper. */
/* CRO 0x1088..0x10b8. Two-register helper. */
/* CRO 0x10b8..0x1150. Three-register helper. */
/* CRO 0x1150..0x1178. Two-register helper. */
/* CRO 0x1178..0x118c. Two-register helper. */
/* CRO 0x118c..0x11a0. Two-register helper. */
/* CRO 0x11a0..0x1470. Six-register helper. */
/* CRO 0x1470..0x149c. Two-register helper. */
/* CRO 0x149c..0x1538. Three-register helper. */
/* CRO 0x1538..0x1570. Two-register helper. */
/* CRO 0x1570..0x1584. Two-register helper. */
/* CRO 0x1584..0x2468. Ten-register + fp helper (push {r4-r10,fp,lr}) --
 *   the largest function in this module. Drives the event-player
 *   state machine: dispatches on r5->state (==0/1/2/...), polls
 *   thunks 0x190/0x198/0x1a0/0x1a8/0x1b0, and calls the actor/camera
 *   helpers 0x11a0/0x990/0xc94 via vtable lookup. */
/* CRO 0x2468..0x247c. Two-register helper. */
/* CRO 0x247c..0x24ac. Two-register helper. */
/* CRO 0x24ac..0x25a0. Three-register helper. */
/* CRO 0x25a0..0x25b4. Two-register helper. */
/* CRO 0x25b4..0x2db0. 12-register full-context helper
 *   (push {r0,r1,r2,r3,r4-r10,fp,lr}). Saves every caller-saved
 *   register before invoking one of the field API thunks 0x1c8/0x1d0. */
/* CRO 0x2db0..0x2dc4. Two-register helper. */
/* CRO 0x2dc4..0x2dec. Two-register helper. */
/* CRO 0x2dec..0x3960. Seven-register helper. */
/* CRO 0x3960..0x3974. Two-register helper. */
/* CRO 0x3974..0x39c0. Three-register helper. */
/* CRO 0x39c0..0x3abc. Three-register helper. */
/* CRO 0x3abc..0x3ae8. Two-register helper. */
/* CRO 0x3ae8..0x3bec. Three-register helper. */
/* CRO 0x3bec..0x3cd8. Two-register helper. */
/* CRO 0x3cd8..0x3d50. Two-register helper. */

/* --- C++ mangled export --- */

/* CRO 0x3a4c..0x3a80. The exported symbol
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` lands at 0x3a80 -- the
 * symbol is therefore a mid-function offset. The frame stores a flag
 * (mov r1, #0x40000000) then calls thunks 0x2f8 / 0x3f8 to update the
 * background-system call-draw flag. */
static void field_event_player_set_is_call_draw(FieldEventPlayerProc *self,
                                                int flag);

/* --- nnroControlObject_ entry --- */

/* CRO 0x3b30..0x3bd4. The exported symbol `nnroControlObject_` lands
 * at 0x3b50 which is `cmp r0, #1` -- the symbol is therefore a mid-
 * function offset. The frame polls child->state (+0x24 == 1), dispatches
 * thunk 0x200 if state==1, then increments self->field_18 (counter). */
static void *field_event_player_nnro_control(void *loader_arg) {
    /* TODO: not yet decoded */
    (void)loader_arg;
    return 0;
}