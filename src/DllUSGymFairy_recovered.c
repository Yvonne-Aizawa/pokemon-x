/*
 * Preliminary decompilation of DllUSGymFairy.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: one of the eight US-region gym scene modules (Fairy gym).
 * Builds a small object with two child views (an "outer" pair +0x18/+0x1c and
 * an "inner" pair), drives them with a 4-state machine, and dispatches
 * vtable slots 0x1c/0x38/0x40/0x6c per frame.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x678 (constructor entry point).
 *   - 15 static-module imports + 9 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x7cc..0x8a0.
 *
 * Recovered:
 *   - 9 function boundaries (see stubs below).
 *   - Object layout (sparse, mostly pointer fields):
 *       +0x00 vtable
 *       +0x04 parent
 *       +0x08 parent2 (gameplay world)
 *       +0x0c state (one byte -- 0..3)
 *       +0x10 work pointer
 *       +0x14 field
 *       +0x18 child slot A
 *       +0x1c child slot B
 *       +0x20 view table 0 (5 entries at +0x20, +0x24, +0x28, +0x2c, +0x30)
 *       +0x44 view table 1 (5 entries at +0x44, +0x48, +0x4c, +0x50, +0x54)
 *       +0x68 view table 2 (9 entries at +0x68..+0x8c)
 *   - Two helper functions called from the worker: a setter at 0x240 and a
 *     "find slot" stub at 0x5b8 (3-arg, looks up an entry in a 4-entry table).
 *
 * Not yet decoded:
 *   - The exact 5 imported events called at 0x3e0..0x460.
 *   - The literal pool constants at 0x4a4, 0x75c..0x794, 0x7c4..0x7c8.
 *   - The state machine inputs - which fields the state=0 path expects to
 *     be initialized by nnroControlObject_.
 */

#include <stdint.h>

typedef struct GymFairyProc GymFairyProc;

/* Confirmed from field accesses in the original ARM code. */
struct GymFairyProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *parent2;         /* 0x08 */
    uint32_t state;        /* 0x0c - 0/1/2/3 */
    void *work;            /* 0x10 */
    void *field;           /* 0x14 */
    void *child_a;         /* 0x18 */
    void *child_b;         /* 0x1c */
    void *view0[5];        /* 0x20..0x30 (5 ptrs, 4 bytes each) */
    uint8_t reserved34[8];
    void *view1[5];        /* 0x44..0x54 */
    uint8_t reserved58[16];
    void *view2[9];        /* 0x68..0x8c */
    uint8_t reserved90[0x90-0x8c];
    uint8_t flag;          /* 0x90 - one-byte flag set by the worker */
    uint8_t reserved91[0xb0-0x91];
    uint8_t flag_b0;       /* 0xb0 - one-byte flag */
};

/* --- Lifecycle stubs (return 1/0). --- */

/* CRO 0x180..0x218: import jump table. */

/* CRO 0x220..0x238: lifecycle helpers. */
static int gymfairy_can_run(void) { return 1; }
static int gymfairy_can_stop(void) { return 0; }
static int gymfairy_can_draw(void) { return 0; }
static int gymfairy_can_other(void) { return 0; }
static void gymfairy_release_noop(void);

/* --- Setter. CRO 0x240. --- */
/* Reads self->view0[idx].child->vtable->slot_0x1c(r2); the indirect call
 * walks the vtable of a child UI surface and invokes the "set field" slot. */
static void gymfairy_set_slot(GymFairyProc *self, int idx, int value);

/* --- Lifecycle stub. CRO 0x258. --- */
static void gymfairy_release_noop2(void);

/* --- Destroy. CRO 0x260. --- */
/* Releases two child UI surfaces (0x18 and 0x1c) by calling their vtable
 * destructors, then frees 4 view-entries from each of the two view tables
 * (0x20 and 0x44), and finally releases self->work (calling 0x190 then 0x198). */
static int gymfairy_destroy(GymFairyProc *self);

/* --- Main worker. CRO 0x2e8. --- */
/* Builds 5 layout slots into view0 (+0x20..+0x30) and view1 (+0x44..+0x54)
 * using imported services 0x1a0/0x1a8.  Then for child slots +0x18/+0x1c
 * calls vtable+0x1c and vtable+0x6c on each.  Finally sets self->state = 4. */
static int gymfairy_run(GymFairyProc *self);

/* --- Lifecycle stub. CRO 0x4a8. --- */
static void gymfairy_release_noop3(void);

/* --- Per-cell renderer. CRO 0x4ac. --- */
/* Iterates the cell-handle count returned by an imported service at 0x1c0,
 * and calls vtable+0x38/0x40 on each cell to push a draw list update.
 * If the imported service 0x1c8 returns a non-NULL pointer, propagates that
 * pointer through 0x1d0/0x1d8 and finally calls vtable+0x1c on the child
 * surface to commit the frame. */
static int gymfairy_draw_cell(GymFairyProc *self, int idx);

/* --- Per-cell query. CRO 0x56c. --- */
/* Iterates a cell list and queries vtable+0x60 on each cell; returns 1 if
 * any cell matches, otherwise 0. */
static int gymfairy_query_cell(GymFairyProc *self, int idx);

/* --- Setter. CRO 0x5b8. --- */
/* 3-arg form: writes r1 into the vtable+0x3c slot of the child at
 * self->view0[idx].child->child (i.e. the grandchild). */
static void gymfairy_set_slot2(GymFairyProc *self, int idx, int value);

/* --- Per-frame update. CRO 0x5d0. --- */
/* Dispatches on self->state (0/1/2/3).  State 0 calls imported 0x1e0 with
 * r1=0x9d and advances to 1. State 1 calls 0x1e8 and advances to 2 if the
 * call returned non-zero. State 2/3 polls self->field at +0x14 and toggles
 * self->state to 3. */
static int gymfairy_update(GymFairyProc *self);

/* --- Constructor. CRO 0x6d4. --- */
/* Initializes a GymFairyProc: stores parent at +0x04 and +0x08, zeroes
 * +0x0c/+0x14, fills view0/view1 with 4 entries each, and allocates a
 * 0x3c-byte work pointer via imported heap allocator (slot 0x208). */
static void gymfairy_init(GymFairyProc *self, void *parent);

/* --- Destructor. CRO 0x764. --- */
static void gymfairy_dtor(GymFairyProc *self);

/* --- Lifecycle stub. CRO 0x798. --- */
static void gymfairy_release_noop4(void);

/* --- Standard NN loader infrastructure --- */

/* CRO 0x7cc. Init for the module's BSS -- sets two error-counter slots to -1. */
static void gymfairy_bss_init(void);

/* CRO 0x7f8. Loader vtable dispatcher (slot 0..5). */
static int gymfairy_loader_dispatch(void *obj, int slot);