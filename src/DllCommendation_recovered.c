/*
 * Preliminary decompilation of DllCommendation.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the `|static|` imports and
 * the `UIInputListener`/commendation-specific process IDs still need
 * to be recovered.
 *
 * Module file: extracted/romfs/DllCommendation.cro
 *   code region     0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0xf0c
 *   segment 1 (THM) 0x1000 .. 0x118c
 *   segment 2 (RO)  0x2778 .. 0x2794 (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x24
 *   bss             0x44
 *   exports named   1 (`nnroControlObject_`, segment 0, +0xc0c)
 *   imports         57 anonymous entries from `|static|`
 *   external patches 0 (imports module-only)
 *
 * RTTI type names recovered from the `.rodata` region (file offsets):
 *     "N3app12commendation4ProcE"
 *     "N3app12commendation4ViewE"
 *     "N3app2ui15UIInputListenerE"
 *     "N3gfl4proc11BaseProcessE"
 *
 * Behavioral summary:
 *   Implements the in-game "Commendation" (Thank-you) dialog that
 *   appears after a successful PGL mission submission.  Hierarchy:
 *       app::commendation::Proc  ->  app::commendation::View
 *   The dialog processes a state byte (+0x24) and produces a
 *   multi-step UI animation per state code.
 *
 * Curiosities:
 *   - File offsets 0xd60-0xd7c reset two 64-bit BSS slots and `bx lr`;
 *     this is the BSS initializer that runs as a static ctor pair.
 *   - The region 0xd8c-0xe1c is byte-for-byte identical to the
 *     dispatch stub documented in DllTestTamada.cro — likely a static
 *     singleton accessor or a placeholder anchored from the loader.
 */

#include <stdint.h>
#include <stddef.h>

typedef struct CommendationProc CommendationProc;
typedef struct CommendationView CommendationView;
typedef struct UIInputListener UIInputListener;

/* Layout mirrored from the constructor at CRO 0xc94: clears
 * +0x00 (vtable) and +0x14 (a single pointer). */
struct CommendationProc {
    void *vtable;
    uint8_t reserved04[0x10];
    void *anchor;             /* +0x14 */
    uint8_t reserved18[0x70]; /* +0x18..0x87 */
    uint8_t flag_88;          /* +0x88 — toggled by helpers @ 0xd08/0xd38 */
    uint8_t reserved89[0x27];
};

/* Layout confirmed from the constructor at CRO 0xccc: writes vtable
 * pointer and clears +0x14. */
struct CommendationView {
    void *vtable;
    uint8_t reserved04[0x10];
    void *anchor;             /* +0x14 */
};

struct UIInputListener {
    uint8_t reserved[0x30];   /* placeholder; size derived from C++ name */
};

/* ---------- Internal forwarders -------------------------------------- */

extern int commendation_import_0(int, ...);  /* 0x230 */
extern int commendation_import_1(int, ...);  /* 0x238 */
extern int commendation_import_2(int, ...);  /* 0x240 */
extern int commendation_import_3(int, ...);  /* 0x248 */
extern int commendation_import_4(int, ...);  /* 0x258 */
extern int commendation_import_5(int, ...);  /* 0x260 */
extern int commendation_import_6(int, ...);  /* 0x268 */
extern int commendation_import_7(int, ...);  /* 0x270 */
extern int commendation_import_8(int, ...);  /* 0x278 */
extern int commendation_import_9(int, ...);  /* 0x280 */
extern int commendation_import_10(int, ...); /* 0x288 */
extern int commendation_import_11(int, ...); /* 0x290 */
extern int commendation_import_12(int, ...); /* 0x298 */
extern int commendation_import_13(int, ...); /* 0x2a0 */
extern int commendation_import_14(int, ...); /* 0x2a8 */
extern int commendation_import_15(int, ...); /* 0x2b0 */
extern int commendation_import_16(int, ...); /* 0x2b8 */
extern int commendation_import_17(int, ...); /* 0x2c0 */
extern int commendation_import_18(int, ...); /* 0x2c8 */
extern int commendation_import_19(int, ...); /* 0x2d0 */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x2d8 — outer Proc::CanRun. */
static int commendation_can_run(void);

/* CRO 0x414 — outer Proc::Exec; a long switch on state [+0x24], with
 * the inner worker at CRO 0x490 invoked from one of the branches. */
static int commendation_proc_exec(void);

/* CRO 0x490 — inner Exec worker.  Reads self->view and dispatches
 * vtable [+0x08] [+0x18]. */
static int commendation_proc_exec_inner(void);

/* CRO 0x6e0 — CanDraw + view vtable dispatch helpers. */
static int commendation_can_draw(void);

/* CRO 0x738, 0x788, 0x7dc, 0x808 — pair of (CanRun/CanDraw/CanStop)/
 * (Exec2) lifecycle helpers that toggle flag_88 (+0x88) on the inner
 * listener. */
static int commendation_can_run_inner(void);
static int commendation_can_draw_inner(void);
static int commendation_can_stop_inner(void);
static int commendation_exec_inner(void);

/* CRO 0x82c — large Exec body that:
 *  - reads self->view (+0x20) and steps through a 6-state UI sequence;
 *  - on each step calls one of commendation_import_0..19.
 *  Marked TODO: state-machine transitions are not yet fully decoded. */
static int commendation_proc_full_exec(void);

/* CRO 0xae0, 0xb48, 0xb74, 0xbfc — pair of allocators.  They call
 * import slot 0x248 (memset-like routine) and import slot 0x260
 * (linked-list insertion). */
static void *commendation_alloc_a(size_t bytes);
static void *commendation_alloc_b(size_t bytes);

/* CRO 0xc94 — Proc ctor: sets vtable from literal-pool anchor at 0xcc8,
 * clears +0x14, tail-delegates to slot 1 (`bl 0x238`). */
static CommendationProc *CommendationProc_ctor(CommendationProc *self);

/* CRO 0xccc — View ctor: identical pattern to Proc, uses literal
 * pool at 0xcfc. */
static CommendationView *CommendationView_ctor(CommendationView *self);

/* CRO 0xd08 — listener::bind slot (init): sets flag_88 to 1 after a
 * successful import call (`bl 0x240`). */
static int commendation_listener_bind(UIInputListener *self, void *arg);

/* CRO 0xd38 — listener::detach slot (init): clears flag_88 to 1 after
 * a successful import call (`bl 0x248`). */
static int commendation_listener_detach(UIInputListener *self, void *arg);

/* CRO 0xd60 — BSS initializer: writes -1 to a 64-bit slot at 0xd84 and
 * 0 to a 64-bit slot at 0xd88. */
static void commendation_bss_init(void);

/* CRO 0xd8c — diagnostic get-or-set stub (see note in header). */
static int commendation_stub_getset(void *self, int op, void *arg);

/* ---------- Implementations (preliminary) ---------------------------- */

static int commendation_can_run(void)                  { return 1; }
static int commendation_can_draw(void)                 { return 1; }
static int commendation_can_run_inner(void)            { return 1; }
static int commendation_can_draw_inner(void)           { return 1; }
static int commendation_can_stop_inner(void)           { return 1; }
static int commendation_exec_inner(void)               { (void)0; /* TODO */ return 1; }

static int commendation_proc_exec(void) {
    /* TODO: not yet decoded */
    return 1;
}

static int commendation_proc_exec_inner(void) {
    /* Reads self->view (+0x20) and dispatches vtable [+0x08] then
     * vtable [+0x18].  This is the standard "Init/Delete"
     * lifecycle-vtable dispatch. */
    commendation_import_0(0);
    commendation_import_1(0);
    return 1;
}

static int commendation_proc_full_exec(void) {
    /* State machine: 6 UI states, each calling one of
     * commendation_import_{0..19} and toggling inner flags.
     * The literal pool at 0x1018-0x1038 holds six 32-bit values
     * (0x4a/0xf/0xb/0x17/0x11/0x13) used as transition keys. */
    commendation_import_0(0);
    commendation_import_1(0);
    commendation_import_2(0);
    commendation_import_3(0);
    commendation_import_4(0);
    commendation_import_5(0);
    return 1;
}

static void *commendation_alloc_a(size_t bytes) { (void)bytes; return 0; }
static void *commendation_alloc_b(size_t bytes) { (void)bytes; return 0; }

static CommendationProc *CommendationProc_ctor(CommendationProc *self) {
    self->vtable = 0;
    if (self->anchor)
        commendation_import_0(0);
    self->anchor = 0;
    commendation_import_1(0);
    return self;
}

static CommendationView *CommendationView_ctor(CommendationView *self) {
    self->vtable = 0;
    if (self->anchor)
        commendation_import_0(0);
    self->anchor = 0;
    commendation_import_1(0);
    return self;
}

static int commendation_listener_bind(UIInputListener *self, void *arg) {
    if (!commendation_alloc_a(0x30))
        return 1;
    self = (UIInputListener *)((uintptr_t)self + 0x74);
    self->reserved[0x88] = 1; /* placeholder */
    (void)arg;
    return 0;
}

static int commendation_listener_detach(UIInputListener *self, void *arg) {
    if (!commendation_alloc_b(0x30))
        return 1;
    self = (UIInputListener *)((uintptr_t)self + 0x74);
    self->reserved[0x88] = 1;
    (void)arg;
    return 0;
}

static void commendation_bss_init(void) {
    /* TODO: not yet decoded; writes to literal anchors at 0xd84/0xd88 */
}

static int commendation_stub_getset(void *self, int op, void *arg) {
    (void)self; (void)arg;
    /* Same shape as the TestTamada stub at 0x180: a 6-way
     * (cases 0..5) dispatch based on `op`, returning 0 on
     * success.  The MIRROR magic constants (0x30000000,
     * 0x30000026, 0xd8e12c21) appear at 0xe2c/0xe30/0xe34. */
    switch (op) {
    case 0: case 1: case 2: case 3: case 4: return 0;
    default: return 0;
    }
}
