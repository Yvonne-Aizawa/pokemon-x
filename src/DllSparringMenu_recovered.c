/*
 * Preliminary decompilation of DllSparringMenu.cro.
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

/* Module summary (from DllSparringMenu.cro header):
 *   file size: 0x9000
 *   code:      offset 0x180  size 0x6e80
 *   data:      offset 0x8728  size 0x1c
 *   bss:       size  0x7c
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 188
 *   import veneers (ldr pc,[pc,#N]): 162 at 0x180..0x688
 *   total BL sites: 594 (to imports: 549, internal: 45)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x04 (hit 276x)
 *   +0x18 (hit 138x)
 *   +0x28 (hit 130x)
 *   +0x0c (hit 100x)
 *   +0x10 (hit 56x)
 *   +0x20 (hit 49x)
 *   +0x54 (hit 47x)
 *   +0x50 (hit 28x)
 *   +0x14 (hit 27x)
 *   +0x08 (hit 23x)
 *   +0x44 (hit 18x)
 *   +0x02 (hit 17x)
 *   +0x1c (hit 17x)
 *   +0x30 (hit 17x)
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

/* Index: 40 ARM prologue-paired functions recovered.
 * Each entry shows start/end, internal vs import-link BL count, and any
 * address reaching a known named export if applicable.
 *
 *   CRO 0x0690..0x15a4  BL(local=5, imp=106)
 *   CRO 0x15c0..0x15d8  BL(local=0, imp=1)
 *   CRO 0x15dc..0x1790  BL(local=5, imp=11)
 *   CRO 0x179c..0x208c  BL(local=8, imp=55)
 *   CRO 0x2098..0x2370  BL(local=2, imp=29)
 *   CRO 0x23dc..0x24d0  BL(local=1, imp=5)
 *   CRO 0x24d8..0x268c  BL(local=0, imp=12)
 *   CRO 0x26a4..0x28c0  BL(local=0, imp=16)
 *   CRO 0x2988..0x29fc  BL(local=0, imp=4)
 *   CRO 0x2a04..0x3080  BL(local=0, imp=54)
 *   CRO 0x30c8..0x324c  BL(local=0, imp=12)
 *   CRO 0x3254..0x34cc  BL(local=3, imp=18)
 *   CRO 0x34f8..0x35f8  BL(local=0, imp=5)
 *   CRO 0x3600..0x372c  BL(local=0, imp=5)
 *   CRO 0x3778..0x3840  BL(local=0, imp=4)
 *   CRO 0x3858..0x3a84  BL(local=0, imp=4)
 *   CRO 0x3a94..0x3aac  BL(local=1, imp=1)
 *   CRO 0x3ab0..0x3be0  BL(local=2, imp=8)
 *   CRO 0x3bf0..0x3f44  BL(local=2, imp=30)
 *   CRO 0x3f64..0x4930  BL(local=8, imp=57)
 *   CRO 0x4938..0x4dd8  BL(local=7, imp=27)
 *   CRO 0x4de4..0x4f68  BL(local=0, imp=3)
 *   CRO 0x4f70..0x5164  BL(local=0, imp=9)
 *   CRO 0x5184..0x5298  BL(local=0, imp=9)
 *   CRO 0x52a8..0x53cc  BL(local=0, imp=5)
 *   CRO 0x53dc..0x560c  BL(local=0, imp=21)
 *   CRO 0x5620..0x56fc  BL(local=0, imp=6)
 *   CRO 0x570c..0x573c  BL(local=0, imp=0)
 *   CRO 0x5748..0x577c  BL(local=0, imp=0)
 *   CRO 0x5784..0x57b0  BL(local=1, imp=1)
 *   CRO 0x57bc..0x5828  BL(local=0, imp=3)
 *   CRO 0x582c..0x5854  BL(local=0, imp=1)
 *   CRO 0x5858..0x58d0  BL(local=0, imp=5)
 *   CRO 0x58dc..0x5934  BL(local=0, imp=4)
 *   CRO 0x5944..0x599c  BL(local=0, imp=4) [contains export: _ZN9xy_system2bg6System13SetIsCallDrawEb]
 *   CRO 0x5a14..0x5a4c  BL(local=0, imp=2)
 *   CRO 0x5a50..0x5a58  BL(local=0, imp=1)
 *   CRO 0x5aa0..0x5acc  BL(local=0, imp=1)
 *   CRO 0x5ad8..0x5b04  BL(local=0, imp=1)
 *   CRO 0x5ca0..0x5d1c  BL(local=0, imp=0)
 */

/* CRO 0x690, body spans 0x690..0x15a4 (~0xf14 bytes). */
static int sparringmenu_690(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x188, 0x188, 0x188, 0x188, 0x190, 0x198, 0x190, ... (111 total) */
    /* Field offsets touched: +0x02, +0x04, +0x08, +0x0a, +0x0c, +0x0e, +0x10, +0x12, +0x14, +0x18, +0x1c, +0x20, +0x28, +0x30, +0x38, +0x40, +0x50, +0x54, +0x5c, +0x60, +0x64, +0x68, +0x69, +0x6c, +0x70, +0x72, +0x73, +0x90, +0x94, +0x128 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x15c0, body spans 0x15c0..0x15d8 (~0x18 bytes). */
static int sparringmenu_15c0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x300 */
    /* Field offsets touched: +0x24 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x15dc, body spans 0x15dc..0x1790 (~0x1b4 bytes). */
static int sparringmenu_15dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2098, 0x2f0, 0x2f0, 0x278, 0x2f8, 0x2f0, 0x308, 0x2f8, ... (16 total) */
    /* Field offsets touched: +0x01, +0x02, +0x04, +0x0c, +0x10, +0x14, +0x18, +0x20, +0x24, +0x28, +0x44, +0x70 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x179c, body spans 0x179c..0x208c (~0x8f0 bytes). */
static int sparringmenu_179c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x330, 0x330, 0x330, 0x30c8, 0x1a0, 0x338, 0x340, 0x30c8, ... (63 total) */
    /* Field offsets touched: +0x01, +0x02, +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x3c, +0x40, +0x44, +0x48, +0x4c, +0x50, +0x54, +0x58, +0x71, +0x80, +0x84, +0x88, +0x100, +0x104 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x2098, body spans 0x2098..0x2370 (~0x2d8 bytes). */
static int sparringmenu_2098(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3c0, 0x2a8, 0x2a8, 0x3c8, 0x3d0, 0x3d8, 0x3e0, 0x3e8, ... (31 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x26, +0x28, +0x30 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x23dc, body spans 0x23dc..0x24d0 (~0xf4 bytes). */
static int sparringmenu_23dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x458, 0x5620, 0x460, 0x468, 0x470, 0x470 */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x28 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x24d8, body spans 0x24d8..0x268c (~0x1b4 bytes). */
static int sparringmenu_24d8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x1b8, 0x1c0, 0x480, 0x200, 0x1b8, 0x1c0, 0x480, ... (12 total) */
    /* Field offsets touched: +0x01, +0x04, +0x08, +0x0c, +0x10, +0x18, +0x1c, +0x20, +0x28, +0x50 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x26a4, body spans 0x26a4..0x28c0 (~0x21c bytes). */
static int sparringmenu_26a4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x200, 0x490, 0x490, 0x498, 0x498, 0x210, 0x200, ... (16 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x20, +0x28, +0x44, +0x70, +0x78, +0x80 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x2988, body spans 0x2988..0x29fc (~0x74 bytes). */
static int sparringmenu_2988(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x198, 0x190, 0x198 */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x2a04, body spans 0x2a04..0x3080 (~0x67c bytes). */
static int sparringmenu_2a04(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x200, 0x190, 0x198, 0x200, 0x200, 0x200, 0x4b0, ... (54 total) */
    /* Field offsets touched: +0x02, +0x04, +0x08, +0x0a, +0x0c, +0x0e, +0x10, +0x18, +0x20, +0x28, +0x4c, +0x50, +0x70, +0x74, +0x78, +0x80 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x30c8, body spans 0x30c8..0x324c (~0x184 bytes). */
static int sparringmenu_30c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x190, 0x198, 0x190, 0x198, 0x190, 0x190, 0x198, 0x190, ... (12 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x18, +0x28 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3254, body spans 0x3254..0x34cc (~0x278 bytes). */
static int sparringmenu_3254(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x26a4, 0x1b0, ... (21 total) */
    /* Field offsets touched: +0x04, +0x08, +0x28, +0x44, +0x48, +0x74, +0x78 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x34f8, body spans 0x34f8..0x35f8 (~0x100 bytes). */
static int sparringmenu_34f8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x208, 0x2f0, 0x2f8, 0x2f0, 0x2f8 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x70 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3600, body spans 0x3600..0x372c (~0x12c bytes). */
static int sparringmenu_3600(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x248, 0x250, 0x4d8, 0x4e0, 0x260 */
    /* Field offsets touched: +0x02, +0x04, +0x94 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3778, body spans 0x3778..0x3840 (~0xc8 bytes). */
static int sparringmenu_3778(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x350, 0x350, 0x350 */
    /* Field offsets touched: +0x04, +0x28 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3858, body spans 0x3858..0x3a84 (~0x22c bytes). */
static int sparringmenu_3858(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x278, 0x2f0, 0x4e8, 0x4e8 */
    /* Field offsets touched: +0x02, +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x20, +0x28, +0x44, +0x48, +0x74, +0x78, +0x7c, +0x80 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3a94, body spans 0x3a94..0x3aac (~0x18 bytes). */
static int sparringmenu_3a94(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x23dc, 0x4f0 */
    /* Field offsets touched: +0x20 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3ab0, body spans 0x3ab0..0x3be0 (~0x130 bytes). */
static int sparringmenu_3ab0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x200, 0x200, 0x498, 0x490, 0x490, 0x330, 0x2988, 0x4a0, ... (10 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x18, +0x28 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3bf0, body spans 0x3bf0..0x3f44 (~0x354 bytes). */
static int sparringmenu_3bf0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x188, 0x188, 0x188, 0x188, 0x190, 0x198, 0x190, 0x198, ... (32 total) */
    /* Field offsets touched: +0x04, +0x10, +0x18, +0x20, +0x28, +0x4c, +0x54 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x3f64, body spans 0x3f64..0x4930 (~0x9cc bytes). */
static int sparringmenu_3f64(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3b8, 0x3600, 0x380, 0x190, 0x198, 0x3b8, 0x190, 0x198, ... (65 total) */
    /* Field offsets touched: +0x01, +0x02, +0x04, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x26, +0x28, +0x54, +0x58, +0x5c, +0x60, +0x68, +0x69, +0x6c, +0x71, +0x72, +0x73, +0x128 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x4938, body spans 0x4938..0x4dd8 (~0x4a0 bytes). */
static int sparringmenu_4938(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x330, 0x2988, 0x4a0, 0x4a8, 0x190, 0x198, 0x190, 0x198, ... (34 total) */
    /* Field offsets touched: +0x02, +0x04, +0x0c, +0x10, +0x14, +0x18, +0x1c, +0x24, +0x28, +0x2c, +0x54, +0x12c */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x4de4, body spans 0x4de4..0x4f68 (~0x184 bytes). */
static int sparringmenu_4de4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x358, 0x540, 0x548 */
    /* Field offsets touched: +0x04, +0x0c, +0x18, +0x1c, +0x20, +0x28, +0x40, +0x48, +0x88, +0x100, +0x104 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x4f70, body spans 0x4f70..0x5164 (~0x1f4 bytes). */
static int sparringmenu_4f70(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x550, 0x550, 0x558, 0x560, 0x558, 0x560, 0x568, 0x568, ... (9 total) */
    /* Field offsets touched: +0x04, +0x48, +0x4c, +0x90, +0x94 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5184, body spans 0x5184..0x5298 (~0x114 bytes). */
static int sparringmenu_5184(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x578, 0x1b8, 0x580, 0x588, 0x590, 0x378, 0x378, ... (9 total) */
    /* Field offsets touched: +0x04, +0x0c, +0x74, +0x84, +0x88, +0x8c */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x52a8, body spans 0x52a8..0x53cc (~0x124 bytes). */
static int sparringmenu_52a8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b0, 0x200, 0x350, 0x598, 0x4b0 */
    /* Field offsets touched: +0x04, +0x10, +0x14, +0x1c, +0x24, +0x26 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x53dc, body spans 0x53dc..0x560c (~0x230 bytes). */
static int sparringmenu_53dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x5a8, 0x5b0, 0x5b8, 0x5c0, 0x5c8, 0x5d0, 0x5d8, ... (21 total) */
    /* Field offsets touched: +0x04, +0x08, +0x18, +0x1c */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5620, body spans 0x5620..0x56fc (~0xdc bytes). */
static int sparringmenu_5620(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x470, 0x608, 0x610, 0x618, 0x620, 0x628 */
    /* Field offsets touched: +0x04, +0x0c, +0x10, +0x18, +0x1c, +0x90 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x570c, body spans 0x570c..0x573c (~0x30 bytes). */
static int sparringmenu_570c(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x18 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5748, body spans 0x5748..0x577c (~0x34 bytes). */
static int sparringmenu_5748(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04, +0x18 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5784, body spans 0x5784..0x57b0 (~0x2c bytes). */
static int sparringmenu_5784(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4de4, 0x630 */
    /* Field offsets touched: +0x24 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x57bc, body spans 0x57bc..0x5828 (~0x6c bytes). */
static int sparringmenu_57bc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x638, 0x638, 0x638 */
    /* Field offsets touched: +0x04, +0x0c, +0x14, +0x18, +0x24, +0x28 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x582c, body spans 0x582c..0x5854 (~0x28 bytes). */
static int sparringmenu_582c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2f8 */
    /* Field offsets touched: +0x04, +0x14, +0x1c, +0x24, +0x1e0 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5858, body spans 0x5858..0x58d0 (~0x78 bytes). */
static int sparringmenu_5858(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x640, 0x648, 0x650, 0x2a8, 0x658 */
    /* Field offsets touched: +0x20, +0x24, +0x28, +0x71, +0x12c */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x58dc, body spans 0x58dc..0x5934 (~0x58 bytes). */
static int sparringmenu_58dc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x660, 0x470, 0x668, 0x670 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5944, body spans 0x5944..0x599c (~0x58 bytes). */
static int sparringmenu_5944(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x660, 0x470, 0x668, 0x670 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5a14, body spans 0x5a14..0x5a4c (~0x38 bytes). */
static int sparringmenu_5a14(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x678, 0x680 */
    /* Field offsets touched: +0x88 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5a50, body spans 0x5a50..0x5a58 (~0x8 bytes). */
static int sparringmenu_5a50(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x688 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5aa0, body spans 0x5aa0..0x5acc (~0x2c bytes). */
static int sparringmenu_5aa0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x670 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5ad8, body spans 0x5ad8..0x5b04 (~0x2c bytes). */
static int sparringmenu_5ad8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x670 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* CRO 0x5ca0, body spans 0x5ca0..0x5d1c (~0x7c bytes). */
static int sparringmenu_5ca0(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllSparringMenu.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x5b18 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x5b18..; BL targets:  */
    /* TODO: not yet decoded */
    return 1;
}

/* CRO 0x598c (segment 0) — _ZN9xy_system2bg6System13SetIsCallDrawEb */
int _ZN9xy_system2bg6System13SetIsCallDrawEb(ModuleActor *self) {
    (void)self;
    /* Body spans 0x598c..; BL targets: 0x670 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 40 candidate function boundaries (push/pop pairing).
 * Total BL sites: 594 (to imports: 549, internal: 45).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */