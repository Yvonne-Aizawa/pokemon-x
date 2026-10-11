/*
 * Preliminary decompilation of DllTrialDownload.cro.
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

/* Module summary (from DllTrialDownload.cro header):
 *   file size: 0xb000
 *   code:      offset 0x180  size 0x8e80
 *   data:      offset 0xa7b8  size 0x34
 *   bss:       size  0x20
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 201
 *   import veneers (ldr pc,[pc,#N]): 176 at 0x180..0x6f8
 *   total BL sites: 606 (to imports: 510, internal: 96)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x5c (hit 124x)
 *   +0x40 (hit 76x)
 *   +0x74 (hit 43x)
 *   +0x04 (hit 42x)
 *   +0x9c (hit 42x)
 *   +0x5d (hit 40x)
 *   +0xb0 (hit 38x)
 *   +0xa40 (hit 36x)
 *   +0xac (hit 28x)
 *   +0xa4c (hit 28x)
 *   +0xa0 (hit 27x)
 *   +0xd4 (hit 23x)
 *   +0x80 (hit 23x)
 *   +0x60 (hit 22x)
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

/* Index: 65 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x0728..0x0754  BL(local=0, imp=1)
 *   CRO 0x0760..0x078c  BL(local=0, imp=1)
 *   CRO 0x0794..0x07fc  BL(local=1, imp=0)
 *   CRO 0x0800..0x12e0  BL(local=16, imp=58)
 *   CRO 0x1300..0x1774  BL(local=15, imp=14)
 *   CRO 0x1788..0x19e4  BL(local=6, imp=10)
 *   CRO 0x1a08..0x1a84  BL(local=1, imp=0)
 *   CRO 0x1a88..0x1b70  BL(local=0, imp=4)
 *   CRO 0x1b74..0x1cdc  BL(local=1, imp=0)
 *   CRO 0x1cf8..0x1eb0  BL(local=0, imp=11)
 *   CRO 0x1ec0..0x1fb0  BL(local=3, imp=0)
 *   CRO 0x1fb4..0x21a8  BL(local=2, imp=12)
 *   CRO 0x21b8..0x2300  BL(local=0, imp=10)
 *   CRO 0x2394..0x2490  BL(local=2, imp=0)
 *   CRO 0x2494..0x252c  BL(local=2, imp=0)
 *   CRO 0x2534..0x25d0  BL(local=1, imp=3)
 *   CRO 0x25d8..0x266c  BL(local=0, imp=3)
 *   CRO 0x267c..0x27f4  BL(local=0, imp=4)
 *   CRO 0x2850..0x28e4  BL(local=0, imp=3)
 *   CRO 0x2908..0x2ab4  BL(local=0, imp=2)
 *   CRO 0x2abc..0x2be8  BL(local=0, imp=11)
 *   CRO 0x2c08..0x2d98  BL(local=0, imp=13)
 *   CRO 0x2db0..0x2dd8  BL(local=0, imp=1)
 *   CRO 0x2ddc..0x2f38  BL(local=0, imp=4)
 *   CRO 0x2f44..0x2f8c  BL(local=0, imp=2)
 *   CRO 0x2fa0..0x2fe8  BL(local=0, imp=2)
 *   CRO 0x2ff4..0x3024  BL(local=1, imp=2)
 *   CRO 0x3028..0x30b4  BL(local=0, imp=2)
 *   CRO 0x30c8..0x3118  BL(local=1, imp=1)
 *   CRO 0x311c..0x318c  BL(local=1, imp=2)
 *   CRO 0x3190..0x33e0  BL(local=0, imp=8)
 *   CRO 0x3404..0x3434  BL(local=0, imp=3)
 *   CRO 0x3440..0x3470  BL(local=0, imp=3)
 *   CRO 0x3478..0x399c  BL(local=18, imp=25)
 *   CRO 0x39ac..0x3d60  BL(local=2, imp=13)
 *   CRO 0x3d88..0x436c  BL(local=3, imp=21)
 *   CRO 0x4374..0x4450  BL(local=0, imp=4)
 *   CRO 0x445c..0x44b4  BL(local=0, imp=6)
 *   CRO 0x44b8..0x4710  BL(local=0, imp=22)
 *   CRO 0x4718..0x496c  BL(local=4, imp=3)
 *   CRO 0x497c..0x4a00  BL(local=1, imp=1)
 *   CRO 0x4a08..0x4a8c  BL(local=1, imp=1)
 *   CRO 0x4a94..0x4bb0  BL(local=0, imp=19)
 *   CRO 0x4c0c..0x4db8  BL(local=0, imp=14)
 *   CRO 0x4dc4..0x5350  BL(local=3, imp=19)
 *   CRO 0x535c..0x558c  BL(local=2, imp=17)
 *   CRO 0x55a4..0x5864  BL(local=1, imp=12)
 *   CRO 0x5870..0x5988  BL(local=0, imp=5)
 *   CRO 0x598c..0x5b20  BL(local=0, imp=15)
 *   CRO 0x5b2c..0x5c30  BL(local=0, imp=8)
 *   CRO 0x5c38..0x5d58  BL(local=0, imp=8)
 *   CRO 0x5d94..0x5ec0  BL(local=0, imp=10)
 *   CRO 0x5ec8..0x6018  BL(local=0, imp=8)
 *   CRO 0x6028..0x612c  BL(local=0, imp=8)
 *   CRO 0x6134..0x61e8  BL(local=0, imp=8)
 *   CRO 0x61f8..0x6434  BL(local=0, imp=13)
 *   CRO 0x6448..0x6548  BL(local=0, imp=6)
 *   CRO 0x6554..0x6ba8  BL(local=1, imp=37)
 *   CRO 0x6bb0..0x6bb8  BL(local=1, imp=0)
 *   CRO 0x6bc0..0x6cf0  BL(local=0, imp=10)
 *   CRO 0x6d08..0x6d60  BL(local=0, imp=0)
 *   CRO 0x6d90..0x6e28  BL(local=2, imp=0)
 *   CRO 0x6e38..0x6f34  BL(local=2, imp=0) [contains export: nnroControlObject_]
 *   CRO 0x6f38..0x6fc4  BL(local=0, imp=2)
 *   CRO 0x7020..0x709c  BL(local=0, imp=0)
 */

/* CRO 0x728, body spans 0x728..0x754 (~0x2c bytes). */
static int trialdownload_728(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x760, body spans 0x760..0x78c (~0x2c bytes). */
static int trialdownload_760(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x794, body spans 0x794..0x7fc (~0x68 bytes). */
static int trialdownload_794(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4c0c */
    /* Field offsets touched: +0xa0, +0xac, +0xb0, +0x160, +0x164 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x800, body spans 0x800..0x12e0 (~0xae0 bytes). */
static int trialdownload_800(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x6554, 0x198, 0x1a0, 0x1a8, 0x1b0, 0x535c, 0x1b8, ... (74 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x0d, +0x10, +0x14, +0x18, +0x2c, +0x40, +0x44, +0x48, +0x4c, +0x50, +0x51, +0x54, +0x5c, +0x5d, +0x60, +0x84, +0x88, +0x9c, +0xa0, +0xa3, +0xa8, +0xac, +0xb0, +0xb4, +0xbc, +0xc0, +0xc6, +0xd0, +0xd4, +0xd8, +0xdc, +0xe0, +0xe4, +0x15c, +0x15d, +0x160, +0x164, +0x8f1, +0x8f8, +0x8fc, +0xa40, +0xa44, +0xa4c, +0xa80, +0xa8c, +0xa94, +0xa98, +0xaa0, +0xaa4, +0xaa9, +0xab4, +0xab8, +0xabc */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1300, body spans 0x1300..0x1774 (~0x474 bytes). */
static int trialdownload_1300(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x298, 0x298, 0x298, 0x298, 0x2a0, 0x2a0, 0x2a0, 0x4a08, ... (29 total) */
    /* Field offsets touched: +0x1c, +0x40, +0x5d, +0x60, +0x74, +0x9c, +0xa0, +0xb0, +0x8fc, +0xa40, +0xa44, +0xa4c, +0xa9c, +0xaa8 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1788, body spans 0x1788..0x19e4 (~0x25c bytes). */
static int trialdownload_1788(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b0, 0x445c, 0x445c, 0x1e0, 0x200, 0x200, 0x4bc0, 0x445c, ... (16 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x0d, +0x10, +0x2c, +0x40, +0x44, +0x84, +0x88, +0xa0, +0xa4, +0xac, +0xb0, +0xbc, +0xc8, +0xcc, +0x16c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1a08, body spans 0x1a08..0x1a84 (~0x7c bytes). */
static int trialdownload_1a08(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5870 */
    /* Field offsets touched: +0x40, +0x5d, +0xa0 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1a88, body spans 0x1a88..0x1b70 (~0xe8 bytes). */
static int trialdownload_1a88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2c8, 0x2d0, 0x2c8, 0x2d0 */
    /* Field offsets touched: +0x6c, +0xa1, +0xa2, +0xa3, +0xa4, +0xa8, +0xac, +0xb0 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1b74, body spans 0x1b74..0x1cdc (~0x168 bytes). */
static int trialdownload_1b74(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x267c */
    /* Field offsets touched: +0x0a, +0x48, +0x74, +0x75, +0x88, +0xa8, +0xac, +0xb0, +0xb8, +0xbc, +0xc4, +0xc5 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1cf8, body spans 0x1cf8..0x1eb0 (~0x1b8 bytes). */
static int trialdownload_1cf8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x1f8, 0x1c0, 0x1c8, 0x1d0, 0x190, 0x1d0, 0x1f0, ... (11 total) */
    /* Field offsets touched: +0x08, +0x14, +0x18, +0x40, +0xac, +0xb0, +0xc8, +0xd0, +0xd4, +0xdc, +0xe0, +0xe4, +0x15d, +0x168, +0x178, +0xa40 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1ec0, body spans 0x1ec0..0x1fb0 (~0xf0 bytes). */
static int trialdownload_1ec0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x44b8, 0x44b8, 0x4bc0 */
    /* Field offsets touched: +0x08, +0x40, +0x6c, +0x78, +0xa1, +0xa2, +0xa8, +0xb0, +0xc0, +0xd4, +0xdc, +0x8fc, +0xa40, +0xa44, +0xa4c, +0xa74, +0xa78, +0xa80, +0xa8c, +0xa94, +0xa98, +0xaa4, +0xab4, +0xab8, +0xabc */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x1fb4, body spans 0x1fb4..0x21a8 (~0x1f4 bytes). */
static int trialdownload_1fb4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x1c0, 0x1c8, 0x1d0, 0x190, 0x1d0, 0x1f0, 0x1d8, ... (14 total) */
    /* Field offsets touched: +0x08, +0x14, +0x18, +0x40, +0x6c, +0x84, +0xac, +0xb0, +0xc0, +0xc8, +0xd0, +0xd4, +0xdc, +0x168, +0x170, +0x178, +0xa40, +0xa44, +0xa4c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x21b8, body spans 0x21b8..0x2300 (~0x148 bytes). */
static int trialdownload_21b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2e8, 0x2f0, 0x2f8, 0x1c8, 0x300, 0x308, 0x310, 0x188, ... (10 total) */
    /* Field offsets touched: +0x14, +0x1c, +0x2c, +0x48, +0x88, +0xbc, +0xc4, +0xc5, +0x174, +0x175 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2394, body spans 0x2394..0x2490 (~0xfc bytes). */
static int trialdownload_2394(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5d94, 0x5b2c */
    /* Field offsets touched: +0x40, +0x5d, +0x60, +0xa0, +0xb0, +0xa9c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2494, body spans 0x2494..0x252c (~0x98 bytes). */
static int trialdownload_2494(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4718, 0x44b8 */
    /* Field offsets touched: +0x40, +0x5d, +0x60, +0xa0, +0xc6, +0xa40, +0xa44, +0xa4c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2534, body spans 0x2534..0x25d0 (~0x9c bytes). */
static int trialdownload_2534(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x21b8, 0x2a8, 0x338, 0x340 */
    /* Field offsets touched: +0x40, +0x5d, +0x60, +0xa0, +0xa1, +0xa2, +0xa3, +0xc6, +0xa4c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x25d8, body spans 0x25d8..0x266c (~0x94 bytes). */
static int trialdownload_25d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x338, 0x340 */
    /* Field offsets touched: +0x40, +0x5d, +0x60, +0xa0, +0xa1, +0xa2, +0xa3, +0xc6, +0xa4c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x267c, body spans 0x267c..0x27f4 (~0x178 bytes). */
static int trialdownload_267c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x348, 0x350, 0x2e0, 0x2e0 */
    /* Field offsets touched: +0x04, +0x08, +0x09, +0x0b, +0x40, +0x48, +0x88, +0xc4, +0xc5, +0xd4, +0x28e, +0x9c0, +0xad8 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2850, body spans 0x2850..0x28e4 (~0x94 bytes). */
static int trialdownload_2850(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x338, 0x340 */
    /* Field offsets touched: +0x40, +0x5d, +0x60, +0xa0, +0xa1, +0xa2, +0xa3, +0xc6, +0xa4c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2908, body spans 0x2908..0x2ab4 (~0x1ac bytes). */
static int trialdownload_2908(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d8, 0x2d8 */
    /* Field offsets touched: +0x08, +0x40, +0x74, +0xa1, +0xa3, +0xa8, +0xac, +0xb0, +0xc8, +0xd0, +0xd4, +0xdc, +0xe4, +0x168, +0x178, +0xa40 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2abc, body spans 0x2abc..0x2be8 (~0x12c bytes). */
static int trialdownload_2abc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x358, 0x358, 0x358, 0x358, 0x360, 0x210, 0x218, 0x220, ... (11 total) */
    /* Field offsets touched: +0x04, +0x18, +0x40, +0x44, +0x48, +0xb4, +0xbc, +0xc0, +0xc8, +0xd0, +0xd4 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2c08, body spans 0x2c08..0x2d98 (~0x190 bytes). */
static int trialdownload_2c08(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x370, 0x378, 0x380, 0x380, 0x388, 0x390, 0x390, 0x390, ... (13 total) */
    /* Field offsets touched: +0x0a, +0x2c, +0x48, +0x54, +0x58, +0x5d, +0x90, +0xac, +0xb0, +0xb4, +0xbc, +0xc0, +0xc8, +0xd0, +0xd4 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2db0, body spans 0x2db0..0x2dd8 (~0x28 bytes). */
static int trialdownload_2db0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3b8 */
    /* Field offsets touched: +0x5c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2ddc, body spans 0x2ddc..0x2f38 (~0x15c bytes). */
static int trialdownload_2ddc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c0, 0x3c8, 0x210, 0x3d0 */
    /* Field offsets touched: +0x20, +0x40, +0x44, +0x50, +0x51, +0x54, +0x58, +0x5c, +0x5d, +0x60, +0x64, +0x68, +0x6c, +0x70, +0x74, +0x78, +0x7c, +0x80, +0x84, +0x88, +0x8c, +0x90, +0x94, +0x98, +0x9c, +0xa0, +0xa1, +0xa2, +0xa3, +0xa4, +0xb0, +0xb4, +0xb8, +0xbc, +0xc0, +0xc4, +0xc5, +0xc6, +0xc8, +0xcc, +0xd0, +0xd4, +0xd8, +0xdc, +0xe0, +0xe4, +0x15c, +0x15d, +0x160, +0x164, +0x168, +0x16c, +0x170, +0x174, +0x175, +0x178 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2f44, body spans 0x2f44..0x2f8c (~0x48 bytes). */
static int trialdownload_2f44(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3d8, 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2fa0, body spans 0x2fa0..0x2fe8 (~0x48 bytes). */
static int trialdownload_2fa0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3d8, 0x180 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x2ff4, body spans 0x2ff4..0x3024 (~0x30 bytes). */
static int trialdownload_2ff4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x445c, 0x248, 0x3e0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x3028, body spans 0x3028..0x30b4 (~0x8c bytes). */
static int trialdownload_3028(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x328, 0x3e8 */
    /* Field offsets touched: +0x32, +0x36, +0x3a */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x30c8, body spans 0x30c8..0x3118 (~0x50 bytes). */
static int trialdownload_30c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x445c, 0x400 */
    /* Field offsets touched: +0x04, +0x08, +0x10 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x311c, body spans 0x311c..0x318c (~0x70 bytes). */
static int trialdownload_311c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x445c, 0x408, 0x400 */
    /* Field offsets touched: +0x04, +0x08, +0x10 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x3190, body spans 0x3190..0x33e0 (~0x250 bytes). */
static int trialdownload_3190(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x410, 0x418, 0x1e0, 0x330, 0x200, 0x1e0, 0x1e0 */
    /* Field offsets touched: +0x0c, +0x0d, +0x10, +0x20, +0x68, +0xa90 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x3404, body spans 0x3404..0x3434 (~0x30 bytes). */
static int trialdownload_3404(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x228, 0x240, 0x420 */
    /* Field offsets touched: +0x08 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x3440, body spans 0x3440..0x3470 (~0x30 bytes). */
static int trialdownload_3440(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x228, 0x240, 0x420 */
    /* Field offsets touched: +0x08 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x3478, body spans 0x3478..0x399c (~0x524 bytes). */
static int trialdownload_3478(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x428, 0x428, 0x260, 0x428, 0x4c0c, 0x428, 0x438, 0x44b8, ... (43 total) */
    /* Field offsets touched: +0x20, +0x5c, +0x80, +0x84, +0x9c, +0xb0, +0x8f4, +0x8f8, +0x8fc, +0xa40, +0xa44, +0xa4c, +0xa6c, +0xa70, +0xa9c, +0xaa4 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x39ac, body spans 0x39ac..0x3d60 (~0x3b4 bytes). */
static int trialdownload_39ac(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x480, 0x480, 0x480, 0x488, 0x480, 0x480, 0x488, 0x480, ... (15 total) */
    /* Field offsets touched: +0x5c, +0xb8, +0xbc, +0xc0, +0xc4, +0xf1, +0x8f1, +0x8f4, +0xa81, +0xa84 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x3d88, body spans 0x3d88..0x436c (~0x5e4 bytes). */
static int trialdownload_3d88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x490, 0x498, 0x440, 0x448, 0x44b8, 0x480, 0x480, 0x480, ... (24 total) */
    /* Field offsets touched: +0x5c, +0x80, +0xb8, +0xbc, +0xf1, +0x8f1, +0x8f4, +0x8fc, +0xa40, +0xa44, +0xa48, +0xa4c, +0xa50, +0xa81, +0xa84, +0xaa8 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x4374, body spans 0x4374..0x4450 (~0xdc bytes). */
static int trialdownload_4374(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x480, 0x488, 0x428, 0x428 */
    /* Field offsets touched: +0x5c, +0x8fc, +0xa48, +0xa4c, +0xa50, +0xa6c, +0xa80, +0xaa4 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x445c, body spans 0x445c..0x44b4 (~0x58 bytes). */
static int trialdownload_445c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x228, 0x208, 0x228, 0x4a8, 0x228, 0x4b0 */
    /* Field offsets touched: +0x0c, +0x0d */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x44b8, body spans 0x44b8..0x4710 (~0x258 bytes). */
static int trialdownload_44b8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x428, 0x428, 0x428, 0x428, 0x428, 0x438, 0x4b8, 0x4c0, ... (22 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x8f8, +0x900, +0x940, +0x980, +0xa40, +0xa74, +0xa8c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x4718, body spans 0x4718..0x496c (~0x254 bytes). */
static int trialdownload_4718(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x490, 0x498, 0x3d88, 0x3d88, 0x3d88, 0x3d88, 0x440 */
    /* Field offsets touched: +0x80, +0x81, +0xbc, +0xf1, +0x8f4, +0xa4c, +0xa6c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x497c, body spans 0x497c..0x4a00 (~0x84 bytes). */
static int trialdownload_497c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x39ac, 0x2a8 */
    /* Field offsets touched: +0xb0, +0x8f1, +0x8f4, +0xa81, +0xa84 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x4a08, body spans 0x4a08..0x4a8c (~0x84 bytes). */
static int trialdownload_4a08(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x39ac, 0x2a8 */
    /* Field offsets touched: +0xb0, +0xb8, +0xbc, +0x8f1, +0x8f4, +0xa81, +0xa84 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x4a94, body spans 0x4a94..0x4bb0 (~0x11c bytes). */
static int trialdownload_4a94(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x228, 0x208, 0x380, 0x380, 0x4f0, 0x4f8, 0x210, 0x500, ... (19 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x18 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x4c0c, body spans 0x4c0c..0x4db8 (~0x1ac bytes). */
static int trialdownload_4c0c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x428, 0x428, 0x428, 0x4c8, 0x4d0, 0x538, 0x428, 0x428, ... (14 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x80, +0x8c, +0x9c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x4dc4, body spans 0x4dc4..0x5350 (~0x58c bytes). */
static int trialdownload_4dc4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4c0c, 0x4c0c, 0x4c0c, 0x3b0, 0x3b0, 0x3b0, 0x3b0, 0x3b0, ... (22 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x0d, +0x0e, +0x0f, +0x10, +0x5c, +0x74, +0x80, +0x8f8, +0x8fc, +0x900, +0x904, +0x908, +0x90c, +0x940, +0x944, +0x948, +0x94c, +0x950, +0x980, +0x9c0, +0x9c4, +0x9c8, +0x9cc, +0x9d0, +0xa00, +0xa0c, +0xa10, +0xa50, +0xa74, +0xa88 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x535c, body spans 0x535c..0x558c (~0x230 bytes). */
static int trialdownload_535c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x540, 0x550, 0x558, 0x560, 0x568, 0x570, 0x270, 0x578, ... (19 total) */
    /* Field offsets touched: +0x04, +0x20, +0x5c, +0x74, +0x80, +0x84, +0x88, +0x8c, +0x8d, +0x90, +0x94, +0x98, +0x9c, +0x9d, +0xa4, +0xa70, +0xa9d */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x55a4, body spans 0x55a4..0x5864 (~0x2c0 bytes). */
static int trialdownload_55a4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b8, 0x4c0, 0x4e8, 0x4b8, 0x4c0, 0x4e8, 0x4b8, 0x4c0, ... (13 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x80, +0x98, +0x9c, +0x8f8, +0xa00, +0xa40, +0xa8c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x5870, body spans 0x5870..0x5988 (~0x118 bytes). */
static int trialdownload_5870(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5a0, 0x5a0, 0x5a8, 0x5b0, 0x5b0 */
    /* Field offsets touched: +0x1c, +0x70, +0x80, +0x81, +0x9c, +0xb0, +0xb4, +0xb8, +0xbc, +0x8f1, +0xa6c, +0xa81, +0xa84, +0xaa8 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x598c, body spans 0x598c..0x5b20 (~0x194 bytes). */
static int trialdownload_598c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c8, 0x398, 0x468, 0x450, 0x588, 0x580, 0x5b8, 0x398, ... (15 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x90, +0x94 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x5b2c, body spans 0x5b2c..0x5c30 (~0x104 bytes). */
static int trialdownload_5b2c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x438, 0x5e8, 0x5e8, 0x5e8, 0x5f0, 0x5f0, 0x5f0 */
    /* Field offsets touched: +0x9c, +0xec, +0xf0, +0x8f0, +0x8f4, +0xa40, +0xa74 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x5c38, body spans 0x5c38..0x5d58 (~0x120 bytes). */
static int trialdownload_5c38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x428, 0x5f8, 0x438, 0x600, 0x438, 0x608, 0x438, 0x428 */
    /* Field offsets touched: +0x5c, +0xc4, +0xec, +0xf0, +0x8f0 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x5d94, body spans 0x5d94..0x5ec0 (~0x12c bytes). */
static int trialdownload_5d94(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x438, 0x5e8, 0x5e8, 0x5e8, 0x5f0, 0x5f0, 0x5f0, ... (10 total) */
    /* Field offsets touched: +0x1c, +0x9c, +0xec, +0xf0, +0x8f0, +0x8f4, +0xa40, +0xa74 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x5ec8, body spans 0x5ec8..0x6018 (~0x150 bytes). */
static int trialdownload_5ec8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x480, 0x488, 0x428, 0x428, 0x428, 0x428, 0x480, 0x488 */
    /* Field offsets touched: +0x5c, +0xb0, +0xc0, +0xc4, +0xec */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6028, body spans 0x6028..0x612c (~0x104 bytes). */
static int trialdownload_6028(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x438, 0x5e8, 0x5e8, 0x5e8, 0x5f0, 0x5f0, 0x5f0 */
    /* Field offsets touched: +0x9c, +0xec, +0x8f0, +0x8f4, +0xa40 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6134, body spans 0x6134..0x61e8 (~0xb4 bytes). */
static int trialdownload_6134(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x440, 0x450, 0x588, 0x618, 0x620, 0x260, 0x260 */
    /* Field offsets touched: +0x04, +0x74, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x61f8, body spans 0x61f8..0x6434 (~0x23c bytes). */
static int trialdownload_61f8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x428, 0x4b8, 0x4c0, 0x438, 0x428, 0x428, 0x428, 0x428, ... (13 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x74, +0x8f8, +0x8fc, +0x9c0, +0xa4c, +0xa8c, +0xa90, +0xa98 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6448, body spans 0x6448..0x6548 (~0x100 bytes). */
static int trialdownload_6448(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x628, 0x628, 0x640, 0x650, 0x658, 0x660 */
    /* Field offsets touched: +0x24, +0x58, +0x5c, +0x78, +0x80, +0x84, +0x88, +0x94, +0x9c, +0xa4, +0xaa0 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6554, body spans 0x6554..0x6ba8 (~0x654 bytes). */
static int trialdownload_6554(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x668, 0x1e0, 0x670, 0x678, 0x1c8, 0x580, 0x680, 0x688, ... (38 total) */
    /* Field offsets touched: +0x04, +0x08, +0x10, +0x20, +0x5c, +0x74, +0x78, +0x80, +0x84, +0x88, +0x8c, +0x8d, +0x90, +0x94, +0x98, +0xa4, +0xb0, +0xb4, +0xb8, +0xbc, +0xc0, +0xc4, +0xc8, +0xcc, +0xd0, +0xd4, +0xd8, +0xdc, +0xe0, +0xe4, +0xe8, +0xec, +0x8f0, +0x8f1, +0x8f4, +0x8f8, +0x900, +0x904, +0x908, +0x90c, +0x910, +0x914, +0x918, +0x91c, +0x920, +0x924, +0x928, +0x92c, +0x930, +0x934, +0x938, +0x93c, +0x940, +0x944, +0x948, +0x94c, +0x950, +0x954, +0x958, +0x95c, +0x960, +0x964, +0x968, +0x96c, +0x970, +0x974, +0x978, +0x97c, +0x980, +0x984, +0x988, +0x98c, +0x990, +0x994, +0x998, +0x99c, +0x9a0, +0x9a4, +0x9a8, +0x9ac, +0x9b0, +0x9b4, +0x9b8, +0x9bc, +0x9c0, +0x9c4, +0x9c8, +0x9cc, +0x9d0, +0x9d4, +0x9d8, +0x9dc, +0x9e0, +0x9e4, +0x9e8, +0x9ec, +0x9f0, +0x9f4, +0x9f8, +0x9fc, +0xa00, +0xa04, +0xa08, +0xa0c, +0xa10, +0xa14, +0xa18, +0xa1c, +0xa20, +0xa24, +0xa28, +0xa2c, +0xa30, +0xa34, +0xa38, +0xa3c, +0xa40, +0xa44, +0xa48, +0xa4c, +0xa50, +0xa54, +0xa58, +0xa5c, +0xa60, +0xa64, +0xa68, +0xa6c, +0xa74, +0xa78, +0xa7c, +0xa80, +0xa81, +0xa84, +0xa90, +0xa94, +0xa98, +0xa9c, +0xa9d, +0xaa0, +0xaa4, +0xaa8, +0xaa9, +0xaac, +0xab0, +0xab4, +0xab8, +0xabc */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6bb0, body spans 0x6bb0..0x6bb8 (~0x8 bytes). */
static int trialdownload_6bb0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6bc0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6bc0, body spans 0x6bc0..0x6cf0 (~0x130 bytes). */
static int trialdownload_6bc0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6c8, 0x188, 0x258, 0x188, 0x270, 0x6d0, 0x6d8, 0x6e0, ... (10 total) */
    /* Field offsets touched: +0x04, +0x18, +0x5c, +0x80, +0x84, +0x88, +0x90, +0x94, +0x9c, +0xa4 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6d08, body spans 0x6d08..0x6d60 (~0x58 bytes). */
static int trialdownload_6d08(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x40, +0x5d, +0xa0 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6d90, body spans 0x6d90..0x6e28 (~0x98 bytes). */
static int trialdownload_6d90(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4718, 0x44b8 */
    /* Field offsets touched: +0x40, +0x5d, +0x60, +0x80, +0xa0, +0xc6, +0xa40, +0xa44, +0xa4c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6e38, body spans 0x6e38..0x6f34 (~0xfc bytes). */
static int trialdownload_6e38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5d94, 0x5b2c */
    /* Field offsets touched: +0x39, +0x40, +0x5d, +0x60, +0xa0, +0xb0, +0xa9c */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x6f38, body spans 0x6f38..0x6fc4 (~0x8c bytes). */
static int trialdownload_6f38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x328, 0x3e8 */
    /* Field offsets touched: +0x32, +0x36, +0x3a */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* CRO 0x7020, body spans 0x7020..0x709c (~0x7c bytes). */
static int trialdownload_7020(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllTrialDownload.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x6e98 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x6e98..; BL targets: 0x5d94, 0x5b2c */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 65 candidate function boundaries (push/pop pairing).
 * Total BL sites: 606 (to imports: 510, internal: 96).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */