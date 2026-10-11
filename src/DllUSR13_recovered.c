/*
 * Preliminary decompilation of DllUSR13.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: Route 13 region scene module (USR13 = Route 13).  Iterates
 * a list of "trainers in view" and resolves a per-entity gameplay slot id, then
 * advances self->state to the matching sprite phase.  Largest of the gym-class
 * modules after BattlePartySelect.
 *   - bss size 0x20, data size 0x14.
 *   - 1 named export: nnroControlObject_ at 0xb58 (constructor entry point).
 *   - 15 static-module imports + 12 DllField imports.
 *   - The standard NN loader dispatcher tail occupies 0xae8..0xbbc.
 *
 * Recovered:
 *   - 9 function boundaries (see stubs below).
 *   - Object layout (a relatively large object):
 *       +0x00 vtable
 *       +0x04 parent
 *       +0x08 gameplay world ptr
 *       +0x0c field obj (resolves via 0x180)
 *       +0x18 work pointer (heap-allocated, stores 24-byte entries)
 *       +0x6c state (one byte, 0..255)
 *   - The main worker at 0x26c iterates a `count` byte at +0x6c, reads
 *     3-tuples from self->work (slot 0x4 has a 'present' flag, slot 0x2 has
 *     a 16-bit sprite id, slot 0x0 has a target index), and either:
 *       (a) advances the state to the next phase if the entity is present, or
 *       (b) calls 0x1b8 to publish a noop.
 *
 * Not yet decoded:
 *   - The exact sprite-id to phase mapping (the 0x21/0x2e arithmetic at
 *     0x308..0x320 suggests a 4-bit slice plus an offset).
 *   - The 0x664 helper (called from 0x358) -- looks like a sprite-clear
 *     helper that walks the work list.
 *   - The exact 12 imported events called at 0x2c4..0x350.
 */

#include <stdint.h>

typedef struct USR13Proc USR13Proc;

/* Confirmed from field accesses in the original ARM code. */
struct USR13Proc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *parent2;         /* 0x08 - gameplay world */
    void *field;           /* 0xc  - resolves via 0x180 (entity lookup) */
    uint8_t reserved10[8];
    void *work;            /* 0x18 - 24-byte entries, count at +0x6c */
    uint8_t reserved1c[0x6c - 0x1c];
    uint8_t count;         /* 0x6c - one-byte count */
};

/* --- Lifecycle stubs (return 1/0). --- */

/* CRO 0x180..0x240: import jump table. */

/* CRO 0x248..0x268: lifecycle helpers. */
static int usr13_can_run(void) { return 1; }
static int usr13_can_stop(void) { return 0; }
static int usr13_can_draw(void) { return 0; }
static int usr13_can_other(void) { return 0; }
static void usr13_release_noop(void);
static void usr13_release_noop2(void);
static void usr13_release_noop3(void);

/* --- Main worker. CRO 0x26c. --- */
/* Iterates self->count (byte at +0x6c), reads 24-byte entries from
 * self->work, looks up the entity by id via imported 0x180, then dispatches
 * one of three branches based on the entity-presence flag at slot 0x4 of
 * each entry. */
static int usr13_run(USR13Proc *self);

/* --- Lifecycle stub. CRO 0x3c4. --- */
/* Releases self->work via slot 0x1b0. */
static void usr13_release_work(USR13Proc *self);

/* --- Per-frame update. CRO 0x3e8. --- */
/* Iterates 12 entries from the gameplay world's "in-view" list at +0x50
 * (each 16 bytes: 0xc+0x10), filters for sprites in the 0x38..0x3a range,
 * and copies them into self->work (24-byte entries).  When 12 entries are
 * collected, calls 0x1b8 to publish a noop. */
static int usr13_update(USR13Proc *self);

/* --- Per-frame update (alternative path). CRO 0x5a4. --- */
/* 4-state machine. State 0 calls 0x1e0 with r1=0x9d and advances to 1.
 * State 1 calls 0x1e8 and advances to 2 if non-zero. State 2/3 poll
 * self->field at +0x14 and advance to 3. */
static int usr13_update_v2(USR13Proc *self);

/* --- Constructor. CRO 0x6dc. --- */
/* Initializes a USR13Proc: stores parent at +0x04/+0x08, zeroes +0x0c/+0x14,
 * allocates a 0x3c-byte work pointer via imported heap allocator (slot 0x208),
 * fills view tables, and zeroes the byte at +0x6c. */
static void usr13_init(USR13Proc *self, void *parent);

/* --- Destructor. CRO 0x76c. --- */
static void usr13_dtor(USR13Proc *self);

/* --- Lifecycle stub. CRO 0x7a0. --- */
static void usr13_release_noop4(void);

/* --- Sprite-clear helper. CRO 0x664. --- */
/* Called from usr13_run; walks self->work to find the slot whose target
 * index matches r1 and zeroes its 'present' flag. */
static void usr13_sprite_clear(USR13Proc *self, int target_idx);

/* --- Standard NN loader infrastructure --- */

/* CRO 0xa4c. Init for the module's BSS -- sets two error-counter slots to -1. */
static void usr13_bss_init(void);

/* CRO 0xa78. Loader vtable dispatcher (slot 0..5). */
static int usr13_loader_dispatch(void *obj, int slot);