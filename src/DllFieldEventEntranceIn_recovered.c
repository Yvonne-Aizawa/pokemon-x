/*
 * Preliminary decompilation of DllFieldEventEntranceIn.cro.
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
 *   - vtable layout for DllFieldEventEntranceIn objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllFieldEventEntranceIn.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3b80 size 0x54 (84 bytes)
 *   bss:  0x20 bytes
 *   named exports: 1
 *   import modules: 2
 *   external patches: 58
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1a1c: nnroControlObject_
 */

/*
 * CRO 0x1a1c: control-object table. Loader entry for DllFieldEventEntranceIn.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 36 slot(s)
 *   [1] module `DllField`: 11 anonymous slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllFieldEventEntranceIn_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllFieldEventEntranceIn_Object DllFieldEventEntranceIn_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x2e0: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_2e0(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x358: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_358(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x3d0: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_3d0(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x448: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_448(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x4c0: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_4c0(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x538: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_538(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x5b0: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_5b0(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x638: push {r4, lr} */
static int
DllFieldEventEntranceIn_638(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x754: push {r4, lr} */
static int
DllFieldEventEntranceIn_754(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x768: push {r4, lr} */
static int
DllFieldEventEntranceIn_768(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x7d8: push {r4, lr} */
static int
DllFieldEventEntranceIn_7d8(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x808: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_808(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x968: push {r4, lr} */
static int
DllFieldEventEntranceIn_968(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x97c: push {r4, r5, r6, r7, lr} */
static int
DllFieldEventEntranceIn_97c(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb9c: push {r4, r5, r6, r7, r8, lr} */
static int
DllFieldEventEntranceIn_b9c(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xdac: push {r4, lr} */
static int
DllFieldEventEntranceIn_dac(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xdc0: push {r4, r5, r6, lr} */
static int
DllFieldEventEntranceIn_dc0(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1034: push {r4, lr} */
static int
DllFieldEventEntranceIn_1034(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1048: push {r4, r5, r6, r7, lr} */
static int
DllFieldEventEntranceIn_1048(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1268: push {r4, r5, r6, r7, r8, lr} */
static int
DllFieldEventEntranceIn_1268(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x13e8: push {r4, lr} */
static int
DllFieldEventEntranceIn_13e8(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x13fc: push {r4, r5, r6, r7, lr} */
static int
DllFieldEventEntranceIn_13fc(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x161c: push {r4, r5, r6, r7, lr} */
static int
DllFieldEventEntranceIn_161c(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19c8: push {r4, lr} */
static int
DllFieldEventEntranceIn_19c8(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19ec: push {r4, lr} */
static int
DllFieldEventEntranceIn_19ec(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a00: push {r4, lr} */
static int
DllFieldEventEntranceIn_1a00(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a14: push {r4, r5, r6, r7, lr} */
static int
DllFieldEventEntranceIn_1a14(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1ba4: push {r4, lr} */
static int
DllFieldEventEntranceIn_1ba4(DllFieldEventEntranceIn_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 28 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 28 intra-CRO functions above,
 *   (b) the 2 import module(s), or
 *   (c) the 58 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
