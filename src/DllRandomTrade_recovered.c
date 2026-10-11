/*
 * Preliminary decompilation of DllRandomTrade.cro.
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

/* Module summary (from DllRandomTrade.cro header):
 *   file size: 0x8000
 *   code:      offset 0x180  size 0x5e80
 *   data:      offset 0x7e30  size 0x1c
 *   bss:       size  0x80
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 273
 *   import veneers (ldr pc,[pc,#N]): 226 at 0x180..0x888
 *   total BL sites: 505 (to imports: 477, internal: 28)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 60x)
 *   +0x2c (hit 42x)
 *   +0x0c (hit 41x)
 *   +0x14 (hit 39x)
 *   +0x5c (hit 37x)
 *   +0x10 (hit 29x)
 *   +0x08 (hit 25x)
 *   +0x28 (hit 24x)
 *   +0x78c (hit 21x)
 *   +0x75c (hit 21x)
 *   +0x74 (hit 21x)
 *   +0x94 (hit 20x)
 *   +0x18 (hit 19x)
 *   +0x80 (hit 19x)
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

/* Index: 49 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x08b4..0x08e0  BL(local=0, imp=1)
 *   CRO 0x08ec..0x0918  BL(local=0, imp=1)
 *   CRO 0x092c..0x0b58  BL(local=0, imp=20)
 *   CRO 0x0b60..0x0c50  BL(local=0, imp=6)
 *   CRO 0x0c5c..0x0cec  BL(local=0, imp=1)
 *   CRO 0x0cf8..0x0d8c  BL(local=0, imp=1)
 *   CRO 0x0df4..0x0e60  BL(local=0, imp=1)
 *   CRO 0x0e64..0x0ef0  BL(local=0, imp=5)
 *   CRO 0x0ef8..0x0f24  BL(local=0, imp=5)
 *   CRO 0x0f38..0x0f50  BL(local=0, imp=3)
 *   CRO 0x0f58..0x0f78  BL(local=0, imp=2)
 *   CRO 0x0f84..0x0fa0  BL(local=0, imp=1)
 *   CRO 0x0fac..0x1024  BL(local=0, imp=5)
 *   CRO 0x1030..0x1128  BL(local=0, imp=4)
 *   CRO 0x1130..0x1290  BL(local=3, imp=13)
 *   CRO 0x1294..0x15ec  BL(local=3, imp=34)
 *   CRO 0x1850..0x18d4  BL(local=0, imp=7)
 *   CRO 0x18e4..0x1968  BL(local=0, imp=6)
 *   CRO 0x1974..0x1a48  BL(local=1, imp=3)
 *   CRO 0x1a4c..0x1adc  BL(local=0, imp=9)
 *   CRO 0x1ae0..0x1bc8  BL(local=1, imp=5)
 *   CRO 0x1bd4..0x1c2c  BL(local=0, imp=8)
 *   CRO 0x1c40..0x2520  BL(local=0, imp=72)
 *   CRO 0x2538..0x269c  BL(local=0, imp=21)
 *   CRO 0x26a0..0x2848  BL(local=0, imp=8)
 *   CRO 0x2860..0x297c  BL(local=0, imp=18)
 *   CRO 0x2984..0x2a60  BL(local=0, imp=8)
 *   CRO 0x2a64..0x2ad4  BL(local=0, imp=5)
 *   CRO 0x2ae0..0x2af0  BL(local=0, imp=1)
 *   CRO 0x2af4..0x2c3c  BL(local=0, imp=17)
 *   CRO 0x2c44..0x2da8  BL(local=0, imp=8)
 *   CRO 0x2dc8..0x30e4  BL(local=2, imp=22)
 *   CRO 0x3108..0x3110  BL(local=1, imp=0)
 *   CRO 0x3118..0x3210  BL(local=0, imp=10)
 *   CRO 0x321c..0x32b0  BL(local=0, imp=4)
 *   CRO 0x32b8..0x32f4  BL(local=0, imp=2)
 *   CRO 0x32f8..0x335c  BL(local=0, imp=1)
 *   CRO 0x3360..0x3384  BL(local=0, imp=2)
 *   CRO 0x3388..0x33a4  BL(local=0, imp=1)
 *   CRO 0x33ac..0x33ec  BL(local=0, imp=0)
 *   CRO 0x3430..0x3eb8  BL(local=15, imp=72)
 *   CRO 0x3ed8..0x4084  BL(local=0, imp=17)
 *   CRO 0x4088..0x4094  BL(local=0, imp=1)
 *   CRO 0x40b8..0x40cc  BL(local=0, imp=1)
 *   CRO 0x40d4..0x4200  BL(local=0, imp=11) [contains export: _ZN9xy_system2bg6System13SetIsCallDrawEb]
 *   CRO 0x4210..0x4218  BL(local=1, imp=0)
 *   CRO 0x4220..0x4330  BL(local=0, imp=6) [contains export: nnroControlObject_]
 *   CRO 0x434c..0x43ec  BL(local=0, imp=0)
 *   CRO 0x4434..0x44b0  BL(local=0, imp=0)
 */

/* CRO 0x8b4, body spans 0x8b4..0x8e0 (~0x2c bytes). */
static int randomtrade_8b4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x8ec, body spans 0x8ec..0x918 (~0x2c bytes). */
static int randomtrade_8ec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x92c, body spans 0x92c..0xb58 (~0x22c bytes). */
static int randomtrade_92c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x198, 0x198, 0x1a0, 0x1a8, 0x1b0, 0x1b8, 0x1c0, ... (20 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x11, +0x12, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x34, +0x38, +0x3c, +0x40 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xb60, body spans 0xb60..0xc50 (~0xf0 bytes). */
static int randomtrade_b60(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x210, 0x218, 0x198, 0x198, 0x198 */
    /* Field offsets touched: +0x0c, +0x14, +0x18, +0x20, +0x24, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xc5c, body spans 0xc5c..0xcec (~0x90 bytes). */
static int randomtrade_c5c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188 */
    /* Field offsets touched: +0x04, +0x08, +0x20, +0x24, +0x28, +0x2c, +0x38 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xcf8, body spans 0xcf8..0xd8c (~0x94 bytes). */
static int randomtrade_cf8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188 */
    /* Field offsets touched: +0x04, +0x08, +0x20, +0x24, +0x28, +0x2c, +0x38 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xdf4, body spans 0xdf4..0xe60 (~0x6c bytes). */
static int randomtrade_df4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x3ac, +0x3ad, +0x75c, +0x78c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xe64, body spans 0xe64..0xef0 (~0x8c bytes). */
static int randomtrade_e64(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x240, 0x248, 0x250, 0x1e0, 0x238 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x28, +0x34, +0x3ac, +0x3ad, +0x78c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xef8, body spans 0xef8..0xf24 (~0x2c bytes). */
static int randomtrade_ef8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x260, 0x268, 0x270, 0x260, 0x278 */
    /* Field offsets touched: +0x5c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xf38, body spans 0xf38..0xf50 (~0x18 bytes). */
static int randomtrade_f38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x288, 0x260, 0x278 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xf58, body spans 0xf58..0xf78 (~0x20 bytes). */
static int randomtrade_f58(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x298, 0x2a0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xf84, body spans 0xf84..0xfa0 (~0x1c bytes). */
static int randomtrade_f84(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x298 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0xfac, body spans 0xfac..0x1024 (~0x78 bytes). */
static int randomtrade_fac(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x2b0, 0x270, 0x2b0, 0x270 */
    /* Field offsets touched: +0x24, +0x5c, +0x78, +0xa1 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1030, body spans 0x1030..0x1128 (~0xf8 bytes). */
static int randomtrade_1030(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238, 0x2b8, 0x2c0, 0x2c8 */
    /* Field offsets touched: +0x04, +0x30, +0x38, +0x78, +0x94, +0x9c, +0xa0, +0xa1, +0xa4, +0x12c, +0x136 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1130, body spans 0x1130..0x1290 (~0x160 bytes). */
static int randomtrade_1130(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d0, 0x2d8, 0x2d0, 0x2d8, 0x2e0, 0x278, 0x2e8, 0x278, ... (16 total) */
    /* Field offsets touched: +0x5c, +0x74, +0x78, +0x80, +0x88, +0x8c, +0x9c, +0x124, +0x128, +0x136 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1294, body spans 0x1294..0x15ec (~0x358 bytes). */
static int randomtrade_1294(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x308, 0x310, 0x238, 0x318, 0x278, 0x320, 0x328, ... (37 total) */
    /* Field offsets touched: +0x04, +0x10, +0x5c, +0x78, +0x7c, +0x80, +0x8c, +0x90, +0x94, +0x98, +0x9c, +0xa0, +0xa1, +0xa2, +0x11c, +0x136 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1850, body spans 0x1850..0x18d4 (~0x84 bytes). */
static int randomtrade_1850(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x278, 0x3a0, 0x3a8, 0x3a8, 0x298, 0x3b0, 0x2a0 */
    /* Field offsets touched: +0x18, +0x74, +0x78 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x18e4, body spans 0x18e4..0x1968 (~0x84 bytes). */
static int randomtrade_18e4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x278, 0x3a0, 0x3a8, 0x3a8, 0x298, 0x3b0 */
    /* Field offsets touched: +0x18, +0x74, +0x78 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1974, body spans 0x1974..0x1a48 (~0xd4 bytes). */
static int randomtrade_1974(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1030, 0x460, 0x468, 0x470 */
    /* Field offsets touched: +0x04, +0x18, +0xa0, +0x75c, +0x76c, +0x770, +0x794, +0x79c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1a4c, body spans 0x1a4c..0x1adc (~0x90 bytes). */
static int randomtrade_1a4c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x478, 0x480, 0x278, 0x488, 0x468, 0x470, 0x3a8, 0x3a8, ... (9 total) */
    /* Field offsets touched: +0x5c, +0x74, +0x7c, +0x94, +0xa0 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1ae0, body spans 0x1ae0..0x1bc8 (~0xe8 bytes). */
static int randomtrade_1ae0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x198, 0x498, 0x198, 0x1294, 0x4a0 */
    /* Field offsets touched: +0x14, +0x28, +0x2c, +0x34, +0x75c, +0x764, +0x768, +0x76c, +0x770, +0x78c, +0x798, +0x79c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1bd4, body spans 0x1bd4..0x1c2c (~0x58 bytes). */
static int randomtrade_1bd4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4a8, 0x278, 0x4b0, 0x278, 0x350, 0x278, 0x350, 0x278 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x1c40, body spans 0x1c40..0x2520 (~0x8e0 bytes). */
static int randomtrade_1c40(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x468, 0x470, 0x468, 0x4c0, 0x468, 0x4c8, 0x4d0, 0x4d8, ... (72 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x20, +0x24, +0x28, +0x29, +0x2c, +0x30, +0x34, +0x38, +0x80, +0x88, +0x89, +0xe0, +0xe4, +0xe8, +0x108, +0x10c, +0x110, +0x118, +0x120, +0x124, +0x128 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2538, body spans 0x2538..0x269c (~0x164 bytes). */
static int randomtrade_2538(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3b8, 0x278, 0x3c0, 0x278, 0x2f8, 0x3c8, 0x278, 0x3d0, ... (21 total) */
    /* Field offsets touched: +0x8c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x26a0, body spans 0x26a0..0x2848 (~0x1a8 bytes). */
static int randomtrade_26a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x238, 0x238, 0x3f0, 0x3f8, 0x400, 0x408, 0x410, 0x418 */
    /* Field offsets touched: +0x04, +0x0c, +0x20, +0x34, +0x38, +0x8c, +0x94, +0x12c, +0x134, +0x144, +0x337, +0x3ed */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2860, body spans 0x2860..0x297c (~0x11c bytes). */
static int randomtrade_2860(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x420, 0x428, 0x430, 0x438, 0x440, 0x448, 0x450, 0x278, ... (18 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x74 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2984, body spans 0x2984..0x2a60 (~0xdc bytes). */
static int randomtrade_2984(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x1b8, 0x5f0, 0x5f8, 0x600, 0x318, 0x608, 0x610 */
    /* Field offsets touched: +0x04, +0x08, +0x5c, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2a64, body spans 0x2a64..0x2ad4 (~0x70 bytes). */
static int randomtrade_2a64(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x270, 0x260, 0x278, 0x280 */
    /* Field offsets touched: +0x5c, +0x94, +0xa4, +0xa8 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2ae0, body spans 0x2ae0..0x2af0 (~0x10 bytes). */
static int randomtrade_2ae0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2c8 */
    /* Field offsets touched: +0xa4 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2af4, body spans 0x2af4..0x2c3c (~0x148 bytes). */
static int randomtrade_2af4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x288, 0x628, 0x260, 0x278, 0x290, 0x638, 0x640, 0x648, ... (17 total) */
    /* Field offsets touched: +0x08, +0x34, +0x80, +0x94, +0x98, +0x9c, +0xa4 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2c44, body spans 0x2c44..0x2da8 (~0x164 bytes). */
static int randomtrade_2c44(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x680, 0x688, 0x690, 0x698, 0x6a0, 0x198, 0x6b0 */
    /* Field offsets touched: +0x04, +0x90, +0x94, +0x98, +0xa8 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x2dc8, body spans 0x2dc8..0x30e4 (~0x31c bytes). */
static int randomtrade_2dc8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x6b8, 0x368, 0x370, 0x378, 0x2c44, 0x6c0, 0x198, ... (24 total) */
    /* Field offsets touched: +0x04, +0x08, +0x10, +0x20, +0x74, +0x9c, +0xa4, +0xa8, +0xdc, +0x11c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x3108, body spans 0x3108..0x3110 (~0x8 bytes). */
static int randomtrade_3108(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3118 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x3118, body spans 0x3118..0x3210 (~0xf8 bytes). */
static int randomtrade_3118(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x710, 0x710, 0x718, 0x720, 0x188, 0x728, 0x730, 0x738, ... (10 total) */
    /* Field offsets touched: +0x04, +0x74, +0x94, +0x98, +0xa4, +0x12c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x321c, body spans 0x321c..0x32b0 (~0x94 bytes). */
static int randomtrade_321c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x748, 0x750, 0x758, 0x750 */
    /* Field offsets touched: +0x04, +0x14, +0x5c, +0x7c, +0x80 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x32b8, body spans 0x32b8..0x32f4 (~0x3c bytes). */
static int randomtrade_32b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x748, 0x760 */
    /* Field offsets touched: +0x04, +0x5c, +0x80 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x32f8, body spans 0x32f8..0x335c (~0x64 bytes). */
static int randomtrade_32f8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x748 */
    /* Field offsets touched: +0x04, +0x5c, +0x7c, +0x80 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x3360, body spans 0x3360..0x3384 (~0x24 bytes). */
static int randomtrade_3360(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x468, 0x768 */
    /* Field offsets touched: +0x04, +0x128 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x3388, body spans 0x3388..0x33a4 (~0x1c bytes). */
static int randomtrade_3388(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x468 */
    /* Field offsets touched: +0x04, +0x128 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x33ac, body spans 0x33ac..0x33ec (~0x40 bytes). */
static int randomtrade_33ac(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x128, +0x129 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x3430, body spans 0x3430..0x3eb8 (~0xa88 bytes). */
static int randomtrade_3430(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x328, 0x780, 0x328, 0x788, 0x790, 0x1ae0, 0x478, 0x480, ... (87 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2a, +0x2c, +0x30, +0x32, +0x33, +0x34, +0x38, +0x5c, +0x78, +0xa2, +0xdb, +0xdc, +0xe0, +0xe4, +0xe8, +0x124, +0x12a, +0x12b, +0x136, +0x374, +0x375, +0x3ac, +0x3ad, +0x75c, +0x764, +0x78c, +0x790, +0x794, +0x798, +0x79c, +0x888, +0x88c, +0x890, +0x891 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x3ed8, body spans 0x3ed8..0x4084 (~0x1ac bytes). */
static int randomtrade_3ed8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x218, 0x7f0, 0x7f8, 0x800, 0x808, 0x810, 0x818, 0x818, ... (17 total) */
    /* Field offsets touched: +0x0c, +0x10, +0x14, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3ac, +0x3ad, +0x75c, +0x78c, +0x7a0 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x4088, body spans 0x4088..0x4094 (~0xc bytes). */
static int randomtrade_4088(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x40b8, body spans 0x40b8..0x40cc (~0x14 bytes). */
static int randomtrade_40b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0x75c */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x40d4, body spans 0x40d4..0x4200 (~0x12c bytes). */
static int randomtrade_40d4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x850, 0x858, 0x860, 0x468, 0x868, 0x420, 0x198, 0x198, ... (11 total) */
    /* Field offsets touched: +0x04, +0x14, +0x1c, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x760, +0x764, +0x768, +0x78c, +0x794, +0x7a0, +0x888, +0x890 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x4210, body spans 0x4210..0x4218 (~0x8 bytes). */
static int randomtrade_4210(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4220 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x4220, body spans 0x4220..0x4330 (~0x110 bytes). */
static int randomtrade_4220(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x468, 0x878, 0x880, 0x888, 0x180 */
    /* Field offsets touched: +0x04, +0x08, +0x14, +0x28, +0x2c, +0x30, +0x76c, +0x770, +0x78c, +0x794 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x434c, body spans 0x434c..0x43ec (~0xa0 bytes). */
static int randomtrade_434c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x08 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* CRO 0x4434, body spans 0x4434..0x44b0 (~0x7c bytes). */
static int randomtrade_4434(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllRandomTrade.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x42ac (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x42ac..; BL targets: 0x180, 0x468, 0x878 */
    /* TODO: not yet decoded */
    return 1;
}

/* CRO 0x41bc (segment 0) — _ZN9xy_system2bg6System13SetIsCallDrawEb */
int _ZN9xy_system2bg6System13SetIsCallDrawEb(ModuleActor *self) {
    (void)self;
    /* Body spans 0x41bc..; BL targets: 0x870 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 49 candidate function boundaries (push/pop pairing).
 * Total BL sites: 505 (to imports: 477, internal: 28).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */