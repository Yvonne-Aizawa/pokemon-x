#!/usr/bin/env python3
"""Write a deterministic inventory and SHA-256 manifest for local extracted files."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT / "extracted")
    parser.add_argument("--output", type=Path, default=ROOT / "work" / "inventory.sha256")
    args = parser.parse_args()

    root = args.root.resolve()
    if not root.is_dir():
        parser.error(f"extraction directory does not exist: {root}")

    files = sorted(path for path in root.rglob("*") if path.is_file())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", encoding="utf-8") as manifest:
        for path in files:
            manifest.write(f"{digest(path)}  {path.relative_to(root)}\n")

    print(f"Indexed {len(files)} files under {root}")
    print(f"Wrote {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

