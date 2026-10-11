/*
 * Preliminary decompilation of DllPssPlaySelect.cro.
 *
 * Source address notation uses CRO file offsets (segment-0 aligned).
 * This file is intentionally not wired into a build yet: cross-CRO
 * imports, the exact CRO relocation layout, and the imported service
 * signatures still need to be recovered.
 *
 * Recovered:
 *   - named exports and their CRO offsets
 *   - imported module list (anonymous slot counts)
 *   - ARM-mode function boundaries (one stub per identified prologue)
 *   - inferred object layouts from observed field accesses
 *
 * Not yet decoded:
 *   - exact call graph across imports (anonymity hides symbol names)
 *   - string-table contents (multibyte UTF-8/UTF-16)
 *   - vtable layout for DllPssPlaySelect objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllPssPlaySelect.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3900 size 0x14 (20 bytes)
 *   bss:  0x5c bytes
 *   named exports: 2
 *   import modules: 1
 *   external patches: 56
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0xefc: nnroControlObject_
 *   0xd8c: _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/*
 * CRO 0xefc: control-object table. Loader entry for DllPssPlaySelect.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * CRO 0xd8c: _ZN9xy_system2bg6System13SetIsCallDrawEb
 * Demangled: xy_system::bg::System::SetIsCallDraw(bool)
 * Confirmed signature: void (*)(System*, bool)
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 51 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllPssPlaySelect_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllPssPlaySelect_Object DllPssPlaySelect_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x2e4: push {r4, lr} */
static int
DllPssPlaySelect_2e4(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x3a4: push {r4, lr} */
static int
DllPssPlaySelect_3a4(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x3f4: push {r4, lr} */
static int
DllPssPlaySelect_3f4(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x444: push {r4, r5, r6, lr} */
static int
DllPssPlaySelect_444(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x4d8: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllPssPlaySelect_4d8(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x610: push {r3, r4, r5, r6, r7, lr} */
static int
DllPssPlaySelect_610(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x7d8: push {r4, r5, lr} */
static int
DllPssPlaySelect_7d8(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x884: push {r4, r5, r6, r7, r8, lr} */
static int
DllPssPlaySelect_884(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x91c: push {r4, r5, r6, lr} */
static int
DllPssPlaySelect_91c(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa20: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllPssPlaySelect_a20(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xbdc: push {r4, lr} */
static int
DllPssPlaySelect_bdc(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xc10: push {r4, lr} */
static int
DllPssPlaySelect_c10(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xc48: push {r4, r5, r6, lr} */
static int
DllPssPlaySelect_c48(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xd44: push {r4, lr} */
static int
DllPssPlaySelect_d44(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xd9c: push {r3, r4, r5, r6, r7, lr} */
static int
DllPssPlaySelect_d9c(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe2c: push {r4, lr} */
static int
DllPssPlaySelect_e2c(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe64: push {r4, lr} */
static int
DllPssPlaySelect_e64(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xea0: push {r4, lr} */
static int
DllPssPlaySelect_ea0(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xed8: push {r4, lr} */
static int
DllPssPlaySelect_ed8(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf1c: push {r4, r5, r6, lr} */
static int
DllPssPlaySelect_f1c(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1084: push {r4, lr} */
static int
DllPssPlaySelect_1084(DllPssPlaySelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 21 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 21 intra-CRO functions above,
 *   (b) the 1 import module(s), or
 *   (c) the 56 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
