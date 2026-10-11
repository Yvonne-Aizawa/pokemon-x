/*
 * Preliminary decompilation of DllUSPassage.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 31 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllUSPassage */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4ac0 */
/* Data size      : 0x3c (60 bytes) */
/* BSS size       : 0x50 (80 bytes) */
/* Named exports  : 1 */
/* External patches : 61 */
/* Imported modules  : 2 */
/* ARM prologues  : 31 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x2028 id=0 */
/*   seg 1: offset=0x3000 size=0x290 id=1 */
/*   seg 2: offset=0x4ac0 size=0x3c id=2 */
/*   seg 3: offset=0x0 size=0x30 id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x4380 anonymous_count=42 */
/* index 1: module `DllField` */
/*   anonymous_head=0x44d0 anonymous_count=16 */

/* === Named exports === */
/* CRO 0x1f78 -> `nnroControlObject_` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x1f78. */
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
static void DllUSPassage_01d0(void);
static void DllUSPassage_04cc(void);
static void DllUSPassage_05d8(void);
static void DllUSPassage_0678(void);
static void DllUSPassage_094c(void);
static void DllUSPassage_09a0(void);
static void DllUSPassage_0b74(void);
static void DllUSPassage_0c8c(void);
static void DllUSPassage_0ce0(void);
static void DllUSPassage_0ee0(void);
static void DllUSPassage_0f00(void);
static void DllUSPassage_1040(void);
static void DllUSPassage_1120(void);
static void DllUSPassage_119c(void);
static void DllUSPassage_1224(void);
static void DllUSPassage_1298(void);
static void DllUSPassage_1354(void);
static void DllUSPassage_1478(void);
static void DllUSPassage_14a8(void);
static void DllUSPassage_1554(void);
static void DllUSPassage_15ec(void);
static void DllUSPassage_188c(void);
static void DllUSPassage_1914(void);
static void DllUSPassage_1968(void);
static void DllUSPassage_19f8(void);
static void DllUSPassage_1b08(void);
static void DllUSPassage_1dcc(void);
static void DllUSPassage_1e48(void);
static void DllUSPassage_1e9c(void);
static void DllUSPassage_1f2c(void);
static void DllUSPassage_1f80(void);

/* === Patch table (segment-0 trampolines) === */
/* 61 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x01d0 */
static void DllUSPassage_01d0(void) {
    /* TODO: not yet decoded - body of function 0x01d0 */
}

/* CRO 0x04cc */
static void DllUSPassage_04cc(void) {
    /* TODO: not yet decoded - body of function 0x04cc */
}

/* CRO 0x05d8 */
static void DllUSPassage_05d8(void) {
    /* TODO: not yet decoded - body of function 0x05d8 */
}

/* CRO 0x0678 */
static void DllUSPassage_0678(void) {
    /* TODO: not yet decoded - body of function 0x0678 */
}

/* CRO 0x094c */
static void DllUSPassage_094c(void) {
    /* TODO: not yet decoded - body of function 0x094c */
}

/* CRO 0x09a0 */
static void DllUSPassage_09a0(void) {
    /* TODO: not yet decoded - body of function 0x09a0 */
}

/* CRO 0x0b74 */
static void DllUSPassage_0b74(void) {
    /* TODO: not yet decoded - body of function 0x0b74 */
}

/* CRO 0x0c8c */
static void DllUSPassage_0c8c(void) {
    /* TODO: not yet decoded - body of function 0x0c8c */
}

/* CRO 0x0ce0 */
static void DllUSPassage_0ce0(void) {
    /* TODO: not yet decoded - body of function 0x0ce0 */
}

/* CRO 0x0ee0 */
static void DllUSPassage_0ee0(void) {
    /* TODO: not yet decoded - body of function 0x0ee0 */
}

/* CRO 0x0f00 */
static void DllUSPassage_0f00(void) {
    /* TODO: not yet decoded - body of function 0x0f00 */
}

/* CRO 0x1040 */
static void DllUSPassage_1040(void) {
    /* TODO: not yet decoded - body of function 0x1040 */
}

/* CRO 0x1120 */
static void DllUSPassage_1120(void) {
    /* TODO: not yet decoded - body of function 0x1120 */
}

/* CRO 0x119c */
static void DllUSPassage_119c(void) {
    /* TODO: not yet decoded - body of function 0x119c */
}

/* CRO 0x1224 */
static void DllUSPassage_1224(void) {
    /* TODO: not yet decoded - body of function 0x1224 */
}

/* CRO 0x1298 */
static void DllUSPassage_1298(void) {
    /* TODO: not yet decoded - body of function 0x1298 */
}

/* CRO 0x1354 */
static void DllUSPassage_1354(void) {
    /* TODO: not yet decoded - body of function 0x1354 */
}

/* CRO 0x1478 */
static void DllUSPassage_1478(void) {
    /* TODO: not yet decoded - body of function 0x1478 */
}

/* CRO 0x14a8 */
static void DllUSPassage_14a8(void) {
    /* TODO: not yet decoded - body of function 0x14a8 */
}

/* CRO 0x1554 */
static void DllUSPassage_1554(void) {
    /* TODO: not yet decoded - body of function 0x1554 */
}

/* CRO 0x15ec */
static void DllUSPassage_15ec(void) {
    /* TODO: not yet decoded - body of function 0x15ec */
}

/* CRO 0x188c */
static void DllUSPassage_188c(void) {
    /* TODO: not yet decoded - body of function 0x188c */
}

/* CRO 0x1914 */
static void DllUSPassage_1914(void) {
    /* TODO: not yet decoded - body of function 0x1914 */
}

/* CRO 0x1968 */
static void DllUSPassage_1968(void) {
    /* TODO: not yet decoded - body of function 0x1968 */
}

/* CRO 0x19f8 */
static void DllUSPassage_19f8(void) {
    /* TODO: not yet decoded - body of function 0x19f8 */
}

/* CRO 0x1b08 */
static void DllUSPassage_1b08(void) {
    /* TODO: not yet decoded - body of function 0x1b08 */
}

/* CRO 0x1dcc */
static void DllUSPassage_1dcc(void) {
    /* TODO: not yet decoded - body of function 0x1dcc */
}

/* CRO 0x1e48 */
static void DllUSPassage_1e48(void) {
    /* TODO: not yet decoded - body of function 0x1e48 */
}

/* CRO 0x1e9c */
static void DllUSPassage_1e9c(void) {
    /* TODO: not yet decoded - body of function 0x1e9c */
}

/* CRO 0x1f2c */
static void DllUSPassage_1f2c(void) {
    /* TODO: not yet decoded - body of function 0x1f2c */
}

/* CRO 0x1f80 */
static void DllUSPassage_1f80(void) {
    /* TODO: not yet decoded - body of function 0x1f80 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x01d0 -> DllUSPassage_01d0 */
/*   0x04cc -> DllUSPassage_04cc */
/*   0x09a0 -> DllUSPassage_09a0 */
/*   0x1040 -> DllUSPassage_1040 */
/*   0x119c -> DllUSPassage_119c */
/*   0x1224 -> DllUSPassage_1224 */
/*   0x1b08 -> DllUSPassage_1b08 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x0048 -> imported via patch at seg_off 0x48 */
/*   0x0050 -> imported via patch at seg_off 0x50 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
