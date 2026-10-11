/*
 * Preliminary decompilation of DllStartMenu.cro.
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
 *   - vtable layout for DllStartMenu objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllStartMenu.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3df8 size 0x14 (20 bytes)
 *   bss:  0x20 bytes
 *   named exports: 1
 *   import modules: 1
 *   external patches: 118
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1b70: nnroControlObject_
 */

/*
 * CRO 0x1b70: control-object table. Loader entry for DllStartMenu.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 111 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllStartMenu_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllStartMenu_Object DllStartMenu_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x480: push {r4, lr} */
static int
DllStartMenu_480(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x4c0: push {r4, lr} */
static int
DllStartMenu_4c0(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x4f8: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllStartMenu_4f8(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x778: push {r4, r5, r6, lr} */
static int
DllStartMenu_778(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x838: push {r4, r5, r6, lr} */
static int
DllStartMenu_838(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x8e0: push {r4, lr} */
static int
DllStartMenu_8e0(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x938: push {r4, r5, r6, lr} */
static int
DllStartMenu_938(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa00: push {r4, lr} */
static int
DllStartMenu_a00(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa48: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllStartMenu_a48(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe5c: push {r4, lr} */
static int
DllStartMenu_e5c(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xeac: push {r4, lr} */
static int
DllStartMenu_eac(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xefc: push {r4, r5, r6, lr} */
static int
DllStartMenu_efc(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xfa4: push {r3, r4, r5, r6, r7, lr} */
static int
DllStartMenu_fa4(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x115c: push {r4, r5, r6, r7, r8, lr} */
static int
DllStartMenu_115c(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x11f4: push {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
static int
DllStartMenu_11f4(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, sl, fp, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1628: push {r4, lr} */
static int
DllStartMenu_1628(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1658: push {r4, r5, r6, r7, r8, lr} */
static int
DllStartMenu_1658(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1804: push {r4, lr} */
static int
DllStartMenu_1804(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x184c: push {r4, lr} */
static int
DllStartMenu_184c(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1890: push {r4, r5, r6, lr} */
static int
DllStartMenu_1890(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1900: push {r4, lr} */
static int
DllStartMenu_1900(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1948: push {r4, lr} */
static int
DllStartMenu_1948(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1994: push {r3, r4, r5, r6, r7, r8, r9, lr} */
static int
DllStartMenu_1994(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1ae4: push {r4, lr} */
static int
DllStartMenu_1ae4(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b08: push {r4, lr} */
static int
DllStartMenu_1b08(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b40: push {r4, lr} */
static int
DllStartMenu_1b40(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1b90: push {r4, lr} */
static int
DllStartMenu_1b90(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1bc8: push {r4, lr} */
static int
DllStartMenu_1bc8(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1c04: push {r4, r5, r6, lr} */
static int
DllStartMenu_1c04(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1cf8: push {r4, lr} */
static int
DllStartMenu_1cf8(DllStartMenu_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/*
 * ---- Notes ----
 * 30 function prologues identified in the ARM-mode disassembly.
 * Identical Thumb prologues are not recovered (see header).
 * BL call sites point to either:
 *   (a) one of the 30 intra-CRO functions above,
 *   (b) the 1 import module(s), or
 *   (c) the 118 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
