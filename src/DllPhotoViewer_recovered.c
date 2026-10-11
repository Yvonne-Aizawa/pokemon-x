/*
 * Preliminary decompilation of DllPhotoViewer.cro.
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
 *   - vtable layout for DllPhotoViewer objects (only field offsets observed)
 *   - any Thumb-mode function (the upstream disassembler emits the
 *     Thumb disassembly as ARM, so push-prologue detection sees ARM only)
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the
 * disassembly shows; everything else is marked TODO.
 */

#include <stdint.h>

/*
 * CRO parameters (from work/modules/DllPhotoViewer.info.md):
 *   code: offset 0x180 size 0x2e80 (11904 bytes)
 *   data: offset 0x3d98 size 0x14 (20 bytes)
 *   bss:  0x5c bytes
 *   named exports: 2
 *   import modules: 1
 *   external patches: 100
 */

/*
 * ---- Named exports (CRO offsets / names) ----
 *   0x1958: nnroControlObject_
 *   0x1828: _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/*
 * CRO 0x1958: control-object table. Loader entry for DllPhotoViewer.
 * The CRO patches list fixes up the addresses of every slot in
 * this table at load time.
 */

/*
 * CRO 0x1828: _ZN9xy_system2bg6System13SetIsCallDrawEb
 * Demangled: xy_system::bg::System::SetIsCallDraw(bool)
 * Confirmed signature: void (*)(System*, bool)
 */

/*
 * ---- Imported modules (anonymized) ----
 *   [0] same-CRO anonymous imports: 95 slot(s)
 * (each anonymous slot is a static / external call target.)
 */

/*
 * ---- Inferred object layout ----
 * Confirmed by repeated access patterns (e.g. ldr r0, [r0, #N]).
 */
struct DllPhotoViewer_Object {
    void *vtable;       /* 0x00 slot[0]; loaded first by destructors and polymorphic call sites in BL chains. */
    void *child;        /* 0x04 first owner reference. */
    /* TODO: not yet decoded - extend using observed [r0, #N] in the disassembly */
};
typedef struct DllPhotoViewer_Object DllPhotoViewer_Object;

/*
 * ---- Function stubs (one per identified prologue) ----
 * Offsets are file-space addresses of the push/ldm instruction.
 */
/* CRO 0x408: push {r4, lr} */
static int
DllPhotoViewer_408(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x454: push {r3, r4, r5, r6, r7, r8, r9, lr} */
static int
DllPhotoViewer_454(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r3, r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x734: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_734(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x8b4: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_8b4(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x954: push {r4, lr} */
static int
DllPhotoViewer_954(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x9b8: push {r4, lr} */
static int
DllPhotoViewer_9b8(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xa68: push {r4, lr} */
static int
DllPhotoViewer_a68(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xac4: push {r4, lr} */
static int
DllPhotoViewer_ac4(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xb84: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_b84(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xc08: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_c08(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xce4: push {r4, lr} */
static int
DllPhotoViewer_ce4(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xd10: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_d10(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe04: push {r4, lr} */
static int
DllPhotoViewer_e04(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xe60: push {r4, lr} */
static int
DllPhotoViewer_e60(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0xeb4: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllPhotoViewer_eb4(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1018: push {r4, r5, r6, r7, r8, r9, lr} */
static int
DllPhotoViewer_1018(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, r8, r9, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x153c: push {r4, lr} */
static int
DllPhotoViewer_153c(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x158c: push {r4, r5, r6, r7, lr} */
static int
DllPhotoViewer_158c(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, r7, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x17ec: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_17ec(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1888: push {r4, r5, r6, lr} */
static int
DllPhotoViewer_1888(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, r5, r6, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x193c: push {r4, lr} */
static int
DllPhotoViewer_193c(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1974: push {r4, lr} */
static int
DllPhotoViewer_1974(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
{
    /* Original prologue saves {r4, lr}; behavior not recovered. */
    (void)self;
    return 0;
}

/* CRO 0x1ae0: push {r4, lr} */
static int
DllPhotoViewer_1ae0(DllPhotoViewer_Object *self /* TODO: not yet decoded */)
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
 *   (b) the 1 import module(s), or
 *   (c) the 100 external patches (which form the PLT).
 *
 * Without demangled names for the imported symbols, no single call site
 * can be grounded in a C-level function; bodies are stubs.
 */
