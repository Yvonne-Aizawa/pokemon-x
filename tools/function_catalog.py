#!/usr/bin/env python3
"""Catalog every function boundary in a CRO's disassembly.

A "function boundary" is a Thumb/ARM prologue — `push {<regs>, lr}` followed
by an epilogue — plus the loader veneer branch targets. We detect
prologues and emit a tab-separated file:

  work/functions/<stem>.functions.tsv

Columns: offset, size, prologue, prologue_size, candidate_role

offset         : byte offset inside the .text segment (= file offset - code_offset)
size           : bytes until next function (or end of segment)
prologue       : text of the prologue instruction
prologue_size  : 2 for Thumb, 4 for ARM
candidate_role : heuristic role (loader / lifecycle / event / unknown)

The catalog is the input for per-function workers in the next campaign.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DIS = ROOT / "work" / "disassembly"
OUT = ROOT / "work" / "functions"


# Match "   1ac:  push {r4, lr}"  (4-hex Thumb or 8-hex ARM)
PROLOGUE_RE = re.compile(
    r"^\s*(?P<off>[0-9a-f]+):\s+(?P<size>[0-9a-f]+)\s+(?P<text>\S+.*)$"
)
ARM_PUSH_RE = re.compile(r"\bpush\s*\{[^}]*lr[^}]*\}")
THUMB_PUSH_RE = re.compile(r"\b(?:push|PUSH)\s*\{[^}]*\b(?:r7|lr|pc)\b[^}]*\}")


def is_prologue(text: str, insn_word: str) -> tuple[bool, str, int]:
    """Return (is_prologue, mode, prologue_size)."""
    if ARM_PUSH_RE.search(text):
        return True, "arm", 4
    if THUMB_PUSH_RE.search(text) and len(insn_word) == 4:
        # Thumb push is encoded in a 2-byte or 4-byte insn; for our objdump
        # output the 4-hex-digit insn means Thumb-2 (32-bit) push.
        return True, "thumb", 4
    if THUMB_PUSH_RE.search(text) and len(insn_word) == 2:
        return True, "thumb", 2
    return False, "", 0


def parse_disassembly(text: str) -> list[tuple[int, str, str]]:
    """Return [(offset, insn_bytes, asm_text), ...]."""
    rows = []
    for line in text.splitlines():
        m = PROLOGUE_RE.match(line)
        if m:
            off = int(m["off"], 16)
            insn = m["size"]
            tail = m["text"].strip()
            rows.append((off, insn, tail))
    return rows


def candidate_role(stem: str, off: int, all_offsets: list[int], insn_text: str) -> str:
    """Heuristic. Many specifics come from worker reports; keep conservative."""
    if off < 0x20:
        return "loader_control_entry"
    if 0x40 < off < 0x250:
        # Most CROs have their loader nnroControlObject_ body near 0x180..0x250
        return "loader_dispatch"
    if "r3, r4, r5, r6" in insn_text or "r4, r5, r6, r7" in insn_text:
        return "lifecycle_or_event"
    return "unknown"


def catalog_module(stem: str, dis_dir: Path, out_dir: Path) -> Path | None:
    arm_asm = dis_dir / f"{stem}.arm.asm"
    if not arm_asm.is_file():
        return None
    rows = parse_disassembly(arm_asm.read_text(encoding="utf-8", errors="replace"))

    # We want prologues specifically.
    prologues = []
    for off, insn, text in rows:
        is_p, mode, psz = is_prologue(text, insn)
        if is_p:
            prologues.append((off, mode, psz, text))

    # Compute gap to next prologue as approximate size
    prologues.sort(key=lambda x: x[0])
    all_offsets = [p[0] for p in prologues]
    out_rows = []
    for i, (off, mode, psz, text) in enumerate(prologues):
        next_off = prologues[i + 1][0] if i + 1 < len(prologues) else off + 0x100
        size = max(next_off - off, psz)
        role = candidate_role(stem, off, all_offsets, text)
        out_rows.append((off, size, mode, psz, role, text))

    out = out_dir / f"{stem}.functions.tsv"
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8") as fh:
        fh.write("offset\tsize\tmode\tprologue_size\trole\tprologue\n")
        for off, size, mode, psz, role, text in out_rows:
            fh.write(f"0x{off:x}\t0x{size:x}\t{mode}\t{psz}\t{role}\t{text}\n")
    return out


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--modules", nargs="*", help="specific module stems")
    args = parser.parse_args()

    if args.modules:
        stems = args.modules
    else:
        stems = sorted(p.stem.replace(".text", "") for p in DIS.glob("*.text.bin"))
        stems = sorted(set(stems))

    written = 0
    total_funcs = 0
    for stem in stems:
        out = catalog_module(stem, DIS, OUT)
        if out:
            written += 1
            with out.open() as f:
                total_funcs += sum(1 for _ in f) - 1  # minus header
    print(f"cataloged {written} modules; {total_funcs} function prologues total")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
