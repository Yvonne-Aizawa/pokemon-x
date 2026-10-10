#!/usr/bin/env python3
"""Print the header and segment metadata of a 3DS CRO module."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


FIELDS = {
    "name_offset": 0x84,
    "file_size": 0x90,
    "bss_size": 0x94,
    "fixed_size": 0x98,
    "control_object": 0xA0,
    "on_load": 0xA4,
    "on_exit": 0xA8,
    "on_unresolved": 0xAC,
    "code_offset": 0xB0,
    "code_size": 0xB4,
    "data_offset": 0xB8,
    "data_size": 0xBC,
    "module_name_offset": 0xC0,
    "module_name_size": 0xC4,
    "segment_table": 0xC8,
    "segment_count": 0xCC,
    "export_named_table": 0xD0,
    "export_named_count": 0xD4,
    "export_indexed_table": 0xD8,
    "export_indexed_count": 0xDC,
    "import_module_table": 0xF0,
    "import_module_count": 0xF4,
    "external_patch_table": 0xF8,
    "external_patch_count": 0xFC,
}


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", type=Path)
    args = parser.parse_args()
    data = args.module.read_bytes()
    if data[0x80:0x84] not in (b"CRO0", b"FIXD"):
        parser.error(f"{args.module} is not a CRO/FIXD module")

    print(f"module: {args.module}")
    print(f"magic: {data[0x80:0x84].decode('ascii')}")
    for name, offset in FIELDS.items():
        print(f"{name}: 0x{u32(data, offset):08x} ({u32(data, offset)})")

    name_offset = u32(data, 0xC0)
    name_size = u32(data, 0xC4)
    if name_offset + name_size <= len(data):
        raw_name = data[name_offset:name_offset + name_size].split(b"\0", 1)[0]
        print(f"module_name: {raw_name.decode('utf-8', errors='replace')}")

    print("segments:")
    segment_table = u32(data, 0xC8)
    segment_count = u32(data, 0xCC)
    for index in range(segment_count):
        offset = segment_table + index * 0x8
        if offset + 0x8 > len(data):
            break
        first, second = struct.unpack_from("<II", data, offset)
        print(f"  {index}: 0x{first:08x}, 0x{second:08x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

