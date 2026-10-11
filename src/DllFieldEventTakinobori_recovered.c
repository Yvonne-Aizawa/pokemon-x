/*
 * Preliminary decompilation of DllFieldEventTakinobori.cro.
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
 *   - vtable layout for DllFieldEventTakinobori objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllFieldEventTakinobori.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x37c0 size 0x14 (20 bytes)
 *   bss:  0x20 bytes
 *   named exports: 1
 *   import modules: 2
 *   external patches: 63
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1af8: nnroControlObject_
 */

/*
 * CRO 0x1af8: control-object table. Loader entry for DllFieldEventTakinobori.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 34 slot(s)
 *   [1] module `DllField`: 29 anonymous slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllFieldEventTakinobori_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllFieldEventTakinobori_Object DllFieldEventTakinobori_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x368: push {r4, r5, r6, lr} */
static int
DllFieldEventTakinobori_368(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x9a0: push {r4, r5, r6, lr} */
static int
DllFieldEventTakinobori_9a0(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x10f8: push {r4, r5, lr} */
static int
DllFieldEventTakinobori_10f8(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1178: push {r4, r5, r6, lr} */
static int
DllFieldEventTakinobori_1178(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x11e4: push {r4, r5, r6, r7, r8, lr} */
static int
DllFieldEventTakinobori_11e4(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1344: push {r4, r5, r6, lr} */
static int
DllFieldEventTakinobori_1344(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x15f4: push {r4, lr} */
static int
DllFieldEventTakinobori_15f4(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1640: push {r4, r5, r6, r7, r8, r9, sl, lr} */
static int
DllFieldEventTakinobori_1640(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c38: push {r4, lr} */
static int
DllFieldEventTakinobori_1c38(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c80: push {r4, lr} */
static int
DllFieldEventTakinobori_1c80(DllFieldEventTakinobori_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 10 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 10 intra-CRO functions above,
 *   (b) the 2 import module(s), or
 *   (c) the 63 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
