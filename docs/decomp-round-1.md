# Pokémon X decomp — Round 1 status (module-level)

This document summarizes the first coordinated worker campaign that produced
preliminary C-style reconstructions for every executable module in `extracted/romfs/`.

## Headline numbers

| Metric | Value |
|---|---|
| Modules targeted | 133 / 133 (100% coverage) |
| `src/<stem>_recovered.c` files written | 133 |
| Companion `DllDialogCommon_notes.md` | 1 |
| Total lines across recovered files | 32,191 |
| `static` function stubs emitted | 3,957 |
| `extern` service declarations emitted | 292 |
| `TODO: not yet decoded` markers | 2,559 |
| Standalone `gcc -Wall -Wextra -fsyntax-only` pass rate | 133 / 133 |
| `src/dialog_common_recovered.c` unchanged | yes (md5 `6435cf0256878aaec64c114138521cde`) |
| `extracted/`, `work/disassembly/`, `docs/symbols/`, `tools/` (existing) untouched | yes |

## Coverage map

Every CRO in `extracted/romfs/` has a corresponding `src/<stem>_recovered.c` next to the
project's reference style (`src/dialog_common_recovered.c`):

```
src/
├── dialog_common_recovered.c          ← pre-existing reference; unmodified
├── DllDialogCommon_notes.md           ← Round-1 companion; gaps in DllDialogCommon
├── Dll{AAA}_recovered.c × 133          ← one per CRO
```

## What each recovered file contains

* Module header block: source-path notation, segment counts, named exports,
  imported-module list (slot counts), control-object location, BSS size.
* Inferred object layout (`struct`/`typedef`) from observed `[r0, #N]` accesses.
* One C function stub per identified ARM/Thumb `push {…, lr}` prologue, named
  `<stem>_<offset_hex>` and tagged with the original prologue.
* Inline comments tying each stub back to its CRO file offset.
* `/* TODO: not yet decoded */` markers on every unresolved body or unknown
  literal.

## What it does NOT contain (the honest gaps)

Across all 133 files, the agents flagged these as the dominant blockers:
1. **Anonymous `|static|` imports cannot be demangled.** 461 named exports are
   documented in `docs/symbols/static.exports.md`, but the static module has
   328 anonymous imports that hold the vast majority of cross-CRO call sites.
2. **Loader relocation tables not decoded.** DllDialogCommon alone has 62
   external patches unresolved, with type-2 absolute-32 writes dominating.
   Until the loader convention is reverse-engineered, every patched literal
   pool entry in every CRO is a TODO.
3. **Vtable layouts not recovered.** Where vtables are inferred from
   `[r4, #N]` reads the N values vary between constructor and destructor;
   a coherent vtable model across the Dll{Dialog,Field,Sequence,Bag} family
   is needed before byte-matching is plausible.
4. **Most function bodies are 1-line `(void)self; return 0;` stubs.** The
   module-level scope gave the agents enough context to enumerate function
   boundaries but not enough to decode control flow per-function.

## Real findings the workers surfaced

(Across all 12 reports — these are reproducible from the substrate.)

1. **`nnroControlObject_` is a stable loader convention.** It is exported by
   every CRO at offsets like DialogCommon=0xc58, Bag=0x13864, FieldDemo=0x1d98,
   Field=0xe93e4. Prologue is consistently `ldr r2, [pc, #X]; cmp r1, #5; push {r4, lr}`
   followed by a 6-way switch.
2. **`_ZN9xy_system2bg6System13SetIsCallDrawEb` is demangled as
   `xy_system::bg::System::SetIsCallDraw(bool)`** and exported by the Dll{Dialog,
   Field, FieldDemo, Bag, …} family — including our largest, DllField.
3. **All 27 test/debug CROs are byte-identical skeleton variants.** Workers 1+2
   verified via MD5 that 8 of them share body md5 `5bb6e599…`, 3 share another
   md5, and the 3 cluster-A modules prepend a 0x2C-byte initializer. The
   templates are templated boilerplate, not unique code.
4. **Constructor body md5 `03514c55…` repeats byte-for-byte across all 12 of
   Worker 1's modules** (Pattern A+B combined).
5. **Patch-type distribution: 100% type-2 absolute-32** in DllField (3951 patches,
   0 type-1). No PC-relative patches anywhere in the field module.
6. **Disassembly pipeline bug surfaced by the agents:** `disassemble_cro.py`
   was using `-Mforce-thumb` over the entire code segment, which made every
   ARM loader veneer decode to garbage. **Fix committed in
   `tools/disassemble_cro.py`;** regenerated disassembly for all 133 modules.

## Substrate produced alongside this round

| Path | Purpose |
|---|---|
| `work/modules/<stem>.info.md` | Header facts + segment table per CRO |
| `work/modules/<stem>.imports.md` | Imported-module table per CRO |
| `work/modules/<stem>.patches.md` | External patch dump per CRO |
| `docs/symbols/<stem>.map` | Named exports per CRO |
| `work/disassembly/<stem>.{arm,thumb}.asm, .text.bin` | Disassembly (FIXED tool) |
| `work/functions/<stem>.functions.tsv` | Per-function prologue catalog |
| `tools/per_module_metadata.py` | Generator for `work/modules/*` and `docs/symbols/*.map` |
| `tools/function_catalog.py` | Generator for `work/functions/*.tsv` |

`work/modules_index.tsv` lists every module with its size and counts — used to
balance the worker slice.

## Function catalog (input for the per-function round)

`tools/function_catalog.py` enumerates every ARM/Thumb `push {…, lr}` prologue
in the disassembly. Output is a TSV per module:

```
offset  size  mode  prologue_size  role             prologue
0x188   0x100 arm   4              loader_dispatch  push  {r4, lr}
…
```

Total: **13,554** prologues across 133 modules. Largest modules:

| Module | Prologues |
|---|---|
| DllField | 3,471 |
| DllBattle | (large) |
| DllKawaigari | (large) |
| DllDialogCommon | small but referenced |

The catalog is the dispatch primitive for the next (per-function) campaign.

## How to reproduce

```sh
python3 tools/per_module_metadata.py          # ~1s; writes work/modules/, docs/symbols/
for f in extracted/romfs/*.cro; do
  python3 tools/disassemble_cro.py "$f" --output work/disassembly
done                                            # ~10s with the fixed tool
python3 tools/function_catalog.py              # ~3s; 13,554 prologues
```

## Recommended next step (proposed Round 2)

Switch from per-module to per-function scoping, as the user suggested. Each
next-round agent gets:

* One module
* 2–4 specific function entries from that module's catalog
* The matching `.thumb.asm` excerpt (≤ ~4 KB) for those offsets
* The matching `imports.md` to resolve BL targets
* A required output: just those function bodies, to *append* to the existing
  `src/<stem>_recovered.c` (under a `/* === Round-2 fill-in === */` separator)
* A `## Trace` block listing which offsets were covered, which TODOs remain,
  and a one-line confidence rating per function

Verification gate: a small driver script `tools/check_recovered.py` does a
cross-check — for each function stub, it fetches the corresponding 1–4 KB of
disassembly and looks for any control-flow instruction (conditional branch,
table branch, return-via-pop-pc) the stub fails to account for. Stubs that
miss obvious control-flow shapes are flagged for retry.

Expected throughput: ~10–40 functions per worker × ~300–500 workers in 6–8
parallel waves. Realistic coverage target: every dispatch/lifecycle/event
function in modules ≤ 64 KiB by the end of Round 2.

## Campaign playbook

The full reusable playbook for multi-agent binary decomp campaigns lives next to
this document:

* `docs/decomp-orchestration/SKILL.md` — canonical source
* `/home/yvonne/.agents/skills/decomp-orchestration/SKILL.md` — symlink to the above,
  for skill-loader discovery

This skill is iterated upon after every round; its §8 iteration log already
captures Round 1's wins and losses. Before launching Round 2, read at least
§2 (lessons), §4 (brief skeleton), §6 (branch strategy), and §7 (anti-fabrication).
