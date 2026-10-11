/*
 * Preliminary decompilation of DllColosseum.cro.
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

/* Module summary (from DllColosseum.cro header):
 *   file size: 0x8000
 *   code:      offset 0x180  size 0x5e80
 *   data:      offset 0x74a8  size 0x54
 *   bss:       size  0x80
 *   imports module: 1 (anonymous import slots: 0)
 *   external patches: 153
 *   import veneers (ldr pc,[pc,#N]): 134 at 0x180..0x5a8
 *   total BL sites: 487 (to imports: 415, internal: 72)
 */

/* Forward declarations for derived structures */
typedef struct ModuleActor ModuleActor;
typedef struct ModuleWork ModuleWork;

/* Per-module work area reference layout (observed offsets hit by ldr/str):
 *   +0x08 (hit 89x)
 *   +0x0c (hit 56x)
 *   +0x28 (hit 44x)
 *   +0x04 (hit 43x)
 *   +0x10 (hit 42x)
 *   +0x5c (hit 37x)
 *   +0x14 (hit 36x)
 *   +0x2c (hit 27x)
 *   +0x24 (hit 21x)
 *   +0x34 (hit 20x)
 *   +0x84 (hit 19x)
 *   +0x18 (hit 14x)
 *   +0x88 (hit 14x)
 *   +0x78 (hit 14x)
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
 *   CRO 0x05c0..0x0950  BL(local=0, imp=7)
 *   CRO 0x0954..0x0a24  BL(local=0, imp=3)
 *   CRO 0x0a34..0x0a6c  BL(local=0, imp=1)
 *   CRO 0x0a78..0x0ab4  BL(local=0, imp=1)
 *   CRO 0x0abc..0x0af8  BL(local=0, imp=2)
 *   CRO 0x0afc..0x0b70  BL(local=0, imp=3)
 *   CRO 0x0b74..0x1628  BL(local=22, imp=64)
 *   CRO 0x1630..0x1974  BL(local=14, imp=7)
 *   CRO 0x197c..0x1a24  BL(local=2, imp=7)
 *   CRO 0x1aa0..0x1bc4  BL(local=2, imp=16)
 *   CRO 0x1bcc..0x1c90  BL(local=0, imp=3)
 *   CRO 0x1c94..0x1d7c  BL(local=0, imp=1)
 *   CRO 0x1d8c..0x1f64  BL(local=0, imp=10)
 *   CRO 0x1f88..0x2340  BL(local=1, imp=32)
 *   CRO 0x2370..0x24bc  BL(local=2, imp=11)
 *   CRO 0x24c8..0x2558  BL(local=1, imp=5)
 *   CRO 0x2560..0x25bc  BL(local=0, imp=2)
 *   CRO 0x25c8..0x26b0  BL(local=0, imp=6)
 *   CRO 0x26c4..0x276c  BL(local=0, imp=2)
 *   CRO 0x2778..0x2a20  BL(local=3, imp=29)
 *   CRO 0x2a24..0x2bd8  BL(local=2, imp=3)
 *   CRO 0x2be0..0x2cf8  BL(local=3, imp=4)
 *   CRO 0x2d0c..0x2e28  BL(local=2, imp=3)
 *   CRO 0x2e2c..0x3028  BL(local=4, imp=8)
 *   CRO 0x3030..0x31e4  BL(local=0, imp=11)
 *   CRO 0x31f0..0x3230  BL(local=1, imp=1)
 *   CRO 0x3240..0x3288  BL(local=1, imp=1)
 *   CRO 0x3290..0x34b8  BL(local=0, imp=30)
 *   CRO 0x34cc..0x3740  BL(local=0, imp=26)
 *   CRO 0x3754..0x38bc  BL(local=0, imp=6)
 *   CRO 0x38fc..0x3a30  BL(local=0, imp=9)
 *   CRO 0x3a58..0x3b50  BL(local=1, imp=12)
 *   CRO 0x3b58..0x3cc8  BL(local=1, imp=14)
 *   CRO 0x3cd0..0x3d64  BL(local=0, imp=3)
 *   CRO 0x3dc0..0x3e20  BL(local=0, imp=4)
 *   CRO 0x3e24..0x4010  BL(local=2, imp=16)
 *   CRO 0x4018..0x4324  BL(local=4, imp=26)
 *   CRO 0x4344..0x43d0  BL(local=0, imp=5)
 *   CRO 0x43e0..0x4468  BL(local=0, imp=4)
 *   CRO 0x4474..0x4498  BL(local=1, imp=0)
 *   CRO 0x44c8..0x455c  BL(local=0, imp=3)
 *   CRO 0x4564..0x45b0  BL(local=0, imp=3) [contains export: _ZN9xy_system2bg6System13SetIsCallDrawEb]
 *   CRO 0x45bc..0x4618  BL(local=0, imp=2)
 *   CRO 0x4628..0x4680  BL(local=0, imp=2) [contains export: nnroControlObject_]
 *   CRO 0x4690..0x46bc  BL(local=0, imp=1)
 *   CRO 0x46c8..0x46f4  BL(local=0, imp=1)
 *   CRO 0x47dc..0x4858  BL(local=0, imp=0)
 */

/* CRO 0x5c0, body spans 0x5c0..0x950 (~0x390 bytes). */
static int colosseum_5c0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x180, 0x188, 0x198, 0x198, 0x198, 0x198, 0x198 */
    /* Field offsets touched: +0x01, +0x02, +0x04, +0x06, +0x08, +0x0a, +0x0c, +0x10, +0x11, +0x12, +0x13, +0x14, +0x15, +0x18, +0x1c, +0x1d, +0x20, +0x24, +0x26, +0x2a */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x954, body spans 0x954..0xa24 (~0xd0 bytes). */
static int colosseum_954(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a0, 0x1a8, 0x1b0 */
    /* Field offsets touched: +0x08, +0x0c, +0x10, +0x11, +0x12, +0x13, +0x14, +0x15, +0x18, +0x1c, +0x1d, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40, +0x44, +0x48, +0x4c, +0x50, +0x54 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0xa34, body spans 0xa34..0xa6c (~0x38 bytes). */
static int colosseum_a34(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8 */
    /* Field offsets touched: +0x04, +0x08 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0xa78, body spans 0xa78..0xab4 (~0x3c bytes). */
static int colosseum_a78(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1b8 */
    /* Field offsets touched: +0x04, +0x08 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0xabc, body spans 0xabc..0xaf8 (~0x3c bytes). */
static int colosseum_abc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c8, 0x1c8 */
    /* Field offsets touched: +0x08, +0x4c, +0x5c, +0xa8 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0xafc, body spans 0xafc..0xb70 (~0x74 bytes). */
static int colosseum_afc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c8, 0x1c8, 0x1d0 */
    /* Field offsets touched: +0x08, +0x2c, +0x4c, +0x5c, +0x98, +0xa8 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0xb74, body spans 0xb74..0x1628 (~0xab4 bytes). */
static int colosseum_b74(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1d8, 0x1e0, 0x1d8, 0x1e8, 0x1f0, 0x1d8, 0x1f8, 0x200, ... (86 total) */
    /* Field offsets touched: +0x02, +0x04, +0x08, +0x0c, +0x10, +0x14, +0x15, +0x18, +0x1c, +0x24, +0x28, +0x2a, +0x2c, +0x2d, +0x2e, +0x36, +0x44, +0x45, +0x46, +0x5c, +0x68, +0x6c, +0x70, +0x74, +0x78, +0x7c, +0x84, +0x86, +0x88, +0x8c, +0x90, +0x98, +0xa8, +0xaf, +0xe0, +0x184 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x1630, body spans 0x1630..0x1974 (~0x344 bytes). */
static int colosseum_1630(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1c8, 0x1c8, 0x2370, 0x1aa0, 0x2e2c, 0x1aa0, 0x2778, 0x1aa0, ... (21 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x28, +0x2c, +0x2e, +0x4c, +0x5c, +0x78, +0xa0, +0xa8 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x197c, body spans 0x197c..0x1a24 (~0xa8 bytes). */
static int colosseum_197c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x250, 0x258, 0x250, 0x258, 0x2560, 0x250, 0x308, 0x248, ... (9 total) */
    /* Field offsets touched: +0x78, +0xa0, +0xa4, +0xac */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x1aa0, body spans 0x1aa0..0x1bc4 (~0x124 bytes). */
static int colosseum_1aa0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x250, 0x308, 0x250, 0x308, 0x250, 0x308, 0x250, 0x308, ... (18 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x10, +0x1d, +0x28, +0x2c, +0x90 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x1bcc, body spans 0x1bcc..0x1c90 (~0xc4 bytes). */
static int colosseum_1bcc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x298, 0x310, 0x318 */
    /* Field offsets touched: +0x04, +0x08, +0x18, +0x8c, +0x90 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x1c94, body spans 0x1c94..0x1d7c (~0xe8 bytes). */
static int colosseum_1c94(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x280 */
    /* Field offsets touched: (none) */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x1d8c, body spans 0x1d8c..0x1f64 (~0x1d8 bytes). */
static int colosseum_1d8c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x198, 0x198, 0x320, 0x328, 0x330, 0x338, 0x340, ... (10 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x28, +0x5c, +0x78, +0xad */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x1f88, body spans 0x1f88..0x2340 (~0x3b8 bytes). */
static int colosseum_1f88(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x350, 0x1a0, 0x4018, 0x358, 0x1a0, 0x360, 0x368, 0x370, ... (33 total) */
    /* Field offsets touched: +0x08, +0x14, +0x18, +0x28, +0x2c, +0x2d, +0x34, +0x5c, +0x7c, +0x8c, +0xad, +0xae */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2370, body spans 0x2370..0x24bc (~0x14c bytes). */
static int colosseum_2370(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2560, 0x248, 0x250, 0x308, 0x250, 0x258, 0x250, 0x258, ... (13 total) */
    /* Field offsets touched: +0x08, +0x2c, +0x84, +0xa0, +0xa4, +0xac, +0xad, +0xaf */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x24c8, body spans 0x24c8..0x2558 (~0x90 bytes). */
static int colosseum_24c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x250, 0x258, 0x250, 0x258, 0x248, 0x25c8 */
    /* Field offsets touched: +0xa4, +0xac, +0xad */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2560, body spans 0x2560..0x25bc (~0x5c bytes). */
static int colosseum_2560(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x398, 0x3a0 */
    /* Field offsets touched: +0x5c, +0xa0, +0xa8 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x25c8, body spans 0x25c8..0x26b0 (~0xe8 bytes). */
static int colosseum_25c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x380, 0x3c0, 0x3c8, 0x3d0, 0x240, 0x210 */
    /* Field offsets touched: +0x04, +0x10, +0x78, +0xa0 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x26c4, body spans 0x26c4..0x276c (~0xa8 bytes). */
static int colosseum_26c4(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x198, 0x3d8 */
    /* Field offsets touched: +0x08, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x44, +0x54 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2778, body spans 0x2778..0x2a20 (~0x2a8 bytes). */
static int colosseum_2778(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2a8, 0x2b0, 0x1a0, 0x2b8, 0x2c0, 0x2c8, 0x220, 0x2d0, ... (32 total) */
    /* Field offsets touched: +0x01, +0x04, +0x08, +0x0a, +0x10, +0x14, +0x18, +0x28, +0x2c, +0x78, +0x80, +0xa0, +0xa4, +0xac, +0xad */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2a24, body spans 0x2a24..0x2bd8 (~0x1b4 bytes). */
static int colosseum_2a24(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x26c4, 0x197c, 0x210, 0x218, 0x280 */
    /* Field offsets touched: +0x08, +0x0c, +0x10, +0x24, +0x25, +0x2c, +0x34, +0x35, +0x44, +0x45, +0x90 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2be0, body spans 0x2be0..0x2cf8 (~0x118 bytes). */
static int colosseum_2be0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3e0, 0x26c4, 0x3e0, 0x26c4, 0x190, 0x197c, 0x278 */
    /* Field offsets touched: +0x08, +0x0c, +0x24, +0x28, +0x2c, +0x2e, +0x34, +0x3e, +0x44, +0x4e */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2d0c, body spans 0x2d0c..0x2e28 (~0x11c bytes). */
static int colosseum_2d0c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0xb74, 0x228, 0x3d8, 0x3f0, 0x5c0 */
    /* Field offsets touched: +0x08, +0x0c, +0x1d, +0x20, +0x30, +0x34, +0x44, +0x48, +0x4c, +0x50, +0x54, +0x8c */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x2e2c, body spans 0x2e2c..0x3028 (~0x1fc bytes). */
static int colosseum_2e2c(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3f8, 0x3a58, 0x3b58, 0x2560, 0x248, 0x2560, 0x248, 0x1f0, ... (12 total) */
    /* Field offsets touched: +0x08, +0x10, +0x14, +0x28, +0x2c, +0x2d, +0xa4, +0xac, +0xad */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3030, body spans 0x3030..0x31e4 (~0x1b4 bytes). */
static int colosseum_3030(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x400, 0x380, 0x3b0, 0x3b8, 0x380, 0x3b0, 0x3b8, 0x250, ... (11 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x1c, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x40, +0x44, +0x50, +0x5c, +0x7c, +0x88 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x31f0, body spans 0x31f0..0x3230 (~0x40 bytes). */
static int colosseum_31f0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1bcc, 0x408 */
    /* Field offsets touched: +0x04, +0x0c */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3240, body spans 0x3240..0x3288 (~0x48 bytes). */
static int colosseum_3240(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1bcc, 0x408 */
    /* Field offsets touched: +0x04, +0x0c */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3290, body spans 0x3290..0x34b8 (~0x228 bytes). */
static int colosseum_3290(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x250, 0x410, 0x250, 0x308, 0x250, 0x308, 0x250, 0x308, ... (30 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x88 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x34cc, body spans 0x34cc..0x3740 (~0x274 bytes). */
static int colosseum_34cc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x248, 0x248, 0x248, 0x248, 0x248, 0x248, 0x248, 0x248, ... (26 total) */
    /* Field offsets touched: +0x80 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3754, body spans 0x3754..0x38bc (~0x168 bytes). */
static int colosseum_3754(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x450, 0x458, 0x460, 0x468, 0x470, 0x1a0 */
    /* Field offsets touched: +0x04, +0x08, +0x10, +0x20, +0x5c, +0x84, +0xa0, +0xaf */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x38fc, body spans 0x38fc..0x3a30 (~0x134 bytes). */
static int colosseum_38fc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x380, 0x480, 0x380, 0x480, 0x480, 0x480, 0x480, 0x480, ... (9 total) */
    /* Field offsets touched: +0x08, +0x0c, +0x10, +0x14, +0x18 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3a58, body spans 0x3a58..0x3b50 (~0xf8 bytes). */
static int colosseum_3a58(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x490, 0x498, 0x3290, 0x250, 0x308, 0x250, 0x308, 0x250, ... (13 total) */
    /* Field offsets touched: +0x78, +0x7c, +0x80, +0x84, +0x88 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3b58, body spans 0x3b58..0x3cc8 (~0x170 bytes). */
static int colosseum_3b58(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x3f8, 0x4a0, 0x4a8, 0x4b0, 0x3290, 0x250, 0x308, 0x250, ... (15 total) */
    /* Field offsets touched: +0x04, +0x08, +0x0c, +0x10, +0x78 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3cd0, body spans 0x3cd0..0x3d64 (~0x94 bytes). */
static int colosseum_3cd0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4b8, 0x308, 0x398 */
    /* Field offsets touched: +0x5c, +0x8c, +0x90, +0xad */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3dc0, body spans 0x3dc0..0x3e20 (~0x60 bytes). */
static int colosseum_3dc0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4c0, 0x4c0, 0x4c0, 0x4c0 */
    /* Field offsets touched: +0x58, +0x5c, +0x84 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x3e24, body spans 0x3e24..0x4010 (~0x1ec bytes). */
static int colosseum_3e24(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4d0, 0x1c8, 0x1c8, 0x460, 0x1c8, 0x1c8, 0x250, 0x258, ... (18 total) */
    /* Field offsets touched: +0x04, +0x5c, +0x84, +0x8c, +0xa0, +0xa4, +0xa8, +0xac, +0xad, +0xae, +0xaf, +0xe0 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x4018, body spans 0x4018..0x4324 (~0x30c bytes). */
static int colosseum_4018(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x4f8, 0x500, 0x508, 0x510, 0x518, 0x520, 0x1a0, 0x528, ... (30 total) */
    /* Field offsets touched: +0x04, +0x08, +0x10, +0x5c, +0x78, +0x7c, +0x80, +0x84, +0x88, +0xad, +0xe0 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x4344, body spans 0x4344..0x43d0 (~0x8c bytes). */
static int colosseum_4344(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x558, 0x560, 0x568, 0x570, 0x578 */
    /* Field offsets touched: +0x04, +0x7c, +0x80, +0x88 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x43e0, body spans 0x43e0..0x4468 (~0x88 bytes). */
static int colosseum_43e0(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x558, 0x560, 0x568, 0x570 */
    /* Field offsets touched: +0x04, +0x7c, +0x80, +0x88 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x4474, body spans 0x4474..0x4498 (~0x24 bytes). */
static int colosseum_4474(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x2d0c */
    /* Field offsets touched: +0x24 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x44c8, body spans 0x44c8..0x455c (~0x94 bytes). */
static int colosseum_44c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x1a0, 0x580, 0x588 */
    /* Field offsets touched: +0x08, +0x20, +0x24, +0x2c, +0x2d, +0x2e, +0x30, +0x34, +0x88, +0x8c, +0x98 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x4564, body spans 0x4564..0x45b0 (~0x4c bytes). */
static int colosseum_4564(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x590, 0x200, 0x598 */
    /* Field offsets touched: +0x04, +0x20 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x45bc, body spans 0x45bc..0x4618 (~0x5c bytes). */
static int colosseum_45bc(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5a0, 0x5a8 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x4628, body spans 0x4628..0x4680 (~0x58 bytes). */
static int colosseum_4628(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5a0, 0x5a8 */
    /* Field offsets touched: +0x14, +0x20, +0x24 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x4690, body spans 0x4690..0x46bc (~0x2c bytes). */
static int colosseum_4690(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5a8 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x46c8, body spans 0x46c8..0x46f4 (~0x2c bytes). */
static int colosseum_46c8(ModuleActor *self) {
    (void)self;
    /* BL targets: 0x5a8 */
    /* Field offsets touched: +0x14 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* CRO 0x47dc, body spans 0x47dc..0x4858 (~0x7c bytes). */
static int colosseum_47dc(ModuleActor *self) {
    (void)self;
    /* BL targets:  */
    /* Field offsets touched: +0x04 */
    /* Concrete body not yet decoded; see DllColosseum.cro disassembly. */
    return 1;
}

/* ===== Named exports ===== */

/* CRO 0x4654 (segment 0) — nnroControlObject_ */
int nnroControlObject_(ModuleActor *self) {
    (void)self;
    /* Body spans 0x4654..; BL targets: 0x5a0, 0x5a8 */
    /* TODO: not yet decoded */
    return 1;
}

/* CRO 0x457c (segment 0) — _ZN9xy_system2bg6System13SetIsCallDrawEb */
int _ZN9xy_system2bg6System13SetIsCallDrawEb(ModuleActor *self) {
    (void)self;
    /* Body spans 0x457c..; BL targets: 0x200, 0x598 */
    /* TODO: not yet decoded */
    return 1;
}

/* Summary: 47 candidate function boundaries (push/pop pairing).
 * Total BL sites: 487 (to imports: 415, internal: 72).
 * This preliminary reconstruction documents structure only; rebinding call
 * targets to named slots in other CROs requires resolving the loader patch table,
 * which is outside the scope of this file.
 */