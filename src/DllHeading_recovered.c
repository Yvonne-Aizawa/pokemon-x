/*
 * Preliminary decompilation of DllHeading.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Recovery summary:
 *   - Single named export `nnroControlObject_` at CRO 0xa2e4 (a loader object).
 *   - 184 anonymous |static| imports and 204 external patches.
 *   - 115 ARM prologues and 3 Thumb prologues in the disassembly.
 *   - No remaining demangled C++ exports.
 */

#include <stdint.h>

/* The single named export: the `nnroControlObject_` loader object.
 * Falls inside the loader trampoline area near the end of segment 0. */
extern void nnroControlObject_(void);

/* Loader / control object table reference. Inferred layout = 4-word stub. */
extern uint32_t DllHeadingControlTable[4];

/* External static imports are accessed via patches inside .text.bin. The most
 * heavily-targeted hot functions are typical |static| allocator / message-bus
 * entry points (exact names require .crs). Forward-declared opaquely:
 */
typedef void *(*HeadingStaticAlloc)(uint32_t size, uint32_t align);
typedef void  (*HeadingStaticFree)(void *ptr);

/* HeadingProc instance layout (inferred from field accesses in the
 * ARM prologues around +0x4..+0x30). Size is at least 0x40 bytes. */
struct HeadingProc {
    void *vtable;              /* 0x00 */
    void *parent;              /* 0x04 */
    void *bg_handle;           /* 0x08 (handle to background plane) */
    uint8_t reserved0c[0x18]; /* 0x0c..0x23 */
    uint8_t state;             /* 0x24 */
    uint8_t sub_state;         /* 0x25 */
    uint16_t parameter;        /* 0x26 */
    int32_t timer;             /* 0x28 */
    uint8_t reserved2c[0x14]; /* 0x2c..0x3f */
};

/* CRO 0x6878: Thumb prologue `push {r3, r4, r6, r7, lr}`.
 * Initialiser for the HeadingProc instance — allocates the layout
 * referenced by the patch around +0x688c. Calls three different
 * |static| imports in sequence.
 */
static void heading_init(struct HeadingProc *self) {
    (void)self; /* TODO: not yet decoded */
}

/* CRO 0xabe..0xac0: ARM-style prologue `push {r1, r2, r6, r7, lr}`.
 * Heading-mode update routine; dispatches on a state byte at `self + 0x24`.
 * Size: ~32 bytes inlined body.
 */
static void heading_update(struct HeadingProc *self) {
    /* TODO: not yet decoded — body switches on `self + 0x24`. */
    (void)self;
}

/* CRO 0x1366..0x1380: Thumb `push {r6, r7, lr}` followed by an immediate
 * tail call into one of the |static| import helpers. Destructor / cleanup.
 */
static void heading_shutdown(struct HeadingProc *self) {
    /* TODO: not yet decoded — body is mostly a tail call. */
    (void)self;
}
