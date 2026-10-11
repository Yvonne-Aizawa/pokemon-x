/*
 * Preliminary decompilation of DllPssMainMenu.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 37 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllPssMainMenu */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4d50 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x5c (92 bytes) */
/* Named exports  : 2 */
/* External patches : 104 */
/* Imported modules  : 1 */
/* ARM prologues  : 37 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x236c id=0 */
/*   seg 1: offset=0x3000 size=0x4c4 id=1 */
/*   seg 2: offset=0x4d50 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x3c id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x45a8 anonymous_count=99 */

/* === Named exports === */
/* CRO 0x22bc -> `nnroControlObject_` (segment 0) */
/* CRO 0x2108 -> `_ZN9xy_system2bg6System13SetIsCallDrawEb` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x22bc. */
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
/* Located at CRO 0x2108. */
/* The original is two instructions: `strb r1, [r0, #0xd9]; bx lr`. */
/* It is a non-virtual helper that flips the BG system's `IsCallDraw` byte */
/* (offset 0xd9 in the BG system object) and returns. */
/* TODO: not yet decoded - body recovered as a one-liner. */

/* === Forward declarations for identified function boundaries === */
static void DllPssMainMenu_02c0(void);
static void DllPssMainMenu_0434(void);
static void DllPssMainMenu_04f8(void);
static void DllPssMainMenu_0580(void);
static void DllPssMainMenu_0620(void);
static void DllPssMainMenu_07c0(void);
static void DllPssMainMenu_0804(void);
static void DllPssMainMenu_0844(void);
static void DllPssMainMenu_091c(void);
static void DllPssMainMenu_0b40(void);
static void DllPssMainMenu_0c88(void);
static void DllPssMainMenu_0d60(void);
static void DllPssMainMenu_0dc8(void);
static void DllPssMainMenu_0f14(void);
static void DllPssMainMenu_0fec(void);
static void DllPssMainMenu_1148(void);
static void DllPssMainMenu_11f0(void);
static void DllPssMainMenu_12f0(void);
static void DllPssMainMenu_1318(void);
static void DllPssMainMenu_1344(void);
static void DllPssMainMenu_1410(void);
static void DllPssMainMenu_1564(void);
static void DllPssMainMenu_1690(void);
static void DllPssMainMenu_18f4(void);
static void DllPssMainMenu_1a44(void);
static void DllPssMainMenu_1dac(void);
static void DllPssMainMenu_1e04(void);
static void DllPssMainMenu_1e5c(void);
static void DllPssMainMenu_1e98(void);
static void DllPssMainMenu_1ed0(void);
static void DllPssMainMenu_1f48(void);
static void DllPssMainMenu_2028(void);
static void DllPssMainMenu_2060(void);
static void DllPssMainMenu_209c(void);
static void DllPssMainMenu_20d4(void);
static void DllPssMainMenu_2118(void);
static void DllPssMainMenu_22c4(void);

/* === Patch table (segment-0 trampolines) === */
/* 104 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x02c0 */
static void DllPssMainMenu_02c0(void) {
    /* TODO: not yet decoded - body of function 0x02c0 */
}

/* CRO 0x0434 */
static void DllPssMainMenu_0434(void) {
    /* TODO: not yet decoded - body of function 0x0434 */
}

/* CRO 0x04f8 */
static void DllPssMainMenu_04f8(void) {
    /* TODO: not yet decoded - body of function 0x04f8 */
}

/* CRO 0x0580 */
static void DllPssMainMenu_0580(void) {
    /* TODO: not yet decoded - body of function 0x0580 */
}

/* CRO 0x0620 */
static void DllPssMainMenu_0620(void) {
    /* TODO: not yet decoded - body of function 0x0620 */
}

/* CRO 0x07c0 */
static void DllPssMainMenu_07c0(void) {
    /* TODO: not yet decoded - body of function 0x07c0 */
}

/* CRO 0x0804 */
static void DllPssMainMenu_0804(void) {
    /* TODO: not yet decoded - body of function 0x0804 */
}

/* CRO 0x0844 */
static void DllPssMainMenu_0844(void) {
    /* TODO: not yet decoded - body of function 0x0844 */
}

/* CRO 0x091c */
static void DllPssMainMenu_091c(void) {
    /* TODO: not yet decoded - body of function 0x091c */
}

/* CRO 0x0b40 */
static void DllPssMainMenu_0b40(void) {
    /* TODO: not yet decoded - body of function 0x0b40 */
}

/* CRO 0x0c88 */
static void DllPssMainMenu_0c88(void) {
    /* TODO: not yet decoded - body of function 0x0c88 */
}

/* CRO 0x0d60 */
static void DllPssMainMenu_0d60(void) {
    /* TODO: not yet decoded - body of function 0x0d60 */
}

/* CRO 0x0dc8 */
static void DllPssMainMenu_0dc8(void) {
    /* TODO: not yet decoded - body of function 0x0dc8 */
}

/* CRO 0x0f14 */
static void DllPssMainMenu_0f14(void) {
    /* TODO: not yet decoded - body of function 0x0f14 */
}

/* CRO 0x0fec */
static void DllPssMainMenu_0fec(void) {
    /* TODO: not yet decoded - body of function 0x0fec */
}

/* CRO 0x1148 */
static void DllPssMainMenu_1148(void) {
    /* TODO: not yet decoded - body of function 0x1148 */
}

/* CRO 0x11f0 */
static void DllPssMainMenu_11f0(void) {
    /* TODO: not yet decoded - body of function 0x11f0 */
}

/* CRO 0x12f0 */
static void DllPssMainMenu_12f0(void) {
    /* TODO: not yet decoded - body of function 0x12f0 */
}

/* CRO 0x1318 */
static void DllPssMainMenu_1318(void) {
    /* TODO: not yet decoded - body of function 0x1318 */
}

/* CRO 0x1344 */
static void DllPssMainMenu_1344(void) {
    /* TODO: not yet decoded - body of function 0x1344 */
}

/* CRO 0x1410 */
static void DllPssMainMenu_1410(void) {
    /* TODO: not yet decoded - body of function 0x1410 */
}

/* CRO 0x1564 */
static void DllPssMainMenu_1564(void) {
    /* TODO: not yet decoded - body of function 0x1564 */
}

/* CRO 0x1690 */
static void DllPssMainMenu_1690(void) {
    /* TODO: not yet decoded - body of function 0x1690 */
}

/* CRO 0x18f4 */
static void DllPssMainMenu_18f4(void) {
    /* TODO: not yet decoded - body of function 0x18f4 */
}

/* CRO 0x1a44 */
static void DllPssMainMenu_1a44(void) {
    /* TODO: not yet decoded - body of function 0x1a44 */
}

/* CRO 0x1dac */
static void DllPssMainMenu_1dac(void) {
    /* TODO: not yet decoded - body of function 0x1dac */
}

/* CRO 0x1e04 */
static void DllPssMainMenu_1e04(void) {
    /* TODO: not yet decoded - body of function 0x1e04 */
}

/* CRO 0x1e5c */
static void DllPssMainMenu_1e5c(void) {
    /* TODO: not yet decoded - body of function 0x1e5c */
}

/* CRO 0x1e98 */
static void DllPssMainMenu_1e98(void) {
    /* TODO: not yet decoded - body of function 0x1e98 */
}

/* CRO 0x1ed0 */
static void DllPssMainMenu_1ed0(void) {
    /* TODO: not yet decoded - body of function 0x1ed0 */
}

/* CRO 0x1f48 */
static void DllPssMainMenu_1f48(void) {
    /* TODO: not yet decoded - body of function 0x1f48 */
}

/* CRO 0x2028 */
static void DllPssMainMenu_2028(void) {
    /* TODO: not yet decoded - body of function 0x2028 */
}

/* CRO 0x2060 */
static void DllPssMainMenu_2060(void) {
    /* TODO: not yet decoded - body of function 0x2060 */
}

/* CRO 0x209c */
static void DllPssMainMenu_209c(void) {
    /* TODO: not yet decoded - body of function 0x209c */
}

/* CRO 0x20d4 */
static void DllPssMainMenu_20d4(void) {
    /* TODO: not yet decoded - body of function 0x20d4 */
}

/* CRO 0x2118 */
static void DllPssMainMenu_2118(void) {
    /* TODO: not yet decoded - body of function 0x2118 */
}

/* CRO 0x22c4 */
static void DllPssMainMenu_22c4(void) {
    /* TODO: not yet decoded - body of function 0x22c4 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0620 -> DllPssMainMenu_0620 */
/*   0x091c -> DllPssMainMenu_091c */
/*   0x0b40 -> DllPssMainMenu_0b40 */
/*   0x0dc8 -> DllPssMainMenu_0dc8 */
/*   0x0f14 -> DllPssMainMenu_0f14 */
/*   0x1148 -> DllPssMainMenu_1148 */
/*   0x1410 -> DllPssMainMenu_1410 */
/*   0x1564 -> DllPssMainMenu_1564 */
/*   0x18f4 -> DllPssMainMenu_18f4 */
/*   0x1a44 -> DllPssMainMenu_1a44 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
