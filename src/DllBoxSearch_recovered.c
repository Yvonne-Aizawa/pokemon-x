/*
 * Preliminary decompilation of DllBoxSearch.cro.
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

/* Module summary (from DllBoxSearch.cro header):
 *   file size: 0x9000
 *   code:      offset 0x180  size 0x6e80
 *   data:      offset 0x87a8  size 0x2c
 *   bss:       size  0x20
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 161
 *   import veneers (ldr pc,[pc,#N]): 135 at 0x180..0x5b0
 *   total BL sites: 533 (to imports: 478, internal: 55)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 310x)
 *   +0x28 (hit 134x)
 *   +0x14 (hit 40x)
 *   +0x24 (hit 35x)
 *   +0x08 (hit 34x)
 *   +0x0c (hit 33x)
 *   +0x10 (hit 23x)
 *   +0x48 (hit 19x)
 *   +0x30 (hit 19x)
 *   +0xca (hit 18x)
 *   +0x18 (hit 18x)
 *   +0x54 (hit 16x)
 *   +0x5c (hit 16x)
 *   +0x20 (hit 14x)
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

/* Index: 52 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x05b8..0x05d0  BL(local=0, imp=1)
 *   CRO 0x05d4..0x0720  BL(local=1, imp=10)
 *   CRO 0x0734..0x09dc  BL(local=1, imp=1)
 *   CRO 0x09e4..0x0e0c  BL(local=1, imp=39)
 *   CRO 0x0e38..0x0f40  BL(local=1, imp=6)
 *   CRO 0x0f44..0x10c0  BL(local=0, imp=6)
 *   CRO 0x10f0..0x1198  BL(local=1, imp=0)
 *   CRO 0x11a8..0x12a0  BL(local=0, imp=3)
 *   CRO 0x12a4..0x1648  BL(local=3, imp=21)
 *   CRO 0x1660..0x16b4  BL(local=1, imp=0)
 *   CRO 0x16b8..0x18b8  BL(local=2, imp=7)
 *   CRO 0x18dc..0x1a08  BL(local=0, imp=12)
 *   CRO 0x1a18..0x2020  BL(local=1, imp=26)
 *   CRO 0x2034..0x2248  BL(local=7, imp=14)
 *   CRO 0x2254..0x2350  BL(local=1, imp=9)
 *   CRO 0x2364..0x240c  BL(local=0, imp=4)
 *   CRO 0x2418..0x24ac  BL(local=1, imp=1)
 *   CRO 0x25cc..0x26d4  BL(local=0, imp=10)
 *   CRO 0x26e8..0x2bac  BL(local=0, imp=36)
 *   CRO 0x2bd8..0x2dbc  BL(local=0, imp=12)
 *   CRO 0x2dc4..0x2df4  BL(local=0, imp=1)
 *   CRO 0x2dfc..0x3088  BL(local=2, imp=15)
 *   CRO 0x3184..0x3248  BL(local=0, imp=6)
 *   CRO 0x3250..0x3424  BL(local=0, imp=18)
 *   CRO 0x3588..0x3604  BL(local=2, imp=0)
 *   CRO 0x360c..0x36dc  BL(local=2, imp=3)
 *   CRO 0x36e0..0x37a8  BL(local=2, imp=6)
 *   CRO 0x37b4..0x3a10  BL(local=4, imp=16)
 *   CRO 0x3a20..0x3c04  BL(local=0, imp=10)
 *   CRO 0x3c0c..0x3d00  BL(local=0, imp=4)
 *   CRO 0x3d04..0x3e10  BL(local=2, imp=4)
 *   CRO 0x3e24..0x4014  BL(local=3, imp=9)
 *   CRO 0x402c..0x4734  BL(local=8, imp=55)
 *   CRO 0x4744..0x4750  BL(local=0, imp=1)
 *   CRO 0x4764..0x4774  BL(local=0, imp=1)
 *   CRO 0x4780..0x47fc  BL(local=0, imp=1)
 *   CRO 0x4894..0x497c  BL(local=0, imp=9)
 *   CRO 0x4998..0x4a88  BL(local=0, imp=10)
 *   CRO 0x4aa8..0x4d78  BL(local=0, imp=33)
 *   CRO 0x4d9c..0x4e90  BL(local=0, imp=8)
 *   CRO 0x4e94..0x4fa4  BL(local=0, imp=9)
 *   CRO 0x4fa8..0x5024  BL(local=0, imp=2)
 *   CRO 0x5034..0x50cc  BL(local=0, imp=4)
 *   CRO 0x50d0..0x5114  BL(local=0, imp=2)
 *   CRO 0x5118..0x518c  BL(local=0, imp=5)
 *   CRO 0x519c..0x51f4  BL(local=0, imp=2)
 *   CRO 0x5204..0x5258  BL(local=0, imp=2) [contains export: nnroControlObject_]
 *   CRO 0x5278..0x52b0  BL(local=0, imp=2)
 *   CRO 0x52b4..0x52bc  BL(local=0, imp=1)
 *   CRO 0x52fc..0x5328  BL(local=0, imp=1)
 *   CRO 0x5334..0x5360  BL(local=0, imp=1)
 *   CRO 0x53bc..0x5438  BL(local=0, imp=0)
 */

/* CRO 0x5b8, body spans 0x5b8..0x5d0 (~0x18 bytes). */
static int boxsearch_5b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x20 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x5d4, body spans 0x5d4..0x720 (~0x14c bytes). */
static int boxsearch_5d4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188, 0x190, 0x198, 0x198, 0x198, 0x198, 0x198, 0x190, ... (11 total) */
    /* Field offsets touched: +0x04, +0x20, +0x28 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x734, body spans 0x734..0x9dc (~0x2a8 bytes). */
static int boxsearch_734(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b0, 0x3184 */
    /* Field offsets touched: +0x02, +0x04, +0x05, +0x06, +0x07, +0x08, +0x09, +0x0a, +0x0b, +0x28, +0x48, +0x54, +0xc8, +0xc9, +0xca */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x9e4, body spans 0x9e4..0xe0c (~0x428 bytes). */
static int boxsearch_9e4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c0, 0x1c8, 0x1d0, 0x1c8, 0x1d0, 0x1d8, 0x1e0, 0x1d8, ... (40 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x28, +0x29, +0x30, +0x44, +0x48, +0x4c, +0x50 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0xe38, body spans 0xe38..0xf40 (~0x108 bytes). */
static int boxsearch_e38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4d9c, 0x2a8, 0x2b0, 0x2b0, 0x2b8, 0x2b8, 0x2c0 */
    /* Field offsets touched: +0x04, +0x14, +0x18, +0x28, +0x44, +0x48, +0x4c, +0x50 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0xf44, body spans 0xf44..0x10c0 (~0x17c bytes). */
static int boxsearch_f44(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x208, 0x2c8, 0x2d0, 0x2d8, 0x2e0, 0x2e8 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x28, +0x44, +0x5c */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x10f0, body spans 0x10f0..0x1198 (~0xa8 bytes). */
static int boxsearch_10f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3250 */
    /* Field offsets touched: +0x02, +0x04, +0x0b, +0x28 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x11a8, body spans 0x11a8..0x12a0 (~0xf8 bytes). */
static int boxsearch_11a8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x2f8, 0x270 */
    /* Field offsets touched: +0x28, +0x48, +0x54, +0x58 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x12a4, body spans 0x12a4..0x1648 (~0x3a4 bytes). */
static int boxsearch_12a4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x1b0, 0x308, 0x3184, 0x310, 0x190, 0x198, 0x208, ... (24 total) */
    /* Field offsets touched: +0x02, +0x04, +0x05, +0x06, +0x07, +0x08, +0x09, +0x0a, +0x0b, +0x14, +0x28, +0x48, +0x54, +0x58, +0xc8, +0xc9, +0xca, +0xcb */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x1660, body spans 0x1660..0x16b4 (~0x54 bytes). */
static int boxsearch_1660(ModuleActor *self) {
    (void)self;
    /* BL targets: 0xe38 */
    /* Field offsets touched: +0x1c, +0x24, +0x28 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x16b8, body spans 0x16b8..0x18b8 (~0x200 bytes). */
static int boxsearch_16b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x330, 0x338, 0x2dc4, 0x340, 0x208, 0x210, 0x250, 0x258, ... (9 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x28, +0x3c, +0x3e */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x18dc, body spans 0x18dc..0x1a08 (~0x12c bytes). */
static int boxsearch_18dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x2e8, 0x350, 0x198, 0x190, 0x208, 0x210, 0x340, ... (12 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x18, +0x1c, +0x20, +0x28 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x1a18, body spans 0x1a18..0x2020 (~0x608 bytes). */
static int boxsearch_1a18(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x330, 0x338, 0x360, 0x340, 0x368, 0x360, 0x340, 0x368, ... (27 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x1c, +0x20, +0x24, +0x28, +0x29, +0x2a, +0x2b, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x3e, +0x40, +0x42, +0x44, +0x46 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2034, body spans 0x2034..0x2248 (~0x214 bytes). */
static int boxsearch_2034(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x1b8, 0x390, 0x2f0, 0x2e0, 0x320, 0x2b0, 0x2dfc, ... (21 total) */
    /* Field offsets touched: +0x08, +0x14, +0x28, +0x48, +0x54, +0x58, +0xc8, +0xca, +0xcb */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2254, body spans 0x2254..0x2350 (~0xfc bytes). */
static int boxsearch_2254(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x340, 0x198, 0x198, 0x198, 0x198, 0x198, 0x198, 0x198, ... (10 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x14, +0x28, +0xc8, +0xca */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2364, body spans 0x2364..0x240c (~0xa8 bytes). */
static int boxsearch_2364(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x398, 0x1b8, 0x398 */
    /* Field offsets touched: +0x28, +0x4c */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2418, body spans 0x2418..0x24ac (~0x94 bytes). */
static int boxsearch_2418(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x26e8 */
    /* Field offsets touched: +0x04, +0x28, +0x5c, +0xc9, +0xca */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x25cc, body spans 0x25cc..0x26d4 (~0x108 bytes). */
static int boxsearch_25cc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x198, 0x198, 0x198, 0x198, 0x198, 0x3a0, 0x3a8, ... (10 total) */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x26e8, body spans 0x26e8..0x2bac (~0x4c4 bytes). */
static int boxsearch_26e8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3b0, 0x3b8, 0x3c0, 0x3c8, 0x3a8, 0x3a0, 0x3a8, 0x190, ... (36 total) */
    /* Field offsets touched: +0x01, +0x02, +0x04, +0x08, +0x0c, +0x10 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2bd8, body spans 0x2bd8..0x2dbc (~0x1e4 bytes). */
static int boxsearch_2bd8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x398, 0x1b8, 0x398, 0x410, 0x270, 0x398, 0x418, ... (12 total) */
    /* Field offsets touched: +0x28, +0x48, +0x50, +0x54, +0x58 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2dc4, body spans 0x2dc4..0x2df4 (~0x30 bytes). */
static int boxsearch_2dc4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x428 */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x2dfc, body spans 0x2dfc..0x3088 (~0x28c bytes). */
static int boxsearch_2dfc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x1b8, 0x190, 0x190, 0x190, 0x270, 0x270, 0x390, ... (17 total) */
    /* Field offsets touched: +0x04, +0x28, +0x48, +0x5c, +0xc8, +0xc9, +0xca */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3184, body spans 0x3184..0x3248 (~0xc4 bytes). */
static int boxsearch_3184(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x398, 0x418, 0x1b8, 0x398, 0x1b8 */
    /* Field offsets touched: +0x28, +0x4c */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3250, body spans 0x3250..0x3424 (~0x1d4 bytes). */
static int boxsearch_3250(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c8, 0x3a8, 0x3a0, 0x3a8, 0x3a0, 0x3a8, 0x3d0, 0x3a8, ... (18 total) */
    /* Field offsets touched: +0x02, +0x04, +0x05, +0x06, +0x07, +0x08, +0x09, +0x0a, +0x0b */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3588, body spans 0x3588..0x3604 (~0x7c bytes). */
static int boxsearch_3588(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3184, 0x480c */
    /* Field offsets touched: +0x04, +0x08, +0x28, +0xc9, +0xca, +0xcb */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x360c, body spans 0x360c..0x36dc (~0xd0 bytes). */
static int boxsearch_360c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x2bd8, 0x308, 0x2bd8, 0x308 */
    /* Field offsets touched: +0x28, +0x54, +0x58, +0x5c */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x36e0, body spans 0x36e0..0x37a8 (~0xc8 bytes). */
static int boxsearch_36e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x350, 0x198, 0x198, 0x190, 0x358, 0x119c, 0xf44 */
    /* Field offsets touched: +0x04, +0x18, +0x28, +0xc8, +0xc9, +0xca, +0xcb */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x37b4, body spans 0x37b4..0x3a10 (~0x25c bytes). */
static int boxsearch_37b4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x430, 0x2e0, 0x320, 0x2b0, 0x328, 0x3250, 0x198, 0x198, ... (20 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x18, +0x20, +0x28, +0x54, +0x58, +0x88, +0xc9, +0xcc, +0xd0, +0xd4, +0xd8 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3a20, body spans 0x3a20..0x3c04 (~0x1e4 bytes). */
static int boxsearch_3a20(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x270, 0x270, 0x398, 0x1b8, 0x270, 0x398, 0x1b8, 0x398, ... (10 total) */
    /* Field offsets touched: +0x28, +0x5c */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3c0c, body spans 0x3c0c..0x3d00 (~0xf4 bytes). */
static int boxsearch_3c0c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x350, 0x378, 0x378 */
    /* Field offsets touched: +0x04, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3d04, body spans 0x3d04..0x3e10 (~0x10c bytes). */
static int boxsearch_3d04(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2dc4, 0x2dc4, 0x208, 0x210, 0x250, 0x258 */
    /* Field offsets touched: +0x04, +0x0c, +0x14, +0x28, +0x2a, +0x2b */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x3e24, body spans 0x3e24..0x4014 (~0x1f0 bytes). */
static int boxsearch_3e24(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2dc4, 0x208, 0x210, 0x250, 0x258, 0x2dc4, 0x208, 0x210, ... (12 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x14, +0x28, +0x2a, +0x2b */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x402c, body spans 0x402c..0x4734 (~0x708 bytes). */
static int boxsearch_402c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x3c8, 0x3a8, 0x190, 0x190, 0x3a0, 0x3a8, 0x198, ... (63 total) */
    /* Field offsets touched: +0x02, +0x04, +0x05, +0x06, +0x07, +0x08, +0x09, +0x0a, +0x0b, +0x28, +0xc8 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4744, body spans 0x4744..0x4750 (~0xc bytes). */
static int boxsearch_4744(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x438 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4764, body spans 0x4764..0x4774 (~0x10 bytes). */
static int boxsearch_4764(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x438 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4780, body spans 0x4780..0x47fc (~0x7c bytes). */
static int boxsearch_4780(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8 */
    /* Field offsets touched: +0x04, +0x08, +0x0c */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4894, body spans 0x4894..0x497c (~0xe8 bytes). */
static int boxsearch_4894(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x198, 0x198, 0x198, 0x198, 0x3e8, 0x3a8, 0x190, ... (9 total) */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4998, body spans 0x4998..0x4a88 (~0xf0 bytes). */
static int boxsearch_4998(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x198, 0x198, 0x198, 0x198, 0x198, 0x3e0, 0x3a8, ... (10 total) */
    /* Field offsets touched: +0x04, +0x14 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4aa8, body spans 0x4aa8..0x4d78 (~0x2d0 bytes). */
static int boxsearch_4aa8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d8, 0x448, 0x450, 0x458, 0x460, 0x468, 0x470, 0x478, ... (33 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x14, +0x18, +0x74 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4d9c, body spans 0x4d9c..0x4e90 (~0xf4 bytes). */
static int boxsearch_4d9c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4f0, 0x4f8, 0x500, 0x508, 0x510, 0x518, 0x520, 0x528 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4e94, body spans 0x4e94..0x4fa4 (~0x110 bytes). */
static int boxsearch_4e94(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x530, 0x380, 0x538, 0x540, 0x540, 0x548, 0x548, 0x548, ... (9 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x14 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x4fa8, body spans 0x4fa8..0x5024 (~0x7c bytes). */
static int boxsearch_4fa8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x550, 0x558 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x14, +0x18, +0x24, +0x28 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x5034, body spans 0x5034..0x50cc (~0x98 bytes). */
static int boxsearch_5034(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x560, 0x560, 0x560, 0x568 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x18, +0x1c, +0x20, +0x24, +0x28 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x50d0, body spans 0x50d0..0x5114 (~0x44 bytes). */
static int boxsearch_50d0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x578, 0x580 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x1c, +0x24 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x5118, body spans 0x5118..0x518c (~0x74 bytes). */
static int boxsearch_5118(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x588, 0x1c8, 0x1d0, 0x1d8, 0x590 */
    /* Field offsets touched: +0x04, +0x18, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x519c, body spans 0x519c..0x51f4 (~0x58 bytes). */
static int boxsearch_519c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8, 0x598 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x5204, body spans 0x5204..0x5258 (~0x54 bytes). */
static int boxsearch_5204(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b8, 0x598 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x5278, body spans 0x5278..0x52b0 (~0x38 bytes). */
static int boxsearch_5278(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5a0, 0x5a8 */
    /* Field offsets touched: +0x88 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x52b4, body spans 0x52b4..0x52bc (~0x8 bytes). */
static int boxsearch_52b4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5b0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x52fc, body spans 0x52fc..0x5328 (~0x2c bytes). */
static int boxsearch_52fc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x598 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x5334, body spans 0x5334..0x5360 (~0x2c bytes). */
static int boxsearch_5334(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x598 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* CRO 0x53bc, body spans 0x53bc..0x5438 (~0x7c bytes). */
static int boxsearch_53bc(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllBoxSearch.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x5234 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x5234..; BL targets: 0x598 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 52 candidate function boundaries (push/pop pairing).
 * Total BL sites: 533 (to imports: 478, internal: 55).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */