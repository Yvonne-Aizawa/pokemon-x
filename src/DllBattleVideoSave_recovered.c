/*
 * Preliminary decompilation of DllBattleVideoSave.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 28 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllBattleVideoSave */
/* File size      : 0x5000 (20480 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x4df8 */
/* Data size      : 0x14 (20 bytes) */
/* BSS size       : 0x5c (92 bytes) */
/* Named exports  : 2 */
/* External patches : 96 */
/* Imported modules  : 1 */
/* ARM prologues  : 28 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x1eec id=0 */
/*   seg 1: offset=0x3000 size=0x364 id=1 */
/*   seg 2: offset=0x4df8 size=0x14 id=2 */
/*   seg 3: offset=0x0 size=0x3c id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x454c anonymous_count=91 */

/* === Named exports === */
/* CRO 0x1e3c -> `nnroControlObject_` (segment 0) */
/* CRO 0x1d64 -> `_ZN9xy_system2bg6System13SetIsCallDrawEb` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x1e3c. */
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
/* Located at CRO 0x1d64. */
/* The original is two instructions: `strb r1, [r0, #0xd9]; bx lr`. */
/* It is a non-virtual helper that flips the BG system's `IsCallDraw` byte */
/* (offset 0xd9 in the BG system object) and returns. */
/* TODO: not yet decoded - body recovered as a one-liner. */

/* === Forward declarations for identified function boundaries === */
static void DllBattleVideoSave_0274(void);
static void DllBattleVideoSave_02dc(void);
static void DllBattleVideoSave_03cc(void);
static void DllBattleVideoSave_05cc(void);
static void DllBattleVideoSave_0614(void);
static void DllBattleVideoSave_069c(void);
static void DllBattleVideoSave_08e4(void);
static void DllBattleVideoSave_0970(void);
static void DllBattleVideoSave_09f4(void);
static void DllBattleVideoSave_0bb8(void);
static void DllBattleVideoSave_0cdc(void);
static void DllBattleVideoSave_0f90(void);
static void DllBattleVideoSave_1080(void);
static void DllBattleVideoSave_111c(void);
static void DllBattleVideoSave_1284(void);
static void DllBattleVideoSave_14c0(void);
static void DllBattleVideoSave_153c(void);
static void DllBattleVideoSave_15bc(void);
static void DllBattleVideoSave_1700(void);
static void DllBattleVideoSave_180c(void);
static void DllBattleVideoSave_18cc(void);
static void DllBattleVideoSave_19dc(void);
static void DllBattleVideoSave_1ba8(void);
static void DllBattleVideoSave_1c1c(void);
static void DllBattleVideoSave_1c6c(void);
static void DllBattleVideoSave_1cf8(void);
static void DllBattleVideoSave_1d30(void);
static void DllBattleVideoSave_1e44(void);

/* === Patch table (segment-0 trampolines) === */
/* 96 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x0274 */
static void DllBattleVideoSave_0274(void) {
    /* TODO: not yet decoded - body of function 0x0274 */
}

/* CRO 0x02dc */
static void DllBattleVideoSave_02dc(void) {
    /* TODO: not yet decoded - body of function 0x02dc */
}

/* CRO 0x03cc */
static void DllBattleVideoSave_03cc(void) {
    /* TODO: not yet decoded - body of function 0x03cc */
}

/* CRO 0x05cc */
static void DllBattleVideoSave_05cc(void) {
    /* TODO: not yet decoded - body of function 0x05cc */
}

/* CRO 0x0614 */
static void DllBattleVideoSave_0614(void) {
    /* TODO: not yet decoded - body of function 0x0614 */
}

/* CRO 0x069c */
static void DllBattleVideoSave_069c(void) {
    /* TODO: not yet decoded - body of function 0x069c */
}

/* CRO 0x08e4 */
static void DllBattleVideoSave_08e4(void) {
    /* TODO: not yet decoded - body of function 0x08e4 */
}

/* CRO 0x0970 */
static void DllBattleVideoSave_0970(void) {
    /* TODO: not yet decoded - body of function 0x0970 */
}

/* CRO 0x09f4 */
static void DllBattleVideoSave_09f4(void) {
    /* TODO: not yet decoded - body of function 0x09f4 */
}

/* CRO 0x0bb8 */
static void DllBattleVideoSave_0bb8(void) {
    /* TODO: not yet decoded - body of function 0x0bb8 */
}

/* CRO 0x0cdc */
static void DllBattleVideoSave_0cdc(void) {
    /* TODO: not yet decoded - body of function 0x0cdc */
}

/* CRO 0x0f90 */
static void DllBattleVideoSave_0f90(void) {
    /* TODO: not yet decoded - body of function 0x0f90 */
}

/* CRO 0x1080 */
static void DllBattleVideoSave_1080(void) {
    /* TODO: not yet decoded - body of function 0x1080 */
}

/* CRO 0x111c */
static void DllBattleVideoSave_111c(void) {
    /* TODO: not yet decoded - body of function 0x111c */
}

/* CRO 0x1284 */
static void DllBattleVideoSave_1284(void) {
    /* TODO: not yet decoded - body of function 0x1284 */
}

/* CRO 0x14c0 */
static void DllBattleVideoSave_14c0(void) {
    /* TODO: not yet decoded - body of function 0x14c0 */
}

/* CRO 0x153c */
static void DllBattleVideoSave_153c(void) {
    /* TODO: not yet decoded - body of function 0x153c */
}

/* CRO 0x15bc */
static void DllBattleVideoSave_15bc(void) {
    /* TODO: not yet decoded - body of function 0x15bc */
}

/* CRO 0x1700 */
static void DllBattleVideoSave_1700(void) {
    /* TODO: not yet decoded - body of function 0x1700 */
}

/* CRO 0x180c */
static void DllBattleVideoSave_180c(void) {
    /* TODO: not yet decoded - body of function 0x180c */
}

/* CRO 0x18cc */
static void DllBattleVideoSave_18cc(void) {
    /* TODO: not yet decoded - body of function 0x18cc */
}

/* CRO 0x19dc */
static void DllBattleVideoSave_19dc(void) {
    /* TODO: not yet decoded - body of function 0x19dc */
}

/* CRO 0x1ba8 */
static void DllBattleVideoSave_1ba8(void) {
    /* TODO: not yet decoded - body of function 0x1ba8 */
}

/* CRO 0x1c1c */
static void DllBattleVideoSave_1c1c(void) {
    /* TODO: not yet decoded - body of function 0x1c1c */
}

/* CRO 0x1c6c */
static void DllBattleVideoSave_1c6c(void) {
    /* TODO: not yet decoded - body of function 0x1c6c */
}

/* CRO 0x1cf8 */
static void DllBattleVideoSave_1cf8(void) {
    /* TODO: not yet decoded - body of function 0x1cf8 */
}

/* CRO 0x1d30 */
static void DllBattleVideoSave_1d30(void) {
    /* TODO: not yet decoded - body of function 0x1d30 */
}

/* CRO 0x1e44 */
static void DllBattleVideoSave_1e44(void) {
    /* TODO: not yet decoded - body of function 0x1e44 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x02dc -> DllBattleVideoSave_02dc */
/*   0x069c -> DllBattleVideoSave_069c */
/*   0x0bb8 -> DllBattleVideoSave_0bb8 */
/*   0x0cdc -> DllBattleVideoSave_0cdc */
/*   0x0f90 -> DllBattleVideoSave_0f90 */
/*   0x1080 -> DllBattleVideoSave_1080 */
/*   0x111c -> DllBattleVideoSave_111c */
/*   0x1284 -> DllBattleVideoSave_1284 */
/*   0x15bc -> DllBattleVideoSave_15bc */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x01d0 -> imported via patch at seg_off 0x1d0 */
/*   0x01f0 -> imported via patch at seg_off 0x1f0 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
