/*
 * Preliminary decompilation of DllFriendEntry.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 38 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllFriendEntry */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4f10 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x20 (32 bytes) */
/* Named exports  : 1 */
/* External patches : 127 */
/* Imported modules  : 1 */
/* ARM prologues  : 38 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x2a38 id=0 */
/*   seg 1: offset=0x3000 size=0x430 id=1 */
/*   seg 2: offset=0x4f10 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x0 id=0 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x4684 anonymous_count=114 */

/* === Named exports === */
/* CRO 0x2988 -> `nnroControlObject_` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x2988. */
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
static void DllFriendEntry_0344(void);
static void DllFriendEntry_037c(void);
static void DllFriendEntry_03b0(void);
static void DllFriendEntry_0408(void);
static void DllFriendEntry_0478(void);
static void DllFriendEntry_05c4(void);
static void DllFriendEntry_06dc(void);
static void DllFriendEntry_097c(void);
static void DllFriendEntry_0b00(void);
static void DllFriendEntry_0d98(void);
static void DllFriendEntry_12ac(void);
static void DllFriendEntry_13cc(void);
static void DllFriendEntry_15c4(void);
static void DllFriendEntry_16d4(void);
static void DllFriendEntry_17e0(void);
static void DllFriendEntry_187c(void);
static void DllFriendEntry_192c(void);
static void DllFriendEntry_1b34(void);
static void DllFriendEntry_1b60(void);
static void DllFriendEntry_1b90(void);
static void DllFriendEntry_1cc4(void);
static void DllFriendEntry_1d04(void);
static void DllFriendEntry_1d50(void);
static void DllFriendEntry_1f38(void);
static void DllFriendEntry_1fb4(void);
static void DllFriendEntry_2020(void);
static void DllFriendEntry_209c(void);
static void DllFriendEntry_20d0(void);
static void DllFriendEntry_2168(void);
static void DllFriendEntry_21d4(void);
static void DllFriendEntry_2220(void);
static void DllFriendEntry_2270(void);
static void DllFriendEntry_25b0(void);
static void DllFriendEntry_26e0(void);
static void DllFriendEntry_2704(void);
static void DllFriendEntry_2840(void);
static void DllFriendEntry_28a4(void);
static void DllFriendEntry_2990(void);

/* === Patch table (segment-0 trampolines) === */
/* 127 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x0344 */
static void DllFriendEntry_0344(void) {
    /* TODO: not yet decoded - body of function 0x0344 */
}

/* CRO 0x037c */
static void DllFriendEntry_037c(void) {
    /* TODO: not yet decoded - body of function 0x037c */
}

/* CRO 0x03b0 */
static void DllFriendEntry_03b0(void) {
    /* TODO: not yet decoded - body of function 0x03b0 */
}

/* CRO 0x0408 */
static void DllFriendEntry_0408(void) {
    /* TODO: not yet decoded - body of function 0x0408 */
}

/* CRO 0x0478 */
static void DllFriendEntry_0478(void) {
    /* TODO: not yet decoded - body of function 0x0478 */
}

/* CRO 0x05c4 */
static void DllFriendEntry_05c4(void) {
    /* TODO: not yet decoded - body of function 0x05c4 */
}

/* CRO 0x06dc */
static void DllFriendEntry_06dc(void) {
    /* TODO: not yet decoded - body of function 0x06dc */
}

/* CRO 0x097c */
static void DllFriendEntry_097c(void) {
    /* TODO: not yet decoded - body of function 0x097c */
}

/* CRO 0x0b00 */
static void DllFriendEntry_0b00(void) {
    /* TODO: not yet decoded - body of function 0x0b00 */
}

/* CRO 0x0d98 */
static void DllFriendEntry_0d98(void) {
    /* TODO: not yet decoded - body of function 0x0d98 */
}

/* CRO 0x12ac */
static void DllFriendEntry_12ac(void) {
    /* TODO: not yet decoded - body of function 0x12ac */
}

/* CRO 0x13cc */
static void DllFriendEntry_13cc(void) {
    /* TODO: not yet decoded - body of function 0x13cc */
}

/* CRO 0x15c4 */
static void DllFriendEntry_15c4(void) {
    /* TODO: not yet decoded - body of function 0x15c4 */
}

/* CRO 0x16d4 */
static void DllFriendEntry_16d4(void) {
    /* TODO: not yet decoded - body of function 0x16d4 */
}

/* CRO 0x17e0 */
static void DllFriendEntry_17e0(void) {
    /* TODO: not yet decoded - body of function 0x17e0 */
}

/* CRO 0x187c */
static void DllFriendEntry_187c(void) {
    /* TODO: not yet decoded - body of function 0x187c */
}

/* CRO 0x192c */
static void DllFriendEntry_192c(void) {
    /* TODO: not yet decoded - body of function 0x192c */
}

/* CRO 0x1b34 */
static void DllFriendEntry_1b34(void) {
    /* TODO: not yet decoded - body of function 0x1b34 */
}

/* CRO 0x1b60 */
static void DllFriendEntry_1b60(void) {
    /* TODO: not yet decoded - body of function 0x1b60 */
}

/* CRO 0x1b90 */
static void DllFriendEntry_1b90(void) {
    /* TODO: not yet decoded - body of function 0x1b90 */
}

/* CRO 0x1cc4 */
static void DllFriendEntry_1cc4(void) {
    /* TODO: not yet decoded - body of function 0x1cc4 */
}

/* CRO 0x1d04 */
static void DllFriendEntry_1d04(void) {
    /* TODO: not yet decoded - body of function 0x1d04 */
}

/* CRO 0x1d50 */
static void DllFriendEntry_1d50(void) {
    /* TODO: not yet decoded - body of function 0x1d50 */
}

/* CRO 0x1f38 */
static void DllFriendEntry_1f38(void) {
    /* TODO: not yet decoded - body of function 0x1f38 */
}

/* CRO 0x1fb4 */
static void DllFriendEntry_1fb4(void) {
    /* TODO: not yet decoded - body of function 0x1fb4 */
}

/* CRO 0x2020 */
static void DllFriendEntry_2020(void) {
    /* TODO: not yet decoded - body of function 0x2020 */
}

/* CRO 0x209c */
static void DllFriendEntry_209c(void) {
    /* TODO: not yet decoded - body of function 0x209c */
}

/* CRO 0x20d0 */
static void DllFriendEntry_20d0(void) {
    /* TODO: not yet decoded - body of function 0x20d0 */
}

/* CRO 0x2168 */
static void DllFriendEntry_2168(void) {
    /* TODO: not yet decoded - body of function 0x2168 */
}

/* CRO 0x21d4 */
static void DllFriendEntry_21d4(void) {
    /* TODO: not yet decoded - body of function 0x21d4 */
}

/* CRO 0x2220 */
static void DllFriendEntry_2220(void) {
    /* TODO: not yet decoded - body of function 0x2220 */
}

/* CRO 0x2270 */
static void DllFriendEntry_2270(void) {
    /* TODO: not yet decoded - body of function 0x2270 */
}

/* CRO 0x25b0 */
static void DllFriendEntry_25b0(void) {
    /* TODO: not yet decoded - body of function 0x25b0 */
}

/* CRO 0x26e0 */
static void DllFriendEntry_26e0(void) {
    /* TODO: not yet decoded - body of function 0x26e0 */
}

/* CRO 0x2704 */
static void DllFriendEntry_2704(void) {
    /* TODO: not yet decoded - body of function 0x2704 */
}

/* CRO 0x2840 */
static void DllFriendEntry_2840(void) {
    /* TODO: not yet decoded - body of function 0x2840 */
}

/* CRO 0x28a4 */
static void DllFriendEntry_28a4(void) {
    /* TODO: not yet decoded - body of function 0x28a4 */
}

/* CRO 0x2990 */
static void DllFriendEntry_2990(void) {
    /* TODO: not yet decoded - body of function 0x2990 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x06dc -> DllFriendEntry_06dc */
/*   0x0b00 -> DllFriendEntry_0b00 */
/*   0x15c4 -> DllFriendEntry_15c4 */
/*   0x16d4 -> DllFriendEntry_16d4 */
/*   0x17e0 -> DllFriendEntry_17e0 */
/*   0x187c -> DllFriendEntry_187c */
/*   0x1b90 -> DllFriendEntry_1b90 */
/*   0x25b0 -> DllFriendEntry_25b0 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x01f8 -> imported via patch at seg_off 0x1f8 */
/*   0x0200 -> imported via patch at seg_off 0x200 */
/*   0x0208 -> imported via patch at seg_off 0x208 */
/*   0x0230 -> imported via patch at seg_off 0x230 */
/*   0x0238 -> imported via patch at seg_off 0x238 */
/*   0x0248 -> imported via patch at seg_off 0x248 */
/*   0x0250 -> imported via patch at seg_off 0x250 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
