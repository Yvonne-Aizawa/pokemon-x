#!/usr/bin/env python3
"""List the modules and symbol-list heads imported by a CRS/CRO module."""

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
    parser.add_argument("module", type=Path)
    args = parser.parse_args()
    data = args.module.read_bytes()
    module_table = u32(data, 0xF0)
    module_count = u32(data, 0xF4)
    strings = u32(data, 0x118)
    print("index module indexed_head indexed_count anonymous_head anonymous_count")
    for index in range(module_count):
        offset = module_table + index * 20
        name = cstring(data, u32(data, offset))
        indexed_head, indexed_count = u32(data, offset + 4), u32(data, offset + 8)
        anonymous_head, anonymous_count = u32(data, offset + 12), u32(data, offset + 16)
        print(f"{index:5d} {name:28s} 0x{indexed_head:08x} {indexed_count:13d} 0x{anonymous_head:08x} {anonymous_count:15d}")
    print(f"import string table: 0x{strings:x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

