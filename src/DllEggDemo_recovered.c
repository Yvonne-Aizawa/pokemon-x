/*
 * Preliminary decompilation of DllEggDemo.cro.
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
 *   - vtable layout for DllEggDemo objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllEggDemo.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3e08 size 0x1c (28 bytes)
 *   bss:  0x20 bytes
 *   named exports: 2
 *   import modules: 2
 *   external patches: 137
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x161c: nnroControlObject_
 *   0x15e0: _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/*
 * CRO 0x161c: control-object table. Loader entry for DllEggDemo.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * CRO 0x15e0: _ZN9xy_system2bg6System13SetIsCallDrawEb
 * Demangled: xy_system::bg::System::SetIsCallDraw(bool)
 * Confirmed signature: void (*)(System*, bool)
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 124 slot(s)
 *   [1] module `DllSequence`: 11 anonymous slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllEggDemo_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllEggDemo_Object DllEggDemo_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x568: push {r4, lr} */
static int
DllEggDemo_568(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x584: push {r3, r4, r5, lr} */
static int
DllEggDemo_584(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x680: push {r4, r5, r6, r7, lr} */
static int
DllEggDemo_680(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x72c: push {r4, lr} */
static int
DllEggDemo_72c(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x780: push {r4, r5, lr} */
static int
DllEggDemo_780(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x810: push {r4, r5, r6, lr} */
static int
DllEggDemo_810(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x8dc: push {r4, r5, r6, lr} */
static int
DllEggDemo_8dc(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x9b4: push {r4, r5, r6, r7, r8, lr} */
static int
DllEggDemo_9b4(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb54: push {r4, r5, r6, r7, lr} */
static int
DllEggDemo_b54(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xcfc: push {r4, r5, r6, lr} */
static int
DllEggDemo_cfc(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe68: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllEggDemo_e68(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf6c: push {r3, r4, r5, r6, r7, lr} */
static int
DllEggDemo_f6c(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x113c: push {r4, r5, r6, lr} */
static int
DllEggDemo_113c(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1304: push {r4, r5, r6, r7, r8, lr} */
static int
DllEggDemo_1304(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x14dc: push {r4, lr} */
static int
DllEggDemo_14dc(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1514: push {r4, lr} */
static int
DllEggDemo_1514(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1548: push {r4, lr} */
static int
DllEggDemo_1548(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1578: push {r3, r4, r5, r6, r7, lr} */
static int
DllEggDemo_1578(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x15f4: push {r4, lr} */
static int
DllEggDemo_15f4(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1674: push {r4, lr} */
static int
DllEggDemo_1674(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x16f4: push {r4, lr} */
static int
DllEggDemo_16f4(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x172c: push {r4, lr} */
static int
DllEggDemo_172c(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x17a4: push {r4, lr} */
static int
DllEggDemo_17a4(DllEggDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 23 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 23 intra-CRO functions above,
 *   (b) the 2 import module(s), or
 *   (c) the 137 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
