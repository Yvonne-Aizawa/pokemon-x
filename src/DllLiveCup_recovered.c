/*
 * Preliminary decompilation of DllLiveCup.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllLiveCup.info.md):
 *   file size           : 0x11000 (69,632)
 *   code                : offset 0x180 size 0xce80
 *   data                : offset 0x103b0 size 0x1c
 *   bss size            : 0x80
 *   exports named       : 2
 *   imports module      : 1
 *   external patches    : 281
 *
 * What was recovered:
 *   - 183 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x66c). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 186 ARM and 0 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 258 `pop {..., pc}` returns that bound those prologues into
 *     closed functions.
 *   - The named exports listed below.
 *
 * What was NOT recovered:
 *   - Exact struct layouts (offsets guessed from field accesses only).
 *   - Imported service names (the `|static|` anonymous imports do not carry
 *     a public symbol table we have access to).
 *   - Calling conventions, register usage, and constant pools.
 *   - Real bodies for the discovered function boundaries; only their entry
 *     addresses and register-save footprints are recorded.
 */

#include <stdint.h>

/* Imported modules (from work/modules/DllLiveCup.imports.md): */
/*   index 0: `|static|` (198 anonymous symbols) */

/* Named exports (from docs/symbols/DllLiveCup.map): */
/*   CRO 0xa5c8  nnroControlObject_  (segment tag 0x000a5c80) */
/*   CRO 0x98d0  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x00098d00) */

/*
 * Trampoline table (segment 0, 0x000..0x5b8, 183 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllLiveCup.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0764: push { r4, lr } */
static void dlllivecup_arm_0764(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x079c: push { r4, lr } */
static void dlllivecup_arm_079c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x07d0: push { r4, r5, r6, lr } */
static void dlllivecup_arm_07d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b1c: push { r4, r5, r6, r7, lr } */
static void dlllivecup_arm_0b1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0ce4: push { r4, lr } */
static void dlllivecup_arm_0ce4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0d04: push { r4, lr } */
static void dlllivecup_arm_0d04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0d1c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_0d1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0e84: push { r4, lr } */
static void dlllivecup_arm_0e84(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0ef8: push { r4, r5, r6, lr } */
static void dlllivecup_arm_0ef8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x106c: push { r4, lr } */
static void dlllivecup_arm_106c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10bc: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlllivecup_arm_10bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x17ec: push { r4, lr } */
static void dlllivecup_arm_17ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x17fc: push { r4, r5, r6, lr } */
static void dlllivecup_arm_17fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1988: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_1988(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1ab4: push { r4, lr } */
static void dlllivecup_arm_1ab4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1af8: push { r4, lr } */
static void dlllivecup_arm_1af8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1b34: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_1b34(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1cd4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlllivecup_arm_1cd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e28: push { r4, lr } */
static void dlllivecup_arm_1e28(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e4c: push { r4, lr } */
static void dlllivecup_arm_1e4c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e88: push { r4, lr } */
static void dlllivecup_arm_1e88(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1eac: push { r4, lr } */
static void dlllivecup_arm_1eac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1ed4: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_1ed4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2078: push { r4, lr } */
static void dlllivecup_arm_2078(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x20ec: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlllivecup_arm_20ec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2204: push { r4, lr } */
static void dlllivecup_arm_2204(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2238: push { r4, lr } */
static void dlllivecup_arm_2238(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2268: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_2268(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2420: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlllivecup_arm_2420(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2540: push { r4, lr } */
static void dlllivecup_arm_2540(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2564: push { r4, lr } */
static void dlllivecup_arm_2564(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x258c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_258c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x261c: push { r4, lr } */
static void dlllivecup_arm_261c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2660: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_2660(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2708: push { r4, r5, r6, lr } */
static void dlllivecup_arm_2708(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x279c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_279c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x28a4: push { r4, lr } */
static void dlllivecup_arm_28a4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x28d8: push { r4, lr } */
static void dlllivecup_arm_28d8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2908: push { r4, lr } */
static void dlllivecup_arm_2908(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2964: push { r4, r5, r6, lr } */
static void dlllivecup_arm_2964(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2a40: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_2a40(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2b6c: push { r4, lr } */
static void dlllivecup_arm_2b6c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ba0: push { r4, lr } */
static void dlllivecup_arm_2ba0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2bd4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlllivecup_arm_2bd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e64: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_2e64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ef4: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_2ef4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ff4: push { r4, lr } */
static void dlllivecup_arm_2ff4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3018: push { r4, lr } */
static void dlllivecup_arm_3018(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3040: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_3040(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3190: push { r4, r5, r6, lr } */
static void dlllivecup_arm_3190(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x32c4: push { r4, lr } */
static void dlllivecup_arm_32c4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3320: push { r4, r5, r6, lr } */
static void dlllivecup_arm_3320(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x33fc: push { r4, lr } */
static void dlllivecup_arm_33fc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3420: push { r4, lr } */
static void dlllivecup_arm_3420(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3448: push { r4, r5, r6, lr } */
static void dlllivecup_arm_3448(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x349c: push { r4, lr } */
static void dlllivecup_arm_349c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x34e0: push { r3, r4, r5, r6, r7, lr } */
static void dlllivecup_arm_34e0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3578: push { r4, lr } */
static void dlllivecup_arm_3578(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x35c4: push { r4, lr } */
static void dlllivecup_arm_35c4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x360c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_360c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3744: push { r4, r5, r6, lr } */
static void dlllivecup_arm_3744(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37a0: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_37a0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ab8: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_3ab8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3bd8: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_3bd8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3cd0: push { r4, lr } */
static void dlllivecup_arm_3cd0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3cfc: push { r4, lr } */
static void dlllivecup_arm_3cfc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3d20: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_3d20(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3f9c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_3f9c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4024: push { r4, lr } */
static void dlllivecup_arm_4024(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x406c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_406c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4124: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_4124(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4254: push { r4, lr } */
static void dlllivecup_arm_4254(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4280: push { r4, lr } */
static void dlllivecup_arm_4280(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x42b4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_42b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4314: push { r4, r5, r6, lr } */
static void dlllivecup_arm_4314(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x43cc: push { r4, r5, r6, lr } */
static void dlllivecup_arm_43cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4460: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_4460(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x45c4: push { r4, lr } */
static void dlllivecup_arm_45c4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x45f0: push { r4, lr } */
static void dlllivecup_arm_45f0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4614: push { r4, r5, r6, lr } */
static void dlllivecup_arm_4614(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4d28: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_4d28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5380: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_5380(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x543c: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_543c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5514: push { r4, lr } */
static void dlllivecup_arm_5514(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5564: push { r3, r4, r5, lr } */
static void dlllivecup_arm_5564(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5618: push { r4, r5, r6, lr } */
static void dlllivecup_arm_5618(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x56a8: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_56a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57e8: push { r4, r5, r6, lr } */
static void dlllivecup_arm_57e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5854: push { r4, lr } */
static void dlllivecup_arm_5854(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x588c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_588c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5ce0: push { r4, lr } */
static void dlllivecup_arm_5ce0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5d14: push { r4, r5, r6, lr } */
static void dlllivecup_arm_5d14(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e1c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_5e1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5ecc: push { r4, r5, r6, lr } */
static void dlllivecup_arm_5ecc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5fc8: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_5fc8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6134: push { r4, lr } */
static void dlllivecup_arm_6134(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6170: push { r4, lr } */
static void dlllivecup_arm_6170(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x61a4: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_61a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6400: push { r4, r5, r6, lr } */
static void dlllivecup_arm_6400(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6504: push { r4, r5, r6, lr } */
static void dlllivecup_arm_6504(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6560: push { r4, r5, r6, lr } */
static void dlllivecup_arm_6560(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6608: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_6608(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6700: push { r4, lr } */
static void dlllivecup_arm_6700(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x672c: push { r4, lr } */
static void dlllivecup_arm_672c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6750: push { r4, r5, r6, r7, lr } */
static void dlllivecup_arm_6750(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6bd8: push { r4, r5, r6, lr } */
static void dlllivecup_arm_6bd8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6cf8: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_6cf8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ea0: push { r4, lr } */
static void dlllivecup_arm_6ea0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ecc: push { r4, lr } */
static void dlllivecup_arm_6ecc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ef0: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_6ef0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x73e4: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_73e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7538: push { r4, r5, r6, lr } */
static void dlllivecup_arm_7538(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x75b4: push { r4, lr } */
static void dlllivecup_arm_75b4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7620: push { r4, r5, r6, lr } */
static void dlllivecup_arm_7620(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x76b0: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_76b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7728: push { r4, lr } */
static void dlllivecup_arm_7728(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7754: push { r4, lr } */
static void dlllivecup_arm_7754(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7778: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_7778(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7a18: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_7a18(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7ae8: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_7ae8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7bc4: push { r4, lr } */
static void dlllivecup_arm_7bc4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7be4: push { r4, lr } */
static void dlllivecup_arm_7be4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7bfc: push { r4, r5, r6, lr } */
static void dlllivecup_arm_7bfc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7d00: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_7d00(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7ec0: push { r4, r5, r6, lr } */
static void dlllivecup_arm_7ec0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7f64: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_7f64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7fec: push { r4, lr } */
static void dlllivecup_arm_7fec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x800c: push { r4, lr } */
static void dlllivecup_arm_800c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8024: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8024(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x80c4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_80c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x816c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_816c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8240: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_8240(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8360: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlllivecup_arm_8360(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8500: push { r4, lr } */
static void dlllivecup_arm_8500(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x852c: push { r4, lr } */
static void dlllivecup_arm_852c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8550: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8550(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8718: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8718(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8828: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_8828(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x89d4: push { r4, lr } */
static void dlllivecup_arm_89d4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8a00: push { r4, lr } */
static void dlllivecup_arm_8a00(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8a24: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_8a24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8c5c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8c5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8d60: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8d60(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8dbc: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8dbc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8e1c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_8e1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8ecc: push { r4, lr } */
static void dlllivecup_arm_8ecc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8ef8: push { r4, lr } */
static void dlllivecup_arm_8ef8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8f2c: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_8f2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x902c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_902c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x91f4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_91f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x92d0: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dlllivecup_arm_92d0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x944c: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_944c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x95c4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_95c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x96f4: push { r4, r5, r6, r7, r8, lr } */
static void dlllivecup_arm_96f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x97e8: push { r4, lr } */
static void dlllivecup_arm_97e8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9814: push { r4, lr } */
static void dlllivecup_arm_9814(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9838: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9838(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98bc: push { r4, lr } */
static void dlllivecup_arm_98bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98dc: push { r4, lr } */
static void dlllivecup_arm_98dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98f4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_98f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x99dc: push { r4, lr } */
static void dlllivecup_arm_99dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x99fc: push { r4, lr } */
static void dlllivecup_arm_99fc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9a18: push { r4, lr } */
static void dlllivecup_arm_9a18(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9a38: push { r4, lr } */
static void dlllivecup_arm_9a38(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9a60: push { r4, lr } */
static void dlllivecup_arm_9a60(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ac0: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9ac0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9b58: push { r4, lr } */
static void dlllivecup_arm_9b58(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9b9c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9b9c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c20: push { r4, lr } */
static void dlllivecup_arm_9c20(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c7c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9c7c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9d84: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9d84(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9df0: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9df0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e78: push { r4, lr } */
static void dlllivecup_arm_9e78(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ec4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9ec4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9f24: push { r4, r5, r6, lr } */
static void dlllivecup_arm_9f24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9fdc: push { r4, lr } */
static void dlllivecup_arm_9fdc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa010: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a010(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa11c: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a11c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa214: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a214(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa294: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a294(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa310: push { r4, lr } */
static void dlllivecup_arm_a310(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa380: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a380(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa438: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a438(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa530: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a530(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa5a4: push { r4, r5, r6, lr } */
static void dlllivecup_arm_a5a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa750: push { r4, lr } */
static void dlllivecup_arm_a750(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
