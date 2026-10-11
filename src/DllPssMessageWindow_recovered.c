/*
 * Preliminary decompilation of DllPssMessageWindow.cro.
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
 *   - vtable layout for DllPssMessageWindow objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllPssMessageWindow.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3de8 size 0x1c (28 bytes)
 *   bss:  0x80 bytes
 *   named exports: 2
 *   import modules: 1
 *   external patches: 91
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1954: nnroControlObject_
 *   0x1738: _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/*
 * CRO 0x1954: control-object table. Loader entry for DllPssMessageWindow.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * CRO 0x1738: _ZN9xy_system2bg6System13SetIsCallDrawEb
 * Demangled: xy_system::bg::System::SetIsCallDraw(bool)
 * Confirmed signature: void (*)(System*, bool)
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 86 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllPssMessageWindow_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllPssMessageWindow_Object DllPssMessageWindow_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x3dc: push {r4, r5, r6, lr} */
static int
DllPssMessageWindow_3dc(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x594: push {r4, r5, r6, r7, r8, lr} */
static int
DllPssMessageWindow_594(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x75c: push {r4, lr} */
static int
DllPssMessageWindow_75c(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x788: push {r4, r5, r6, lr} */
static int
DllPssMessageWindow_788(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x820: push {r4, r5, r6, lr} */
static int
DllPssMessageWindow_820(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x8b4: push {r4, lr} */
static int
DllPssMessageWindow_8b4(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x994: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllPssMessageWindow_994(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xaec: push {r4, lr} */
static int
DllPssMessageWindow_aec(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb58: push {r4, lr} */
static int
DllPssMessageWindow_b58(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xba0: push {r4, r5, lr} */
static int
DllPssMessageWindow_ba0(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xccc: push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllPssMessageWindow_ccc(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1154: push {r4, r5, r6, r7, lr} */
static int
DllPssMessageWindow_1154(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x12b8: push {r4, lr} */
static int
DllPssMessageWindow_12b8(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1328: push {r4, lr} */
static int
DllPssMessageWindow_1328(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1380: push {r4, r5, r6, lr} */
static int
DllPssMessageWindow_1380(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1448: push {r4, lr} */
static int
DllPssMessageWindow_1448(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x14b8: push {r4, r5, r6, r7, lr} */
static int
DllPssMessageWindow_14b8(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x15e8: push {r4, lr} */
static int
DllPssMessageWindow_15e8(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1620: push {r4, lr} */
static int
DllPssMessageWindow_1620(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x16d4: push {r3, r4, r5, r6, r7, lr} */
static int
DllPssMessageWindow_16d4(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x17d8: push {r4, lr} */
static int
DllPssMessageWindow_17d8(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1810: push {r4, lr} */
static int
DllPssMessageWindow_1810(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x184c: push {r4, lr} */
static int
DllPssMessageWindow_184c(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1884: push {r4, lr} */
static int
DllPssMessageWindow_1884(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x18c8: push {r4, lr} */
static int
DllPssMessageWindow_18c8(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19a0: push {r4, lr} */
static int
DllPssMessageWindow_19a0(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1adc: push {r4, lr} */
static int
DllPssMessageWindow_1adc(DllPssMessageWindow_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 27 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 27 intra-CRO functions above,
 *   (b) the 1 import module(s), or
 *   (c) the 91 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
