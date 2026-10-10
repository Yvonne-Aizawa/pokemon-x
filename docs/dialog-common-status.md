# DllDialogCommon decompilation status

## Recovered

- CRO header, code/data ranges, segment count, and export table.
- One named export: `nnroControlObject_`.
- Preliminary object layout for the process object, including state at `+0x24`,
  sub-state at `+0x25`, timer at `+0x28`, child/work pointer at `+0x20`, and owner
  pointer at `+0x7c`.
- Preliminary boundaries for the main update, shutdown, transition, constructors,
  destructors, event handlers, and the large dialog operation.
- C-like reconstruction in `src/dialog_common_recovered.c` for the simplest lifecycle
  helpers and the state-dispatch skeleton.
- Static module export metadata in `docs/symbols/static.exports.md` (461 exports).
- External patch table decoded: 62 entries, all patch type 2 (absolute 32-bit writes),
  with output segment tags and addends recorded by `tools/cro_patches.py`.

## Current blocker

The decompilation cannot yet be made buildable or byte-matching. The dynamic module
contains 62 external patch entries whose target symbol identities are still not
decoded: this file has no named/indexed/anonymous import entries, so the patches
appear to rely on compact loader metadata or static anonymous symbols. The exact CRO
linker/build conventions are also not established.
Several calls therefore still resolve only to loader stubs such as `0x180` through
`0x2d4`. The next required reverse-engineering step is decoding the imported-module,
imported-symbol, and patch-entry structures, then resolving them against `static.crs`.

The current source is consequently a documented preliminary reconstruction, not a
claim of binary equivalence.

