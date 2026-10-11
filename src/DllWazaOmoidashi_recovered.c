/*
 * Preliminary decompilation of DllWazaOmoidashi.cro.
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

/* Module summary (from DllWazaOmoidashi.cro header):
 *   file size: 0x7000
 *   code:      offset 0x180  size 0x4e80
 *   data:      offset 0x66f8  size 0x18c
 *   bss:       size  0x5c
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 187
 *   import veneers (ldr pc,[pc,#N]): 142 at 0x180..0x5e8
 *   total BL sites: 434 (to imports: 387, internal: 47)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x5c (hit 83x)
 *   +0x40 (hit 70x)
 *   +0x04 (hit 53x)
 *   +0x30 (hit 44x)
 *   +0x7c (hit 41x)
 *   +0x3c (hit 31x)
 *   +0x44 (hit 22x)
 *   +0x08 (hit 20x)
 *   +0x9c (hit 18x)
 *   +0x14 (hit 18x)
 *   +0x90 (hit 16x)
 *   +0x28 (hit 15x)
 *   +0x0c (hit 15x)
 *   +0x58 (hit 13x)
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

/* Index: 55 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x05f4..0x0778  BL(local=2, imp=14)
 *   CRO 0x0780..0x0788  BL(local=1, imp=0)
 *   CRO 0x0790..0x0854  BL(local=0, imp=4)
 *   CRO 0x0860..0x091c  BL(local=0, imp=1)
 *   CRO 0x0938..0x09bc  BL(local=0, imp=3)
 *   CRO 0x09e0..0x0a1c  BL(local=0, imp=1)
 *   CRO 0x0a58..0x0b28  BL(local=0, imp=4)
 *   CRO 0x0b30..0x0b78  BL(local=0, imp=1)
 *   CRO 0x0c18..0x0c60  BL(local=0, imp=1)
 *   CRO 0x0d00..0x0d48  BL(local=0, imp=1)
 *   CRO 0x0de8..0x0fe0  BL(local=6, imp=14)
 *   CRO 0x0fe8..0x1140  BL(local=6, imp=7)
 *   CRO 0x1168..0x1414  BL(local=7, imp=19)
 *   CRO 0x142c..0x1584  BL(local=3, imp=10)
 *   CRO 0x15b0..0x1858  BL(local=5, imp=23)
 *   CRO 0x1860..0x18a8  BL(local=0, imp=2)
 *   CRO 0x18d8..0x1a90  BL(local=3, imp=7)
 *   CRO 0x1aa0..0x1aa8  BL(local=1, imp=0)
 *   CRO 0x1ab0..0x1c94  BL(local=0, imp=10)
 *   CRO 0x1c98..0x1d28  BL(local=0, imp=3)
 *   CRO 0x1d3c..0x1d58  BL(local=0, imp=1)
 *   CRO 0x1d60..0x1f08  BL(local=0, imp=20)
 *   CRO 0x1f24..0x1fac  BL(local=0, imp=4)
 *   CRO 0x1fcc..0x21a8  BL(local=0, imp=23)
 *   CRO 0x2248..0x22c4  BL(local=0, imp=5)
 *   CRO 0x22cc..0x2334  BL(local=0, imp=4)
 *   CRO 0x2338..0x2374  BL(local=0, imp=2)
 *   CRO 0x2384..0x23cc  BL(local=0, imp=3)
 *   CRO 0x23e8..0x2438  BL(local=0, imp=3)
 *   CRO 0x2444..0x2480  BL(local=0, imp=2)
 *   CRO 0x2490..0x24cc  BL(local=0, imp=2)
 *   CRO 0x24d8..0x25f8  BL(local=0, imp=8)
 *   CRO 0x2604..0x26b0  BL(local=0, imp=5)
 *   CRO 0x26d4..0x26f8  BL(local=0, imp=0)
 *   CRO 0x26fc..0x27ac  BL(local=0, imp=5)
 *   CRO 0x27c4..0x28e4  BL(local=0, imp=15)
 *   CRO 0x28fc..0x2994  BL(local=0, imp=6)
 *   CRO 0x299c..0x2aa0  BL(local=1, imp=11)
 *   CRO 0x2aa8..0x2d18  BL(local=2, imp=18)
 *   CRO 0x2d38..0x2d40  BL(local=1, imp=0)
 *   CRO 0x2d48..0x2e48  BL(local=0, imp=10)
 *   CRO 0x2e54..0x3338  BL(local=5, imp=67)
 *   CRO 0x338c..0x34a8  BL(local=1, imp=7) [contains export: _ZN9xy_system2bg6System13SetIsCallDrawEb]
 *   CRO 0x34c8..0x34e0  BL(local=0, imp=2)
 *   CRO 0x34ec..0x3508  BL(local=0, imp=1)
 *   CRO 0x352c..0x3558  BL(local=0, imp=1)
 *   CRO 0x3564..0x3590  BL(local=0, imp=1)
 *   CRO 0x35a8..0x35e4  BL(local=0, imp=3)
 *   CRO 0x35ec..0x3728  BL(local=0, imp=15)
 *   CRO 0x3730..0x375c  BL(local=0, imp=1)
 *   CRO 0x376c..0x3790  BL(local=0, imp=0)
 *   CRO 0x3794..0x3840  BL(local=0, imp=5) [contains export: nnroControlObject_]
 *   CRO 0x3850..0x3858  BL(local=1, imp=0)
 *   CRO 0x38a0..0x3958  BL(local=0, imp=0)
 *   CRO 0x39a4..0x3a20  BL(local=0, imp=0)
 */

/* CRO 0x5f4, body spans 0x5f4..0x778 (~0x184 bytes). */
static int wazaomoidashi_5f4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x188, 0x190, 0x198, 0x190, 0x1a0, 0x190, 0x1b0, ... (16 total) */
    /* Field offsets touched: +0x04, +0x58, +0x5c, +0x74, +0x78, +0x7c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x780, body spans 0x780..0x788 (~0x8 bytes). */
static int wazaomoidashi_780(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x790 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x790, body spans 0x790..0x854 (~0xc4 bytes). */
static int wazaomoidashi_790(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d0, 0x1d0, 0x1d8, 0x1e0 */
    /* Field offsets touched: +0x04, +0x18, +0x5c, +0x78, +0x7c, +0x80, +0x84 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x860, body spans 0x860..0x91c (~0xbc bytes). */
static int wazaomoidashi_860(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f0 */
    /* Field offsets touched: +0x30, +0x34, +0x38, +0x40, +0x44, +0x5c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x938, body spans 0x938..0x9bc (~0x84 bytes). */
static int wazaomoidashi_938(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8, 0x200, 0x208 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x9e0, body spans 0x9e0..0xa1c (~0x3c bytes). */
static int wazaomoidashi_9e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0xa58, body spans 0xa58..0xb28 (~0xd0 bytes). */
static int wazaomoidashi_a58(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8, 0x220, 0x220, 0x220 */
    /* Field offsets touched: +0x40, +0x44, +0x48, +0x49, +0x4c, +0x50, +0x7c, +0x90, +0xa1 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0xb30, body spans 0xb30..0xb78 (~0x48 bytes). */
static int wazaomoidashi_b30(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0xc18, body spans 0xc18..0xc60 (~0x48 bytes). */
static int wazaomoidashi_c18(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0xd00, body spans 0xd00..0xd48 (~0x48 bytes). */
static int wazaomoidashi_d00(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0xde8, body spans 0xde8..0xfe0 (~0x1f8 bytes). */
static int wazaomoidashi_de8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x228, 0x230, 0x238, 0x2384, 0x2338, 0x240, 0x248, 0x250, ... (20 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x0e, +0x3c, +0x40, +0x44, +0x54, +0x58, +0x5c, +0x7c, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0xfe8, body spans 0xfe8..0x1140 (~0x158 bytes). */
static int wazaomoidashi_fe8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8, 0x2248, 0x228, 0x230, 0x238, 0x2384, 0x2338, 0x240, ... (13 total) */
    /* Field offsets touched: +0x04, +0x24, +0x28, +0x3c, +0x40, +0x44, +0x5c, +0x7c, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1168, body spans 0x1168..0x1414 (~0x2ac bytes). */
static int wazaomoidashi_1168(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2248, 0x228, 0x230, 0x258, 0x2384, 0x2338, 0x240, 0x248, ... (26 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x0e, +0x24, +0x28, +0x3c, +0x40, +0x44, +0x54, +0x58, +0x5c, +0x7c, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x142c, body spans 0x142c..0x1584 (~0x158 bytes). */
static int wazaomoidashi_142c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f8, 0x228, 0x230, 0x238, 0x228, 0x230, 0x258, 0x2384, ... (13 total) */
    /* Field offsets touched: +0x04, +0x0e, +0x34, +0x38, +0x3c, +0x40, +0x44, +0x5c, +0x7c, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x15b0, body spans 0x15b0..0x1858 (~0x2a8 bytes). */
static int wazaomoidashi_15b0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x288, 0x228, 0x230, 0x258, 0x2384, 0x2338, 0x240, 0x248, ... (28 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x0e, +0x3c, +0x40, +0x5c, +0x7c, +0x9c, +0xa0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1860, body spans 0x1860..0x18a8 (~0x48 bytes). */
static int wazaomoidashi_1860(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x298, 0x2a0 */
    /* Field offsets touched: +0x40, +0x5c, +0x7c, +0xb0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x18d8, body spans 0x18d8..0x1a90 (~0x1b8 bytes). */
static int wazaomoidashi_18d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b0, 0x2b8, 0x2c0, 0x190, 0x5f4, 0x190, 0x2c8, 0x220, ... (10 total) */
    /* Field offsets touched: +0x04, +0x10, +0x20, +0x24, +0x30, +0x38, +0x3c, +0x40, +0x44, +0x48, +0x49, +0x7c, +0x8c, +0x90, +0xa1 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1aa0, body spans 0x1aa0..0x1aa8 (~0x8 bytes). */
static int wazaomoidashi_1aa0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f20 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1ab0, body spans 0x1ab0..0x1c94 (~0x1e4 bytes). */
static int wazaomoidashi_1ab0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d0, 0x2d8, 0x190, 0x2e0, 0x1f8, 0x2d0, 0x1f8, 0x2d8, ... (10 total) */
    /* Field offsets touched: +0x01, +0x04, +0x0c, +0x0e, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1c98, body spans 0x1c98..0x1d28 (~0x90 bytes). */
static int wazaomoidashi_1c98(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x338, 0x340, 0x348 */
    /* Field offsets touched: +0x5c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1d3c, body spans 0x1d3c..0x1d58 (~0x1c bytes). */
static int wazaomoidashi_1d3c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350 */
    /* Field offsets touched: +0x88 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1d60, body spans 0x1d60..0x1f08 (~0x1a8 bytes). */
static int wazaomoidashi_1d60(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x358, 0x360, 0x368, 0x370, 0x368, 0x370, 0x230, 0x378, ... (20 total) */
    /* Field offsets touched: +0x5c, +0xa8 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1f24, body spans 0x1f24..0x1fac (~0x88 bytes). */
static int wazaomoidashi_1f24(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c8, 0x3a8, 0x3b0, 0x2d0 */
    /* Field offsets touched: +0x14, +0x18, +0x20, +0x38, +0x40, +0x44 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x1fcc, body spans 0x1fcc..0x21a8 (~0x1dc bytes). */
static int wazaomoidashi_1fcc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x288, 0x3b8, 0x3c0, 0x3c0, 0x3c0, 0x3c0, 0x3c0, 0x3c0, ... (23 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x10, +0x14, +0x18, +0x5c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2248, body spans 0x2248..0x22c4 (~0x7c bytes). */
static int wazaomoidashi_2248(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c0, 0x3e0, 0x3e8, 0x3f0, 0x330 */
    /* Field offsets touched: +0x5c, +0x7c, +0x90, +0x98, +0xa1, +0xa4, +0xac, +0xad */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x22cc, body spans 0x22cc..0x2334 (~0x68 bytes). */
static int wazaomoidashi_22cc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3f8, 0x1f8, 0x248, 0x248 */
    /* Field offsets touched: +0x7c, +0x9c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2338, body spans 0x2338..0x2374 (~0x3c bytes). */
static int wazaomoidashi_2338(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c0, 0x3c0 */
    /* Field offsets touched: +0x5c, +0x7c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2384, body spans 0x2384..0x23cc (~0x48 bytes). */
static int wazaomoidashi_2384(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x400, 0x390, 0x408 */
    /* Field offsets touched: +0x5c, +0x7c, +0xa0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x23e8, body spans 0x23e8..0x2438 (~0x50 bytes). */
static int wazaomoidashi_23e8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2b0, 0x2f0, 0x2f8 */
    /* Field offsets touched: +0x20, +0x24, +0x28, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2444, body spans 0x2444..0x2480 (~0x3c bytes). */
static int wazaomoidashi_2444(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x2d0 */
    /* Field offsets touched: +0x14, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2490, body spans 0x2490..0x24cc (~0x3c bytes). */
static int wazaomoidashi_2490(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300, 0x2d0 */
    /* Field offsets touched: +0x14, +0x2c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x24d8, body spans 0x24d8..0x25f8 (~0x120 bytes). */
static int wazaomoidashi_24d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x308, 0x310, 0x190, 0x318, 0x190, 0x320, 0x328, 0x330 */
    /* Field offsets touched: +0x04, +0x18, +0x58, +0x94, +0x98, +0xa4, +0xac, +0x238 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2604, body spans 0x2604..0x26b0 (~0xac bytes). */
static int wazaomoidashi_2604(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x420, 0x428, 0x430, 0x438 */
    /* Field offsets touched: +0x04, +0x0c, +0x80, +0x84, +0xa4 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x26d4, body spans 0x26d4..0x26f8 (~0x24 bytes). */
static int wazaomoidashi_26d4(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x8c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x26fc, body spans 0x26fc..0x27ac (~0xb0 bytes). */
static int wazaomoidashi_26fc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x448, 0x450, 0x458, 0x460, 0x468 */
    /* Field offsets touched: +0x08, +0x8c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x27c4, body spans 0x27c4..0x28e4 (~0x120 bytes). */
static int wazaomoidashi_27c4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x3d8, 0x360, 0x230, 0x258, 0x368, 0x368, 0x368, ... (15 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x5c, +0x88 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x28fc, body spans 0x28fc..0x2994 (~0x98 bytes). */
static int wazaomoidashi_28fc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x478, 0x480, 0x488, 0x490, 0x498, 0x3f0 */
    /* Field offsets touched: +0x24, +0x4c, +0x58, +0x5c, +0x90, +0x94, +0x98, +0x9c, +0xa4, +0xad, +0xb0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x299c, body spans 0x299c..0x2aa0 (~0x104 bytes). */
static int wazaomoidashi_299c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4a8, 0x4b0, 0x4b8, 0x3e0, 0x3e0, 0x4c0, 0x350, 0x1d60, ... (12 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x88, +0x8c, +0x90, +0x94, +0x98, +0xa1, +0xa4, +0xad */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2aa8, body spans 0x2aa8..0x2d18 (~0x270 bytes). */
static int wazaomoidashi_2aa8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x190, 0x4e0, 0x4e8, 0x4f0, 0x4f8, 0x190, 0x310, ... (20 total) */
    /* Field offsets touched: +0x04, +0x18, +0x58, +0x5c, +0x74, +0x78, +0x80, +0x84, +0x88, +0x8c, +0x90, +0x94, +0x98, +0x9c, +0xa1, +0xa8, +0xad, +0xb0 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2d38, body spans 0x2d38..0x2d40 (~0x8 bytes). */
static int wazaomoidashi_2d38(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d48 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2d48, body spans 0x2d48..0x2e48 (~0x100 bytes). */
static int wazaomoidashi_2d48(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x538, 0x1c8, 0x540, 0x1c8, 0x548, 0x1c8, 0x550, 0x558, ... (10 total) */
    /* Field offsets touched: +0x04, +0x18, +0x74, +0x90, +0x94, +0x98, +0x9c, +0xa4, +0xa8 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x2e54, body spans 0x2e54..0x3338 (~0x4e4 bytes). */
static int wazaomoidashi_2e54(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x568, 0x570, 0x578, 0x230, 0x238, 0x368, 0x580, 0x360, ... (72 total) */
    /* Field offsets touched: +0x5c, +0x74 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x338c, body spans 0x338c..0x34a8 (~0x11c bytes). */
static int wazaomoidashi_338c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x428, 0x430, 0x428, 0x430, 0x4f0, 0x4f8, 0x2e54 */
    /* Field offsets touched: +0x04, +0x08, +0x58, +0x5c, +0x74 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x34c8, body spans 0x34c8..0x34e0 (~0x18 bytes). */
static int wazaomoidashi_34c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x560, 0x1e8 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x34ec, body spans 0x34ec..0x3508 (~0x1c bytes). */
static int wazaomoidashi_34ec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x560 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x352c, body spans 0x352c..0x3558 (~0x2c bytes). */
static int wazaomoidashi_352c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d0 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x3564, body spans 0x3564..0x3590 (~0x2c bytes). */
static int wazaomoidashi_3564(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d0 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x35a8, body spans 0x35a8..0x35e4 (~0x3c bytes). */
static int wazaomoidashi_35a8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5e0, 0x5e8, 0x4b8 */
    /* Field offsets touched: +0x94 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x35ec, body spans 0x35ec..0x3728 (~0x13c bytes). */
static int wazaomoidashi_35ec(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x3d8, 0x360, 0x230, 0x258, 0x368, 0x368, 0x368, ... (15 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x5c, +0x88 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x3730, body spans 0x3730..0x375c (~0x2c bytes). */
static int wazaomoidashi_3730(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350 */
    /* Field offsets touched: +0x88 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x376c, body spans 0x376c..0x3790 (~0x24 bytes). */
static int wazaomoidashi_376c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x8c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x3794, body spans 0x3794..0x3840 (~0xac bytes). */
static int wazaomoidashi_3794(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x448, 0x450, 0x458, 0x460, 0x468 */
    /* Field offsets touched: +0x08, +0x8c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x3850, body spans 0x3850..0x3858 (~0x8 bytes). */
static int wazaomoidashi_3850(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1f20 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x38a0, body spans 0x38a0..0x3958 (~0xb8 bytes). */
static int wazaomoidashi_38a0(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x08, +0x10, +0x14, +0x28, +0x3c */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* CRO 0x39a4, body spans 0x39a4..0x3a20 (~0x7c bytes). */
static int wazaomoidashi_39a4(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllWazaOmoidashi.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x381c (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x381c..; BL targets: 0x460, 0x468, 0x1f20 */
    /* TODO: not yet decoded */
    return 1;
}

/* CRO 0x3418 (segment 0) — _ZN9xy_system2bg6System13SetIsCallDrawEb */
int _ZN9xy_system2bg6System13SetIsCallDrawEb(ModuleActor *self) {
    (void)self;
    /* Body spans 0x3418..; BL targets: 0x428, 0x430 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 55 candidate function boundaries (push/pop pairing).
 * Total BL sites: 434 (to imports: 387, internal: 47).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */