/*
 * Preliminary decompilation of DllFatalErrorProc.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the layout of the
 * `xy_system::error::FatalErrorProc` object is only partially decoded
 * and the inner XY-system callbacks have not been resolved.
 *
 * Module file: extracted/romfs/DllFatalErrorProc.cro
 *   code region     0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0x820
 *   segment 1 (THM) 0x1000 .. 0x1164
 *   segment 2 (RO)  0x2280 .. 0x229c (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x20
 *   bss             0x28
 *   exports named   1 (`nnroControlObject_`, segment 0, +0x648)
 *   imports         39 anonymous entries from `|static|`
 *   external patches 0
 *
 * RTTI type names recovered from the `.rodata` region (file offsets):
 *     "N3gfl4proc11BaseProcessE"
 *     "N9xy_system5error14FatalErrorProcE"
 *
 * Behavioral summary:
 *   The 3DS "fatal system error" overlay handler (analogous to the
 *   old DS "white screen" handler).  Driven by the outer xy_system
 *   error pump: receives a fatal code, pops an internal message
 *   queue, and renders a stack-trace / context block before exiting
 *   the application.
 */

#include <stdint.h>

typedef struct FatalErrorProc FatalErrorProc;
typedef struct FatalErrorWork FatalErrorWork;

/* Object layout inferred from the constructor at CRO 0x2bc, which
 * zeroes +0x14 and writes a vtable pointer at +0x00; and from CRO
 * 0x360, which reads +0x38/+0x3c/+0x40/+0x44/+0x48/+0x4c/+0x50/+0x54. */
struct FatalErrorProc {
    void *vtable;             /* 0x00 */
    uint8_t reserved04[0x10]; /* 0x04..0x13 */
    void *anchor;             /* 0x14 */
    uint8_t reserved18[0x08]; /* 0x18..0x1f */
    uint8_t state_byte;       /* 0x20 — sub-state byte in CRO 0x2f0 */
    uint8_t reserved21[0x17]; /* 0x21..0x37 */
    void *service_a;          /* 0x38 — pumped by every Exec */
    void *service_b;          /* 0x3c — cleared in destructor */
    void *param_a;            /* 0x40 — passed into 0x1a8 */
    void *param_b;            /* 0x44 — passed into 0x1b0 */
    uint8_t reserved48[0x08];
    void *closure_a;          /* 0x50 */
    void *closure_b;          /* 0x54 — cleared and stub-released */
};

struct FatalErrorWork {
    uint8_t reserved[0x38];   /* only offsets +0x38..+0x54 are referenced */
};

/* ---------- Internal forwarders -------------------------------------- */

extern int fe_import_0(int, ...);  /* 0x180 — work-area allocator */
extern int fe_import_1(int, ...);  /* 0x188 — work-area freer */
extern int fe_import_2(int, ...);  /* 0x190 */
extern int fe_import_3(int, ...);  /* 0x198 */
extern int fe_import_4(int, ...);  /* 0x1a0 */
extern int fe_import_5(int, ...);  /* 0x1a8 */
extern int fe_import_6(int, ...);  /* 0x1b0 */
extern int fe_import_7(int, ...);  /* 0x1b8 */
extern int fe_import_8(int, ...);  /* 0x1c0 */
extern int fe_import_9(int, ...);  /* 0x1c8 */
extern int fe_import_10(int, ...); /* 0x1d0 */
extern int fe_import_11(int, ...); /* 0x1d8 */
extern int fe_import_12(int, ...); /* 0x1e0 */
extern int fe_import_13(int, ...); /* 0x1e8 */
extern int fe_import_14(int, ...); /* 0x1f0 */
extern int fe_import_15(int, ...); /* 0x1f8 */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x284 — outer Process ctor (lifecycle vtable +0x00 Init).
 * Sets vtable from literal pool at 0x2b8, clears +0x14, tail-delegates
 * to slot 1 (`bl 0x188`). */
static FatalErrorProc *FatalErrorProc_ctor(FatalErrorProc *self);

/* CRO 0x2bc — outer Process ctor (#2): symmetric pattern, uses
 * literal pool at 0x2ec. */
static FatalErrorProc *FatalErrorProc_ctor2(FatalErrorProc *self);

/* CRO 0x2f0 — Exec: 3-way switch on `[+0x20]`.
 *   case 0: allocate one work block, advance state to 1
 *   case 1: ask another slot (0x198) if anything is left, advance or
 *           drop through
 *   default: just advance the state
 * In all branches the service @ `[+0x38]` is fed `0xffff` (literal
 * pool at 0x35c).  Returns 0. */
static int FatalErrorProc_exec(FatalErrorProc *self);

/* CRO 0x360 — Delete/dtor: tears down service_b (+0x3c) via vtable
 * delete, releases closure_b (+0x54), and frees work through `bl
 * 0x1b8` and `bl 0x188`. */
static int FatalErrorProc_delete(FatalErrorProc *self);

/* CRO 0x460 — CanDraw helper. */
static int FatalErrorProc_can_draw(void);

/* CRO 0x4a8 — CanRun helper. */
static int FatalErrorProc_can_run(void);

/* CRO 0x6fc..0x7d0 — pair of small accessors (vtable indices +0x04
 * and +0x08 / +0x10 / +0x14) — documented in the comments but each
 * recovers a single field via the dispatcher pattern. */
static int fe_slot4(FatalErrorProc *self);
static int fe_slot8(FatalErrorProc *self);
static int fe_slotC(FatalErrorProc *self);
static int fe_slot10(FatalErrorProc *self);

/* ---------- Implementations (preliminary) ---------------------------- */

static FatalErrorProc *FatalErrorProc_ctor(FatalErrorProc *self) {
    if (self->anchor)
        fe_import_0(0);
    self->anchor = 0;
    self->vtable = 0; /* resolved from literal pool 0x2b8 */
    fe_import_1(0);
    return self;
}

static FatalErrorProc *FatalErrorProc_ctor2(FatalErrorProc *self) {
    if (self->anchor)
        fe_import_0(0);
    self->anchor = 0;
    self->vtable = 0; /* resolved from literal pool 0x2ec */
    return self;
}

static int FatalErrorProc_exec(FatalErrorProc *self) {
    uint8_t s = self->state_byte;
    if (s == 0) {
        /* Allocate a 2-byte work slot and advance the state. */
        fe_import_2(0);
    } else if (s == 1) {
        /* Poll slot 3 to determine whether we are done polling. */
        if (fe_import_3(0) == 0)
            return 0;
    }
    if (s <= 1)
        self->state_byte = s + 1;

    /* Pump the underlying fatal-error renderer; literal at 0x35c = 0xffff */
    fe_import_4(0);
    return 0;
}

static int FatalErrorProc_delete(FatalErrorProc *self) {
    /* Calls fe_import_5 with (self->service_a, self->param_a) then
     * fe_import_6 with (self->service_b, self->param_b), then vtable-
     * deletes service_b if non-NULL, and finally frees two closure
     * slots through fe_import_7 and fe_import_1. */
    if (self->service_b) {
        void (*del)(void) = 0;
        (void)del;
        self->service_b = 0;
    }
    fe_import_5(self->service_a, self->param_a);
    fe_import_6(self->param_b, 0);
    if (self->closure_b)
        fe_import_7(0);
    fe_import_1(0);
    return 0;
}

static int FatalErrorProc_can_draw(void)                  { return 1; }
static int FatalErrorProc_can_run(void)                   { return 1; }
static int fe_slot4(FatalErrorProc *self)                 { (void)self; return 0; }
static int fe_slot8(FatalErrorProc *self)                 { (void)self; return 0; }
static int fe_slotC(FatalErrorProc *self)                 { (void)self; return 0; }
static int fe_slot10(FatalErrorProc *self)                { (void)self; return 0; }
