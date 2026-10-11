/*
 * Preliminary decompilation of DllPoke3Select.cro.
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

/* Module summary (from DllPoke3Select.cro header):
 *   file size: 0xa000
 *   code:      offset 0x180  size 0x6e80
 *   data:      offset 0x8e48  size 0x3a4
 *   bss:       size  0x3c8
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 201
 *   import veneers (ldr pc,[pc,#N]): 151 at 0x184..0x634
 *   total BL sites: 374 (to imports: 321, internal: 53)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 154x)
 *   +0x14 (hit 64x)
 *   +0x0c (hit 63x)
 *   +0x08 (hit 56x)
 *   +0x7c (hit 36x)
 *   +0x10 (hit 35x)
 *   +0x6c (hit 29x)
 *   +0x84 (hit 28x)
 *   +0x8c (hit 28x)
 *   +0x5c (hit 26x)
 *   +0x38 (hit 25x)
 *   +0x18 (hit 23x)
 *   +0xbc (hit 23x)
 *   +0x94 (hit 19x)
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

/* Index: 63 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x0668..0x0670  BL(local=1, imp=0)
 *   CRO 0x0678..0x0774  BL(local=0, imp=3)
 *   CRO 0x0784..0x0908  BL(local=0, imp=8)
 *   CRO 0x0914..0x09a0  BL(local=0, imp=4)
 *   CRO 0x09f0..0x0b04  BL(local=2, imp=3)
 *   CRO 0x0b10..0x0c18  BL(local=2, imp=6)
 *   CRO 0x0c20..0x0c74  BL(local=0, imp=3)
 *   CRO 0x0c84..0x0ccc  BL(local=0, imp=3)
 *   CRO 0x0cdc..0x0d2c  BL(local=0, imp=3)
 *   CRO 0x0d38..0x0f14  BL(local=7, imp=4)
 *   CRO 0x0f6c..0x1030  BL(local=0, imp=5)
 *   CRO 0x1060..0x1120  BL(local=0, imp=10)
 *   CRO 0x1128..0x12a8  BL(local=3, imp=12)
 *   CRO 0x12bc..0x1348  BL(local=0, imp=3)
 *   CRO 0x135c..0x13e4  BL(local=0, imp=2)
 *   CRO 0x13f0..0x148c  BL(local=0, imp=1)
 *   CRO 0x1498..0x1534  BL(local=0, imp=1)
 *   CRO 0x153c..0x1618  BL(local=4, imp=3)
 *   CRO 0x1668..0x18f4  BL(local=0, imp=14)
 *   CRO 0x1904..0x1ae8  BL(local=2, imp=14)
 *   CRO 0x1b74..0x1cd8  BL(local=3, imp=4)
 *   CRO 0x1cfc..0x1d18  BL(local=0, imp=1)
 *   CRO 0x1d20..0x1e0c  BL(local=0, imp=2)
 *   CRO 0x1e10..0x20b0  BL(local=1, imp=19)
 *   CRO 0x20d0..0x2170  BL(local=0, imp=4)
 *   CRO 0x2184..0x221c  BL(local=0, imp=3)
 *   CRO 0x2230..0x228c  BL(local=0, imp=2)
 *   CRO 0x2298..0x245c  BL(local=0, imp=3)
 *   CRO 0x2474..0x2578  BL(local=0, imp=3)
 *   CRO 0x2584..0x260c  BL(local=0, imp=3)
 *   CRO 0x2624..0x263c  BL(local=1, imp=1)
 *   CRO 0x2644..0x272c  BL(local=2, imp=2)
 *   CRO 0x2774..0x28b0  BL(local=0, imp=8)
 *   CRO 0x28c4..0x29e4  BL(local=2, imp=4)
 *   CRO 0x2a0c..0x2d24  BL(local=9, imp=6)
 *   CRO 0x2d48..0x2e68  BL(local=0, imp=6)
 *   CRO 0x2e70..0x2f94  BL(local=0, imp=4)
 *   CRO 0x2f98..0x3264  BL(local=0, imp=12)
 *   CRO 0x3268..0x3408  BL(local=0, imp=8)
 *   CRO 0x3444..0x3514  BL(local=2, imp=7)
 *   CRO 0x3528..0x36a4  BL(local=0, imp=4)
 *   CRO 0x36a8..0x390c  BL(local=3, imp=12)
 *   CRO 0x3938..0x39d8  BL(local=0, imp=4)
 *   CRO 0x39ec..0x3a84  BL(local=0, imp=3)
 *   CRO 0x3a90..0x3c98  BL(local=0, imp=10)
 *   CRO 0x3ca4..0x3df8  BL(local=3, imp=2)
 *   CRO 0x3e04..0x3e24  BL(local=0, imp=1)
 *   CRO 0x3e34..0x3e5c  BL(local=0, imp=1)
 *   CRO 0x3e6c..0x3e8c  BL(local=0, imp=1)
 *   CRO 0x3e9c..0x3ec4  BL(local=0, imp=1)
 *   CRO 0x3ed8..0x4020  BL(local=0, imp=17)
 *   CRO 0x4024..0x4334  BL(local=0, imp=17)
 *   CRO 0x4358..0x4408  BL(local=0, imp=11)
 *   CRO 0x4414..0x44c8  BL(local=0, imp=11)
 *   CRO 0x44f8..0x4580  BL(local=0, imp=0)
 *   CRO 0x458c..0x45b8  BL(local=0, imp=1)
 *   CRO 0x45c4..0x45f0  BL(local=0, imp=1)
 *   CRO 0x4600..0x46c4  BL(local=0, imp=5)
 *   CRO 0x46d8..0x4714  BL(local=1, imp=1)
 *   CRO 0x47c0..0x4828  BL(local=0, imp=2)
 *   CRO 0x48c4..0x4954  BL(local=0, imp=4)
 *   CRO 0x49a4..0x5728  BL(local=0, imp=1) [contains export: nnroControlObject_]
 *   CRO 0x5744..0x57c0  BL(local=0, imp=0)
 */

/* CRO 0x668, body spans 0x668..0x670 (~0x8 bytes). */
static int poke3select_668(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x678 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x678, body spans 0x678..0x774 (~0xfc bytes). */
static int poke3select_678(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x18c, 0x194, 0x19c */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x18, +0x38 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x784, body spans 0x784..0x908 (~0x184 bytes). */
static int poke3select_784(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a4, 0x1ac, 0x1b4, 0x1ac, 0x1b4, 0x1bc, 0x1b4, 0x1c4 */
    /* Field offsets touched: +0x04, +0x3c, +0x48, +0x4c, +0x80, +0xbc */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x914, body spans 0x914..0x9a0 (~0x8c bytes). */
static int poke3select_914(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1cc, 0x1d4, 0x1dc, 0x1e4 */
    /* Field offsets touched: +0x04, +0x1c, +0x40, +0x48 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x9f0, body spans 0x9f0..0xb04 (~0x114 bytes). */
static int poke3select_9f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x1ec, 0x3528, 0x1d20, 0x1f4 */
    /* Field offsets touched: +0x04, +0x18, +0x1c, +0x3c, +0x40, +0x7c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0xb10, body spans 0xb10..0xc18 (~0x108 bytes). */
static int poke3select_b10(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x204, 0x1cc, 0x20c, 0x1cc, 0x214, 0x204, 0x1128, 0xd38 */
    /* Field offsets touched: +0x04, +0x28, +0x3c, +0x40, +0x44, +0x88 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0xc20, body spans 0xc20..0xc74 (~0x54 bytes). */
static int poke3select_c20(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x21c, 0x224, 0x22c */
    /* Field offsets touched: +0x44, +0x48, +0x4c */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0xc84, body spans 0xc84..0xccc (~0x48 bytes). */
static int poke3select_c84(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x234, 0x23c, 0x18c */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0xcdc, body spans 0xcdc..0xd2c (~0x50 bytes). */
static int poke3select_cdc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x234, 0x23c, 0x18c */
    /* Field offsets touched: +0x14, +0x20 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0xd38, body spans 0xd38..0xf14 (~0x1dc bytes). */
static int poke3select_d38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x244, 0x24c, 0x3a90, 0x2f98, 0x2e70, 0x2d48, 0x3268, ... (11 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x38, +0x78, +0x7c, +0x80, +0x84, +0x88, +0x90, +0x9c, +0xac, +0xe0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0xf6c, body spans 0xf6c..0x1030 (~0xc4 bytes). */
static int poke3select_f6c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x25c, 0x264, 0x1d4, 0x26c */
    /* Field offsets touched: +0x02, +0x04, +0x0c, +0x6c, +0x7c, +0x84, +0x8c, +0xec */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1060, body spans 0x1060..0x1120 (~0xc0 bytes). */
static int poke3select_1060(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x274, 0x27c, 0x284, 0x28c, 0x294, 0x29c, 0x28c, 0x294, ... (10 total) */
    /* Field offsets touched: +0x08, +0x10, +0x14, +0x84 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1128, body spans 0x1128..0x12a8 (~0x180 bytes). */
static int poke3select_1128(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b4, 0x204, 0x2bc, 0x2c4, 0x204, 0x2cc, 0x4024, 0x204, ... (15 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x74, +0x78, +0x7c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x12bc, body spans 0x12bc..0x1348 (~0x8c bytes). */
static int poke3select_12bc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2ec, 0x2ec, 0x2f4 */
    /* Field offsets touched: +0x04, +0x18, +0x7c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x135c, body spans 0x135c..0x13e4 (~0x88 bytes). */
static int poke3select_135c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2ec, 0x2ec */
    /* Field offsets touched: +0x04, +0x18, +0x7c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x13f0, body spans 0x13f0..0x148c (~0x9c bytes). */
static int poke3select_13f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x194 */
    /* Field offsets touched: +0x04, +0x08, +0x0c */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1498, body spans 0x1498..0x1534 (~0x9c bytes). */
static int poke3select_1498(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x194 */
    /* Field offsets touched: +0x04, +0x08, +0x0c */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x153c, body spans 0x153c..0x1618 (~0xdc bytes). */
static int poke3select_153c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2fc, 0x28c4, 0x2774, 0x2fc, 0x2774, 0x2fc, 0x2774 */
    /* Field offsets touched: +0xb4 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1668, body spans 0x1668..0x18f4 (~0x28c bytes). */
static int poke3select_1668(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x30c, 0x314, 0x30c, 0x314, 0x30c, 0x314, 0x31c, 0x324, ... (14 total) */
    /* Field offsets touched: +0x0c, +0x10, +0x14, +0x18, +0x30, +0x38, +0x60, +0x7c, +0x88, +0x8c, +0x98, +0x9c, +0xa0, +0xbc, +0xe8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1904, body spans 0x1904..0x1ae8 (~0x1e4 bytes). */
static int poke3select_1904(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x304, 0x354, 0x35c, 0x35c, 0x304, 0x364, 0x36c, 0x354, ... (16 total) */
    /* Field offsets touched: +0x04, +0x20, +0x5c, +0x84, +0xa8, +0xb4, +0xb8, +0xbc */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1b74, body spans 0x1b74..0x1cd8 (~0x164 bytes). */
static int poke3select_1b74(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x39c, 0x37c, 0x384, 0x2730, 0x2730, 0x2774 */
    /* Field offsets touched: +0x04, +0x20, +0x80, +0x8c, +0xa8, +0xb4, +0xbc */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1cfc, body spans 0x1cfc..0x1d18 (~0x1c bytes). */
static int poke3select_1cfc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3a4 */
    /* Field offsets touched: +0x58, +0x5c, +0xb8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1d20, body spans 0x1d20..0x1e0c (~0xec bytes). */
static int poke3select_1d20(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x34c, 0x3b4 */
    /* Field offsets touched: +0x04, +0x14, +0x38, +0x7c, +0x8c, +0xa0, +0xb0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x1e10, body spans 0x1e10..0x20b0 (~0x2a0 bytes). */
static int poke3select_1e10(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b4, 0x3bc, 0x3c4, 0x304, 0x304, 0x354, 0x204, 0x204, ... (20 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x14, +0x18, +0x38, +0x58, +0x5c, +0x74, +0x7c, +0x84, +0x88, +0x8c, +0xa0, +0xa4, +0xa8, +0xac, +0xb8, +0xbc */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x20d0, body spans 0x20d0..0x2170 (~0xa0 bytes). */
static int poke3select_20d0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3fc, 0x184, 0x404, 0x2f4 */
    /* Field offsets touched: +0x04, +0x88, +0xa4, +0xa8, +0xb8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2184, body spans 0x2184..0x221c (~0x98 bytes). */
static int poke3select_2184(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3fc, 0x184, 0x404 */
    /* Field offsets touched: +0x04, +0x88, +0xa4, +0xa8, +0xb8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2230, body spans 0x2230..0x228c (~0x5c bytes). */
static int poke3select_2230(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x26c */
    /* Field offsets touched: +0x02, +0x04, +0x70, +0x7c */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2298, body spans 0x2298..0x245c (~0x1c4 bytes). */
static int poke3select_2298(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x204, 0x40c */
    /* Field offsets touched: +0x04, +0x14, +0x34, +0x38, +0x40, +0x54, +0x6c, +0x70, +0x74, +0x78, +0x7c, +0x84 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2474, body spans 0x2474..0x2578 (~0x104 bytes). */
static int poke3select_2474(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x414, 0x1d4 */
    /* Field offsets touched: +0x1c, +0x28, +0x30, +0x34, +0x38 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2584, body spans 0x2584..0x260c (~0x88 bytes). */
static int poke3select_2584(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x40c, 0x37c, 0x384 */
    /* Field offsets touched: +0x04, +0x20, +0x24, +0x5c */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2624, body spans 0x2624..0x263c (~0x18 bytes). */
static int poke3select_2624(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x274, 0x1904 */
    /* Field offsets touched: +0xa8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2644, body spans 0x2644..0x272c (~0xe8 bytes). */
static int poke3select_2644(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2474, 0x2474, 0x37c, 0x384 */
    /* Field offsets touched: +0x04, +0x08, +0x20, +0x24, +0x34, +0x38, +0x58, +0x94 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2774, body spans 0x2774..0x28b0 (~0x13c bytes). */
static int poke3select_2774(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x39c, 0x304, 0x1d4, 0x41c, 0x424, 0x42c, 0x3c4 */
    /* Field offsets touched: +0x5c, +0x84, +0x8c, +0xb4, +0xbc */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x28c4, body spans 0x28c4..0x29e4 (~0x120 bytes). */
static int poke3select_28c4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x39c, 0x37c, 0x384, 0x2730, 0x2730 */
    /* Field offsets touched: +0x04, +0x20, +0x80, +0x8c, +0xa8, +0xb4, +0xbc */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2a0c, body spans 0x2a0c..0x2d24 (~0x318 bytes). */
static int poke3select_2a0c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2730, 0x2730, 0x2730, 0x2730, 0x2730, 0x2730, 0x2730, 0x37c, ... (15 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x6c, +0x7c, +0x84, +0xa0, +0xe8, +0xec, +0x230, +0x248 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2d48, body spans 0x2d48..0x2e68 (~0x120 bytes). */
static int poke3select_2d48(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x434, 0x43c, 0x204, 0x44c, 0x204, 0x45c */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2e70, body spans 0x2e70..0x2f94 (~0x124 bytes). */
static int poke3select_2e70(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x46c, 0x474, 0x47c, 0x484 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x2f98, body spans 0x2f98..0x3264 (~0x2cc bytes). */
static int poke3select_2f98(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x1d4, 0x43c, 0x1d4, 0x204, 0x48c, 0x494, 0x204, ... (12 total) */
    /* Field offsets touched: +0x04, +0x08, +0x09, +0x0c, +0x10, +0x14, +0x18, +0x38 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3268, body spans 0x3268..0x3408 (~0x1a0 bytes). */
static int poke3select_3268(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x30c, 0x314, 0x31c, 0x324, 0x31c, 0x33c, 0x344 */
    /* Field offsets touched: +0x0c, +0x10, +0x14, +0x30, +0x38, +0x78, +0x90, +0x94, +0x98, +0xb4, +0xbc, +0xe8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3444, body spans 0x3444..0x3514 (~0xd0 bytes). */
static int poke3select_3444(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x274, 0x2644, 0x2474, 0x4b4, 0x1d4, 0x4bc, 0x28c, 0x4c4, ... (9 total) */
    /* Field offsets touched: +0x08, +0x14, +0x38, +0x78, +0x84, +0xa0, +0xf0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3528, body spans 0x3528..0x36a4 (~0x17c bytes). */
static int poke3select_3528(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x34c, 0x4d4, 0x4dc, 0x3b4 */
    /* Field offsets touched: +0x04, +0x08, +0x14, +0x38, +0x6c, +0x74, +0x78, +0x84, +0x94, +0x98, +0xe4, +0x1d0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x36a8, body spans 0x36a8..0x390c (~0x264 bytes). */
static int poke3select_36a8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b4, 0x3bc, 0x304, 0x204, 0x204, 0x204, 0x28c, 0x204, ... (15 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x14, +0x38, +0x58, +0x5c, +0x78, +0x90, +0x94, +0x98, +0x9c, +0xa0, +0xa4, +0xcc, +0xd4, +0xd8, +0xdc, +0xe0, +0xe4, +0xe8, +0xf0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3938, body spans 0x3938..0x39d8 (~0xa0 bytes). */
static int poke3select_3938(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4f4, 0x184, 0x404, 0x2f4 */
    /* Field offsets touched: +0x04, +0x74, +0x90, +0x9c, +0xa0, +0xf0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x39ec, body spans 0x39ec..0x3a84 (~0x98 bytes). */
static int poke3select_39ec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4f4, 0x184, 0x404 */
    /* Field offsets touched: +0x04, +0x74, +0x90, +0x9c, +0xa0, +0xf0 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3a90, body spans 0x3a90..0x3c98 (~0x208 bytes). */
static int poke3select_3a90(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4fc, 0x504, 0x50c, 0x514, 0x25c, 0x51c, 0x524, 0x52c, ... (10 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x20, +0x34, +0x60, +0x64, +0x68, +0x6c, +0x70, +0x144, +0x1d0, +0x337, +0x3ed */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3ca4, body spans 0x3ca4..0x3df8 (~0x154 bytes). */
static int poke3select_3ca4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2474, 0x2474, 0x2474, 0x52c, 0x53c */
    /* Field offsets touched: +0x04, +0x08, +0x6c, +0x78, +0x7c, +0xb0, +0xec, +0x128, +0x13c, +0x337 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3e04, body spans 0x3e04..0x3e24 (~0x20 bytes). */
static int poke3select_3e04(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x544 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3e34, body spans 0x3e34..0x3e5c (~0x28 bytes). */
static int poke3select_3e34(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x544 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3e6c, body spans 0x3e6c..0x3e8c (~0x20 bytes). */
static int poke3select_3e6c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x544 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3e9c, body spans 0x3e9c..0x3ec4 (~0x28 bytes). */
static int poke3select_3e9c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x544 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x3ed8, body spans 0x3ed8..0x4020 (~0x148 bytes). */
static int poke3select_3ed8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x27c, 0x54c, 0x554, 0x55c, 0x554, 0x55c, 0x28c, 0x564, ... (17 total) */
    /* Field offsets touched: +0x04, +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x4024, body spans 0x4024..0x4334 (~0x310 bytes). */
static int poke3select_4024(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x204, 0x5a4, 0x40c, 0x204, 0x5ac, 0x254, 0x5b4, 0x27c, ... (17 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x38 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x4358, body spans 0x4358..0x4408 (~0xb0 bytes). */
static int poke3select_4358(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5ec, 0x5f4, 0x184, 0x5fc, 0x604, 0x60c, 0x614, 0x61c, ... (11 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x4414, body spans 0x4414..0x44c8 (~0xb4 bytes). */
static int poke3select_4414(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5ec, 0x5f4, 0x184, 0x5fc, 0x604, 0x60c, 0x614, 0x61c, ... (11 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x44f8, body spans 0x44f8..0x4580 (~0x88 bytes). */
static int poke3select_44f8(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40, +0x48, +0x4c, +0x50, +0x54, +0x58, +0x5c, +0x60 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x458c, body spans 0x458c..0x45b8 (~0x2c bytes). */
static int poke3select_458c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x18c */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x45c4, body spans 0x45c4..0x45f0 (~0x2c bytes). */
static int poke3select_45c4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x18c */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x4600, body spans 0x4600..0x46c4 (~0xc4 bytes). */
static int poke3select_4600(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x25c, 0x264, 0x1d4, 0x26c */
    /* Field offsets touched: +0x02, +0x04, +0x08, +0x0c, +0x6c, +0x7c, +0x84, +0x8c, +0xec */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x46d8, body spans 0x46d8..0x4714 (~0x3c bytes). */
static int poke3select_46d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2fc, 0x28c4 */
    /* Field offsets touched: +0xb4 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x47c0, body spans 0x47c0..0x4828 (~0x68 bytes). */
static int poke3select_47c0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d4, 0x26c */
    /* Field offsets touched: +0x02, +0x04, +0x70, +0x7c */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x48c4, body spans 0x48c4..0x4954 (~0x90 bytes). */
static int poke3select_48c4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1cc, 0x1d4, 0x1dc, 0x1e4 */
    /* Field offsets touched: +0x04, +0x1c, +0x40, +0x48 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x49a4, body spans 0x49a4..0x5728 (~0xd84 bytes). */
static int poke3select_49a4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x634 */
    /* Field offsets touched: +0x08, +0x0c, +0x1c, +0x24, +0x28, +0x30, +0x38, +0x3c, +0x48, +0x4c, +0x54, +0x60, +0x6c, +0x70, +0x74, +0x78, +0x7c, +0x84, +0x90, +0x9c, +0xc0, +0xcc, +0xd8, +0xe4, +0xf0, +0xf8 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* CRO 0x5744, body spans 0x5744..0x57c0 (~0x7c bytes). */
static int poke3select_5744(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllPoke3Select.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x55bc (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x55bc..; BL targets:  */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 63 candidate function boundaries (push/pop pairing).
 * Total BL sites: 374 (to imports: 321, internal: 53).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */