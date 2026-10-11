/*
 * Preliminary decompilation of DllPssRuleSelect.cro.
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
/* Module name    : DllPssRuleSelect */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4b48 */
/* Data size      : 0x28 (40 bytes) */
/* BSS size       : 0x20 (32 bytes) */
/* Named exports  : 1 */
/* External patches : 70 */
/* Imported modules  : 1 */
/* ARM prologues  : 30 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x216c id=0 */
/*   seg 1: offset=0x3000 size=0x390 id=1 */
/*   seg 2: offset=0x4b48 size=0x28 id=2 */
/*   seg 3: offset=0x0 size=0x0 id=0 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x43dc anonymous_count=65 */

/* === Named exports === */
/* CRO 0x20bc -> `nnroControlObject_` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x20bc. */
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
static void DllPssRuleSelect_01f0(void);
static void DllPssRuleSelect_021c(void);
static void DllPssRuleSelect_0440(void);
static void DllPssRuleSelect_0564(void);
static void DllPssRuleSelect_05b4(void);
static void DllPssRuleSelect_0604(void);
static void DllPssRuleSelect_06b0(void);
static void DllPssRuleSelect_0848(void);
static void DllPssRuleSelect_094c(void);
static void DllPssRuleSelect_0cac(void);
static void DllPssRuleSelect_1148(void);
static void DllPssRuleSelect_11cc(void);
static void DllPssRuleSelect_1258(void);
static void DllPssRuleSelect_1330(void);
static void DllPssRuleSelect_140c(void);
static void DllPssRuleSelect_14bc(void);
static void DllPssRuleSelect_18ec(void);
static void DllPssRuleSelect_1918(void);
static void DllPssRuleSelect_198c(void);
static void DllPssRuleSelect_1cf4(void);
static void DllPssRuleSelect_1d64(void);
static void DllPssRuleSelect_1dbc(void);
static void DllPssRuleSelect_1dd8(void);
static void DllPssRuleSelect_1e38(void);
static void DllPssRuleSelect_1eec(void);
static void DllPssRuleSelect_1f24(void);
static void DllPssRuleSelect_1f60(void);
static void DllPssRuleSelect_1f98(void);
static void DllPssRuleSelect_1fd4(void);
static void DllPssRuleSelect_20c4(void);

/* === Patch table (segment-0 trampolines) === */
/* 70 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x01f0 */
static void DllPssRuleSelect_01f0(void) {
    /* TODO: not yet decoded - body of function 0x01f0 */
}

/* CRO 0x021c */
static void DllPssRuleSelect_021c(void) {
    /* TODO: not yet decoded - body of function 0x021c */
}

/* CRO 0x0440 */
static void DllPssRuleSelect_0440(void) {
    /* TODO: not yet decoded - body of function 0x0440 */
}

/* CRO 0x0564 */
static void DllPssRuleSelect_0564(void) {
    /* TODO: not yet decoded - body of function 0x0564 */
}

/* CRO 0x05b4 */
static void DllPssRuleSelect_05b4(void) {
    /* TODO: not yet decoded - body of function 0x05b4 */
}

/* CRO 0x0604 */
static void DllPssRuleSelect_0604(void) {
    /* TODO: not yet decoded - body of function 0x0604 */
}

/* CRO 0x06b0 */
static void DllPssRuleSelect_06b0(void) {
    /* TODO: not yet decoded - body of function 0x06b0 */
}

/* CRO 0x0848 */
static void DllPssRuleSelect_0848(void) {
    /* TODO: not yet decoded - body of function 0x0848 */
}

/* CRO 0x094c */
static void DllPssRuleSelect_094c(void) {
    /* TODO: not yet decoded - body of function 0x094c */
}

/* CRO 0x0cac */
static void DllPssRuleSelect_0cac(void) {
    /* TODO: not yet decoded - body of function 0x0cac */
}

/* CRO 0x1148 */
static void DllPssRuleSelect_1148(void) {
    /* TODO: not yet decoded - body of function 0x1148 */
}

/* CRO 0x11cc */
static void DllPssRuleSelect_11cc(void) {
    /* TODO: not yet decoded - body of function 0x11cc */
}

/* CRO 0x1258 */
static void DllPssRuleSelect_1258(void) {
    /* TODO: not yet decoded - body of function 0x1258 */
}

/* CRO 0x1330 */
static void DllPssRuleSelect_1330(void) {
    /* TODO: not yet decoded - body of function 0x1330 */
}

/* CRO 0x140c */
static void DllPssRuleSelect_140c(void) {
    /* TODO: not yet decoded - body of function 0x140c */
}

/* CRO 0x14bc */
static void DllPssRuleSelect_14bc(void) {
    /* TODO: not yet decoded - body of function 0x14bc */
}

/* CRO 0x18ec */
static void DllPssRuleSelect_18ec(void) {
    /* TODO: not yet decoded - body of function 0x18ec */
}

/* CRO 0x1918 */
static void DllPssRuleSelect_1918(void) {
    /* TODO: not yet decoded - body of function 0x1918 */
}

/* CRO 0x198c */
static void DllPssRuleSelect_198c(void) {
    /* TODO: not yet decoded - body of function 0x198c */
}

/* CRO 0x1cf4 */
static void DllPssRuleSelect_1cf4(void) {
    /* TODO: not yet decoded - body of function 0x1cf4 */
}

/* CRO 0x1d64 */
static void DllPssRuleSelect_1d64(void) {
    /* TODO: not yet decoded - body of function 0x1d64 */
}

/* CRO 0x1dbc */
static void DllPssRuleSelect_1dbc(void) {
    /* TODO: not yet decoded - body of function 0x1dbc */
}

/* CRO 0x1dd8 */
static void DllPssRuleSelect_1dd8(void) {
    /* TODO: not yet decoded - body of function 0x1dd8 */
}

/* CRO 0x1e38 */
static void DllPssRuleSelect_1e38(void) {
    /* TODO: not yet decoded - body of function 0x1e38 */
}

/* CRO 0x1eec */
static void DllPssRuleSelect_1eec(void) {
    /* TODO: not yet decoded - body of function 0x1eec */
}

/* CRO 0x1f24 */
static void DllPssRuleSelect_1f24(void) {
    /* TODO: not yet decoded - body of function 0x1f24 */
}

/* CRO 0x1f60 */
static void DllPssRuleSelect_1f60(void) {
    /* TODO: not yet decoded - body of function 0x1f60 */
}

/* CRO 0x1f98 */
static void DllPssRuleSelect_1f98(void) {
    /* TODO: not yet decoded - body of function 0x1f98 */
}

/* CRO 0x1fd4 */
static void DllPssRuleSelect_1fd4(void) {
    /* TODO: not yet decoded - body of function 0x1fd4 */
}

/* CRO 0x20c4 */
static void DllPssRuleSelect_20c4(void) {
    /* TODO: not yet decoded - body of function 0x20c4 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x021c -> DllPssRuleSelect_021c */
/*   0x0440 -> DllPssRuleSelect_0440 */
/*   0x06b0 -> DllPssRuleSelect_06b0 */
/*   0x0848 -> DllPssRuleSelect_0848 */
/*   0x094c -> DllPssRuleSelect_094c */
/*   0x11cc -> DllPssRuleSelect_11cc */
/*   0x140c -> DllPssRuleSelect_140c */
/*   0x198c -> DllPssRuleSelect_198c */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x0178 -> imported via patch at seg_off 0x178 */
/*   0x0188 -> imported via patch at seg_off 0x188 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
