/*
 * Preliminary decompilation of DllNuts.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllNuts.info.md):
 *   file size           : 0x12000 (73,728)
 *   code                : offset 0x180 size 0xee80
 *   data                : offset 0x10c78 size 0x38c
 *   bss size            : 0x30c
 *   exports named       : 1
 *   imports module      : 1
 *   external patches    : 202
 *
 * What was recovered:
 *   - 177 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0x63c). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 87 ARM and 2 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 129 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllNuts.imports.md): */
/*   index 0: `|static|` (186 anonymous symbols) */

/* Named exports (from docs/symbols/DllNuts.map): */
/*   CRO 0x87e0  nnroControlObject_  (segment tag 0x00087e00) */

/*
 * Trampoline table (segment 0, 0x000..0x588, 177 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllNuts.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0750: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllnuts_arm_0750(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x09e8: push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_09e8(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0ce8: push { r4, r5, r6, lr } */
static void dllnuts_arm_0ce8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0e30: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllnuts_arm_0e30(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0fd0: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_0fd0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1134: push { r4, r5, r6, lr } */
static void dllnuts_arm_1134(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1178: push { r4, r5, r6, lr } */
static void dllnuts_arm_1178(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11bc: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_11bc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x12cc: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_12cc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x13f4: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_13f4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x17f4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_17f4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1ab0: push { r4, r5, r6, lr } */
static void dllnuts_arm_1ab0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1b34: push { r4, r5, r6, lr } */
static void dllnuts_arm_1b34(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1bb8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllnuts_arm_1bb8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2050: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_2050(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2218: push { r4, r5, r6, lr } */
static void dllnuts_arm_2218(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2270: push { r4, r5, r6, lr } */
static void dllnuts_arm_2270(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x22c8: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_22c8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x234c: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_234c(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2448: push { r4, r5, lr } */
static void dllnuts_arm_2448(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2550: push { r4, r5, r6, r7 } */
static void dllnuts_arm_2550(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7 }; ... ; pop { ..., pc } */ }

/* ARM 0x25fc: push { r4, r5, r6, r7, lr } */
static void dllnuts_arm_25fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x27b0: push { r4, r5, r6, r7, lr } */
static void dllnuts_arm_27b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2940: push { r4, r5, r6, lr } */
static void dllnuts_arm_2940(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2984: push { r4, r5, r6, lr } */
static void dllnuts_arm_2984(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x29c8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_29c8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2c68: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dllnuts_arm_2c68(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e00: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_2e00(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x31b4: push { r4, r5, r6, r7, lr } */
static void dllnuts_arm_31b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3390: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_3390(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3774: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_3774(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x37dc: push { r4, r5, r6, lr } */
static void dllnuts_arm_37dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x388c: push { r4, r5, r6, lr } */
static void dllnuts_arm_388c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3938: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_3938(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a5c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllnuts_arm_3a5c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3cb8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_3cb8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3de4: push { r4, r5, r6, r7, lr } */
static void dllnuts_arm_3de4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3e94: push { r4, r5, r6, r7, lr } */
static void dllnuts_arm_3e94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x40b0: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllnuts_arm_40b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4348: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllnuts_arm_4348(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4534: push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_4534(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x48b0: push { r4, r5, r6, lr } */
static void dllnuts_arm_48b0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x49bc: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_49bc(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4b04: push { r3, r4, r5, lr } */
static void dllnuts_arm_4b04(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4c74: push { r4, lr } */
static void dllnuts_arm_4c74(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4cc0: push { r4, r5, r6, lr } */
static void dllnuts_arm_4cc0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4d94: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_4d94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4e6c: push { r4, r5, r6, r7, lr } */
static void dllnuts_arm_4e6c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4ef8: push { r4, r5 } */
static void dllnuts_arm_4ef8(void) /* TODO: not yet decoded */
{ /* push { r4, r5 }; ... ; pop { ..., pc } */ }

/* ARM 0x4f80: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_4f80(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5084: push { r4, lr } */
static void dllnuts_arm_5084(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x50d4: push { r4, r5, r6, lr } */
static void dllnuts_arm_50d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5124: push { r4, r5, r6, lr } */
static void dllnuts_arm_5124(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5174: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_5174(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x53a8: push { r4, r5, r6, lr } */
static void dllnuts_arm_53a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5494: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllnuts_arm_5494(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x55b4: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_55b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57a0: push { r4, r5, r6, lr } */
static void dllnuts_arm_57a0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x57f8: push { r4, r5, r6, lr } */
static void dllnuts_arm_57f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5850: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_5850(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5ad0: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_5ad0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5bb4: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_5bb4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5db8: push { r4, r5, r6, lr } */
static void dllnuts_arm_5db8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e10: push { r4, r5, r6, lr } */
static void dllnuts_arm_5e10(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5e8c: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_5e8c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6130: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_6130(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x62c4: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_62c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6630: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dllnuts_arm_6630(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x681c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllnuts_arm_681c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6a54: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_6a54(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6cd0: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dllnuts_arm_6cd0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ed0: push { r4, r5, r6, lr } */
static void dllnuts_arm_6ed0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6ff4: push { r4, r5, r6, lr } */
static void dllnuts_arm_6ff4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x70f4: push { r4, lr } */
static void dllnuts_arm_70f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7230: push { r4, r5, r6, r7, r8, r9, lr } */
static void dllnuts_arm_7230(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7740: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dllnuts_arm_7740(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7bac: push { r4, lr } */
static void dllnuts_arm_7bac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7c18: push { r4, lr } */
static void dllnuts_arm_7c18(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7c50: push { r4, lr } */
static void dllnuts_arm_7c50(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7c84: push { r3, r4, r5, r6, r7, lr } */
static void dllnuts_arm_7c84(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7dd4: push { r4, r5, r6, r7, r8, lr } */
static void dllnuts_arm_7dd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7f84: push { r4, r5, r6, lr } */
static void dllnuts_arm_7f84(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7fdc: push { r4, r5, r6, lr } */
static void dllnuts_arm_7fdc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8038: push { r4, lr } */
static void dllnuts_arm_8038(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8070: push { r4, lr } */
static void dllnuts_arm_8070(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x80ac: push { r4, lr } */
static void dllnuts_arm_80ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8968: push { r4, lr } */
static void dllnuts_arm_8968(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x0836: push { r6, r7, lr } */
static void dllnuts_thumb_0836(void) /* TODO: not yet decoded */
{ /* push { r6, r7, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0x083a: push { r2, r6, r7, lr } */
static void dllnuts_thumb_083a(void) /* TODO: not yet decoded */
{ /* push { r2, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
