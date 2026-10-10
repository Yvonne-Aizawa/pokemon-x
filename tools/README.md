# Local tools

`ctrtool` and `makerom` are third-party binaries and are intentionally not stored
in this repository. Download compatible releases from the
[Project_CTR releases page](https://github.com/3DSGuy/Project_CTR/releases).

Place them in this directory for local development, or put them on `PATH`. They are
ignored by Git.

## Inventory

After extracting a ROM, generate a deterministic local manifest with:

```sh
python3 tools/inventory.py
```

The output is written to `work/inventory.sha256`, which is also ignored. Only copy
reference hashes into `docs/target.md`; do not commit extracted files or manifests
that reveal the contents of the supplied ROM.

## Module inventory

Generate a source-controlled metadata inventory of executable modules with:

```sh
python3 tools/module_info.py
```

This writes `docs/modules.md`. It records names, sizes, hashes, and preliminary
categories, but does not copy any binary data into the repository.

## CRO inspection

Inspect a module's header and segment table with:

```sh
python3 tools/cro_info.py extracted/romfs/DllDialogCommon.cro
```

## Disassembly

The container provides `arm-none-eabi-objdump`. Generate ARM and Thumb views of a
CRO's code segment with:

```sh
python3 tools/disassemble_cro.py extracted/romfs/DllDialogCommon.cro
```

Output is written under ignored `work/disassembly/`. The code segment is extracted
without modifying the source CRO.

## Export symbols

Extract named exports into a source-controlled symbol map with:

```sh
python3 tools/export_symbols.py extracted/romfs/DllDialogCommon.cro
```

The symbol map contains names and segment tags only; it does not copy binary data.

