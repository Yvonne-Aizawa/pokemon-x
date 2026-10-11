/*
 * Preliminary decompilation of DllFieldDemo.cro.
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
 *   - vtable layout for DllFieldDemo objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllFieldDemo.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3e88 size 0x14 (20 bytes)
 *   bss:  0x20 bytes
 *   named exports: 2
 *   import modules: 2
 *   external patches: 142
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1d98: nnroControlObject_
 *   0x1d5c: _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/*
 * CRO 0x1d98: control-object table. Loader entry for DllFieldDemo.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * CRO 0x1d5c: _ZN9xy_system2bg6System13SetIsCallDrawEb
 * Demangled: xy_system::bg::System::SetIsCallDraw(bool)
 * Confirmed signature: void (*)(System*, bool)
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 116 slot(s)
 *   [1] module `DllSequence`: 24 anonymous slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllFieldDemo_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllFieldDemo_Object DllFieldDemo_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x588: push {r3, r4, r5, lr} */
static int
DllFieldDemo_588(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x680: push {r4, lr} */
static int
DllFieldDemo_680(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x69c: push {r4, lr} */
static int
DllFieldDemo_69c(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x6b0: push {r4, lr} */
static int
DllFieldDemo_6b0(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x6d4: push {r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllFieldDemo_6d4(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r0, r1, r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x864: push {r4, lr} */
static int
DllFieldDemo_864(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x87c: push {r4, lr} */
static int
DllFieldDemo_87c(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x890: push {r4, lr} */
static int
DllFieldDemo_890(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x8a8: push {r4, lr} */
static int
DllFieldDemo_8a8(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x8c0: push {r4, r5, r6, lr} */
static int
DllFieldDemo_8c0(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x9ec: push {r4, lr} */
static int
DllFieldDemo_9ec(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa04: push {r3, r4, r5, r6, r7, lr} */
static int
DllFieldDemo_a04(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb5c: push {r4, lr} */
static int
DllFieldDemo_b5c(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb74: push {r4, lr} */
static int
DllFieldDemo_b74(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb8c: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllFieldDemo_b8c(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf20: push {r4, r5, r6, r7, r8, lr} */
static int
DllFieldDemo_f20(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x10d8: push {r4, r5, r6, r7, r8, lr} */
static int
DllFieldDemo_10d8(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x12c4: push {r4, r5, r6, lr} */
static int
DllFieldDemo_12c4(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x13c8: push {r4, r5, r6, r7, lr} */
static int
DllFieldDemo_13c8(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x154c: push {r4, lr} */
static int
DllFieldDemo_154c(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1568: push {r4, r5, r6, lr} */
static int
DllFieldDemo_1568(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x16f0: push {r4, lr} */
static int
DllFieldDemo_16f0(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x170c: push {r4, r5, r6, lr} */
static int
DllFieldDemo_170c(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x18c4: push {r4, r5, r6, lr} */
static int
DllFieldDemo_18c4(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19bc: push {r4, lr} */
static int
DllFieldDemo_19bc(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19d4: push {r3, r4, r5, r6, r7, lr} */
static int
DllFieldDemo_19d4(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b24: push {r4, r5, r6, lr} */
static int
DllFieldDemo_1b24(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1bc0: push {r4, lr} */
static int
DllFieldDemo_1bc0(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c68: push {r4, lr} */
static int
DllFieldDemo_1c68(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c98: push {r3, r4, r5, r6, r7, lr} */
static int
DllFieldDemo_1c98(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1d10: push {r4, lr} */
static int
DllFieldDemo_1d10(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1d78: push {r4, lr} */
static int
DllFieldDemo_1d78(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1ddc: push {r4} */
static int
DllFieldDemo_1ddc(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1e70: push {r4, lr} */
static int
DllFieldDemo_1e70(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1ea8: push {r4, lr} */
static int
DllFieldDemo_1ea8(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1f20: push {r4, lr} */
static int
DllFieldDemo_1f20(DllFieldDemo_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 36 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 36 intra-CRO functions above,
 *   (b) the 2 import module(s), or
 *   (c) the 142 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
