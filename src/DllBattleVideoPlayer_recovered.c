/*
 * Preliminary decompilation of DllBattleVideoPlayer.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllBattleVideoPlayer.info.md):
 *   file size           : 0x13000 (77,824)
 *   code                : offset 0x180 size 0xfe80
 *   data                : offset 0x12d28 size 0x1c
 *   bss size            : 0x80
 *   exports named       : 2
 *   imports module      : 1
 *   external patches    : 344
 *
 * What was recovered:
 *   - 297 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x9fc). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 128 ARM and 3 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 234 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllBattleVideoPlayer.imports.md): */
/*   index 0: `|static|` (318 anonymous symbols) */

/* Named exports (from docs/symbols/DllBattleVideoPlayer.map): */
/*   CRO 0xdb10  nnroControlObject_  (segment tag 0x000db100) */
/*   CRO 0xd964  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x000d9640) */

/*
 * Trampoline table (segment 0, 0x000..0x948, 297 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllBattleVideoPlayer.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0acc: push { r4, lr } */
static void dllbattlevideoplayer_arm_0acc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0af4: push { r4, lr } */
static void dllbattlevideoplayer_arm_0af4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b38: push { r4, lr } */
static void dllbattlevideoplayer_arm_0b38(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b5c: push { r4, lr } */
static void dllbattlevideoplayer_arm_0b5c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b88: push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_0b88(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10e4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_10e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x12dc: push { r4, lr } */
static void dllbattlevideoplayer_arm_12dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x12ec: push { r4, lr } */
static void dllbattlevideoplayer_arm_12ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1308: push { r4, lr } */
static void dllbattlevideoplayer_arm_1308(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1358: push { r3, r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_1358(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x13f4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_13f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1574: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_1574(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x18c0: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_18c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1a3c: push { r4, lr } */
static void dllbattlevideoplayer_arm_1a3c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1a58: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_1a58(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1b74: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_1b74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e2c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_1e2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1fe4: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_1fe4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2068: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_2068(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x22b0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_22b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2430: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_2430(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2644: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_2644(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x26c8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_26c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x27fc: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_27fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x28e8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_28e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3210: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_3210(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3798: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_3798(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37d8: push { r3, r4, r5, lr } */
static void dllbattlevideoplayer_arm_37d8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x386c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_386c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ba0: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_3ba0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3c6c: push { r3, r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_3c6c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3e7c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_3e7c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x41b8: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_41b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x42f8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_42f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47fc: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_47fc(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4ce4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_4ce4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x549c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_549c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5694: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_5694(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x581c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_581c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5b14: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllbattlevideoplayer_arm_5b14(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x601c: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_601c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x679c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_679c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x68f4: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_68f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6934: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_6934(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ae0: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_6ae0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6cf0: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_6cf0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7090: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_7090(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7180: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllbattlevideoplayer_arm_7180(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7554: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_7554(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7684: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_7684(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7dfc: push { r4, lr } */
static void dllbattlevideoplayer_arm_7dfc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7e60: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_7e60(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7f78: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_7f78(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8180: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_8180(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x82c8: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_82c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8378: push { r4, lr } */
static void dllbattlevideoplayer_arm_8378(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8424: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_8424(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x84f0: push { r3, r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_84f0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8544: push { r4, lr } */
static void dllbattlevideoplayer_arm_8544(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8608: push { r3, r4, r5, lr } */
static void dllbattlevideoplayer_arm_8608(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x866c: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_866c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x86e8: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_86e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x87b4: push { r4, lr } */
static void dllbattlevideoplayer_arm_87b4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8804: push { r3, r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_8804(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8918: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_8918(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8abc: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_8abc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8b44: push { r4, lr } */
static void dllbattlevideoplayer_arm_8b44(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8c08: push { r4, lr } */
static void dllbattlevideoplayer_arm_8c08(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8ca0: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_8ca0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8d1c: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_8d1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8da8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_8da8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9878: push { r4, lr } */
static void dllbattlevideoplayer_arm_9878(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98dc: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_98dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9a20: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_9a20(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ae0: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_9ae0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9da8: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_9da8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9df8: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_9df8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9eb0: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_9eb0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9eec: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_9eec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9f28: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_9f28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa340: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_a340(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa3f4: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_a3f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa604: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_a604(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xafac: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_afac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb17c: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_b17c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb238: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_b238(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb5e4: push { r4, r5, r6, r7, r8 } */
static void dllbattlevideoplayer_arm_b5e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8 }; ... ; pop { ..., pc } */ }

/* ARM 0xb668: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_b668(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb8d0: push { r4, r5 } */
static void dllbattlevideoplayer_arm_b8d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0xb938: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_b938(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xba20: push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_ba20(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc138: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_c138(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc2e0: push { r3, r4, r5, lr } */
static void dllbattlevideoplayer_arm_c2e0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc360: push { r4, r5, lr } */
static void dllbattlevideoplayer_arm_c360(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc3b8: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_c3b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc528: push { r4, lr } */
static void dllbattlevideoplayer_arm_c528(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc538: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_c538(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc61c: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_c61c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc780: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_c780(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc8d8: push { r4, lr } */
static void dllbattlevideoplayer_arm_c8d8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc960: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_c960(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcb58: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_cb58(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcc80: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_cc80(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcd44: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllbattlevideoplayer_arm_cd44(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xce98: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_ce98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd31c: push { r4, r5, r6, r7, r8, lr } */
static void dllbattlevideoplayer_arm_d31c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd4dc: push { r4, r5, lr } */
static void dllbattlevideoplayer_arm_d4dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd570: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_d570(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd6a8: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_d6a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd778: push { r4, lr } */
static void dllbattlevideoplayer_arm_d778(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd7c8: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_d7c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd87c: push { r3, r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_d87c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd944: push { r4, lr } */
static void dllbattlevideoplayer_arm_d944(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd96c: push { r4, lr } */
static void dllbattlevideoplayer_arm_d96c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd9a4: push { r4, lr } */
static void dllbattlevideoplayer_arm_d9a4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd9ec: push { r4, lr } */
static void dllbattlevideoplayer_arm_d9ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xda28: push { r4, lr } */
static void dllbattlevideoplayer_arm_da28(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xda70: push { r4, lr } */
static void dllbattlevideoplayer_arm_da70(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdaa8: push { r4, lr } */
static void dllbattlevideoplayer_arm_daa8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdb0c: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_db0c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdb48: push { r4, r5, r6, lr } */
static void dllbattlevideoplayer_arm_db48(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdc98: push { r4, lr } */
static void dllbattlevideoplayer_arm_dc98(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdd3c: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllbattlevideoplayer_arm_dd3c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xde9c: push { r4, r5, lr } */
static void dllbattlevideoplayer_arm_de9c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xded0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllbattlevideoplayer_arm_ded0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe644: push { r4, r5, lr } */
static void dllbattlevideoplayer_arm_e644(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe678: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllbattlevideoplayer_arm_e678(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xea4c: push { r4, r5, r6, r7, lr } */
static void dllbattlevideoplayer_arm_ea4c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x758e: push { r0, r1, r4, r7, lr } */
static void dllbattlevideoplayer_thumb_758e(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r7, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0xbbb2: push { r0, r1, r4, r7, lr } */
static void dllbattlevideoplayer_thumb_bbb2(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r7, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0xea86: push { r0, r1, r4, r7, lr } */
static void dllbattlevideoplayer_thumb_ea86(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
