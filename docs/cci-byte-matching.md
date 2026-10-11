# CCI byte-matching — what's actually possible

This document explains why a byte-for-byte match of the Pokémon X `.cci`
container is **not** on the table for a community decomp (and was never on the
table for `pret/pokeemerald` either — they just don't have to think about it
because GBA ROMs are unsigned). It then describes what we *can* match, which
mirrors the same confidence role that `pret`'s `make compare` plays in their
project.

## Container layout (the thing we can't match)

The Pokémon X distribution file `0004000000055D00 Pokemon X.cci` is a **CTR
Cartridge Image (CCI)**. Approximately:

```
┌─────────────────────────────────────────────────────────────┐
│ NCSD header                                                  │
│   - magic, version                                           │
│   - partition table (3 partitions)                            │
│   - RSA signature over SHA-256 of partition 0's NCCH header  │
│   - RSA signature over SHA-256 of partition 0's ExeFS        │
│   - RSA signature over SHA-256 of partition 0's RomFS        │
│   - ...etc, per partition...                                 │
├─────────────────────────────────────────────────────────────┤
│ Partition 0 (the game):                                      │
│   ┌─ NCCH header ────────────────────────────────────────┐  │
│   │  - title ID, version, content type                    │  │
│   │  - SHA-256 hashes of every section below              │  │
│   │  - RSA signature over the above                       │  │
│   ├──────────────────────────────────────────────────────┤  │
│   │  ExeFS (executable file system):                      │  │
│   │    /code.bin    - 5 MB ARM/Thumb program              │  │
│   │    /banner.bin  - top-screen banner                   │  │
│   │    /icon.bin    - home-menu icon                      │  │
│   ├──────────────────────────────────────────────────────┤  │
│   │  RomFS (read-only data file system):                   │  │
│   │    /static.crs     - main module's exported symbols   │  │
│   │    /Dll*.cro       - ~133 code modules (CRO format)   │  │
│   │    /a/             - encrypted sub-archive            │  │
│   │    /m/             - encrypted sub-archive            │  │
│   │    /shaders/       - GSP shader bundles               │  │
│   │    /sound/         - audio streams                    │  │
│   │    /sounddebug/    - audio debug streams              │  │
│   │    /<garbage>/     - service and overlay data         │  │
│   └──────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
```

Every SHA-256 in that hierarchy is wrapped in an **RSA signature** that the
3DS bootrom verifies before allowing the cartridge (or installed title) to run.
The private half of the keypair is held by Nintendo. It has never leaked. A
matching CI is therefore not reproducible without either the key or a
suitable substitute signer (e.g. a debug/development key, which is a different
release format).

That's not a tooling problem we can solve with another subagent — it's a
physical property of the format.

## What we *can* match

What we control:

1. **The bytes of every CRO, code.bin, and RomFS sub-file.** These are not
   individually signed; the *layout* of the partitions is signed, but the
   contents of any individual file inside is just data.
2. **The C source we write into `src/<stem>_recovered.c`.** If we build a
   CRO from our recovered C and it produces bytes that hash the same as the
   original, that's a real, structural match — verifiable with no signing.

What we cannot control, in the same sense:

3. **The NCSD / NCCH headers' RSA signatures.** These bind the partition
   layout, file sizes, and content hashes. Changing any one of them breaks
   signatures for everyone.

## How `pret/pokeemerald` does it (and why they don't have to think)

Their `make compare` is brutal:

```sh
$ make compare
... build ...
pokeemerald.gba: OK            # sha1sum -c rom.sha1 passed
```

That's the whole check. The GBA ROM has no signature, no license check, no
bootrom verification. Whatever bytes the assembler emits are the bytes that
will run on hardware. Either the SHA1 of the produced ROM equals the recorded
SHA1, or it doesn't. That's pret's confidence model.

For a decomp PR, the contributor runs `make compare` locally; CI runs it on
every push; the answer is binary PASS/FAIL. There is no partial credit, no
"close enough", no signed-container exceptions.

## Our equivalent (`make compare`)

Our pipeline mirrors pret's intent, minus the signature wall:

```
                          ┌─────────────────────────────────────┐
                          │  make compare                         │
                          └─────────────┬─────────────────────────┘
                                        │
                ┌───────────────────────┼────────────────────────────┐
                │                       │                            │
                ▼                       ▼                            ▼
  tools/inventory_verify.py    tools/asmdiff_cro.py         docs/cci-byte-matching.md
  (component SHA256)           (per-function structure)     (this file)
        │                              │                            │
        │ sha256sum -c rom.sha256       │ diff block/branch/call    │ honest framing
        │ per file under extracted/     │ counts between            │
        │ vs the committed manifest      │ original asm and          │
        │                                │ recovered C               │
```

Three pieces of evidence, each telling a different story:

1. **`make inventory-verify`** — every file inside `extracted/` (657 of them)
   matches its recorded SHA-256. This catches substrate corruption *before*
   any build runs. Translation: "the inputs to the decomp have not drifted."

2. **`make asmdiff MODULE=… OFFSET=… SIZE=…`** — for a specific function, dump
   the original's disassembly and the recovered C, count basic blocks and
   branches, and emit a structural diff. Translation: "this particular
   function's *shape* matches the original's. Body bytes are checked when a
   build pipeline exists."

3. **(Future) `make compare` after a CRO linker exists.** — once we can
   compile `src/<stem>_recovered.c` into CRO bytes and stitch a rebuilt
   container, the diff becomes byte-for-byte and the SHA-256 of any rebuilt
   component must equal the original. This is what pret gets for free today
   and what we earn incrementally as Round 2+ lands.

Today's PR gate is steps 1 and 2 only. Step 3 lands when the linker script
and CRO build pipeline are written.

## What we deliberately do NOT claim

- We do not produce a `.cci` that boots on retail hardware (would require
  re-signing).
- We do not produce a `.cci` that hashes byte-identical to the original
  (would require re-signing).
- We do not produce a `.cci` whose parts hash identically when individually
  extracted — that requires rebuilding the CROs in the first place, and we
  don't have that pipeline yet.

What we DO claim, from the moment this doc and `make compare` land:

- The 657 files under `extracted/` are bit-for-bit what setup.py produced
  from a Pokémon X ROM SHA-256 equal to `62cc7268d594abdb36ffff77a868ba5f571b240afd985f5d5264843abb2e4c11`.
- The recovered C source compiles cleanly with `gcc -Wall -Wextra -fsyntax-only`
  (a syntactic gate, not a semantic one).
- The asmdiff tool can compare any recovered function against its original
  byte range and report whether the structural shape aligns.

Everything else is an aspiration. Pret has the same aspiration differently
shaped because their format lets them.

## Next steps toward a real `make compare`

In rough priority order:

1. **CRO build pipeline.** Assemble `src/<stem>_recovered.c` to a CRO file
   that the loader would accept. This requires:
   - A CRO linker script (the "linker script" you asked for).
   - A compiler invocation that emits CRO-format object files.
   - Possibly: a vendor ABI baseline (C ABI for the 3DS / nnRuntime) so
     function calls hit the right vtables.
2. **Stitcher.** Take the original CCI, swap in any CROs we have rebuilt,
   recompute SHA-256s for the sections that changed, write a new NCCH
   with placeholder signatures. Bytes won't match the original but every
   *intermediate* SHA we can match, *will* match.
3. **Sign with a dev/private key** (out of scope). Once 1 and 2 are done, a
   developer with the matching 3DS dev kit can sign with their legitimate
   key. A community signer is not in scope.

Until then, this file + `make compare` + `make inventory-verify` is the
correct, honest verification gate.
