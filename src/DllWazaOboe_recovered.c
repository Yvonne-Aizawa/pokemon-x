/*
 * Preliminary decompilation of DllWazaOboe.cro.
 *
 * Source address notation uses CRO segment 0 (code) offsets unless noted.
 * This file is intentionally not wired into a build: imported services
 * and the exact CRO linker layout still need to be recovered.
 *
 * What was recovered:
 *   - Module header facts (code/data/bss, veneer count, export names)
 *   - Per-function prologue offsets enumerated via push/pop pairing
 *   - BL target list (sliced from disassembly) for each prologue
 *   - Most-frequently-referenced base offsets
 *
 * What was NOT recovered:
 *   - Concretely-resolved call targets (loader patches unresolved)
 *   - Type signatures of import slots
 *   - String literals in segment 2 (data)
 *   - Exact register layout of every work struct
 */

#include <stdint.h>

/* Module summary (from DllWazaOboe.cro header):
 *   file size: 0x8000
 *   code:      offset 0x180  size 0x5e80
 *   data:      offset 0x79b8  size 0xc8
 *   bss:       size  0x20
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 239
 *   import veneers (ldr pc,[pc,#N]): 203 at 0x194..0x7e4
 *   total BL sites: 454 (to imports: 430, internal: 24)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x24 (hit 115x)
 *   +0x04 (hit 65x)
 *   +0x20 (hit 50x)
 *   +0x28 (hit 46x)
 *   +0x4c (hit 33x)
 *   +0x10 (hit 32x)
 *   +0x2c (hit 27x)
 *   +0x0c (hit 25x)
 *   +0x60 (hit 23x)
 *   +0x08 (hit 20x)
 *   +0x14 (hit 19x)
 *   +0x7c (hit 18x)
 *   +0x50 (hit 17x)
 *   +0x54 (hit 13x)
 */
struct ModuleActor {
    void *vtable;       /* 0x00 */
    void *parent;       /* 0x04 */
    void *child;        /* 0x08 - state-machine / state-table */
    ModuleWork *work;   /* 0x0c - module-private work area */
    void *loader_ptr;   /* 0x10 */
    uint32_t flags;     /* 0x14 */
    uint8_t reserved18[0x68]; /* 0x18..0x7f */
    void *owner;        /* 0x80 */
    void *bg_iter;      /* 0x84 - bg::System* or layer iterator */
};

struct ModuleWork {
    uint8_t bytes[0x60]; /* seen: 0x00, 0x14, 0x18, 0x38 fields */
};

/*
 * Function recovery index. Each entry below corresponds to a `push`
 * prologue enumerated in the disassembly. The end offset is the next
 * pop {...,pc} before the next prologue; bodies are intentionally
 * omitted.
 */

/* Index: 45 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x0838..0x0a20  BL(local=0, imp=9)
 *   CRO 0x0a40..0x0af4  BL(local=0, imp=4)
 *   CRO 0x0af8..0x0b1c  BL(local=0, imp=1)
 *   CRO 0x0b28..0x0d24  BL(local=0, imp=16)
 *   CRO 0x0d38..0x0dd8  BL(local=0, imp=5)
 *   CRO 0x0dec..0x0e84  BL(local=0, imp=7)
 *   CRO 0x0e88..0x0f14  BL(local=0, imp=6)
 *   CRO 0x0f1c..0x1018  BL(local=2, imp=5)
 *   CRO 0x1028..0x1144  BL(local=0, imp=8)
 *   CRO 0x114c..0x11cc  BL(local=0, imp=2)
 *   CRO 0x11dc..0x1670  BL(local=1, imp=44)
 *   CRO 0x1688..0x16ac  BL(local=0, imp=3)
 *   CRO 0x16b4..0x1c08  BL(local=1, imp=43)
 *   CRO 0x1c2c..0x1da4  BL(local=0, imp=12)
 *   CRO 0x1db8..0x1e98  BL(local=0, imp=4)
 *   CRO 0x1ea8..0x2030  BL(local=0, imp=12)
 *   CRO 0x2040..0x209c  BL(local=0, imp=4)
 *   CRO 0x20a0..0x223c  BL(local=0, imp=12)
 *   CRO 0x2244..0x22d4  BL(local=0, imp=3)
 *   CRO 0x22e0..0x250c  BL(local=0, imp=30)
 *   CRO 0x2514..0x2924  BL(local=3, imp=30)
 *   CRO 0x2960..0x2968  BL(local=1, imp=0)
 *   CRO 0x2970..0x2a84  BL(local=0, imp=11)
 *   CRO 0x2a8c..0x2bb8  BL(local=0, imp=10)
 *   CRO 0x2bc8..0x2e70  BL(local=4, imp=18)
 *   CRO 0x2e88..0x2fe4  BL(local=0, imp=12)
 *   CRO 0x2fec..0x30d8  BL(local=0, imp=7)
 *   CRO 0x30e0..0x322c  BL(local=0, imp=11)
 *   CRO 0x324c..0x3290  BL(local=0, imp=5)
 *   CRO 0x329c..0x32f4  BL(local=0, imp=4)
 *   CRO 0x3304..0x3360  BL(local=0, imp=4)
 *   CRO 0x3368..0x344c  BL(local=1, imp=4)
 *   CRO 0x3470..0x3684  BL(local=2, imp=17)
 *   CRO 0x3690..0x379c  BL(local=0, imp=12)
 *   CRO 0x37a8..0x3ce8  BL(local=9, imp=42)
 *   CRO 0x3d04..0x3d4c  BL(local=0, imp=1)
 *   CRO 0x3d54..0x3d80  BL(local=0, imp=1)
 *   CRO 0x3d8c..0x3db8  BL(local=0, imp=1)
 *   CRO 0x3dc0..0x3dc8  BL(local=0, imp=1)
 *   CRO 0x3dd8..0x3e04  BL(local=0, imp=1)
 *   CRO 0x3e10..0x3e3c  BL(local=0, imp=1)
 *   CRO 0x3e6c..0x3e90  BL(local=0, imp=1)
 *   CRO 0x3e9c..0x3f3c  BL(local=0, imp=5)
 *   CRO 0x3f54..0x3ff8  BL(local=0, imp=0)
 *   CRO 0x4020..0x409c  BL(local=0, imp=0)
 */

/* CRO 0x838, body spans 0x838..0xa20 (~0x1e8 bytes). */
static int wazaoboe_838(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x19c, 0x1a4, 0x1ac, 0x1b4, 0x1bc, 0x19c, 0x19c, 0x1cc, ... (9 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x3c, +0x5c, +0x60, +0x64, +0x68, +0x6c, +0x70, +0x74 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xa40, body spans 0xa40..0xaf4 (~0xb4 bytes). */
static int wazaoboe_a40(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1dc, 0x1e4, 0x1ec, 0x1f4 */
    /* Field offsets touched: +0x04, +0x10, +0x18, +0x20, +0x24, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xaf8, body spans 0xaf8..0xb1c (~0x24 bytes). */
static int wazaoboe_af8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1fc */
    /* Field offsets touched: +0x20, +0x1dc */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xb28, body spans 0xb28..0xd24 (~0x1fc bytes). */
static int wazaoboe_b28(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x20c, 0x214, 0x21c, 0x224, 0x22c, 0x1a4, 0x234, 0x23c, ... (16 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x10, +0x20, +0x28 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xd38, body spans 0xd38..0xdd8 (~0xa0 bytes). */
static int wazaoboe_d38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x284, 0x28c, 0x294, 0x29c, 0x2a4 */
    /* Field offsets touched: +0x20, +0x144, +0x337, +0x3ed */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xdec, body spans 0xdec..0xe84 (~0x98 bytes). */
static int wazaoboe_dec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a4, 0x234, 0x2b4, 0x2bc, 0x2c4, 0x2bc, 0x2cc */
    /* Field offsets touched: +0x08, +0x20, +0x28 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xe88, body spans 0xe88..0xf14 (~0x8c bytes). */
static int wazaoboe_e88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d4, 0x2dc, 0x2e4, 0x2ec, 0x2f4, 0x2f4 */
    /* Field offsets touched: +0x08, +0x20, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0xf1c, body spans 0xf1c..0x1018 (~0xfc bytes). */
static int wazaoboe_f1c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x304, 0x838, 0x30c, 0x314, 0x31c, 0xb28, 0x324 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x24, +0x28, +0x60 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x1028, body spans 0x1028..0x1144 (~0x11c bytes). */
static int wazaoboe_1028(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x19c, 0x334, 0x33c, 0x19c, 0x334, 0x33c, 0x19c, 0x19c */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x114c, body spans 0x114c..0x11cc (~0x80 bytes). */
static int wazaoboe_114c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x35c, 0x32c */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x18 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x11dc, body spans 0x11dc..0x1670 (~0x494 bytes). */
static int wazaoboe_11dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x364, 0x36c, 0x374, 0x37c, 0x384, 0x38c, 0x394, 0x38c, ... (45 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x1c, +0x24, +0x28, +0x4c, +0x80, +0x88 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x1688, body spans 0x1688..0x16ac (~0x24 bytes). */
static int wazaoboe_1688(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x43c, 0x43c, 0x444 */
    /* Field offsets touched: +0x24, +0x28, +0x7c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x16b4, body spans 0x16b4..0x1c08 (~0x554 bytes). */
static int wazaoboe_16b4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a4, 0x44c, 0x454, 0x45c, 0x464, 0x3dc, 0x46c, 0x474, ... (44 total) */
    /* Field offsets touched: +0x04, +0x10, +0x18, +0x1c, +0x20, +0x24, +0x34, +0x4c, +0x50, +0x54, +0x58, +0x59, +0x5a, +0x5b, +0x60, +0x7c, +0x84, +0x88, +0x90, +0x91 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x1c2c, body spans 0x1c2c..0x1da4 (~0x178 bytes). */
static int wazaoboe_1c2c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x30c, 0x514, 0x30c, 0x51c, 0x524, 0x31c, 0x52c, 0x534, ... (12 total) */
    /* Field offsets touched: +0x04, +0x10, +0x14, +0x24, +0x28, +0x2c, +0x30 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x1db8, body spans 0x1db8..0x1e98 (~0xe0 bytes). */
static int wazaoboe_1db8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x544, 0x54c, 0x544, 0x554 */
    /* Field offsets touched: +0x04, +0x05, +0x06, +0x07, +0x08, +0x0c, +0x24, +0x25, +0x26, +0x27, +0x28, +0x29, +0x2a, +0x2c, +0x4c, +0x50, +0x80 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x1ea8, body spans 0x1ea8..0x2030 (~0x188 bytes). */
static int wazaoboe_1ea8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x404, 0x55c, 0x564, 0x39c, 0x39c, 0x38c, 0x38c, 0x56c, ... (12 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2040, body spans 0x2040..0x209c (~0x5c bytes). */
static int wazaoboe_2040(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a4, 0x234, 0x2b4, 0x574 */
    /* Field offsets touched: +0x7c, +0x91 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x20a0, body spans 0x20a0..0x223c (~0x19c bytes). */
static int wazaoboe_20a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x614, 0x3b4, 0x41c, 0x424, 0x61c, 0x38c, 0x39c, 0x61c, ... (12 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2244, body spans 0x2244..0x22d4 (~0x90 bytes). */
static int wazaoboe_2244(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x62c, 0x634, 0x63c */
    /* Field offsets touched: +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x22e0, body spans 0x22e0..0x250c (~0x22c bytes). */
static int wazaoboe_22e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x47c, 0x48c, 0x644, 0x64c, 0x42c, 0x554, 0x654, 0x654, ... (30 total) */
    /* Field offsets touched: +0x20, +0x24, +0x28, +0x4c, +0x50, +0x54, +0x5b, +0x5c, +0x60, +0x7c, +0x91 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2514, body spans 0x2514..0x2924 (~0x410 bytes). */
static int wazaoboe_2514(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x584, 0x58c, 0x594, 0x59c, 0x5a4, 0x1c2c, 0x5ac, 0x5ac, ... (33 total) */
    /* Field offsets touched: +0x01, +0x04, +0x08, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x4c, +0x50, +0x54, +0x58, +0x59, +0x5a, +0x5b, +0x5c, +0x60, +0x74, +0x7c, +0x80, +0x84, +0x88, +0x8c, +0x90, +0x91 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2960, body spans 0x2960..0x2968 (~0x8 bytes). */
static int wazaoboe_2960(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2970 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2970, body spans 0x2970..0x2a84 (~0x114 bytes). */
static int wazaoboe_2970(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x66c, 0x674, 0x67c, 0x684, 0x32c, 0x68c, 0x68c, 0x694, ... (11 total) */
    /* Field offsets touched: +0x04, +0x14, +0x18, +0x24, +0x28, +0x2c, +0x30, +0x4c, +0x54, +0x60, +0x7c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2a8c, body spans 0x2a8c..0x2bb8 (~0x12c bytes). */
static int wazaoboe_2a8c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x30c, 0x514, 0x52c, 0x30c, 0x51c, 0x524, 0x31c, 0x534, ... (10 total) */
    /* Field offsets touched: +0x04, +0x10, +0x14, +0x24, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2bc8, body spans 0x2bc8..0x2e70 (~0x2a8 bytes). */
static int wazaoboe_2bc8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6ac, 0x6b4, 0x6b4, 0x6b4, 0x6b4, 0x6b4, 0x6b4, 0x39c, ... (22 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2e88, body spans 0x2e88..0x2fe4 (~0x15c bytes). */
static int wazaoboe_2e88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x38c, 0x38c, 0x38c, 0x38c, 0x38c, 0x38c, 0x38c, 0x38c, ... (12 total) */
    /* Field offsets touched: +0x04, +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x2fec, body spans 0x2fec..0x30d8 (~0xec bytes). */
static int wazaoboe_2fec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x364, 0x6c4, 0x3b4, 0x6cc, 0x39c, 0x3b4, 0x38c */
    /* Field offsets touched: +0x04, +0x0c, +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x30e0, body spans 0x30e0..0x322c (~0x14c bytes). */
static int wazaoboe_30e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6d4, 0x6dc, 0x65c, 0x6d4, 0x3b4, 0x3b4, 0x3b4, 0x3b4, ... (11 total) */
    /* Field offsets touched: +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x324c, body spans 0x324c..0x3290 (~0x44 bytes). */
static int wazaoboe_324c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a4, 0x234, 0x2b4, 0x2b4, 0x574 */
    /* Field offsets touched: +0x24 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x329c, body spans 0x329c..0x32f4 (~0x58 bytes). */
static int wazaoboe_329c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x68c, 0x694, 0x694, 0x6a4 */
    /* Field offsets touched: +0x14, +0x24, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3304, body spans 0x3304..0x3360 (~0x5c bytes). */
static int wazaoboe_3304(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x68c, 0x694, 0x694, 0x6a4 */
    /* Field offsets touched: +0x14, +0x24, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3368, body spans 0x3368..0x344c (~0xe4 bytes). */
static int wazaoboe_3368(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6e4, 0x6ec, 0x47c, 0x20a0, 0x6f4 */
    /* Field offsets touched: +0x01, +0x08, +0x10, +0x18, +0x30, +0x34, +0x38, +0x40, +0x44, +0x48, +0x4c, +0x54, +0x58, +0x59, +0x5a, +0x88 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3470, body spans 0x3470..0x3684 (~0x214 bytes). */
static int wazaoboe_3470(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x45c, 0x6fc, 0x704, 0x70c, 0xa40, 0x714, 0x114c, 0x45c, ... (19 total) */
    /* Field offsets touched: +0x04, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x40, +0x44, +0x48, +0x64 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3690, body spans 0x3690..0x379c (~0x10c bytes). */
static int wazaoboe_3690(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a4, 0x234, 0x2b4, 0x2b4, 0x2b4, 0x744, 0x744, 0x1a4, ... (12 total) */
    /* Field offsets touched: +0x0c, +0x24, +0x34, +0x40, +0x44, +0x48, +0x60, +0x7c, +0x91 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x37a8, body spans 0x37a8..0x3ce8 (~0x540 bytes). */
static int wazaoboe_37a8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x45c, 0x74c, 0x74c, 0x754, 0x754, 0x19c, 0x19c, 0x1a4, ... (51 total) */
    /* Field offsets touched: +0x01, +0x04, +0x08, +0x10, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40, +0x44, +0x48, +0x4c, +0x50, +0x54 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3d04, body spans 0x3d04..0x3d4c (~0x48 bytes). */
static int wazaoboe_3d04(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x7d4 */
    /* Field offsets touched: +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40, +0x44, +0x48, +0x4c, +0x50 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3d54, body spans 0x3d54..0x3d80 (~0x2c bytes). */
static int wazaoboe_3d54(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x7dc */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3d8c, body spans 0x3d8c..0x3db8 (~0x2c bytes). */
static int wazaoboe_3d8c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x7dc */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3dc0, body spans 0x3dc0..0x3dc8 (~0x8 bytes). */
static int wazaoboe_3dc0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x7e4 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3dd8, body spans 0x3dd8..0x3e04 (~0x2c bytes). */
static int wazaoboe_3dd8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x7dc */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3e10, body spans 0x3e10..0x3e3c (~0x2c bytes). */
static int wazaoboe_3e10(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x7dc */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3e6c, body spans 0x3e6c..0x3e90 (~0x24 bytes). */
static int wazaoboe_3e6c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1fc */
    /* Field offsets touched: +0x04, +0x20, +0x1dc */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3e9c, body spans 0x3e9c..0x3f3c (~0xa0 bytes). */
static int wazaoboe_3e9c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x284, 0x28c, 0x294, 0x29c, 0x2a4 */
    /* Field offsets touched: +0x20, +0x144, +0x337, +0x3ed */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x3f54, body spans 0x3f54..0x3ff8 (~0xa4 bytes). */
static int wazaoboe_3f54(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x20, +0x28 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* CRO 0x4020, body spans 0x4020..0x409c (~0x7c bytes). */
static int wazaoboe_4020(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllWazaOboe.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x3e98 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x3e98..; BL targets: 0x284 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 45 candidate function boundaries (push/pop pairing).
 * Total BL sites: 454 (to imports: 430, internal: 24).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */