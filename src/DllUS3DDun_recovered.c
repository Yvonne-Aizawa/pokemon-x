/*
 * Preliminary decompilation of DllUS3DDun.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: "US 3D dungeon" subscene (likely the ice-rock cave or the
 * connecting tunnel).  Iterates a short list of cells and dispatches a pair of
 * gameplay events per cell.  Contains a shuffle routine (Fisher-Yates-like) at
 * 0x4d0 that randomizes a 5-entry table before broadcasting.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x6d0.
 *   - 23 static-module imports + 5 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x824..0x8f8.
 *
 * Recovered:
 *   - 7 function boundaries (see stubs below).
 *   - Object layout: parent at +0x04, field obj at +0x08, gameplay world ptr
 *     at +0x0c, status at +0x14 (one byte), an array of cell handles at
 *     +0x18/+0x1c, count at +0x1c, work ptr at +0x24, heap at +0x28.
 *   - The shuffle uses a Fisher-Yates over `count` uint16_t entries stored at
 *     `self->cell_table[0..2*count-1]`.
 *
 * Not yet decoded:
 *   - The exact 12 imported events (each "cell" handler at 0x39c/0x568/0x58c
 *     broadcasts three parameters - one constant + two runtime values).
 *   - The vtable slot table at 0x8dc..0x8f8.
 *   - Whether the 0x404 worker is the "render" path or the "shuffle" path.
 */

#include <stdint.h>

typedef struct Dun3DProc Dun3DProc;
typedef struct Dun3DWork Dun3DWork;

/* Confirmed from field accesses in the original ARM code. */
struct Dun3DProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *field;           /* 0x08 */
    void *world;           /* 0x0c */
    uint8_t status14;      /* 0x14 - one-byte flag */
    uint8_t reserved15[3];
    void *cell_a;          /* 0x18 */
    uint32_t cell_count;   /* 0x1c */
    void *cell_b;          /* 0x20 */
    void *work;            /* 0x24 */
    void *heap;            /* 0x28 */
};

struct Dun3DWork {
    void *cells[8];        /* 0x00..0x1f - cell handles */
};

/* --- Lifecycle stubs (return 0 / 1). --- */

/* CRO 0x180..0x240: import jump table (twelve slots, mostly static + a few
 * DllField). */

/* CRO 0x248..0x270: lifecycle helpers -- several bx-lr stubs. */
static int dun3d_can_run(void) { return 1; }
static int dun3d_can_stop(void) { return 0; }
static int dun3d_can_draw(void) { return 0; }
static int dun3d_can_other(void) { return 0; }
static void dun3d_release_noop(void);

/* --- Per-frame update. CRO 0x274. --- */
/* Polls an imported "world is ready" check (slot 0x180) in a busy-wait loop.
 * When it returns the success code (0x95), increments self->cell_count at
 * +0x1c. Once the loop terminates, calls the cell-handler at 0x404 (the
 * "shuffle & broadcast" path) and returns 1. */
static int dun3d_update(Dun3DProc *self);

/* --- Cell-shuffle worker. CRO 0x404. --- */
/* For each cell, calls the imported cell-broadcast slot (0x198) three times
 * with parameter triples drawn from self->cell_a/self->cell_b.  Then runs a
 * Fisher-Yates-style shuffle over `count` uint16_t slots stored in a heap
 * buffer at self->cell_a, and rebroadcasts the shuffled result over 0x1d8. */
static int dun3d_run_cells(Dun3DProc *self);

/* --- Lifecycle helpers --- */

/* CRO 0x5dc. Reads vtable+0x1c8 of self->field to find the next stage index,
 * allocates a 0x28-byte work object via imported heap, stores parent handle
 * and an inline vtable pointer at +0x00, zeroes self->work->field at +0x18,
 * and returns 1. */
static int dun3d_advance(Dun3DProc *self);

/* --- Per-frame update (alternative path). CRO 0x710. --- */
/* Dispatches on self->state (0/1/other).  State 0 reads self->state at +0x24,
 * calls vtable+0x24 of self->field twice, advances state to 1. */
static int dun3d_update_v2(Dun3DProc *self);

/* --- Constructor. CRO 0x7cc. --- */
/* Initializes a Dun3DProc: stores parent at +0x04 and +0x08, status at +0x14,
 * cell handles at +0x18..0x20, count at +0x24, heap at +0x28 (via imported
 * "heap create" service). */
static void dun3d_init(Dun3DProc *self, void *parent);

/* --- Lifecycle stub. CRO 0x820. --- */
static void dun3d_release_v1(void); /* TODO: not yet decoded */

/* --- Standard NN loader infrastructure --- */

/* CRO 0x824. Init for the module's BSS -- sets two error-counter slots to -1. */
static void dun3d_bss_init(void);

/* CRO 0x850. Loader vtable dispatcher (slot 0..5). */
static int dun3d_loader_dispatch(void *obj, int slot);