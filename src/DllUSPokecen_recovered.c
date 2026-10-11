/*
 * Preliminary decompilation of DllUSPokecen.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: Pokemon Center scene module (US-region Pokemon Center).
 * Drives the heal-your-pokemon animation: registers the healing player with
 * the gameplay world (slot 0x180/0x188), spins up a 6-slot "pokemon frame"
 * via slot 0x1b8, and pushes the result into the imported DrawList.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x7a4 (constructor entry point).
 *   - 18 static-module imports + 10 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x978..0xa4c.
 *
 * Recovered:
 *   - 11 function boundaries (see stubs below).
 *   - Object layout:
 *       +0x00 vtable
 *       +0x04 parent
 *       +0x08 gameplay world ptr
 *       +0x0c heal flag (one byte - 1 during heal animation)
 *       +0x10 work pointer
 *       +0x14 sub_obj_a (resolves via 0x180)
 *       +0x18 sub_obj_b
 *       +0x20 child (with sub-cells at +0x24 and +0x2c)
 *       +0x2c state (4-byte counter)
 *   - The big worker at 0x3f8 sets up 4 layout entries (slots 0/1/5/6 at
 *     +0x2c/+0x50/+0x74/+0x98) and 4 internal children, then runs two
 *     per-cell render passes that call vtable+0x40 and vtable+0x60.
 *   - The "heal" worker at 0x268 checks self->heal flag at +0x0c and
 *     transitions the heal animation forward.
 *
 * Not yet decoded:
 *   - The 0x6c0 / 0x858 / 0x888 / 0x8c0 / 0x92c worker functions - all
 *     small lifecycle helpers, the exact slot semantics are unclear.
 *   - The literal pool constants at 0x854 and 0x880.
 *   - The exact 0x1b0 service used to register the heal animation (called
 *     from 0x3f8 with 5 args).
 */

#include <stdint.h>

typedef struct PokecenProc PokecenProc;
typedef struct PokecenHeal PokecenHeal;

/* Confirmed from field accesses in the original ARM code. */
struct PokecenProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *world;           /* 0x08 - gameplay world */
    uint8_t heal;          /* 0x0c - one-byte flag */
    uint8_t reserved0d[3];
    void *work;            /* 0x10 */
    void *sub_a;           /* 0x14 - resolves via 0x180 (heal target) */
    void *sub_b;           /* 0x18 */
    uint8_t reserved1c[4];
    void *child;           /* 0x20 - sub-cells at +0x24 and +0x2c */
    uint32_t state;        /* 0x2c - 4-byte state counter */
    uint8_t reserved30[0x10]; /* additional sub-cells */
    void *sub_c;           /* +0x40 */
    uint8_t reserved44[0x10];
    void *sub_d;           /* +0x54 */
    uint8_t reserved58[0x10];
    void *sub_e;           /* +0x68 */
    uint8_t reserved6c[0x10];
    void *sub_f;           /* +0x7c */
    uint8_t reserved80[0x10];
    void *sub_g;           /* +0x90 */
    uint8_t reserved94[0x50];
    /* +0xe4..+0x1cc: shader / animate struct referenced by the worker */
    uint8_t animate[0xe8];
};

/* --- Lifecycle stubs (return 0/1). --- */

/* CRO 0x180..0x238: import jump table. */

/* CRO 0x240..0x264: lifecycle helpers. */
static int pokecen_can_run(void) { return 1; }
static int pokecen_can_stop(void) { return 1; }
static int pokecen_can_draw(void) { return 0; }
static int pokecen_can_other(void) { return 0; }
static void pokecen_release_noop(void);

/* --- Heal animator. CRO 0x268. --- */
/* Iterates 2 cells and dispatches heal animation per cell. Reads the
 * self->heal byte at +0x0c; if !=1, transitions.  Uses float registers
 * (vpush {d8}) for cell timing. */
static int pokecen_heal_anim(PokecenProc *self);

/* --- Destroy. CRO 0x378. --- */
/* Iterates the 5 cells laid out by the worker and calls vtable+0x04 on each,
 * then releases 5 layout entries (slot 0x188).  Finally frees self->work
 * via slot 0x190/0x198. */
static int pokecen_destroy(PokecenProc *self);

/* --- Main worker. CRO 0x3f8. --- */
/* Sets up 4 layout entries at +0x2c/+0x50/+0x74/+0x98 with imported slots
 * 0x1a0/0x1a8/0x1b8.  Reads the gameplay world via +0x180, pushes a frame
 * data blob (via 0x1c0), then runs two per-cell render passes that call
 * vtable+0x40 and vtable+0x60 on each cell.  When done, sets state = 3. */
static int pokecen_run(PokecenProc *self);

/* --- Per-frame update. CRO 0x6c0. --- */
/* 4-state machine over self->state (0/1/2/3).  State 0 calls 0x1d8 with
 * r1=0x9d and advances to 1. State 1 calls 0x1e0 and advances to 2 if
 * non-zero. State 2/3 poll self->sub_obj_b at +0x14 and advance to 3. */
static int pokecen_update(PokecenProc *self);

/* --- Constructor. CRO 0x7b4. --- */
/* Initializes a PokecenProc: stores parent at +0x04, world at +0x08,
 * zero-init +0x10..+0x2c, allocates 5 layout entries + 0x3c-byte work
 * pointer. */
static void pokecen_init(PokecenProc *self, void *parent);

/* --- Destructor. CRO 0x858. --- */
static void pokecen_dtor(PokecenProc *self);

/* --- Lifecycle stub. CRO 0x888. --- */
static void pokecen_release_v1(void); /* TODO: not yet decoded */

/* --- Lifecycle stub. CRO 0x8c0. --- */
static void pokecen_release_v2(void); /* TODO: not yet decoded */

/* --- Lifecycle stub. CRO 0x92c. --- */
static void pokecen_release_v3(void); /* TODO: not yet decoded */

/* --- Standard NN loader infrastructure --- */

/* CRO 0x978. Init for the module's BSS -- sets two error-counter slots to -1. */
static void pokecen_bss_init(void);

/* CRO 0x9a4. Loader vtable dispatcher (slot 0..5). */
static int pokecen_loader_dispatch(void *obj, int slot);