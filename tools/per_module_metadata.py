#!/usr/bin/env python3
"""Build per-module metadata for every CRO under extracted/romfs/.

For each module we emit:
  work/modules/<name>.info.md     header, segments, counts
  docs/symbols/<name>.map         named exports (uses existing logic)
  work/modules/<name>.imports.md  imported modules + indexed/anonymous heads
  work/modules/<name>.patches.md  external patch table

A master index is written to work/modules_index.tsv.
"""

from __future__ import annotations

import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ROMFS = ROOT / "extracted" / "romfs"
SYMBOLS = ROOT / "docs" / "symbols"
MODULES = ROOT / "work" / "modules"
INDEX = ROOT / "work" / "modules_index.tsv"


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def cstring(data: bytes, off: int) -> str:
    end = data.find(b"\0", off)
    return data[off:end].decode("utf-8", errors="replace") if end >= 0 else ""


def parse_header(path: Path) -> dict | None:
    try:
        data = path.read_bytes()
    except OSError:
        return None
    if len(data) < 0x120 or data[0x80:0x84] not in (b"CRO0", b"FIXD"):
        return None
    seg_table = u32(data, 0xC8)
    seg_count = u32(data, 0xCC)
    code_off = u32(data, 0xB0)
    code_size = u32(data, 0xB4)
    data_off = u32(data, 0xB8)
    data_size = u32(data, 0xBC)
    bss_size = u32(data, 0x94)
    name_off = u32(data, 0xC0)
    name_size = u32(data, 0xC4)
    name = (
        cstring(data, name_off)
        if name_off and name_off + name_size <= len(data)
        else path.stem
    )
    return {
        "path": path,
        "data": data,
        "seg_table": seg_table,
        "seg_count": seg_count,
        "code_off": code_off,
        "code_size": code_size,
        "data_off": data_off,
        "data_size": data_size,
        "bss_size": bss_size,
        "name": name,
        "exports_named": u32(data, 0xD4),
        "exports_indexed": u32(data, 0xDC),
        "imports_module_count": u32(data, 0xF4),
        "patches": u32(data, 0xFC),
    }


def write_info(meta: dict) -> Path:
    """Write work/modules/<name>.info.md using only header data (cheap)."""
    out = MODULES / f"{meta['path'].stem}.info.md"
    out.parent.mkdir(parents=True, exist_ok=True)
    data = meta["data"]
    with out.open("w", encoding="utf-8") as fh:
        fh.write(f"# {meta['path'].name} header\n\n")
        fh.write(f"- module name: `{meta['name']}`\n")
        fh.write(f"- file size: 0x{len(data):x} ({len(data):,})\n")
        fh.write(f"- code: offset 0x{meta['code_off']:x} size 0x{meta['code_size']:x}\n")
        fh.write(f"- data: offset 0x{meta['data_off']:x} size 0x{meta['data_size']:x}\n")
        fh.write(f"- bss size: 0x{meta['bss_size']:x}\n")
        fh.write(f"- segments ({meta['seg_count']}):\n")
        for i in range(min(meta["seg_count"], 64)):
            seg_off = meta["seg_table"] + i * 12
            if seg_off + 12 > len(data):
                break
            off, size, sid = struct.unpack_from("<III", data, seg_off)
            fh.write(f"  - {i}: offset=0x{off:x} size=0x{size:x} id={sid}\n")
        fh.write(f"- exports named: {meta['exports_named']}\n")
        fh.write(f"- exports indexed: {meta['exports_indexed']}\n")
        fh.write(f"- imports module: {meta['imports_module_count']}\n")
        fh.write(f"- external patches: {meta['patches']}\n")
    return out


def write_named_exports(meta: dict) -> Path:
    out = SYMBOLS / f"{meta['path'].stem}.map"
    out.parent.mkdir(parents=True, exist_ok=True)
    data = meta["data"]
    table = u32(data, 0xD0)
    count = meta["exports_named"]
    with out.open("w", encoding="utf-8") as fh:
        fh.write(f"# Exported symbols: {meta['path'].name}\n\n")
        fh.write("| Name | Segment tag | Segment | Offset |\n|---|---:|---:|---:|\n")
        for i in range(count):
            entry = table + i * 8
            name_off = u32(data, entry)
            tag = u32(data, entry + 4)
            if name_off >= len(data):
                continue
            name = cstring(data, name_off)
            fh.write(f"| `{name}` | `0x{tag:08x}` | {tag & 0xF} | `0x{tag >> 4:x}` |\n")
    return out


def write_imports(meta: dict) -> Path | None:
    data = meta["data"]
    table = u32(data, 0xF0)
    count = meta["imports_module_count"]
    strings = u32(data, 0x118)
    if count == 0:
        return None
    out = MODULES / f"{meta['path'].stem}.imports.md"
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8") as fh:
        fh.write(f"# Imports of {meta['path'].name}\n\n")
        fh.write("| index | module | indexed_head | indexed_count | anonymous_head | anonymous_count |\n")
        fh.write("|---:|---|---:|---:|---:|---:|\n")
        for i in range(count):
            entry = table + i * 20
            name_off = u32(data, entry)
            name = cstring(data, name_off) if name_off < len(data) else "?"
            idx_head = u32(data, entry + 4)
            idx_count = u32(data, entry + 8)
            ano_head = u32(data, entry + 12)
            ano_count = u32(data, entry + 16)
            fh.write(
                f"| {i} | `{name}` | 0x{idx_head:x} | {idx_count} | 0x{ano_head:x} | {ano_count} |\n"
            )
        fh.write(f"\nimport string table: 0x{strings:x}\n")
    return out


def write_patches(meta: dict) -> Path | None:
    data = meta["data"]
    if meta["patches"] == 0:
        return None
    table = u32(data, 0xF8)
    count = meta["patches"]
    out = MODULES / f"{meta['path'].stem}.patches.md"
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8") as fh:
        fh.write(f"# External patches of {meta['path'].name}\n\n")
        fh.write(
            "Each row: `index`  output_tag  segment_offset  patch_type  segment_or_last  addend  status  pad\n\n"
        )
        fh.write("```\n")
        fh.write("index output_tag seg_off type last status pad addend\n")
        for i in range(count):
            off = table + i * 12
            output_tag = u32(data, off)
            patch_type = data[off + 4]
            last = data[off + 5]
            status = data[off + 6]
            pad = data[off + 7]
            addend = u32(data, off + 8)
            fh.write(
                f"{i:5d} 0x{output_tag:08x} 0x{output_tag >> 4:07x} {patch_type:4d} {last:4d} {status:6d} {pad:3d} {addend:#x}\n"
            )
        fh.write("```\n")
    return out


def main() -> int:
    if not ROMFS.is_dir():
        print(f"missing {ROMFS}", file=sys.stderr)
        return 1
    MODULES.mkdir(parents=True, exist_ok=True)
    rows = []
    failures = []
    cro_paths = sorted(ROMFS.glob("*.cro")) + sorted(ROMFS.glob("*.code"))
    for path in cro_paths:
        meta = parse_header(path)
        if meta is None:
            failures.append(path.name)
            continue
        write_info(meta)
        write_named_exports(meta)
        write_imports(meta)
        write_patches(meta)
        rows.append(
            (
                path.name,
                len(meta["data"]),
                meta["code_size"],
                meta["exports_named"],
                meta["imports_module_count"],
                meta["patches"],
            )
        )
    INDEX.write_text(
        "module\tfile_size\tcode_size\texports_named\timports_module\tpatches\n",
        encoding="utf-8",
    )
    with INDEX.open("a", encoding="utf-8") as fh:
        for r in rows:
            fh.write("\t".join(str(x) for x in r) + "\n")
    print(f"Indexed {len(rows)} modules; failures={len(failures)}")
    if failures:
        print("Unreadable:", failures)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
