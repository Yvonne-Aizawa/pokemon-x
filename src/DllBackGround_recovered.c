/*
 * Preliminary decompilation of DllBackGround.cro.
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

/* Module summary (from DllBackGround.cro header):
 *   file size: 0x8000
 *   code:      offset 0x180  size 0x6e80
 *   data:      offset 0x7da0  size 0xbc
 *   bss:       size  0x20
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 108
 *   import veneers (ldr pc,[pc,#N]): 107 at 0x180..0x4d0
 *   total BL sites: 298 (to imports: 280, internal: 18)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 104x)
 *   +0x18 (hit 67x)
 *   +0x0c (hit 58x)
 *   +0x150 (hit 51x)
 *   +0x08 (hit 39x)
 *   +0x6c (hit 38x)
 *   +0x30 (hit 37x)
 *   +0x60 (hit 22x)
 *   +0x10 (hit 21x)
 *   +0x48 (hit 19x)
 *   +0x154 (hit 18x)
 *   +0x239 (hit 17x)
 *   +0xdc (hit 17x)
 *   +0x90 (hit 17x)
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

/* Index: 36 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x0508..0x0608  BL(local=0, imp=0)
 *   CRO 0x060c..0x0670  BL(local=0, imp=3)
 *   CRO 0x0678..0x06b8  BL(local=0, imp=1)
 *   CRO 0x06dc..0x06f4  BL(local=0, imp=1)
 *   CRO 0x06f8..0x073c  BL(local=0, imp=2)
 *   CRO 0x0740..0x0830  BL(local=0, imp=2)
 *   CRO 0x0834..0x08f0  BL(local=0, imp=4)
 *   CRO 0x08f4..0x0f84  BL(local=0, imp=16)
 *   CRO 0x0f94..0x0ff8  BL(local=0, imp=1)
 *   CRO 0x0ffc..0x1084  BL(local=0, imp=4)
 *   CRO 0x1088..0x1434  BL(local=0, imp=20) [contains export: _ZN9xy_system2bg6System13SetIsCallDrawEb]
 *   CRO 0x14ac..0x1534  BL(local=0, imp=0)
 *   CRO 0x1540..0x1710  BL(local=3, imp=5)
 *   CRO 0x172c..0x1790  BL(local=0, imp=0)
 *   CRO 0x1794..0x1918  BL(local=0, imp=4)
 *   CRO 0x1920..0x19e0  BL(local=0, imp=1)
 *   CRO 0x19e8..0x1a44  BL(local=0, imp=3)
 *   CRO 0x1a4c..0x1a88  BL(local=0, imp=1)
 *   CRO 0x1a8c..0x1b28  BL(local=0, imp=0)
 *   CRO 0x1b2c..0x1cb4  BL(local=0, imp=0)
 *   CRO 0x1ce8..0x1d0c  BL(local=0, imp=1)
 *   CRO 0x1d10..0x1d58  BL(local=0, imp=2)
 *   CRO 0x1d5c..0x1d84  BL(local=1, imp=0)
 *   CRO 0x1d88..0x1f90  BL(local=0, imp=1)
 *   CRO 0x1f98..0x3150  BL(local=4, imp=98)
 *   CRO 0x316c..0x3214  BL(local=0, imp=2)
 *   CRO 0x3320..0x3454  BL(local=0, imp=3)
 *   CRO 0x3458..0x37d4  BL(local=1, imp=11)
 *   CRO 0x37d8..0x40f8  BL(local=3, imp=62)
 *   CRO 0x4108..0x42a4  BL(local=0, imp=20)
 *   CRO 0x42a8..0x4338  BL(local=0, imp=0)
 *   CRO 0x4340..0x44f0  BL(local=6, imp=0) [contains export: nnroControlObject_]
 *   CRO 0x4508..0x4528  BL(local=0, imp=3)
 *   CRO 0x4534..0x4550  BL(local=0, imp=3)
 *   CRO 0x4564..0x4584  BL(local=0, imp=3)
 *   CRO 0x45c0..0x463c  BL(local=0, imp=0)
 */

/* CRO 0x508, body spans 0x508..0x608 (~0x100 bytes). */
static int background_508(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x01, +0x30, +0x40, +0x48, +0x58, +0x60, +0x6c, +0xd7, +0xda, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x60c, body spans 0x60c..0x670 (~0x64 bytes). */
static int background_60c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188, 0x188, 0x190 */
    /* Field offsets touched: +0x08, +0x10, +0xc4, +0xda, +0xf4, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x678, body spans 0x678..0x6b8 (~0x40 bytes). */
static int background_678(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190 */
    /* Field offsets touched: +0x10, +0x18, +0xda, +0xdc, +0xf4, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x6dc, body spans 0x6dc..0x6f4 (~0x18 bytes). */
static int background_6dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198 */
    /* Field offsets touched: +0x10, +0x18, +0xec */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x6f8, body spans 0x6f8..0x73c (~0x44 bytes). */
static int background_6f8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188, 0x198 */
    /* Field offsets touched: +0x10, +0x18, +0xd9, +0xda, +0xec, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x740, body spans 0x740..0x830 (~0xf0 bytes). */
static int background_740(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a0, 0x1a0 */
    /* Field offsets touched: +0x04, +0x0c, +0x20, +0x140, +0x144 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x834, body spans 0x834..0x8f0 (~0xbc bytes). */
static int background_834(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b0, 0x1b8, 0x1b8, 0x1c0 */
    /* Field offsets touched: +0x18, +0x30, +0x58, +0x60, +0x6c, +0x8c, +0x9c, +0xda, +0xdc, +0x100, +0x104, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x8f4, body spans 0x8f4..0xf84 (~0x690 bytes). */
static int background_8f4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c8, 0x1c8, 0x1d0, 0x1c8, 0x1c8, 0x1c8, 0x1c8, 0x1c8, ... (16 total) */
    /* Field offsets touched: +0x48, +0xd8, +0x150, +0x154, +0x158, +0x164 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0xf94, body spans 0xf94..0xff8 (~0x64 bytes). */
static int background_f94(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f0 */
    /* Field offsets touched: +0x20, +0x204, +0x208, +0x238 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0xffc, body spans 0xffc..0x1084 (~0x88 bytes). */
static int background_ffc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8, 0x1f8, 0x1f8, 0x1f8 */
    /* Field offsets touched: +0x18, +0x30, +0x58, +0x60, +0x6c, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1088, body spans 0x1088..0x1434 (~0x3ac bytes). */
static int background_1088(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x208, 0x210, 0x218, 0x208, 0x228, 0x230, 0x238, 0x240, ... (20 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x18, +0x1c, +0x48, +0xa8, +0xbc, +0xd8, +0xe8, +0x11c, +0x120, +0x124, +0x130, +0x13c, +0x140, +0x144, +0x148, +0x14c, +0x150, +0x154, +0x158, +0x15c, +0x160 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x14ac, body spans 0x14ac..0x1534 (~0x88 bytes). */
static int background_14ac(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x30, +0x58, +0x60, +0xbc, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1540, body spans 0x1540..0x1710 (~0x1d0 bytes). */
static int background_1540(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3320, 0x740, 0x1f0, 0x1f0, 0x1088, 0x1a8, 0x298, 0x2a0 */
    /* Field offsets touched: +0x18, +0x20, +0xd9, +0x11a, +0x138, +0x13c, +0x13d, +0x150, +0x160, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x172c, body spans 0x172c..0x1790 (~0x64 bytes). */
static int background_172c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x6c, +0xb8, +0xd0, +0xd6 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1794, body spans 0x1794..0x1918 (~0x184 bytes). */
static int background_1794(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x2a8, 0x2a8, 0x2a8 */
    /* Field offsets touched: +0x30, +0xe8, +0xe9, +0x165, +0x168, +0x1e8, +0x1e9, +0x200 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1920, body spans 0x1920..0x19e0 (~0xc0 bytes). */
static int background_1920(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x19e8, body spans 0x19e8..0x1a44 (~0x5c bytes). */
static int background_19e8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188, 0x188, 0x2b0 */
    /* Field offsets touched: +0x08, +0x10, +0xd4, +0xda, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1a4c, body spans 0x1a4c..0x1a88 (~0x3c bytes). */
static int background_1a4c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b0 */
    /* Field offsets touched: +0x10, +0x18, +0xda, +0xec, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1a8c, body spans 0x1a8c..0x1b28 (~0x9c bytes). */
static int background_1a8c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x1c, +0x48, +0xd8, +0x13c, +0x150, +0x160 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1b2c, body spans 0x1b2c..0x1cb4 (~0x188 bytes). */
static int background_1b2c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x01, +0x40, +0x48, +0x60, +0x6c, +0xd7, +0x200, +0x201 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1ce8, body spans 0x1ce8..0x1d0c (~0x24 bytes). */
static int background_1ce8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8 */
    /* Field offsets touched: +0x10, +0x18, +0xdc, +0xf4 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1d10, body spans 0x1d10..0x1d58 (~0x48 bytes). */
static int background_1d10(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188, 0x2b8 */
    /* Field offsets touched: +0x10, +0x18, +0xda, +0xdc, +0xf4, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1d5c, body spans 0x1d5c..0x1d84 (~0x28 bytes). */
static int background_1d5c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3458 */
    /* Field offsets touched: +0x20 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1d88, body spans 0x1d88..0x1f90 (~0x208 bytes). */
static int background_1d88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2c8 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40, +0x44, +0x48, +0x4c, +0x50, +0x54, +0x58, +0x5c, +0x5d, +0x5e, +0x60, +0x68, +0x6c, +0x70, +0x74, +0x78, +0x7c, +0x80, +0x84, +0x88, +0x8c, +0x90, +0x94, +0x98, +0x9c, +0xa0, +0xa4, +0xac, +0xad, +0xc8, +0xcc, +0xd0, +0xd4, +0xd5, +0xd6, +0xd7, +0xd8, +0xd9, +0xdc, +0xe0, +0xe4, +0xe8, +0xec, +0xf0, +0xf4, +0xf8, +0xfc, +0x100, +0x104, +0x118, +0x119, +0x11a, +0x138, +0x13c, +0x13d, +0x200, +0x220, +0x224, +0x228, +0x22c, +0x230, +0x234, +0x238, +0x239, +0x240, +0x244, +0x24c */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x1f98, body spans 0x1f98..0x3150 (~0x11b8 bytes). */
static int background_1f98(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x240, 0x208, 0x250, 0x200, 0x208, 0x210, 0x218, 0x2d0, ... (102 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x18, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x44, +0x48, +0x4c, +0x54, +0x58, +0x5c, +0x60, +0x68, +0x6c, +0x70, +0x74, +0x78, +0x7c, +0x80, +0x84, +0x88, +0x8c, +0x90, +0x94, +0x9c, +0xa4, +0xa8, +0xac, +0xbc, +0xd4, +0xd5, +0xd6, +0xd7, +0xd8, +0xe8, +0x100, +0x104, +0x164, +0x165, +0x168, +0x1a8, +0x1e8, +0x1e9, +0x220, +0x224, +0x228, +0x22c, +0x230, +0x234, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x316c, body spans 0x316c..0x3214 (~0xa8 bytes). */
static int background_316c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a0, 0x180 */
    /* Field offsets touched: +0x20, +0x204, +0x208 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x3320, body spans 0x3320..0x3454 (~0x134 bytes). */
static int background_3320(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x390, 0x398, 0x398 */
    /* Field offsets touched: +0x04, +0x140, +0x144, +0x148, +0x14c, +0x150, +0x15c, +0x160 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x3458, body spans 0x3458..0x37d4 (~0x37c bytes). */
static int background_3458(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a8, 0x298, 0x2a0, 0x3320, 0x3a0, 0x3a8, 0x3b0, 0x3b8, ... (12 total) */
    /* Field offsets touched: +0x04, +0x18, +0x2c, +0x30, +0x34, +0x44, +0x54, +0x58, +0x5c, +0x60, +0x68, +0x6c, +0x70, +0x80, +0x90, +0x94, +0x9c, +0xa4, +0xa8, +0xd4, +0xd7, +0xda, +0xdc, +0xe0, +0xe4, +0xec, +0x13c, +0x150, +0x160, +0x220, +0x239, +0x240 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x37d8, body spans 0x37d8..0x40f8 (~0x920 bytes). */
static int background_37d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3d8, 0x3e0, 0x3e8, 0x3f0, 0x3f8, 0x3e0, 0x1f0, 0x400, ... (65 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x18, +0x19, +0x1c, +0x20, +0x30, +0x34, +0x35, +0x39, +0x48, +0x58, +0x5c, +0x60, +0x64, +0x6c, +0x90, +0x9c, +0xa0, +0xa4, +0xac, +0xad, +0xd5, +0xd9, +0xda, +0xdc, +0xe0, +0xe4, +0xe8, +0xec, +0xf8, +0xfc, +0x108, +0x109, +0x10c, +0x164, +0x230, +0x238, +0x23c, +0x240, +0x24c */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x4108, body spans 0x4108..0x42a4 (~0x19c bytes). */
static int background_4108(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x280, 0x1f8, 0x280, 0x1f8, 0x280, 0x1f8, 0x280, 0x1f8, ... (20 total) */
    /* Field offsets touched: +0x18, +0x30, +0x58, +0x60, +0x6c, +0x94, +0x9c, +0xa4, +0xc8, +0xcc, +0xda, +0xdc, +0xf0, +0x239 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x42a8, body spans 0x42a8..0x4338 (~0x90 bytes). */
static int background_42a8(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x6c, +0xbc, +0xd6 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x4340, body spans 0x4340..0x44f0 (~0x1b0 bytes). */
static int background_4340(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x316c, 0x316c, 0x316c, 0x316c, 0x316c, 0x316c */
    /* Field offsets touched: +0x01, +0x03, +0x04, +0x05, +0x0c, +0xd4, +0xd5, +0xda, +0xdc, +0x138, +0x13c, +0x13d, +0x148, +0x14c, +0x150, +0x15c, +0x160, +0x164, +0x204, +0x208, +0x20c, +0x210, +0x214, +0x218, +0x21c, +0x238, +0x23c */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x4508, body spans 0x4508..0x4528 (~0x20 bytes). */
static int background_4508(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b8, 0x4b8, 0x4c0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x4534, body spans 0x4534..0x4550 (~0x1c bytes). */
static int background_4534(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4c8, 0x4d0, 0x4d0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x4564, body spans 0x4564..0x4584 (~0x20 bytes). */
static int background_4564(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4c8, 0x4d0, 0x4d0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* CRO 0x45c0, body spans 0x45c0..0x463c (~0x7c bytes). */
static int background_45c0(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllBackGround.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x4438 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x4438..; BL targets: 0x316c */
    /* TODO: not yet decoded */
    return 1;
}

/* CRO 0x13b8 (segment 0) — _ZN9xy_system2bg6System13SetIsCallDrawEb */
int _ZN9xy_system2bg6System13SetIsCallDrawEb(ModuleActor *self) {
    (void)self;
    /* Body spans 0x13b8..; BL targets: 0x280, 0x1f8, 0x1f8 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 36 candidate function boundaries (push/pop pairing).
 * Total BL sites: 298 (to imports: 280, internal: 18).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */