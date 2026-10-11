# Progress

## Bootstrap

- [x] Public repository created
- [x] ROM and extracted assets excluded from Git
- [x] Local setup script added
- [x] Confirm the reference ROM release and hashes
- [ ] Confirm a clean-clone extraction on a second machine

## Decompilation

- [x] Inventory ExeFS and CRO modules
- [x] Choose `DllDialogCommon.cro` as the first reconstruction target
- [x] Parse and document the CRO header and section layout
- [x] Add disassembly and symbol-generation tooling
- [x] Add a Makefile developer workflow
- [x] Identify preliminary function boundaries in `DllDialogCommon.cro`
- [x] Write preliminary C-like reconstruction and object layout
- [x] Decode the CRO segment and external patch entry layouts
- [x] Inventory static CRS exports and imported modules
- [x] Trace the `DllDialogCommon` static-side anonymous import
- [x] **Round-1 module-level preliminary recovery: 133 / 133 modules covered** (see [`docs/decomp-round-1.md`](decomp-round-1.md))
- [x] Catalog every function prologue across all 133 modules (13,554 entries)
- [x] Fix disassembly tool bug: `-Mforce-thumb` mis-interprets ARM loader veneers
- [x] Persist the orchestration playbook at `docs/decomp-orchestration/SKILL.md`
- [x] **Round-3 build pipeline**: `tools/rebuild_cro.py` compiles src/<stem>_recovered.c and overlays onto a copy of the original CRO; `tools/cro_byte_diff.py` walks the function catalog and SHA-256-checks each function's byte range in both (see [`docs/cro-build-pipeline.md`](cro-build-pipeline.md))
- [ ] Reconstruct the first function with resolved imports
- [ ] **Round-4 per-function recovery** (planned: feed the byte-diff punch list to dense C, watch match rate rise toward 13,554)
- [ ] CCI stitcher + sign-with-dev-key (out of scope; see docs/cci-byte-matching.md)

