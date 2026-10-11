/*
 * Preliminary decompilation of DllCommWait.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the `|static|` imports have
 * not been resolved against concrete external CROs.
 *
 * Module file: extracted/romfs/DllCommWait.cro
 *   code region     0x180 .. 0x180 + 0x1e80   (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0xdbc
 *   segment 1 (THM) 0x1000 .. 0x118c
 *   segment 2 (RO)  0x2778 .. 0x2794 (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x24
 *   bss             0x44
 *   exports named   1 (`nnroControlObject_`, segment 0, +0xb8c)
 *   imports         49 anonymous entries from `|static|`
 *   external patches 53
 *
 * RTTI type names recovered from the `.rodata` region (file offset
 * 0x1088-0x10f6):
 *     "N3gfl4proc11BaseProcessE"
 *     "N6netapp9comm_wait10MainSystemE"
 *     "N6netapp9comm_wait4ProcE"
 *     "N6netapp9comm_wait8ViewWorkE"
 *
 * Behavioral summary:
 *   Implements the "communication in progress" overlay that the game
 *   pushes on top of any sub-menu while it is exchanging packets with
 *   the Game Sync / PGL servers.  Hierarchy:
 *       MainSystem  -> Proc  -> (delegates to ViewWork)
 *   Inner Process dispatched by state byte at +0x24.
 */

#include <stdint.h>

typedef struct CommWaitMainSystem CommWaitMainSystem;
typedef struct CommWaitProc CommWaitProc;
typedef struct CommWaitViewWork CommWaitViewWork;

/* Outer sub-object inferred from the constructor at CRO 0x2ac..0x2dc
 * (which sets +0x00 vtable and zero-clears +0x14). */
struct CommWaitMainSystem {
    void *vtable;
    uint8_t reserved04[0x10];
    void *anchor;
};

/* Inner Process layout reconstructed from the Exec stub at CRO 0x318
 * which reads state/sub_state/timer/child at offsets +0x24..+0x37. */
struct CommWaitProc {
    void *vtable;             /* 0x00 */
    void *proc_parent;        /* 0x04 */
    uint8_t reserved08[0x18]; /* 0x08..0x1f */
    void *view;               /* 0x20 (CommWaitViewWork*) */
    uint8_t state;            /* 0x24 (jump table dispatch) */
    uint8_t sub_state;        /* 0x25 */
    uint8_t reserved26[2];
    int32_t timer;            /* 0x28 */
    uint8_t reserved2c[0xc];  /* 0x2c..0x37 */
    void *child_ui_a;         /* 0x38 */
};

struct CommWaitViewWork {
    uint8_t reserved[0x30];   /* the only confirmed offsets are +0x28/+0x2c/+0x30 */
};

/* ---------- Internal forwarders -------------------------------------- */

extern int comm_wait_import_0(int, ...);   /* 0x180 — first `|static|` slot */
extern int comm_wait_import_1(int, ...);   /* 0x188 */
extern int comm_wait_import_2(int, ...);   /* 0x190 */
extern int comm_wait_import_3(int, ...);   /* 0x198 */
extern int comm_wait_import_4(int, ...);   /* 0x1a0 */
extern int comm_wait_import_5(int, ...);   /* 0x1a8 */
extern int comm_wait_import_6(int, ...);   /* 0x1b0 */
extern int comm_wait_import_7(int, ...);   /* 0x1b8 */
extern int comm_wait_import_8(int, ...);   /* 0x1c0 */
extern int comm_wait_import_9(int, ...);   /* 0x1c8 */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x2ac — MainSystem / outer ctor (Init in the lifecycle vtable).
 * 1) Installs the vtable pointer from a literal pool entry.
 * 2) Clears +0x14.
 * 3) Tail-delegates to slot 1 (`bl 0x188`). */
static CommWaitMainSystem *CommWaitMainSystem_ctor(CommWaitMainSystem *self);

/* CRO 0x2e4 — MainSystem / outer dtor (Delete in the lifecycle vtable).
 * Symmetric pattern to the ctor: clears +0x14, calls `bl 0x188`. */
static void CommWaitMainSystem_dtor(CommWaitMainSystem *self);

/* CRO 0x318 — Proc::Exec.
 * Reads state (+0x24) and dispatches a 6-way switch on it
 * (0..5), each branch mutating self->state/self->sub_state and
 * calling the respective import slots. */
static int comm_wait_proc_exec(CommWaitProc *self);

/* CRO 0x40c — Proc::ExecInner (a long-lived worker).
 * Decrements a timer at +0x28 and dispatches on a sub-state byte
 * pulled from self->view->reserved[..]. */
static int comm_wait_proc_inner(CommWaitProc *self);

/* CRO 0x688 — Proc::subroutine invoked from exec state 1.
 * Calls `bl 0x300` (alias of MainSystem exec helper), then runs
 * the inner vtable delete dispatch on self->child_ui_a. */
static int comm_wait_post_exec_300(CommWaitProc *self);

/* CRO 0x6c4 — Proc::CanRun. */
static int comm_wait_can_run(CommWaitProc *self);

/* CRO 0x6e8 — Proc::CanDraw (returns 0 if child is null, else
 * dispatches vtable [+0x24] -- the gfx loop hook). */
static int comm_wait_can_draw(CommWaitProc *self);

/* CRO 0x708 — Proc::CanStop (default true). */
static int comm_wait_can_stop(CommWaitProc *self);

/* CRO 0x710 — Proc::ctor: allocates 0x2c bytes through slot 5
 * (`bl 0x190`), fills the vtable pointer and inner child UI list,
 * and links the ViewWork struct. */
static CommWaitProc *CommWaitProc_ctor(CommWaitProc *self, void *arg);

/* ---------- Implementations (preliminary) ---------------------------- */

static CommWaitMainSystem *CommWaitMainSystem_ctor(CommWaitMainSystem *self) {
    /* literal pool @ 0x2e0 — final relocation resolves to the vtable */
    if (self->anchor)
        comm_wait_import_0(0);
    self->anchor = 0;
    comm_wait_import_1(0);
    return self;
}

static void CommWaitMainSystem_dtor(CommWaitMainSystem *self) {
    if (self->anchor)
        comm_wait_import_0(0);
    self->anchor = 0;
    comm_wait_import_1(0);
}

static int comm_wait_proc_exec(CommWaitProc *self) {
    switch (self->state) {
    case 0:
        self->sub_state = 0;
        comm_wait_import_2(0);
        self->state = 1;
        comm_wait_import_3(0);
        self->state = 1;
        return 1;
    case 1: case 2:
        comm_wait_post_exec_300(self);
        return 1;
    case 3:
        if (comm_wait_import_4(0) == 0) {
            comm_wait_import_5(0);
            self->state = 3;
            return 1;
        }
        self->state = 4;
        return 1;
    case 4: default:
        /* teardown path: clears self->view, calls view->vtable[+0x18]() */
        if (self->view) {
            /* ldr r1, [r1, #24]; blx r1 */
        }
        comm_wait_import_5(0);
        self->sub_state = 0;
        comm_wait_import_2(0);
        self->state = 4;
        return 1;
    }
}

static int comm_wait_proc_inner(CommWaitProc *self) {
    if (self->timer > 0)
        --self->timer;
    if (self->sub_state)
        self->state = 2;
    return 1;
}

static int comm_wait_post_exec_300(CommWaitProc *self) {
    comm_wait_proc_inner(self);
    if (self->view) {
        void (*del)(void) = 0; /* TODO: not yet decoded */
        (void)del;
    }
    if (comm_wait_import_3(0))
        return 1;
    return 0;
}

static int comm_wait_can_run(CommWaitProc *self)  { (void)self; return 1; }
static int comm_wait_can_draw(CommWaitProc *self) { (void)self; return 1; }
static int comm_wait_can_stop(CommWaitProc *self) { (void)self; return 1; }

static CommWaitProc *CommWaitProc_ctor(CommWaitProc *self, void *arg) {
    self->view = 0; /* patched via the loader literal pool */
    self->state = 0;
    self->sub_state = 0;
    self->timer = 0;
    self->child_ui_a = 0;
    self->view = (CommWaitViewWork *)comm_wait_import_2(0);   /* bl 0x180 */
    /* 0x2c bytes reserved */
    {
        /* optional inline-import calls in the original disasm:
         * `bl 0x200` / `bl 0x190` / `bl 0x198` for UI window allocation */
    }
    (void)arg;
    return self;
}
