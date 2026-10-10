# Static module (`static.crs`)

`static.crs` is the symbol/relocation companion for the main executable. It is not
the main executable itself: its code segment size is zero, while its segment table
describes the main process address space.

## Local metadata

```text
SHA-256: 30d10ada3f829ae5ae2080c15d27ddf809b3d852cbaf5928c44e609764bffdaa
Module: |static|
Named exports: 461
Imported modules: 78
Anonymous imports: 328
External patches: 331
```

The import-module table names the dynamic modules known to the static module, such
as `DllBoxSearch`, `FieldDemo`, and other `Dll*.cro` modules. Generate the complete
table with:

```sh
python3 tools/static_imports.py extracted/romfs/static.crs
```

The static export map is in [`symbols/static.exports.md`](symbols/static.exports.md).

## Relevance to DllDialogCommon

`DllDialogCommon.cro` imports the `|static|` module and has 62 external patch entries,
but no ordinary named/indexed/anonymous import records. This suggests its patch data
uses a compact/static linkage form. The static module's 328 anonymous imports and
78-module import table are now the next structures to correlate against those patch
locations.

The static module's import record for `DllDialogCommon` is index 41. Its anonymous
import list has one entry at `0x8168`, containing segment tag `0x00005900` and patch
list head `0x00006bb8`. That list contains one absolute patch with output tag
`0x009a9280` and addend zero. This is a static-to-dynamic callback relationship and
is separate from the 62 external patches stored in `DllDialogCommon.cro`.

