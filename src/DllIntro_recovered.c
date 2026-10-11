/*
 * Preliminary decompilation of DllIntro.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllIntro.info.md):
 *   file size           : 0xf000 (61,440)
 *   code                : offset 0x180 size 0xbe80
 *   data                : offset 0xe7c8 size 0x124
 *   bss size            : 0x8c
 *   exports named       : 2
 *   imports module      : 1
 *   external patches    : 246
 *
 * What was recovered:
 *   - 218 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x784). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 86 ARM and 0 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 171 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllIntro.imports.md): */
/*   index 0: `|static|` (224 anonymous symbols) */

/* Named exports (from docs/symbols/DllIntro.map): */
/*   CRO 0xa09c  nnroControlObject_  (segment tag 0x000a09c0) */
/*   CRO 0x9d30  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x0009d300) */

/*
 * Trampoline table (segment 0, 0x000..0x6d4, 218 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllIntro.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0858: push { r4, lr } */
static void dllintro_arm_0858(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0870: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_0870(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0a50: push { r4, lr } */
static void dllintro_arm_0a50(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0c58: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllintro_arm_0c58(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0d9c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllintro_arm_0d9c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f40: push { r4, r5, r6, lr } */
static void dllintro_arm_0f40(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1044: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_1044(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11c0: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_11c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1284: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_1284(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1344: push { r4, r5, r6, lr } */
static void dllintro_arm_1344(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1500: push { r4, lr } */
static void dllintro_arm_1500(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1514: push { r4, lr } */
static void dllintro_arm_1514(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1638: push { r4, lr } */
static void dllintro_arm_1638(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x164c: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_164c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1740: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_1740(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x18c8: push { r4, r5, r6, lr } */
static void dllintro_arm_18c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1988: push { r4, r5, r6, lr } */
static void dllintro_arm_1988(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1a44: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_1a44(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1b00: push { r4, r5, r6, lr } */
static void dllintro_arm_1b00(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1bf8: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_1bf8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1f10: push { r4, lr } */
static void dllintro_arm_1f10(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1f20: push { r4, r5, r6, lr } */
static void dllintro_arm_1f20(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x202c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllintro_arm_202c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x21e4: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_21e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x24a4: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllintro_arm_24a4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x28e4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllintro_arm_28e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2c04: push { r4, r5, r6, lr } */
static void dllintro_arm_2c04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2cec: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_2cec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2dec: push { r3, r4, r5, lr } */
static void dllintro_arm_2dec(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ee8: push { r4, r5, lr } */
static void dllintro_arm_2ee8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3000: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_3000(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3148: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_3148(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3248: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllintro_arm_3248(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3b08: push { r4, lr } */
static void dllintro_arm_3b08(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3c94: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_3c94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3e20: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_3e20(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4834: push { r4, lr } */
static void dllintro_arm_4834(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4934: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllintro_arm_4934(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5214: push { r4, lr } */
static void dllintro_arm_5214(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x55bc: push { r4, r5, r6, lr } */
static void dllintro_arm_55bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5738: push { r4, r5, r6, lr } */
static void dllintro_arm_5738(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6178: push { r4, r5, lr } */
static void dllintro_arm_6178(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6304: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_6304(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x63c8: push { r4, r5, r6, lr } */
static void dllintro_arm_63c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6474: push { r4, lr } */
static void dllintro_arm_6474(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x65d0: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_65d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x66cc: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_66cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6924: push { r4, lr } */
static void dllintro_arm_6924(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6960: push { r4, lr } */
static void dllintro_arm_6960(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a10: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_6a10(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a94: push { r4, r5, r6, lr } */
static void dllintro_arm_6a94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6b04: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_6b04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6b64: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllintro_arm_6b64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6dd0: push { r4, lr } */
static void dllintro_arm_6dd0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6de0: push { r4, r5, lr } */
static void dllintro_arm_6de0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ea0: push { r4, lr } */
static void dllintro_arm_6ea0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6eb4: push { r4, lr } */
static void dllintro_arm_6eb4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ed0: push { r4, r5, r6, lr } */
static void dllintro_arm_6ed0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7004: push { r4, r5, r6, lr } */
static void dllintro_arm_7004(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7104: push { r4, lr } */
static void dllintro_arm_7104(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7140: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_7140(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8888: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_8888(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x89f4: push { r4, r5, r6, lr } */
static void dllintro_arm_89f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8ab0: push { r4, r5, r6, lr } */
static void dllintro_arm_8ab0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8b64: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_8b64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8c14: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_8c14(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8dc8: push { r4, r5, r6, lr } */
static void dllintro_arm_8dc8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8e2c: push { r4, r5, lr } */
static void dllintro_arm_8e2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8ea8: push { r4, lr } */
static void dllintro_arm_8ea8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8ef0: push { r4, lr } */
static void dllintro_arm_8ef0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8f38: push { r4, lr } */
static void dllintro_arm_8f38(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8f78: push { r4, lr } */
static void dllintro_arm_8f78(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8f8c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_8f8c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x912c: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllintro_arm_912c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x91fc: push { r4, r5, r6, r7, lr } */
static void dllintro_arm_91fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x93fc: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_93fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9608: push { r4, lr } */
static void dllintro_arm_9608(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9644: push { r4, lr } */
static void dllintro_arm_9644(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x967c: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllintro_arm_967c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ba8: push { r4, r5, r6, r7, r8, lr } */
static void dllintro_arm_9ba8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c98: push { r4, r5, r6, lr } */
static void dllintro_arm_9c98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9d24: push { r4, r5, r6, lr } */
static void dllintro_arm_9d24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e44: push { r4, lr } */
static void dllintro_arm_9e44(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e7c: push { r4, lr } */
static void dllintro_arm_9e7c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ee4: push { r4, lr } */
static void dllintro_arm_9ee4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa224: push { r4, lr } */
static void dllintro_arm_a224(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
