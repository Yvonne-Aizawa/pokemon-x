/*
 * Preliminary decompilation of DllCaptureRegister.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 43 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllCaptureRegister */
/* File size      : 0x6000 (24576 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x5898 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x68 (104 bytes) */
/* Named exports  : 2 */
/* External patches : 180 */
/* Imported modules  : 3 */
/* ARM prologues  : 43 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x2a20 id=0 */
/*   seg 1: offset=0x3000 size=0x508 id=1 */
/*   seg 2: offset=0x5898 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x48 id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x4964 anonymous_count=88 */
/* index 1: module `DllZukan` */
/*   anonymous_head=0x4c24 anonymous_count=41 */
/* index 2: module `DllBattle` */
/*   anonymous_head=0x4d6c anonymous_count=15 */

/* === Named exports === */
/* CRO 0x2970 -> `nnroControlObject_` (segment 0) */
/* CRO 0x2630 -> `_ZN9xy_system2bg6System13SetIsCallDrawEb` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x2970. */
/* Standard pattern: dispatches on `r1` (selector 0..5) via the inline jump */
/* table populated by the loader (`ldrcc pc, [pc, r1, lsl #2]`). Selectors: */
/*   0 -> no-op / self-init, */
/*   1 -> returns 0, */
/*   2 -> stores r0 into the module's global object pointer, */
/*   3 -> loads the global object pointer into *r0, */
/*   4 -> initialises a two-word header at *r0, */
/*   5 -> returns an error pointer. */
/* TODO: not yet decoded - the body is documented at a high level only. */

/* === `xy_system::bg::System::SetIsCallDraw(bool)` shim === */
/* Located at CRO 0x2630. */
/* The original is two instructions: `strb r1, [r0, #0xd9]; bx lr`. */
/* It is a non-virtual helper that flips the BG system's `IsCallDraw` byte */
/* (offset 0xd9 in the BG system object) and returns. */
/* TODO: not yet decoded - body recovered as a one-liner. */

/* === Forward declarations for identified function boundaries === */
static void DllCaptureRegister_03e8(void);
static void DllCaptureRegister_05e0(void);
static void DllCaptureRegister_08a0(void);
static void DllCaptureRegister_0910(void);
static void DllCaptureRegister_097c(void);
static void DllCaptureRegister_09d0(void);
static void DllCaptureRegister_09e4(void);
static void DllCaptureRegister_0aa4(void);
static void DllCaptureRegister_0b28(void);
static void DllCaptureRegister_0b78(void);
static void DllCaptureRegister_0cf8(void);
static void DllCaptureRegister_0e84(void);
static void DllCaptureRegister_0fa8(void);
static void DllCaptureRegister_10e8(void);
static void DllCaptureRegister_1258(void);
static void DllCaptureRegister_1378(void);
static void DllCaptureRegister_1480(void);
static void DllCaptureRegister_159c(void);
static void DllCaptureRegister_164c(void);
static void DllCaptureRegister_1670(void);
static void DllCaptureRegister_1940(void);
static void DllCaptureRegister_1998(void);
static void DllCaptureRegister_19f4(void);
static void DllCaptureRegister_1e38(void);
static void DllCaptureRegister_1e90(void);
static void DllCaptureRegister_1edc(void);
static void DllCaptureRegister_1f34(void);
static void DllCaptureRegister_1fb4(void);
static void DllCaptureRegister_2090(void);
static void DllCaptureRegister_21cc(void);
static void DllCaptureRegister_2258(void);
static void DllCaptureRegister_22dc(void);
static void DllCaptureRegister_2334(void);
static void DllCaptureRegister_2360(void);
static void DllCaptureRegister_2514(void);
static void DllCaptureRegister_2564(void);
static void DllCaptureRegister_25c4(void);
static void DllCaptureRegister_25fc(void);
static void DllCaptureRegister_26c8(void);
static void DllCaptureRegister_2788(void);
static void DllCaptureRegister_27e0(void);
static void DllCaptureRegister_283c(void);
static void DllCaptureRegister_2978(void);

/* === Patch table (segment-0 trampolines) === */
/* 180 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x03e8 */
static void DllCaptureRegister_03e8(void) {
    /* TODO: not yet decoded - body of function 0x03e8 */
}

/* CRO 0x05e0 */
static void DllCaptureRegister_05e0(void) {
    /* TODO: not yet decoded - body of function 0x05e0 */
}

/* CRO 0x08a0 */
static void DllCaptureRegister_08a0(void) {
    /* TODO: not yet decoded - body of function 0x08a0 */
}

/* CRO 0x0910 */
static void DllCaptureRegister_0910(void) {
    /* TODO: not yet decoded - body of function 0x0910 */
}

/* CRO 0x097c */
static void DllCaptureRegister_097c(void) {
    /* TODO: not yet decoded - body of function 0x097c */
}

/* CRO 0x09d0 */
static void DllCaptureRegister_09d0(void) {
    /* TODO: not yet decoded - body of function 0x09d0 */
}

/* CRO 0x09e4 */
static void DllCaptureRegister_09e4(void) {
    /* TODO: not yet decoded - body of function 0x09e4 */
}

/* CRO 0x0aa4 */
static void DllCaptureRegister_0aa4(void) {
    /* TODO: not yet decoded - body of function 0x0aa4 */
}

/* CRO 0x0b28 */
static void DllCaptureRegister_0b28(void) {
    /* TODO: not yet decoded - body of function 0x0b28 */
}

/* CRO 0x0b78 */
static void DllCaptureRegister_0b78(void) {
    /* TODO: not yet decoded - body of function 0x0b78 */
}

/* CRO 0x0cf8 */
static void DllCaptureRegister_0cf8(void) {
    /* TODO: not yet decoded - body of function 0x0cf8 */
}

/* CRO 0x0e84 */
static void DllCaptureRegister_0e84(void) {
    /* TODO: not yet decoded - body of function 0x0e84 */
}

/* CRO 0x0fa8 */
static void DllCaptureRegister_0fa8(void) {
    /* TODO: not yet decoded - body of function 0x0fa8 */
}

/* CRO 0x10e8 */
static void DllCaptureRegister_10e8(void) {
    /* TODO: not yet decoded - body of function 0x10e8 */
}

/* CRO 0x1258 */
static void DllCaptureRegister_1258(void) {
    /* TODO: not yet decoded - body of function 0x1258 */
}

/* CRO 0x1378 */
static void DllCaptureRegister_1378(void) {
    /* TODO: not yet decoded - body of function 0x1378 */
}

/* CRO 0x1480 */
static void DllCaptureRegister_1480(void) {
    /* TODO: not yet decoded - body of function 0x1480 */
}

/* CRO 0x159c */
static void DllCaptureRegister_159c(void) {
    /* TODO: not yet decoded - body of function 0x159c */
}

/* CRO 0x164c */
static void DllCaptureRegister_164c(void) {
    /* TODO: not yet decoded - body of function 0x164c */
}

/* CRO 0x1670 */
static void DllCaptureRegister_1670(void) {
    /* TODO: not yet decoded - body of function 0x1670 */
}

/* CRO 0x1940 */
static void DllCaptureRegister_1940(void) {
    /* TODO: not yet decoded - body of function 0x1940 */
}

/* CRO 0x1998 */
static void DllCaptureRegister_1998(void) {
    /* TODO: not yet decoded - body of function 0x1998 */
}

/* CRO 0x19f4 */
static void DllCaptureRegister_19f4(void) {
    /* TODO: not yet decoded - body of function 0x19f4 */
}

/* CRO 0x1e38 */
static void DllCaptureRegister_1e38(void) {
    /* TODO: not yet decoded - body of function 0x1e38 */
}

/* CRO 0x1e90 */
static void DllCaptureRegister_1e90(void) {
    /* TODO: not yet decoded - body of function 0x1e90 */
}

/* CRO 0x1edc */
static void DllCaptureRegister_1edc(void) {
    /* TODO: not yet decoded - body of function 0x1edc */
}

/* CRO 0x1f34 */
static void DllCaptureRegister_1f34(void) {
    /* TODO: not yet decoded - body of function 0x1f34 */
}

/* CRO 0x1fb4 */
static void DllCaptureRegister_1fb4(void) {
    /* TODO: not yet decoded - body of function 0x1fb4 */
}

/* CRO 0x2090 */
static void DllCaptureRegister_2090(void) {
    /* TODO: not yet decoded - body of function 0x2090 */
}

/* CRO 0x21cc */
static void DllCaptureRegister_21cc(void) {
    /* TODO: not yet decoded - body of function 0x21cc */
}

/* CRO 0x2258 */
static void DllCaptureRegister_2258(void) {
    /* TODO: not yet decoded - body of function 0x2258 */
}

/* CRO 0x22dc */
static void DllCaptureRegister_22dc(void) {
    /* TODO: not yet decoded - body of function 0x22dc */
}

/* CRO 0x2334 */
static void DllCaptureRegister_2334(void) {
    /* TODO: not yet decoded - body of function 0x2334 */
}

/* CRO 0x2360 */
static void DllCaptureRegister_2360(void) {
    /* TODO: not yet decoded - body of function 0x2360 */
}

/* CRO 0x2514 */
static void DllCaptureRegister_2514(void) {
    /* TODO: not yet decoded - body of function 0x2514 */
}

/* CRO 0x2564 */
static void DllCaptureRegister_2564(void) {
    /* TODO: not yet decoded - body of function 0x2564 */
}

/* CRO 0x25c4 */
static void DllCaptureRegister_25c4(void) {
    /* TODO: not yet decoded - body of function 0x25c4 */
}

/* CRO 0x25fc */
static void DllCaptureRegister_25fc(void) {
    /* TODO: not yet decoded - body of function 0x25fc */
}

/* CRO 0x26c8 */
static void DllCaptureRegister_26c8(void) {
    /* TODO: not yet decoded - body of function 0x26c8 */
}

/* CRO 0x2788 */
static void DllCaptureRegister_2788(void) {
    /* TODO: not yet decoded - body of function 0x2788 */
}

/* CRO 0x27e0 */
static void DllCaptureRegister_27e0(void) {
    /* TODO: not yet decoded - body of function 0x27e0 */
}

/* CRO 0x283c */
static void DllCaptureRegister_283c(void) {
    /* TODO: not yet decoded - body of function 0x283c */
}

/* CRO 0x2978 */
static void DllCaptureRegister_2978(void) {
    /* TODO: not yet decoded - body of function 0x2978 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x03e8 -> DllCaptureRegister_03e8 */
/*   0x05e0 -> DllCaptureRegister_05e0 */
/*   0x1480 -> DllCaptureRegister_1480 */
/*   0x2090 -> DllCaptureRegister_2090 */
/*   0x2360 -> DllCaptureRegister_2360 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x00c0 -> imported via patch at seg_off 0xc0 */
/*   0x00c8 -> imported via patch at seg_off 0xc8 */
/*   0x00d0 -> imported via patch at seg_off 0xd0 */
/*   0x0120 -> imported via patch at seg_off 0x120 */
/*   0x0130 -> imported via patch at seg_off 0x130 */
/*   0x0140 -> imported via patch at seg_off 0x140 */
/*   0x0150 -> imported via patch at seg_off 0x150 */
/*   0x0168 -> imported via patch at seg_off 0x168 */
/*   0x0170 -> imported via patch at seg_off 0x170 */
/*   0x0178 -> imported via patch at seg_off 0x178 */
/*   0x02e8 -> imported via patch at seg_off 0x2e8 */
/*   0x02f0 -> imported via patch at seg_off 0x2f0 */
/*   0x0300 -> imported via patch at seg_off 0x300 */
/*   0x0320 -> imported via patch at seg_off 0x320 */
/*   0x0328 -> imported via patch at seg_off 0x328 */
/*   0x0338 -> imported via patch at seg_off 0x338 */
/*   0x0348 -> imported via patch at seg_off 0x348 */
/*   0x0380 -> imported via patch at seg_off 0x380 */
/*   0x03c0 -> imported via patch at seg_off 0x3c0 */
/*   0x03d0 -> imported via patch at seg_off 0x3d0 */
/*   0x03d8 -> imported via patch at seg_off 0x3d8 */
/*   0x03e8 -> imported via patch at seg_off 0x3e8 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
