/*
 * Preliminary decompilation of DllZukan.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x1d90c,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x1b948.
 *   - Imports two peer modules: DllTownmap (22 anonymous entry points)
 *     and DllBackGround (12 anonymous entry points).
 *   - 452 |static| imports, 668 external patches (highest in this group).
 *   - 517 ARM prologues and 39 Thumb prologues.
 *   - Zukan = Pokémon "Pokédex" — biggest UI module in this assignment.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0x1d90c */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0x1b948 */

/* Loader / control object table reference. */
extern uint32_t DllZukanControlTable[4];

/* Cross-module peer imports — first few callees out of 12 from each. */
extern void DllTownmap_op0(void *self);
extern void DllTownmap_op1(void *self, int32_t a);
extern void DllTownmap_op2(void *self, int32_t a, int32_t b);
extern void DllBackGround_op0(void *self);
extern void DllBackGround_op1(void *self, int32_t a);
extern void DllBackGround_op2(void *self, int32_t a);

/* Zukan (Pokédex) proc layout — most field accesses occur at +0x04,
 * +0x18, +0x24..+0x28, +0x40..+0x80, +0xc4..+0x130. */
struct ZukanProc {
    void *vtable;             /* 0x00 */
    void *owner;              /* 0x04 */
    void *page_buffer;        /* 0x08 (tall sprite page, ~0x80 bytes) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;            /* 0x24 */
    uint8_t sub_state;        /* 0x25 */
    uint16_t parameter;       /* 0x26 */
    int32_t timer;            /* 0x28 */
    uint8_t reserved2c[0x18]; /* 0x2c..0x43 */
    void *dex_data;           /* 0x44 (pointer to dex records) */
    uint8_t reserved48[0x84]; /* 0x48..0xcb */
    void *anim_state;         /* 0xcc */
};

/* Standard 6-hook lifecycle. */
static void zukan_construct(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_init(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_run(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_animate(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_draw(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_shutdown(struct ZukanProc *self) { /* TODO: not yet decoded */ }

/* The Zukan UI has multiple "pages" (list / area / stats / forms / search).
 * These appear to be the seven internal state-machine handlers, each at a
 * separate CRO offset. Names below are provisional. */
static void zukan_page_list(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_page_area(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_page_stats(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_page_form(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_page_search(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_page_voice(struct ZukanProc *self) { /* TODO: not yet decoded */ }
static void zukan_page_size(struct ZukanProc *self) { /* TODO: not yet decoded */ }
