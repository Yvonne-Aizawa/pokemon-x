#!/usr/bin/env python3
"""Validate a user-provided Pokémon X image and extract local build inputs."""

from __future__ import annotations

import argparse
import hashlib
import shutil
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path, help="path to a CCI/3DS image")
    parser.add_argument("--ctrtool", type=Path, help="path to ctrtool")
    parser.add_argument("--sha256", help="expected ROM SHA-256, if known")
    args = parser.parse_args()

    rom = args.rom.expanduser().resolve()
    if not rom.is_file():
        parser.error(f"ROM does not exist: {rom}")

    digest = sha256(rom)
    if args.sha256 and digest.lower() != args.sha256.lower():
        parser.error(f"ROM hash mismatch: got {digest}, expected {args.sha256}")

    ctrtool = (args.ctrtool or ROOT / "tools" / "ctrtool").resolve()
    if not ctrtool.is_file():
        ctrtool = Path(shutil.which("ctrtool") or "")
    if not ctrtool.is_file():
        parser.error("ctrtool was not found; pass --ctrtool or install it in PATH")

    work = ROOT / "work"
    extracted = ROOT / "extracted"
    work.mkdir(exist_ok=True)
    extracted.mkdir(exist_ok=True)
    (work / "rom.sha256").write_text(f"{digest}  {rom}\n", encoding="utf-8")

    exefs_dir = extracted / "exefs"
    romfs_dir = extracted / "romfs"
    exefs_dir.mkdir(exist_ok=True)
    romfs_dir.mkdir(exist_ok=True)
    subprocess.run(
        [str(ctrtool), f"--exheader={extracted / 'exheader.bin'}", str(rom)],
        check=True,
    )
    subprocess.run(
        [str(ctrtool), f"--exefsdir={exefs_dir}", str(rom)],
        check=True,
    )
    subprocess.run(
        [str(ctrtool), f"--romfsdir={romfs_dir}", str(rom)],
        check=True,
    )

    print(f"Validated ROM: {rom}")
    print(f"SHA-256: {digest}")
    print(f"Extracted local build inputs to: {extracted}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

