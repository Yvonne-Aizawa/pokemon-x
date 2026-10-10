#!/usr/bin/env python3
"""Trace one dynamic module's import record in static.crs."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def cstring(data: bytes, offset: int) -> str:
    return data[offset:].split(b"\0", 1)[0].decode("utf-8", errors="replace")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("crs", type=Path)
    parser.add_argument("module")
    args = parser.parse_args()
    data = args.crs.read_bytes()
    table, count = u32(data, 0xF0), u32(data, 0xF4)
    strings = u32(data, 0x118)
    found = False
    for index in range(count):
        entry = table + index * 20
        name = cstring(data, u32(data, entry))
        if name != args.module:
            continue
        found = True
        anonymous_head, anonymous_count = u32(data, entry + 12), u32(data, entry + 16)
        print(f"module_index: {index}")
        print(f"module: {name}")
        print(f"anonymous_head: 0x{anonymous_head:x}")
        print(f"anonymous_count: {anonymous_count}")
        for symbol_index in range(anonymous_count):
            symbol = anonymous_head + symbol_index * 8
            segment_tag, patch_head = struct.unpack_from("<II", data, symbol)
            print(f"anonymous[{symbol_index}]: segment_tag=0x{segment_tag:08x} patch_head=0x{patch_head:x}")
            patch = patch_head
            patch_index = 0
            while patch_index < 10000 and patch + 12 <= len(data):
                output_tag = u32(data, patch)
                patch_type, last, status, padding = struct.unpack_from("<4B", data, patch + 4)
                addend = u32(data, patch + 8)
                print(f"  patch[{patch_index}]: output=0x{output_tag:08x} type={patch_type} last={last} addend=0x{addend:x}")
                patch_index += 1
                if last:
                    break
                patch += 12
        break
    if not found:
        parser.error(f"module not found: {args.module}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

