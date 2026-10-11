/*
 * Preliminary decompilation of DllGts.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x1bf78,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x1b664.
 *   - 440 |static| imports, 593 external patches.
 *   - 496 ARM prologues and 98 Thumb prologues.
 *   - GTS = "Global Trade Station"; this module talks to the network service
 *     via several patches into the static comms layer.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0x1bf78 */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0x1b664 */

/* Loader / control object table reference. */
extern uint32_t DllGtsControlTable[4];

/* GTS instance layout — inferred from disassembly. Note the unusually
 * large data segment (0x54 here plus a BSS of 0xa4) relative to other
 * DllGame sysmodules, suggesting a small packet buffer cache. */
struct GtsProc {
    void *vtable;             /* 0x00 */
    void *owner;              /* 0x04 */
    void *net_session;        /* 0x08 (opaque network handle) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;            /* 0x24 */
    uint8_t sub_state;        /* 0x25 */
    uint16_t parameter;       /* 0x26 */
    int32_t timer;            /* 0x28 */
    uint8_t reserved2c[0x50]; /* 0x2c..0x7b */
    void *pkt_buf;            /* 0x7c (8-byte aligned scratch) */
    uint32_t retry_count;     /* 0x84 */
    uint8_t reserved88[0x18]; /* 0x88..0x9f */
    uint32_t req_flags;       /* 0xa0 */
};

/* Top five hot external patches (segment offsets, lower 16 bits):
 *   +0x0c0 area — comm allocator (likely).
 *   +0xb40 area — comm free.
 *   +0x84  area — async message dispatch (DL-call completion).
 *   +0xc44 area — request encoder.
 *   +0x240 area — response decoder.
 */
static void gts_alloc(struct GtsProc *self, uint32_t size);
static void gts_free(struct GtsProc *self, void *ptr);
static void gts_dispatch_msg(struct GtsProc *self);
static void gts_encode_request(struct GtsProc *self);
static void gts_decode_response(struct GtsProc *self);

/* Standard 6-hook lifecycle for the GTS UI proc. */
static void gts_construct(struct GtsProc *self) { /* TODO: not yet decoded */ }
static void gts_init(struct GtsProc *self) { /* TODO: not yet decoded */ }
static void gts_run(struct GtsProc *self) { /* TODO: not yet decoded */ }
static void gts_animate(struct GtsProc *self) { /* TODO: not yet decoded */ }
static void gts_draw(struct GtsProc *self) { /* TODO: not yet decoded */ }
static void gts_shutdown(struct GtsProc *self) { /* TODO: not yet decoded */ }
