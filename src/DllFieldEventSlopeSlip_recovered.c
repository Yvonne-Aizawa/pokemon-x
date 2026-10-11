/*
 * Preliminary decompilation of DllFieldEventSlopeSlip.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the inner object +0x48/.+0x1ac
 * walk pattern matches a `FieldPlayerEntity` accessor that has not yet
 * been recovered in this CRO independently.
 *
 * Module file: extracted/romfs/DllFieldEventSlopeSlip.cro
 *   code region     0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0x788  (small)
 *   segment 1 (THM) 0x1000 .. 0x10ac
 *   segment 2 (RO)  0x21c0 .. 0x21dc (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x10
 *   bss             0x10
 *   exports named   1 (`nnroControlObject_`, segment 0, +0x328)
 *   imports         21 anonymous entries from `|static|`,
 *                    2 entries from `DllField`
 *   external patches 0
 *
 * RTTI type names recovered from `.rodata`:
 *     "N5field14EventSlopeSlipE"
 *
 * Behavioral summary:
 *   Plays the "slip on a slope" animation when the player attempts to
 *   climb an icy/sandy slope without proper boots.  Triggers a 1-frame
 *   visual effect (camera shake + slide-back animation), then yields
 *   control back to the field engine through the `DllField` slots.
 *
 * Notes:
 *   - The 0x47c region is the same BSS initializer pattern as in the
 *     other field-event CROs (writes -1 to a 64-bit slot, 0 to another).
 *   - The 0x4a8 region is the same TestStub diagnostic region as in
 *     DllTestTamada.cro / DllCommendation.cro; keep as a static
 *     singleton accessor until a confirming call site is found.
 */

#include <stdint.h>

typedef struct EventSlopeSlip EventSlopeSlip;

struct EventSlopeSlip {
    void *vtable;             /* 0x00 */
    uint8_t reserved04[0x14];
    void *param_a;            /* 0x18 — set in ctor */
    uint8_t reserved1c[0x08];
    uint8_t state_byte;       /* 0x24 — set in ctor */
    uint8_t reserved25[0x03];
    void *work;               /* 0x28 — populated by `bl 0x180` */
    uint8_t reserved2c[0x04];
    uint8_t flag_30;          /* 0x30 — bool populated by `bl 0x190` */
    uint8_t reserved31[0x10]; /* 0x31..0x40 */
    void *field_entity;       /* 0x48 — read by long helper @ 0x308 */
};

/* ---------- Internal forwarders -------------------------------------- */

extern int slope_import_0(int, ...);   /* 0x180 */
extern int slope_import_1(int, ...);   /* 0x188 */
extern int slope_import_2(int, ...);   /* 0x190 */
extern int slope_import_3(int, ...);   /* 0x198 */
extern int slope_import_4(int, ...);   /* 0x1a0 */
extern int slope_import_5(int, ...);   /* 0x1a8 */
extern int slope_import_6(int, ...);   /* 0x1b0 */
extern int slope_import_7(int, ...);   /* 0x1b8 */
extern int slope_import_8(int, ...);   /* 0x1c0 */
extern int slope_import_9(int, ...);   /* 0x1c8 */
extern int slope_import_10(int, ...);  /* 0x1d0 */
extern int slope_import_11(int, ...);  /* 0x1d8 */
extern int slope_import_12(int, ...);  /* 0x1e0 */
extern int slope_import_13(int, ...);  /* 0x1e8 */
extern int slope_field_a(int, ...);    /* DllField slot A */
extern int slope_field_b(int, ...);    /* DllField slot B */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x228 — ctor: stores params at +0x18/+0x24, allocates the work
 * area through slot 0x180, pulls `[work, +0xc]` -> `+0x1c`, and writes
 * the `state_byte` at +0x24.  Calls slot 0x188 and slot 0x190; returns
 * 1 in r0 and stores it to flag_30 (+0x30). */
static int EventSlopeSlip_ctor(EventSlopeSlip *self, void *param, uint32_t mode);

/* CRO 0x270 — Exec/main loop: allocates a 0x28-byte stack frame,
 * calls `mvn r2, #0` then `mov r1, #0`, then `bl 0x198` (a typed
 * marshal/format call), then `bl 0x1a0` with self->work[+0x1c],
 * then `bl 0x1a8` with the same byte and `r1=sp`. */
static int EventSlopeSlip_exec(EventSlopeSlip *self);

/* CRO 0x308 — big helper (slide-back animation):
 * Reads `self->field_entity [+0x48]` and walks `[+0x48]->...->[+0x1ac]`
 * (5-level pointer chase), then issues DllField slot A. */
static int EventSlopeSlip_anim(EventSlopeSlip *self);

/* CRO 0x468 — CanDraw/CanRun style helper that just trampolines
 * through `bl 0x218` -> `bl 0x220`.  Real semantics live in the
 * loader-jump slots; semantics not yet decoded. */
static int slope_trampoline(void);

/* CRO 0x47c — BSS initializer (-1,0 / 0,0 writes; bx lr). */
static void slope_bss_init(void);

/* CRO 0x4a8 — TestStub diagnostic region (same as the other modules).
 * Treat as a singleton accessor. */
static int slope_stub_getset(void *self, int op, void *arg);

/* ---------- Implementations (preliminary) ---------------------------- */

static int EventSlopeSlip_ctor(EventSlopeSlip *self, void *param, uint32_t mode) {
    self->param_a    = param;
    self->work       = (void *)(uintptr_t)0; /* TODO */
    self->state_byte = (uint8_t)mode;
    slope_import_0(0);
    self->flag_30 = 0;
    slope_import_1(0);
    int r = !!slope_import_2(0);
    self->flag_30 = (uint8_t)r;
    return r;
}

static int EventSlopeSlip_exec(EventSlopeSlip *self) {
    /* The disasm:
     *   bl 0x198 (alloc / marshal with mvn r2, #0)
     *   ldr r0, [r4, #28]; bl 0x1a0
     *   ldrb r0, [r4, #36]; mov r1, sp; bl 0x1a8
     *   ...
     */
    slope_import_3(0);
    slope_import_4(0);
    slope_import_5(0);
    /* TODO: not yet decoded */
    return 1;
}

static int EventSlopeSlip_anim(EventSlopeSlip *self) {
    /* Pointer chase: r5 = self->field_entity;
     *                r0 = r5[+0x48];
     *                r0 = r0[+0x1ac];
     * The 0x1ac offset is roughly the player-control +0x1ac field;
     * it must be confirmed against the FieldPlayerEntity layout. */
    slope_import_6(0);
    slope_import_13(0);
    slope_field_a(0);
    return 1;
}

static int slope_trampoline(void) { return 1; }

static void slope_bss_init(void) {
    /* TODO: not yet decoded */
}

static int slope_stub_getset(void *self, int op, void *arg) {
    (void)self; (void)arg;
    switch (op) {
    case 0: case 1: case 2: case 3: case 4: return 0;
    default: return 0;
    }
}
