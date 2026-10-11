/*
 * Preliminary decompilation of DllTestTamada.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the imports table is empty
 * and the only named export is the CRO loader table.
 *
 * Module file: extracted/romfs/DllTestTamada.cro
 *   code region     0x180 .. 0x180 + 0xe80  (ARM mode, all 32-bit)
 *   data region     0x10f4                 (4 bytes; pad/flag)
 *   bss             0x20 bytes
 *   exports named   1 (nnroControlObject_)
 *   imports         0
 *   external patches 0
 *
 * Behavioral summary:
 *   The single function reachable through the control-object table at
 *   CRO 0x180 implements a six-way switch on the parameter passed in r1
 *   (cases 0..4 dispatched through a literal-pool jump table; case 5+ fall
 *   through).  Each case either stores/loads a pointer through the BSS
 *   anchor at [r2] or returns a constant derived from a literal pool entry.
 *   No business logic — this is a developer test/stub module for the
 *   "Tamada" prototype.
 */

#include <stdint.h>

typedef struct TestStub TestStub;

/* Inferred from the BSS anchor at +0x14 and the only data slot handled
 * by the switch.  No field has a confirmed size beyond the listed offsets;
 * the struct is documented as `reserved` blocks. */
struct TestStub {
    void *vtable;             /* 0x00 (set to literal-pool pointer) */
    uint8_t reserved04[0x10]; /* 0x04..0x13 */
    void *anchor;             /* 0x14 (singleton backing ptr) */
    uint8_t reserved18[0x28]; /* 0x18..0x3f */
};

/* CRO 0x180
 * switch (op) { case 0: store  -> 0; case 1: copy   -> 0; case 2..4: load
 *               default:        load immediate and return; }
 * Always returns 0 on a handled case. */
static int test_stub_dispatch(void *self, int op, void *arg);

/* CRO 0x1ec — second stub function; loads a series of literals from
 * the pool and `pop`s without storing them.  Treated as a getter
 * placeholder. */
static int test_stub_getter(void);

static int test_stub_dispatch(void *self, int op, void *arg) {
    TestStub *t = (TestStub *)self;
    switch (op) {
    case 0:
        /* Literal-pool anchor address stored through t->anchor. */
        if (t->anchor)
            (void)arg;
        t->anchor = 0;
        return 0;
    case 1: case 2: case 3: case 4:
        /* Each case copies/loads a 4-byte literal through t->anchor. */
        return 0;
    default:
        /* Fall-through: returns a constant pulled from the literal pool. */
        return test_stub_getter();
    }
}

static int test_stub_getter(void) {
    /* The original loads 0x30000000 / 0x30000026 / 0xd8e12c21 from
     * the constant pool at 0x220-0x228; semantics not decoded. */
    /* TODO: not yet decoded */
    return 0;
}
