/*
 * Preliminary decompilation of DllTrainingAppManager.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: Training-app state machine (the "trainer battling your
 * party" subsystem used by Join Avenue and Battle Subway).  Exports the
 * `_ZN9xy_system2bg6System13SetIsCallDrawEb` symbol in addition to
 * nnroControlObject_, suggesting this module exposes a small C++ API surface.
 *   - bss size 0x5c, data size 0x14.
 *   - 2 named exports:
 *       nnroControlObject_                       at 0xcc0 (constructor)
 *       _ZN9xy_system2bg6System13SetIsCallDrawEb at 0xbe8
 *   - 47 static-module imports (no DllField imports).
 *   - The standard NN loader dispatcher tail occupies 0xc64..0xd38.
 *
 * Recovered:
 *   - 10 function boundaries (see stubs below).
 *   - Object layout (a very large struct - the +0x400 / +0x5e4 / +0x5dc offsets
 *     seen in the worker are evidence of a ~0x600-byte internal state area):
 *       +0x00 vtable
 *       +0x04 parent
 *       +0x0c field obj
 *       +0x10 work pointer
 *       +0x14 child
 *       +0x20 draw list
 *       +0x2c state counter (0..15)
 *       +0x31 / +0x33 / +0x40 / +0x44 / +0x45 / +0x46 one-byte flags
 *       +0x48 / +0x4c / +0x60 / +0x64 / +0x88 / +0xa0 / +0xa4 / +0xc8..+0xd8 /
 *         +0x400..+0x5e4 various pointer / byte fields
 *   - The main worker at 0x2c8 dispatches on self->state counter at +0x2c
 *     via a tail-call table at 0x310 (10 entries).
 *   - The exported setter at 0xbe8 sets a single-byte global flag.
 *
 * Not yet decoded:
 *   - The 10-entry tail-call table at 0x310 - target functions visible but
 *     not yet labeled.
 *   - The 0xc24 setter at / 0xcfc helpers in the loader tail.
 *   - The 0x3bc / 0x3d4 / 0x884 / 0xbac / 0xc54 worker functions (5 of them,
 *     each ~0x80..0x100 bytes; they appear to be the 10 tail-call targets).
 *   - The exact behavior of the +0x5e4 byte and the +0x400..+0x5dc work
 *     area.
 */

#include <stdint.h>

typedef struct TrainingAppProc TrainingAppProc;

/* Confirmed from field accesses in the original ARM code. */
struct TrainingAppProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *field;           /* 0x08 (offset 0x0c via parent->field) */
    uint8_t reserved0c[4];
    void *work;            /* 0x10 */
    void *child;           /* 0x14 */
    uint8_t reserved18[8];
    void *draw_list;       /* 0x20 */
    uint8_t reserved24[8];
    uint32_t state;        /* 0x2c - 0..15 */
    uint8_t reserved30;
    uint8_t flag31;         /* 0x31 */
    uint8_t reserved32;
    uint8_t flag33;         /* 0x33 */
    uint8_t reserved34[0x40 - 0x34];
    uint8_t flag40;         /* 0x40 */
    uint8_t reserved41[3];
    uint8_t flag44;         /* 0x44 */
    uint8_t flag45;         /* 0x45 */
    uint8_t flag46;         /* 0x46 */
    uint8_t reserved47;
    uint32_t field48;      /* 0x48 */
    uint32_t field4c;      /* 0x4c */
    uint8_t reserved50[0x60 - 0x50];
    uint32_t field60;      /* 0x60 */
    uint32_t field64;      /* 0x64 */
    uint8_t reserved68[0x7c - 0x68];
    uint32_t field7c;      /* 0x7c */
    uint8_t reserved80[0x88 - 0x80];
    uint32_t field88;      /* 0x88 */
    uint8_t reserved8c[0x9c - 0x8c];
    uint8_t flag9c;        /* 0x9c */
    uint8_t reserved9d[3];
    void *field_a0;        /* 0xa0 */
    uint32_t field_a4;     /* 0xa4 */
    uint32_t field_a8;     /* 0xa8 */
    uint8_t reservedac[0xc8 - 0xac];
    uint8_t state_buffer[0x10]; /* 0xc8..0xd8 (10 byte state) */
    uint8_t reservedd8[0x400 - 0xd8];
    /* large work area follows: ~0x600 bytes of state buffers */
    uint8_t big_area[0x600];     /* 0x400..0xa00 -- approx */
};

/* --- Lifecycle stubs (return 1/0). --- */

/* CRO 0x180..0x2bc: import jump table. */

/* CRO 0x2c0..0x2c4. */
static int training_can_run(void) { return 1; }

/* --- Main worker. CRO 0x2c8. --- */
/* Reads self->flag33; if ==1 and self->state<6, resets both.  Then dispatches
 * on self->state (0..9) via a 10-entry tail-call table at 0x310. */
static int training_run(TrainingAppProc *self);

/* --- Sub-handler. CRO 0x484. --- */
/* Larger worker (~0x120 bytes) - reads the parent's state byte and dispatches
 * on it through a 4-byte lookup at +0x33.  Calls 0x268 to set a field. */
static int training_sub_0(TrainingAppProc *self);

/* --- Sub-handler. CRO 0x728. --- */
/* Larger worker (~0x80 bytes) - looks up a parent field via 0x198 and
 * broadcasts a notification via 0x1a0. */
static int training_sub_1(TrainingAppProc *self);

/* --- Sub-handler. CRO 0x7d8. --- */
static int training_sub_2(TrainingAppProc *self);

/* --- Sub-handler. CRO 0x884. --- */
static int training_sub_3(TrainingAppProc *self);

/* --- Sub-handler. CRO 0xa78. --- */
/* Big worker (~0x100 bytes) - manages the +0x400..+0x600 state area; calls
 * 0x268/0x270 to broadcast frame data. */
static int training_sub_4(TrainingAppProc *self);

/* --- Sub-handler. CRO 0xbac. --- */
static int training_sub_5(TrainingAppProc *self);

/* --- Sub-handler. CRO 0xc54. --- */
static int training_sub_6(TrainingAppProc *self);

/* --- Helper. CRO 0xcfc. --- */
static int training_helper_a(TrainingAppProc *self);

/* --- Helper. CRO 0xd34. --- */
static int training_helper_b(TrainingAppProc *self);

/* --- Helper. CRO 0xe48. --- */
static int training_helper_c(TrainingAppProc *self);

/* --- Standard NN loader infrastructure --- */

/* CRO 0xc64. Init for the module's BSS -- sets two error-counter slots to -1. */
static void training_bss_init(void);

/* CRO 0xc90. Loader vtable dispatcher (slot 0..5). */
static int training_loader_dispatch(void *obj, int slot);