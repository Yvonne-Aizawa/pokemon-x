/*
 * Preliminary decompilation of DllUSGymRock.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: one of the eight US-region gym scene modules (Rock gym).
 * Has the largest static-data segment of the batch (0x1d4 bytes of literal
 * pairs at 0x1034..0x150c -- these are likely tile/dimension tables indexed
 * by gym level).  Behavior is similar to the other gym modules: small object
 * with a 4-state machine and one "rendered" worker.
 *   - bss size 0x20, data size 0x1d4.
 *   - 1 named export: nnroControlObject_ at 0x428 (constructor entry point).
 *   - 10 static-module imports + 2 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x57c..0x650.
 *
 * Recovered:
 *   - 9 function boundaries (see stubs below).
 *   - Object layout: parent at +0x04, parent2 at +0x08, work at +0x0c, a
 *     float field at +0x10 (the "render progress"), state at +0x14 (0..1),
 *     and a 16-byte child view at +0x18.
 *   - Three helper functions: a 1-arg setter at 0x404 (sets a controller
 *     field to -1 or a literal pool reference), a 4-arg finder at 0x318
 *     (searches a 28-entry literal table for a cell-id match), and the
 *     state-machine worker at 0x43c.
 *
 * Not yet decoded:
 *   - The exact 28 entries of the literal pool at 0x400..0x43c (each entry
 *     appears to be a 16-byte struct with 3 32-bit values + a 4-byte tail).
 *   - The 12 imported events called at 0x4c8..0x52c.
 *   - The 0x404 setter's exact behavior on the r1 == -1 path (sets
 *     parent2->field252->c4 to zero) vs the default path (sets c4 to the
 *     literal-pool offset).
 */

#include <stdint.h>

typedef struct GymRockProc GymRockProc;

/* Confirmed from field accesses in the original ARM code. */
struct GymRockProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *parent2;         /* 0x08 */
    void *work;            /* 0x0c */
    float render_progress; /* 0x10 - 1.0f when complete */
    uint16_t state;        /* 0x14 - 0/1 */
    uint8_t reserved16[2];
    void *child_view;      /* 0x18 */
};

/* --- Lifecycle stubs (return 1/0). --- */

/* CRO 0x180..0x1c8: import jump table. */

/* CRO 0x1d0..0x1f0: lifecycle helpers. */
static int gymrock_can_run(void) { return 1; }
static int gymrock_can_stop(void) { return 0; }
static int gymrock_can_draw(void) { return 0; }
static int gymrock_can_other(void) { return 0; }
static void gymrock_release_noop(void);
static void gymrock_release_noop2(void);

/* --- Draw worker. CRO 0x1f4. --- */
/* Reads self->state; if ==1, walks a 4-cell neighborhood via the imported
 * 0x180 service, computes a 5-bit bucket index from the cell id, then
 * broadcasts a clamped (0..19) value through slot 0x190. */
static int gymrock_draw(GymRockProc *self);

/* --- Lifecycle stub. CRO 0x284. --- */
static void gymrock_release_noop3(void);

/* --- Lifecycle stub. CRO 0x294. --- */
static void gymrock_release_noop4(void);

/* --- Setter. CRO 0x298. --- */
/* Reads a 4-tuple at *r1, walks a 28-entry table at +0x314 looking for a
 * triple-match on the first three float slots, and returns the matching
 * entry's 4th value (or -1 if no match). */
static int32_t gymrock_lookup(GymRockProc *self, void *tuple);

/* --- Cell-id dispatcher. CRO 0x318. --- */
/* Looks up self->parent2->field252->c4 from a 24-byte literal table at
 * 0x400 indexed by r1*3; falls back to zero if the entry is invalid. */
static int gymrock_pick_cell(GymRockProc *self, int idx);

/* --- Setter. CRO 0x404. --- */
/* Sets the controller field: writes a literal pool offset (or 0 if r1==-1)
 * to parent2->field252->c4, then updates self->work->c0 with r1. */
static void gymrock_set_cell(GymRockProc *self, int32_t value);

/* --- Per-frame update. CRO 0x43c. --- */
/* Dispatches on self->state (0/1).  State 0 reads gameplay world at
 * self->parent->field50->c28->c0+0x2e4->c4 and updates self->work and
 * self->render_progress; advances to state 1. */
static int gymrock_update(GymRockProc *self);

/* --- Constructor. CRO 0x544. --- */
/* Initializes a GymRockProc with vtable const from literal pool +0x570,
 * stores parent at +0x04, zeroes +0x08/+0x0c/+0x14, sets render_progress
 * to 1.0f. */
static void gymrock_init(GymRockProc *self, void *parent);

/* --- Lifecycle stub. CRO 0x574. --- */
static void gymrock_release_noop5(void);

/* --- Lifecycle stub. CRO 0x578. --- */
static void gymrock_release_noop6(void);

/* --- Standard NN loader infrastructure --- */

/* CRO 0x57c. Init for the module's BSS -- sets two error-counter slots to -1. */
static void gymrock_bss_init(void);

/* CRO 0x5a8. Loader vtable dispatcher (slot 0..5). */
static int gymrock_loader_dispatch(void *obj, int slot);