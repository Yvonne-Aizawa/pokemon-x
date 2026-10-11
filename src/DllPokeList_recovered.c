/*
 * Preliminary decompilation of DllPokeList.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllPokeList.info.md):
 *   file size           : 0x17000 (94,208)
 *   code                : offset 0x180 size 0x12e80
 *   data                : offset 0x16b10 size 0x1c
 *   bss size            : 0x80
 *   exports named       : 2
 *   imports module      : 1
 *   external patches    : 289
 *
 * What was recovered:
 *   - 235 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x80c). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 204 ARM and 0 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 346 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllPokeList.imports.md): */
/*   index 0: `|static|` (257 anonymous symbols) */

/* Named exports (from docs/symbols/DllPokeList.map): */
/*   CRO 0x10470  nnroControlObject_  (segment tag 0x00104700) */
/*   CRO 0xff94  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x000ff940) */

/*
 * Trampoline table (segment 0, 0x000..0x75c, 235 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllPokeList.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0910: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_0910(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0a54: push { r4, lr } */
static void dllpokelist_arm_0a54(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0ab0: push { r4, lr } */
static void dllpokelist_arm_0ab0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0b04: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_0b04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0d68: push { r4, r5, r6, lr } */
static void dllpokelist_arm_0d68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0e30: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_0e30(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0fc8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_0fc8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10e8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_10e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1208: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_1208(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1340: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_1340(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1498: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_1498(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x15e0: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_15e0(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1734: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_1734(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x19c4: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_19c4(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1dd0: push { r4, lr } */
static void dllpokelist_arm_1dd0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1de0: push { r4, r5, r6, lr } */
static void dllpokelist_arm_1de0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e88: push { r4, r5 } */
static void dllpokelist_arm_1e88(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0x1f70: push { r4, r5, r6, lr } */
static void dllpokelist_arm_1f70(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2058: push { r4, r5, r6, lr } */
static void dllpokelist_arm_2058(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x21c0: push { r4, r5, r6, lr } */
static void dllpokelist_arm_21c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x221c: push { r4, r5, r6, lr } */
static void dllpokelist_arm_221c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2278: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_2278(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x248c: push { r4, lr } */
static void dllpokelist_arm_248c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x24cc: push { r4, lr } */
static void dllpokelist_arm_24cc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2508: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_2508(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2820: push { r4, r5, r6, lr } */
static void dllpokelist_arm_2820(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2884: push { r4, r5, lr } */
static void dllpokelist_arm_2884(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2af8: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_2af8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2b70: push { r4, r5, lr } */
static void dllpokelist_arm_2b70(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ce0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_2ce0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e58: push { r4, r5, lr } */
static void dllpokelist_arm_2e58(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2fa8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_2fa8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3414: push { r4, r5, lr } */
static void dllpokelist_arm_3414(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3500: push { r4, r5, r6, lr } */
static void dllpokelist_arm_3500(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x357c: push { r4, r5, lr } */
static void dllpokelist_arm_357c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x35e4: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_35e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37d8: push { r4, lr } */
static void dllpokelist_arm_37d8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37e8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_37e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3970: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_3970(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3acc: push { r4, r5, r6, lr } */
static void dllpokelist_arm_3acc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3b44: push { r4, lr } */
static void dllpokelist_arm_3b44(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3b54: push { r4, r5, r6, lr } */
static void dllpokelist_arm_3b54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3c04: push { r4, r5, r6, lr } */
static void dllpokelist_arm_3c04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3c5c: push { r4, r5, r6, r7, lr } */
static void dllpokelist_arm_3c5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3edc: push { r4, r5, r6, lr } */
static void dllpokelist_arm_3edc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3f3c: push { r4, lr } */
static void dllpokelist_arm_3f3c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4020: push { r4, r5, lr } */
static void dllpokelist_arm_4020(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4078: push { r4, lr } */
static void dllpokelist_arm_4078(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x408c: push { r4, r5, r6, r7, lr } */
static void dllpokelist_arm_408c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x46fc: push { r4, r5, r6, lr } */
static void dllpokelist_arm_46fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4754: push { r4, r5, r6, lr } */
static void dllpokelist_arm_4754(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47ac: push { r4, r5, r6, lr } */
static void dllpokelist_arm_47ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x492c: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_492c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4d74: push { r4, r5, lr } */
static void dllpokelist_arm_4d74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5004: push { r4, r5, r6, lr } */
static void dllpokelist_arm_5004(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5184: push { r4, r5, r6, lr } */
static void dllpokelist_arm_5184(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5304: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_5304(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x54bc: push { r4, r5, r6, lr } */
static void dllpokelist_arm_54bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5710: push { r4, r5, lr } */
static void dllpokelist_arm_5710(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57e8: push { r4, r5, r6, r7, lr } */
static void dllpokelist_arm_57e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5a38: push { r4, r5, lr } */
static void dllpokelist_arm_5a38(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5b90: push { r4, r5, lr } */
static void dllpokelist_arm_5b90(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c68: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_5c68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x609c: push { r3, r4, r5, r6, r7, lr } */
static void dllpokelist_arm_609c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x613c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_613c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x61b0: push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_61b0(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6428: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_6428(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x64ec: push { r4, lr } */
static void dllpokelist_arm_64ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x656c: push { r4, lr } */
static void dllpokelist_arm_656c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x668c: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_668c(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x68b8: push { r4, lr } */
static void dllpokelist_arm_68b8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x69a4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_69a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a24: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_6a24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6b08: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_6b08(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6c6c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_6c6c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6d68: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_6d68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6e44: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllpokelist_arm_6e44(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f48: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_6f48(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x70fc: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_70fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7210: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_7210(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x73a8: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_73a8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7770: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_7770(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7860: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_7860(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x78bc: push { r4, r5, r6, lr } */
static void dllpokelist_arm_78bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x795c: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_795c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7a68: push { r4, r5, r6, lr } */
static void dllpokelist_arm_7a68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7b38: push { r4, lr } */
static void dllpokelist_arm_7b38(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7b78: push { r4, lr } */
static void dllpokelist_arm_7b78(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7bd8: push { r4, r5, r6, r7, lr } */
static void dllpokelist_arm_7bd8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7c8c: push { r4, lr } */
static void dllpokelist_arm_7c8c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7cc8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_7cc8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7da4: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_7da4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7e24: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_7e24(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7f40: push { r4, r5, r6, lr } */
static void dllpokelist_arm_7f40(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7fb4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_7fb4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8020: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_8020(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x80c0: push { r4, r5, r6, lr } */
static void dllpokelist_arm_80c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x813c: push { r4, r5, r6, lr } */
static void dllpokelist_arm_813c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x81b0: push { r4, r5, r6, lr } */
static void dllpokelist_arm_81b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8214: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_8214(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8288: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_8288(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x86e8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_86e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8864: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_8864(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x88dc: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_88dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8aac: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_8aac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8dc8: push { r4, r5, r6, lr } */
static void dllpokelist_arm_8dc8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8e94: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_8e94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8f88: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_8f88(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x94e8: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_94e8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9668: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_9668(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x97a4: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_97a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9828: push { r4, lr } */
static void dllpokelist_arm_9828(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9878: push { r4, lr } */
static void dllpokelist_arm_9878(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x98e0: push { r4, r5, r6, r7, lr } */
static void dllpokelist_arm_98e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9b30: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_9b30(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c3c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_9c3c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa38c: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_a38c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa840: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_a840(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xacb0: push { r4, r5, lr } */
static void dllpokelist_arm_acb0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xaf8c: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_af8c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb434: push { r4, r5, r6, lr } */
static void dllpokelist_arm_b434(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb798: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_b798(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbc48: push { r4, r5, r6, lr } */
static void dllpokelist_arm_bc48(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbca8: push { r4, lr } */
static void dllpokelist_arm_bca8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbd8c: push { r4, r5, lr } */
static void dllpokelist_arm_bd8c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbe08: push { r4, lr } */
static void dllpokelist_arm_be08(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbe1c: push { r4, r5, r6, lr } */
static void dllpokelist_arm_be1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbe80: push { r4, r5, r6, lr } */
static void dllpokelist_arm_be80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xbed8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_bed8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc224: push { r4, r5, r6, lr } */
static void dllpokelist_arm_c224(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc284: push { r4, lr } */
static void dllpokelist_arm_c284(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc368: push { r4, r5, lr } */
static void dllpokelist_arm_c368(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc3cc: push { r4, lr } */
static void dllpokelist_arm_c3cc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc3e0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_c3e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc55c: push { r4, r5, r6, lr } */
static void dllpokelist_arm_c55c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc5c0: push { r4, r5, r6, lr } */
static void dllpokelist_arm_c5c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc618: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_c618(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc97c: push { r4, r5, r6, lr } */
static void dllpokelist_arm_c97c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xc9dc: push { r4, lr } */
static void dllpokelist_arm_c9dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcac0: push { r4, r5, lr } */
static void dllpokelist_arm_cac0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcb24: push { r4, lr } */
static void dllpokelist_arm_cb24(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcb38: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_cb38(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xccb4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_ccb4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcd18: push { r4, r5, r6, lr } */
static void dllpokelist_arm_cd18(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xcd70: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_cd70(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd0d4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_d0d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd134: push { r4, lr } */
static void dllpokelist_arm_d134(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd218: push { r4, r5, lr } */
static void dllpokelist_arm_d218(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd27c: push { r4, lr } */
static void dllpokelist_arm_d27c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd290: push { r4, r5, r6, lr } */
static void dllpokelist_arm_d290(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd2b0: push { r4, lr } */
static void dllpokelist_arm_d2b0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd33c: push { r4, r5, r6, lr } */
static void dllpokelist_arm_d33c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd454: push { r4, lr } */
static void dllpokelist_arm_d454(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd4d0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_d4d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd5c4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_d5c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd6d4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_d6d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xd874: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_d874(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xda30: push { r4, r5, r6, lr } */
static void dllpokelist_arm_da30(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdb9c: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_db9c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdd5c: push { r4, lr } */
static void dllpokelist_arm_dd5c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdeb4: push { r4, r5, r6, lr } */
static void dllpokelist_arm_deb4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xdf40: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_df40(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe0b8: push { r4, r5, r6, lr } */
static void dllpokelist_arm_e0b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe168: push { r4, lr } */
static void dllpokelist_arm_e168(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe1b0: push { r4, lr } */
static void dllpokelist_arm_e1b0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe1f0: push { r3, r4, r5, lr } */
static void dllpokelist_arm_e1f0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe270: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_e270(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe350: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_e350(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe508: push { r4, r5, r6, r7, lr } */
static void dllpokelist_arm_e508(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe678: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_e678(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe7b0: push { r3, r4, r5, lr } */
static void dllpokelist_arm_e7b0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe818: push { r3, r4, r5, lr } */
static void dllpokelist_arm_e818(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe888: push { r3, r4, r5, lr } */
static void dllpokelist_arm_e888(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe8f0: push { r3, r4, r5, lr } */
static void dllpokelist_arm_e8f0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xe958: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllpokelist_arm_e958(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xeab4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_eab4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xeeac: push { r4, lr } */
static void dllpokelist_arm_eeac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xeebc: push { r4, lr } */
static void dllpokelist_arm_eebc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xef9c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_ef9c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf0fc: push { r4, r5, r6, r7, r8, lr } */
static void dllpokelist_arm_f0fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf2f0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_f2f0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf508: push { r4, r5, r6, lr } */
static void dllpokelist_arm_f508(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf5c0: push { r4, r5, r6, lr } */
static void dllpokelist_arm_f5c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf6b0: push { r4, lr } */
static void dllpokelist_arm_f6b0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf6ec: push { r4, lr } */
static void dllpokelist_arm_f6ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xf700: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_f700(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfd3c: push { r4, lr } */
static void dllpokelist_arm_fd3c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfd4c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllpokelist_arm_fd4c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xfe00: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllpokelist_arm_fe00(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xff44: push { r3, r4, r5, r6, r7, lr } */
static void dllpokelist_arm_ff44(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1001c: push { r4, lr } */
static void dllpokelist_arm_1001c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10060: push { r4, lr } */
static void dllpokelist_arm_10060(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x100a8: push { r4, lr } */
static void dllpokelist_arm_100a8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x100e0: push { r4, lr } */
static void dllpokelist_arm_100e0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10260: push { r4, lr } */
static void dllpokelist_arm_10260(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x102bc: push { r4, lr } */
static void dllpokelist_arm_102bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10314: push { r4, lr } */
static void dllpokelist_arm_10314(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10328: push { r4, lr } */
static void dllpokelist_arm_10328(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1033c: push { r4, lr } */
static void dllpokelist_arm_1033c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10384: push { r4, lr } */
static void dllpokelist_arm_10384(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10408: push { r4, lr } */
static void dllpokelist_arm_10408(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10464: push { r4, lr } */
static void dllpokelist_arm_10464(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x104bc: push { r4, lr } */
static void dllpokelist_arm_104bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x105f8: push { r4, lr } */
static void dllpokelist_arm_105f8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
