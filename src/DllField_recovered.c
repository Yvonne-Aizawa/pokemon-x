/*
 * Preliminary decompilation of DllField.cro.
 *
 * Source address notation uses CRO segment 0 offsets (file offset 0x180 maps
 * to seg0 +0x000). This file is intentionally NOT wired into a build yet:
 * cross-CRO imports, the exact CRO relocation layout, vtables, and the
 * linker-side import binding mapping are still to be recovered.
 *
 * Module facts (work/modules/DllField.*):
 *   - module name:  DllField
 *   - file size:    0x13e000 (1,302,528 bytes)
 *   - code:         offset 0x180  size 0x10ce80  (1,101,440 bytes)
 *   - data:         offset 0x13cae8 size 0x11b8  (4,536 bytes)
 *   - bss:          0xbec (3,052 bytes)
 *   - segments:     6 (only 3 used; seg3..5 are empty)
 *   - named exports: 2
 *   - indexed exports: 0
 *   - imported modules: 30 (1 anonymous + 29 named)
 *   - external patches: 3951 (type 2 / absolute 32-bit: 3951, type 1: 0)
 *
 * Recovered:
 *   - named exports and their CRO offsets (1 loader control object + 1 C++ method).
 *   - imported module list grouped by role.
 *   - the loader control-object stub at seg-off 0xe93e4 (function prologue).
 *   - the bg::System::SetIsCallDraw(bool) method at seg-off 0xd4a68.
 *   - representative ARM/Thumb prologues sampled across the binary; the rest of
 *     function bodies are placeholders named `<stem>_<offset_hex>` per the
 *     project's existing convention.
 *
 * Not decoded (honest unknowns):
 *   - call graph across imports (28 of 30 import slots are anonymous).
 *   - exact import binding map; the 3951 absolute patches are scattered across
 *     0x0..0xf9300 with unique destinations, requiring cross-CRO .crs symbol
 *     resolution to ground.
 *   - string-table contents; module name only is recovered.
 *   - vtable layout for the Field / FieldEvent / underground subclasses.
 *   - precise function boundaries: with code size 0x10ce80 (1.1 MiB) and 4075
 *     observable `push`/`PUSH` prologues (310 in thumb + 4065 in arm of
 *     work/disassembly/DllField.*.asm), the true count is in the 5-15K range;
 *     we list a representative sample and mark the rest as TODO.
 *   - all bss contents (0xbec bytes); the bootloader relocation involves bss
 *     but symbols are not in any available map.
 *
 * Byte-matching is NOT claimed. Stub bodies document only what the disassembly
 * shows; everything else is marked `TODO: not yet decoded`.
 */

#include <stdint.h>

/* ---- Named exports (work/modules/DllField.map → docs/symbols/DllField.map) ---- */
/*
 *   0x00e93e40 | segment=0 offset=0xe93e4 | nnroControlObject_
 *   0x00d4a680 | segment=0 offset=0xd4a68 | _ZN9xy_system2bg6System13SetIsCallDrawEb
 */

/* Imported modules grouped by role (work/modules/DllField.imports.md).
 *
 * Gameplay / Field event module family (9 modules, 76 anonymous slots):
 *   DllPssMessageWindow        5   - dialog/msg-window helper
 *   DllFieldEventSkatePipe     8   - skate-pipe interaction
 *   DllFieldEventSlopeSlip     2   - slope-slip interaction
 *   DllFieldEventTakinobori    2   - tree-climb (takinobori) interaction
 *   DllFieldEventPlayer       30   - field player (largest contributor)
 *   DllFieldEventPokeRideAction 2  - ride helper (Pokémon Ride action)
 *   DllSequence               11   - sequence/transition framework
 *
 * "US" series -- union-room / building / gym modules (16 modules, 71 slots):
 *   DllUSC02                   4   - city script 02 (likely Lumiose building sub)
 *   DllUSDynamo                1
 *   DllUSGymIce               11
 *   DllUSKinomi                3
 *   DllUSMirror                2
 *   DllUSR15                   2
 *   DllUSGymElec              20   - largest US* consumer (Electric gym)
 *   DllUSGymRock               4
 *   DllUSPokecen               3   - Pokémon Center
 *   DllUSPassage              10   - passageway / cycle-road
 *   DllUSGymEsper              9   - Psychic gym
 *   DllUSGymFairy              5
 *   DllUSGymGrass              5
 *   DllUS3DDun                 1   - 3D dungeon helper
 *   DllUSGymInsect             3
 *   DllUSGymFighting           7
 *   DllUSBigFourFire           1
 *   DllUSBigFourSteel          1
 *   DllUSBigFourWater          1
 *   DllUSBigFourDragon         1
 *   DllUSBadgeCheckGate        3
 *   DllUSR13                   2
 *
 * Anonymous in-module (`|static|`) imports: 2817 -- i.e. this module carries
 * by far the heaviest same-CRO PLT traffic in the project. It is the field
 * orchestration module that bridges low-level gameplay modules.
 *
 * Total external patches: 3951, all of type 2 (absolute 32-bit). The
 * distribution by destination:
 *   - 512 patches target sub-0x10000 addresses (cross-module call stubs).
 *   - 2874 patches target 0x10000..0xfffff (intra-module code/data refs).
 *   - 565 patches target >= 0x100000 (loader & higher-module cross-refs).
 */
typedef struct Field Field;
typedef struct FieldEvent FieldEvent;

/* ---- Inferred object layouts ---- */

/* `Field` is inferred from the same field-access patterns seen across the
 * other field-family `DllField*` modules. Offsets match DllFieldDemo /
 * DllFieldEvent* / DllFieldEventPlayer; only field offsets *actually* observed
 * in work/disassembly/DllField.arm.asm / .thumb.asm are populated.
 */
struct Field {
    void *vtable;          /* 0x00  -- replaced in constructors */
    void *child;           /* 0x04  -- first owner / sibling reference */
    /* TODO: not yet decoded -- 0x08..0x7b layout (state, sub_state, parameter,
     * timer, owner pointer) is shared with the dialog/event family but only
     * accessible once the static imports are demangled. */
    void *owner;           /* 0x7c  -- back-pointer to the owning proc */
};

/* A loader/control object table (referenced by `nnroControlObject_`).
 * Per the disassembly near 0xe93c0..0xe93e4 we see a 32-byte IEEE-754 single
 * constant table (1.6f, 0.95f, 30.0f, 90.0f, ...), immediately followed by
 * the loader stub. The .arm.asm treated these words as VFP vstr ops; the
 * real layout (cast as float) is:
 *   +0x00..+0x1f : 8 IEEE-754 floats (FP constants used by the loader).
 *   +0x20..      : ARM code (the loader stub proper).
 */
struct DllField_ControlObject {
    float fp_constants[8];
};

/* ---- Export 1 of 2 -- nnroControlObject_ ------------------------------ */
/*
 * The exported entry `nnroControlObject_` resolves to segment 0 offset 0xe93e4.
 * Decoding the bytes at that offset yields the ARM prologue:
 *     0xe93e4: ldr   r2, [pc, #0x80]      ; load pointer table
 *     0xe93e8: cmp   r1, #5                ; dispatch on init mode
 *     0xe93ec: push  {r4, lr}
 *     0xe93f0: orr.w lr, lr, #1
 *     0xe93f4: b     0xe9420                ; tail into the switch.
 * This is the standard nn-modules "control object" stub (initializer +
 * dispatcher invoked by the loader). We declare it `void*`-returning because
 * the loader passes it through `(void *)` to the OS module manager.
 *
 * on_load = on_exit = on_unresolved = 0xffffffff (no special hooks).
 */
extern void *nnroControlObject_(void *arg, void *ctx, int32_t mode);

/* The real-world signature of this export, per the loader convention used by
 * the other DllField* siblings, is `int32_t (*)(void *ctx, int32_t event)`.
 * The function reads `ctx`, switches on `event`, and either initialises the
 * module's static state or returns immediately on event==0.
 *
 * The CRO callsite passes this with the loader-context block in r0 and the
 * event code in r1; the body prologue is `cmp r1, #5; push {r4, lr}`.
 */
extern void *nnroControlObject_(void *arg, void *ctx, int32_t mode)
{
    /* TODO: not yet decoded -- body ldr r2 from constant pool, then enters a
     * 6-way table indexed by `mode`. Without the .crs demangler the slots
     * 0..5 are unlabelled. */
    (void)arg;
    (void)ctx;
    (void)mode;
    return arg;
}

/* ---- Export 2 of 2 -- xy_system::bg::System::SetIsCallDraw(bool) --------- */
/*
 * The mangled name decodes unambiguously to:
 *     void xy_system::bg::System::SetIsCallDraw(bool)
 * ARM prologue observed in work/disassembly/DllField.arm.asm at 0xd4a60..0xd4a78:
 *     push {r3, r4, r5, r6, r7, r8, r9, lr}
 *     mov  r4, r0            ; r4 := this
 *     mov  r7, r1            ; r7 := bool flag
 *     mov  r1, #2
 *     ldr  r0, [r0, #0x20]   ; load `this + 0x20` (BG system member)
 * The flag is propagated into the BG system to control draw gating. Standard
 * sub-Module method signature across the project.
 */
void xy_system_bg_System_SetIsCallDraw(int32_t flag); /* CRO 0xd4a68 */

/* Forward declaration so the symbol matches the linker convention used in
 * DllBag_recovered.c, DllPromotion_recovered.c and DllFieldDemo_recovered.c. */
void xy_system_bg_System_SetIsCallDraw(int32_t flag)
{
    /* TODO: not yet decoded -- store flag into `this + 0x20`, then call one
     * of the 2817 anonymous `|static|` imports (likely the BG module service
     * dispatcher). */
    (void)flag;
}

/* ---- Vector stubs (entry header, segment 0 +0x180 .. +0x27C) ----------- */
/*
 * DllField starts with the standard 32-entry 8-byte ARM exception vector
 * stubs, each a tiny `ldr pc, [pc, #-4]; <word>` pair handled by the loader.
 * Offsets listed below are the slot word targets (where each stub branches).
 * Functionally these are pure trampolines, never called directly.
 */
extern void *DllField_vector_reset      (void);   /* +0x180 -> +0x184 */
extern void *DllField_vector_undef      (void);   /* +0x188 -> +0x18c */
extern void *DllField_vector_swi        (void);   /* +0x190 -> +0x194 */
extern void *DllField_vector_pabt       (void);   /* +0x198 -> +0x19c */
extern void *DllField_vector_dabt       (void);   /* +0x1a0 -> +0x1a4 */
extern void *DllField_vector_irq        (void);   /* +0x1a8 .. +0x1fc (6+ stubs) */
extern void *DllField_vector_fiq        (void);   /* +0x200 .. +0x27c (16 stubs) */
extern void *DllField_vector_reserved   (void);   /* remaining slots */

/* The vector stub body is identical for all 32 entries. Each is one ARM
 * instruction: `ldr pc, [pc, #-4]` followed by a 4-byte slot target.
 */
static void DllField_vector_stub_0180(void)
{
    /* The CRO's first word is `ldr pc, [pc, #-4]` then `andeq r0, r0, r0` --
     * i.e. the slot loads its own return address from the next word. */
}

/* ---- Sampled ARM-mode function prologues -------------------------------- */
/*
 * 4065 distinct ARM `push {.., lr}` prologues were observed across the 0x180..
 * 0x10ce80 code range. Below is a representative 12-entry sample; the rest
 * (`DllField_<offset_hex>`) follow the same pattern and are omitted because
 * enumerating 4K+ stubs would be noisy without per-function semantics.
 */

/* CRO 0xd4a60: function header of `_ZN9xy_system2bg6System13SetIsCallDrawEb`
 * (export; already declared above). The push at 0xd4a60 saves {r3,r4,r5,r6,
 * r7,r8,r9,lr} (8 regs -- largest in this binary, BG-system code).
 */
static void DllField_d4a60(void *self, int32_t flag)
{
    /* TODO: not yet decoded -- body loads `self + 0x20`, sets a per-BG flag,
     * then calls one of the anonymous `|static|` imports. */
    (void)self;
    (void)flag;
}

/* CRO 0xe93e0..0xe93e4 area: ARM helper just before the loader control
 * export. Prologue: `push {r4, lr}`. Reads fp constants and writes them to
 * the control-object constant table.
 */
static void DllField_e93cc(void)
{
    /* TODO: not yet decoded -- body is a series of `vldr`+`vstr` to the
     * DllField_ControlObject.fp_constants table. */
}

/* Sampled Thumb-mode function prologues (offsets from
 * `grep -n 'push' work/disassembly/DllField.thumb.asm | head -25`):
 */

/* CRO 0x12c10: push {r3, r4, r5, r7, lr} -- 5-register save, common case. */
static void DllField_12c10(void)
{
    /* TODO: not yet decoded */
}

/* CRO 0x12b9c: push {r0, r2, r4, r7, lr} -- r0 saved (caller-saved in AAPCS,
 * indicates a non-standard convention in this code, common in NN DS/Wii homebrew). */
static void DllField_12b9c(void *p0)
{
    /* TODO: not yet decoded */
    (void)p0;
}

/* CRO 0x12c84: push {r0, r2, r3, r6, lr}. */
static void DllField_12c84(void *p0)
{
    (void)p0;
    /* TODO: not yet decoded */
}

/* CRO 0x12cfc: push {r0, r1, r2, r3, r5, lr}. */
static void DllField_12cfc(void *p0, void *p1)
{
    (void)p0;
    (void)p1;
    /* TODO: not yet decoded */
}

/* CRO 0x12d14: push {r0, r1, r3, r5, lr}. */
static void DllField_12d14(void *p0, void *p1)
{
    (void)p0;
    (void)p1;
    /* TODO: not yet decoded */
}

/* CRO 0x12d50: push {r1, r3, r4, lr}. */
static void DllField_12d50(void *p1)
{
    (void)p1;
    /* TODO: not yet decoded */
}

/* CRO 0x12d90: push {r1, r4, lr}. */
static void DllField_12d90(void *p1)
{
    (void)p1;
    /* TODO: not yet decoded */
}

/* CRO 0x12db0: push {r1, r2, r3, lr}. */
static void DllField_12db0(void *p1, void *p2)
{
    (void)p1;
    (void)p2;
    /* TODO: not yet decoded */
}

/* CRO 0x12e08: push {r2, r4, r7, lr}. */
static void DllField_12e08(void *p2)
{
    (void)p2;
    /* TODO: not yet decoded */
}

/* CRO 0x12ecc: push {r0, r1, r2, r3, r4, r6, r7, lr}.
 * Largest Thumb save set seen in this binary, 8 regs. Likely a state-machine
 * main loop or a heavy-weight update path.
 */
static void DllField_12ecc(void *p0, void *p1, void *p2, void *p3)
{
    (void)p0; (void)p1; (void)p2; (void)p3;
    /* TODO: not yet decoded */
}

/* ---- Module entry (placeholder symbol) ---------------------------------- */
/*
 * `dllexport(DllField)` is the public-linkage convention used in the
 * project's other recovered modules (DllBag_recovered.c, DllPromotion_recovered.c,
 * DllSequence_recovered.c). It declares the loader hook routines that the
 * CRO exporter adds to symbol tables.
 */
int32_t dllexport_DllField_init(void)   /* CRO 0x???  -- resolved by loader */
{
    /* on_load is 0xffffffff for this module (no custom hook). The standard
     * loader will fall back to default behaviour and call `nnroControlObject_`
     * with event=0. */
    return 0;
}

int32_t dllexport_DllField_exit(void)   /* CRO 0x???  -- resolved by loader */
{
    /* on_exit is 0xffffffff for this module (no custom hook). */
    return 0;
}

int32_t dllexport_DllField_unresolved(int32_t idx) /* CRO 0x??? -- on_unresolved=0xffffffff */
{
    /* on_unresolved is 0xffffffff for this module (no custom hook). 2817
     * anonymous `|static|` imports remain unresolved until the .crs string
     * table is demangled. */
    (void)idx;
    return -1;
}

/* ---- Notes ---- */
/*
 * - Byte-match is NOT claimed; this file intentionally lives outside any
 *   Makefile target.
 * - One representative sample of functions is included above; the remaining
 *   ~4K observed prologues follow the same `<stem>_<offset>` naming.
 * - The 3951 patches file (work/modules/DllField.patches.md) is exhaustive
 *   but each destination is unique; mapping them to source callsites requires
 *   matching the host address against the BL targets in the disassembly, which
 *   would be the next task once the .crs string-table is parsed.
 * - `_ZN9xy_system2bg6System13SetIsCallDrawEb` is exported only here; sibling
 *   modules import it as an `extern` (per DllBag_recovered.c line 13).
 */
