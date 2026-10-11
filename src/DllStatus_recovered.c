/*
 * Preliminary decompilation of DllStatus.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllStatus.info.md):
 *   file size           : 0xf000 (61,440)
 *   code                : offset 0x180 size 0xbe80
 *   data                : offset 0xed98 size 0x150
 *   bss size            : 0x1a8
 *   exports named       : 1
 *   imports module      : 1
 *   external patches    : 371
 *
 * What was recovered:
 *   - 321 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0xabc). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 110 ARM and 1 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 158 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllStatus.imports.md): */
/*   index 0: `|static|` (348 anonymous symbols) */

/* Named exports (from docs/symbols/DllStatus.map): */
/*   CRO 0xa974  nnroControlObject_  (segment tag 0x000a9740) */

/*
 * Trampoline table (segment 0, 0x000..0xa08, 321 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllStatus.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0b88: push { r4, lr } */
static void dllstatus_arm_0b88(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0c00: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_0c00(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f68: push { r4, r5, r6, lr } */
static void dllstatus_arm_0f68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x116c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_116c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1638: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_1638(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1de0: push { r3, r4, r5, r6, r7, lr } */
static void dllstatus_arm_1de0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e5c: push { r4, r5, r6, lr } */
static void dllstatus_arm_1e5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1fb0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_1fb0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x20e8: push { r4, lr } */
static void dllstatus_arm_20e8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2158: push { r4, lr } */
static void dllstatus_arm_2158(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x21b8: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_21b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x22b8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_22b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x25e0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_25e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x26c8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_26c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x27cc: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_27cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2998: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_2998(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ccc: push { r4, r5, r6, lr } */
static void dllstatus_arm_2ccc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2d80: push { r4, r5, r6, lr } */
static void dllstatus_arm_2d80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e54: push { r4, lr } */
static void dllstatus_arm_2e54(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e74: push { r4, lr } */
static void dllstatus_arm_2e74(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e90: push { r4, r5, r6, r7, lr } */
static void dllstatus_arm_2e90(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2f14: push { r4, r5, r6, r7, lr } */
static void dllstatus_arm_2f14(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2f94: push { r4, lr } */
static void dllstatus_arm_2f94(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2fb8: push { r4, lr } */
static void dllstatus_arm_2fb8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2fd8: push { r4, r5, r6, lr } */
static void dllstatus_arm_2fd8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x303c: push { r4, r5, r6, lr } */
static void dllstatus_arm_303c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x30a4: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_30a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3244: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_3244(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x33ac: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_33ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x361c: push { r4, r5, r6, lr } */
static void dllstatus_arm_361c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x36bc: push { r4, r5, r6, lr } */
static void dllstatus_arm_36bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3754: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_3754(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3878: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_3878(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3d5c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_3d5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ed8: push { r3, r4, r5, r6, r7, lr } */
static void dllstatus_arm_3ed8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3f24: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_3f24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4184: push { r4, lr } */
static void dllstatus_arm_4184(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x41a8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_41a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x43f4: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_43f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x459c: push { r3, r4, r5, lr } */
static void dllstatus_arm_459c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4654: push { r4, r5, r6, lr } */
static void dllstatus_arm_4654(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4684: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_4684(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47d0: push { r4, r5, r6, lr } */
static void dllstatus_arm_47d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4910: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllstatus_arm_4910(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4a98: push { r4, r5, r6, r7, lr } */
static void dllstatus_arm_4a98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4b28: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_4b28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c50: push { r4, lr } */
static void dllstatus_arm_4c50(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c60: push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_4c60(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5424: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_5424(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x54f8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_54f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57b8: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_57b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x58c8: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_58c8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5b1c: push { r4, r5 } */
static void dllstatus_arm_5b1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0x5b80: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_5b80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5cfc: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_5cfc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x60f4: push { r4, r5, r6, lr } */
static void dllstatus_arm_60f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x619c: push { r4, r5, r6, lr } */
static void dllstatus_arm_619c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6280: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_6280(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6320: push { r4, r5, r6, r7, lr } */
static void dllstatus_arm_6320(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6468: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_6468(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x65bc: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_65bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x667c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_667c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6800: push { r4, lr } */
static void dllstatus_arm_6800(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x69a4: push { r3, r4, r5, r6, r7, lr } */
static void dllstatus_arm_69a4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a00: push { r4, lr } */
static void dllstatus_arm_6a00(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a30: push { r4, lr } */
static void dllstatus_arm_6a30(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a64: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_6a64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6c4c: push { r3, r4, r5, r6, r7, lr } */
static void dllstatus_arm_6c4c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ca4: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_6ca4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f04: push { r4, lr } */
static void dllstatus_arm_6f04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f34: push { r4, lr } */
static void dllstatus_arm_6f34(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f94: push { r4, lr } */
static void dllstatus_arm_6f94(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7020: push { r4, r5, lr } */
static void dllstatus_arm_7020(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x70dc: push { r4, lr } */
static void dllstatus_arm_70dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x71cc: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_71cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x78a0: push { r4, r5, r6, r7, r8, lr } */
static void dllstatus_arm_78a0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7d44: push { r4, r5, r6, lr } */
static void dllstatus_arm_7d44(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7edc: push { r4, r5, r6, lr } */
static void dllstatus_arm_7edc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7ffc: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_7ffc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x85c8: push { r4, lr } */
static void dllstatus_arm_85c8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8680: push { r4, lr } */
static void dllstatus_arm_8680(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x86d0: push { r4, lr } */
static void dllstatus_arm_86d0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8724: push { r4, lr } */
static void dllstatus_arm_8724(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x87ac: push { r4, lr } */
static void dllstatus_arm_87ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x87c0: push { r4, r5, r6, lr } */
static void dllstatus_arm_87c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8a3c: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_8a3c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8df0: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_8df0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x95d8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstatus_arm_95d8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c5c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstatus_arm_9c5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9db0: push { r4, lr } */
static void dllstatus_arm_9db0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e20: push { r4, lr } */
static void dllstatus_arm_9e20(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e80: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstatus_arm_9e80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa184: push { r4, r5, r6, lr } */
static void dllstatus_arm_a184(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa304: push { r4, lr } */
static void dllstatus_arm_a304(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa33c: push { r4, lr } */
static void dllstatus_arm_a33c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa378: push { r4, lr } */
static void dllstatus_arm_a378(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa404: push { r4, lr } */
static void dllstatus_arm_a404(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa46c: push { r4, lr } */
static void dllstatus_arm_a46c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa4ec: push { r4, r5, r6, lr } */
static void dllstatus_arm_a4ec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa520: push { r4, lr } */
static void dllstatus_arm_a520(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa588: push { r4, lr } */
static void dllstatus_arm_a588(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa5ec: push { r4, lr } */
static void dllstatus_arm_a5ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa600: push { r4, lr } */
static void dllstatus_arm_a600(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa61c: push { r4, lr } */
static void dllstatus_arm_a61c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa630: push { r4, lr } */
static void dllstatus_arm_a630(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa664: push { r4, lr } */
static void dllstatus_arm_a664(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa694: push { r4, lr } */
static void dllstatus_arm_a694(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa6c8: push { r4, lr } */
static void dllstatus_arm_a6c8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa6f4: push { r4, lr } */
static void dllstatus_arm_a6f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xaafc: push { r4, lr } */
static void dllstatus_arm_aafc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x4e30: push { r3, r5, r6, r7, lr } */
static void dllstatus_thumb_4e30(void) /* TODO: not yet decoded */
{ /* push { r3, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
