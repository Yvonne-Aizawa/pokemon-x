#!/usr/bin/env python3
"""Extract named exports from a 3DS CRO module into a symbol map."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    data = args.module.read_bytes()
    if data[0x80:0x84] not in (b"CRO0", b"FIXD"):
        parser.error(f"{args.module} is not a CRO/FIXD module")
    table = u32(data, 0xD0)
    count = u32(data, 0xD4)
    output = args.output or ROOT / "docs" / "symbols" / f"{args.module.stem}.map"
    output.parent.mkdir(parents=True, exist_ok=True)
    rows = []
    for index in range(count):
        entry = table + index * 8
        name_offset = u32(data, entry)
        tag = u32(data, entry + 4)
        if name_offset >= len(data):
            parser.error(f"export {index} has an invalid name offset 0x{name_offset:x}")
        name = data[name_offset:].split(b"\0", 1)[0].decode("utf-8", errors="replace")
        rows.append((name, tag, tag & 0xF, tag >> 4))
    with output.open("w", encoding="utf-8") as stream:
        stream.write(f"# Exported symbols: {args.module.name}\n\n")
        stream.write("| Name | Segment tag | Segment | Offset |\n|---|---:|---:|---:|\n")
        for name, tag, segment, segment_offset in rows:
            stream.write(f"| `{name}` | `0x{tag:08x}` | {segment} | `0x{segment_offset:x}` |\n")
    print(f"Extracted {len(rows)} named exports")
    print(f"Wrote {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

