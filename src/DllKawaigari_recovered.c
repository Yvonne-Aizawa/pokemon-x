/*
 * Preliminary decompilation of DllKawaigari.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary (LARGE module — full byte-by-byte decoding skipped):
 *   - Two named exports: `nnroControlObject_` at CRO 0x43b04,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x43a00.
 *   - 423 |static| imports (lowest among the three huge modules).
 *   - 478 external patches.
 *   - 411 ARM prologues, 69 Thumb prologues, 4224 visible BL targets in Thumb.
 *     (The very high BL count is characteristic of dense C++-style state
 *     machines where every branch-and-link is a virtual call.)
 *   - 0x24790 bytes of segment 2 — large constant/string pool (likely the
 *     Pokémon-contest dialogue / dance pattern tables).
 *   - 0x62d1c bytes of BSS — substantial per-process work area.
 *
 * "Kawaigari" = "Pokémon Amie", the petting/feeding minigame module.
 *
 * Because the disassembly is larger than the cache budget for a single pass,
 * only the loader stub, two named exports, and high-level structure are
 * documented below.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0x43b04 */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0x43a00 */

/* Loader / control object table reference. */
extern uint32_t DllKawaigariControlTable[4];

/* Kawaigari (Amie) proc layout — most field accesses cluster around
 * +0x04, +0x18, +0x24..+0x28, +0x40..+0x60, +0x84..+0xb0, +0x100..+0x180,
 * +0x200..+0x240, +0x300..+0x340, +0x400..+0x480. */
struct KawaigariProc {
    void *vtable;              /* 0x00 */
    void *owner;               /* 0x04 */
    void *touch_buffer;        /* 0x08 (multi-touch state) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;             /* 0x24 */
    uint8_t sub_state;         /* 0x25 */
    uint16_t parameter;        /* 0x26 */
    int32_t timer;             /* 0x28 */
    uint8_t reserved2c[0x14]; /* 0x2c..0x3f */
    void *anim_state;          /* 0x40 */
    /* ...heart/affection meters, treat inventory, response cooldown... */
};

/* Top 10 most-imported |static| helpers inferred from patch density.
 * Real names need the .crs symbol map.
 *
 * Patch slots (lower 12 bits) — these are the call sites that show up the
 * most times across the module's many internal state handlers:
 *   +0x00c..+0x024 — framework boot/init.
 *   +0x040..+0x080 — heap allocator and free.
 *   +0x0c0..+0x100 — virtual call dispatch.
 *   +0x180..+0x1c0 — dialogue/feed interaction verbs.
 *   +0x240..+0x280 — animation/sprite mount.
 *   +0x300..+0x340 — pointer-button hit-test.
 *   +0x3c0..+0x400 — sound effect trigger.
 */
extern void *DllKawaigari_static_00c(void);
extern void *DllKawaigari_static_014(void);
extern void *DllKawaigari_static_01c(void);
extern void *DllKawaigari_static_024(void);
extern void *DllKawaigari_static_040(void);
extern void *DllKawaigari_static_044(void);
extern void *DllKawaigari_static_04c(void);
extern void *DllKawaigari_static_054(void);
extern void *DllKawaigari_static_05c(void);
extern void *DllKawaigari_static_064(void);

/* Standard lifecycle (with extra event-listener variants). */
static void kawaigari_construct(struct KawaigariProc *self) { /* TODO: not yet decoded */ }
static void kawaigari_init(struct KawaigariProc *self) { /* TODO: not yet decoded */ }
static void kawaigari_run(struct KawaigariProc *self) { /* TODO: not yet decoded */ }
static void kawaigari_animate(struct KawaigariProc *self) { /* TODO: not yet decoded */ }
static void kawaigari_draw(struct KawaigariProc *self) { /* TODO: not yet decoded */ }
static void kawaigari_idle(struct KawaigariProc *self) { /* TODO: not yet decoded */ }
static void kawaigari_event_a(void *self, int32_t evt) {
    (void)self; (void)evt; /* TODO: not yet decoded */
}
static void kawaigari_event_b(void *self, int32_t evt) {
    (void)self; (void)evt; /* TODO: not yet decoded */
}
static void kawaigari_shutdown(struct KawaigariProc *self) { /* TODO: not yet decoded */ }

/* High-level structure of DllKawaigari based on visible prologues:
 *
 *   Segment 0 (0x180..0x44000):
 *     - 0x000..0x800   : external patch dispatcher wrappers (~120 calls).
 *     - 0x800..0x8000  : touch and feed state machines.
 *     - 0x8000..0x18000: dialogue and pose sequences.
 *     - 0x18000..0x30000: large response/react handler array.
 *     - 0x30000..0x43bbc: main loop + cleanup.
 *
 *   Segment 1 (0x44000..0xe2578): ~600 KiB segment — large constant
 *      pool holding dialogue scripts, pose pose data, and treat
 *      inventory metadata. This is where most of the file size lives.
 *
 *   Segment 2 (0xe8618..0x10cda8): another big data area (~150 KiB) —
 *      likely sprite atlas indices or animation lookup tables.
 *
 *   Segment 3 (0x00..0x62cfc): BSS — runtime per-process work areas
 *      (>400 KiB).
 *
 * TODO: not yet decoded — touch hit-test, dialogue branches, item/treat
 * feed handler, affection meter updates, end-of-session save.
 */
