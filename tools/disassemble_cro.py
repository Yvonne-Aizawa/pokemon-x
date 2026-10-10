#!/usr/bin/env python3
"""Extract and disassemble the code segment from a 3DS CRO module."""

from __future__ import annotations

import argparse
import struct
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", type=Path)
    parser.add_argument("--output", type=Path, default=ROOT / "work" / "disassembly")
    parser.add_argument("--mode", choices=("arm", "thumb", "both"), default="both")
    args = parser.parse_args()

    data = args.module.read_bytes()
    if data[0x80:0x84] not in (b"CRO0", b"FIXD"):
        parser.error(f"{args.module} is not a CRO/FIXD module")
    code_offset = u32(data, 0xB0)
    code_size = u32(data, 0xB4)
    code = data[code_offset:code_offset + code_size]
    if len(code) != code_size:
        parser.error("CRO code segment extends beyond the file")

    args.output.mkdir(parents=True, exist_ok=True)
    stem = args.module.stem
    raw = args.output / f"{stem}.text.bin"
    raw.write_bytes(code)
    modes = ("arm", "thumb") if args.mode == "both" else (args.mode,)
    for mode in modes:
        output = args.output / f"{stem}.{mode}.asm"
        command = [
            "arm-none-eabi-objdump", "-D", "-b", "binary", "-m", "arm",
            "--adjust-vma", str(code_offset),
        ]
        if mode == "thumb":
            command.append("-Mforce-thumb")
        command.append(str(raw))
        with output.open("w", encoding="utf-8") as stream:
            subprocess.run(command, check=True, stdout=stream)
    metadata = args.output / f"{stem}.meta"
    metadata.write_text(
        f"module={args.module}\ncode_offset=0x{code_offset:x}\ncode_size=0x{code_size:x}\n"
        f"modes={','.join(modes)}\n",
        encoding="utf-8",
    )
    print(f"Extracted {code_size:#x} bytes from {args.module}")
    print(f"Wrote disassembly to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

