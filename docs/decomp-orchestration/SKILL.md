---
name: decomp-orchestration
description: Run coordinated multi-agent reverse-engineering campaigns against large binary titles (3DS, GBA, NDS, Switch, firmware blobs). Use when decompiling a project that has more code than can fit in a single model context — typically 1+ MiB of ARM/Thumb or PowerPC, with dozens-to-hundreds of code modules. Covers substrate pre-computation, agent slicing, per-agent brief templates, verification gates, branch isolation, and round-by-round iteration. Skip for small (under 100 KiB) or already-decoded binaries.
metadata:
  version: "1"
  scope: "binary decomp, multi-agent orchestration"
  worked_example: "Pokemon X (3DS) Round 1, 2026-10-11"
---

# Decomp-orchestration

A reusable playbook for running an LLM-driven reverse-engineering campaign against a
large binary title. The trick: don't let any single agent see more than it can ground
itself against. Build the *substrate* in the parent, slice work into bounded chunks,
lock down what each agent can touch, and gate acceptance on independent checks.

The principles below were learned from one full round on Pokémon X (3DS, 134 modules,
~5.8 MiB of mixed ARM/Thumb C++); the worked example at the end shows them applied.

---

## 1. Decide what is *your* job, not the agents'

Before launching any subagent, the parent must own these. Each is cheap (seconds to
minutes) and unblocks every worker downstream.

| Step | Why the parent owns it |
|---|---|
| Module inventory + classification (size, kind, category) | Lets you size slices honestly. |
| Header / segment / count dump per module | Workers waste turns rediscovering facts already in the binary. |
| Import table + external patch dump per module | Same as above, plus patches are the only way to resolve anonymous imports. |
| Symbol-export map per module | Every worker needs `nnroControlObject_` and friends in front of them. |
| Disassembly (ARM + Thumb) | Workers cannot reasonably call `objdump` over and over. |
| Function-prologue catalog | **Critical**: this is the per-function slice primitive. |

A working pattern from Pokémon X:

```
tools/per_module_metadata.py   # writes work/modules/, docs/symbols/
tools/disassemble_cro.py       # writes work/disassembly/*.text.bin + .arm.asm/.thumb.asm
tools/function_catalog.py      # writes work/functions/*.functions.tsv
```

`function_catalog.py` emits a TSV per module: `(offset, size, mode, prologue_size,
role, prologue)`. Total: one row per `push {…, lr}`. For 5.8 MiB of code, expect
10k–20k rows. This catalog is what Round-2 agents dispatch on.

**Rule of thumb:** if the substrate is re-derivable from the binary, do not ask any
agent to maintain it. Substrate files are immutable from the workers' perspective.

---

## 2. The 12 lessons from Round 1 (read before Round 2)

### What worked

1. **Substrate-first.** Pre-computing all metadata, symbol maps, and disassembly let
   each agent start at *decomp* rather than *parse*. Wall-clock and per-agent
   context both shrank.
2. **Templated worker briefs.** A shared "your assignment is N modules … emit this
   exact `## Report` block" template produced uniform, parseable reports. No agent
   invented its own format.
3. **Forbidden file list in every brief.** "Do NOT modify extracted/, work/disassembly/,
   docs/symbols/, or src/dialog_common_recovered.c" + `git status` verification
   made accidents rare and detectable.
4. **Per-module `gcc -fsyntax-only` as cheap gate.** 90 %+ pass rate without anyone
   reading the content. Frees the orchestrator to spot-check samples, not rows.
5. **Workers' tools stayed narrow.** Use existing tools (`cro_info.py`,
   `module_info.py`, `export_symbols.py`) instead of having agents write new tooling.
   Tooling churn is the worst thing you can let a worker do.
6. **Cross-validation.** Two or three agents independently flagging the same bug
   (the `-Mforce-thumb` disaster here) is a free reliability signal. If one agent
   says "this looks wrong" and another independently agrees, fix it; if only one
   agent says so, defer.
7. **Pre-existing files are sacred.** `git log` + md5 of the reference
   `dialog_common_recovered.c` was checked by worker 3 — and re-checked by me. Two
   layers of defense against worker overwrites.
8. **Brief-enforced report schema.** `## Report` heading + table with named columns
   + cross-cutting findings + blockers. The schema is what enables automated
   acceptance.

### What didn't work (and how to fix in Round 2)

| Failure | Root cause | Round-2 fix |
|---|---|---|
| Function bodies defaulted to `(void)self; return 0;` stubs across modules. | Per-agent context was bigger than the agent's actual decomp capacity. The agent enumerated prologues honestly and then ran out of energy. | **Per-function scope.** A worker gets 2–4 specific functions from the catalog, not a whole module. |
| No automated gate against shallow fabrication. | I had a `gcc` syntax gate but not a *content* gate — `return 0;` parses cleanly. | **Anti-fabrication gate:** each appended function must contain at least one branch / load / call beyond the prologue, else flagged. |
| Mid-round discovery of a tooling bug. | Disassembly pipeline was wrong from day 1 but the orchestrator (me) hadn't noticed. | **Pre-flight substrate audit before launching a round:** parent runs the substrate end-to-end on a sample and visually inspects output. |
| 13 of 133 source files failed gcc due to forward typedef slips. | Worker template didn't anticipate parameter-type declarations ahead of the struct. | **Encoding pattern in the brief:** "always write `typedef struct X X;` immediately after the struct definition." Add this to a generic brief template. |
| Workers re-ran tools inconsistently. | Some called `arm-none-eabi-objdump` directly, others used the helper script. | **One tool, one path.** Document it; workers use the documented interface only. |
| Mixed output quality. Worker 1's tiny modules were byte-identical-validated; Workers 5/11 produced shallow stubs. | Slice was *uniform* (12 modules per agent) regardless of difficulty. Easy and hard got the same budget. | **Difficulty-weighted slices.** Tiny modules get bigger slices; massive modules (DllField, DllBattle) get dedicated agents. |
| No branch isolation. All 12 agents wrote to `main`. | I forgot to provision worktrees. | **One worktree per worker.** Mandatory. Orchestrator merges or discards after the gate. |
| Late notification aggregation. Some workers wrote all files before sending their completion ping; some sent the ping sooner. | The skill docs say "do not poll" — so I didn't, but I also had no visible progress signal. | **`## Progress` block optional at intervals**, mandatory at end. Plus a per-module `wc -l` so file growth is visible even mid-run. |
| The user had to interrupt to redirect. | I should have foreseen: 12 modules × 12-agent batch was always going to be too coarse for *real* decomp. The brief template's pattern matched the brief but not the goal. | **Default to per-function scope** unless the user explicitly asks for module-level. |

### What changed structurally going into Round 2

1. **Per-function scope is the default.** Module-level is reserved for inventory work
   or when a module has too few functions to slice (≤ 10 prologues).
2. **Worktree per agent.** Each worker gets `git worktree add agents/<worker-id>`
   and writes there. Orchestrator reviews the diff before merging.
3. **Pre-flight gate before launching.** Run the entire substrate pipeline on
   a 5-module sample; spot-check the output. *Then* dispatch.
4. **Brief template encodes the anti-pattern guardrails.** Three things every worker
   brief now mandates: the `## Report` schema, the file-existence proof, and a
   `gcc -fsyntax-only` line in `commandsRun`.
5. **Static analysis tools get a vendored `stdint.h`.** Workers were losing cycles
   to "no stdint.h on include path" complaints; provide a stub header.
6. **A "current round" doc** (`docs/decomp-round-N.md`) is the orchestrator's
   running report. Each worker brief points at it.
7. **Worker counter on file output.** Each worker's output must include a literal
   `## Worker counter: <id>` line so we can attribute completion to one agent.
   Mitigation for the late-ping problem.

---

## 3. The wave template (reusable)

This is the rhythm. Each "round" goes:

```
Pre-flight:   parent computes the substrate, audits it, runs `make check`.
Brief drafting: parent groups modules (or function-catalog rows) into workers.
               Append per-agent brief files; do not inline in the dispatch.
Dispatch:     fan out via subagent({...}) async — up to 12 simultaneous
               is comfortable; >20 strains context.
Acceptance:   parent runs the verification gate on every worker's output.
Merge:        parent merges or discards per-worker worktrees/branches.
Doc:          parent updates docs/decomp-round-N.md.
Iterate:      parent edits THIS skill file with new lessons.
```

### Sizing rules

| Bucket | Size | Recommended slice |
|---|---|---|
| Tiny (< 8 KiB code, no imports) | single simple function | 20–40 modules per agent |
| Small (8–32 KiB code) | handful of related functions | 8–15 modules per agent |
| Medium (32–128 KiB code) | full module behavior | 4–8 modules per agent, **or** per-function if function count is > 50 |
| Large (128 KiB–1 MiB code) | substantial | dedicated single-module worker, **structure-only** (header + imports + named exports + spot-check 2–3 prologues) |
| Huge (> 1 MiB code) | usually the gameplay engine | dedicated single-module worker + per-function drilldown afterwards |

When in doubt, **err small**. A worker that produces 5 functions done well is more
useful than a worker that produces 50 functions done superficially.

---

## 4. Per-agent brief — the canonical skeleton

This is what every worker reads. Adapt the bracketed fields per agent.

```text
You are [worker-name] for [project-name] decomp.
Working directory: [absolute cwd]
Substrate was prepared by the orchestrator; do NOT regenerate it.

## Your assignment ([N] [units])
[list of modules / function-catalog entries]

## What you produce
For EACH [unit] above, write [output file]. Document [exports], [boundaries],
[data layout]. NOT a byte-matching build. Mark anything unresolved with
`/* TODO: not yet decoded */`.

Reference style: [path to existing exemplar].

## Shared substrate (read these, don't modify)
[list of paths the worker is allowed to read — usually 5–15 files]

## Anti-patterns (MUST READ)
- Do NOT modify [immutable paths list].
- Do NOT run [tools the orchestrator already ran].
- Do NOT claim byte-matching equivalence.
- Do NOT invent constants / strings / bodies not grounded in disassembly.
- Do NOT skip units. Process all of them.

## Required output

### Function / module body
[template guidance + a 5-line example]

### Mandatory report block (must appear at the end of your reply)

```
## Report

## Worker counter: [worker-id]

### Per-[unit] results
| [unit] | [output path] | lines | functions | known unknowns | est. to byte-match |
|---|---:|---:|---:|---:|---|
| ... | ... | ? | ? | ? | ? |

### Commands run (paste verbatim, with results)
- `<command>` → `<result>`
- ...

### Cross-cutting findings
- ...

### Blockers for byte-match
- ...
```

The orchestrator parses this block. Without it, the work is incomplete.
```

The `commandsRun` array (raw + result) is a quiet but powerful gate: it forces the
worker to actually execute and report what happened, not just describe what they
think happened.

### Brief checklist (parent must verify before dispatch)

- [ ] `## Anti-patterns` lists *every* immutable path.
- [ ] Substrate paths the worker should READ are listed (no unlisted file reads).
- [ ] Required output format is shown, with the `## Report` schema explicit.
- [ ] The worker has explicit permission to write ONLY in `src/` (or wherever).
- [ ] Brief is sized so the worker's context budget isn't exceeded.
      Heuristic: total substrate bytes read should be < 10 % of context.

---

## 5. Verification gate (run after every wave)

The orchestrator runs this script (or its equivalent) per worker:

```sh
worker=$1
# 1. Confirm files exist
test -f src/${worker}_recovered.c || { echo MISSING; exit 1; }
# 2. Compile-clean
gcc -Wall -Wextra -fsyntax-only -x c src/${worker}_recovered.c \
  || { echo BADCOMPILE; exit 1; }
# 3. Protected files unchanged
md5sum -c protected.md5 || { echo PROTECTEDCHANGED; exit 1; }
# 4. Report block present
grep -q '^## Report$' src/${worker}_recovered.c.../report.md \
  || { echo NOREPORT; exit 1; }
# 5. Functions-per-file > 0 (no fully empty stubs)
grep -c '^static int\|^static void\|^static uint32_t' \
   src/${worker}_recovered.c | grep -q '^0$' \
   && { echo NOFUNCTIONS; exit 1; }
```

A `tools/check_round.sh` that takes a manifest of expected files and runs these
checks in batch is the right shape. Build it BEFORE Round 2.

For per-function (Round 2) the gate looks slightly different: each appended
function must compile, and a stub-fabrication heuristic (no body beyond the
prologue / `return 0`) is an automatic retry trigger.

---

## 6. Branch strategy

Three classes of branches live at all times:

```
main                              # stable; only orchestrator merges here
agents/<id>                       # one per dispatched worker; orchestrator-owned
rollups/round-<N>                 # one per round; merged at end of round
```

A worker is dispatched with:

```sh
git worktree add -b agents/<id> /tmp/wt-<id> main
```

The worker writes only inside `/tmp/wt-<id>`. When the worker reports back, the
orchestrator runs the verification gate against the worktree. If it passes,
merge with `--no-ff` to `rollups/round-<N>`; if it fails, drop the worktree.

After all workers are merged into `rollups/round-<N>`, the orchestrator does a
final round-level smoke test (full `gcc` of all generated files; git diff on
key invariants; a manual sample audit) and merges to `main`.

**Worktree overhead for small workers:** negligible. The win is that a misbehaving
worker literally cannot corrupt `main`; rollback is `git branch -D agents/<id>`.

---

## 7. Anti-fabrication (replaces "good output")

The most insidious failure mode is *looks-valid-but-empty*. A worker writes
`static int foo(void) { return 0; }` for every function and gets away with it
because it's syntactically correct.

Plausible detection:

1. **No body beyond the prologue.** Every function body should contain
   - at least one branch (`if`/`?:`/`goto`/`while`/`for`)
   - or at least one load (`ldr`-equivalent field access),
   - or at least one call,
   - unless the function is provably a noop (matches specific binary patterns).
2. **Length heuristic.** A function stub > 5 bytes of body without a control-
   flow statement is rejected. (Calibrate against the survivors.)
3. **No ascii-monoculture.** Recovery files that are mostly "TODO" and `\t`
   are flagged.
4. **Per-function recompile gate after every append.** The Round-2 worker
   must recompile the module's `_recovered.c` after each function append; if
   it breaks, that append is reverted.

The orchestrator can implement (1) and (3) trivially; (2) and (4) require the
worker to participate — but a tight loop ("you wrote a stub, fix it") reduces
drift dramatically.

---

## 8. Iteration log

Each completed round, the orchestrator appends a section here with:
- what was tried differently
- what worked and what didn't
- new fixes merged in

### Round 1 — Pokémon X (2026-10-11)

**Tried**: 12 workers × 12 modules each, all in parallel, module-level scope.

**Won**:
- 133 / 133 modules covered with a `_recovered.c` file.
- All 133 pass `gcc -fsyntax-only`.
- Disassembly bug caught and fixed mid-round.
- Cross-agent finding convergence on `nnroControlObject_` and
  `xy_system::bg::System::SetIsCallDraw` patterns.
- ~32k lines / 13.5k function prologues laid down.

**Lost**:
- Module-level scope was too coarse — most bodies stubbed.
- No worktrees, all workers wrote to `main`.
- Late notification aggregation hid real progress.
- 13 gcc failures fixed manually post-hoc (forward typedef + array bound).
- `gcc` was a *syntax* gate only, not a content gate.

**Net delta for Round 2**:
- Switch default scope to per-function.
- Workers run in `git worktree` per-agent branches.
- Build `tools/check_round.sh` before launching.
- Anti-fabrication gate added (no-body and length heuristic).
- Mandatory `## Worker counter` line in reports.
- A vendored `stdint.h` so `gcc -fsyntax-only` doesn't complain about the path.
- Bigger agents for tiny modules, per-function agents for medium/large, dedicated
  structure-only agents for huge (DllField, DllBattle, DllKawaigari).

---

## 9. Worked example — Round 1 on Pokémon X

| Phase | Action | Wall time | Output |
|---|---|---|---|
| Inventory | `tools/module_info.py` | 1 s | `docs/modules.md` (134 modules) |
| Substrate (per-module) | `tools/per_module_metadata.py` | < 1 s | `docs/symbols/*.map` (133), `work/modules/*.info.md/.imports.md/.patches.md` (399) |
| Substrate (per-binary) | `tools/disassemble_cro.py` × 133 | 10 s (after fix) | `work/disassembly/*.{text.bin,arm.asm,thumb.asm,meta}` (532) |
| Function catalog | `tools/function_catalog.py` | 3 s | `work/functions/*.functions.tsv` (133, 13,554 prologues total) |
| Brief generation | `tools/worker_brief.py` | < 1 s | `/tmp/wbriefs/w1..w12.md` |
| Dispatch | `subagent({async, agent:"worker", task: <brief>})` × 12 | fan-out | 12 running |
| Worker work | (model) | varies | `src/<stem>_recovered.c` × 133 |
| Verification | `git status` + md5 + `gcc -fsyntax-only` | ~10 s | trust-but-verify gate |
| Patch | inline typedef fix script | < 1 s | 133 / 133 pass |
| Doc | `docs/decomp-round-1.md` + `docs/progress.md` | < 1 s | human summary |

Total wall-clock (model time excluded): under 1 minute for substrate + verification,
plus worker time. Round 2 will reuse this phase shape.

---

## 10. Don'ts (recap)

- Do NOT let a worker write a new tool. The orchestrator writes tools.
- Do NOT let two workers touch overlapping modules. Module-level overlap =
  lost-write race; per-function overlap should use disjoint catalog slices.
- Do NOT accept a worker report without verifying the `## Report` block
  parses AND the `commandsRun` rows are believable (no `success` for a
  syntax-only pass that has warnings, etc.).
- Do NOT re-run substrate from inside a worker.
- Do NOT keep dispatching without backpressure. If three agents fail the gate
  in a row, fix the brief template before launching the next round.

---

## 11. Acceptance criteria for THIS skill

This skill is "working" if:
- A second binary-decomp campaign (any title, ≥ 30 modules) can reproduce
  the substrate + wave + gate + branch-isolation flow described above
  using only what is written here.
- After the campaign, a new entry is added to the iteration log.

The orchestrator edits this file after every round. The file should get longer
and clearer over time, not shorter.

---

## 12. Round-2 lessons — Pokémon X (2026-10-11, build & verify)

Two new tools and a new honesty floor landed this round.

### What landed

- `tools/inventory_verify.py` — `sha256sum -c`-equivalent for the
  substrate. Catches extracted/ corruption before any build runs.
- `tools/asmdiff_cro.py` — `pret/asmdiff.sh` equivalent, but structural
  (block/branch/call counts) rather than byte-exact. Per-function.
- `make compare` and `make asmdiff` targets in the Makefile.
- `rom.sha256` — the canonical manifest of every file under
  `extracted/`, analogous to `pret/pokeemerald`'s `rom.sha1`. 657 entries.
- `docs/cci-byte-matching.md` — honest write-up of why a full-CCI byte
  match is impossible without Nintendo's signing key, and what we can
  match instead.

### Why this round felt different

Pret's `make compare` works because GBA ROMs have no signature. For a
3DS title, **the surrounding NCSD/NCCH container is RSA-signed**. We
*cannot* produce a byte-identical `.cci` without the (Nintendo-held,
private, never-leaked) signing key. Pret got away without thinking
about this; we have to think about it on day one.

The honest equivalent for us has two layers:

1. **Component SHA-256** of every file under `extracted/`. Today this
   trivially passes (we've never modified the substrate). For Round 3+
   when a CRO build pipeline exists, this check becomes meaningful: a
   rebuilt `.cro` whose contents hash identically to the original is
   the win criterion.

2. **Per-function structural diff.** For any function in our catalog,
   we can dump the original disassembly and the recovered C, count the
   basic-block and branch shape, and report a gap. Once a CRO build
   pipeline exists, this tool's `--rebuilt` mode can produce a real
   byte diff.

### What we still don't have (Round 3 backlog)

- **CRO build pipeline.** The "linker script" originally requested
  would assemble `src/<stem>_recovered.c` into a CRO file that the
  loader would accept. This requires:
  - An ABI baseline (the 3DS / nnRuntime C ABI), since our function
    calls need to hit the right vtables / register conventions.
  - A compiler invocation that produces CRO-format object files.
  - A linker that lays out the assembled object into a valid CRO
    with the loader's section table populated correctly.
- **Stitcher.** A tool that takes the original `.cci`, swaps in any
  CROs we have rebuilt, recomputes SHA-256 for sections that changed,
  and writes a new NCCH with placeholder signatures. Bytes won't
  match the original but every *intermediate* SHA we can match, will.
- **Dev signer.** Out of scope for a community decomp. A developer
  with a 3DS dev kit can sign the rebuilt CCI with their legitimate
  dev key. We don't and shouldn't do that.

### New gate pattern

```
make compare              # substrate integrity (always)
make asmdiff MODULE=...   # per-function structural diff
                          # (use during development on one function at a time)
```

CI runs `make compare` on every PR. A PR that fails `make compare` is
suspect: someone has modified the inputs to the decomp, or someone
needs to regenerate `rom.sha256`.

### What changed in the skill because of this round

- §5 (verification gate) now references `inventory_verify` and
  `asmdiff_cro`.
- §6 (branch strategy) is unchanged — worktrees still apply.
- §9 (worked example) shows the new tools by name.
- §10 (don'ts) gained: "don't promise byte-matching the surrounding
  container when the format is signed."
