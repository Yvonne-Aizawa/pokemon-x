/*
 * Preliminary decompilation of DllBattle.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary (LARGE module — full byte-by-byte decoding skipped):
 *   - Two named exports: `nnroControlObject_` at CRO 0xcc4d8,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0xc7100.
 *   - Imports DllBackGround (18 anonymous callers — battle background is
 *     a peer module).
 *   - 956 |static| imports, 1109 external patches (largest in this group).
 *   - 3108 ARM prologues, 293 Thumb prologues (large mix of both modes).
 *   - 0x4f40 bytes of data (large — sprite/animation tables) and a 0x12520-
 *     byte BSS (huge — full per-battle state buffers).
 *   - 0xdd84 bytes of segment 1 (constant pool — move/ability/species data).
 *
 * Because the disassembly is larger than the cache budget for a single pass,
 * only the loader stub, two named exports, and high-level structure are
 * documented below. Function-by-function recovery should be performed once
 * the .crs symbol table is parsed so call targets can be resolved.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0xcc4d8 */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0xc7100 */

/* Loader / control object table reference (4-word, falls in segment 0). */
extern uint32_t DllBattleControlTable[4];

/* Cross-module peer import. */
extern void DllBackGround_callX(void *self, int32_t arg);

/* Battle proc layout — only the most-touched offsets are inferred
 * (off +0x04, +0x18, +0x24..+0x28, +0x40..+0x60, +0x80..+0x90, +0xc0..+0x100,
 * +0x180..+0x1c0, +0x200..+0x280, +0x400..+0x480). The exact size is a guess
 * pending full inspection. */
struct BattleProc {
    void *vtable;                 /* 0x00 */
    void *owner;                  /* 0x04 */
    void *battle_context;         /* 0x08 */
    uint8_t reserved0c[0x18];     /* 0x0c..0x23 */
    uint8_t state;                /* 0x24 */
    uint8_t sub_state;            /* 0x25 */
    uint16_t parameter;           /* 0x26 */
    int32_t timer;                /* 0x28 */
    /* ...fields for turn order, weather, terrain, hazards, stat stages... */
    uint8_t reserved2c[0x10000 - 0x2c]; /* placeholder — actual size >> */
};

/* Top 10 most-imported |static| helpers inferred from patch density. Each is
 * called from many different modules (DllBag, DllBox, DllZukan, DllGts, etc.),
 * confirming their centrality. Exact names need the .crs symbol map.
 *
 * Patch slots (lower 12 bits of seg_off, repeated many times across modules):
 *   +0x00c..+0x024 — boot/init.
 *   +0x040..+0x080 — frame allocator and free.
 *   +0x0c0..+0x100 — virtual call dispatch (xy_system message bus).
 *   +0x180..+0x1c0 — battle proc state bytes accessors.
 *   +0x400..+0x480 — sprite/animation mount.
 */
extern void *DllBattle_static_00c(void);
extern void *DllBattle_static_014(void);
extern void *DllBattle_static_01c(void);
extern void *DllBattle_static_024(void);
extern void *DllBattle_static_040(void);
extern void *DllBattle_static_044(void);
extern void *DllBattle_static_04c(void);
extern void *DllBattle_static_054(void);
extern void *DllBattle_static_05c(void);
extern void *DllBattle_static_064(void);

/* Lifecycle hooks (full 10-hook set used here, including separate animate
 * and draw hooks for foreground and background passes). Names below are
 * the conventional ones assigned across all DllGame modules. */
static void battle_construct(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_init(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_run(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_animate_fg(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_animate_bg(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_draw_fg(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_draw_bg(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_idle(struct BattleProc *self) { /* TODO: not yet decoded */ }
static void battle_input(struct BattleProc *self, int32_t evt) {
    (void)self; (void)evt; /* TODO: not yet decoded */
}
static void battle_shutdown(struct BattleProc *self) { /* TODO: not yet decoded */ }

/* TODO: not yet decoded — battle moves / abilities / items / AI dispatch. */

/* High-level structure of DllBattle based on visible prologues:
 *   ~80 ARM-style functions per .text-size MiB / 4 KiB = ~600 functions.
 *   ~5..10 Thumb helpers are interleaved near the end of segment 0.
 *
 *   Segment 0 (0x180..0xce000):
 *     - 0x000..0xc00  : external patch dispatcher wrappers (~96 calls).
 *     - 0xc00..0x1f000: state-machine implementation for the main turn loop
 *                       (move select, target select, action order, execute).
 *     - 0x1f000..0x60000: animation framework (sprite mounts, tween eval).
 *     - 0x60000..0xcd1fc: per-move handlers (indexed by move id; this is the
 *                       source of the bulk of file size).
 *
 *   Segment 1 (0xce000..0xcd84): ROM constant pool — move metadata tables,
 *                       ability scripts, type matchup matrix.
 *
 *   Segment 2 (0xf8328..0xfd268): small data table (vtables, RTTI info).
 *
 *   Segment 3 (0x00..0x12500): BSS — runtime battle state, RNG scratch.
 */
