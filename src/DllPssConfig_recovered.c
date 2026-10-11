/*
 * Preliminary decompilation of DllPssConfig.cro.
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
 *   - vtable layout for DllPssConfig objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllPssConfig.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3e98 size 0x14 (20 bytes)
 *   bss:  0x5c bytes
 *   named exports: 2
 *   import modules: 1
 *   external patches: 98
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1c98: nnroControlObject_
 *   0x1aa0: _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/*
 * CRO 0x1c98: control-object table. Loader entry for DllPssConfig.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * CRO 0x1aa0: _ZN9xy_system2bg6System13SetIsCallDrawEb
 * Demangled: xy_system::bg::System::SetIsCallDraw(bool)
 * Confirmed signature: void (*)(System*, bool)
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 92 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllPssConfig_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllPssConfig_Object DllPssConfig_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x41c: push {r4, r5, r6, r7, r8, r9, sl, lr} */
static int
DllPssConfig_41c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x620: push {r4, r5, r6, lr} */
static int
DllPssConfig_620(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x66c: push {r4, r5, r6, lr} */
static int
DllPssConfig_66c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x7e0: push {r4, r5, r6, lr} */
static int
DllPssConfig_7e0(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x834: push {r4, r5, r6, lr} */
static int
DllPssConfig_834(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x880: push {r4, r5, r6, lr} */
static int
DllPssConfig_880(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa04: push {r4, r5, r6, lr} */
static int
DllPssConfig_a04(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa50: push {r4, lr} */
static int
DllPssConfig_a50(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa88: push {r4, lr} */
static int
DllPssConfig_a88(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xac0: push {r4, r5, r6, lr} */
static int
DllPssConfig_ac0(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb10: push {r4, lr} */
static int
DllPssConfig_b10(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb3c: push {r4, lr} */
static int
DllPssConfig_b3c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb6c: push {r4, r5, r6, lr} */
static int
DllPssConfig_b6c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xc70: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllPssConfig_c70(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xda0: push {r4, lr} */
static int
DllPssConfig_da0(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xea4: push {r4, r5, r6, lr} */
static int
DllPssConfig_ea4(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xf38: push {r4, r5, lr} */
static int
DllPssConfig_f38(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xfe8: push {r4, lr} */
static int
DllPssConfig_fe8(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1108: push {r3, r4, r5, r6, r7, lr} */
static int
DllPssConfig_1108(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x12c0: push {r4, r5, r6, lr} */
static int
DllPssConfig_12c0(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1450: push {r4, lr} */
static int
DllPssConfig_1450(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1618: push {r4, lr} */
static int
DllPssConfig_1618(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x173c: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllPssConfig_173c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1958: push {r4, lr} */
static int
DllPssConfig_1958(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x198c: push {r4, lr} */
static int
DllPssConfig_198c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x19c4: push {r4, r5, r6, lr} */
static int
DllPssConfig_19c4(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a00: push {r4, lr} */
static int
DllPssConfig_1a00(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a30: push {r4, lr} */
static int
DllPssConfig_1a30(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1a8c: push {r3, r4, r5, r6, r7, lr} */
static int
DllPssConfig_1a8c(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b40: push {r4, lr} */
static int
DllPssConfig_1b40(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b78: push {r4, lr} */
static int
DllPssConfig_1b78(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1bb4: push {r4, lr} */
static int
DllPssConfig_1bb4(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1bec: push {r4, lr} */
static int
DllPssConfig_1bec(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c50: push {r4, r5, r6, lr} */
static int
DllPssConfig_1c50(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1e20: push {r4, lr} */
static int
DllPssConfig_1e20(DllPssConfig_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 35 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 35 intra-CRO functions above,
 *   (b) the 1 import module(s), or
 *   (c) the 98 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
