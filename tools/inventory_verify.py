#!/usr/bin/env python3
"""Verify that extracted/ matches the recorded SHA-256 manifest.

This is the substrate integrity gate. It does NOT byte-match the surrounding
CCI/NCSD/NCCH containers (those are RSA-signed by Nintendo and unmatchable
without the private key — see docs/cci-byte-matching.md). It DOES ensure the
contents of every extracted file (each CRO, code.bin, RomFS sub-archive, etc.)
are exactly what they were when setup.py first extracted them.

It is the equivalent of pret/pokeemerald's `sha1sum -c rom.sha1` for the parts
we can actually match.
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = ROOT / "rom.sha256"


def digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def parse_manifest(path: Path) -> dict[str, str]:
    out: dict[str, str] = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        # `<hex>  <relative>`; handle either single or double space
        parts = line.split(None, 1)
        if len(parts) != 2 or len(parts[0]) != 64:
            continue
        out[parts[1]] = parts[0]
    return out


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--root", type=Path, default=ROOT / "extracted",
        help="Directory the manifest is taken relative to",
    )
    parser.add_argument(
        "--manifest", type=Path, default=DEFAULT_MANIFEST,
        help="Path to the SHA-256 manifest (default: rom.sha256)",
    )
    parser.add_argument(
        "--generate", action="store_true",
        help="Generate the manifest from current extracted/ instead of checking it",
    )
    parser.add_argument(
        "--allow-missing", action="store_true",
        help="Warn rather than fail on missing files (for partial checkouts)",
    )
    args = parser.parse_args()

    if args.generate:
        # Regenerate the manifest from current extracted/
        args.manifest.parent.mkdir(parents=True, exist_ok=True)
        files = sorted(p for p in args.root.rglob("*") if p.is_file())
        with args.manifest.open("w", encoding="utf-8") as fh:
            for path in files:
                fh.write(f"{digest(path)}  {path.relative_to(args.root)}\n")
        print(f"Wrote {len(files)} entries to {args.manifest}")
        return 0

    if not args.manifest.is_file():
        print(f"manifest not found: {args.manifest}", file=sys.stderr)
        print("Hint: generate it once with `make inventory-verify-generate`", file=sys.stderr)
        return 2

    expected = parse_manifest(args.manifest)
    if not expected:
        print(f"empty or unparseable manifest: {args.manifest}", file=sys.stderr)
        return 2

    failed = 0
    missing = 0
    extra = 0
    unchanged = 0

    # Check every entry in the manifest.
    for rel, want in sorted(expected.items()):
        p = args.root / rel
        if not p.is_file():
            print(f"MISSING: {rel}")
            missing += 1
            continue
        got = digest(p)
        if got == want:
            unchanged += 1
        else:
            print(f"CHANGED: {rel}")
            print(f"  expected: {want}")
            print(f"  got:      {got}")
            failed += 1

    # Check for unlisted files.
    listed = set(expected)
    for path in sorted(args.root.rglob("*")):
        if not path.is_file():
            continue
        rel = str(path.relative_to(args.root))
        if rel not in listed:
            print(f"UNLISTED: {rel}")
            extra += 1

    print()
    print(f"summary: unchanged={unchanged}  changed={failed}  missing={missing}  extra={extra}")
    if failed or missing:
        if missing and args.allow_missing:
            print("ALLOW-MISSING: missing files not treated as failure")
        else:
            return 1
    if extra:
        return 3
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
