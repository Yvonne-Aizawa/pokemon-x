/*
 * Preliminary decompilation of DllGameSync.cro.
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

/* Module summary (from DllGameSync.cro header):
 *   file size: 0x8000
 *   code:      offset 0x180  size 0x5e80
 *   data:      offset 0x7488  size 0x1c
 *   bss:       size  0x5c
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 156
 *   import veneers (ldr pc,[pc,#N]): 137 at 0x180..0x5c0
 *   total BL sites: 434 (to imports: 399, internal: 35)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x5c (hit 83x)
 *   +0x40 (hit 46x)
 *   +0x80 (hit 40x)
 *   +0x1c (hit 34x)
 *   +0x59 (hit 30x)
 *   +0xe0 (hit 30x)
 *   +0xa4 (hit 28x)
 *   +0xbc (hit 26x)
 *   +0xe1 (hit 23x)
 *   +0x8c (hit 20x)
 *   +0xc8 (hit 17x)
 *   +0xf4 (hit 17x)
 *   +0x134 (hit 16x)
 *   +0xc4 (hit 15x)
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

/* Index: 47 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x05e0..0x060c  BL(local=0, imp=1)
 *   CRO 0x0618..0x0644  BL(local=0, imp=1)
 *   CRO 0x066c..0x06e0  BL(local=0, imp=3)
 *   CRO 0x06e8..0x0b04  BL(local=9, imp=21)
 *   CRO 0x0b24..0x0c4c  BL(local=0, imp=7)
 *   CRO 0x0cec..0x0fa4  BL(local=4, imp=22)
 *   CRO 0x0fc8..0x11b0  BL(local=2, imp=16)
 *   CRO 0x11e8..0x1258  BL(local=0, imp=1)
 *   CRO 0x1270..0x12c0  BL(local=0, imp=3)
 *   CRO 0x12c8..0x1534  BL(local=5, imp=14)
 *   CRO 0x1558..0x16e8  BL(local=3, imp=9)
 *   CRO 0x16ec..0x1a30  BL(local=3, imp=31)
 *   CRO 0x1a3c..0x1ca8  BL(local=4, imp=5)
 *   CRO 0x1cb4..0x1d14  BL(local=0, imp=2)
 *   CRO 0x1d1c..0x1d44  BL(local=0, imp=2)
 *   CRO 0x1d48..0x1d90  BL(local=0, imp=4)
 *   CRO 0x1db4..0x1df8  BL(local=0, imp=1)
 *   CRO 0x1e10..0x1fac  BL(local=0, imp=19)
 *   CRO 0x1fb0..0x2100  BL(local=0, imp=19)
 *   CRO 0x2110..0x229c  BL(local=0, imp=16)
 *   CRO 0x22ac..0x233c  BL(local=1, imp=5)
 *   CRO 0x2340..0x2a14  BL(local=3, imp=60)
 *   CRO 0x2a28..0x2ad4  BL(local=0, imp=1)
 *   CRO 0x2ae0..0x2b4c  BL(local=0, imp=1)
 *   CRO 0x2b58..0x2bc4  BL(local=0, imp=1)
 *   CRO 0x2bf0..0x2c94  BL(local=0, imp=5)
 *   CRO 0x2c98..0x2cf4  BL(local=0, imp=4)
 *   CRO 0x2d14..0x2ddc  BL(local=1, imp=6)
 *   CRO 0x2dfc..0x2f24  BL(local=0, imp=11)
 *   CRO 0x2fb4..0x2fdc  BL(local=0, imp=1)
 *   CRO 0x2fe0..0x3120  BL(local=0, imp=4)
 *   CRO 0x312c..0x3174  BL(local=0, imp=2)
 *   CRO 0x3188..0x31d0  BL(local=0, imp=2)
 *   CRO 0x31dc..0x3440  BL(local=0, imp=8)
 *   CRO 0x3468..0x34e0  BL(local=0, imp=2)
 *   CRO 0x34f4..0x36e8  BL(local=0, imp=18)
 *   CRO 0x36f0..0x3838  BL(local=0, imp=9)
 *   CRO 0x3844..0x389c  BL(local=0, imp=3)
 *   CRO 0x38a0..0x3b10  BL(local=0, imp=20) [contains export: _ZN9xy_system2bg6System13SetIsCallDrawEb]
 *   CRO 0x3b30..0x3ba8  BL(local=0, imp=6)
 *   CRO 0x3bb8..0x3c24  BL(local=0, imp=5)
 *   CRO 0x3c74..0x3cd4  BL(local=0, imp=2)
 *   CRO 0x3cdc..0x3d04  BL(local=0, imp=2)
 *   CRO 0x3d08..0x3d50  BL(local=0, imp=4)
 *   CRO 0x3d74..0x3e18  BL(local=0, imp=5) [contains export: nnroControlObject_]
 *   CRO 0x3e20..0x3e74  BL(local=0, imp=4)
 *   CRO 0x3f60..0x3fdc  BL(local=0, imp=0)
 */

/* CRO 0x5e0, body spans 0x5e0..0x60c (~0x2c bytes). */
static int gamesync_5e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x618, body spans 0x618..0x644 (~0x2c bytes). */
static int gamesync_618(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x66c, body spans 0x66c..0x6e0 (~0x74 bytes). */
static int gamesync_66c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x198, 0x1a0 */
    /* Field offsets touched: +0x40, +0x88, +0xbc, +0xc4, +0xc8, +0x13c */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x6e8, body spans 0x6e8..0xb04 (~0x41c bytes). */
static int gamesync_6e8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a8, 0x1b0, 0x1b8, 0x2340, 0x22ac, 0x2110, 0x22ac, 0x2340, ... (30 total) */
    /* Field offsets touched: +0x04, +0x18, +0x2c, +0x40, +0x48, +0x4c, +0x4d, +0x50, +0x58, +0x59, +0x5c, +0x80, +0x84, +0x88, +0x89, +0x90, +0xbc, +0xbf, +0xc0, +0xc4, +0xd8, +0xd9, +0xe0, +0x114 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0xb24, body spans 0xb24..0xc4c (~0x128 bytes). */
static int gamesync_b24(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x230, 0x190, 0x238, 0x230, 0x230, 0x198, 0x240 */
    /* Field offsets touched: +0x08, +0x1c, +0x40, +0x59, +0xbc, +0xd9, +0x1d8 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0xcec, body spans 0xcec..0xfa4 (~0x2b8 bytes). */
static int gamesync_cec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238, 0x248, 0x1c0, 0x1c8, 0x1fb0, 0x250, 0x258, 0x238, ... (26 total) */
    /* Field offsets touched: +0x18, +0x1c, +0x2c, +0x30, +0x40, +0x80, +0xa4, +0xc4, +0xc8, +0xdc, +0xe0, +0xe1, +0xe8, +0xec, +0xf4, +0x134 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0xfc8, body spans 0xfc8..0x11b0 (~0x1e8 bytes). */
static int gamesync_fc8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e10, 0x1c0, 0x1c0, 0x1c8, 0x1c8, 0x190, 0x238, 0x2b0, ... (18 total) */
    /* Field offsets touched: +0x04, +0x1c, +0x2c, +0x30, +0x40, +0x80, +0xc4, +0xc8, +0xdb, +0xe0, +0xe1, +0xf4, +0x104, +0x108, +0x10c, +0x110, +0x114, +0x12c, +0x130 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x11e8, body spans 0x11e8..0x1258 (~0x70 bytes). */
static int gamesync_11e8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0x59, +0x5c, +0xbc, +0xbd, +0xbe, +0xbf, +0xe0, +0xe1 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1270, body spans 0x1270..0x12c0 (~0x50 bytes). */
static int gamesync_1270(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c0, 0x1c8, 0x190 */
    /* Field offsets touched: +0x40, +0x80, +0xc4, +0xc8, +0xe0 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x12c8, body spans 0x12c8..0x1534 (~0x26c bytes). */
static int gamesync_12c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e10, 0x238, 0x248, 0x1c0, 0x1c8, 0x1fb0, 0x250, 0x258, ... (19 total) */
    /* Field offsets touched: +0x04, +0x1c, +0x24, +0x30, +0x31, +0x40, +0x80, +0xc4, +0xc8, +0xe0, +0xe1, +0xf4, +0x104, +0x124, +0x131, +0x134 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1558, body spans 0x1558..0x16e8 (~0x190 bytes). */
static int gamesync_1558(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2110, 0x238, 0x290, 0x298, 0x2f0, 0x238, 0x2f8, 0x300, ... (12 total) */
    /* Field offsets touched: +0x18, +0x1c, +0x2c, +0x31, +0x40, +0x80, +0xc4, +0xc8, +0xdb, +0xe0, +0xe1, +0x104, +0x124, +0x131, +0x134 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x16ec, body spans 0x16ec..0x1a30 (~0x344 bytes). */
static int gamesync_16ec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238, 0x248, 0x1c0, 0x1c8, 0x238, 0x2a8, 0x238, 0x290, ... (34 total) */
    /* Field offsets touched: +0x18, +0x1c, +0x2c, +0x30, +0x40, +0x80, +0xa4, +0xc4, +0xc8, +0xdb, +0xdc, +0xe0, +0xe8, +0xec, +0xf4, +0x100, +0x12c, +0x134 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1a3c, body spans 0x1a3c..0x1ca8 (~0x26c bytes). */
static int gamesync_1a3c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x31dc, 0x190, 0x3468, 0x190, 0x3468, 0x190, 0x31dc, ... (9 total) */
    /* Field offsets touched: +0x40, +0x59, +0x5c, +0xa4, +0xbc, +0xdc */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1cb4, body spans 0x1cb4..0x1d14 (~0x60 bytes). */
static int gamesync_1cb4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x330 */
    /* Field offsets touched: +0xe1, +0x131, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1d1c, body spans 0x1d1c..0x1d44 (~0x28 bytes). */
static int gamesync_1d1c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x338 */
    /* Field offsets touched: +0xe1, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1d48, body spans 0x1d48..0x1d90 (~0x48 bytes). */
static int gamesync_1d48(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x340, 0x238, 0x348 */
    /* Field offsets touched: +0x1c, +0xe1, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1db4, body spans 0x1db4..0x1df8 (~0x44 bytes). */
static int gamesync_1db4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0xbc, +0xd8 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1e10, body spans 0x1e10..0x1fac (~0x19c bytes). */
static int gamesync_1e10(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x370, 0x378, 0x380, 0x388, 0x180, 0x180, 0x180, 0x390, ... (19 total) */
    /* Field offsets touched: +0x10, +0x1c, +0xf4, +0xf8, +0xfc, +0x100, +0x108, +0x114, +0x12c, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x1fb0, body spans 0x1fb0..0x2100 (~0x150 bytes). */
static int gamesync_1fb0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x390, 0x1b0, 0x238, 0x3c8, 0x3d0, 0x3d0, 0x3d0, 0x3d8, ... (19 total) */
    /* Field offsets touched: +0x1c, +0x2c, +0x30, +0xe8, +0xec, +0xf0, +0xf4, +0xf8, +0xfc, +0x100, +0x114, +0x11c, +0x120 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2110, body spans 0x2110..0x229c (~0x18c bytes). */
static int gamesync_2110(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x408, 0x408, 0x410, 0x408, 0x408, 0x408, 0x408, 0x418, ... (16 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x88 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x22ac, body spans 0x22ac..0x233c (~0x90 bytes). */
static int gamesync_22ac(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x440, 0x448, 0x450, 0x36f0, 0x210, 0x408 */
    /* Field offsets touched: +0x5c, +0x80, +0x84, +0x88, +0x99 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2340, body spans 0x2340..0x2a14 (~0x6d4 bytes). */
static int gamesync_2340(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x408, 0x408, 0x1c0, 0x1c8, 0x198, 0x1a0, 0x408, 0x408, ... (63 total) */
    /* Field offsets touched: +0x5c, +0x80, +0x8c, +0x94, +0x99, +0xa4 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2a28, body spans 0x2a28..0x2ad4 (~0xac bytes). */
static int gamesync_2a28(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0x26, +0x28, +0x59, +0x5c, +0xa4, +0xbc, +0xbd, +0xbe, +0xbf, +0xdc, +0xe0, +0xe1 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2ae0, body spans 0x2ae0..0x2b4c (~0x6c bytes). */
static int gamesync_2ae0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0x40, +0x59, +0x5c, +0x91, +0x98, +0xbc, +0xc8, +0xe0 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2b58, body spans 0x2b58..0x2bc4 (~0x6c bytes). */
static int gamesync_2b58(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0x40, +0x59, +0x5c, +0x91, +0x98, +0xbc, +0xc8, +0xe0 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2bf0, body spans 0x2bf0..0x2c94 (~0xa4 bytes). */
static int gamesync_2bf0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238, 0x358, 0x238, 0x360, 0x368 */
    /* Field offsets touched: +0x02, +0x1c, +0x104, +0x108, +0x114 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2c98, body spans 0x2c98..0x2cf4 (~0x5c bytes). */
static int gamesync_2c98(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x458, 0x238, 0x460, 0x238 */
    /* Field offsets touched: +0x1c, +0x58, +0xdc, +0x104, +0x114 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2d14, body spans 0x2d14..0x2ddc (~0xc8 bytes). */
static int gamesync_2d14(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e10, 0x470, 0x478, 0x180, 0x180, 0x180, 0x480 */
    /* Field offsets touched: +0x04, +0x10, +0x18, +0x40, +0xf4, +0xf8, +0xfc, +0x100, +0x114 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2dfc, body spans 0x2dfc..0x2f24 (~0x128 bytes). */
static int gamesync_2dfc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x398, 0x398, 0x488, 0x238, 0x468, 0x1b0, 0x238, 0x238, ... (11 total) */
    /* Field offsets touched: +0x1c, +0x2c, +0x50, +0x54, +0x58, +0x59, +0xa4, +0xc4, +0xc8, +0xdc, +0xe0, +0x114 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2fb4, body spans 0x2fb4..0x2fdc (~0x28 bytes). */
static int gamesync_2fb4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b0 */
    /* Field offsets touched: +0x58 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x2fe0, body spans 0x2fe0..0x3120 (~0x140 bytes). */
static int gamesync_2fe0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b8, 0x4c0, 0x238, 0x4c8 */
    /* Field offsets touched: +0x0c, +0x1c, +0x26, +0x28, +0x40, +0x4c, +0x4d, +0x50, +0x54, +0x58, +0x59, +0xbc, +0xbd, +0xbe, +0xbf, +0xc0, +0xc8, +0xd8, +0xd9, +0xda, +0xdb, +0xdc, +0xe0, +0xe1, +0xe4, +0xe8, +0xec, +0xf0, +0xf4, +0xf8, +0xfc, +0x100, +0x104, +0x108, +0x10c, +0x110, +0x114, +0x118, +0x11c, +0x120, +0x124, +0x12c, +0x130, +0x131, +0x134, +0x138, +0x13c */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x312c, body spans 0x312c..0x3174 (~0x48 bytes). */
static int gamesync_312c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4d0, 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3188, body spans 0x3188..0x31d0 (~0x48 bytes). */
static int gamesync_3188(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4d0, 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x31dc, body spans 0x31dc..0x3440 (~0x264 bytes). */
static int gamesync_31dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x408, 0x408, 0x408, 0x408, 0x4d8, 0x4d8, 0x438, 0x438 */
    /* Field offsets touched: +0x5c, +0x8c, +0x91, +0x94, +0x98, +0xa4 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3468, body spans 0x3468..0x34e0 (~0x78 bytes). */
static int gamesync_3468(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x438, 0x438 */
    /* Field offsets touched: +0x8c, +0xa4 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x34f4, body spans 0x34f4..0x36e8 (~0x1f4 bytes). */
static int gamesync_34f4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x418, 0x4d8, 0x4d8, 0x4d8, 0x4d8, 0x4d8, 0x4d8, 0x438, ... (18 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x8c, +0xa0, +0x194, +0x19c, +0x19d, +0x19e, +0x19f, +0x1a0 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x36f0, body spans 0x36f0..0x3838 (~0x148 bytes). */
static int gamesync_36f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4f8, 0x500, 0x238, 0x508, 0x510, 0x518, 0x520, 0x528, ... (9 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x84, +0x88, +0x89 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3844, body spans 0x3844..0x389c (~0x58 bytes). */
static int gamesync_3844(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x538, 0x538, 0x540 */
    /* Field offsets touched: +0x58, +0x5c, +0x78, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x38a0, body spans 0x38a0..0x3b10 (~0x270 bytes). */
static int gamesync_38a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x558, 0x238, 0x560, 0x568, 0x238, 0x508, 0x570, 0x528, ... (20 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x1c, +0x20, +0x5c, +0x74, +0x78, +0x80, +0x84, +0x88, +0x89, +0x8c, +0x90, +0x91, +0x94, +0x98, +0x99, +0xa0 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3b30, body spans 0x3b30..0x3ba8 (~0x78 bytes). */
static int gamesync_3b30(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x188, 0x5a8, 0x5b0, 0x5b8, 0x5c0 */
    /* Field offsets touched: +0x04, +0x5c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3bb8, body spans 0x3bb8..0x3c24 (~0x6c bytes). */
static int gamesync_3bb8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x188, 0x5a8, 0x5b0, 0x5b8 */
    /* Field offsets touched: +0x04, +0x5c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3c74, body spans 0x3c74..0x3cd4 (~0x60 bytes). */
static int gamesync_3c74(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x330 */
    /* Field offsets touched: +0xe1, +0x131, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3cdc, body spans 0x3cdc..0x3d04 (~0x28 bytes). */
static int gamesync_3cdc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x338 */
    /* Field offsets touched: +0xe1, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3d08, body spans 0x3d08..0x3d50 (~0x48 bytes). */
static int gamesync_3d08(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x340, 0x238, 0x348 */
    /* Field offsets touched: +0x1c, +0xe1, +0x138 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3d74, body spans 0x3d74..0x3e18 (~0xa4 bytes). */
static int gamesync_3d74(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238, 0x358, 0x238, 0x360, 0x368 */
    /* Field offsets touched: +0x02, +0x1c, +0xe4, +0x104, +0x108, +0x114 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3e20, body spans 0x3e20..0x3e74 (~0x54 bytes). */
static int gamesync_3e20(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x458, 0x238, 0x460, 0x238 */
    /* Field offsets touched: +0x1c, +0x58, +0xb8, +0xe0, +0xf0 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* CRO 0x3f60, body spans 0x3f60..0x3fdc (~0x7c bytes). */
static int gamesync_3f60(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllGameSync.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x3dd8 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x3dd8..; BL targets: 0x238, 0x360, 0x368 */
    /* TODO: not yet decoded */
    return 1;
}

/* CRO 0x3ab0 (segment 0) — _ZN9xy_system2bg6System13SetIsCallDrawEb */
int _ZN9xy_system2bg6System13SetIsCallDrawEb(ModuleActor *self) {
    (void)self;
    /* Body spans 0x3ab0..; BL targets: 0x1b0, 0x238 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 47 candidate function boundaries (push/pop pairing).
 * Total BL sites: 434 (to imports: 399, internal: 35).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */