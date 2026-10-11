/*
 * Preliminary decompilation of DllLangSelect.cro.
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
 *   - vtable layout for DllLangSelect objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllLangSelect.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3bd0 size 0x1c (28 bytes)
 *   bss:  0x44 bytes
 *   named exports: 1
 *   import modules: 1
 *   external patches: 95
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1a9c: nnroControlObject_
 */

/*
 * CRO 0x1a9c: control-object table. Loader entry for DllLangSelect.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 93 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllLangSelect_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllLangSelect_Object DllLangSelect_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x438: push {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllLangSelect_438(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x5b0: push {r4, lr} */
static int
DllLangSelect_5b0(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x5cc: push {r3, r4, r5, lr} */
static int
DllLangSelect_5cc(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x70c: push {r3, r4, r5, lr} */
static int
DllLangSelect_70c(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x87c: push {r3, r4, r5, r6, r7, r8, r9, lr} */
static int
DllLangSelect_87c(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x98c: push {r4, r5, r6, lr} */
static int
DllLangSelect_98c(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa04: push {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllLangSelect_a04(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe64: push {r4, r5, lr} */
static int
DllLangSelect_e64(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xebc: push {r3, r4, r5, r6, r7, lr} */
static int
DllLangSelect_ebc(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf50: push {r3, r4, r5, lr} */
static int
DllLangSelect_f50(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x102c: push {r4, r5, r6, r7, lr} */
static int
DllLangSelect_102c(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x10f0: push {r3, r4, r5, lr} */
static int
DllLangSelect_10f0(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1194: push {r3, r4, r5, r6, r7, lr} */
static int
DllLangSelect_1194(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x130c: push {r4, r5, r6, lr} */
static int
DllLangSelect_130c(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x13c0: push {r4, lr} */
static int
DllLangSelect_13c0(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1414: push {r4, r5, r6, r7, r8, lr} */
static int
DllLangSelect_1414(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1564: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllLangSelect_1564(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1814: push {r4, r5, r6, lr} */
static int
DllLangSelect_1814(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x18fc: push {r4, r5, r6, lr} */
static int
DllLangSelect_18fc(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19a0: push {r4, lr} */
static int
DllLangSelect_19a0(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a18: push {r4, lr} */
static int
DllLangSelect_1a18(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a38: push {r3, r4, r5, r6, r7, lr} */
static int
DllLangSelect_1a38(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1aac: push {r4, lr} */
static int
DllLangSelect_1aac(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b14: push {r4, lr} */
static int
DllLangSelect_1b14(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b7c: push {r4, lr} */
static int
DllLangSelect_1b7c(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1bb4: push {r4, lr} */
static int
DllLangSelect_1bb4(DllLangSelect_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c24: push {r4, lr} */
static int
DllLangSelect_1c24(DllLangSelect_Object *self /* TODO: not yet decoded */)
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
 *   (c) the 95 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
