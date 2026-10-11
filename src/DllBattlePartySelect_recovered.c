/*
 * Preliminary decompilation of DllBattlePartySelect.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module summary: Battle-party-selection overlay (the screen that pops up
 * before a battle to let the player pick which 6 Pokemon to send in).  The
 * largest single non-battle module in the batch (text segment 0x1734 bytes,
 * ~5000 bytes of static data, ~90 imported events).  Has its own private
 * subscene machinery and uses the imported DllField world ptr to grab the
 * player's party box.
 *   - bss size 0x20, data size 0x40.
 *   - 1 named export: nnroControlObject_ at 0x1684 (constructor entry point).
 *   - 88 static-module imports (no DllField imports).
 *   - The standard NN loader dispatcher tail occupies 0x185c..0x1930.
 *
 * Recovered:
 *   - 27 function boundaries (see stubs below).  Most are short lifecycle
 *     helpers returning 0/1; the bulk is split across three named "update"
 *     paths at 0x50c, 0xc68, and 0xfec, plus a "big worker" at 0x121c.
 *   - Object layout: parent at +0x04, work at +0x0c (subscene struct, 0x90
 *     bytes), draw list head at +0x20, status byte at +0x24 (0/1/2), and
 *     several small flag bytes scattered between +0x28..+0x30.
 *   - The static data tables at 0x1034..0x21d8 encode Pokemon-list indices
 *     and per-Pokemon party-slot weights (the pattern `3,6,9,0xc,...` at
 *     0x2070..0x21a8 strongly suggests a 4-byte lookup of pokemon_id ->
 *     party_index with stride 0xa; needs cross-referencing against the
 *     crodata Pokemon table).
 *
 * Not yet decoded:
 *   - The exact subscene bindings -- which imported slots correspond to
 *     "list_view" / "pokemon_icon" / "command_window".
 *   - The big worker at 0xfec has 8 callee-saved registers and is ~0x130
 *     bytes long; only its prologue is recognized here.
 *   - The 0x15c0 helper contains a tail-call into 0x198 (probably the
 *     shared "release parent handle" tail), but its slot 0 is a 4-arg call.
 *   - The 0x1694 destructor looks like a release-then-tail-call pattern.
 *   - The literal pool constants at 0x2070..0x21d8 -- the 144-byte "pokemon
 *     weight" table.
 */

#include <stdint.h>

typedef struct PartySelectProc PartySelectProc;
typedef struct PartySelectSubscene PartySelectSubscene;

/* Confirmed from field accesses in the original ARM code. */
struct PartySelectProc {
    void *vtable;          /* 0x00 */
    void *parent;          /* 0x04 */
    void *work;            /* 0x08 (8 bytes) */
    void *subscene;         /* 0x0c - heap-allocated 0x90-byte struct */
    void *draw_list;       /* 0x10 */
    uint8_t reserved14[8];
    void *draw_head;       /* 0x20 - subscene draw head */
    uint8_t reserved24[4];
    uint8_t status;         /* 0x24 - one-byte status (0/1/2) */
    uint8_t reserved25[3];
    uint8_t state28;       /* 0x28 - one-byte state */
    uint8_t state29;       /* 0x29 - one-byte flag */
    uint8_t reserved2a[2];
    void *draw_head2;      /* 0x2c */
    void *draw_head3;      /* 0x30 */
    uint8_t reserved34[8];
    void *list_view;       /* 0x3c */
};

struct PartySelectSubscene {
    uint8_t reserved00[0x24];
    uint8_t flag24;        /* 0x24 - one-byte flag */
    uint8_t reserved25[3];
    void *parent;          /* 0x28 - back-pointer */
    uint8_t reserved2c[0x54];
    void *child;           /* 0x80 - one child object */
    uint8_t reserved84[4];
    void *child2;          /* 0x88 - second child */
    uint8_t reserved8c[4];
    uint8_t flag8c;        /* 0x8c */
    uint8_t flag8d;        /* 0x8d */
    uint8_t flag8e;        /* 0x8e */
    uint8_t reserved8f;
    void *list_view;       /* 0x90 */
};

/* --- Lifecycle stubs (return 0/1). --- */

/* CRO 0x180..0x378: import jump table. */

/* CRO 0x380..0x3cc: lifecycle helpers. */
static int partysel_can_run(void) { return 1; }
static int partysel_can_stop(void) { return 0; }
static int partysel_can_draw(void) { return 0; }
static int partysel_can_other(void) { return 0; }
static int partysel_yes(void) { return 1; }
static int partysel_no(void) { return 0; }
static void partysel_noop(void);
static void partysel_release_noop(void);

/* --- Destructor. CRO 0x3d0. --- */
/* Calls a virtual destructor (vtable+0x18) on self->subscene, frees
 * self->work via slot 0x1b0, and zeroes self->state28. */
static int partysel_destroy(PartySelectProc *self);

/* --- Lifecycle stub. CRO 0x504. --- */
static int partysel_can_other2(void) { return 1; }

/* --- Main update. CRO 0x50c. --- */
/* Initializes self->state29 = 0, then opens the subscene and registers it.
 * Dispatches on self->status (0/1/2).  Reads self->subscene->flag8c..flag8e
 * to drive three sub-states of the selection animation. */
static int partysel_run(PartySelectProc *self);

/* --- Per-cell iterator. CRO 0x7e8. --- */
/* Iterates the 12 entries in self->subscene->parent and emits a "frame
 * present" notification for each via slot 0x1f0. */
static int partysel_iterate_cells(PartySelectProc *self);

/* --- Setter. CRO 0x864. --- */
static void partysel_set_a(PartySelectProc *self);

/* --- Setter. CRO 0x8b4. --- */
static void partysel_set_b(PartySelectProc *self);

/* --- Helper. CRO 0x904. --- */
/* Calls a virtual method on self->work via slot 0x1c8 (3-arg). */
static int partysel_helper_a(PartySelectProc *self);

/* --- Per-frame update. CRO 0x940. --- */
/* Reads a byte from the work buffer; returns 0/1. */
static int partysel_check(PartySelectProc *self);

/* --- Lifecycle helper. CRO 0x980. --- */
static void partysel_release_v1(void) { /* TODO: not yet decoded */ }

/* --- Lifecycle helper. CRO 0x988. --- */
static void partysel_release_v2(void) { /* TODO: not yet decoded */ }

/* --- Per-cell renderer. CRO 0x98c. --- */
/* For each sub-cell, calls vtable+0x40 and vtable+0x44 to update frame
 * data; emits a "frame present" notification via slot 0x1c8. */
static int partysel_render_cell(PartySelectProc *self);

/* --- Float worker. CRO 0x994. --- */
/* Reads floats from a literal pool at 0xa2c and processes them via slot
 * 0x1d8 with 5 args. */
static int partysel_float_worker(PartySelectProc *self);

/* --- Helper. CRO 0xa40. --- */
static void partysel_helper_b(PartySelectProc *self);

/* --- Helper. CRO 0xa8c. --- */
static void partysel_helper_c(PartySelectProc *self);

/* --- Per-cell renderer. CRO 0xad4. --- */
/* Calls vtable+0x40 on each sub-cell. */
static int partysel_render_subcell(PartySelectProc *self);

/* --- Lifecycle stubs. CRO 0xb20 / 0xb8c. --- */
static int partysel_yes_v2(void) { return 1; }
static int partysel_no_v2(void) { return 0; }

/* --- Setter. CRO 0xbb4. --- */
/* Conditional write -- if r1 < 0, return immediately (via bxlt lr); else
 * call into the next function. */
static int partysel_set_conditional(PartySelectProc *self, int idx);

/* --- Main update. CRO 0xc68. --- */
/* 4-arg function: dispatches on a state byte and broadcasts a per-frame
 * notification through 8 callee-saved registers. */
static int partysel_update_big(PartySelectProc *self, int arg1, int arg2, int arg3);

/* --- Lifecycle stub. CRO 0xe88. --- */
static void partysel_release_v3(void) { /* TODO: not yet decoded */ }

/* --- Per-cell renderer. CRO 0xe8c. --- */
/* Iterates the 5 children of self->subscene, calls vtable+0x40 on each. */
static int partysel_render_children(PartySelectProc *self);

/* --- Helper. CRO 0xf68. --- */
static void partysel_helper_d(PartySelectProc *self);

/* --- Lifecycle stub. CRO 0xf94. --- */
static int partysel_yes_v3(void) { return 1; }

/* --- Big worker. CRO 0xfec. --- */
/* 10 callee-saved registers, ~0x130 bytes; processes all 6 children of
 * self->subscene and forwards frame data via slots 0x1f0..0x218. */
static int partysel_worker_big(PartySelectProc *self);

/* --- Helper. CRO 0x1120. --- */
static int partysel_helper_e(PartySelectProc *self);

/* --- Setter. CRO 0x11c8. --- */
static void partysel_set_c(PartySelectProc *self);

/* --- Setter. CRO 0x1204. --- */
static void partysel_set_d(PartySelectProc *self);

/* --- Big worker. CRO 0x121c. --- */
/* 6 callee-saved registers, called from partysel_run at 0x56c. */
static int partysel_run_big(PartySelectProc *self);

/* --- Per-cell renderer. CRO 0x13d4. --- */
static int partysel_render_subsubcell(PartySelectProc *self);

/* --- Per-cell renderer. CRO 0x1484. --- */
static int partysel_render_subsubcell2(PartySelectProc *self);

/* --- Lifecycle stubs. CRO 0x1530 / 0x1538 / 0x153c / 0x1540 / 0x1544 / 0x1548. --- */
static int partysel_yes_v4(void) { return 1; }
static int partysel_no_v3(void) { return 0; }
static int partysel_helper_v1(void) { return 1; }
static int partysel_helper_v2(void) { return 1; }
static void partysel_release_v4(void);
static void partysel_release_v5(void);

/* --- Setter. CRO 0x154c. --- */
static void partysel_set_e(PartySelectProc *self);

/* --- Setter. CRO 0x1584. --- */
static void partysel_set_f(PartySelectProc *self);

/* --- Per-cell renderer. CRO 0x15c0. --- */
static int partysel_render_subsubcell3(PartySelectProc *self);

/* --- Lifecycle stub. CRO 0x1690. --- */
static int partysel_helper_v3(void) { return 1; }

/* --- Destructor. CRO 0x1694. --- */
/* Releases self->subscene via slot 0x1d8 then returns 0. */
static int partysel_destroy_v2(PartySelectProc *self);

/* --- Per-cell renderer. CRO 0x1724. --- */
static int partysel_render_subsubcell4(PartySelectProc *self);

/* --- Setter. CRO 0x180c. --- */
static void partysel_set_g(PartySelectProc *self);

/* --- Constructor. CRO 0x185c. nnroControlObject_ entry. --- */
/* Allocates the subscene (slot 0x208, 0x90 bytes), stores parent at +0x28,
 * stores work at +0x0c, initializes 6 children via slot 0x210. */
static PartySelectProc *partysel_create(void *parent);

/* --- Standard NN loader infrastructure --- */

/* CRO 0x1864. Init for the module's BSS -- sets two error-counter slots to -1. */
static void partysel_bss_init(void);

/* CRO 0x1890. Loader vtable dispatcher (slot 0..5). */
static int partysel_loader_dispatch(void *obj, int slot);