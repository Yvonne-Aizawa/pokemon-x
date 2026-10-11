/*
 * Preliminary decompilation of DllTestTomoya.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is
 * intentionally NOT wired into a build yet: the imports table is empty
 * and the only named export is the CRO loader table.
 *
 * Module file: extracted/romfs/DllTestTomoya.cro
 *   code region     0x180 .. 0x180 + 0xe80  (ARM mode, all 32-bit)
 *   data region     0x10f4                 (4 bytes; pad/flag)
 *   bss             0x20 bytes
 *   exports named   1 (nnroControlObject_)
 *   imports         0
 *   external patches 0
 *
 * Disassembly observation: byte-for-byte identical to DllTestTamada.cro
 * and DllTestTaya.cro. The three "Test*" CROs are three near-identical
 * developer test stubs that share the same dispatch skeleton; only the
 * data-region token and the external name differ.
 */

#include <stdint.h>

typedef struct TestStub3 TestStub3;

/* See src/DllTestTamada_recovered.c — same offsets and layout. */
struct TestStub3 {
    void *vtable;             /* 0x00 */
    uint8_t reserved04[0x10]; /* 0x04..0x13 */
    void *anchor;             /* 0x14 */
    uint8_t reserved18[0x28]; /* 0x18..0x3f */
};

/* CRO 0x180 — six-way dispatch skeleton (shared with the other Test*). */
static int test_stub_dispatch(void *self, int op, void *arg);

/* CRO 0x1ec — fallback getter (shared with the other Test*). */
static int test_stub_getter(void);

static int test_stub_dispatch(void *self, int op, void *arg) {
    TestStub3 *t = (TestStub3 *)self;
    switch (op) {
    case 0: case 1: case 2: case 3: case 4:
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
