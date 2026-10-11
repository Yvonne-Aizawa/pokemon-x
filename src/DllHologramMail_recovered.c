/*
 * Preliminary decompilation of DllHologramMail.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllHologramMail.info.md):
 *   file size           : 0x1a000 (106,496)
 *   code                : offset 0x180 size 0x13e80
 *   data                : offset 0x19ad0 size 0x7c
 *   bss size            : 0x230
 *   exports named       : 2
 *   imports module      : 2
 *   external patches    : 576
 *
 * What was recovered:
 *   - 433 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0xe3c). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 269 ARM and 0 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 420 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllHologramMail.imports.md): */
/*   index 0: `|static|` (450 anonymous symbols) */
/*   index 1: `DllBackGround` (12 anonymous symbols) */

/* Named exports (from docs/symbols/DllHologramMail.map): */
/*   CRO 0x114a4  nnroControlObject_  (segment tag 0x00114a40) */
/*   CRO 0xf834  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x000f8340) */

/*
 * Trampoline table (segment 0, 0x000..0xd88, 433 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllHologramMail.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0f14: push { r4, lr } */
static void dllhologrammail_arm_0f14(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f5c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_0f5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1064: push { r4, lr } */
static void dllhologrammail_arm_1064(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1094: push { r4, lr } */
static void dllhologrammail_arm_1094(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10e4: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_10e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1338: push { r4, lr } */
static void dllhologrammail_arm_1338(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x134c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_134c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1410: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_1410(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x148c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_148c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1508: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_1508(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x189c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_189c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1a54: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_1a54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1b38: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_1b38(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1c94: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_1c94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e94: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_1e94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1fb4: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_1fb4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x21c0: push { r4, lr } */
static void dllhologrammail_arm_21c0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2254: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_2254(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x249c: push { r3, r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_249c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2524: push { r4, lr } */
static void dllhologrammail_arm_2524(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2574: push { r4, lr } */
static void dllhologrammail_arm_2574(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x25c8: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_25c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x26c4: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_26c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x28a8: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_28a8(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2bb8: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_2bb8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2dd4: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_2dd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3024: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_3024(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3108: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_3108(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x324c: push { r4, lr } */
static void dllhologrammail_arm_324c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3270: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_3270(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x336c: push { r4, lr } */
static void dllhologrammail_arm_336c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3390: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_3390(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x33bc: push { r4, lr } */
static void dllhologrammail_arm_33bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3428: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_3428(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3698: push { r4, lr } */
static void dllhologrammail_arm_3698(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x36ac: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_36ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x36f4: push { r4, lr } */
static void dllhologrammail_arm_36f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x374c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_374c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3820: push { r4, lr } */
static void dllhologrammail_arm_3820(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x38ac: push { r4, lr } */
static void dllhologrammail_arm_38ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x39ac: push { r4, lr } */
static void dllhologrammail_arm_39ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x39e4: push { r4, lr } */
static void dllhologrammail_arm_39e4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a18: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_3a18(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3aec: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_3aec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3b90: push { r4, lr } */
static void dllhologrammail_arm_3b90(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ba4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_3ba4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3c98: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_3c98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3e80: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_3e80(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x41e0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_41e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4374: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_4374(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x44d0: push { r4, lr } */
static void dllhologrammail_arm_44d0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x44e0: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_44e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4620: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_4620(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x46a0: push { r3, r4, r5, lr } */
static void dllhologrammail_arm_46a0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47a0: push { r4, lr } */
static void dllhologrammail_arm_47a0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47d0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_47d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4934: push { r4, lr } */
static void dllhologrammail_arm_4934(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4984: push { r4, lr } */
static void dllhologrammail_arm_4984(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x49d4: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_49d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4bd4: push { r3, r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_4bd4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c70: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_4c70(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4d10: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_4d10(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4e00: push { r4, lr } */
static void dllhologrammail_arm_4e00(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4e10: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_4e10(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4f1c: push { r4, lr } */
static void dllhologrammail_arm_4f1c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4f70: push { r4, lr } */
static void dllhologrammail_arm_4f70(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4f84: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_4f84(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x503c: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_503c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x50bc: push { r4, lr } */
static void dllhologrammail_arm_50bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x50f4: push { r4, lr } */
static void dllhologrammail_arm_50f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5120: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_5120(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5258: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_5258(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x52bc: push { r4, lr } */
static void dllhologrammail_arm_52bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x52e8: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_52e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5474: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_5474(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5714: push { r4, lr } */
static void dllhologrammail_arm_5714(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57f0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_57f0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5980: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_5980(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5acc: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_5acc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5b50: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_5b50(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5bc8: push { r3, r4, r5, lr } */
static void dllhologrammail_arm_5bc8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5d80: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_5d80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5fd4: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_5fd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6044: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_6044(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x60e4: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_60e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6228: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_6228(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6298: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_6298(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x63c8: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_63c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6414: push { r4, lr } */
static void dllhologrammail_arm_6414(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x644c: push { r4, lr } */
static void dllhologrammail_arm_644c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6560: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_6560(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6854: push { r4, lr } */
static void dllhologrammail_arm_6854(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6868: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_6868(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6928: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_6928(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6acc: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_6acc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6b84: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_6b84(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6bb4: push { r4, lr } */
static void dllhologrammail_arm_6bb4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6d48: push { r3, r4, r5, lr } */
static void dllhologrammail_arm_6d48(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f24: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_6f24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6fac: push { r4, lr } */
static void dllhologrammail_arm_6fac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7000: push { r4, lr } */
static void dllhologrammail_arm_7000(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7050: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_7050(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x71f0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_71f0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7330: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_7330(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x73a4: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_73a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7408: push { r3, r4, r5, lr } */
static void dllhologrammail_arm_7408(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x74ac: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_74ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x758c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_758c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7640: push { r4, lr } */
static void dllhologrammail_arm_7640(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x76a0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_76a0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x776c: push { r4, lr } */
static void dllhologrammail_arm_776c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7ad4: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_7ad4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7bd4: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_7bd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7d04: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_7d04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7d98: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_7d98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7f54: push { r4, r5, lr } */
static void dllhologrammail_arm_7f54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7fe0: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_7fe0(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x814c: push { r3, r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_814c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x81a8: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllhologrammail_arm_81a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8260: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_8260(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8304: push { r3, r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_8304(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x841c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_841c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8724: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_8724(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x88a0: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_88a0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8a98: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_8a98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8b54: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_8b54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8c44: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_8c44(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8cf0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_8cf0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8fc0: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_8fc0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x91c4: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_91c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x92a8: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_92a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9690: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_9690(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9854: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_9854(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98bc: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_98bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9af8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_9af8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ce0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_9ce0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9d68: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_9d68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa1b8: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_a1b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa274: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_a274(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa2e0: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_a2e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa3a4: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_a3a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa468: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_a468(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa568: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_a568(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa5f0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_a5f0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa750: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_a750(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa88c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_a88c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa90c: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_a90c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa97c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_a97c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa9fc: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_a9fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xab74: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_ab74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xabbc: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_abbc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xabf4: push { r4, lr } */
static void dllhologrammail_arm_abf4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xad1c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_ad1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xaf1c: push { r4, lr } */
static void dllhologrammail_arm_af1c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xaf2c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_af2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb050: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_b050(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb21c: push { r4, lr } */
static void dllhologrammail_arm_b21c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb244: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_b244(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb3a8: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_b3a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb638: push { r4, lr } */
static void dllhologrammail_arm_b638(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb6e8: push { r4, lr } */
static void dllhologrammail_arm_b6e8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb80c: push { r4, lr } */
static void dllhologrammail_arm_b80c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb83c: push { r4, lr } */
static void dllhologrammail_arm_b83c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb868: push { r4, lr } */
static void dllhologrammail_arm_b868(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb88c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_b88c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb8e8: push { r4, r5, lr } */
static void dllhologrammail_arm_b8e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbb6c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_bb6c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbc60: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_bc60(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbf78: push { r3, r4, r5, lr } */
static void dllhologrammail_arm_bf78(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbffc: push { r4, lr } */
static void dllhologrammail_arm_bffc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc060: push { r4, lr } */
static void dllhologrammail_arm_c060(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc0c8: push { r4, lr } */
static void dllhologrammail_arm_c0c8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc0f0: push { r4, lr } */
static void dllhologrammail_arm_c0f0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc2bc: push { r4, r5, lr } */
static void dllhologrammail_arm_c2bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc384: push { r4, lr } */
static void dllhologrammail_arm_c384(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc464: push { r4, lr } */
static void dllhologrammail_arm_c464(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc494: push { r4, lr } */
static void dllhologrammail_arm_c494(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc4c0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_c4c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc64c: push { r4, lr } */
static void dllhologrammail_arm_c64c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc68c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_c68c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc7dc: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_c7dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcccc: push { r4, lr } */
static void dllhologrammail_arm_cccc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xccf0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_ccf0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcd48: push { r4, lr } */
static void dllhologrammail_arm_cd48(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcde0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_cde0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcec0: push { r4, lr } */
static void dllhologrammail_arm_cec0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcef0: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_cef0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd13c: push { r4, lr } */
static void dllhologrammail_arm_d13c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd160: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_d160(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd204: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_d204(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd270: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_d270(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd290: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_d290(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd380: push { r4, lr } */
static void dllhologrammail_arm_d380(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd3ac: push { r4, lr } */
static void dllhologrammail_arm_d3ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd424: push { r4, lr } */
static void dllhologrammail_arm_d424(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd448: push { r4, lr } */
static void dllhologrammail_arm_d448(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd4b0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_d4b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd5e4: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_d5e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd660: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_d660(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd794: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_d794(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd95c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_d95c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdcd0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_dcd0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe05c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_e05c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe5e4: push { r4, lr } */
static void dllhologrammail_arm_e5e4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe620: push { r4, lr } */
static void dllhologrammail_arm_e620(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe664: push { r4, lr } */
static void dllhologrammail_arm_e664(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe690: push { r4, lr } */
static void dllhologrammail_arm_e690(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe6cc: push { r4, lr } */
static void dllhologrammail_arm_e6cc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe700: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_e700(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe8a8: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_e8a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe970: push { r4, lr } */
static void dllhologrammail_arm_e970(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe994: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_e994(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xea94: push { r4, lr } */
static void dllhologrammail_arm_ea94(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xeac4: push { r4, r5, r6, r7, lr } */
static void dllhologrammail_arm_eac4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xebec: push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_ebec(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf1c0: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_f1c0(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf47c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_f47c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf510: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_f510(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf5a0: push { r4, lr } */
static void dllhologrammail_arm_f5a0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf7d4: push { r4, lr } */
static void dllhologrammail_arm_f7d4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf80c: push { r4, lr } */
static void dllhologrammail_arm_f80c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf840: push { r4, lr } */
static void dllhologrammail_arm_f840(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf948: push { r4, lr } */
static void dllhologrammail_arm_f948(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf980: push { r4, lr } */
static void dllhologrammail_arm_f980(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf9e4: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_f9e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfa90: push { r4, lr } */
static void dllhologrammail_arm_fa90(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfabc: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_fabc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfb1c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllhologrammail_arm_fb1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfd04: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllhologrammail_arm_fd04(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1001c: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_1001c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10230: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_10230(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1030c: push { r4, lr } */
static void dllhologrammail_arm_1030c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10330: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_10330(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10428: push { r4, lr } */
static void dllhologrammail_arm_10428(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1044c: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_1044c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x104f8: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_104f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10528: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_10528(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10608: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_10608(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x106e0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_106e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10824: push { r4, lr } */
static void dllhologrammail_arm_10824(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10870: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_10870(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1095c: push { r4, lr } */
static void dllhologrammail_arm_1095c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10990: push { r4, lr } */
static void dllhologrammail_arm_10990(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10a88: push { r4, lr } */
static void dllhologrammail_arm_10a88(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10b28: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_10b28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10bd0: push { r4, lr } */
static void dllhologrammail_arm_10bd0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10c34: push { r4, lr } */
static void dllhologrammail_arm_10c34(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10c90: push { r4, lr } */
static void dllhologrammail_arm_10c90(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10cc0: push { r4, lr } */
static void dllhologrammail_arm_10cc0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10cf0: push { r4, lr } */
static void dllhologrammail_arm_10cf0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10d2c: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_10d2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10da8: push { r4, lr } */
static void dllhologrammail_arm_10da8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10dcc: push { r4, lr } */
static void dllhologrammail_arm_10dcc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10df0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_10df0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10e88: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllhologrammail_arm_10e88(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10f74: push { r4, lr } */
static void dllhologrammail_arm_10f74(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10f98: push { r4, lr } */
static void dllhologrammail_arm_10f98(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11008: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_11008(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x110e0: push { r4, r5, r6, lr } */
static void dllhologrammail_arm_110e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11100: push { r4, lr } */
static void dllhologrammail_arm_11100(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11138: push { r4, r5, r6, r7, r8, lr } */
static void dllhologrammail_arm_11138(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x111cc: push { r4, lr } */
static void dllhologrammail_arm_111cc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11200: push { r4, lr } */
static void dllhologrammail_arm_11200(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1162c: push { r4, lr } */
static void dllhologrammail_arm_1162c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11744: push { r4, lr } */
static void dllhologrammail_arm_11744(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1179c: push { r4, lr } */
static void dllhologrammail_arm_1179c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1184c: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllhologrammail_arm_1184c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11a18: push { r4, lr } */
static void dllhologrammail_arm_11a18(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11a7c: push { r4, lr } */
static void dllhologrammail_arm_11a7c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
