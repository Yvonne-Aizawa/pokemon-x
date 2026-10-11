/*
 * Preliminary decompilation of DllTrialHouseResult.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 32 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllTrialHouseResult */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4dc0 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x20 (32 bytes) */
/* Named exports  : 1 */
/* External patches : 113 */
/* Imported modules  : 1 */
/* ARM prologues  : 32 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x2618 id=0 */
/*   seg 1: offset=0x3000 size=0x3e4 id=1 */
/*   seg 2: offset=0x4dc0 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x0 id=0 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x45e0 anonymous_count=111 */

/* === Named exports === */
/* CRO 0x2568 -> `nnroControlObject_` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x2568. */
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
static void DllTrialHouseResult_0348(void);
static void DllTrialHouseResult_0364(void);
static void DllTrialHouseResult_053c(void);
static void DllTrialHouseResult_09a8(void);
static void DllTrialHouseResult_0b18(void);
static void DllTrialHouseResult_0b58(void);
static void DllTrialHouseResult_0bf4(void);
static void DllTrialHouseResult_0c8c(void);
static void DllTrialHouseResult_0d2c(void);
static void DllTrialHouseResult_0e1c(void);
static void DllTrialHouseResult_0ea0(void);
static void DllTrialHouseResult_0fec(void);
static void DllTrialHouseResult_1304(void);
static void DllTrialHouseResult_13fc(void);
static void DllTrialHouseResult_16cc(void);
static void DllTrialHouseResult_17fc(void);
static void DllTrialHouseResult_18bc(void);
static void DllTrialHouseResult_1940(void);
static void DllTrialHouseResult_1a84(void);
static void DllTrialHouseResult_1c7c(void);
static void DllTrialHouseResult_1da0(void);
static void DllTrialHouseResult_2044(void);
static void DllTrialHouseResult_2134(void);
static void DllTrialHouseResult_2244(void);
static void DllTrialHouseResult_22dc(void);
static void DllTrialHouseResult_2338(void);
static void DllTrialHouseResult_237c(void);
static void DllTrialHouseResult_23f8(void);
static void DllTrialHouseResult_2460(void);
static void DllTrialHouseResult_24c8(void);
static void DllTrialHouseResult_2500(void);
static void DllTrialHouseResult_2570(void);

/* === Patch table (segment-0 trampolines) === */
/* 113 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x0348 */
static void DllTrialHouseResult_0348(void) {
    /* TODO: not yet decoded - body of function 0x0348 */
}

/* CRO 0x0364 */
static void DllTrialHouseResult_0364(void) {
    /* TODO: not yet decoded - body of function 0x0364 */
}

/* CRO 0x053c */
static void DllTrialHouseResult_053c(void) {
    /* TODO: not yet decoded - body of function 0x053c */
}

/* CRO 0x09a8 */
static void DllTrialHouseResult_09a8(void) {
    /* TODO: not yet decoded - body of function 0x09a8 */
}

/* CRO 0x0b18 */
static void DllTrialHouseResult_0b18(void) {
    /* TODO: not yet decoded - body of function 0x0b18 */
}

/* CRO 0x0b58 */
static void DllTrialHouseResult_0b58(void) {
    /* TODO: not yet decoded - body of function 0x0b58 */
}

/* CRO 0x0bf4 */
static void DllTrialHouseResult_0bf4(void) {
    /* TODO: not yet decoded - body of function 0x0bf4 */
}

/* CRO 0x0c8c */
static void DllTrialHouseResult_0c8c(void) {
    /* TODO: not yet decoded - body of function 0x0c8c */
}

/* CRO 0x0d2c */
static void DllTrialHouseResult_0d2c(void) {
    /* TODO: not yet decoded - body of function 0x0d2c */
}

/* CRO 0x0e1c */
static void DllTrialHouseResult_0e1c(void) {
    /* TODO: not yet decoded - body of function 0x0e1c */
}

/* CRO 0x0ea0 */
static void DllTrialHouseResult_0ea0(void) {
    /* TODO: not yet decoded - body of function 0x0ea0 */
}

/* CRO 0x0fec */
static void DllTrialHouseResult_0fec(void) {
    /* TODO: not yet decoded - body of function 0x0fec */
}

/* CRO 0x1304 */
static void DllTrialHouseResult_1304(void) {
    /* TODO: not yet decoded - body of function 0x1304 */
}

/* CRO 0x13fc */
static void DllTrialHouseResult_13fc(void) {
    /* TODO: not yet decoded - body of function 0x13fc */
}

/* CRO 0x16cc */
static void DllTrialHouseResult_16cc(void) {
    /* TODO: not yet decoded - body of function 0x16cc */
}

/* CRO 0x17fc */
static void DllTrialHouseResult_17fc(void) {
    /* TODO: not yet decoded - body of function 0x17fc */
}

/* CRO 0x18bc */
static void DllTrialHouseResult_18bc(void) {
    /* TODO: not yet decoded - body of function 0x18bc */
}

/* CRO 0x1940 */
static void DllTrialHouseResult_1940(void) {
    /* TODO: not yet decoded - body of function 0x1940 */
}

/* CRO 0x1a84 */
static void DllTrialHouseResult_1a84(void) {
    /* TODO: not yet decoded - body of function 0x1a84 */
}

/* CRO 0x1c7c */
static void DllTrialHouseResult_1c7c(void) {
    /* TODO: not yet decoded - body of function 0x1c7c */
}

/* CRO 0x1da0 */
static void DllTrialHouseResult_1da0(void) {
    /* TODO: not yet decoded - body of function 0x1da0 */
}

/* CRO 0x2044 */
static void DllTrialHouseResult_2044(void) {
    /* TODO: not yet decoded - body of function 0x2044 */
}

/* CRO 0x2134 */
static void DllTrialHouseResult_2134(void) {
    /* TODO: not yet decoded - body of function 0x2134 */
}

/* CRO 0x2244 */
static void DllTrialHouseResult_2244(void) {
    /* TODO: not yet decoded - body of function 0x2244 */
}

/* CRO 0x22dc */
static void DllTrialHouseResult_22dc(void) {
    /* TODO: not yet decoded - body of function 0x22dc */
}

/* CRO 0x2338 */
static void DllTrialHouseResult_2338(void) {
    /* TODO: not yet decoded - body of function 0x2338 */
}

/* CRO 0x237c */
static void DllTrialHouseResult_237c(void) {
    /* TODO: not yet decoded - body of function 0x237c */
}

/* CRO 0x23f8 */
static void DllTrialHouseResult_23f8(void) {
    /* TODO: not yet decoded - body of function 0x23f8 */
}

/* CRO 0x2460 */
static void DllTrialHouseResult_2460(void) {
    /* TODO: not yet decoded - body of function 0x2460 */
}

/* CRO 0x24c8 */
static void DllTrialHouseResult_24c8(void) {
    /* TODO: not yet decoded - body of function 0x24c8 */
}

/* CRO 0x2500 */
static void DllTrialHouseResult_2500(void) {
    /* TODO: not yet decoded - body of function 0x2500 */
}

/* CRO 0x2570 */
static void DllTrialHouseResult_2570(void) {
    /* TODO: not yet decoded - body of function 0x2570 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0ea0 -> DllTrialHouseResult_0ea0 */
/*   0x0fec -> DllTrialHouseResult_0fec */
/*   0x13fc -> DllTrialHouseResult_13fc */
/*   0x17fc -> DllTrialHouseResult_17fc */
/*   0x18bc -> DllTrialHouseResult_18bc */
/*   0x1940 -> DllTrialHouseResult_1940 */
/*   0x1a84 -> DllTrialHouseResult_1a84 */
/*   0x1c7c -> DllTrialHouseResult_1c7c */
/*   0x1da0 -> DllTrialHouseResult_1da0 */
/*   0x2044 -> DllTrialHouseResult_2044 */
/*   0x2134 -> DllTrialHouseResult_2134 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
