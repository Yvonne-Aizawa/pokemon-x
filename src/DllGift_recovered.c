/*
 * Preliminary decompilation of DllGift.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllGift.info.md):
 *   file size           : 0xe000 (57,344)
 *   code                : offset 0x180 size 0xae80
 *   data                : offset 0xd7e8 size 0x68
 *   bss size            : 0x5c
 *   exports named       : 2
 *   imports module      : 1
 *   external patches    : 331
 *
 * What was recovered:
 *   - 300 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0xa14). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 75 ARM and 0 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 155 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllGift.imports.md): */
/*   index 0: `|static|` (321 anonymous symbols) */

/* Named exports (from docs/symbols/DllGift.map): */
/*   CRO 0x958c  nnroControlObject_  (segment tag 0x000958c0) */
/*   CRO 0x92ac  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x00092ac0) */

/*
 * Trampoline table (segment 0, 0x000..0x960, 300 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllGift.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0afc: push { r4, lr } */
static void dllgift_arm_0afc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b34: push { r4, lr } */
static void dllgift_arm_0b34(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b90: push { r4, r5, r6, lr } */
static void dllgift_arm_0b90(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0c2c: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_0c2c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1380: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllgift_arm_1380(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x176c: push { r4, r5, r6, lr } */
static void dllgift_arm_176c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x19c0: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_19c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1a70: push { r4, r5, r6, lr } */
static void dllgift_arm_1a70(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1bc0: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_1bc0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e34: push { r4, r5, r6, lr } */
static void dllgift_arm_1e34(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1ecc: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllgift_arm_1ecc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1fec: push { r4, r5, r6, lr } */
static void dllgift_arm_1fec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x22c0: push { r4, r5, r6, lr } */
static void dllgift_arm_22c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x23f8: push { r4, r5, r6, lr } */
static void dllgift_arm_23f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x254c: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllgift_arm_254c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x29d4: push { r4, r5, r6, lr } */
static void dllgift_arm_29d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2b60: push { r4, r5, r6, lr } */
static void dllgift_arm_2b60(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2b84: push { r4, r5, r6, lr } */
static void dllgift_arm_2b84(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ba8: push { r4, r5, r6, lr } */
static void dllgift_arm_2ba8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2be0: push { r4, lr } */
static void dllgift_arm_2be0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2d38: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_2d38(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x309c: push { r4, r5, r6, lr } */
static void dllgift_arm_309c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3178: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_3178(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3220: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_3220(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3390: push { r4, r5, r6, lr } */
static void dllgift_arm_3390(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3504: push { r4, lr } */
static void dllgift_arm_3504(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x35bc: push { r4, r5, r6, lr } */
static void dllgift_arm_35bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x36ac: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_36ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3738: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_3738(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a78: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_3a78(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3e3c: push { r4, r5, r6, lr } */
static void dllgift_arm_3e3c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3f4c: push { r4, r5, r6, lr } */
static void dllgift_arm_3f4c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x409c: push { r4, r5, r6, lr } */
static void dllgift_arm_409c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x41a8: push { r4, lr } */
static void dllgift_arm_41a8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x41d4: push { r4, r5, r6, lr } */
static void dllgift_arm_41d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4394: push { r4, lr } */
static void dllgift_arm_4394(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x43f4: push { r4, lr } */
static void dllgift_arm_43f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4450: push { r4, r5, r6, lr } */
static void dllgift_arm_4450(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x449c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllgift_arm_449c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4630: push { r4, r5, r6, lr } */
static void dllgift_arm_4630(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x467c: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_467c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x46e8: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_46e8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4abc: push { r4, lr } */
static void dllgift_arm_4abc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4b80: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllgift_arm_4b80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c20: push { r4, lr } */
static void dllgift_arm_4c20(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c7c: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_4c7c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4ce0: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_4ce0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5024: push { r4, r5, r6, lr } */
static void dllgift_arm_5024(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x50b4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_50b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5524: push { r4, r5, r6, lr } */
static void dllgift_arm_5524(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5658: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllgift_arm_5658(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x58cc: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllgift_arm_58cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c64: push { r4, r5, r6, lr } */
static void dllgift_arm_5c64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5df0: push { r4, lr } */
static void dllgift_arm_5df0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e04: push { r4, lr } */
static void dllgift_arm_5e04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e2c: push { r4, lr } */
static void dllgift_arm_5e2c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e68: push { r4, lr } */
static void dllgift_arm_5e68(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5ea0: push { r4, r5, r6, r7, lr } */
static void dllgift_arm_5ea0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6cc4: push { r4, r5, r6, lr } */
static void dllgift_arm_6cc4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6e18: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_6e18(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x75a4: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_75a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7658: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllgift_arm_7658(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7854: push { r4, r5, r6, lr } */
static void dllgift_arm_7854(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7900: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_7900(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7a6c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_7a6c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x83fc: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_83fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8584: push { r4, lr } */
static void dllgift_arm_8584(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8718: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllgift_arm_8718(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9120: push { r4, lr } */
static void dllgift_arm_9120(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9130: push { r4, r5, r6, r7, r8, lr } */
static void dllgift_arm_9130(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x94f8: push { r4, r5, r6, lr } */
static void dllgift_arm_94f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x951c: push { r4, r5, r6, lr } */
static void dllgift_arm_951c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9540: push { r4, r5, r6, lr } */
static void dllgift_arm_9540(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x95c4: push { r4, lr } */
static void dllgift_arm_95c4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9714: push { r4, lr } */
static void dllgift_arm_9714(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
