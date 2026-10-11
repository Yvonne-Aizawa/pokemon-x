/*
 * Preliminary decompilation of DllUSGymGrass.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: one of the eight US-region gym scene modules (Grass gym).
 * Layout is similar to DllUSGymFairy but with 16 child cells (vs Fairy gym's
 * 2 cells), 28 layout entries, and 13 cell-render passes.  This is the busiest
 * of the gym modules.
 *   - bss size 0x20, data size 0x50.
 *   - 1 named export: nnroControlObject_ at 0x834 (constructor entry point).
 *   - 15 static-module imports + 10 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x8c8..0x99c.
 *
 * Recovered:
 *   - 8 function boundaries (see stubs below).
 *   - Object layout (very wide; pointers via 13 inner "render" cells):
 *       +0x00 vtable
 *       +0x04 parent
 *       +0x08 parent2
 *       +0x0c work pointer
 *       +0x18..+0x54: 16 child cell pointers (16*4 = 0x40 bytes)
 *       +0x58..+0xc4: 14 layout entries (each 8 bytes - probably (ptr, count))
 *       +0xc8..+0x168: 13 cell render-pairs (each 8 bytes)
 *   - Destroy function at 0x250 walks 16 cells, calls vtable+0x04 on each,
 *     then releases 28 layout entries, then releases self->work.
 *   - Worker at 0x2d0 builds layout entries + render pairs and runs 13
 *     per-cell render passes.
 *
 * Not yet decoded:
 *   - The exact 13 imported events called at 0x3e0..0x414.
 *   - The literal pool constants at 0x564..0x56c (float constants used in
 *     the worker).
 *   - The 0x828 destructor (one-liner release).
 */

#include <stdint.h>

typedef struct GymGrassProc GymGrassProc;

/* Confirmed from field accesses in the original ARM code. */
struct GymGrassProc {
    void *vtable;            /* 0x00 */
    void *parent;            /* 0x04 */
    void *parent2;           /* 0x08 */
    void *work;              /* 0x0c */
    uint8_t reserved10[8];
    void *cells[16];         /* 0x18..0x54 (16 ptrs) */
    void *layout[14];        /* 0x58..0xc4 (14 ptrs) */
    void *renders[26];       /* 0xc8..0x168 (26 ptrs - 13 pairs) */
};

/* --- Lifecycle stubs (return 1/0). --- */

/* CRO 0x180..0x220: import jump table. */

/* CRO 0x228..0x248: lifecycle helpers. */
static int gymgrass_can_run(void) { return 1; }
static int gymgrass_can_stop(void) { return 0; }
static int gymgrass_can_draw(void) { return 0; }
static int gymgrass_can_other(void) { return 0; }
static void gymgrass_release_noop(void);
static void gymgrass_release_noop2(void);
static void gymgrass_release_noop3(void);

/* --- Destroy. CRO 0x250. --- */
/* Iterates 16 cells (self->cells[0..15]), calls vtable+0x04 on each, then
 * releases 28 layout entries (slot 0x180), then frees self->work via slots
 * 0x188/0x190. */
static int gymgrass_destroy(GymGrassProc *self);

/* --- Main worker. CRO 0x2d0. --- */
/* Builds 14 layout entries (5 of them in two passes each), registers them
 * via imported slots 0x198/0x1a0/0x1a8, then runs 13 per-cell render passes
 * (0x1b0..0x1c0).  Each render pass reads a gameplay world pointer and
 * pushes float triples to slot 0x1b8. */
static int gymgrass_run(GymGrassProc *self);

/* --- Per-cell renderer. CRO 0x4ac. --- */
/* Looks up the cell at self->cells[idx] and calls vtable+0x18 with three
 * float args (read from the sp-area at offset 0..0x0b). */
static void gymgrass_cell_set(GymGrassProc *self, int idx);

/* --- Per-cell query. CRO 0x5c8. --- */
/* Iterates the cells from idx..idx+count, calling vtable+0x60 on each; if
 * any returns non-zero, sets self->state to 1 and advances. */
static int gymgrass_cell_query(GymGrassProc *self, int idx);

/* --- Per-frame update. CRO 0x5d4. --- */
/* Dispatches on self->state (0/1/2/3).  State 0 calls imported 0x1e0 with
 * r1=0x9d and advances to 1. State 1 calls 0x1e8 and advances to 2 if
 * non-zero. State 2/3 poll self->field at +0x14 and advance to 3. */
static int gymgrass_update(GymGrassProc *self);

/* --- Constructor. CRO 0x6dc. --- */
/* Initializes a GymGrassProc: stores parent at +0x04/+0x08, zeroes +0x0c/+0x14,
 * initializes 28 layout entries + 16 child cells + a 0x3c-byte work pointer. */
static void gymgrass_init(GymGrassProc *self, void *parent);

/* --- Destructor. CRO 0x76c. --- */
static void gymgrass_dtor(GymGrassProc *self);

/* --- Lifecycle stub. CRO 0x7a0. --- */
static void gymgrass_release_noop4(void);

/* --- Standard NN loader infrastructure --- */

/* CRO 0x7cc. Init for the module's BSS -- sets two error-counter slots to -1. */
static void gymgrass_bss_init(void);

/* CRO 0x7f8. Loader vtable dispatcher (slot 0..5). */
static int gymgrass_loader_dispatch(void *obj, int slot);