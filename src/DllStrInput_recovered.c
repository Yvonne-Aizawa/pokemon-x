/*
 * Preliminary decompilation of DllStrInput.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllStrInput.info.md):
 *   file size           : 0xc000 (49,152)
 *   code                : offset 0x180 size 0x9e80
 *   data                : offset 0xb600 size 0x24
 *   bss size            : 0x5c
 *   exports named       : 2
 *   imports module      : 1
 *   external patches    : 160
 *
 * What was recovered:
 *   - 150 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x564). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 66 ARM and 2 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 119 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllStrInput.imports.md): */
/*   index 0: `|static|` (156 anonymous symbols) */

/* Named exports (from docs/symbols/DllStrInput.map): */
/*   CRO 0x65d0  nnroControlObject_  (segment tag 0x00065d00) */
/*   CRO 0x64ec  _ZN9xy_system2bg6System13SetIsCallDrawEb  (segment tag 0x00064ec0) */

/*
 * Trampoline table (segment 0, 0x000..0x4b0, 150 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllStrInput.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0630: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllstrinput_arm_0630(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0714: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_0714(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x08e4: push { r4, lr } */
static void dllstrinput_arm_08e4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0900: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_0900(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0e50: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_0e50(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1464: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllstrinput_arm_1464(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1eac: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_1eac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x20e0: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_20e0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2238: push { r4, r5, r6, lr } */
static void dllstrinput_arm_2238(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x22e8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_22e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x23dc: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstrinput_arm_23dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x25a8: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllstrinput_arm_25a8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2708: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_2708(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2984: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_2984(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2a5c: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_2a5c(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2be0: push { r4, r5, r6, r7, r8, r9, sl } */
static void dllstrinput_arm_2be0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl }; ... ; pop { ..., pc } */ }

/* ARM 0x2cf4: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllstrinput_arm_2cf4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2de8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_2de8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x30b0: push { r3, lr } */
static void dllstrinput_arm_30b0(void) /* TODO: not yet decoded */
{ /* push { r3, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3170: push { r4, r5, r6, r7 } */
static void dllstrinput_arm_3170(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7 }; ... ; pop { ..., pc } */ }

/* ARM 0x3218: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllstrinput_arm_3218(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x32a4: push { r4, r5 } */
static void dllstrinput_arm_32a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0x33ac: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_33ac(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3408: push { r4, r5, r6, lr } */
static void dllstrinput_arm_3408(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x34bc: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_34bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3554: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_3554(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x35f8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_35f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x380c: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_380c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a24: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_3a24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3ac4: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_3ac4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3c50: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_3c50(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3cd8: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_3cd8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3e3c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstrinput_arm_3e3c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3fe0: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_3fe0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4110: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllstrinput_arm_4110(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x42d8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_42d8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x46c4: push { r4, r5, r6, lr } */
static void dllstrinput_arm_46c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4734: push { r4, r5, lr } */
static void dllstrinput_arm_4734(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47c4: push { r4, r5, r6, lr } */
static void dllstrinput_arm_47c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x48f4: push { r4, lr } */
static void dllstrinput_arm_48f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4a04: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_4a04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4b10: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_4b10(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x50a8: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_50a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5208: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_5208(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x530c: push { r4, lr } */
static void dllstrinput_arm_530c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x532c: push { r4, lr } */
static void dllstrinput_arm_532c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5344: push { r4, lr } */
static void dllstrinput_arm_5344(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5438: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_5438(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5518: push { r4, r5, r6, r7, lr } */
static void dllstrinput_arm_5518(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5618: push { r3, r4, r5, lr } */
static void dllstrinput_arm_5618(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5774: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_5774(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c38: push { r4, r5, r6, lr } */
static void dllstrinput_arm_5c38(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c88: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllstrinput_arm_5c88(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e2c: push { r4, r5, r6, lr } */
static void dllstrinput_arm_5e2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5efc: push { r4, lr } */
static void dllstrinput_arm_5efc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x60d4: push { r4, r5, r6, lr } */
static void dllstrinput_arm_60d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6150: push { r4, lr } */
static void dllstrinput_arm_6150(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x61dc: push { r4, lr } */
static void dllstrinput_arm_61dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6224: push { r3, r4, r5, lr } */
static void dllstrinput_arm_6224(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6298: push { r4, lr } */
static void dllstrinput_arm_6298(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6300: push { r4, lr } */
static void dllstrinput_arm_6300(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6360: push { r4, r5, r6, r7, r8, lr } */
static void dllstrinput_arm_6360(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6478: push { r4, r5, r6, r7, lr } */
static void dllstrinput_arm_6478(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6600: push { r4, lr } */
static void dllstrinput_arm_6600(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6638: push { r4, lr } */
static void dllstrinput_arm_6638(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6758: push { r4, lr } */
static void dllstrinput_arm_6758(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x3650: push { r1, r2, r4, r5, r7, lr } */
static void dllstrinput_thumb_3650(void) /* TODO: not yet decoded */
{ /* push { r1, r2, r4, r5, r7, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0x4f28: push { r1, r2, r4, r5, r7, lr } */
static void dllstrinput_thumb_4f28(void) /* TODO: not yet decoded */
{ /* push { r1, r2, r4, r5, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
