#!/usr/bin/env python3
"""Generate a Markdown inventory of executable modules in a local extraction."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def classify(name: str) -> str:
    lower = name.lower()
    if name == "code.bin":
        return "Main executable"
    if "battle" in lower or "btl" in lower:
        return "Battle"
    if "field" in lower or "town" in lower or "map" in lower:
        return "Field / map"
    if any(token in lower for token in ("bag", "box", "menu", "select", "dialog", "pc")):
        return "UI / menu"
    if "test" in lower or "debug" in lower:
        return "Test / debug"
    return "Unclassified"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT / "extracted")
    parser.add_argument("--output", type=Path, default=ROOT / "docs" / "modules.md")
    args = parser.parse_args()

    root = args.root.resolve()
    if not root.is_dir():
        parser.error(f"extraction directory does not exist: {root}")

    modules = sorted(
        path
        for path in root.rglob("*")
        if path.is_file() and (path.name == "code.bin" or path.suffix.lower() in {".cro", ".code"})
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", encoding="utf-8") as output:
        output.write("# Module inventory\n\n")
        output.write("Generated from the local extraction. Binaries remain local and are not tracked.\n\n")
        output.write("| Module | Location | Size | SHA-256 | Category | Priority |\n")
        output.write("|---|---|---:|---|---|---|\n")
        for path in modules:
            name = path.name
            category = classify(name)
            priority = "High" if name == "code.bin" else "Medium" if category != "Unclassified" else "Low"
            relative = path.relative_to(root).as_posix()
            output.write(
                f"| `{name}` | `{relative}` | {path.stat().st_size:,} | "
                f"`{sha256(path)}` | {category} | {priority} |\n"
            )
        output.write(f"\nTotal modules: **{len(modules)}**.\n")

    print(f"Indexed {len(modules)} executable modules")
    print(f"Wrote {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

