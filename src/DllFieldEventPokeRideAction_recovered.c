/*
 * Preliminary decompilation of DllFieldEventPokeRideAction.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the field-engine (DllField)
 * import slot has not been resolved against a concrete symbol, and the
 * VecMath-style inner layout (+0x40 / +0x48 / +0xbc) needs the
 * associated field/pokemon entity to be recovered.
 *
 * Module file: extracted/romfs/DllFieldEventPokeRideAction.cro
 *   code region     0x180 .. 0x180 + 0x1e80  (ARM mode)
 *   segment 0 (ARM) 0x180 .. 0xf0c
 *   segment 1 (THM) 0x1000 .. 0x118c
 *   segment 2 (RO)  0x22fc .. 0x2318 (28 bytes)
 *   segment 3 (BSS) 0x0, size 0x24
 *   bss             0x44
 *   exports named   1 (`nnroControlObject_`, segment 0, +0x964)
 *   imports         46 anonymous entries from `|static|`,
 *                    1 entry from `DllField`
 *   external patches 0
 *
 * RTTI type names recovered from `.rodata`:
 *     "N5field19EventPokeRideActionE"
 *
 * Behavioral summary:
 *   One of the four "field-event" CROs that handle non-trivial
 *   overworld animations for the player character.  This one is the
 *   "mount / ride a Pokemon" action: when the player presses `A` near a
 *   ride-eligible Pokemon, this object drives the camera, player-state
 *   transition, and the entity-overlay mount/unmount animation.  Uses
 *   double-precision floats (vpush/vpop) at multiple entry points,
 *   indicating vector math against the field camera.
 *
 * Structure observed from disassembly:
 *   - Instance size ≈ 0x288 bytes (ctor at 0xa00/-0xa60 str's the
 *     literal-pool anchor +0x284).
 *   - Sub-object size 0xbc at +0xbc (the `char-vector` work struct).
 *   - Sub-object size 0x40 at +0x48 (a secondary inner).
 *   - 64-byte stride loops (r4, r5 lsl #6) at 0x338+ suggest an array
 *     of inner objects (likely the candidate ride-eligible Pokemon list).
 */

#include <stdint.h>

typedef struct EventPokeRideAction EventPokeRideAction;
typedef struct RideVecContext RideVecContext;
typedef struct RideInnerContext RideInnerContext;

struct RideVecContext {
    /* Confirmed offsets: 0x40, 0x44 (work area).  Bounded by the
     * exec loop at 0x338 which writes a 64-byte stride. */
    uint8_t data[0x40];
};

struct RideInnerContext {
    /* +0x48 / +0xbc sub-structures.  Size 0x40 (handler) + 0xbc (vec). */
    uint8_t data[0x100];
};

struct EventPokeRideAction {
    void *vtable;             /* 0x00 */
    uint8_t reserved04[0x0c];
    void *field_state;        /* 0x10 */
    uint8_t reserved14[0x0c];
    void *owner;              /* 0x20 */
    int32_t state_flags;      /* 0x24 */
    void *entity;             /* 0x28 */
    uint8_t state_byte;       /* 0x2c */
    uint8_t reserved2d[0x13]; /* 0x2d..0x3f */
    RideVecContext vec;       /* 0x40 */
    RideInnerContext inner;   /* 0x48..+0x140 */
    /* Total confirmed extent ≈ +0x284 */
};

/* ---------- Internal forwarders -------------------------------------- */

extern int ride_import_0(int, ...);   /* 0x180 */
extern int ride_import_1(int, ...);   /* 0x188 */
extern int ride_import_2(int, ...);   /* 0x190 */
extern int ride_import_3(int, ...);   /* 0x198 */
extern int ride_import_4(int, ...);   /* 0x1a0 */
extern int ride_import_5(int, ...);   /* 0x1a8 */
extern int ride_import_6(int, ...);   /* 0x1b0 */
extern int ride_import_7(int, ...);   /* 0x1b8 */
extern int ride_import_8(int, ...);   /* 0x1c0 */
extern int ride_import_9(int, ...);   /* 0x1c8 */
extern int ride_import_10(int, ...);  /* 0x1d0 */
extern int ride_import_11(int, ...);  /* 0x1d8 */
extern int ride_import_12(int, ...);  /* 0x1e0 */
extern int ride_import_13(int, ...);  /* 0x1e8 */
extern int ride_import_14(int, ...);  /* 0x1f0 */
extern int ride_import_15(int, ...);  /* 0x1f8 */
extern int ride_import_16(int, ...);  /* 0x200 */
extern int ride_import_17(int, ...);  /* 0x218 */
extern int ride_import_18(int, ...);  /* 0x220 */
extern int ride_import_19(int, ...);  /* 0x228 */
extern int ride_import_20(int, ...);  /* 0x230 */
extern int ride_import_21(int, ...);  /* 0x238 */
extern int ride_import_22(int, ...);  /* 0x240 */
extern int ride_import_23(int, ...);  /* 0x248 */
extern int ride_import_24(int, ...);  /* 0x250 */
extern int ride_import_25(int, ...);  /* 0x258 */
extern int ride_import_26(int, ...);  /* 0x260 */
extern int ride_import_27(int, ...);  /* 0x278 */
extern int ride_import_28(int, ...);  /* 0x280 */
extern int ride_import_29(int, ...);  /* 0x288 */
extern int ride_import_30(int, ...);  /* 0x290 */
extern int ride_import_31(int, ...);  /* 0x298 */
extern int ride_import_32(int, ...);  /* 0x2a0 */
extern int ride_import_33(int, ...);  /* 0x2a8 */
extern int ride_import_34(int, ...);  /* 0x2b0 */
extern int ride_import_35(int, ...);  /* 0x2b8 */
extern int ride_import_36(int, ...);  /* 0x2c0 */
extern int ride_import_37(int, ...);  /* 0x2c8 */
extern int ride_import_38(int, ...);  /* 0x2d0 */
extern int ride_field_a(int, ...);    /* 0x614 — DllField imported slot */

/* ---------- Function reconstructions --------------------------------- */

/* CRO 0x2d8 — main Exec.
 * Reads `[+0x2c]` (state byte); early-return path is `[+0x2c] == 0`,
 * otherwise it pulls the ridable list, iterates the 64-byte stride
 * array at +0x48, and calls DllField::slot 0x614.  Uses vpush/vpop
 * heavily, indicating an inner VecMath/RideCam controller. */
static int EventPokeRideAction_exec(EventPokeRideAction *self, void *p1, void *p2);

/* CRO 0x528 — pair of CanRun/CanStop/CanDraw helpers. */
static int EventPokeRideAction_can_run(void);
static int EventPokeRideAction_can_stop(void);

/* CRO 0x614 — DllField incoming callback (lifecycle slot).  Same
 * vpush/vpop frame layout as the Exec above; reads `self->field_state`
 * (+0x10) and routes through the inner field-poke entity. */
static int ride_field_lifecycle(void *self, int arg1, int arg2);

/* CRO 0x750 — CanDraw helper. */
static int EventPokeRideAction_can_draw(void);

/* CRO 0x7dc — secondary Exec (mount-side vec math).
 * Pushes r3..fp onto the stack and uses vpush; on `[+0x1c]==0x0` it
 * branches into the inner entity-update loop and calls slot 0x614
 * again. */
static int EventPokeRideAction_mount_exec(EventPokeRideAction *self);

/* CRO 0xa00, 0xa60 — Ctor #1 and Ctor #2: each writes the literal
 * vtable anchor +0x284 against `r0` then advances to literal
 * address +0xbc (so the object has 0xbc bytes of sub-structure before
 * the inner VecContext).  Both follow up by calling `slot 2c0` twice
 * (counter, sub-block initializer) and `slot 2c8` / `slot 2d0`. */
static EventPokeRideAction *EventPokeRideAction_ctor1(EventPokeRideAction *self);
static EventPokeRideAction *EventPokeRideAction_ctor2(EventPokeRideAction *self);

/* CRO 0xaec — same TestStub diagnostic region as in
 *   DllTestTamada.cro / DllCommendation.cro (6-way dispatch with the
 *   MIRROR magic constants at +0xb6c/+0xb70/+0xb74).  Treat as a
 *   singleton accessor; semantics not yet decoded. */
static int ride_stub_getset(void *self, int op, void *arg);

/* ---------- Implementations (preliminary) ---------------------------- */

static int EventPokeRideAction_exec(EventPokeRideAction *self, void *p1, void *p2) {
    /* Early-out: state_byte == 0 -> return 1. */
    if (self->state_byte == 0)
        return 1;
    if (!ride_import_0(self->owner, &self->vec))
        return 1;
    ride_import_1(&self->vec, &self->inner);
    /* Iterate the stride array at +0x48 — `ldr r1, [r8, r5, lsl #2]`
     * feeds the dispatch in pairs. */
    for (uint32_t i = 0; i < /*TODO: count*/ 0; ++i) {
        ride_import_2(0);
    }
    ride_field_a(self, p1, p2);
    (void)p1; (void)p2;
    return 0;
}

static int EventPokeRideAction_can_run(void)  { return 1; }
static int EventPokeRideAction_can_stop(void) { return 1; }
static int EventPokeRideAction_can_draw(void) { return 1; }

static int ride_field_lifecycle(void *self, int arg1, int arg2) {
    /* Reads `self->field_state [+0x10]` and routes through the
     * inner field-poke entity.  Uses DllField slot 0x614. */
    (void)self; (void)arg1; (void)arg2;
    return 1;
}

static int EventPokeRideAction_mount_exec(EventPokeRideAction *self) {
    ride_field_lifecycle(self->field_state, 0, 0);
    return 0;
}

static EventPokeRideAction *EventPokeRideAction_ctor1(EventPokeRideAction *self) {
    /* Mirror of the vtable-anchor pattern from CRO 0xa00: writes a
     * 0x284-byte anchor, then pre-fills a 0xbc inner struct and a 0x40
     * secondary struct via the four import slots 2b8/2c0/2c8/2d0. */
    ride_import_35(0);
    ride_import_36(0); /* three calls total per the disasm */
    ride_import_36(0);
    ride_import_37(0);
    ride_import_38(0);
    ride_import_17(0);
    return self;
}

static EventPokeRideAction *EventPokeRideAction_ctor2(EventPokeRideAction *self) {
    ride_import_35(0);
    ride_import_36(0);
    ride_import_36(0);
    ride_import_37(0);
    ride_import_38(0);
    return self;
}

static int ride_stub_getset(void *self, int op, void *arg) {
    (void)self; (void)arg;
    /* Same shape as the TestTamada stub at 0x180. */
    switch (op) {
    case 0: case 1: case 2: case 3: case 4: return 0;
    default: return 0;
    }
}
