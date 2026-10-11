/*
 * Preliminary decompilation of DllTrainerCase.cro.
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

/* Module summary (from DllTrainerCase.cro header):
 *   file size: 0x7000
 *   code:      offset 0x180  size 0x4e80
 *   data:      offset 0x6a08  size 0x40
 *   bss:       size  0x80
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 216
 *   import veneers (ldr pc,[pc,#N]): 171 at 0x180..0x6d0
 *   total BL sites: 381 (to imports: 341, internal: 40)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 87x)
 *   +0x74 (hit 57x)
 *   +0x08 (hit 47x)
 *   +0x5c (hit 40x)
 *   +0x78 (hit 40x)
 *   +0x14 (hit 34x)
 *   +0x38 (hit 32x)
 *   +0x0c (hit 30x)
 *   +0xa4 (hit 23x)
 *   +0x98 (hit 21x)
 *   +0x18 (hit 18x)
 *   +0x10 (hit 15x)
 *   +0x1c (hit 15x)
 *   +0x84 (hit 14x)
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
 *   CRO 0x06d8..0x072c  BL(local=2, imp=3)
 *   CRO 0x0738..0x0778  BL(local=1, imp=1)
 *   CRO 0x0788..0x07b8  BL(local=1, imp=0)
 *   CRO 0x07e4..0x084c  BL(local=2, imp=4)
 *   CRO 0x0858..0x0894  BL(local=0, imp=1)
 *   CRO 0x0898..0x08ec  BL(local=1, imp=0)
 *   CRO 0x0908..0x0a0c  BL(local=1, imp=5)
 *   CRO 0x0a10..0x0adc  BL(local=1, imp=1)
 *   CRO 0x0af8..0x0b78  BL(local=1, imp=3)
 *   CRO 0x0b84..0x0bb4  BL(local=0, imp=2)
 *   CRO 0x0bc0..0x0bf0  BL(local=0, imp=2)
 *   CRO 0x0c00..0x0c30  BL(local=0, imp=2)
 *   CRO 0x0c38..0x0f2c  BL(local=3, imp=27)
 *   CRO 0x0f48..0x10c8  BL(local=0, imp=12)
 *   CRO 0x10f0..0x11fc  BL(local=0, imp=11)
 *   CRO 0x1204..0x17ac  BL(local=1, imp=67)
 *   CRO 0x17cc..0x189c  BL(local=0, imp=8)
 *   CRO 0x18a0..0x1acc  BL(local=1, imp=9)
 *   CRO 0x1ae0..0x1b8c  BL(local=0, imp=0)
 *   CRO 0x1b90..0x1d4c  BL(local=0, imp=3)
 *   CRO 0x1d58..0x1ee4  BL(local=0, imp=12)
 *   CRO 0x1ee8..0x1fac  BL(local=0, imp=2)
 *   CRO 0x1fb4..0x2044  BL(local=1, imp=2)
 *   CRO 0x2054..0x21f8  BL(local=0, imp=6)
 *   CRO 0x2210..0x248c  BL(local=1, imp=22)
 *   CRO 0x24b0..0x2590  BL(local=1, imp=10)
 *   CRO 0x2598..0x2630  BL(local=0, imp=5)
 *   CRO 0x2638..0x2714  BL(local=0, imp=7)
 *   CRO 0x271c..0x2bac  BL(local=10, imp=32)
 *   CRO 0x2bb4..0x2f38  BL(local=1, imp=25)
 *   CRO 0x3000..0x3258  BL(local=2, imp=25)
 *   CRO 0x3260..0x3358  BL(local=3, imp=4)
 *   CRO 0x335c..0x3490  BL(local=0, imp=7)
 *   CRO 0x34a0..0x34a8  BL(local=1, imp=0)
 *   CRO 0x34b0..0x35c4  BL(local=0, imp=1)
 *   CRO 0x35d4..0x3700  BL(local=3, imp=7)
 *   CRO 0x3718..0x3784  BL(local=2, imp=1)
 *   CRO 0x3790..0x3798  BL(local=0, imp=1)
 *   CRO 0x37e4..0x3810  BL(local=0, imp=1)
 *   CRO 0x381c..0x3848  BL(local=0, imp=1)
 *   CRO 0x3858..0x3888  BL(local=0, imp=2) [contains export: nnroControlObject_]
 *   CRO 0x3894..0x38c4  BL(local=0, imp=2)
 *   CRO 0x38cc..0x39b0  BL(local=0, imp=0)
 *   CRO 0x3a0c..0x3a88  BL(local=0, imp=0)
 *   CRO 0x3b24..0x3b78  BL(local=0, imp=0)
 *   CRO 0x3b80..0x3bd8  BL(local=0, imp=0)
 *   CRO 0x3be4..0x3c40  BL(local=0, imp=0)
 */

/* CRO 0x6d8, body spans 0x6d8..0x72c (~0x54 bytes). */
static int trainercase_6d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x188, 0x2598, 0x24b0, 0x190 */
    /* Field offsets touched: +0x08, +0x84 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x738, body spans 0x738..0x778 (~0x40 bytes). */
static int trainercase_738(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x3260 */
    /* Field offsets touched: +0x08 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x788, body spans 0x788..0x7b8 (~0x30 bytes). */
static int trainercase_788(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2210 */
    /* Field offsets touched: +0x08 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x7e4, body spans 0x7e4..0x84c (~0x68 bytes). */
static int trainercase_7e4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x188, 0x188, 0x24b0, 0x2598, 0x190 */
    /* Field offsets touched: +0x08, +0x84 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x858, body spans 0x858..0x894 (~0x3c bytes). */
static int trainercase_858(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0xa4 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x898, body spans 0x898..0x8ec (~0x54 bytes). */
static int trainercase_898(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2210 */
    /* Field offsets touched: +0x08, +0x0c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x908, body spans 0x908..0xa0c (~0x104 bytes). */
static int trainercase_908(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a8, 0x1b0, 0x1b0, 0x2054, 0x1a8, 0x1b8 */
    /* Field offsets touched: +0x10, +0x11, +0x14, +0x38, +0x5c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xa10, body spans 0xa10..0xadc (~0xcc bytes). */
static int trainercase_a10(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3000, 0x1c8 */
    /* Field offsets touched: +0x04, +0x14, +0x18, +0x1c, +0x20, +0x38 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xaf8, body spans 0xaf8..0xb78 (~0x80 bytes). */
static int trainercase_af8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d8, 0x1e0, 0x1e8, 0x35d4 */
    /* Field offsets touched: +0x0c, +0x10, +0x11, +0x14, +0x18, +0x1c, +0x24, +0x38 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xb84, body spans 0xb84..0xbb4 (~0x30 bytes). */
static int trainercase_b84(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f0, 0x1f8 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xbc0, body spans 0xbc0..0xbf0 (~0x30 bytes). */
static int trainercase_bc0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x208 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xc00, body spans 0xc00..0xc30 (~0x30 bytes). */
static int trainercase_c00(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x208 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xc38, body spans 0xc38..0xf2c (~0x2f4 bytes). */
static int trainercase_c38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x210, 0x218, 0x220, 0xf48, 0x1e0, 0x228, 0x230, 0x238, ... (30 total) */
    /* Field offsets touched: +0x04, +0x08, +0x34, +0x74, +0x84, +0x90, +0x94, +0xac, +0xb0, +0x164, +0x198 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0xf48, body spans 0xf48..0x10c8 (~0x180 bytes). */
static int trainercase_f48(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x288, 0x1e0, 0x230, 0x290, 0x298, 0x2a0, 0x2a8, 0x2b0, ... (12 total) */
    /* Field offsets touched: +0x04, +0x10, +0x74, +0xa0, +0xb0 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x10f0, body spans 0x10f0..0x11fc (~0x10c bytes). */
static int trainercase_10f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2c0, 0x2c8, 0x238, 0x2d0, 0x1b8, 0x2d8, 0x238, 0x2d0, ... (11 total) */
    /* Field offsets touched: +0x04, +0x08, +0x20, +0x74, +0x190 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x1204, body spans 0x1204..0x17ac (~0x5a8 bytes). */
static int trainercase_1204(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e8, 0x2e8, 0x2f0, 0x2f8, 0x2e8, 0x300, 0x2f0, 0x308, ... (68 total) */
    /* Field offsets touched: +0x04, +0x18, +0x1c, +0x5c, +0x74, +0x164, +0x168 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x17cc, body spans 0x17cc..0x189c (~0xd0 bytes). */
static int trainercase_17cc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x388, 0x390, 0x2f0, 0x308, 0x2f0, 0x308, 0x2e8, 0x2e8 */
    /* Field offsets touched: +0x5c, +0x6c, +0x74, +0x168, +0x16e */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x18a0, body spans 0x18a0..0x1acc (~0x22c bytes). */
static int trainercase_18a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x398, 0x1b8, 0x1b8, 0x3a0, 0x3a8, 0x3b0, 0x3b8, 0x3c0, ... (10 total) */
    /* Field offsets touched: +0x0c, +0x18, +0x1c, +0x48, +0x74, +0x78, +0x90, +0x99, +0xa4, +0x16f, +0x198, +0x19c, +0x1bc, +0x1c0 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x1ae0, body spans 0x1ae0..0x1b8c (~0xac bytes). */
static int trainercase_1ae0(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x0c, +0x1c, +0x20, +0x24, +0x28, +0x30, +0x34, +0x38, +0x3c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x1b90, body spans 0x1b90..0x1d4c (~0x1bc bytes). */
static int trainercase_1b90(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x1e0, 0x1e0 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x14, +0x2c, +0x34, +0x38, +0x3c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x1d58, body spans 0x1d58..0x1ee4 (~0x18c bytes). */
static int trainercase_1d58(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x400, 0x408, 0x410, 0x1b8, 0x1e0, 0x420, 0x1e0, ... (12 total) */
    /* Field offsets touched: +0x04, +0x08, +0x10, +0x38, +0x78, +0x108, +0x170, +0x174, +0x178, +0x17c, +0x180, +0x19c, +0x1e4 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x1ee8, body spans 0x1ee8..0x1fac (~0xc4 bytes). */
static int trainercase_1ee8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x438, 0x440 */
    /* Field offsets touched: +0x04, +0x38, +0x78, +0x170, +0x178, +0x17c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x1fb4, body spans 0x1fb4..0x2044 (~0x90 bytes). */
static int trainercase_1fb4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c0, 0x448, 0x1d58 */
    /* Field offsets touched: +0x1c, +0x74, +0x78, +0xa4, +0x16f */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x2054, body spans 0x2054..0x21f8 (~0x1a4 bytes). */
static int trainercase_2054(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x450, 0x458, 0x460, 0x460, 0x190, 0x190 */
    /* Field offsets touched: +0x0c, +0x11, +0x14, +0x18, +0x1c, +0x24, +0x28, +0x5c, +0x80, +0x84, +0x88 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x2210, body spans 0x2210..0x248c (~0x27c bytes). */
static int trainercase_2210(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x238, 0x470, 0x1fb4, 0x258, 0x318, 0x258, 0x260, ... (23 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x48, +0x5c, +0x74, +0x78, +0xa0, +0xa4, +0xac, +0x199 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x24b0, body spans 0x24b0..0x2590 (~0xe0 bytes). */
static int trainercase_24b0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x488, 0x258, 0x260, 0x258, 0x260, 0x258, 0x260, 0x2210, ... (11 total) */
    /* Field offsets touched: +0x0c, +0x48, +0x78, +0xa0, +0xa4, +0x199 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x2598, body spans 0x2598..0x2630 (~0x98 bytes). */
static int trainercase_2598(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x258, 0x260, 0x258, 0x260, 0x490 */
    /* Field offsets touched: +0x98, +0x9c, +0x9d, +0xb0, +0x19a */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x2638, body spans 0x2638..0x2714 (~0xdc bytes). */
static int trainercase_2638(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3d0, 0x3d8, 0x3d0, 0x3e0, 0x3e8, 0x3f0, 0x3f8 */
    /* Field offsets touched: +0x04, +0x30, +0x38, +0x58, +0x5c, +0x78, +0x88, +0xa0 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x271c, body spans 0x271c..0x2bac (~0x490 bytes). */
static int trainercase_271c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x18a0, 0x17cc, 0x498, 0x4a0, 0x4a8, 0x4b0, 0x4b8, 0x4c0, ... (42 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x1c, +0x2c, +0x38, +0x74, +0x78, +0x88, +0x8c, +0x98, +0x9a, +0x9c, +0x9d, +0xa0, +0xa4, +0xb1, +0xe4 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x2bb4, body spans 0x2bb4..0x2f38 (~0x384 bytes). */
static int trainercase_2bb4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x538, 0x1e0, 0x400, 0x540, 0x2c0, 0x548, 0x550, ... (26 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x34, +0x38, +0x58, +0x74, +0x78, +0x7c, +0x8c, +0x90, +0x98, +0x9c, +0xa8 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3000, body spans 0x3000..0x3258 (~0x258 bytes). */
static int trainercase_3000(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x500, 0x5f0, 0x398, 0x1ee8, 0x5f8, 0x600, 0x5f0, ... (27 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x18, +0x38, +0x78, +0x7c, +0x84, +0x8c, +0x90, +0x98, +0xa0, +0x194 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3260, body spans 0x3260..0x3358 (~0xf8 bytes). */
static int trainercase_3260(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x680, 0x2210, 0x680, 0x2210, 0x680, 0x680, 0x2210 */
    /* Field offsets touched: +0xa4 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x335c, body spans 0x335c..0x3490 (~0x134 bytes). */
static int trainercase_335c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x688, 0x690, 0x690, 0x1e0, 0x698, 0x1e0, 0x6a0 */
    /* Field offsets touched: +0x04, +0x74, +0x88, +0x90, +0x9c, +0x9d, +0xa0, +0xa4, +0xa8, +0xb1, +0xb4, +0xdc, +0xe4, +0xe8, +0xec, +0xf0, +0xf4, +0x11c, +0x124, +0x128, +0x12c, +0x130, +0x164, +0x168, +0x170, +0x174, +0x178, +0x17c, +0x180, +0x190, +0x194, +0x198 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x34a0, body spans 0x34a0..0x34a8 (~0x8 bytes). */
static int trainercase_34a0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x34b0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x34b0, body spans 0x34b0..0x35c4 (~0x114 bytes). */
static int trainercase_34b0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a0 */
    /* Field offsets touched: +0x04, +0x34, +0x38, +0x3c, +0xf4, +0x164, +0x190, +0x19c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x35d4, body spans 0x35d4..0x3700 (~0x12c bytes). */
static int trainercase_35d4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1e0, 0x6b0, 0x6b8, 0x335c, 0x1e0, 0x1e0, 0x6c0, 0xc38, ... (10 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x14, +0x18, +0x1c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3718, body spans 0x3718..0x3784 (~0x6c bytes). */
static int trainercase_3718(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8, 0x2054, 0x2054 */
    /* Field offsets touched: +0x08, +0x11 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3790, body spans 0x3790..0x3798 (~0x8 bytes). */
static int trainercase_3790(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x6d0 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x37e4, body spans 0x37e4..0x3810 (~0x2c bytes). */
static int trainercase_37e4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x208 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x381c, body spans 0x381c..0x3848 (~0x2c bytes). */
static int trainercase_381c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x208 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3858, body spans 0x3858..0x3888 (~0x30 bytes). */
static int trainercase_3858(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x208 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3894, body spans 0x3894..0x38c4 (~0x30 bytes). */
static int trainercase_3894(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x208 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x38cc, body spans 0x38cc..0x39b0 (~0xe4 bytes). */
static int trainercase_38cc(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x08 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3a0c, body spans 0x3a0c..0x3a88 (~0x7c bytes). */
static int trainercase_3a0c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3b24, body spans 0x3b24..0x3b78 (~0x54 bytes). */
static int trainercase_3b24(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x34, +0x38, +0x3c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3b80, body spans 0x3b80..0x3bd8 (~0x58 bytes). */
static int trainercase_3b80(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x34, +0x38, +0x3c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* CRO 0x3be4, body spans 0x3be4..0x3c40 (~0x5c bytes). */
static int trainercase_3be4(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x34, +0x38, +0x3c */
    /* Concrete body not yet decoded; see DllTrainerCase.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x3884 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x3884..; BL targets: 0x200, 0x208 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 47 candidate function boundaries (push/pop pairing).
 * Total BL sites: 381 (to imports: 341, internal: 40).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */