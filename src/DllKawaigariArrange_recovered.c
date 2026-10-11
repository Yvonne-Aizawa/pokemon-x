/*
 * Preliminary decompilation of DllKawaigariArrange.cro.
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

/* Module summary (from DllKawaigariArrange.cro header):
 *   file size: 0xb000
 *   code:      offset 0x180  size 0x8e80
 *   data:      offset 0xa310  size 0x14
 *   bss:       size  0x20
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 161
 *   import veneers (ldr pc,[pc,#N]): 153 at 0x180..0x640
 *   total BL sites: 771 (to imports: 604, internal: 167)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 383x)
 *   +0x0c (hit 265x)
 *   +0x10 (hit 92x)
 *   +0x34 (hit 90x)
 *   +0x28 (hit 90x)
 *   +0x14 (hit 71x)
 *   +0x2c (hit 69x)
 *   +0x18 (hit 66x)
 *   +0x30 (hit 54x)
 *   +0x42 (hit 44x)
 *   +0x40 (hit 42x)
 *   +0x08 (hit 36x)
 *   +0x116 (hit 25x)
 *   +0x20 (hit 24x)
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

/* Index: 83 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x0648..0x07b4  BL(local=4, imp=11)
 *   CRO 0x07bc..0x0958  BL(local=5, imp=12)
 *   CRO 0x0964..0x097c  BL(local=0, imp=1)
 *   CRO 0x0980..0x0c7c  BL(local=13, imp=5)
 *   CRO 0x0c88..0x1200  BL(local=6, imp=24)
 *   CRO 0x1210..0x13a8  BL(local=5, imp=12)
 *   CRO 0x13b0..0x152c  BL(local=0, imp=16)
 *   CRO 0x1534..0x16ec  BL(local=6, imp=12)
 *   CRO 0x16f8..0x17b0  BL(local=1, imp=5)
 *   CRO 0x17b8..0x18c8  BL(local=2, imp=10)
 *   CRO 0x18cc..0x1998  BL(local=1, imp=4)
 *   CRO 0x19a0..0x1ab0  BL(local=6, imp=0)
 *   CRO 0x1ab4..0x1bac  BL(local=1, imp=4)
 *   CRO 0x1bb8..0x1d30  BL(local=1, imp=12)
 *   CRO 0x1d3c..0x1df4  BL(local=1, imp=5)
 *   CRO 0x1dfc..0x1f2c  BL(local=1, imp=5)
 *   CRO 0x1f3c..0x24d0  BL(local=11, imp=36)
 *   CRO 0x24d4..0x2590  BL(local=1, imp=3)
 *   CRO 0x259c..0x2634  BL(local=0, imp=2)
 *   CRO 0x263c..0x272c  BL(local=0, imp=6)
 *   CRO 0x2730..0x2c64  BL(local=13, imp=30)
 *   CRO 0x2c70..0x2d74  BL(local=0, imp=8)
 *   CRO 0x2d84..0x2e3c  BL(local=0, imp=4)
 *   CRO 0x2e9c..0x2f6c  BL(local=0, imp=1)
 *   CRO 0x2f70..0x30e4  BL(local=0, imp=18)
 *   CRO 0x30e8..0x3368  BL(local=4, imp=15)
 *   CRO 0x3374..0x33a8  BL(local=0, imp=1)
 *   CRO 0x33ac..0x33f0  BL(local=2, imp=0)
 *   CRO 0x3408..0x3758  BL(local=7, imp=21)
 *   CRO 0x3768..0x3924  BL(local=2, imp=11)
 *   CRO 0x3930..0x3a60  BL(local=2, imp=8)
 *   CRO 0x3a64..0x3af0  BL(local=2, imp=0)
 *   CRO 0x3afc..0x3bd8  BL(local=1, imp=7)
 *   CRO 0x3bfc..0x3ca0  BL(local=0, imp=3)
 *   CRO 0x3ca4..0x3ddc  BL(local=1, imp=3)
 *   CRO 0x3de0..0x3f5c  BL(local=2, imp=5)
 *   CRO 0x3f70..0x4084  BL(local=1, imp=2)
 *   CRO 0x40a0..0x438c  BL(local=2, imp=15)
 *   CRO 0x43c8..0x4468  BL(local=0, imp=5)
 *   CRO 0x4480..0x465c  BL(local=6, imp=5)
 *   CRO 0x4668..0x4704  BL(local=0, imp=1)
 *   CRO 0x470c..0x4988  BL(local=0, imp=6)
 *   CRO 0x4998..0x49d4  BL(local=0, imp=1)
 *   CRO 0x4a04..0x4b5c  BL(local=1, imp=5)
 *   CRO 0x4b60..0x4d44  BL(local=1, imp=9)
 *   CRO 0x4d8c..0x4e10  BL(local=1, imp=2)
 *   CRO 0x4e74..0x4f54  BL(local=1, imp=3)
 *   CRO 0x4f68..0x5048  BL(local=0, imp=5)
 *   CRO 0x50a8..0x5180  BL(local=0, imp=3)
 *   CRO 0x5200..0x5340  BL(local=0, imp=12)
 *   CRO 0x5348..0x54e8  BL(local=12, imp=2)
 *   CRO 0x54ec..0x5604  BL(local=1, imp=6)
 *   CRO 0x5608..0x5800  BL(local=7, imp=4)
 *   CRO 0x5814..0x58e4  BL(local=0, imp=4)
 *   CRO 0x58f0..0x5bf4  BL(local=6, imp=20)
 *   CRO 0x5c00..0x5d64  BL(local=1, imp=15)
 *   CRO 0x5d68..0x5eb0  BL(local=0, imp=3)
 *   CRO 0x5eb8..0x6128  BL(local=1, imp=9)
 *   CRO 0x6168..0x6244  BL(local=0, imp=6)
 *   CRO 0x6258..0x62f8  BL(local=0, imp=5)
 *   CRO 0x6300..0x643c  BL(local=1, imp=4)
 *   CRO 0x6450..0x6580  BL(local=0, imp=11)
 *   CRO 0x658c..0x6690  BL(local=0, imp=7)
 *   CRO 0x66ac..0x6774  BL(local=0, imp=7)
 *   CRO 0x6778..0x6984  BL(local=4, imp=5)
 *   CRO 0x69e0..0x6aa0  BL(local=1, imp=4)
 *   CRO 0x6ab4..0x6c34  BL(local=2, imp=14)
 *   CRO 0x6c3c..0x6ebc  BL(local=6, imp=5)
 *   CRO 0x6f70..0x70bc  BL(local=1, imp=11)
 *   CRO 0x70cc..0x7164  BL(local=1, imp=0)
 *   CRO 0x7168..0x7294  BL(local=0, imp=14)
 *   CRO 0x72b0..0x74e4  BL(local=2, imp=21)
 *   CRO 0x74f4..0x75dc  BL(local=0, imp=5)
 *   CRO 0x75e0..0x76c0  BL(local=0, imp=4)
 *   CRO 0x76cc..0x7734  BL(local=0, imp=0)
 *   CRO 0x7744..0x7798  BL(local=0, imp=2)
 *   CRO 0x779c..0x77f0  BL(local=0, imp=2)
 *   CRO 0x77f4..0x7868  BL(local=0, imp=5) [contains export: nnroControlObject_]
 *   CRO 0x7874..0x78cc  BL(local=0, imp=4)
 *   CRO 0x78dc..0x7934  BL(local=0, imp=4)
 *   CRO 0x7944..0x7970  BL(local=0, imp=1)
 *   CRO 0x797c..0x79a8  BL(local=0, imp=1)
 *   CRO 0x79ec..0x7a68  BL(local=0, imp=0)
 */

/* CRO 0x648, body spans 0x648..0x7b4 (~0x16c bytes). */
static int kawaigariarrange_648(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5198, 0x50a8, 0x5050, 0x4f68, 0x180, 0x180, 0x188, 0x188, ... (15 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x28, +0x34, +0x36 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x7bc, body spans 0x7bc..0x958 (~0x19c bytes). */
static int kawaigariarrange_7bc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5198, 0x4e74, 0x5050, 0x4f68, 0x180, 0x180, 0x188, 0x188, ... (17 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x28, +0x2c, +0x33, +0x34, +0x36 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x964, body spans 0x964..0x97c (~0x18 bytes). */
static int kawaigariarrange_964(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a8 */
    /* Field offsets touched: +0x30 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x980, body spans 0x980..0xc7c (~0x2fc bytes). */
static int kawaigariarrange_980(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x13b0, 0x3768, 0x1b0, 0x72b0, 0x4d8c, 0x4b60, 0x4a04, 0x4b60, ... (18 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x24, +0x25, +0x26, +0x28, +0x2c, +0x30, +0x34, +0x3f, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0xc88, body spans 0xc88..0x1200 (~0x578 bytes). */
static int kawaigariarrange_c88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d0, 0x1d8, 0x1e0, 0x1e8, 0x1e8, 0x1f0, 0x1f8, 0x470c, ... (30 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x1e, +0x20, +0x24, +0x2c, +0x30, +0x34, +0x39, +0x3b, +0x3d, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1210, body spans 0x1210..0x13a8 (~0x198 bytes). */
static int kawaigariarrange_1210(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5198, 0x50a8, 0x5050, 0x4f68, 0x180, 0x180, 0x188, 0x188, ... (17 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x28, +0x2a, +0x33, +0x34, +0x36 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x13b0, body spans 0x13b0..0x152c (~0x17c bytes). */
static int kawaigariarrange_13b0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x258, 0x260, 0x268, 0x270, 0x278, 0x260, 0x288, 0x260, ... (16 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x20, +0x2c, +0x34, +0x3c, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1534, body spans 0x1534..0x16ec (~0x1b8 bytes). */
static int kawaigariarrange_1534(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5198, 0x4e18, 0x1a0, 0x4e74, 0x5050, 0x4f68, 0x180, 0x180, ... (18 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x28, +0x2a, +0x2c, +0x33, +0x34, +0x36 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x16f8, body spans 0x16f8..0x17b0 (~0xb8 bytes). */
static int kawaigariarrange_16f8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x50a8, 0x2b8, 0x2b8, 0x188, 0x188, 0x198 */
    /* Field offsets touched: +0x04, +0x0c, +0x28, +0x2a, +0x34, +0x36 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x17b8, body spans 0x17b8..0x18c8 (~0x110 bytes). */
static int kawaigariarrange_17b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2c0, 0x470c, 0x2c8, 0x2f70, 0x2d8, 0x2d0, 0x2e0, 0x2e8, ... (12 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x20, +0x2c, +0x34, +0x3c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x18cc, body spans 0x18cc..0x1998 (~0xcc bytes). */
static int kawaigariarrange_18cc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4994, 0x2f8, 0x188, 0x188, 0x180 */
    /* Field offsets touched: +0x04, +0x0c, +0x2c, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x19a0, body spans 0x19a0..0x1ab0 (~0x110 bytes). */
static int kawaigariarrange_19a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x40a0, 0x3f70, 0x40a0, 0x3f70, 0x40a0, 0x3f70 */
    /* Field offsets touched: +0x0c, +0x10, +0x2c, +0x34, +0x3b, +0x3c, +0x3e, +0x3f, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1ab4, body spans 0x1ab4..0x1bac (~0xf8 bytes). */
static int kawaigariarrange_1ab4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x75e0, 0x308, 0x310, 0x190 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x34, +0x3b */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1bb8, body spans 0x1bb8..0x1d30 (~0x178 bytes). */
static int kawaigariarrange_1bb8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x318, 0x198, 0x300, 0x320, 0x328, 0x6168, 0x2b8, 0x2b8, ... (13 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x18, +0x20, +0x28, +0x2c, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1d3c, body spans 0x1d3c..0x1df4 (~0xb8 bytes). */
static int kawaigariarrange_1d3c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4e74, 0x2b8, 0x2b8, 0x188, 0x188, 0x198 */
    /* Field offsets touched: +0x04, +0x0c, +0x28, +0x2a, +0x34, +0x36 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1dfc, body spans 0x1dfc..0x1f2c (~0x130 bytes). */
static int kawaigariarrange_1dfc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x248, 0x3a64, 0x248, 0x1b8, 0x1b8, 0x190 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x2c, +0x34, +0x3b, +0x3c, +0x3d, +0x3f, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x1f3c, body spans 0x1f3c..0x24d0 (~0x594 bytes). */
static int kawaigariarrange_1f3c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8, 0x2b8, 0x188, 0x188, 0x348, 0x1f8, 0x50a8, 0x66ac, ... (47 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x20, +0x22, +0x28, +0x2a, +0x30, +0x32, +0x33, +0x34, +0x3b */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x24d4, body spans 0x24d4..0x2590 (~0xbc bytes). */
static int kawaigariarrange_24d4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x19a0, 0x1b8, 0x1b8, 0x310 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x34, +0x3d, +0x3e, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x259c, body spans 0x259c..0x2634 (~0x98 bytes). */
static int kawaigariarrange_259c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x248, 0x248 */
    /* Field offsets touched: +0x0c, +0x14, +0x31, +0x34, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x263c, body spans 0x263c..0x272c (~0xf0 bytes). */
static int kawaigariarrange_263c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8, 0x218, 0x1b0, 0x1b0, 0x220, 0x228 */
    /* Field offsets touched: +0x04, +0x0c, +0x14, +0x18, +0x1c, +0x1e, +0x2c, +0x30, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x2730, body spans 0x2730..0x2c64 (~0x534 bytes). */
static int kawaigariarrange_2730(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8, 0x2b8, 0x188, 0x188, 0x348, 0x1f8, 0x4e74, 0x66ac, ... (43 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x28, +0x2a, +0x2c, +0x30, +0x32, +0x33, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x2c70, body spans 0x2c70..0x2d74 (~0x104 bytes). */
static int kawaigariarrange_2c70(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x398, 0x398, 0x1b8, 0x1b8, 0x260, 0x3a0, 0x3a8, 0x3b0 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x34, +0x38, +0x3c, +0x40 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x2d84, body spans 0x2d84..0x2e3c (~0xb8 bytes). */
static int kawaigariarrange_2d84(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f0, 0x1f8, 0x1d8, 0x3b8 */
    /* Field offsets touched: +0x0c, +0x10, +0x14, +0x18, +0x28, +0x2a, +0x2c, +0x2e, +0x30, +0x32, +0x33, +0x34, +0x3b, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x2e9c, body spans 0x2e9c..0x2f6c (~0xd0 bytes). */
static int kawaigariarrange_2e9c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c0 */
    /* Field offsets touched: +0x10, +0x40, +0x42, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x2f70, body spans 0x2f70..0x30e4 (~0x174 bytes). */
static int kawaigariarrange_2f70(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c8, 0x2d0, 0x3c8, 0x2d0, 0x3c8, 0x2d0, 0x3d0, 0x3d8, ... (18 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x2c, +0x34, +0x124 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x30e8, body spans 0x30e8..0x3368 (~0x280 bytes). */
static int kawaigariarrange_30e8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x1f8, 0x200, 0x198, 0x6258, 0x2f8, 0x430, 0x180, ... (19 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x28, +0x2a, +0x30, +0x32, +0x34, +0x36, +0x39 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3374, body spans 0x3374..0x33a8 (~0x34 bytes). */
static int kawaigariarrange_3374(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8 */
    /* Field offsets touched: +0x04, +0x0c, +0x28, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x33ac, body spans 0x33ac..0x33f0 (~0x44 bytes). */
static int kawaigariarrange_33ac(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6778, 0x6300 */
    /* Field offsets touched: +0x0c, +0x2c, +0x34, +0x3b */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3408, body spans 0x3408..0x3758 (~0x350 bytes). */
static int kawaigariarrange_3408(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x1f8, 0x4e18, 0x200, 0x198, 0x2f8, 0x4e18, 0x2f8, ... (28 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0a, +0x0c, +0x10, +0x14, +0x18, +0x28, +0x2a, +0x2c, +0x30, +0x32, +0x34, +0x36, +0x39, +0x3a */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3768, body spans 0x3768..0x3924 (~0x1bc bytes). */
static int kawaigariarrange_3768(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5c00, 0x260, 0x448, 0x260, 0x448, 0x260, 0x448, 0x5d68, ... (13 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x28, +0x3c, +0x3e, +0x40, +0x124 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3930, body spans 0x3930..0x3a60 (~0x130 bytes). */
static int kawaigariarrange_3930(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5198, 0x180, 0x180, 0x190, 0x190, 0x2b8, 0x2b8, 0x188, ... (10 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x28, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3a64, body spans 0x3a64..0x3af0 (~0x8c bytes). */
static int kawaigariarrange_3a64(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3afc, 0x3afc */
    /* Field offsets touched: +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3afc, body spans 0x3afc..0x3bd8 (~0xdc bytes). */
static int kawaigariarrange_3afc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4994, 0x1b8, 0x250, 0x300, 0x320, 0x480, 0x1b8, 0x488 */
    /* Field offsets touched: +0x04, +0x2c, +0x124 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3bfc, body spans 0x3bfc..0x3ca0 (~0xa4 bytes). */
static int kawaigariarrange_3bfc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x230, 0x238, 0x240 */
    /* Field offsets touched: +0x0c, +0x10, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3ca4, body spans 0x3ca4..0x3ddc (~0x138 bytes). */
static int kawaigariarrange_3ca4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4994, 0x3c0, 0x490, 0x340 */
    /* Field offsets touched: +0x04, +0x2c, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3de0, body spans 0x3de0..0x3f5c (~0x17c bytes). */
static int kawaigariarrange_3de0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x470c, 0x498, 0x430, 0x430, 0x4e18, 0x430, 0x2f8 */
    /* Field offsets touched: +0x04, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x3f70, body spans 0x3f70..0x4084 (~0x114 bytes). */
static int kawaigariarrange_3f70(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4994, 0x3c0, 0x488 */
    /* Field offsets touched: +0x04, +0x2c, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x40a0, body spans 0x40a0..0x438c (~0x2ec bytes). */
static int kawaigariarrange_40a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x380, 0x4994, 0x4a0, 0x300, 0x320, 0x328, 0x4994, 0x3c0, ... (17 total) */
    /* Field offsets touched: +0x04, +0x14, +0x2c, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x43c8, body spans 0x43c8..0x4468 (~0xa0 bytes). */
static int kawaigariarrange_43c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x330, 0x4a8, 0x4b0, 0x338, 0x4b0 */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4480, body spans 0x4480..0x465c (~0x1dc bytes). */
static int kawaigariarrange_4480(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x248, 0x1b8, 0x3ca4, 0x3f70, 0x3ca4, 0x3f70, 0x3ca4, 0x3f70, ... (11 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x28, +0x34, +0x3b, +0x3e, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4668, body spans 0x4668..0x4704 (~0x9c bytes). */
static int kawaigariarrange_4668(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b8 */
    /* Field offsets touched: +0x04, +0x0c, +0x24, +0x25, +0x26, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x470c, body spans 0x470c..0x4988 (~0x27c bytes). */
static int kawaigariarrange_470c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4c0, 0x498, 0x430, 0x370, 0x370, 0x370 */
    /* Field offsets touched: +0x04, +0x08, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4998, body spans 0x4998..0x49d4 (~0x3c bytes). */
static int kawaigariarrange_4998(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x380 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4a04, body spans 0x4a04..0x4b5c (~0x158 bytes). */
static int kawaigariarrange_4a04(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x380, 0x4994, 0x318, 0x300, 0x320, 0x328 */
    /* Field offsets touched: +0x04, +0x14, +0x20, +0x2c, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4b60, body spans 0x4b60..0x4d44 (~0x1e4 bytes). */
static int kawaigariarrange_4b60(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x380, 0x4994, 0x4c8, 0x238, 0x1b8, 0x1b8, 0x3c0, 0x488, ... (10 total) */
    /* Field offsets touched: +0x04, +0x14, +0x20, +0x2c, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4d8c, body spans 0x4d8c..0x4e10 (~0x84 bytes). */
static int kawaigariarrange_4d8c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x75e0, 0x4d0 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4e74, body spans 0x4e74..0x4f54 (~0xe0 bytes). */
static int kawaigariarrange_4e74(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4e18, 0x350, 0x350, 0x1b8 */
    /* Field offsets touched: +0x04, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x4f68, body spans 0x4f68..0x5048 (~0xe0 bytes). */
static int kawaigariarrange_4f68(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x1b8, 0x1b8, 0x4e0, 0x1b8 */
    /* Field offsets touched: +0x04, +0x08 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x50a8, body spans 0x50a8..0x5180 (~0xd8 bytes). */
static int kawaigariarrange_50a8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x350, 0x1b8 */
    /* Field offsets touched: +0x04, +0x30 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5200, body spans 0x5200..0x5340 (~0x140 bytes). */
static int kawaigariarrange_5200(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x470, 0x1b8, 0x1b8, 0x478, 0x2d0, 0x1b8, 0x1b8, 0x478, ... (12 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x14, +0x18, +0x1c, +0x1e, +0x2c, +0x30, +0x34, +0x40 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5348, body spans 0x5348..0x54e8 (~0x1a0 bytes). */
static int kawaigariarrange_5348(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x1f8, 0x259c, 0x6f70, 0x1210, 0x259c, 0x6f70, 0x648, ... (14 total) */
    /* Field offsets touched: +0x0c, +0x10, +0x14, +0x28, +0x2a, +0x2c, +0x2e, +0x30, +0x31, +0x33, +0x34, +0x3b */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x54ec, body spans 0x54ec..0x5604 (~0x118 bytes). */
static int kawaigariarrange_54ec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x2b8, 0x188, 0x180, 0x2b8, 0x188, 0x1ab4 */
    /* Field offsets touched: +0x04, +0x0c, +0x28, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5608, body spans 0x5608..0x5800 (~0x1f8 bytes). */
static int kawaigariarrange_5608(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x74f4, 0x198, 0x180, 0x4668, 0x4668, 0x4668, 0x198, 0x4668, ... (11 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x24, +0x25, +0x26, +0x28, +0x30, +0x31, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5814, body spans 0x5814..0x58e4 (~0xd0 bytes). */
static int kawaigariarrange_5814(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x1b8, 0x1f0, 0x1b8 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x28, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x58f0, body spans 0x58f0..0x5bf4 (~0x304 bytes). */
static int kawaigariarrange_58f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5198, 0x180, 0x180, 0x190, 0x190, 0x318, 0x198, 0x300, ... (26 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x20, +0x28, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5c00, body spans 0x5c00..0x5d64 (~0x164 bytes). */
static int kawaigariarrange_5c00(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x260, 0x4f0, 0x4f8, 0x500, 0x508, 0x510, 0x518, 0x520, ... (16 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5d68, body spans 0x5d68..0x5eb0 (~0x148 bytes). */
static int kawaigariarrange_5d68(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x550, 0x4e0, 0x380 */
    /* Field offsets touched: +0x08, +0x22, +0x42, +0x116, +0x117, +0x11a, +0x11e */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x5eb8, body spans 0x5eb8..0x6128 (~0x270 bytes). */
static int kawaigariarrange_5eb8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4e18, 0x430, 0x1a0, 0x4e0, 0x200, 0x200, 0x430, 0x370, ... (10 total) */
    /* Field offsets touched: +0x04, +0x08, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6168, body spans 0x6168..0x6244 (~0xdc bytes). */
static int kawaigariarrange_6168(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x430, 0x180, 0x430, 0x180, 0x350 */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6258, body spans 0x6258..0x62f8 (~0xa0 bytes). */
static int kawaigariarrange_6258(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x320, 0x480, 0x440, 0x2f8 */
    /* Field offsets touched: +0x04, +0x08, +0x0a, +0x28, +0x124 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6300, body spans 0x6300..0x643c (~0x13c bytes). */
static int kawaigariarrange_6300(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4994, 0x4a0, 0x2f8, 0x4a0, 0x350 */
    /* Field offsets touched: +0x04, +0x2c, +0x30, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6450, body spans 0x6450..0x6580 (~0x130 bytes). */
static int kawaigariarrange_6450(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b0, 0x300, 0x320, 0x480, 0x558, 0x560, 0x488, 0x488, ... (11 total) */
    /* Field offsets touched: +0x04, +0x30, +0x124 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x658c, body spans 0x658c..0x6690 (~0x104 bytes). */
static int kawaigariarrange_658c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x430, 0x350, 0x2f8, 0x2f8, 0x350, 0x1b8, 0x1b8 */
    /* Field offsets touched: +0x04, +0x30 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x66ac, body spans 0x66ac..0x6774 (~0xc8 bytes). */
static int kawaigariarrange_66ac(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x2b8, 0x188, 0x180, 0x2b8, 0x188, 0x180 */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6778, body spans 0x6778..0x6984 (~0x20c bytes). */
static int kawaigariarrange_6778(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3afc, 0x2b8, 0x3afc, 0x568, 0x4994, 0x4a0, 0x4994, 0x4a0, ... (9 total) */
    /* Field offsets touched: +0x04, +0x2c, +0x34, +0x38, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x69e0, body spans 0x69e0..0x6aa0 (~0xc0 bytes). */
static int kawaigariarrange_69e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4e18, 0x2f8, 0x380, 0x350, 0x1b8 */
    /* Field offsets touched: +0x04, +0x08, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6ab4, body spans 0x6ab4..0x6c34 (~0x180 bytes). */
static int kawaigariarrange_6ab4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2f8, 0x4e18, 0x2f8, 0x4e18, 0x300, 0x320, 0x570, 0x300, ... (16 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0a, +0x10, +0x28, +0x2c, +0x30 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6c3c, body spans 0x6c3c..0x6ebc (~0x280 bytes). */
static int kawaigariarrange_6c3c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4a04, 0x2b8, 0x4a04, 0x568, 0x4994, 0x4a0, 0x4994, 0x4b60, ... (11 total) */
    /* Field offsets touched: +0x04, +0x2c, +0x34, +0x38, +0x40, +0x42 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x6f70, body spans 0x6f70..0x70bc (~0x14c bytes). */
static int kawaigariarrange_6f70(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x210, 0x250, 0x300, 0x320, 0x480, 0x488, 0x560, 0x1b8, ... (12 total) */
    /* Field offsets touched: +0x04, +0x30, +0x3c, +0x124 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x70cc, body spans 0x70cc..0x7164 (~0x98 bytes). */
static int kawaigariarrange_70cc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6ab4 */
    /* Field offsets touched: +0x04, +0x2c, +0x40, +0x116 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x7168, body spans 0x7168..0x7294 (~0x12c bytes). */
static int kawaigariarrange_7168(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x260, 0x590, 0x598, 0x5a0, 0x5a8, 0x5b0, 0x5b8, 0x5c0, ... (14 total) */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x72b0, body spans 0x72b0..0x74e4 (~0x234 bytes). */
static int kawaigariarrange_72b0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b0, 0x300, 0x320, 0x570, 0x330, 0x338, 0x340, 0x370, ... (23 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0a, +0x0c, +0x10, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x74f4, body spans 0x74f4..0x75dc (~0xe8 bytes). */
static int kawaigariarrange_74f4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d0, 0x1d8, 0x1e0, 0x1e8, 0x1e8 */
    /* Field offsets touched: +0x10, +0x18 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x75e0, body spans 0x75e0..0x76c0 (~0xe0 bytes). */
static int kawaigariarrange_75e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x260, 0x5f8, 0x308, 0x4d8 */
    /* Field offsets touched: +0x04, +0x08, +0x18, +0x1c */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x76cc, body spans 0x76cc..0x7734 (~0x68 bytes). */
static int kawaigariarrange_76cc(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x0c, +0x24, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x7744, body spans 0x7744..0x7798 (~0x54 bytes). */
static int kawaigariarrange_7744(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x608, 0x608 */
    /* Field offsets touched: +0x04, +0x0c, +0x24, +0x34, +0x40 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x779c, body spans 0x779c..0x77f0 (~0x54 bytes). */
static int kawaigariarrange_779c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x618, 0x620 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x24, +0x1dc */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x77f4, body spans 0x77f4..0x7868 (~0x74 bytes). */
static int kawaigariarrange_77f4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x628, 0x270, 0x278, 0x260, 0x630 */
    /* Field offsets touched: +0x20, +0x22, +0x24, +0x34 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x7874, body spans 0x7874..0x78cc (~0x58 bytes). */
static int kawaigariarrange_7874(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x638, 0x2d0, 0x2d8, 0x640 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x78dc, body spans 0x78dc..0x7934 (~0x58 bytes). */
static int kawaigariarrange_78dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x638, 0x2d0, 0x2d8, 0x640 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x7944, body spans 0x7944..0x7970 (~0x2c bytes). */
static int kawaigariarrange_7944(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x640 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x797c, body spans 0x797c..0x79a8 (~0x2c bytes). */
static int kawaigariarrange_797c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x640 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* CRO 0x79ec, body spans 0x79ec..0x7a68 (~0x7c bytes). */
static int kawaigariarrange_79ec(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllKawaigariArrange.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x7864 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x7864..; BL targets: 0x638, 0x2d0, 0x2d8 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 83 candidate function boundaries (push/pop pairing).
 * Total BL sites: 771 (to imports: 604, internal: 167).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */