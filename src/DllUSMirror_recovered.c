/*
 * Preliminary decompilation of DllUSMirror.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: short "mirror item" event broadcaster.  Iterates a count of
 * mirrors in the field, calls a vtable slot per item, and submits the result
 * via two gameplay-broadcast imports.  This is a small object whose only
 * non-trivial logic is the 0x200 worker.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0x258 (inside the dispatcher).
 *   - 7 static-module imports + 4 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0x3ac..0x480.
 *
 * Recovered:
 *   - 7 function boundaries (see stubs below).
 *   - Object layout: small struct, parent at +0x04, work at +0x0c (carries
 *     a 32-bit index that is compared to -1 to skip work), and the active
 *     count at +0x10.
 *   - The "tick" function at 0x200 iterates self->field count and broadcasts
 *     two slots per iteration: 0x198 (with r1=1 first time) and 0x1a8.
 *
 * Not yet decoded:
 *   - The setter at 0x1f0 (writes r1 into the field at +0x00 of an object
 *     stored at self->field) - signature `(setter_t)(int, void*)`.
 *   - The vtable slot table at 0x464..0x480.
 *   - The destructor at 0x3a4 (probably just one-liner release).
 */

#include <stdint.h>

typedef struct MirrorProc MirrorProc;
typedef struct MirrorField MirrorField;

/* Confirmed from field accesses in the original ARM code. */
struct MirrorProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *field;           /* 0x08 */
    void *work;            /* 0x0c */
    uint32_t count;        /* 0x10 - mirrored-item count */
};

struct MirrorField {
    int32_t slot;          /* 0x00 - compared to -1 by the worker */
    uint8_t reserved04[8]; /* 0x04..0x0b */
    int32_t index;         /* 0x0c - loop counter */
};

/* --- Lifecycle stubs (return 1/0). --- */

/* CRO 0x1c8 */
static int mirror_can_run(void) { return 1; }
/* CRO 0x1d0 */
static int mirror_can_stop(void) { return 0; }
/* CRO 0x1d4 */
static int mirror_can_draw(void) { return 0; }
/* CRO 0x1d8 */
static int mirror_can_other(void) { return 0; }
/* CRO 0x1dc */
static int mirror_yes(void) { return 1; }
/* CRO 0x1e0 */
static void mirror_noop(void) { /* TODO: not yet decoded */ }
/* CRO 0x1e4 */
static void mirror_release_noop(void) { /* TODO: not yet decoded */ }
/* CRO 0x1e8 */
static void mirror_release_noop2(void) { /* TODO: not yet decoded */ }

/* --- Setter. CRO 0x1f0. --- */
/* self->field->slot = r1; -- writes the 32-bit value passed in r1 into the
 * first 4 bytes of the object stored at self->field. */
static void mirror_set(MirrorProc *self, uint32_t value);

/* --- Lifecycle stub. CRO 0x1fc. --- */
static void mirror_release_noop3(void);

/* --- Main worker. CRO 0x200. --- */
/* Iterates the mirror list at self->field. For each entry, calls vtable+0x5c
 * (count of mirrors in the current cell), then vtable+0x60 (indexed accessor
 * returning a handle) and finally broadcasts via slots 0x198 / 0x1a8.  The
 * dispatch loop also guards on self->work->slot != -1. */
static int mirror_run(MirrorProc *self);

/* --- Lifecycle stub. CRO 0x2e8. --- */
static void mirror_release_noop4(void);

/* --- Per-frame update. CRO 0x2ec. --- */
/* Dispatches on self->state (0/1/other).  State 0 caches the gameplay world
 * pointer at +0x0c, then sets self->state = 1. */
static int mirror_update(MirrorProc *self);

/* --- Constructor. CRO 0x380. --- */
/* Initializes a MirrorProc with vtable const from the literal pool at +0x3a0,
 * stores parent at +0x04, zeroes +0x0c and +0x10. */
static void mirror_init(MirrorProc *self, void *parent);

/* --- Lifecycle stub. CRO 0x3a8. --- */
static void mirror_release_noop5(void);

/* --- Standard NN loader infrastructure --- */

/* CRO 0x3ac. Init for the module's BSS -- sets two error-counter slots to -1. */
static void mirror_bss_init(void);

/* CRO 0x3d8. Loader vtable dispatcher (slot 0..5). */
static int mirror_loader_dispatch(void *obj, int slot);