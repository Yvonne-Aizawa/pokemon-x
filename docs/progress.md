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
- [ ] Reconstruct the first function with resolved imports
- [ ] Add binary comparison checks

