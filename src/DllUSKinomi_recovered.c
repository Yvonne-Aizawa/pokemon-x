/*
 * Preliminary decompilation of DllUSKinomi.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 20 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllUSKinomi */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4820 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x140 (320 bytes) */
/* Named exports  : 1 */
/* External patches : 55 */
/* Imported modules  : 2 */
/* ARM prologues  : 20 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x27e8 id=0 */
/*   seg 1: offset=0x3000 size=0x224 id=1 */
/*   seg 2: offset=0x4820 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x120 id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x4334 anonymous_count=39 */
/* index 1: module `DllField` */
/*   anonymous_head=0x446c anonymous_count=14 */

/* === Named exports === */
/* CRO 0x2738 -> `nnroControlObject_` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x2738. */
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
static void DllUSKinomi_0188(void);
static void DllUSKinomi_0888(void);
static void DllUSKinomi_09a0(void);
static void DllUSKinomi_0a28(void);
static void DllUSKinomi_0de8(void);
static void DllUSKinomi_0f14(void);
static void DllUSKinomi_1490(void);
static void DllUSKinomi_1890(void);
static void DllUSKinomi_1920(void);
static void DllUSKinomi_1b08(void);
static void DllUSKinomi_1df4(void);
static void DllUSKinomi_1e98(void);
static void DllUSKinomi_1fd8(void);
static void DllUSKinomi_20d8(void);
static void DllUSKinomi_2158(void);
static void DllUSKinomi_2274(void);
static void DllUSKinomi_22c0(void);
static void DllUSKinomi_2320(void);
static void DllUSKinomi_24a8(void);
static void DllUSKinomi_2740(void);

/* === Patch table (segment-0 trampolines) === */
/* 55 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x0188 */
static void DllUSKinomi_0188(void) {
    /* TODO: not yet decoded - body of function 0x0188 */
}

/* CRO 0x0888 */
static void DllUSKinomi_0888(void) {
    /* TODO: not yet decoded - body of function 0x0888 */
}

/* CRO 0x09a0 */
static void DllUSKinomi_09a0(void) {
    /* TODO: not yet decoded - body of function 0x09a0 */
}

/* CRO 0x0a28 */
static void DllUSKinomi_0a28(void) {
    /* TODO: not yet decoded - body of function 0x0a28 */
}

/* CRO 0x0de8 */
static void DllUSKinomi_0de8(void) {
    /* TODO: not yet decoded - body of function 0x0de8 */
}

/* CRO 0x0f14 */
static void DllUSKinomi_0f14(void) {
    /* TODO: not yet decoded - body of function 0x0f14 */
}

/* CRO 0x1490 */
static void DllUSKinomi_1490(void) {
    /* TODO: not yet decoded - body of function 0x1490 */
}

/* CRO 0x1890 */
static void DllUSKinomi_1890(void) {
    /* TODO: not yet decoded - body of function 0x1890 */
}

/* CRO 0x1920 */
static void DllUSKinomi_1920(void) {
    /* TODO: not yet decoded - body of function 0x1920 */
}

/* CRO 0x1b08 */
static void DllUSKinomi_1b08(void) {
    /* TODO: not yet decoded - body of function 0x1b08 */
}

/* CRO 0x1df4 */
static void DllUSKinomi_1df4(void) {
    /* TODO: not yet decoded - body of function 0x1df4 */
}

/* CRO 0x1e98 */
static void DllUSKinomi_1e98(void) {
    /* TODO: not yet decoded - body of function 0x1e98 */
}

/* CRO 0x1fd8 */
static void DllUSKinomi_1fd8(void) {
    /* TODO: not yet decoded - body of function 0x1fd8 */
}

/* CRO 0x20d8 */
static void DllUSKinomi_20d8(void) {
    /* TODO: not yet decoded - body of function 0x20d8 */
}

/* CRO 0x2158 */
static void DllUSKinomi_2158(void) {
    /* TODO: not yet decoded - body of function 0x2158 */
}

/* CRO 0x2274 */
static void DllUSKinomi_2274(void) {
    /* TODO: not yet decoded - body of function 0x2274 */
}

/* CRO 0x22c0 */
static void DllUSKinomi_22c0(void) {
    /* TODO: not yet decoded - body of function 0x22c0 */
}

/* CRO 0x2320 */
static void DllUSKinomi_2320(void) {
    /* TODO: not yet decoded - body of function 0x2320 */
}

/* CRO 0x24a8 */
static void DllUSKinomi_24a8(void) {
    /* TODO: not yet decoded - body of function 0x24a8 */
}

/* CRO 0x2740 */
static void DllUSKinomi_2740(void) {
    /* TODO: not yet decoded - body of function 0x2740 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0188 -> DllUSKinomi_0188 */
/*   0x0888 -> DllUSKinomi_0888 */
/*   0x09a0 -> DllUSKinomi_09a0 */
/*   0x0a28 -> DllUSKinomi_0a28 */
/*   0x1490 -> DllUSKinomi_1490 */
/*   0x1890 -> DllUSKinomi_1890 */
/*   0x1e98 -> DllUSKinomi_1e98 */
/*   0x1fd8 -> DllUSKinomi_1fd8 */
/*   0x2320 -> DllUSKinomi_2320 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x0138 -> imported via patch at seg_off 0x138 */
/*   0x0148 -> imported via patch at seg_off 0x148 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
