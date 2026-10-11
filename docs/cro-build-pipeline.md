# CRO build pipeline

The tooling that compiles recovered C source into a CRO-shape binary
that can be byte-diffed against the original.

## What's in place (Round 3, this commit)

- `tools/rebuild_cro.py` — compiles `src/<stem>_recovered.c` with
  arm-none-eabi-gcc + 3DS-appropriate flags, extracts the .text
  section, and overlays it onto a copy of the original CRO at the
  same byte range. Writes `build/rebuilt/<stem>.cro`.
- `tools/cro_byte_diff.py` — walks the function catalog at
  `work/functions/<stem>.functions.tsv` and SHA-256-checks each
  function's byte range in both original and rebuilt CROs. Reports
  match/diverge with first-byte-of-divergence offset.
- Makefile `rebuild` and `byte-diff` targets.

## Quick demo

```
$ make rebuild MODULE=DllDialogCommon
original .text:  7808 bytes @ 0x180 (sha256 d96e4559…)
compiled .text:   246 bytes (sha256 467681fa…)
*** BYTE DIVERGENCE *** 13/246 first 246 bytes match.
new .text is 246 bytes; original is 7808; padding to match
rebuilt CRO:    build/rebuilt/DllDialogCommon.cro (12288 bytes)

$ make byte-diff MODULE=DllDialogCommon
catalog: 18 function entries
[ ... 18 rows, all DIVERGE, expected because recovered C is stubs ...]
summary: 0/18 match  18 diverge  0 truncated
```

End-to-end. Verified mechanically. **No bytes match yet**, because every
function in `src/<stem>_recovered.c` is `return 0;` or equivalent. But the
infrastructure is in place; Round 4's per-function recovery workers can plug
into it directly.

## Why this is the right shape for the project

A "full CRO linker" would have to:

1. Synthesize a CRO header from scratch.
2. Build a segment table.
3. Reconstruct export, import, and external-patch tables with the right
   resolved symbols.
4. Re-derive every relocation.
5. Stitch into the larger CCI container, with its NCSD/NCCH signatures.

Items 1-3 are tractable but the ABI for *what symbols cross which module*
isn't yet decoded. Items 4-5 require understanding the loader's external
patch semantics, which we documented in `docs/static-status.md` as still
unresolved.

Instead, **`tools/rebuild_cro.py` is deliberately a "patcher," not a
"linker."** It copies the original CRO byte-for-byte and replaces only the
`.text` segment. That isolates one variable:

> *Given the recovered C as input, can we produce the same code bytes as
> the original used?*

If yes for one module → that module is fully decompiled. If no → the byte
diff tells us *which function* diverges, *where in the function* the
divergence starts, and *what the SHA of each side looks like*. That's a
well-bounded task for Round 4 per-function agents.

## Toolchain choice

`arm-none-eabi-gcc` 13.2.1 (system-wide, on PATH). Flags:

```
-mthumb -march=armv6k -mtune=arm1136j-s -mfloat-abi=soft
-mthumb-interwork -fno-asynchronous-unwind-tables -fno-toplevel-reorder
-fno-pic -fno-stack-protector -fno-builtin -ffreestanding -fno-ident -O0
```

- **`-mthumb`**: Pokémon X code runs in Thumb-2 mode except for the
  loader control object at the very start of each CRO (which is ARM).
- **`-march=armv6k -mtune=arm1136j-s`**: the 3DS CPU is an ARM1136J-S.
  Matching these tunes instruction selection.
- **`-mfloat-abi=soft`**: 3DS has no FPU exposed to user code; using
  soft-float avoids pulling in FPU instructions that the original
  couldn't use.
- **`-O0`**: optimize for size *and* for matching disassembly. The
  original was compiled with `O0`-equivalent (no inlining, no constant
  folding across function calls), and `-O0` makes our output match that
  style. Higher optimization levels would diverge in instruction selection
  even when source was correct.
- **`-fno-toplevel-reorder`**: keeps function emission order matching
  source order. Without this, gcc places `static` functions in arbitrary
  order; with it, source order = file order = per-function offsets
  match.
- **`-mthumb-interwork`**: needed because some CROs interwork between
  ARM and Thumb; we're compiling pure-Thumb so this is mostly passive.
- **`-Wno-unused-parameter -Wno-unused-function`**: the recovered C
  has stub functions with unused parameters. As recovery matures, these
  warnings should reduce.

**Why these flags probably aren't enough to byte-match.** The original
was built with a different compiler (Nintendo uses a customized ARM
C/C++ compiler, not stock gcc). Even with matching flags, instruction
selection, register allocation, and stack-frame layout differ. Realistic
expectation: byte-matching will be partial at first, and Round 4 closes
gaps by:

1. Matching register allocation per-function (sometimes a manual
   register-binding hint fixes things).
2. Tuning compiler flags further.
3. As a last resort, hand-written Thumb-2 assembly for the
   one or two functions gcc gets in a different order from the
   original.

## Pad-byte decision

`tools/rebuild_cro.py` uses **`0xCC`** to pad the rebuilt `.text` if the
compiled output is shorter than the original. This matches what gcc emits
in uninitialised static data and in `.bss` tails on the platforms we
control. If round-4 byte diffs show pad-byte mismatches in a specific
module, the constant is one line away to change (`0xCC` can be flipped to
`0x00`, `0xFF`, or arbitrary per-module).

## What's NOT in this round (and why)

- **CCI stitching.** Takes the original `.cci`, replaces some bytes,
  recomputes hashes for sections that changed, writes a new NCCH with
  placeholder signatures. Necessary for actually booting the rebuild on
  emulator/CFW, but doesn't add verification value beyond what
  `cro_byte_diff.py` already gives — both check bytes against the
  original. Defer.
- **Dev signer.** Tied to the 3DS dev program; out of scope. See
  `docs/cci-byte-matching.md`.
- **Whole-CRO rewrite.** When we have enough recovered C with real
  bodies (post-Round-4), we can write a CRO from scratch using
  `tools/cro_info.py` (already parses) plus a small linker that fills
  in segment/exports/imports. That replaces the patcher. Trivial to
  swap into `tools/rebuild_cro.py` when the time comes.

## Per-function byte-diff reading guide

When Round 4 starts producing code, the SHA-mismatch table from
`make byte-diff` becomes a per-function punch list:

```
 7 0x07a4 0x004c c0a52dd547c18228 a0920a708fa193cc    0        DIVERGE
```

The columns are `idx`, original function offset, byte size, original
SHA, rebuilt SHA, first-divergence byte, status. Reading the SHA
collision that this row expresses, the most actionable interpretation
is:

> *Function at offset 0x7a4 (size 0x4c) disagrees with our rebuild
> starting at byte 0 of that function.*

A Round-4 worker should:
1. Read `src/<stem>_recovered.c` around the function whose name maps
   to 0x7a4 (the function-catalog row gives the *prologue bytes*,
   which usually identifies it).
2. Disassemble the original bytes at offset 0x7a4 with
   `make asmdiff MODULE=<stem> OFFSET=0x7a4 SIZE=0x4c`.
3. Compare its recovered C with the disassembly.
4. Rewrite the body to match and re-run `make rebuild` + `make byte-diff`.

The compound cycle — function-byte-diff → asmdiff → C-edit → rebuild →
byte-diff — is the actual unit of work, and it's all scriptable from
the Makefile now.

## What's the right next step

`make byte-diff MODULE=DllDialogCommon` showed all 18 functions diverge,
because every recovered function in `dialog_common_recovered.c` is a
stub. To see *any* match, a Round-4 worker would have to produce real
recovered C bodies for one function at a time, and the byte-diff
becomes their feedback loop. That's the plan for Round 4 — *not*
building more verification infrastructure, but feeding the existing
infrastructure dense C source and watching the match count rise from
0 toward 13,554.
