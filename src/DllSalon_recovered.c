/*
 * Preliminary decompilation of DllSalon.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the inner sub-system that
 * drives the salon's BG screen (large `Proc` ctor @ 0x500 uses a
 * 124-byte stack frame) depends on allocations that have not been
 * resolved against the live game.
 *
 * Module file: extracted/romfs/DllSalon.cro
 *   code region     0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0xf44
 *   segment 1 (THM) 0x1000 .. 0x11e8
 *   segment 2 (RO)  0x2410 .. 0x242c (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x20
 *   bss             0x24
 *   exports named   1 (`nnroControlObject_`, segment 0, +0xc7c)
 *   imports         73 anonymous entries from `|static|`
 *   external patches 0
 *
 * RTTI type names recovered from `.rodata`:
 *     "N3app5salon4ProcE"
 *     "N3gfl4proc11BaseProcessE"
 *
 * Behavioral summary:
 *   The Pokemon Salon menu where the player chooses a haircut for
 *   their lead Pokemon.  Same outer "Process" architecture as the
 *   rest of the app, with the addition of a vpush/vpop frame at
 *   CRO 0xab0 (`vpush {d8-d9}`) — the salon animation runs off
 *   double-precision vector math for the stylist camera.
 */

#include <stdint.h>
#include <stddef.h>

typedef struct SalonProc SalonProc;

/* Object layout inferred from the constructor at CRO 0x500 (which
 * subtracts `sp, #0x7c = 124` for the ctor frame) and the various
 * vtable dispatches.  Field-offset catalog:
 *   +0x20 — child inner Proc
 *   +0x24 — inner work (sized at +0x4c = 76 at CRO 0x570)
 *   +0x28 — link 1
 *   +0x30 — link 2 (loaded via ldrd r0, [r4, #48])
 *   +0x34 — link 3 (passed into bl 0x238)
 *   +0x40 — bg text overlay (vtable [0x38])
 *   +0x44 — DllField/animator handle (set by bl 0x230)
 *   +0x48 — main scene inner (r4 = self[0x48]+4 at CRO 0x3b4)
 *   +0x4c — string message id (CRO 0x570)
 *   +0x8c — backdrop resource id (Cro 0x574)
 */
struct SalonProc {
    void *vtable;
    uint8_t reserved04[0x1c];
    void *child_inner;        /* 0x20 */
    uint8_t work_24[0x4c - 0x24];
    void *link_28;            /* 0x28 */
    void *link_2c;            /* 0x2c */
    void *link_30[2];         /* 0x30..0x37 */
    void *link_34;            /* 0x34 */
    uint8_t reserved38[0x08];
    void *bg_overlay;         /* 0x40 */
    void *anim_handle;        /* 0x44 */
    void *scene_inner;        /* 0x48 */
    uint8_t reserved4c[0x40]; /* 0x4c..0x8b */
};

/* ---------- Internal forwarders -------------------------------------- */

extern int salon_import_0(int, ...);   /* 0x180 */
extern int salon_import_1(int, ...);   /* 0x188 */
extern int salon_import_2(int, ...);   /* 0x190 */
extern int salon_import_3(int, ...);   /* 0x198 */
extern int salon_import_4(int, ...);   /* 0x1a0 */
extern int salon_import_5(int, ...);   /* 0x1a8 */
extern int salon_import_6(int, ...);   /* 0x1b0 */
extern int salon_import_7(int, ...);   /* 0x1b8 */
extern int salon_import_8(int, ...);   /* 0x1c0 */
extern int salon_import_9(int, ...);   /* 0x1c8 */
extern int salon_import_10(int, ...);  /* 0x1d0 */
extern int salon_import_11(int, ...);  /* 0x1d8 */
extern int salon_import_12(int, ...);  /* 0x1e0 */
extern int salon_import_13(int, ...);  /* 0x1e8 */
extern int salon_import_14(int, ...);  /* 0x1f0 */
extern int salon_import_15(int, ...);  /* 0x1f8 */
extern int salon_import_16(int, ...);  /* 0x200 */
extern int salon_import_17(int, ...);  /* 0x208 */
extern int salon_import_18(int, ...);  /* 0x210 */
extern int salon_import_19(int, ...);  /* 0x218 */
extern int salon_import_20(int, ...);  /* 0x220 */
extern int salon_import_21(int, ...);  /* 0x228 */
extern int salon_import_22(int, ...);  /* 0x230 */
extern int salon_import_23(int, ...);  /* 0x238 */
extern int salon_import_24(int, ...);  /* 0x240 */
extern int salon_import_25(int, ...);  /* 0x248 */
extern int salon_import_26(int, ...);  /* 0x250 */
extern int salon_import_27(int, ...);  /* 0x258 */
extern int salon_import_28(int, ...);  /* 0x260 */
extern int salon_import_29(int, ...);  /* 0x268 */
extern int salon_import_30(int, ...);  /* 0x270 */
extern int salon_import_31(int, ...);  /* 0x278 */
extern int salon_import_32(int, ...);  /* 0x280 */
extern int salon_import_33(int, ...);  /* 0x288 */
extern int salon_import_34(int, ...);  /* 0x290 */
extern int salon_import_35(int, ...);  /* 0x298 */
extern int salon_import_36(int, ...);  /* 0x2a0 */
extern int salon_import_37(int, ...);  /* 0x2a8 */
extern int salon_import_38(int, ...);  /* 0x2b0 */
extern int salon_import_39(int, ...);  /* 0x2b8 */
extern int salon_import_40(int, ...);  /* 0x2c0 */
extern int salon_import_41(int, ...);  /* 0x2c8 */
extern int salon_import_42(int, ...);  /* 0x2d0 */
extern int salon_import_43(int, ...);  /* 0x2d8 */
extern int salon_import_44(int, ...);  /* 0x2e0 */
extern int salon_import_45(int, ...);  /* 0x2e8 */
extern int salon_import_46(int, ...);  /* 0x2f0 */
extern int salon_import_47(int, ...);  /* 0x2f8 */
extern int salon_import_48(int, ...);  /* 0x300 */
extern int salon_import_49(int, ...);  /* 0x308 */
extern int salon_import_50(int, ...);  /* 0x310 */
extern int salon_import_51(int, ...);  /* 0x318 */
extern int salon_import_52(int, ...);  /* 0x320 */
extern int salon_import_53(int, ...);  /* 0x328 */
extern int salon_import_54(int, ...);  /* 0x330 */
extern int salon_import_55(int, ...);  /* 0x338 */
extern int salon_import_56(int, ...);  /* 0x340 */
extern int salon_import_57(int, ...);  /* 0x348 */
extern int salon_import_58(int, ...);  /* 0x350 */
extern int salon_import_59(int, ...);  /* 0x358 */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x380 — CanRun helper: reads `[+0x48]`, `[+0x48]+4`, and uses
 * `bl 0xaa0` (the vpush-style inner anim call) to determine. */
static int Salon_can_run(SalonProc *self);

/* CRO 0x3a0 — main Exec: 5 phases:
 *   1. Read self->scene_inner (+0x48). If non-NULL:
 *        * read r4 = self->scene_inner + 4
 *        * ldrd r0, [r4, #40]
 *        * call slot 0x180, then slot 0x188 (error path)
 *   2. ldrd/strd pair (`+0x28/+0x2c`) clearing the inner state.
 *   3. Re-establish the inner state via slot 0x198.
 *   4. Step slot 0x1a0/0x1a8/0x1b0/0x1b8/0x1c0 in order.
 *   5. Final slot 0x1c8 to pop the bg panel.
 */
static int Salon_proc_exec(SalonProc *self);

/* CRO 0x4ac — secondary Exec: increments selected inner counters
 * (`+0x2c/+0x30/+0x38`) and pumps the bg via vtable `[+0x08]`. */
static int Salon_proc_inner_exec(SalonProc *self);

/* CRO 0x500 — Proc ctor.  Big one:
 *   * 22-byte alloc (`bl 0x210` -> 0x16)
 *   * 4MB-region alloc (`bl 0x218` -> {0,0,0,0x800} at +0x20)
 *   * 4MB-region alloc with `mov r2, #0x700000 ; mov r3, #234` at
 *     +0x24..+0x68 (`bl 0x220`)
 *   * calls `bl 0x228, 0x230, 0x238, 0x240` in series to set up the
 *     bg text/texture groups.
 *   * `mov r0, #76` (0x4c) final setup of message id.
 */
static SalonProc *SalonProc_ctor(SalonProc *self);

/* CRO 0x790, 0x7b4, 0x7fc — three small helpers. */
static int Salon_can_stop(void);
static int Salon_can_draw(void);
static int Salon_default_op(void);

/* CRO 0x83c — long inner Exec (registers r4..r9): steps through a
 * sequence that increments self->link_28 to step past each event
 * slot (`+0x28/+0x30/+0x38/+0x44`). */
static int Salon_proc_inner_long_exec(SalonProc *self);

/* CRO 0xaa0 — vector-math inner (`vpush {d8-d9}` followed by vldr/vstr
 * on d8/d9); updates the underlying scene renderer. */
static int salon_bg_anim_update(SalonProc *self);

/* CRO 0xd5c, 0xd94, 0xe04 — small allocators/stub init. */
static void *salon_alloc_a(size_t bytes);
static void *salon_alloc_b(size_t bytes);
static void *salon_alloc_c(size_t bytes);

/* ---------- Implementations (preliminary) ---------------------------- */

static int Salon_can_run(SalonProc *self) {
    return self->scene_inner
        ? salon_bg_anim_update(self)
        : 1;
}

static int Salon_proc_exec(SalonProc *self) {
    /* Phase 1: scene-inner check. */
    if (self->scene_inner) {
        void *inner = (char *)self->scene_inner + 4;
        uint64_t r0r1;
        /* ldrd r0, [r4, #40] (Cro 0x3b8).  Pointer pair into
         * the inner state struct. */
        r0r1 = *(uint64_t *)&((char *)inner)[40];
        if (salon_import_0((void *)(uintptr_t)r0r1) == 0) {
            uint32_t zero = 0;
            salon_import_1((void *)(uintptr_t)zero,
                           (void *)(uintptr_t)zero,
                           (void *)(uintptr_t)zero);
        }
    }
    /* Phase 2..5: walk slots 0x190, 0x198, 0x1a0, 0x1a8, 0x1b0,
     *             0x1b8, 0x1c0 in that order. */
    salon_import_2(0);
    salon_import_3(0);
    salon_import_4(0);
    salon_import_5(0);
    salon_import_6(0);
    salon_import_7(0);
    salon_import_8(0);
    return 1;
}

static int Salon_proc_inner_exec(SalonProc *self) {
    /* Calls slot 0x1f0 with self->scene_inner->[+0x2c], then vtable
     * `[+0x08]` on self->bg_overlay[+0x38], then slot 0x1f8 and 0x200
     * with (self->bg_overlay, 0, 1). */
    salon_import_14(0);
    return 1;
}

static SalonProc *SalonProc_ctor(SalonProc *self) {
    /* 22-byte alloc; 4MB-region alloc with descriptor list */
    salon_import_18(0);
    salon_import_19(0);
    salon_import_20(0);
    salon_import_21(0);
    salon_import_22(0);
    salon_import_23(0);
    salon_import_24(0);
    salon_import_25(0);
    return self;
}

static int Salon_can_stop(void)                  { return 1; }
static int Salon_can_draw(void)                  { return 1; }
static int Salon_default_op(void)                { return 1; }

static int Salon_proc_inner_long_exec(SalonProc *self) {
    /* TODO: not yet decoded */
    (void)self;
    return 1;
}

static int salon_bg_anim_update(SalonProc *self) {
    /* vpush {d8-d9}; loads constants and a series of slot calls.
     * The inner uses fp-reg math against the scene-inner's vertical
     * offset (lift the camera, etc.). */
    (void)self;
    return 0;
}

static void *salon_alloc_a(size_t bytes) { (void)bytes; return 0; }
static void *salon_alloc_b(size_t bytes) { (void)bytes; return 0; }
static void *salon_alloc_c(size_t bytes) { (void)bytes; return 0; }
