/*
 * Preliminary decompilation of DllPssFavorite.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 36 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllPssFavorite */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4dd0 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x5c (92 bytes) */
/* Named exports  : 2 */
/* External patches : 107 */
/* Imported modules  : 1 */
/* ARM prologues  : 36 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x2180 id=0 */
/*   seg 1: offset=0x3000 size=0x3e8 id=1 */
/*   seg 2: offset=0x4dd0 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x3c id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x45cc anonymous_count=100 */

/* === Named exports === */
/* CRO 0x20d0 -> `nnroControlObject_` (segment 0) */
/* CRO 0x1ee8 -> `_ZN9xy_system2bg6System13SetIsCallDrawEb` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x20d0. */
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
/* Located at CRO 0x1ee8. */
/* The original is two instructions: `strb r1, [r0, #0xd9]; bx lr`. */
/* It is a non-virtual helper that flips the BG system's `IsCallDraw` byte */
/* (offset 0xd9 in the BG system object) and returns. */
/* TODO: not yet decoded - body recovered as a one-liner. */

/* === Forward declarations for identified function boundaries === */
static void DllPssFavorite_02cc(void);
static void DllPssFavorite_0310(void);
static void DllPssFavorite_0364(void);
static void DllPssFavorite_04a4(void);
static void DllPssFavorite_04e8(void);
static void DllPssFavorite_0538(void);
static void DllPssFavorite_0588(void);
static void DllPssFavorite_0624(void);
static void DllPssFavorite_0774(void);
static void DllPssFavorite_09fc(void);
static void DllPssFavorite_0b48(void);
static void DllPssFavorite_0bbc(void);
static void DllPssFavorite_0d84(void);
static void DllPssFavorite_0f38(void);
static void DllPssFavorite_0fbc(void);
static void DllPssFavorite_0ff4(void);
static void DllPssFavorite_11e8(void);
static void DllPssFavorite_1294(void);
static void DllPssFavorite_134c(void);
static void DllPssFavorite_13bc(void);
static void DllPssFavorite_1454(void);
static void DllPssFavorite_1690(void);
static void DllPssFavorite_18ac(void);
static void DllPssFavorite_1a6c(void);
static void DllPssFavorite_1b94(void);
static void DllPssFavorite_1c34(void);
static void DllPssFavorite_1cd0(void);
static void DllPssFavorite_1d18(void);
static void DllPssFavorite_1d78(void);
static void DllPssFavorite_1e08(void);
static void DllPssFavorite_1e40(void);
static void DllPssFavorite_1e7c(void);
static void DllPssFavorite_1eb4(void);
static void DllPssFavorite_1ef8(void);
static void DllPssFavorite_1f8c(void);
static void DllPssFavorite_20d8(void);

/* === Patch table (segment-0 trampolines) === */
/* 107 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x02cc */
static void DllPssFavorite_02cc(void) {
    /* TODO: not yet decoded - body of function 0x02cc */
}

/* CRO 0x0310 */
static void DllPssFavorite_0310(void) {
    /* TODO: not yet decoded - body of function 0x0310 */
}

/* CRO 0x0364 */
static void DllPssFavorite_0364(void) {
    /* TODO: not yet decoded - body of function 0x0364 */
}

/* CRO 0x04a4 */
static void DllPssFavorite_04a4(void) {
    /* TODO: not yet decoded - body of function 0x04a4 */
}

/* CRO 0x04e8 */
static void DllPssFavorite_04e8(void) {
    /* TODO: not yet decoded - body of function 0x04e8 */
}

/* CRO 0x0538 */
static void DllPssFavorite_0538(void) {
    /* TODO: not yet decoded - body of function 0x0538 */
}

/* CRO 0x0588 */
static void DllPssFavorite_0588(void) {
    /* TODO: not yet decoded - body of function 0x0588 */
}

/* CRO 0x0624 */
static void DllPssFavorite_0624(void) {
    /* TODO: not yet decoded - body of function 0x0624 */
}

/* CRO 0x0774 */
static void DllPssFavorite_0774(void) {
    /* TODO: not yet decoded - body of function 0x0774 */
}

/* CRO 0x09fc */
static void DllPssFavorite_09fc(void) {
    /* TODO: not yet decoded - body of function 0x09fc */
}

/* CRO 0x0b48 */
static void DllPssFavorite_0b48(void) {
    /* TODO: not yet decoded - body of function 0x0b48 */
}

/* CRO 0x0bbc */
static void DllPssFavorite_0bbc(void) {
    /* TODO: not yet decoded - body of function 0x0bbc */
}

/* CRO 0x0d84 */
static void DllPssFavorite_0d84(void) {
    /* TODO: not yet decoded - body of function 0x0d84 */
}

/* CRO 0x0f38 */
static void DllPssFavorite_0f38(void) {
    /* TODO: not yet decoded - body of function 0x0f38 */
}

/* CRO 0x0fbc */
static void DllPssFavorite_0fbc(void) {
    /* TODO: not yet decoded - body of function 0x0fbc */
}

/* CRO 0x0ff4 */
static void DllPssFavorite_0ff4(void) {
    /* TODO: not yet decoded - body of function 0x0ff4 */
}

/* CRO 0x11e8 */
static void DllPssFavorite_11e8(void) {
    /* TODO: not yet decoded - body of function 0x11e8 */
}

/* CRO 0x1294 */
static void DllPssFavorite_1294(void) {
    /* TODO: not yet decoded - body of function 0x1294 */
}

/* CRO 0x134c */
static void DllPssFavorite_134c(void) {
    /* TODO: not yet decoded - body of function 0x134c */
}

/* CRO 0x13bc */
static void DllPssFavorite_13bc(void) {
    /* TODO: not yet decoded - body of function 0x13bc */
}

/* CRO 0x1454 */
static void DllPssFavorite_1454(void) {
    /* TODO: not yet decoded - body of function 0x1454 */
}

/* CRO 0x1690 */
static void DllPssFavorite_1690(void) {
    /* TODO: not yet decoded - body of function 0x1690 */
}

/* CRO 0x18ac */
static void DllPssFavorite_18ac(void) {
    /* TODO: not yet decoded - body of function 0x18ac */
}

/* CRO 0x1a6c */
static void DllPssFavorite_1a6c(void) {
    /* TODO: not yet decoded - body of function 0x1a6c */
}

/* CRO 0x1b94 */
static void DllPssFavorite_1b94(void) {
    /* TODO: not yet decoded - body of function 0x1b94 */
}

/* CRO 0x1c34 */
static void DllPssFavorite_1c34(void) {
    /* TODO: not yet decoded - body of function 0x1c34 */
}

/* CRO 0x1cd0 */
static void DllPssFavorite_1cd0(void) {
    /* TODO: not yet decoded - body of function 0x1cd0 */
}

/* CRO 0x1d18 */
static void DllPssFavorite_1d18(void) {
    /* TODO: not yet decoded - body of function 0x1d18 */
}

/* CRO 0x1d78 */
static void DllPssFavorite_1d78(void) {
    /* TODO: not yet decoded - body of function 0x1d78 */
}

/* CRO 0x1e08 */
static void DllPssFavorite_1e08(void) {
    /* TODO: not yet decoded - body of function 0x1e08 */
}

/* CRO 0x1e40 */
static void DllPssFavorite_1e40(void) {
    /* TODO: not yet decoded - body of function 0x1e40 */
}

/* CRO 0x1e7c */
static void DllPssFavorite_1e7c(void) {
    /* TODO: not yet decoded - body of function 0x1e7c */
}

/* CRO 0x1eb4 */
static void DllPssFavorite_1eb4(void) {
    /* TODO: not yet decoded - body of function 0x1eb4 */
}

/* CRO 0x1ef8 */
static void DllPssFavorite_1ef8(void) {
    /* TODO: not yet decoded - body of function 0x1ef8 */
}

/* CRO 0x1f8c */
static void DllPssFavorite_1f8c(void) {
    /* TODO: not yet decoded - body of function 0x1f8c */
}

/* CRO 0x20d8 */
static void DllPssFavorite_20d8(void) {
    /* TODO: not yet decoded - body of function 0x20d8 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0364 -> DllPssFavorite_0364 */
/*   0x0774 -> DllPssFavorite_0774 */
/*   0x09fc -> DllPssFavorite_09fc */
/*   0x0bbc -> DllPssFavorite_0bbc */
/*   0x0d84 -> DllPssFavorite_0d84 */
/*   0x0ff4 -> DllPssFavorite_0ff4 */
/*   0x1294 -> DllPssFavorite_1294 */
/*   0x1454 -> DllPssFavorite_1454 */
/*   0x1a6c -> DllPssFavorite_1a6c */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x0188 -> imported via patch at seg_off 0x188 */
/*   0x0198 -> imported via patch at seg_off 0x198 */
/*   0x01a8 -> imported via patch at seg_off 0x1a8 */
/*   0x01b0 -> imported via patch at seg_off 0x1b0 */
/*   0x01b8 -> imported via patch at seg_off 0x1b8 */
/*   0x01c0 -> imported via patch at seg_off 0x1c0 */
/*   0x01c8 -> imported via patch at seg_off 0x1c8 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
