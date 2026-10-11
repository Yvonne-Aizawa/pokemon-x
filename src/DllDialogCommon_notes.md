# DllDialogCommon notes

This file is a **companion** to `src/dialog_common_recovered.c`. The
latter documents only the seven functions reachable from the top of the
file. This note captures everything else that the disassembler exposes
and that a byte-match build would also have to provide.

## Module file
`extracted/romfs/DllDialogCommon.cro`
- code region `0x180 .. 0x180 + 0x1e80` (ARM mode)
- segment 0 (ARM) `0x180 .. 0xdbc`
- segment 1 (THM) `0x1000 .. 0x118c`
- segment 2 (RO)  `0x2778 .. 0x2794` (28 bytes)
- segment 3 (BSS) `0x0, size 0x24`
- bss            `0x44`
- exports named  1 (`nnroControlObject_`, segment 0, +0xc58)
- imports       57 anonymous entries from `|static|`

## RTTI type names (decoded from `.rodata`, file offsets)
- `N3app2ui15UIInputListenerE`
- `N3app6dialog10MainSystemE`
- `N3app6dialog22DialogCommonUIListenerE`
- `N3app6dialog4ProcE`
- `N3app6dialog8ViewWorkE`
- `N3gfl4proc11BaseProcessE`

These confirm the existing reconstruction's hierarchy:
```
gfl4::proc::BaseProcess
  └─ app::dialog::MainSystem
        └─ app::dialog::Proc
              └─ app::dialog::ViewWork
                    └─ app::dialog::DialogCommonUIListener
                          └─ app::ui::UIInputListener
```

## Functions recovered by the existing file (kept as-is)
- CRO `0x2d8` — `dialog_can_run`
- CRO `0x2e0` — `dialog_can_stop`
- CRO `0x2e8` — `dialog_can_draw`
- CRO `0x2f0/0x2f4/0x2f8/0x2fc` — four empty lifecycle hooks
- CRO `0x300` — `dialog_update` (state dispatch on `[+0x24]`)
- CRO `0x404` — `dialog_shutdown` (vtable delete + state=4)
- CRO `0x43c` — `dialog_transition` (timer countdown + state=2)

## Functions NOT yet documented in the companion file

`grep` of `work/disassembly/DllDialogCommon.arm.asm` shows nineteen
function prologues, of which only seven are reflected in
`dialog_common_recovered.c`. The remaining twelve (each with a clean
`push {..., lr}` and matching `pop {..., pc}`) are listed below for the
next worker to fill in:

| CRO offset | Register mask | Comment |
|---:|---|---|
| `0x300`   | `{r4,r5,lr}`            | already documented as `dialog_update` |
| `0x43c`   | `{r4,r5,r6,lr}`         | already documented as `dialog_transition` |
| `0x5e8`   | `{r4,lr}`               | View dtors: vtable delete + `bl 0x1a8` |
| `0x638`   | `{r4,lr}`               | View dtors (variant) |
| `0x688`   | `{r4,r5,r6,lr}`         | Post-update worker; reads `[+0x24]` then calls `0x300` |
| `0x6c4`   | `{r4,lr}`               | CanDraw helper |
| `0x710`   | `{r3,r4,r5,r6,r7,lr}`   | Proc ctor: `bl 0x1f8` then `+0x180` allocation chain |
| `0x7a4`   | `{r4,lr}`               | `Proc::CanStop` |
| `0x7f0`   | `{r4,lr}`               | `Proc::CanDraw` |
| `0x840`   | `{r4,lr}`               | `Proc::CanRun` |
| `0x8d0`   | `{r4,lr}`               | inner ViewWork sub-ctor (`sub r0,#0x74`) |
| `0x900`   | `{r4..r10,fp,lr}`       | Multi-frame inner Exec (the longest function in this CRO) |
| `0xc34`   | `{r4,lr}`               | UIInputListener::slot #1 (vtable +0x04) |
| `0xc68`   | `{r4,lr}`               | UIInputListener::slot #2 (vtable +0x08) |
| `0xca4`   | `{r4,lr}`               | UIInputListener::slot #3 (vtable +0x0c) |
| `0xcdc`   | `{r4,lr}`               | UIInputListener::slot #4 (vtable +0x10) |
| `0xd20`   | `{r4,lr}`               | UIInputListener::slot #5 (vtable +0x14) |
| `0xde0`   | `{r4,lr}`               | UIInputListener::slot #6 (vtable +0x18) |

Note: `0x900` is the only "big" function in this CRO — it consumes the
entire region `0x900 .. 0xc2c` (≈ 800 bytes) and includes recursive
calls to itself for layout/scroll handling.

## Import call counts

A frequency histogram over `bl / blx` targets in
`work/disassembly/DllDialogCommon.arm.asm` (top of the list):

| Slot  | bl count | Notes |
|---:|---:|---|
| `0x250` | 8 | utility routine, signature-less |
| `0x180` | 5 | work-area allocation |
| `0x248` | 4 | linked-list push |
| `0x218` | 4 | linked-list pop |
| `0x278` | 3 | memset-like zero-fill |
| `0x1d8` | 3 |  |
| `0x1b0` | 3 |  |
| `0x1a8` | 3 |  |
| `0x2d0` | 1 | likely the destructor allocator |
| `0x2b0`..`0x2c8` | 2 each |  |

The 57 anonymous import slots listed in
`work/modules/DllDialogCommon.imports.md` map onto these `bl` targets via
the loader's static import table at file offset `0x2540`.

## Open issues for byte-match

1. The `[+0x14]` field is consistently used as a "child slot" in the
   outer MainSystem, but the existing `dialog_common_recovered.c` does
   not model it. A byte-match build would need to type it as
   `CommendationView*` (cross-referencing the actual inner type).
2. `[+0x7c]` is described as `DialogProc *owner` in the current draft,
   but the disasm never reads/writes `+0x7c` — every other slot up to
   `+0x24..+0x50` is heavily exercised. Until a confirming write is
   found this field is **probably not at +0x7c**; it should be moved
   later in the struct or removed.
3. The vtable indices inferred from the disasm (+0x04 Init, +0x08 ?, +0x10
   Draw, +0x18 Delete, +0x20 Draw2, +0x24 Update, +0x28 Pause) come
   from the call-site pattern, not from any concrete recovery of the
   `nnroControlObject_` table itself — the table exports entry at
   +0xc58 but the disassembly shows it is currently empty (literal
   `andeq r0,r0,r0`). A confirming read through the dispatch slot is
   required before claiming byte-match for the vtable.
4. `dialog_transition` is missing a concrete body — only the
   `[+0x28]` timer countdown and `[+0x24]` state jump to 2 are
   documented; the rest of the function depends on a
   "DialogWork" struct that has not been recovered.

## Cross-references

- `src/dialog_common_recovered.c` — existing partial reconstruction
- `work/modules/DllDialogCommon.info.md` — header facts
- `work/modules/DllDialogCommon.imports.md` — anonymous imports
- `work/modules/DllDialogCommon.patches.md` — patches (none)
- `docs/symbols/DllDialogCommon.map` — exports table
- `work/disassembly/DllDialogCommon.arm.asm` — full ARM disassembly
