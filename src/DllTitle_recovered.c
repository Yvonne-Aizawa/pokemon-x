/*
 * Preliminary decompilation of DllTitle.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Two named exports: `nnroControlObject_` at CRO 0x1bfdc,
 *     `_ZN9xy_system2bg6System13SetIsCallDrawEb` at CRO 0x1a950.
 *   - Imports DllSequence (12 anonymous callers — the title screen drives
 *     the sequence module's manager directly).
 *   - 199 |static| imports, 275 ARM prologues and 94 Thumb prologues.
 *   - 270 external patches. Heavily uses BL into DllSequence around its
 *     patch slots (segments 0x12000..0x16000 of DllSequence).
 *   - Largest BSS of the small-misc group (0x450) — copyright text plus
 *     demo-loop counters.
 */

#include <stdint.h>

/* Named exports. */
extern void nnroControlObject_(void);             /* CRO 0x1bfdc */
extern void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0x1a950 */

/* Loader / control object table reference. */
extern uint32_t DllTitleControlTable[4];

/* Title proc layout (inferred from disassembly accesses at +0x08, +0x18,
 * +0x24..+0x28, +0x38..+0x48, +0x84). */
struct TitleProc {
    void *vtable;              /* 0x00 */
    void *parent;              /* 0x04 */
    void *demo_state;          /* 0x08 */
    uint8_t reserved0c[0x10]; /* 0x0c..0x1b */
    uint8_t state;             /* 0x1c */
    uint8_t sub_state;         /* 0x1d */
    uint16_t parameter;        /* 0x1e */
    int32_t timer;             /* 0x20 */
    uint8_t reserved24[0x14]; /* 0x24..0x37 */
    void *sequence_link;       /* 0x38 (DllSequence caller handle) */
    uint8_t reserved3c[0x4c]; /* 0x3c..0x87 */
    uint32_t counter;          /* 0x88 (idle timer) */
};

/* DllSequence entry points used by this module (forward decls only). */
extern int32_t DllSequence_call_1203c(void *self);
extern int32_t DllSequence_call_1203d(void *self);
extern int32_t DllSequence_call_1203e(void *self);
extern int32_t DllSequence_call_1203f(void *self);
extern int32_t DllSequence_call_12040(void *self);
extern int32_t DllSequence_call_12041(void *self);
extern int32_t DllSequence_call_12042(void *self);
extern int32_t DllSequence_call_12043(void *self);
extern int32_t DllSequence_call_12044(void *self);
extern int32_t DllSequence_call_12045(void *self);
extern int32_t DllSequence_call_12046(void *self);
extern int32_t DllSequence_call_12047(void *self);

/* Title-mode lifecycle (5 hooks used for the demo/idle loop). */
static void title_construct(struct TitleProc *self);
static void title_init(struct TitleProc *self);
static void title_run(struct TitleProc *self);     /* dispatch on state byte */
static void title_animate(struct TitleProc *self);
static void title_shutdown(struct TitleProc *self);

/* CRO 0x1a950: demangled SetIsCallDraw. ARM prologue is `push {r4, lr}`. */
void xy_system_bg_System_SetIsCallDraw(int32_t flag) {
    /* TODO: not yet decoded — body stores the flag and calls one
       |static| helper. */
    (void)flag;
}

/* CRO ~0x1bd00..0x1bf80: many small Thumb helpers (94 push prologues).
 * Heaviest patch density is in the area +0x190..+0x250, which is the
 * "press-A-to-continue" loop and the various splash/demo transitions.
 * Each helper is documented inline at the recovered .text offset.
 */
