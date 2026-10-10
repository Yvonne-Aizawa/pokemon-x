#!/usr/bin/env python3
"""Dump CRO external patch entries with their target segment locations."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", type=Path)
    args = parser.parse_args()
    data = args.module.read_bytes()
    table = u32(data, 0xF8)
    count = u32(data, 0xFC)
    print("index output_tag segment_offset type segment_or_last addend")
    for index in range(count):
        offset = table + index * 12
        output_tag = u32(data, offset)
        patch_type, segment_or_last, status, padding = struct.unpack_from("<4B", data, offset + 4)
        addend = u32(data, offset + 8)
        print(f"{index:5d} 0x{output_tag:08x} 0x{output_tag >> 4:07x} {patch_type:4d} {segment_or_last:15d} {addend:#x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

