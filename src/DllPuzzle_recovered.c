/*
 * Preliminary decompilation of DllPuzzle.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllPuzzle.info.md):
 *   file size           : 0x14000 (81,920)
 *   code                : offset 0x180 size 0xfe80
 *   data                : offset 0x130a0 size 0xd8
 *   bss size            : 0x4a4
 *   exports named       : 2
 *   imports module      : 2
 *   external patches    : 329
 *
 * What was recovered:
 *   - 301 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0xa1c). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 123 ARM and 3 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 187 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllPuzzle.imports.md): */
/*   index 0: `|static|` (300 anonymous symbols) */
/*   index 1: `DllBackGround` (12 anonymous symbols) */

/* Named exports (from docs/symbols/DllPuzzle.map): */
/*   CRO 0xc600  nnroControlObject_  (segment tag 0x000c6000) */
/*   CRO 0xbe6c  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x000be6c0) */

/*
 * Trampoline table (segment 0, 0x000..0x968, 301 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllPuzzle.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0b04: push { r4, lr } */
static void dllpuzzle_arm_0b04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b84: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_0b84(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0cb0: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_0cb0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0cf8: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_0cf8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f04: push { r4, lr } */
static void dllpuzzle_arm_0f04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f30: push { r4, lr } */
static void dllpuzzle_arm_0f30(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0fa4: push { r4, lr } */
static void dllpuzzle_arm_0fa4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1030: push { r4, lr } */
static void dllpuzzle_arm_1030(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1108: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_1108(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1150: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_1150(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x12cc: push { r4, lr } */
static void dllpuzzle_arm_12cc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x135c: push { r4, lr } */
static void dllpuzzle_arm_135c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1404: push { r4, lr } */
static void dllpuzzle_arm_1404(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1438: push { r4, lr } */
static void dllpuzzle_arm_1438(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1470: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_1470(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x15e0: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_15e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1734: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllpuzzle_arm_1734(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1840: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_1840(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x18b4: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_18b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1924: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_1924(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1aa4: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_1aa4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1c90: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_1c90(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e70: push { r4, lr } */
static void dllpuzzle_arm_1e70(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e90: push { r4, lr } */
static void dllpuzzle_arm_1e90(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1ea8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_1ea8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x22c0: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_22c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2900: push { r4, r5, r6, r7, r8 } */
static void dllpuzzle_arm_2900(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8 }; ... ; pop { ..., pc } */ }

/* ARM 0x2b38: push { r3, r4, r5, lr } */
static void dllpuzzle_arm_2b38(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2c44: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_2c44(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2de4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_2de4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x30d4: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_30d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x32f8: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_32f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3348: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_3348(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3398: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_3398(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x346c: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_346c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3618: push { r4, lr } */
static void dllpuzzle_arm_3618(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37a0: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllpuzzle_arm_37a0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3918: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllpuzzle_arm_3918(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a28: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_3a28(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3f68: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_3f68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4224: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_4224(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4404: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_4404(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x44d8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_44d8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4780: push { r3, r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_4780(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x48bc: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_48bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4b80: push { r4, lr } */
static void dllpuzzle_arm_4b80(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4ba0: push { r4, lr } */
static void dllpuzzle_arm_4ba0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4bb8: push { r3, r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_4bb8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4fcc: push { r3, r4, r5, lr } */
static void dllpuzzle_arm_4fcc(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x51c4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_51c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5258: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_5258(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x53dc: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_53dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x547c: push { r4, r5, lr } */
static void dllpuzzle_arm_547c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5540: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_5540(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x574c: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_574c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x588c: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_588c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x59b4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_59b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5b4c: push { r4, lr } */
static void dllpuzzle_arm_5b4c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c54: push { r4, r5, lr } */
static void dllpuzzle_arm_5c54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5d74: push { r4, r5, lr } */
static void dllpuzzle_arm_5d74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e70: push { r4, lr } */
static void dllpuzzle_arm_5e70(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5f40: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllpuzzle_arm_5f40(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x60ac: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_60ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x61b8: push { r3, r4, r5, lr } */
static void dllpuzzle_arm_61b8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x62c0: push { r3, r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_62c0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x63bc: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_63bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x64f8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_64f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x66c4: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_66c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6784: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_6784(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x684c: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_684c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x68e0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_68e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6cd4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_6cd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6e3c: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_6e3c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f0c: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_6f0c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6fdc: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_6fdc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x706c: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_706c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x71b0: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_71b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7208: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_7208(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7490: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_7490(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7908: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpuzzle_arm_7908(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7a68: push { r3, r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_7a68(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7c1c: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_7c1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7d64: push { r4, r5 } */
static void dllpuzzle_arm_7d64(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0x7e64: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpuzzle_arm_7e64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7f5c: push { r4, r5, lr } */
static void dllpuzzle_arm_7f5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x83e8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_83e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x86bc: push { r4, lr } */
static void dllpuzzle_arm_86bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x86cc: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_86cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x87c0: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_87c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8954: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_8954(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8b0c: push { r4, lr } */
static void dllpuzzle_arm_8b0c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8be4: push { r4, lr } */
static void dllpuzzle_arm_8be4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8c88: push { r4, lr } */
static void dllpuzzle_arm_8c88(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8d2c: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_8d2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x92e4: push { r4, lr } */
static void dllpuzzle_arm_92e4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9310: push { r4, lr } */
static void dllpuzzle_arm_9310(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x933c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_933c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9590: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_9590(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x96ac: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_96ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98cc: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_98cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9a00: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_9a00(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e7c: push { r3, r4, r5, lr } */
static void dllpuzzle_arm_9e7c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9fb4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_9fb4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa498: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_a498(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa6c8: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_a6c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa858: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_a858(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xab2c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_ab2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb040: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_b040(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb380: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_b380(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb3fc: push { r4, lr } */
static void dllpuzzle_arm_b3fc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb434: push { r4, lr } */
static void dllpuzzle_arm_b434(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb470: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_b470(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb58c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_b58c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb960: push { r4, r5, r6, r7, lr } */
static void dllpuzzle_arm_b960(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbb74: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpuzzle_arm_bb74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbcc8: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_bcc8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbd28: push { r4, r5, r6, r7, r8, lr } */
static void dllpuzzle_arm_bd28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbe54: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_be54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbea0: push { r4, r5, r6, lr } */
static void dllpuzzle_arm_bea0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbf80: push { r4, lr } */
static void dllpuzzle_arm_bf80(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbfb8: push { r4, lr } */
static void dllpuzzle_arm_bfb8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbffc: push { r4, lr } */
static void dllpuzzle_arm_bffc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc788: push { r4, lr } */
static void dllpuzzle_arm_c788(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x21e8: push { r1, r3, r6, lr } */
static void dllpuzzle_thumb_21e8(void) /* TODO: not yet decoded */
{ /* push { r1, r3, r6, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0x2380: push { r2, r5, r6, lr } */
static void dllpuzzle_thumb_2380(void) /* TODO: not yet decoded */
{ /* push { r2, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0xd242: push { r0, r2, r7, lr } */
static void dllpuzzle_thumb_d242(void) /* TODO: not yet decoded */
{ /* push { r0, r2, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
