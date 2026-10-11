/*
 * Preliminary decompilation of DllEshop.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 30 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllEShop */
/* File size      : 0x6000 (24576 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x5298 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x5c (92 bytes) */
/* Named exports  : 2 */
/* External patches : 138 */
/* Imported modules  : 1 */
/* ARM prologues  : 30 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x27f4 id=0 */
/*   seg 1: offset=0x3000 size=0x45c id=1 */
/*   seg 2: offset=0x5298 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x3c id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x473c anonymous_count=131 */

/* === Named exports === */
/* CRO 0x2744 -> `nnroControlObject_` (segment 0) */
/* CRO 0x2564 -> `_ZN9xy_system2bg6System13SetIsCallDrawEb` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x2744. */
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
/* Located at CRO 0x2564. */
/* The original is two instructions: `strb r1, [r0, #0xd9]; bx lr`. */
/* It is a non-virtual helper that flips the BG system's `IsCallDraw` byte */
/* (offset 0xd9 in the BG system object) and returns. */
/* TODO: not yet decoded - body recovered as a one-liner. */

/* === Forward declarations for identified function boundaries === */
static void DllEshop_03d4(void);
static void DllEshop_040c(void);
static void DllEshop_0470(void);
static void DllEshop_0710(void);
static void DllEshop_07a8(void);
static void DllEshop_0840(void);
static void DllEshop_0aa4(void);
static void DllEshop_1288(void);
static void DllEshop_1378(void);
static void DllEshop_13f8(void);
static void DllEshop_1530(void);
static void DllEshop_15d0(void);
static void DllEshop_1824(void);
static void DllEshop_1888(void);
static void DllEshop_18e8(void);
static void DllEshop_1990(void);
static void DllEshop_19bc(void);
static void DllEshop_1ae4(void);
static void DllEshop_1b40(void);
static void DllEshop_1b94(void);
static void DllEshop_1ca8(void);
static void DllEshop_1e14(void);
static void DllEshop_200c(void);
static void DllEshop_2058(void);
static void DllEshop_20c0(void);
static void DllEshop_2444(void);
static void DllEshop_2458(void);
static void DllEshop_2574(void);
static void DllEshop_25c0(void);
static void DllEshop_274c(void);

/* === Patch table (segment-0 trampolines) === */
/* 138 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x03d4 */
static void DllEshop_03d4(void) {
    /* TODO: not yet decoded - body of function 0x03d4 */
}

/* CRO 0x040c */
static void DllEshop_040c(void) {
    /* TODO: not yet decoded - body of function 0x040c */
}

/* CRO 0x0470 */
static void DllEshop_0470(void) {
    /* TODO: not yet decoded - body of function 0x0470 */
}

/* CRO 0x0710 */
static void DllEshop_0710(void) {
    /* TODO: not yet decoded - body of function 0x0710 */
}

/* CRO 0x07a8 */
static void DllEshop_07a8(void) {
    /* TODO: not yet decoded - body of function 0x07a8 */
}

/* CRO 0x0840 */
static void DllEshop_0840(void) {
    /* TODO: not yet decoded - body of function 0x0840 */
}

/* CRO 0x0aa4 */
static void DllEshop_0aa4(void) {
    /* TODO: not yet decoded - body of function 0x0aa4 */
}

/* CRO 0x1288 */
static void DllEshop_1288(void) {
    /* TODO: not yet decoded - body of function 0x1288 */
}

/* CRO 0x1378 */
static void DllEshop_1378(void) {
    /* TODO: not yet decoded - body of function 0x1378 */
}

/* CRO 0x13f8 */
static void DllEshop_13f8(void) {
    /* TODO: not yet decoded - body of function 0x13f8 */
}

/* CRO 0x1530 */
static void DllEshop_1530(void) {
    /* TODO: not yet decoded - body of function 0x1530 */
}

/* CRO 0x15d0 */
static void DllEshop_15d0(void) {
    /* TODO: not yet decoded - body of function 0x15d0 */
}

/* CRO 0x1824 */
static void DllEshop_1824(void) {
    /* TODO: not yet decoded - body of function 0x1824 */
}

/* CRO 0x1888 */
static void DllEshop_1888(void) {
    /* TODO: not yet decoded - body of function 0x1888 */
}

/* CRO 0x18e8 */
static void DllEshop_18e8(void) {
    /* TODO: not yet decoded - body of function 0x18e8 */
}

/* CRO 0x1990 */
static void DllEshop_1990(void) {
    /* TODO: not yet decoded - body of function 0x1990 */
}

/* CRO 0x19bc */
static void DllEshop_19bc(void) {
    /* TODO: not yet decoded - body of function 0x19bc */
}

/* CRO 0x1ae4 */
static void DllEshop_1ae4(void) {
    /* TODO: not yet decoded - body of function 0x1ae4 */
}

/* CRO 0x1b40 */
static void DllEshop_1b40(void) {
    /* TODO: not yet decoded - body of function 0x1b40 */
}

/* CRO 0x1b94 */
static void DllEshop_1b94(void) {
    /* TODO: not yet decoded - body of function 0x1b94 */
}

/* CRO 0x1ca8 */
static void DllEshop_1ca8(void) {
    /* TODO: not yet decoded - body of function 0x1ca8 */
}

/* CRO 0x1e14 */
static void DllEshop_1e14(void) {
    /* TODO: not yet decoded - body of function 0x1e14 */
}

/* CRO 0x200c */
static void DllEshop_200c(void) {
    /* TODO: not yet decoded - body of function 0x200c */
}

/* CRO 0x2058 */
static void DllEshop_2058(void) {
    /* TODO: not yet decoded - body of function 0x2058 */
}

/* CRO 0x20c0 */
static void DllEshop_20c0(void) {
    /* TODO: not yet decoded - body of function 0x20c0 */
}

/* CRO 0x2444 */
static void DllEshop_2444(void) {
    /* TODO: not yet decoded - body of function 0x2444 */
}

/* CRO 0x2458 */
static void DllEshop_2458(void) {
    /* TODO: not yet decoded - body of function 0x2458 */
}

/* CRO 0x2574 */
static void DllEshop_2574(void) {
    /* TODO: not yet decoded - body of function 0x2574 */
}

/* CRO 0x25c0 */
static void DllEshop_25c0(void) {
    /* TODO: not yet decoded - body of function 0x25c0 */
}

/* CRO 0x274c */
static void DllEshop_274c(void) {
    /* TODO: not yet decoded - body of function 0x274c */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0aa4 -> DllEshop_0aa4 */
/*   0x13f8 -> DllEshop_13f8 */
/*   0x1530 -> DllEshop_1530 */
/*   0x15d0 -> DllEshop_15d0 */
/*   0x1b94 -> DllEshop_1b94 */
/*   0x1ca8 -> DllEshop_1ca8 */
/*   0x1e14 -> DllEshop_1e14 */
/*   0x20c0 -> DllEshop_20c0 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x0388 -> imported via patch at seg_off 0x388 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
