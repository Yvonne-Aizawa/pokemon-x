/*
 * Preliminary decompilation of DllKisekae.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllKisekae.info.md):
 *   file size           : 0x11000 (69,632)
 *   code                : offset 0x180 size 0xde80
 *   data                : offset 0x103b0 size 0x678
 *   bss size            : 0x44
 *   exports named       : 1
 *   imports module      : 1
 *   external patches    : 271
 *
 * What was recovered:
 *   - 242 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x844). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 102 ARM and 1 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 144 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllKisekae.imports.md): */
/*   index 0: `|static|` (254 anonymous symbols) */

/* Named exports (from docs/symbols/DllKisekae.map): */
/*   CRO 0xb744  nnroControlObject_  (segment tag 0x000b7440) */

/*
 * Trampoline table (segment 0, 0x000..0x790, 242 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllKisekae.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0924: push { r4, lr } */
static void dllkisekae_arm_0924(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0954: push { r4, lr } */
static void dllkisekae_arm_0954(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0974: push { r4, r5, r6, lr } */
static void dllkisekae_arm_0974(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x09d0: push { r4, r5, lr } */
static void dllkisekae_arm_09d0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0c28: push { r4, r5, r6, lr } */
static void dllkisekae_arm_0c28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0d28: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_0d28(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f48: push { r4, lr } */
static void dllkisekae_arm_0f48(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f88: push { r4, r5, r6, lr } */
static void dllkisekae_arm_0f88(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1078: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_1078(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1270: push { r4, r5, r6, lr } */
static void dllkisekae_arm_1270(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1300: push { r4, r5, r6, lr } */
static void dllkisekae_arm_1300(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x13bc: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_13bc(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x14bc: push { r4, lr } */
static void dllkisekae_arm_14bc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x14e8: push { r4, lr } */
static void dllkisekae_arm_14e8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1520: push { r4, lr } */
static void dllkisekae_arm_1520(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1554: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_1554(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1834: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_1834(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x19b0: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_19b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1c0c: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllkisekae_arm_1c0c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1d58: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_1d58(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1e14: push { r4, r5, r6, lr } */
static void dllkisekae_arm_1e14(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1fb8: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllkisekae_arm_1fb8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2220: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllkisekae_arm_2220(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2820: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_2820(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2a40: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_2a40(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2cfc: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_2cfc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e88: push { r4, lr } */
static void dllkisekae_arm_2e88(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2eac: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllkisekae_arm_2eac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37d0: push { r4, lr } */
static void dllkisekae_arm_37d0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x380c: push { r4, lr } */
static void dllkisekae_arm_380c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3844: push { r4, lr } */
static void dllkisekae_arm_3844(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3938: push { r4, lr } */
static void dllkisekae_arm_3938(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3978: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_3978(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x39ec: push { r4, lr } */
static void dllkisekae_arm_39ec(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a54: push { r4, lr } */
static void dllkisekae_arm_3a54(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ab8: push { r4, r5, r6, lr } */
static void dllkisekae_arm_3ab8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ce0: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_3ce0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x40e8: push { r4, r5, r6, lr } */
static void dllkisekae_arm_40e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x427c: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_427c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4338: push { r4, r5, lr } */
static void dllkisekae_arm_4338(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4470: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllkisekae_arm_4470(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4734: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllkisekae_arm_4734(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x497c: push { r4, r5 } */
static void dllkisekae_arm_497c(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0x4a4c: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllkisekae_arm_4a4c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4bcc: push { r4, lr } */
static void dllkisekae_arm_4bcc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c78: push { r4, r5, r6, lr } */
static void dllkisekae_arm_4c78(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4ccc: push { r4, r5, r6, lr } */
static void dllkisekae_arm_4ccc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4e4c: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_4e4c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4f74: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_4f74(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x534c: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_534c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5474: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllkisekae_arm_5474(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57ac: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_57ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x588c: push { r4, r5, r6, lr } */
static void dllkisekae_arm_588c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5958: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_5958(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5ba8: push { r4, r5, r6, lr } */
static void dllkisekae_arm_5ba8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c5c: push { r4, r5, r6, lr } */
static void dllkisekae_arm_5c5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5cfc: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllkisekae_arm_5cfc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e04: push { r4, lr } */
static void dllkisekae_arm_5e04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5fb8: push { r4, lr } */
static void dllkisekae_arm_5fb8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6058: push { r4, r5, r6, lr } */
static void dllkisekae_arm_6058(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x60d4: push { r4, r5, r6, lr } */
static void dllkisekae_arm_60d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6150: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllkisekae_arm_6150(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x66e4: push { r4, r5, r6, lr } */
static void dllkisekae_arm_66e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x684c: push { r4, lr } */
static void dllkisekae_arm_684c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6898: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_6898(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a04: push { r4, r5, r6, lr } */
static void dllkisekae_arm_6a04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6b38: push { r4, lr } */
static void dllkisekae_arm_6b38(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6bd8: push { r4, r5, r6, lr } */
static void dllkisekae_arm_6bd8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ca0: push { r4, r5, r6, lr } */
static void dllkisekae_arm_6ca0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6d30: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_6d30(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6e24: push { r4, r5, r6, lr } */
static void dllkisekae_arm_6e24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ee0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllkisekae_arm_6ee0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x713c: push { r4, lr } */
static void dllkisekae_arm_713c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x724c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllkisekae_arm_724c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x83e8: push { r4, r5, lr } */
static void dllkisekae_arm_83e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x84dc: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllkisekae_arm_84dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8b24: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllkisekae_arm_8b24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8d74: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllkisekae_arm_8d74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8f58: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_8f58(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9158: push { r4, lr } */
static void dllkisekae_arm_9158(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x92a4: push { r4, lr } */
static void dllkisekae_arm_92a4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9304: push { r4, lr } */
static void dllkisekae_arm_9304(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9364: push { r4, r5, r6, lr } */
static void dllkisekae_arm_9364(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x963c: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_963c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9a68: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_9a68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9bc0: push { r4, r5, r6, lr } */
static void dllkisekae_arm_9bc0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c54: push { r4, lr } */
static void dllkisekae_arm_9c54(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9cb0: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_9cb0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9de0: push { r4, r5, r6, lr } */
static void dllkisekae_arm_9de0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9f44: push { r4, r5, r6, r7, r8, lr } */
static void dllkisekae_arm_9f44(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa074: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_a074(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa334: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllkisekae_arm_a334(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa56c: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_a56c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa7fc: push { r3, r4, r5, r6, r7, lr } */
static void dllkisekae_arm_a7fc(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa9c0: push { r4, r5, lr } */
static void dllkisekae_arm_a9c0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xaba4: push { r4, r5, r6, lr } */
static void dllkisekae_arm_aba4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xad20: push { r4, r5, r6, lr } */
static void dllkisekae_arm_ad20(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb010: push { r4, r5, r6, r7, lr } */
static void dllkisekae_arm_b010(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb674: push { r4, lr } */
static void dllkisekae_arm_b674(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb6ac: push { r4, lr } */
static void dllkisekae_arm_b6ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb6fc: push { r4, r5, r6, r7, r8, r9, sl } */
static void dllkisekae_arm_b6fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl }; ... ; pop { ..., pc } */ }

/* ARM 0xb8cc: push { r4, lr } */
static void dllkisekae_arm_b8cc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x9c3a: push { r4, r7, lr } */
static void dllkisekae_thumb_9c3a(void) /* TODO: not yet decoded */
{ /* push { r4, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
