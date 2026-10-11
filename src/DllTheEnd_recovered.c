/*
 * Preliminary decompilation of DllTheEnd.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: post-game credits overlay (DllTheEnd).
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x814.
 *   - 52 static-module imports (resolved via the import table at 0x2314).
 *   - The standard NN loader dispatcher tail occupies 0x968..0xa3c.
 *
 * Recovered:
 *   - 19 function boundaries (see <stem>_NNNN stubs below).
 *   - Object layout: parent at +0x04, work pointer at +0x24, status at +0x14/0x18.
 *   - The end-of-mission state machine splits work in two halves: idle/wait (the
 *     function at 0x404 dispatches on work->phase, an enumerated 0..2 counter).
 *
 * Not yet decoded:
 *   - String table contents beyond the data segment dump (text strings used by
 *     the credits scroll live in segment 1 and were not decoded).
 *   - The exact semantics of the eight half-word entries around 0x1078 (these
 *     look like debug strings "N3ap_pth_\n", "N3fgl_pro1\r4\..." but the module
 *     list they encode is unresolved).
 *   - Floating-point argument count for the "draw" worker at 0x5cc.
 */

#include <stdint.h>

typedef struct TheEndProc TheEndProc;
typedef struct TheEndWork TheEndWork;

/* Confirmed from field accesses in the original ARM code. */
struct TheEndProc {
    void *vtable;        /* 0x00 */
    void *parent;        /* 0x04 */
    uint32_t unknown08;  /* 0x08 (gameplay loopback / generic ptr) */
    uint16_t status10;   /* 0x10 */
    uint8_t reserved12[2];
    uint16_t state14;    /* 0x14 */
    uint8_t reserved16[2];
    uint16_t state18;    /* 0x18 */
    uint8_t reserved1a[2];
    uint16_t field1c;    /* 0x1c */
    uint8_t reserved1e[2];
    uint16_t field20;    /* 0x20 */
    uint8_t reserved22[2];
    void *work;          /* 0x24 -> TheEndWork */
    void *heap;          /* 0x28 */
};

struct TheEndWork {
    uint32_t phase;      /* 0x00 - dispatched in update() */
    void *child;         /* 0x04 */
    uint32_t timer;      /* 0x08 - idle counter */
    uint32_t counter0c;  /* 0x0c */
    void *subview;       /* 0x10 */
    void *resource;      /* 0x14 - heap-backed resource handle */
    uint32_t reserved18; /* 0x18 */
};

/* --- Lifecycle stubs (return 1/0 -- these match the host scheduler API). --- */

/* CRO 0x1b0 */
static int theend_can_run(void) { return 1; }
/* CRO 0x1b4 */
static int theend_can_stop(void) { return 1; }
/* CRO 0x1c0 */
static int theend_can_draw(void) { return 1; }

/* CRO 0x1d4. Reads parent->timer (offset 0x14) and rolls it into a status word. */
static uint16_t theend_status(const TheEndProc *self) {
    return self->state14;
}

/* --- Main update. Dispatches on work->phase. --- */

/* CRO 0x404. State machine over TheEndWork.phase:
 *   0 = idle countdown (advances to 1 when timer saturates at 0x20).
 *   1 = "check input" - polls two keys at vtable+0x3c and +0x40, advances to 2.
 *   2 = finalize - waits on an imported "isDone" callback, sets phase to 0.
 */
static int theend_update(TheEndProc *self) {
    TheEndWork *work = (TheEndWork *)self->work;
    switch (work->phase) {
    case 0:
        if (++work->timer >= 0x20) {
            /* imported svc -- resets work fields. */
            work->phase = 1;
            work->timer = 0;
        }
        return 1;
    case 1: {
        void *child = work->child;
        int pressed = 0;
        (void)pressed;
        /* vtable+0x30 read at child->vtable[0x30/4]; if returns non-zero,
         * call imported "submit" and advance phase to 2. */
        if (child != 0)
            work->phase = 2;
        return 1;
    }
    case 2:
        /* imported poll -- "is the credits overlay finished?". */
        if (work->timer == 0)
            return 0;
        work->phase = 0;
        self->state14 = 4;
        return 1;
    default:
        return 1;
    }
}

/* --- Lifecycle helpers --- */

/* CRO 0x518. Releases the child UI surface and resets the vtable. */
static int theend_shutdown(TheEndProc *self) {
    void *child = self->work ? *(void **)self->work : 0;
    if (child != 0) {
        /* virtual call at child vtable +0x04 */
        child = 0;
    }
    if (self->work != 0)
        self->work = 0;
    /* imported free(self->heap) */
    self->state14 = 0;
    return self->state14;
}

/* --- Resource loader. CRO 0x5cc. --- */
/* Allocates a 0x40-byte child object via imported heap allocator, initializes
 * the embedded DrawList (offsets 0x10/0x14/0x18), and registers it with the
 * imported layout system. The original is ~0x100 bytes long; the exact slot
 * counts passed as immediates (0x80/0x10000/0x100) need further decoding. */
static void theend_load_draw(TheEndProc *self); /* TODO: not yet decoded */

/* --- Lifecycle stubs at 0x6dc/0x750/0x758 --- */

/* CRO 0x6dc. Vtable-slot dispatcher: routes on r1 (0..5) into a tail-call table. */
static int theend_vt_dispatch(TheEndProc *self, int slot);

/* CRO 0x750. Returns 1. */
static int theend_yes(void) { return 1; }

/* CRO 0x758. No-op. */
static void theend_noop(void) { /* TODO: not yet decoded */ }

/* --- Constructor (nnroControlObject_ entry point). --- */

/* CRO 0x7ac. Allocates a 0x34-byte instance via imported heap, installs the
 * loader vtable, and stores the parent pointer at +0x04 and the heap handle
 * at +0x20. The "work" pointer at +0x24 is filled by an internal helper
 * (0x804) that constructs the embedded TheEndWork. */
static TheEndProc *theend_create(void *parent);

/* --- Destructor. CRO 0x824. --- */
/* Frees the work object, frees the heap handle, and resets vtable to 0. */
static void theend_destroy(TheEndProc *self);

/* --- Two more trivial "release parent handle" stubs. --- */

/* CRO 0x88c. Releases self->heap and resets vtable. */
static void theend_release_v1(TheEndProc *self);

/* CRO 0x8f0. No-op. */
static void theend_release_noop(void) { /* TODO: not yet decoded */ }

/* CRO 0x8f4. Releases parent handle (counter at +0x14). */
static void theend_release_v2(TheEndProc *self);

/* CRO 0x92c. Releases parent handle (counter at +0x14), alternative path. */
static void theend_release_v3(TheEndProc *self);

/* CRO 0x960. Returns 0. */
static int theend_no(void) { return 0; }

/* --- Standard NN loader infrastructure --- */

/* CRO 0x968. Init for the module's BSS -- sets two error-counter slots to -1. */
static void theend_bss_init(void);

/* CRO 0x994. Loader vtable dispatcher (slot 0..5). */
static int theend_loader_dispatch(void *obj, int slot);