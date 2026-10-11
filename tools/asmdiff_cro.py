#!/usr/bin/env python3
"""Compare a recovered C function against the original binary's disassembly.

This is the per-function verification tool — the equivalent of
pret/pokeemerald's `asmdiff.sh`. Where pret diffs *byte-for-byte* between
original and rebuilt ROMs, we diff *structurally*: does the recovered C
function's basic-block / branch / call / return topology match the original
binary function's disassembly?

Why not byte-for-byte? See docs/cci-byte-matching.md. Until we have a build
pipeline that can recompile our C source into a CRO that re-stitches into the
signed CCI container, the most we can compare is structural shape. Once that
pipeline exists, this tool gains a `--rebuilt` mode that does the real diff.

Usage examples:

    # Structural diff against original disassembly:
    python3 tools/asmdiff_cro.py DllDialogCommon 0x2d8 0x4c \\
        --recovered src/dialog_common_recovered.c

    # Just dump the original disassembly:
    python3 tools/asmdiff_cro.py DllDialogCommon 0x2d8 0x4c

    # Catalogue a whole module and dump every identified function:
    python3 tools/asmdiff_cro.py DllDialogCommon --list
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path
from typing import Iterable

ROOT = Path(__file__).resolve().parents[1]

# Cycle counts per instruction class. Weights are coarse but informative; they
# let the structural-score show e.g. how many branches a function has without
# caring exactly which.
COND_BRANCH = re.compile(r"\b(?:beq|bne|blt|bgt|ble|bge|bcs|bcc|bhi|bls|ble|bge|cmp)\b.*?$", re.IGNORECASE)
UNCOND_BRANCH = re.compile(r"\b(?:b\.n|b\.|b\s|bl\b|bx\b)\b")
COND_BR_INSN = re.compile(r"^(?:\s*\d+:)?\s*(?:[0-9a-f]+\s+)?(?:b\.[a-z]+|cb[nz])\b")
RET_INSN = re.compile(r"^\s*[\da-f]+:\s+(?:pop\s*\{.*pc\}|bx\s+lr)\b")
PUSH_INSN = re.compile(r"^\s*[\da-f]+:\s+(?:push\s*\{.*lr.*\}|PUSH\s*\{.*lr.*\})", re.IGNORECASE)
LDR_LITERAL = re.compile(r"^\s*[\da-f]+:\s+ldr\s+r", re.IGNORECASE)
BL_INSN = re.compile(r"^\s*[\da-f]+:\s+(?:bl|b\.|blx)\b")


def disasm_range(cro_path: Path, code_offset: int, fn_offset: int, fn_size: int) -> str:
    """Disassemble the [fn_offset, fn_offset+fn_size) range of a CRO's segment 0.

    Mirrors tools/disassemble_cro.py but for an offset range, returned to stdout.
    """
    if not cro_path.is_file():
        raise FileNotFoundError(cro_path)
    data = cro_path.read_bytes()
    abs_off = code_offset + fn_offset
    blob = data[abs_off:abs_off + fn_size]
    # objdump from stdin
    import tempfile
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as tmp:
        tmp.write(blob)
        tmp_path = Path(tmp.name)
    try:
        res = subprocess.run(
            [
                "arm-none-eabi-objdump",
                "-D",
                "-b", "binary",
                "-m", "arm",
                f"--adjust-vma=0x{abs_off:x}",
                "--no-show-raw-insn",
                str(tmp_path),
            ],
            capture_output=True, text=True, check=True,
        )
        return res.stdout
    finally:
        tmp_path.unlink(missing_ok=True)


def original_features(text: str) -> dict[str, object]:
    """Extract structural features from disassembly listing."""
    lines = text.splitlines()
    pushes = sum(1 for l in lines if PUSH_INSN.match(l))
    rets = sum(1 for l in lines if RET_INSN.match(l))
    cond_br = sum(1 for l in lines if COND_BR_INSN.match(l))
    uncond_br = sum(1 for l in lines if UNCOND_BRANCH.search(l)) - cond_br
    ldrs = sum(1 for l in lines if LDR_LITERAL.match(l))
    bls = sum(1 for l in lines if BL_INSN.match(l))
    return {
        "push": pushes,
        "ret": rets,
        "cond_branch": cond_br,
        "uncond_branch": max(uncond_br, 0),
        "ldr_literal": ldrs,
        "bl": bls,
        "lines": len([l for l in lines if l.strip()]),
    }


def recovered_features(src_path: Path, fn_name: str) -> dict[str, object] | None:
    """Heuristically extract structural features from a recovered C function."""
    if not src_path.is_file():
        return None
    text = src_path.read_text(encoding="utf-8", errors="replace")
    # Find a function whose name matches fn_name (or contains it)
    pat = re.compile(
        r"^(?:static\s+)?(?:[\w\s\*]+?\s+)?(?P<name>\w+)\s*\([^)]*\)\s*\{(?P<body>.*?)^\}",
        re.DOTALL | re.MULTILINE,
    )
    body = None
    for m in pat.finditer(text):
        if fn_name in m.group("name"):
            body = m.group("body")
            break
    if body is None:
        return None
    # Strip /* ... */ blocks
    body = re.sub(r"/\*.*?\*/", "", body, flags=re.DOTALL)
    body = re.sub(r"//[^\n]*\n", "\n", body)
    lines = [l for l in body.splitlines() if l.strip()]
    return {
        "if": sum(1 for l in lines if re.search(r"\bif\s*\(", l)),
        "while": sum(1 for l in lines if re.search(r"\bwhile\s*\(", l)),
        "for": sum(1 for l in lines if re.search(r"\bfor\s*\(", l)),
        "switch": sum(1 for l in lines if re.search(r"\bswitch\s*\(", l)),
        "case": sum(1 for l in lines if re.search(r"\bcase\s+", l)),
        "return": sum(1 for l in lines if re.search(r"\breturn\b", l)),
        "call": sum(1 for l in lines if re.search(r"\b\w+\s*\(", l)),
        "lines": len(lines),
    }


def diff(orig: dict, recv: dict) -> Iterable[str]:
    """Yield human-readable comparison rows."""
    yield "feature        | original(asm) | recovered(C) | gap"
    yield "---------------+---------------+--------------+----"
    pairs = [
        ("branch-ish instructions", orig["cond_branch"] + orig["uncond_branch"],
         recv["if"] + recv["while"] + recv["for"] + recv["switch"]),
        ("returns", orig["ret"], recv["return"]),
        ("calls", orig["bl"], recv["call"]),
        ("literal loads", orig["ldr_literal"], "—"),
        ("lines (count)", orig["lines"], recv["lines"]),
    ]
    for label, o, r in pairs:
        if isinstance(o, int) and isinstance(r, int):
            delta = r - o
            sign = f"{delta:+d}" if delta else "="
            yield f"{label:14s} | {o:13d} | {r:12d} | {sign}"
        else:
            yield f"{label:14s} | {o:13} | {r:12} | —"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", help="module stem, e.g. DllDialogCommon")
    parser.add_argument("offset", nargs="?", type=lambda s: int(s, 0),
                        help="function offset within code segment (hex or decimal)")
    parser.add_argument("size", nargs="?", type=lambda s: int(s, 0),
                        help="function size in bytes")
    parser.add_argument("--recovered", type=Path,
                        help="path to the recovered .c file containing this function")
    parser.add_argument("--fn-name", help="function name to search for in --recovered "
                                          "(default: <module>_<offset_hex>)")
    parser.add_argument("--list", action="store_true",
                        help="print the function catalog for this module")
    args = parser.parse_args()

    cro = ROOT / "extracted" / "romfs" / f"{args.module}.cro"
    if not cro.is_file():
        cro = ROOT / "extracted" / "romfs" / f"{args.module}.code"
    if not cro.is_file():
        print(f"not found: {args.module} (.cro or .code)", file=sys.stderr)
        return 2

    code_meta = ROOT / "work" / "modules" / f"{args.module}.info.md"
    code_offset = 0x180
    if code_meta.is_file():
        m = re.search(r"code:\s*offset\s*(0x[0-9a-f]+)\s*size", code_meta.read_text())
        if m:
            code_offset = int(m.group(1), 16)

    if args.list:
        cat = ROOT / "work" / "functions" / f"{args.module}.functions.tsv"
        if cat.is_file():
            print(cat.read_text())
        else:
            print(f"no catalog for {args.module}; run tools/function_catalog.py")
        return 0

    if args.offset is None or args.size is None:
        parser.error("offset and size are required (or use --list)")

    disasm = disasm_range(cro, code_offset, args.offset, args.size)
    orig = original_features(disasm)

    print(f"# {args.module} @ segment-0 offset 0x{args.offset:x}, size 0x{args.size:x}")
    print()
    print(f"## Original disassembly ({orig['lines']} lines)")
    print()
    print("```")
    print(disasm.rstrip())
    print("```")

    recv = None
    if args.recovered:
        fn_name = args.fn_name or f"{args.module}_{args.offset:x}"
        recv = recovered_features(args.recovered, fn_name)

    if recv:
        print()
        print(f"## Recovered C ({args.recovered})")
        print()
        print("```")
        print("```")  # marker — show recovered snippet if available
        # Also print the matched function's body
        text = args.recovered.read_text(encoding="utf-8", errors="replace")
        pat = re.compile(
            r"^(?:static\s+)?(?:[\w\s\*]+?\s+)?(?P<name>\w+)\s*\([^)]*\)\s*\{(?P<body>.*?)^\}",
            re.DOTALL | re.MULTILINE,
        )
        matched = False
        for m in pat.finditer(text):
            if fn_name in m.group("name"):
                print(f"function: {m.group('name')}")
                print("```")
                print("```c")
                print(m.group(0).rstrip())
                print("```")
                matched = True
                break
        if not matched:
            print("```")
            print(f"(function '{fn_name}' not found in {args.recovered})")

        print()
        print("## Structural diff")
        for row in diff(orig, recv):
            print(row)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
