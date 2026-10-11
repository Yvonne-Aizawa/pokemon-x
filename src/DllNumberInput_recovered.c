/*
 * Preliminary decompilation of DllNumberInput.cro.
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
 *   - vtable layout for DllNumberInput objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllNumberInput.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3a18 size 0x14 (20 bytes)
 *   bss:  0x20 bytes
 *   named exports: 1
 *   import modules: 1
 *   external patches: 83
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1978: nnroControlObject_
 */

/*
 * CRO 0x1978: control-object table. Loader entry for DllNumberInput.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 81 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllNumberInput_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllNumberInput_Object DllNumberInput_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x3d8: push {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllNumberInput_3d8(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x6a0: push {r4, lr} */
static int
DllNumberInput_6a0(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x6bc: push {r4, r5, r6, lr} */
static int
DllNumberInput_6bc(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x7e4: push {r3, r4, r5, r6, r7, lr} */
static int
DllNumberInput_7e4(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x9ec: push {r3, r4, r5, r6, r7, lr} */
static int
DllNumberInput_9ec(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb48: push {r4, r5, r6, lr} */
static int
DllNumberInput_b48(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xc44: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllNumberInput_c44(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf34: push {r3, lr} */
static int
DllNumberInput_f34(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf7c: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllNumberInput_f7c(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x129c: push {r4, r5, lr} */
static int
DllNumberInput_129c(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1330: push {r4, lr} */
static int
DllNumberInput_1330(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x13d0: push {r4, lr} */
static int
DllNumberInput_13d0(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x13ec: push {r4, r5, r6, lr} */
static int
DllNumberInput_13ec(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x14d8: push {r4, r5, r6, r7, lr} */
static int
DllNumberInput_14d8(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1648: push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllNumberInput_1648(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1744: push {r3, r4, r5, r6, r7, r8, r9, lr} */
static int
DllNumberInput_1744(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1814: push {r4, r5, r6, lr} */
static int
DllNumberInput_1814(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1890: push {r4, lr} */
static int
DllNumberInput_1890(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x18dc: push {r4, lr} */
static int
DllNumberInput_18dc(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x18fc: push {r3, r4, r5, r6, r7, lr} */
static int
DllNumberInput_18fc(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1974: push {r4, lr} */
static int
DllNumberInput_1974(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19dc: push {r4, lr} */
static int
DllNumberInput_19dc(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a44: push {r4, lr} */
static int
DllNumberInput_1a44(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a7c: push {r4, lr} */
static int
DllNumberInput_1a7c(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b00: push {r4, lr} */
static int
DllNumberInput_1b00(DllNumberInput_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 25 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 25 intra-CRO functions above,
 *   (b) the 1 import module(s), or
 *   (c) the 83 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
