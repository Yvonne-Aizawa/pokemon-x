#!/usr/bin/env python3
"""Per-function byte diff between an original CRO and a rebuilt one.

Walks the function catalog at work/functions/<stem>.functions.tsv and
SHA-256-checks each function's byte range in both CROs. Reports matches
and mismatches with a brief diff excerpt.

This is the answer to "did our recovered C, when compiled, produce
bytes that could replace the original code segment?". When *every*
function matches (or every function with non-stub C body), that module
is fully decompiled.

Limitations:
- Currently does not attempt to align functions whose offsets shifted
  in the rebuilt CRO. We compare by *original* function-catalog offset;
  any shift will show up as a cascade of mismatches.
- Functions whose original was larger than the new .text will be
  truncated; the tail is reported as missing.
"""

from __future__ import annotations

import argparse
import hashlib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def u32(data: bytes, off: int) -> int:
    import struct
    return struct.unpack_from("<I", data, off)[0]


def cro_code_range(data: bytes) -> tuple[int, int]:
    if len(data) < 0x120 or data[0x80:0x84] not in (b"CRO0", b"FIXD"):
        raise ValueError("not a CRO/FIXD file")
    return u32(data, 0xB0), u32(data, 0xB4)


def sha256(b: bytes) -> str:
    h = hashlib.sha256()
    h.update(b)
    return h.hexdigest()


def parse_catalog(catalog_path: Path) -> list[tuple[int, int]]:
    out = []
    for line in catalog_path.read_text().splitlines():
        if line.startswith("offset"):
            continue
        m = re.match(r"^0x([0-9a-f]+)\s+0x([0-9a-f]+)", line)
        if m:
            out.append((int(m.group(1), 16), int(m.group(2), 16)))
    return out


def first_diff(a: bytes, b: bytes, limit: int = 16) -> int | None:
    """Index of first byte that differs; None if equal."""
    for i, (xa, xb) in enumerate(zip(a, b)):
        if xa != xb:
            return i
    return None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", help="module stem (e.g. DllDialogCommon)")
    parser.add_argument(
        "--original", type=Path,
        help="path to the original CRO (default: extracted/romfs/<stem>.cro)",
    )
    parser.add_argument(
        "--rebuilt", type=Path, required=True,
        help="path to the rebuilt CRO (e.g. build/rebuilt/<stem>.cro)",
    )
    parser.add_argument(
        "--catalog", type=Path,
        help="function catalog TSV (default: work/functions/<stem>.functions.tsv)",
    )
    args = parser.parse_args()

    stem = args.module
    original_path = args.original or (ROOT / "extracted" / "romfs" / f"{stem}.cro")
    if not original_path.is_file():
        original_path = ROOT / "extracted" / "romfs" / f"{stem}.code"
    rebuilt_path = args.rebuilt
    catalog_path = args.catalog or (ROOT / "work" / "functions" / f"{stem}.functions.tsv")

    if not original_path.is_file():
        print(f"original CRO not found: {original_path}", file=sys.stderr)
        return 2
    if not rebuilt_path.is_file():
        print(f"rebuilt CRO not found: {rebuilt_path}", file=sys.stderr)
        return 2
    if not catalog_path.is_file():
        print(f"catalog not found: {catalog_path}", file=sys.stderr)
        return 2

    original = original_path.read_bytes()
    rebuilt = rebuilt_path.read_bytes()

    o_code_off, o_code_size = cro_code_range(original)
    r_code_off, r_code_size = cro_code_range(rebuilt)

    funcs = parse_catalog(catalog_path)
    if not funcs:
        print(f"no functions in catalog {catalog_path}", file=sys.stderr)
        return 2

    matched = 0
    diverged = 0
    truncated = 0
    print(f"# {stem} per-function byte diff")
    print(f"original: {original_path} (.text 0x{o_code_size:x} bytes @ 0x{o_code_off:x})")
    print(f"rebuilt:  {rebuilt_path} (.text 0x{r_code_size:x} bytes @ 0x{r_code_off:x})")
    print(f"catalog:  {len(funcs)} function entries")
    print()
    print("idx offset size    orig-sha256      rebuilt-sha256   first-diff  status")
    print("--- ------ ------ ---------------- ---------------- ----------- --------")

    for i, (off, size) in enumerate(funcs):
        # All offsets in the catalog are segment-0 offsets (file offset - code_offset)
        o_lo = o_code_off + off
        r_lo = r_code_off + off
        o_seg = original[o_lo:o_lo + size] if o_lo + size <= len(original) else b""
        r_seg = rebuilt[r_lo:r_lo + size] if r_lo + size <= len(rebuilt) else b""
        if len(o_seg) < size:
            status = "TRUNC-ORIG"
            truncated += 1
            continue
        if len(r_seg) < size:
            status = "TRUNC-REBLT"
            truncated += 1
            print(f"{i:3d} 0x{off:04x} 0x{size:04x} {sha256(o_seg)[:16]} {' '*16} \u2014           {status}")
            continue
        o_sha = sha256(o_seg)
        r_sha = sha256(r_seg)
        idx = first_diff(o_seg, r_seg)
        if o_sha == r_sha:
            status = "MATCH"
            matched += 1
            print(f"{i:3d} 0x{off:04x} 0x{size:04x} {o_sha[:16]} {r_sha[:16]} {'\u2014':11s} {status}")
        else:
            status = "DIVERGE"
            diverged += 1
            print(f"{i:3d} 0x{off:04x} 0x{size:04x} {o_sha[:16]} {r_sha[:16]} {idx!s:>4}        {status}")

    print()
    total = len(funcs)
    print(f"summary: {matched}/{total} match  {diverged} diverge  {truncated} truncated")
    if matched == total:
        print("\n*** ALL CATALOG FUNCTIONS BYTE-EQUIVALENT ***")
    return 0 if matched == total else 1


if __name__ == "__main__":
    raise SystemExit(main())
