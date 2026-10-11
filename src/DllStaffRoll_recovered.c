/*
 * Preliminary decompilation of DllStaffRoll.cro.
 *
 * Source address notation uses CRO segment 0 offsets (offset within the loaded
 * code segment, which lives at file offset 0x180). This file is
 * intentionally not wired into a build yet: the imported services and the
 * exact CRO linker layout still need to be recovered.
 *
 * Recovered from the disassembly of 41 ARM function prologue(s) and
 * the loader-patch stubs (R_ARM_ABS32 trampolines in segment 0). Field access
 * patterns and control-object dispatch are noted in comments; anything not directly
 * visible in the disassembly is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* === Module header facts === */
/* Module name    : DllStaffRoll */
/* File size      : 0x6000 (24576 bytes) */
/* Code offset    : 0x180 */
/* Code size      : 0x3e80 (16000 bytes) */
/* Data offset    : 0x54f8 */
/* Data size      : 0xf4 (244 bytes) */
/* BSS size       : 0x30 (48 bytes) */
/* Named exports  : 2 */
/* External patches : 171 */
/* Imported modules  : 2 */
/* ARM prologues  : 41 */

/* === Segments === */
/*   seg 0: offset=0x180 size=0x2e0c id=0 */
/*   seg 1: offset=0x3000 size=0x51c id=1 */
/*   seg 2: offset=0x54f8 size=0xf4 id=2 */
/*   seg 3: offset=0x0 size=0x10 id=3 */
/*   seg 4: offset=0x0 size=0x0 id=0 */
/*   seg 5: offset=0x0 size=0x0 id=0 */

/* === Imported modules === */
/* index 0: module `|static|` */
/*   anonymous_head=0x48e0 anonymous_count=137 */
/* index 1: module `DllSequence` */
/*   anonymous_head=0x4d28 anonymous_count=13 */

/* === Named exports === */
/* CRO 0x2d5c -> `nnroControlObject_` (segment 0) */
/* CRO 0x2b30 -> `_ZN9xy_system2bg6System13SetIsCallDrawEb` (segment 0) */

/* === Control object (`nnroControlObject_`) === */
/* Located at CRO 0x2d5c. */
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
/* Located at CRO 0x2b30. */
/* The original is two instructions: `strb r1, [r0, #0xd9]; bx lr`. */
/* It is a non-virtual helper that flips the BG system's `IsCallDraw` byte */
/* (offset 0xd9 in the BG system object) and returns. */
/* TODO: not yet decoded - body recovered as a one-liner. */

/* === Forward declarations for identified function boundaries === */
static void DllStaffRoll_0450(void);
static void DllStaffRoll_0778(void);
static void DllStaffRoll_0790(void);
static void DllStaffRoll_0900(void);
static void DllStaffRoll_0b20(void);
static void DllStaffRoll_0bcc(void);
static void DllStaffRoll_0cd0(void);
static void DllStaffRoll_0d10(void);
static void DllStaffRoll_0d40(void);
static void DllStaffRoll_0d70(void);
static void DllStaffRoll_0dd4(void);
static void DllStaffRoll_0e44(void);
static void DllStaffRoll_0eb4(void);
static void DllStaffRoll_0f98(void);
static void DllStaffRoll_0fe8(void);
static void DllStaffRoll_11b4(void);
static void DllStaffRoll_1294(void);
static void DllStaffRoll_1324(void);
static void DllStaffRoll_142c(void);
static void DllStaffRoll_16dc(void);
static void DllStaffRoll_183c(void);
static void DllStaffRoll_1908(void);
static void DllStaffRoll_1d04(void);
static void DllStaffRoll_1ef8(void);
static void DllStaffRoll_2184(void);
static void DllStaffRoll_2194(void);
static void DllStaffRoll_2314(void);
static void DllStaffRoll_2468(void);
static void DllStaffRoll_2570(void);
static void DllStaffRoll_26a8(void);
static void DllStaffRoll_26f8(void);
static void DllStaffRoll_2748(void);
static void DllStaffRoll_279c(void);
static void DllStaffRoll_27e8(void);
static void DllStaffRoll_2948(void);
static void DllStaffRoll_2a0c(void);
static void DllStaffRoll_2ac4(void);
static void DllStaffRoll_2afc(void);
static void DllStaffRoll_2b40(void);
static void DllStaffRoll_2b84(void);
static void DllStaffRoll_2d64(void);

/* === Patch table (segment-0 trampolines) === */
/* 171 external patches. The first contiguous block of */
/* segment 0 contains 8-byte `ldr pc, [pc, #-4]` + 32-bit address trampolines; */
/* each BL into one of them is a cross-CRO call resolved at loader time. */

/* === Identified function bodies === */
/* Each function below starts at the noted offset in segment 0 and is bounded by */
/* its ARM prologue. Bodies are intentionally not yet decoded - this list only */
/* documents which prologues were found so the orchestrator can correlate them */
/* with later callgraph analysis. */

/* CRO 0x0450 */
static void DllStaffRoll_0450(void) {
    /* TODO: not yet decoded - body of function 0x0450 */
}

/* CRO 0x0778 */
static void DllStaffRoll_0778(void) {
    /* TODO: not yet decoded - body of function 0x0778 */
}

/* CRO 0x0790 */
static void DllStaffRoll_0790(void) {
    /* TODO: not yet decoded - body of function 0x0790 */
}

/* CRO 0x0900 */
static void DllStaffRoll_0900(void) {
    /* TODO: not yet decoded - body of function 0x0900 */
}

/* CRO 0x0b20 */
static void DllStaffRoll_0b20(void) {
    /* TODO: not yet decoded - body of function 0x0b20 */
}

/* CRO 0x0bcc */
static void DllStaffRoll_0bcc(void) {
    /* TODO: not yet decoded - body of function 0x0bcc */
}

/* CRO 0x0cd0 */
static void DllStaffRoll_0cd0(void) {
    /* TODO: not yet decoded - body of function 0x0cd0 */
}

/* CRO 0x0d10 */
static void DllStaffRoll_0d10(void) {
    /* TODO: not yet decoded - body of function 0x0d10 */
}

/* CRO 0x0d40 */
static void DllStaffRoll_0d40(void) {
    /* TODO: not yet decoded - body of function 0x0d40 */
}

/* CRO 0x0d70 */
static void DllStaffRoll_0d70(void) {
    /* TODO: not yet decoded - body of function 0x0d70 */
}

/* CRO 0x0dd4 */
static void DllStaffRoll_0dd4(void) {
    /* TODO: not yet decoded - body of function 0x0dd4 */
}

/* CRO 0x0e44 */
static void DllStaffRoll_0e44(void) {
    /* TODO: not yet decoded - body of function 0x0e44 */
}

/* CRO 0x0eb4 */
static void DllStaffRoll_0eb4(void) {
    /* TODO: not yet decoded - body of function 0x0eb4 */
}

/* CRO 0x0f98 */
static void DllStaffRoll_0f98(void) {
    /* TODO: not yet decoded - body of function 0x0f98 */
}

/* CRO 0x0fe8 */
static void DllStaffRoll_0fe8(void) {
    /* TODO: not yet decoded - body of function 0x0fe8 */
}

/* CRO 0x11b4 */
static void DllStaffRoll_11b4(void) {
    /* TODO: not yet decoded - body of function 0x11b4 */
}

/* CRO 0x1294 */
static void DllStaffRoll_1294(void) {
    /* TODO: not yet decoded - body of function 0x1294 */
}

/* CRO 0x1324 */
static void DllStaffRoll_1324(void) {
    /* TODO: not yet decoded - body of function 0x1324 */
}

/* CRO 0x142c */
static void DllStaffRoll_142c(void) {
    /* TODO: not yet decoded - body of function 0x142c */
}

/* CRO 0x16dc */
static void DllStaffRoll_16dc(void) {
    /* TODO: not yet decoded - body of function 0x16dc */
}

/* CRO 0x183c */
static void DllStaffRoll_183c(void) {
    /* TODO: not yet decoded - body of function 0x183c */
}

/* CRO 0x1908 */
static void DllStaffRoll_1908(void) {
    /* TODO: not yet decoded - body of function 0x1908 */
}

/* CRO 0x1d04 */
static void DllStaffRoll_1d04(void) {
    /* TODO: not yet decoded - body of function 0x1d04 */
}

/* CRO 0x1ef8 */
static void DllStaffRoll_1ef8(void) {
    /* TODO: not yet decoded - body of function 0x1ef8 */
}

/* CRO 0x2184 */
static void DllStaffRoll_2184(void) {
    /* TODO: not yet decoded - body of function 0x2184 */
}

/* CRO 0x2194 */
static void DllStaffRoll_2194(void) {
    /* TODO: not yet decoded - body of function 0x2194 */
}

/* CRO 0x2314 */
static void DllStaffRoll_2314(void) {
    /* TODO: not yet decoded - body of function 0x2314 */
}

/* CRO 0x2468 */
static void DllStaffRoll_2468(void) {
    /* TODO: not yet decoded - body of function 0x2468 */
}

/* CRO 0x2570 */
static void DllStaffRoll_2570(void) {
    /* TODO: not yet decoded - body of function 0x2570 */
}

/* CRO 0x26a8 */
static void DllStaffRoll_26a8(void) {
    /* TODO: not yet decoded - body of function 0x26a8 */
}

/* CRO 0x26f8 */
static void DllStaffRoll_26f8(void) {
    /* TODO: not yet decoded - body of function 0x26f8 */
}

/* CRO 0x2748 */
static void DllStaffRoll_2748(void) {
    /* TODO: not yet decoded - body of function 0x2748 */
}

/* CRO 0x279c */
static void DllStaffRoll_279c(void) {
    /* TODO: not yet decoded - body of function 0x279c */
}

/* CRO 0x27e8 */
static void DllStaffRoll_27e8(void) {
    /* TODO: not yet decoded - body of function 0x27e8 */
}

/* CRO 0x2948 */
static void DllStaffRoll_2948(void) {
    /* TODO: not yet decoded - body of function 0x2948 */
}

/* CRO 0x2a0c */
static void DllStaffRoll_2a0c(void) {
    /* TODO: not yet decoded - body of function 0x2a0c */
}

/* CRO 0x2ac4 */
static void DllStaffRoll_2ac4(void) {
    /* TODO: not yet decoded - body of function 0x2ac4 */
}

/* CRO 0x2afc */
static void DllStaffRoll_2afc(void) {
    /* TODO: not yet decoded - body of function 0x2afc */
}

/* CRO 0x2b40 */
static void DllStaffRoll_2b40(void) {
    /* TODO: not yet decoded - body of function 0x2b40 */
}

/* CRO 0x2b84 */
static void DllStaffRoll_2b84(void) {
    /* TODO: not yet decoded - body of function 0x2b84 */
}

/* CRO 0x2d64 */
static void DllStaffRoll_2d64(void) {
    /* TODO: not yet decoded - body of function 0x2d64 */
}

/* === BL targets (cross-function / cross-CRO call relationships) === */
/* These are the immediate branch-with-link targets observed in the disassembly. */
/* Targets within this module land in another function's prologue; targets at */
/* offsets in the loader trampoline area land in the patch table and therefore */
/* belong to an imported module. */

/* Intra-module calls (target = another prologue): */
/*   0x0450 -> DllStaffRoll_0450 */
/*   0x0900 -> DllStaffRoll_0900 */
/*   0x0fe8 -> DllStaffRoll_0fe8 */
/*   0x183c -> DllStaffRoll_183c */
/*   0x1908 -> DllStaffRoll_1908 */
/*   0x1d04 -> DllStaffRoll_1d04 */
/*   0x1ef8 -> DllStaffRoll_1ef8 */
/*   0x2194 -> DllStaffRoll_2194 */
/*   0x27e8 -> DllStaffRoll_27e8 */

/* External patch calls (target = loader trampoline at seg_off): */
/*   0x028c -> imported via patch at seg_off 0x28c */
/*   0x0294 -> imported via patch at seg_off 0x294 */
/*   0x029c -> imported via patch at seg_off 0x29c */
/*   0x02a4 -> imported via patch at seg_off 0x2a4 */
/*   0x02bc -> imported via patch at seg_off 0x2bc */
/*   0x02c4 -> imported via patch at seg_off 0x2c4 */
/*   0x03fc -> imported via patch at seg_off 0x3fc */
/*   0x0404 -> imported via patch at seg_off 0x404 */
/*   0x0414 -> imported via patch at seg_off 0x414 */
/*   0x0450 -> imported via patch at seg_off 0x450 */

/* === End of preliminary reconstruction === */
/* The exports and BL targets above are grounded in the disassembly; the function */
/* bodies are placeholders to be filled in by follow-up analysis. */
