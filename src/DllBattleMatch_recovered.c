/*
 * Preliminary decompilation of DllBattleMatch.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Single named export: `nnroControlObject_` at CRO 0x1ba10.
 *   - 400 anonymous |static| imports, 564 external patches.
 *   - 579 ARM prologues, 54 Thumb prologues, 50 Thumb epilogues.
 *   - Largest data area is empty (data 0x24, BSS 0x44) — most state lives
 *     in the |static| shared heap.
 *   - Module coordinates "matching" screens: pick-an-opponent UI, link
 *     lobby stanzas, and battle-result transitions.
 */

#include <stdint.h>

/* Named export. */
extern void nnroControlObject_(void);  /* CRO 0x1ba10 */

/* Loader / control object table reference. */
extern uint32_t DllBattleMatchControlTable[4];

/* Strongly-typed forward decls for the 20 most-imported |static| callers.
 * Real names require the linked .crs symbol table; numbers below are the
 * patch slots (lower 12 bits of each patch's segment_offset) used in the
 * disassembly as BL targets.
 */
extern void *DllBattleMatch_static_004c(void);
extern void *DllBattleMatch_static_00ac(void);
extern void *DllBattleMatch_static_0124(void);
extern void *DllBattleMatch_static_0134(void);
extern void *DllBattleMatch_static_0194(void);
extern void *DllBattleMatch_static_01c(void);
extern void *DllBattleMatch_static_01d40(void);
extern void *DllBattleMatch_static_023c(void);
extern void *DllBattleMatch_static_02a4(void);
extern void *DllBattleMatch_static_0344(void);

/* BattleMatch proc layout — inferred from field accesses at +0x04, +0x18,
 * +0x24..+0x28, +0x38..+0x40, +0x7c..+0x84, +0x9c, +0x124. */
struct BattleMatchProc {
    void *vtable;             /* 0x00 */
    void *owner;              /* 0x04 */
    void *partner;            /* 0x08 */
    uint8_t reserved0c[0x10]; /* 0x0c..0x1b */
    uint8_t state;            /* 0x1c */
    uint8_t sub_state;        /* 0x1d */
    uint16_t parameter;       /* 0x1e */
    int32_t timer;            /* 0x20 */
    uint8_t reserved24[0x18]; /* 0x24..0x3b */
    void *result_buffer;      /* 0x3c */
    uint8_t reserved40[0x44]; /* 0x40..0x83 */
    uint32_t lfg_mode;        /* 0x84 */
};

/* Lifecycle hooks (6 standard + 4 event-listener variants). */
static void battle_match_construct(struct BattleMatchProc *self) { /* TODO: not yet decoded */ }
static void battle_match_init(struct BattleMatchProc *self) { /* TODO: not yet decoded */ }
static void battle_match_run(struct BattleMatchProc *self) { /* TODO: not yet decoded */ }
static void battle_match_animate(struct BattleMatchProc *self) { /* TODO: not yet decoded */ }
static void battle_match_draw(struct BattleMatchProc *self) { /* TODO: not yet decoded */ }
static void battle_match_shutdown(struct BattleMatchProc *self) { /* TODO: not yet decoded */ }
static void battle_match_event_a(void *self, int32_t evt) { /* TODO: not yet decoded */ }
static void battle_match_event_b(void *self, int32_t evt) { /* TODO: not yet decoded */ }
static void battle_match_event_c(void *self, int32_t evt) { /* TODO: not yet decoded */ }
static void battle_match_event_d(void *self, int32_t evt) { /* TODO: not yet decoded */ }
