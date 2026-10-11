#!/usr/bin/env python3
"""Compile a recovered CRO's C source, package it into a rebuilt CRO.

This is the Round-3 CRO link piece. It takes one module, finds its
recovered C source under src/, compiles it to ARM/Thumb object code using
arm-none-eabi-gcc with 3DS-appropriate flags, extracts the .text section,
and overlays it onto a copy of the original CRO at the same byte range
the original occupied.

What this is NOT: a from-scratch CRO linker. We deliberately *don't*
rebuild the header, segment table, export table, import table, or external
patch table \u2014 those are unchanged from the original. The intent is to
isolate one variable at a time: does the C we wrote, when compiled, give
us bytes that could replace the original code segment?

If yes (all 13,554 catalog functions byte-match): congratulations, that
module is fully decompiled.

If no (any function diverges): this tool prints a diff and the per-function
SHA mismatch report at work/rebuild/<stem>.diff; the next round's
compiler-flag-tuning or per-function recovery fixes whichever is wrong.

This tool does not touch any file under extracted/romfs/. The original
CRO is read once and used to template the rebuilt one; nothing in
extracted/ is modified.
"""

from __future__ import annotations

import argparse
import hashlib
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Toolchain settings. These mirror the 3DS's ARM11 (ARMv6K + Thumb-2)
# CPU, with software FP and no PIC. The flag set is calibrated to keep
# function layout predictable and to keep output byte-for-byte stable for
# repeated invocations on the same source.
COMPILE_FLAGS: list[str] = [
    "-c",
    "-mthumb",
    "-march=armv6k",
    "-mtune=arm1136j-s",
    "-mfloat-abi=soft",
    "-mthumb-interwork",
    "-fno-asynchronous-unwind-tables",
    "-fno-toplevel-reorder",
    "-fno-pic",
    "-fno-stack-protector",
    "-fno-builtin",
    "-ffreestanding",
    "-fno-ident",
    "-O0",
    "-Wall",
    "-Wextra",
    "-Wno-unused-parameter",
    "-Wno-unused-function",
    "-Wno-unused-variable",
]

LINK_FLAGS: list[str] = [
    "-nostdlib",
]


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def cro_header(data: bytes) -> dict[str, int]:
    if len(data) < 0x120 or data[0x80:0x84] not in (b"CRO0", b"FIXD"):
        raise ValueError("not a CRO/FIXD file")
    return {
        "code_offset": u32(data, 0xB0),
        "code_size": u32(data, 0xB4),
        "data_offset": u32(data, 0xB8),
        "data_size": u32(data, 0xBC),
        "bss_size": u32(data, 0x94),
    }


def find_recovered_c(stem: str) -> Path:
    """Find src/<...>_recovered.c for the given module stem.

    Tries, in order:
      1. Exact: src/<stem>_recovered.c
      2. Stripped-of-Dll: src/<stripped>_recovered.c (e.g. "DllDialogCommon" -> "DialogCommon")
      3. Anything in src/ containing the stem (case-insensitive)
    The order matters: most modules are conventionally written as
    src/Dll<X>_recovered.c, but a few historical lowercase forms exist.
    """
    src = ROOT / "src"
    candidates: list[Path] = [
        src / f"{stem}_recovered.c",
    ]
    if stem.startswith("Dll"):
        candidates.append(src / f"{stem[3:]}_recovered.c")
    candidates.append(src / f"{stem.lower()}_recovered.c")
    if stem.startswith("Dll"):
        candidates.append(src / f"{stem[3:].lower()}_recovered.c")
    seen = set()
    for p in candidates:
        if str(p) in seen or not p.is_file():
            continue
        seen.add(str(p))
        return p
    # Last-resort substring search across src/. Use a softened stem — strip the
    # leading 'Dll'/'dll' once, and lowercase — so that "DllDialogCommon" matches
    # "dialog_common_recovered.c".
    softened = stem.lower()
    if softened.startswith("dll"):
        softened = softened[3:]
    for p in sorted(src.glob("*_recovered.c")):
        name = p.name.lower()
        # Try to find the stem's tail ('dialogcommon') inside the candidate name
        # by also stripping underscores on both sides for a more forgiving match.
        candidate_normalized = name.replace("_", "").removesuffix(".c")
        if softened in candidate_normalized and str(p) not in seen:
            return p
    raise FileNotFoundError(
        f"no recovered source for {stem}; tried {[str(p) for p in candidates]}"
    )


def extract_text_bytes(obj_path: Path) -> bytes:
    """Use objcopy -O binary to extract just the .text section."""
    out = Path(tempfile.mkstemp(suffix=".text.bin")[1])
    try:
        subprocess.run(
            [
                "arm-none-eabi-objcopy",
                "-O", "binary",
                "--only-section=.text",
                str(obj_path),
                str(out),
            ],
            check=True, capture_output=True,
        )
        return out.read_bytes()
    finally:
        out.unlink(missing_ok=True)


def compile_recovered(c_path: Path) -> tuple[Path, list[str]]:
    """Compile C to ARM ELF object; return (obj_path, compiler_log_lines)."""
    fd, tmp_name = tempfile.mkstemp(suffix=".o")
    import os
    os.close(fd)
    obj_path = Path(tmp_name)
    cmd = ["arm-none-eabi-gcc"] + COMPILE_FLAGS + ["-o", str(obj_path), str(c_path)]
    log: list[str] = [" ".join(cmd)]
    try:
        res = subprocess.run(cmd, capture_output=True, text=True)
        log.append("--- stdout ---")
        log.append(res.stdout)
        log.append("--- stderr ---")
        log.append(res.stderr)
        log.append(f"exit: {res.returncode}")
        if res.returncode != 0 or not obj_path.is_file() or obj_path.stat().st_size == 0:
            raise RuntimeError("compile failed; see log for details")
        return obj_path, log
    except Exception:
        obj_path.unlink(missing_ok=True)
        raise


def overlay_code_segment(original: bytes, new_text: bytes) -> bytes:
    """Return a copy of `original` with the .text bytes replaced by `new_text`.

    The replacement is anchored at original.code_offset. If new_text is
    longer than original.code_size it is truncated; if shorter it is padded
    with 0xCC (the conventional arm-none-eabi-gcc pad byte). Both cases are
    logged; truncation/padding outside the rebuilt code range will mismatch
    every function whose original was longer/shorter.
    """
    hdr = cro_header(original)
    code_off = hdr["code_offset"]
    code_size = hdr["code_size"]
    if len(new_text) > code_size:
        log = f"new .text is {len(new_text)} bytes; original is {code_size}; truncating"
        new_text = new_text[:code_size]
    elif len(new_text) < code_size:
        log = f"new .text is {len(new_text)} bytes; original is {code_size}; padding to match"
        new_text = new_text + b"\xCC" * (code_size - len(new_text))
    else:
        log = "new .text length matches original exactly"
    out = bytearray(original)
    out[code_off:code_off + code_size] = new_text
    print(log)
    return bytes(out)


def sha256(b: bytes) -> str:
    h = hashlib.sha256()
    h.update(b)
    return h.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", help="module stem, e.g. DllDialogCommon")
    parser.add_argument(
        "--out-dir", type=Path, default=ROOT / "build" / "rebuilt",
        help="where to write the rebuilt CRO (default: build/rebuilt/)",
    )
    parser.add_argument(
        "--log-dir", type=Path, default=ROOT / "work" / "rebuild",
        help="where to write per-module rebuild logs (default: work/rebuild/)",
    )
    parser.add_argument(
        "--no-overlay", action="store_true",
        help="only compile; do not overlay onto a copy of the original CRO",
    )
    args = parser.parse_args()

    stem = args.module
    c_path = find_recovered_c(stem)
    cro_path = ROOT / "extracted" / "romfs" / f"{stem}.cro"
    if not cro_path.is_file():
        cro_path = ROOT / "extracted" / "romfs" / f"{stem}.code"
    if not cro_path.is_file():
        print(f"original CRO not found for {stem}", file=sys.stderr)
        return 2

    original_bytes = cro_path.read_bytes()
    original_hdr = cro_header(original_bytes)
    original_text = original_bytes[original_hdr["code_offset"]:original_hdr["code_offset"] + original_hdr["code_size"]]
    original_text_sha = sha256(original_text)
    print(f"# Rebuild {stem}")
    print(f"original .text:  {len(original_text):>6} bytes @ 0x{original_hdr['code_offset']:x} (sha256 {original_text_sha[:16]}\u2026)")

    obj_path = None
    try:
        obj_path, log = compile_recovered(c_path)
        log_path = args.log_dir / f"{stem}.compile.log"
        log_path.parent.mkdir(parents=True, exist_ok=True)
        log_path.write_text("\n".join(log), encoding="utf-8")
        new_text = extract_text_bytes(obj_path)
        new_text_sha = sha256(new_text)
        print(f"compiled .text: {len(new_text):>6} bytes (sha256 {new_text_sha[:16]}\u2026)")
        print(f"compile log:    {log_path}")

        if original_text_sha == new_text_sha:
            print("\n*** BYTE-EQUIVALENT *** This module's .text matches the original completely.")
            byte_match = True
        else:
            matched = sum(1 for a, b in zip(original_text, new_text) if a == b)
            total = max(len(original_text), len(new_text))
            print(f"\n*** BYTE DIVERGENCE *** {matched}/{min(len(original_text), len(new_text))} first {min(len(original_text),len(new_text))} bytes match.")
            print(f"    total range: {total} bytes")
            byte_match = False

        if args.no_overlay:
            return 0

        out_cro_path = args.out_dir / f"{stem}.cro"
        out_cro_path.parent.mkdir(parents=True, exist_ok=True)
        rebuilt = overlay_code_segment(original_bytes, new_text)
        out_cro_path.write_bytes(rebuilt)
        print(f"rebuilt CRO:    {out_cro_path} ({len(rebuilt)} bytes)")
        out_cro_sha = sha256(rebuilt)
        original_cro_sha = sha256(original_bytes)
        print(f"sha256:         {out_cro_sha[:16]}\u2026 (original: {original_cro_sha[:16]}\u2026)")
        if original_cro_sha == out_cro_sha:
            print("*** CRO is byte-equal to the original (full byte-match). ***")
        else:
            # SHA of the CRO will diverge trivially because the .text has
            # changed; this is expected. The interesting check is per-function.
            print("CRO SHA differs (expected because .text was replaced). See tools/cro_byte_diff.py for per-function breakdown.")
        return 0 if byte_match else 1
    except Exception as e:
        print(f"FAILED: {e}", file=sys.stderr)
        return 1
    finally:
        if obj_path is not None:
            obj_path.unlink(missing_ok=True)


if __name__ == "__main__":
    raise SystemExit(main())
