/*
 * Preliminary decompilation of DllBattleHouseConnect.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the imported services and the
 * exact export offsets in docs/symbols/DllBattleHouseConnect.map still
 * need to be re-aligned against the actual CRO loader-layout formula
 * (some map offsets do not coincide with a documented `push {..., lr}`).
 *
 * Module file: extracted/romfs/DllBattleHouseConnect.cro
 *   code region      0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM)  0x180 .. 0xf0c           (id 0)
 *   segment 1 (THM)  0x1000 .. 0x11e8         (id 1)
 *   segment 2 (RO)   0x2890 .. 0x28a4         (id 2, 20 bytes)
 *   segment 3 (BSS)  0x0, size 0x3c
 *   bss              0x5c
 *   exports named    2 (`nnroControlObject_`, `xy_system::bg::System::SetIsCallDraw`)
 *   imports module   1 (`|static|`, 53 anonymous entries)
 *   external patches 57
 *
 * Behavioral summary:
 *   Drives the Battle Maison "Online Connect" menu — network session
 *   open/query/close + the inner state machine that exchanges leader
 *   data with the partner hall.  Many vtable dispatch sites follow
 *   the standard `[rN] -> [rN+0x??] -> blx r1` shape, identifying this
 *   as a normal "Process" class hierarchy built on the engine `Process`
 *   lifecycle (Init/Exec/Draw/Delete at +0x00/+0x08/+0x10/+0x18).
 */

#include <stdint.h>

typedef struct BHConnectProc BHConnectProc;
typedef struct BHConnectWork BHConnectWork;

/* Object layout inferred from the constructor at CRO 0xbdc, which clears
 * the new instance and writes the standard sub-object pointers. */
struct BHConnectProc {
    void *vtable;             /* 0x00 — system vtable (Init/Exec/Draw/Delete) */
    void *child_a;            /* 0x04 */
    void *child_b;            /* 0x08 */
    void *child_c;            /* 0x0c */
    void *child_d;            /* 0x10 */
    void *reserved14;         /* 0x14 */
    void *reserved18;         /* 0x18 */
    void *reserved1c;         /* 0x1c */
    void *child_e;            /* 0x20 */
    uint8_t reserved24[16];   /* 0x24..0x33 */
    void *child_f;            /* 0x34 (set up as a string-list @ +0x28) */
    uint8_t reserved38[8];    /* 0x38..0x3f */
    BHConnectWork *work;      /* 0x40 — backing BHConnectWork */
    BHConnectProc *owner;     /* 0x44 */
    uint8_t state;            /* 0x48 — outer state */
    uint8_t sub_state;        /* 0x49 */
    uint8_t reserved4a[2];
    void *parent;             /* 0x4c */
    void *service_a;          /* 0x50 */
    uint8_t flag54;           /* 0x54 */
    uint8_t flag55;           /* 0x55 */
    uint8_t reserved56[2];
    void *bg_system;          /* 0x58 — xy_system::bg::System* */
    uint8_t reserved5c[0x5c]; /* 0x5c..0xb7 */
    uint8_t ready;            /* 0xb8 */
    uint8_t draw_flag;        /* 0xb9 — toggled by SetIsCallDraw */
    uint8_t reserved_ba[6];
    void *qword_c0[2];        /* 0xc0..0xc7 */
    void *qword_c8[2];        /* 0xc8..0xcf */
    void *qword_d0[2];        /* 0xd0..0xd7 */
    void *bg_sys_handle;      /* 0xd8 — cached BG system handle */
};

struct BHConnectWork {
    uint8_t reserved[0x620]; /* confirmed up to +0x620 from disasm reads */
};

/* ------- Function stubs (CRO offsets vs. C name) ------------------------
 *
 * The constructors and a handful of state-machine helpers are recovered
 * below at the offsets where the disassembler shows a clean
 * `push {..., lr}` prologue and a matching `pop {..., pc}`.  Internal
 * branches/function entries that the disassembler shows as `bl 0xNNN`
 * are documented as comments; their bodies are not transcribed.
 */

/* Internal forwarders invoked from this CRO.  Names are placeholder. */
extern int bh_lowlevel_a(int, ...);
extern int bh_lowlevel_b(int, ...);
extern int bh_lowlevel_c(int, ...);
extern int bh_lowlevel_d(int, ...);
extern int bh_lowlevel_e(int, ...);

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x2fc — outer Init/CanRun helper. */
static int bh_can_run(void) { return 1; }

/* CRO 0x334 — outer Init/CanStop helper. */
static int bh_can_stop(void) { return 1; }

/* CRO 0x370 — outer Init/CanDraw helper. */
static int bh_can_draw(void) { return 1; }

/* CRO 0x558, 0x57c, 0x650, 0x6f8 — pair of inner Process helpers.
 * Identified by `push {r3,r4,r5,lr} / push {r4,r5,r6,r7,r8,lr}` shapes.
 * Each delegates to one or two of the imported `|static|` services and
 * sets BHConnectWork::* state flags. */
static void bh_inner_helper_a(BHConnectProc *self);
static void bh_inner_helper_b(BHConnectProc *self);
static void bh_inner_helper_c(BHConnectProc *self);
static void bh_inner_helper_d(BHConnectProc *self);

/* CRO 0xbdc — `BHConnectProc *BHConnectProc_ctor(BHConnectProc*, void *)`
 * Constructor: zeroes the field range +0x40..+0xdc, sets up the work
 * subobject via the imported work-allocator (`bl 0x2e0` / `bl 0x2e8`),
 * installs the vtable pointer from the literal pool at 0xc6c, and
 * initialises the standard sub-object slot offsets (+0x28..+0x38). */
static BHConnectProc *BHConnectProc_ctor(BHConnectProc *self, void *sys);

/* CRO 0xc70 — destructor pair (`destructor` / `finalize`).
 * Disasm shows a `push {r4,lr}` and a chain of vtable deletes. */
static void BHConnectProc_dtor(BHConnectProc *self);

/* CRO 0xda0..0xddc — two small wrappers that float-load 1.0f constants
 * from the literal pool (0xbc8 = 3f800000) and stash them in `bg_sys`.
 * They back the bg fading/centering used by the inner Exec. */
static void bh_bg_set_a(BHConnectProc *self);
static void bh_bg_set_b(BHConnectProc *self);

/* CRO 0xba4 — exported `xy_system::bg::System::SetIsCallDraw(bool)`.
 * The disassembly at this offset is only a literal `nop {0}`, but the
 * surrounding logic around 0xb88/0xbac toggles `self->draw_flag`. */
extern void _ZN9xy_system2bg6System13SetIsCallDrawEb(BHConnectProc *sys, int on);

/* ---------- Implementations (preliminary) ---------------------------- */

static void bh_inner_helper_a(BHConnectProc *self) {
    /* Reads self->ready (offset 0xb8), iterates 0..3 calling the
     * corresponding inner helper.  Each iteration triggers
     * `[r0+0x58]->vtable[0x04]()` for slot teardown. */
    bh_lowlevel_a(0);
    bh_lowlevel_b(0);
}

static void bh_inner_helper_b(BHConnectProc *self) {
    /* Reads self->state (0x48), branches on values 4/5/8/9/14,
     * writing a final state to self->state and posting a draw request
     * through bg_system. */
    bh_lowlevel_c(0);
}

static void bh_inner_helper_c(BHConnectProc *self) {
    /* Reads self->bg_sys_handle (0xd8) and triggers a draw. */
    bh_lowlevel_d(0);
}

static void bh_inner_helper_d(BHConnectProc *self) {
    /* Wraps two float-loads (1.0f) and calls into `|static|` service
     * (offset 0x180 in the loader). */
    bh_lowlevel_e(0);
}

static BHConnectProc *BHConnectProc_ctor(BHConnectProc *self, void *sys) {
    /* The literal at 0xc6c supplies the vtable pointer; the offsets
     * +0x48/+0x6c/+0x7c come from the disasm `add r1,pc,#0x48` chain. */
    self->vtable = 0; /* patched at run time */
    self->work   = (BHConnectWork *)(uintptr_t)0; /* TODO: not yet decoded */
    self->owner  = 0;
    self->state  = 0;
    self->sub_state = 1;
    self->parent = 0;
    self->service_a = 0;
    self->flag54 = 0;
    self->flag55 = 0;
    self->bg_system = 0;
    /* +0x5c..+0xb7 cleared by the constructor */
    self->ready = 0;
    self->draw_flag = 1;
    /* +0xc0..+0xd8 cleared */
    self->bg_sys_handle = 0;
    (void)sys;
    return self;
}

static void BHConnectProc_dtor(BHConnectProc *self) {
    if (self->work) {
        BHConnectWork *w = self->work;
        (void)w; /* TODO: free sub-objects */
        self->work = 0;
    }
}

static void bh_bg_set_a(BHConnectProc *self) { (void)self; /* float-load 1.0f */ }
static void bh_bg_set_b(BHConnectProc *self) { (void)self; /* float-load 1.0f */ }

void _ZN9xy_system2bg6System13SetIsCallDrawEb(BHConnectProc *sys, int on) {
    if (sys)
        sys->draw_flag = on ? 1 : 0;
}
