/*
 * Preliminary decompilation of DllGameClearSave.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the inner float constants
 * (literal 0x468 = 1.0f, 0x46c = 0x0f) and the DllField-style save
 * import slots need to be re-confirmed against the live game.
 *
 * Module file: extracted/romfs/DllGameClearSave.cro
 *   code region     0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0xf48
 *   segment 1 (THM) 0x1000 .. 0x11e8
 *   segment 2 (RO)  0x23dc .. 0x23f8 (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x1c
 *   bss             0x1c
 *   exports named   1 (`nnroControlObject_`, segment 0, +0xc8c)
 *   imports         67 anonymous entries from `|static|`
 *   external patches 0
 *
 * RTTI type names recovered from `.rodata`:
 *     "N3app15game_clear_save4ProcE"
 *     "N3app15game_clear_save4ViewE"
 *     "N3gfl4proc11BaseProcessE"
 *
 * Behavioral summary:
 *   The "Game Clear Save" dialog shown after the player finishes the
 *   main story.  Two-step layout:
 *
 *     proc::GameClearSave::Proc
 *       - reads `[+0x04]` state, dispatches a 6-state machine
 *       - calls `+0x38`->vtable[+0x20]() in the dispatcher return
 *
 *     view::GameClearSave::View
 *       - reads `[+0x40]` state, dispatches an 8-state machine
 *       - each state hands control to slot 0x828 with progressively
 *         larger arguments and increments self->state
 *
 *   The literal pool at `0x468 = 0x3f800000` (1.0f) and `0x46c =
 *   0x00000000` (0.0f) confirm a fade-out animation.
 */

#include <stdint.h>
#include <stddef.h>

typedef struct GameClearSaveProc GameClearSaveProc;
typedef struct GameClearSaveView GameClearSaveView;

struct GameClearSaveProc {
    void *vtable;             /* 0x00 */
    uint32_t state;           /* 0x04 — 6-state machine */
    uint8_t reserved08[0x30];
    void *child_dialog;       /* 0x38 — vtable [+0x20] dispatched */
    uint8_t reserved3c[0x04];
};

struct GameClearSaveView {
    void *vtable;             /* 0x00 */
    uint8_t reserved04[0x3c];
    uint8_t state;            /* 0x40 — 8-state machine (CRO 0x488) */
    uint8_t reserved41[0x3f];
};

/* ---------- Internal forwarders -------------------------------------- */

extern int gcs_import_0(int, ...);  /* 0x180 */
extern int gcs_import_1(int, ...);  /* 0x188 */
extern int gcs_import_2(int, ...);  /* 0x190 */
extern int gcs_import_3(int, ...);  /* 0x198 */
extern int gcs_import_4(int, ...);  /* 0x1a0 */
extern int gcs_import_5(int, ...);  /* 0x1a8 */
extern int gcs_import_6(int, ...);  /* 0x1b0 */
extern int gcs_import_7(int, ...);  /* 0x1b8 */
extern int gcs_import_8(int, ...);  /* 0x1c0 */
extern int gcs_import_9(int, ...);  /* 0x1c8 */
extern int gcs_import_10(int, ...); /* 0x1d0 */
extern int gcs_import_11(int, ...); /* 0x1d8 */
extern int gcs_import_12(int, ...); /* 0x1e0 */
extern int gcs_import_13(int, ...); /* 0x1e8 */
extern int gcs_import_14(int, ...); /* 0x1f0 */
extern int gcs_import_15(int, ...); /* 0x1f8 */
extern int gcs_import_16(int, ...); /* 0x208 */
extern int gcs_import_17(int, ...); /* 0x250 */
extern int gcs_import_18(int, ...); /* 0x258 */
extern int gcs_import_19(int, ...); /* 0x260 */
extern int gcs_import_20(int, ...); /* 0x268 */
extern int gcs_import_21(int, ...); /* 0x270 */
extern int gcs_import_22(int, ...); /* 0x278 */
extern int gcs_import_23(int, ...); /* 0x280 */
extern int gcs_import_24(int, ...); /* 0x288 */
extern int gcs_import_25(int, ...); /* 0x290 */
extern int gcs_import_26(int, ...); /* 0x298 */
extern int gcs_import_27(int, ...); /* 0x2a0 */
extern int gcs_view_anim(int, ...); /* 0x828 — view-side animation step */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x330 — Proc::Exec (state machine, 6 states via jump table at
 * the literal pool `+0x348`).  vpush {d8} indicates float math;
 * loads 1.0f (literal 0x468) and the second float `0x46c` (= 0.0f)
 * into stack slots and calls 0x180/0x188/0x198. */
static int GameClearSave_proc_exec(GameClearSaveProc *self);

/* CRO 0x470 — View::Exec (state machine, 8 states).  Uses registers
 * r4-r8 to stage counter/state, reads self->state (+0x40). */
static int GameClearSave_view_exec(GameClearSaveView *self);

/* CRO 0x638 — pair of (CanRun / CanStop / CanDraw) lifecycle helpers;
 * reads `[+0x38]` then dispatches vtable `[+0x20]` through `blx r1`. */
static int GameClearSave_can_run(GameClearSaveProc *self);
static int GameClearSave_can_stop(GameClearSaveProc *self);
static int GameClearSave_can_draw(GameClearSaveProc *self);

/* CRO 0x6d4, 0x828 — view-side helper and animation runner. */
static int GameClearSave_view_helper(GameClearSaveView *self);
static int GameClearSave_view_anim(GameClearSaveView *self);

/* CRO 0x8e4 — pair of inner allocators. */
static void *gcs_alloc_a(size_t bytes);
static void *gcs_alloc_b(size_t bytes);

/* CRO 0xc98, 0xd00, 0xd6c, 0xda4, 0xe14 — small UIInputListener-style
 * slot accessors that each pass `(self, arg)` to the imported
 * service at slot 0x260/0x270/etc.  Documented as forwarding stubs. */
static int gcs_slot4(void *self, void *arg);
static int gcs_slot8(void *self, void *arg);
static int gcs_slotC(void *self, void *arg);
static int gcs_slot10(void *self, void *arg);
static int gcs_slot14(void *self, void *arg);

/* ---------- Implementations (preliminary) ---------------------------- */

static int GameClearSave_proc_exec(GameClearSaveProc *self) {
    switch (self->state) {
    case 0:
        /* set up fade stack slots (1.0f x4) at [sp, +0..+12] */
        gcs_import_0(0, 0); /* fade-out framebuffer / sub-frame */
        gcs_import_1(0, 1, 8);
        gcs_import_0(0, 1);
        if (++self->state && !gcs_import_2(0))
            return 0;
        ++self->state;
        return 1;
    case 1:
        gcs_import_3(0, 1, 8, 0);
        if (++self->state && !gcs_import_2(0))
            return 0;
        self->state = 0;
        return 1;
    case 5:
        /* Inner-work blob @ CRO 0x3d8..0x3ec; not yet decoded. */
        if (gcs_import_4(0, (int)(uintptr_t)self) == 0)
            return 0;
        ++self->state;
        return 1;
    default:
        if (self->child_dialog) {
            void (*upd)(void) = 0; /* vtable +0x20 */
            (void)upd;
        }
        return 0;
    }
}

static int GameClearSave_view_exec(GameClearSaveView *self) {
    /* 8-state jump table at +0x48c; the literal at 0x488 holds the
     * number of states (8). */
    switch (self->state) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        return gcs_view_anim(0, (int)(uintptr_t)self);
    default:
        return 1;
    }
}

static int GameClearSave_can_run(GameClearSaveProc *self)  { (void)self; return 1; }
static int GameClearSave_can_stop(GameClearSaveProc *self) { (void)self; return 1; }
static int GameClearSave_can_draw(GameClearSaveProc *self) { (void)self; return 1; }

static int GameClearSave_view_helper(GameClearSaveView *self) {
    (void)self;
    /* TODO: not yet decoded */
    return 1;
}

static int GameClearSave_view_anim(GameClearSaveView *self) {
    (void)self;
    /* TODO: not yet decoded — animates the bg overlay. */
    return 1;
}

static void *gcs_alloc_a(size_t bytes) { (void)bytes; return 0; }
static void *gcs_alloc_b(size_t bytes) { (void)bytes; return 0; }

static int gcs_slot4(void *self, void *arg)  { (void)self; (void)arg; return 0; }
static int gcs_slot8(void *self, void *arg)  { (void)self; (void)arg; return 0; }
static int gcs_slotC(void *self, void *arg)  { (void)self; (void)arg; return 0; }
static int gcs_slot10(void *self, void *arg) { (void)self; (void)arg; return 0; }
static int gcs_slot14(void *self, void *arg) { (void)self; (void)arg; return 0; }
