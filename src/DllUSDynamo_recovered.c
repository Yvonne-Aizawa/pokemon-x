/*
 * Preliminary decompilation of DllUSDynamo.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: small region event/distance computation.  Dynamo seems to
 * compute a player's distance to a set of 8 region "buckets" and broadcast a
 * field value over the gameplay socket.  Likely a US-region update tick.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x200 (inside the dispatcher).
 *   - 6 static-module imports + 2 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x354..0x428.
 *
 * Recovered:
 *   - 9 function boundaries (see stubs below).
 *   - Object layout: small struct, 4-byte vtable at +0x00, parent at +0x04,
 *     work pointer at +0x08, float at +0x0c (position?), uint16_t at +0x10
 *     (state machine), and a couple of pointer fields.
 *   - The "tick" function at 0x1d4 dispatches on state 0x10: when ==1, computes
 *     Euclidean distance in a 4-cell neighborhood and emits a 14-bit value.
 *
 * Not yet decoded:
 *   - The 8 floating-point constants in the literal pool at 0x298 (referenced
 *     by the distance calculation; not yet typed).
 *   - The vtable pointers at 0x3a0 and 0x40c..0x428.
 *   - Two short mystery functions at 0x350 / 0x3a8 - candidates for being
 *     the "is_call_draw" toggle setter used by the export.
 */

#include <stdint.h>

typedef struct DynamoProc DynamoProc;

/* Confirmed from field accesses in the original ARM code. */
struct DynamoProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *field;          /* 0x08 */
    float position;        /* 0x0c - xz position */
    uint16_t state;        /* 0x10 */
    uint8_t reserved12[2];
};

typedef struct DynamoCtor DynamoCtor;

/* The constructor at 0x320 builds a DynamoProc at +0x00..0x18; not all fields
 * are named, and the literal-pool constant at +0x04 looks like a vtable. */
struct DynamoCtor {
    uint32_t vtable_const; /* 0x00 - usually an absolute address literal */
    void *parent;          /* 0x04 */
    void *field;          /* 0x08 */
    float position;        /* 0x0c */
    uint32_t reserved10;
    uint16_t state;        /* 0x14 */
    uint8_t reserved16[2];
};

/* --- Lifecycle stubs --- */

/* CRO 0x1b0 */
static int dynamo_can_run(void) { return 1; }
/* CRO 0x1b4 */
static int dynamo_can_stop(void) { return 0; }
/* CRO 0x1b8 */
static int dynamo_can_draw(void) { return 0; }
/* CRO 0x1c0 */
static int dynamo_no(void) { return 0; }
/* CRO 0x1c4 */
static int dynamo_yes(void) { return 1; }
/* CRO 0x1c8 */
static void dynamo_noop(void) { /* TODO: not yet decoded */ }

/* --- Main tick. CRO 0x1d4. --- */
/* When self->state == 1, walks a 4-cell neighborhood grid (the static data at
 * 0x400 holds cell-coords), computes a Manhattan/Euclidean distance per cell,
 * and pushes the result into the imported broadcast service (slot 0x190). */
static int dynamo_tick(DynamoProc *self);

/* --- Lifecycle stubs --- */

/* CRO 0x2c0 */
static void dynamo_release_noop(void) { /* TODO: not yet decoded */ }
/* CRO 0x2c4 */
static void dynamo_release_v1(void); /* TODO: not yet decoded */

/* --- Per-frame update. CRO 0x2c8. --- */
/* Dispatches on self->state (0/1/other).  State 0 stores 1.0f into
 * self->position and broadcasts slot 0x1a0 with r1=0. */
static int dynamo_update(DynamoProc *self);

/* --- Constructor. CRO 0x320. --- */
/* Initializes a DynamoCtor from the literal pool at +0x348. Stores parent
 * pointer at +0x04, zeroes +0x08/+0x10, sets +0x14 = 0. */
static void dynamo_init(DynamoCtor *self, void *parent);

/* --- Lifecycle stubs --- */

/* CRO 0x350 */
static void dynamo_release_v2(void); /* TODO: not yet decoded */

/* --- Standard NN loader infrastructure --- */

/* CRO 0x354. Init for the module's BSS -- sets two error-counter slots to -1. */
static void dynamo_bss_init(void);

/* CRO 0x380. Loader vtable dispatcher (slot 0..5). */
static int dynamo_loader_dispatch(void *obj, int slot);