/*
 * Preliminary decompilation of DllTestTaya.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the imports table is empty
 * and the only named export is the CRO loader table.
 *
 * Module file: extracted/romfs/DllTestTaya.cro
 *   code region     0x180 .. 0x180 + 0xe80  (ARM mode, all 32-bit)
 *   data region     0x10f0                 (4 bytes; pad/flag)
 *   bss             0x20 bytes
 *   exports named   1 (nnroControlObject_)
 *   imports         0
 *   external patches 0
 *
 * Disassembly observation: byte-for-byte identical to DllTestTamada.cro
 * (same developer stub reused under a different employee name). The
 * exported `nnroControlObject_` sits at the same CRO offset 0x0; only
 * the file size and a 4-byte data token differ from `DllTestTamada`.
 *
 * The reconstruction below mirrors the Tamada stub exactly; refer to
 * `src/DllTestTamada_recovered.c` for the common commentary.
 */

#include <stdint.h>

typedef struct TestStub2 TestStub2;

/* Same layout as DllTestTamada: only vtable + a single anchor pointer
 * at +0x14 is exercised by the dispatch loop. */
struct TestStub2 {
    void *vtable;             /* 0x00 */
    uint8_t reserved04[0x10]; /* 0x04..0x13 */
    void *anchor;             /* 0x14 */
    uint8_t reserved18[0x28]; /* 0x18..0x3f */
};

/* CRO 0x180 — same dispatch as the Tamada stub. */
static int test_stub_dispatch(void *self, int op, void *arg);

/* CRO 0x1ec — same getter stub. */
static int test_stub_getter(void);

static int test_stub_dispatch(void *self, int op, void *arg) {
    TestStub2 *t = (TestStub2 *)self;
    switch (op) {
    case 0: case 1: case 2: case 3: case 4:
        /* Each case performs a store/load through t->anchor. */
        (void)t; (void)arg;
        return 0;
    default:
        return test_stub_getter();
    }
}

static int test_stub_getter(void) {
    /* TODO: not yet decoded */
    return 0;
}
