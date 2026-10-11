/*
 * Preliminary decompilation of DllUSR15.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 14 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllUSR15 */
/* File size      : 0x4000 (16384 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x2e80 (11904 bytes) */
/* Data offset    : 0x3460 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x11c (284 bytes) */
/* Named exports  : 1 */
/* External patches : 27 */
/* Imported modules  : 2 */
/* ARM prologues  : 14 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x140c id=0 */
/*   seg 1: offset=0x2000 size=0x94 id=1 */
/*   seg 2: offset=0x3460 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0xfc id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x31e4 anonymous_count=20 */
/* index 1: module `DllField` */
/*   anonymous_head=0x3284 anonymous_count=7 */

/* === Named exports === */
/* CRO 0x135c -> `nnroControlObject_` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x135c. */
/* Standard pattern: dispatches on `r1` (selector 0..5) via the inline jump */
/* table populated by the loader (`ldrcc pc, [pc, r1, lsl #2]`). Selectors: */
/*   0 -> no-op / self-init, */
/*   1 -> returns 0, */
/*   2 -> stores r0 into the module's global object pointer, */
/*   3 -> loads the global object pointer into *r0, */
/*   4 -> initialises a two-word header at *r0, */
/*   5 -> returns an error pointer. */
/* TODO: not yet decoded - the body is documented at a high level only. */

/* === Forward declarations for identified function boundaries === */
static void DllUSR15_00ec(void);
static void DllUSR15_0398(void);
static void DllUSR15_064c(void);
static void DllUSR15_0b14(void);
static void DllUSR15_0b8c(void);
static void DllUSR15_0be4(void);
static void DllUSR15_0c90(void);
static void DllUSR15_0d28(void);
static void DllUSR15_0e44(void);
static void DllUSR15_0ed0(void);
static void DllUSR15_0f6c(void);
static void DllUSR15_1050(void);
static void DllUSR15_10c4(void);
static void DllUSR15_1364(void);

/* === Patch table (segment-0 trampolines) === */
/* 27 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x00ec */
static void DllUSR15_00ec(void) {
    /* TODO: not yet decoded - body of function 0x00ec */
}

/* CRO 0x0398 */
static void DllUSR15_0398(void) {
    /* TODO: not yet decoded - body of function 0x0398 */
}

/* CRO 0x064c */
static void DllUSR15_064c(void) {
    /* TODO: not yet decoded - body of function 0x064c */
}

/* CRO 0x0b14 */
static void DllUSR15_0b14(void) {
    /* TODO: not yet decoded - body of function 0x0b14 */
}

/* CRO 0x0b8c */
static void DllUSR15_0b8c(void) {
    /* TODO: not yet decoded - body of function 0x0b8c */
}

/* CRO 0x0be4 */
static void DllUSR15_0be4(void) {
    /* TODO: not yet decoded - body of function 0x0be4 */
}

/* CRO 0x0c90 */
static void DllUSR15_0c90(void) {
    /* TODO: not yet decoded - body of function 0x0c90 */
}

/* CRO 0x0d28 */
static void DllUSR15_0d28(void) {
    /* TODO: not yet decoded - body of function 0x0d28 */
}

/* CRO 0x0e44 */
static void DllUSR15_0e44(void) {
    /* TODO: not yet decoded - body of function 0x0e44 */
}

/* CRO 0x0ed0 */
static void DllUSR15_0ed0(void) {
    /* TODO: not yet decoded - body of function 0x0ed0 */
}

/* CRO 0x0f6c */
static void DllUSR15_0f6c(void) {
    /* TODO: not yet decoded - body of function 0x0f6c */
}

/* CRO 0x1050 */
static void DllUSR15_1050(void) {
    /* TODO: not yet decoded - body of function 0x1050 */
}

/* CRO 0x10c4 */
static void DllUSR15_10c4(void) {
    /* TODO: not yet decoded - body of function 0x10c4 */
}

/* CRO 0x1364 */
static void DllUSR15_1364(void) {
    /* TODO: not yet decoded - body of function 0x1364 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0398 -> DllUSR15_0398 */
/*   0x0b14 -> DllUSR15_0b14 */
/*   0x0b8c -> DllUSR15_0b8c */
/*   0x0d28 -> DllUSR15_0d28 */
/*   0x0e44 -> DllUSR15_0e44 */
/*   0x0ed0 -> DllUSR15_0ed0 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x0000 -> imported via patch at seg_off 0x0 */
/*   0x0008 -> imported via patch at seg_off 0x8 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
