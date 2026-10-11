/*
 * Preliminary decompilation of DllTradelist.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 *
 * Module facts (from work/modules/DllTradelist.info.md):
 *   file size           : 0x11000 (69,632)
 *   code                : offset 0x180 size 0xde80
 *   data                : offset 0x10990 size 0x68
 *   bss size            : 0x44
 *   exports named       : 1
 *   imports module      : 1
 *   external patches    : 341
 *
 * What was recovered:
 *   - 312 ARM `ldr pc, [pc, #4]` import trampolines at the start of
 *     segment 0 (file offset 0x180..0xa74). Each slot is 8
 *     bytes: 4-byte ARM veneer followed by the 4-byte target word that the
 *     loader fills from `|static|` (and any other imported module).
 *   - 138 ARM and 3 Thumb function prologues
 *     in the .text segment, identified by `push {..., lr}` patterns.
 *   - 233 `pop {..., pc}` returns that bound those prologues into
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

/* Imported modules (from work/modules/DllTradelist.imports.md): */
/*   index 0: `|static|` (329 anonymous symbols) */

/* Named exports (from docs/symbols/DllTradelist.map): */
/*   CRO 0xb5fc  nnroControlObject_  (segment tag 0x000b5fc0) */

/*
 * Trampoline table (segment 0, 0x000..0x9c0, 312 slots).
 * Each slot: {e51ff004; <target>}; the target is fixed up by the loader.
 * Identified external calls include the patches in work/modules/DllTradelist.patches.md.
 */

/* ==== ARM function boundaries (segment 0 offsets) ==== */
/* Each prologue was identified from a `push {{..., lr}}` instruction. */
/* Bodies are not yet decoded — register saves are recorded. */

/* ARM 0x0c04: push { r4, lr } */
static void dlltradelist_arm_0c04(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0c3c: push { r4, lr } */
static void dlltradelist_arm_0c3c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0c74: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dlltradelist_arm_0c74(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x0f98: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_0f98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x10e8: push { r4, r5, r6, lr } */
static void dlltradelist_arm_10e8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1170: push { r4, r5, r6, lr } */
static void dlltradelist_arm_1170(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x11f4: push { r4, lr } */
static void dlltradelist_arm_11f4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x122c: push { r4, r5, r6, r7, lr } */
static void dlltradelist_arm_122c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x13c4: push { r4, r5, r6, lr } */
static void dlltradelist_arm_13c4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1444: push { r4, r5, r6, r7, lr } */
static void dlltradelist_arm_1444(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1c2c: push { r4, r5, r6, r7, lr } */
static void dlltradelist_arm_1c2c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1dd4: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_1dd4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x1fe8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_1fe8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x25e4: push { r4, lr } */
static void dlltradelist_arm_25e4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2634: push { r4, lr } */
static void dlltradelist_arm_2634(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2698: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_2698(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2910: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_2910(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2b7c: push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_2b7c(void) /* TODO: not yet decoded */
{ /* push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2cd0: push { r4, lr } */
static void dlltradelist_arm_2cd0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2dc4: push { r3, r4, r5, lr } */
static void dlltradelist_arm_2dc4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2e10: push { r4, r5, r6, lr } */
static void dlltradelist_arm_2e10(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2ee0: push { r3, r4, r5, lr } */
static void dlltradelist_arm_2ee0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2f70: push { r4, lr } */
static void dlltradelist_arm_2f70(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x2f98: push { r3, r4, r5, lr } */
static void dlltradelist_arm_2f98(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x30b0: push { r3, r4, r5, r6, r7, lr } */
static void dlltradelist_arm_30b0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x32d4: push { r4, r5, r6, lr } */
static void dlltradelist_arm_32d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3318: push { r4, lr } */
static void dlltradelist_arm_3318(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3350: push { r4, r5, r6, r7, lr } */
static void dlltradelist_arm_3350(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x343c: push { r4, r5, r6, lr } */
static void dlltradelist_arm_343c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x351c: push { r4, lr } */
static void dlltradelist_arm_351c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3564: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_3564(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x365c: push { r4, r5, r6, lr } */
static void dlltradelist_arm_365c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3714: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_3714(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3858: push { r4, lr } */
static void dlltradelist_arm_3858(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x38d4: push { r3, r4, r5, r6, r7, lr } */
static void dlltradelist_arm_38d4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3a7c: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_3a7c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3b98: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlltradelist_arm_3b98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3d54: push { r4, lr } */
static void dlltradelist_arm_3d54(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3d98: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_3d98(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3eec: push { r4, r5, r6, lr } */
static void dlltradelist_arm_3eec(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x3fb8: push { r4, r5, r6, lr } */
static void dlltradelist_arm_3fb8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x409c: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_409c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4224: push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_4224(void) /* TODO: not yet decoded */
{ /* push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4408: push { r4, r5, r6, lr } */
static void dlltradelist_arm_4408(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4454: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_4454(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4688: push { r4, r5, r6, lr } */
static void dlltradelist_arm_4688(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x47a0: push { r3, r4, r5, r6, r7, lr } */
static void dlltradelist_arm_47a0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x481c: push { r4, lr } */
static void dlltradelist_arm_481c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4864: push { r4, r5, r6, lr } */
static void dlltradelist_arm_4864(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x48a8: push { r3, r4, r5, lr } */
static void dlltradelist_arm_48a8(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x48dc: push { r4, r5, r6, lr } */
static void dlltradelist_arm_48dc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4a50: push { r4, r5, r6, lr } */
static void dlltradelist_arm_4a50(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4acc: push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_4acc(void) /* TODO: not yet decoded */
{ /* push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4d98: push { r3, r4, r5, lr } */
static void dlltradelist_arm_4d98(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4de4: push { r3, r4, r5, lr } */
static void dlltradelist_arm_4de4(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4e54: push { r4, r5, r6, lr } */
static void dlltradelist_arm_4e54(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4ec0: push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_4ec0(void) /* TODO: not yet decoded */
{ /* push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x4f94: push { r4, r5, r6, lr } */
static void dlltradelist_arm_4f94(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5044: push { r4, r5, r6, r7, r8, r9, lr } */
static void dlltradelist_arm_5044(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5284: push { r4, r5, r6, lr } */
static void dlltradelist_arm_5284(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x52dc: push { r4, lr } */
static void dlltradelist_arm_52dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5414: push { r4, lr } */
static void dlltradelist_arm_5414(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5440: push { r4, lr } */
static void dlltradelist_arm_5440(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5480: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_5480(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5638: push { r3, r4, r5, r6, r7, r8, r9, lr } */
static void dlltradelist_arm_5638(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5804: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_5804(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5b1c: push { r4, r5, r6, lr } */
static void dlltradelist_arm_5b1c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5c04: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_5c04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5d50: push { r4, r5, r6 } */
static void dlltradelist_arm_5d50(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6 }; ... ; pop { ..., pc } */ }

/* ARM 0x5e04: push { r4, r5, r6, lr } */
static void dlltradelist_arm_5e04(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5eb0: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_5eb0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5f58: push { r4, r5, r6, lr } */
static void dlltradelist_arm_5f58(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x5f9c: push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_5f9c(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6060: push { r4, r5, r6, lr } */
static void dlltradelist_arm_6060(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6144: push { r3, r4, r5, r6, r7, lr } */
static void dlltradelist_arm_6144(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x62d4: push { r4, r5, r6, r7, r8, r9, sl, fp } */
static void dlltradelist_arm_62d4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp }; ... ; pop { ..., pc } */ }

/* ARM 0x638c: push { r4, r5, r6, lr } */
static void dlltradelist_arm_638c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6454: push { r4, r5, r6, lr } */
static void dlltradelist_arm_6454(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6530: push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_6530(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6620: push { r4, r5, r6, lr } */
static void dlltradelist_arm_6620(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x66a4: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_66a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x69e4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_69e4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6b34: push { r4, r5, r6, lr } */
static void dlltradelist_arm_6b34(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6c24: push { r4, r5, r6, r7 } */
static void dlltradelist_arm_6c24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7 }; ... ; pop { ..., pc } */ }

/* ARM 0x6cf0: push { r4, r5, r6, lr } */
static void dlltradelist_arm_6cf0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6db0: push { r4, r5, r6, lr } */
static void dlltradelist_arm_6db0(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x6f24: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_6f24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x70fc: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_70fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7204: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dlltradelist_arm_7204(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7368: push { r4, r5, r6, lr } */
static void dlltradelist_arm_7368(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7488: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_7488(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7500: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_7500(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7a08: push { r4, lr } */
static void dlltradelist_arm_7a08(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7b24: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_7b24(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x7fb8: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_7fb8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8148: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_8148(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x829c: push { r4, r5, r6, r7, lr } */
static void dlltradelist_arm_829c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8434: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dlltradelist_arm_8434(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8694: push { r4, lr } */
static void dlltradelist_arm_8694(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x86b8: push { r4, r5, lr } */
static void dlltradelist_arm_86b8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x878c: push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_878c(void) /* TODO: not yet decoded */
{ /* push { r0, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8b00: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_8b00(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8de8: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_8de8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x8fc4: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_8fc4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x91fc: push { r4, lr } */
static void dlltradelist_arm_91fc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x931c: push { r4, r5, r6, r7, r8, r9, sl, lr } */
static void dlltradelist_arm_931c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9668: push { r4, lr } */
static void dlltradelist_arm_9668(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x96a0: push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_96a0(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9848: push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr } */
static void dlltradelist_arm_9848(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, ip, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x99a8: push { r4, r5, r6, r7, r8, lr } */
static void dlltradelist_arm_99a8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9ac8: push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_9ac8(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9c64: push { r4, r5, r6, lr } */
static void dlltradelist_arm_9c64(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9d80: push { r4, r5, r6, lr } */
static void dlltradelist_arm_9d80(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0x9e20: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_9e20(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa03c: push { r4, r5, r6, lr } */
static void dlltradelist_arm_a03c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa11c: push { r4, r5, r6, lr } */
static void dlltradelist_arm_a11c(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa1f8: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_a1f8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa5b4: push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_a5b4(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xa944: push { r4, r5, r6, r7, r8, r9, sl, fp, lr } */
static void dlltradelist_arm_a944(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, r7, r8, r9, sl, fp, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xadb0: push { r4, lr } */
static void dlltradelist_arm_adb0(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xadc4: push { r4, r5, r6, lr } */
static void dlltradelist_arm_adc4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb0b4: push { r4, r5, r6, lr } */
static void dlltradelist_arm_b0b4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb0d8: push { r4, r5, r6, lr } */
static void dlltradelist_arm_b0d8(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb0fc: push { r4, r5, r6, lr } */
static void dlltradelist_arm_b0fc(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb164: push { r4, lr } */
static void dlltradelist_arm_b164(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb298: push { r4, lr } */
static void dlltradelist_arm_b298(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb2dc: push { r4, lr } */
static void dlltradelist_arm_b2dc(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb320: push { r4, lr } */
static void dlltradelist_arm_b320(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb3a4: push { r4, r5, r6, lr } */
static void dlltradelist_arm_b3a4(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb464: push { r3, r4, r5, r6, r7, lr } */
static void dlltradelist_arm_b464(void) /* TODO: not yet decoded */
{ /* push { r3, r4, r5, r6, r7, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb4c4: push { r4, lr } */
static void dlltradelist_arm_b4c4(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb518: push { r4, lr } */
static void dlltradelist_arm_b518(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb568: push { r4, r5, r6, lr } */
static void dlltradelist_arm_b568(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb5ac: push { r4, lr } */
static void dlltradelist_arm_b5ac(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb60c: push { r4, lr } */
static void dlltradelist_arm_b60c(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb630: push { r4, r5, r6, lr } */
static void dlltradelist_arm_b630(void) /* TODO: not yet decoded */
{ /* push { r4, r5, r6, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb6f8: push { r4, lr } */
static void dlltradelist_arm_b6f8(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ARM 0xb784: push { r4, lr } */
static void dlltradelist_arm_b784(void) /* TODO: not yet decoded */
{ /* push { r4, lr }; ... ; pop { ..., pc } */ }

/* ==== Thumb function boundaries (segment 0 offsets) ==== */

/* Thumb 0x5e3e: push { r7, lr } */
static void dlltradelist_thumb_5e3e(void) /* TODO: not yet decoded */
{ /* push { r7, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0x5e4a: push { r7, lr } */
static void dlltradelist_thumb_5e4a(void) /* TODO: not yet decoded */
{ /* push { r7, lr }; ... ; pop { ..., pc } */ }

/* Thumb 0x5ff2: push { r0, r1, r2, r3, r4, r7, lr } */
static void dlltradelist_thumb_5ff2(void) /* TODO: not yet decoded */
{ /* push { r0, r1, r2, r3, r4, r7, lr }; ... ; pop { ..., pc } */ }

/* End of preliminary reconstruction. */
