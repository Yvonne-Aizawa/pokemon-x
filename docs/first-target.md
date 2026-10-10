# First reconstruction target

## Selected module

`DllDialogCommon.cro` is the first reconstruction target. It is small (12 KiB),
contains readable C++ RTTI names, and has a focused responsibility shared by the
game's dialog systems. It is a better initial target than `code.bin` or the large
battle/field modules.

Observed RTTI/type names include:

```text
app::dialog::MainSystem
app::dialog::DialogCommonUIListener
app::dialog::Proc
app::dialog::ViewWork
app::ui::UIInputListener
gfl::proc::BaseProcess
```

The module also contains the loader-facing name `DllDialogCommon` and the standard
`nnroControlObject_` symbol. These provide initial anchors for identifying the CRO
header, export table, relocation data, and function boundaries.

## Initial work items

- [ ] Parse and document the CRO header and section layout
- [x] Locate the export/import and relocation tables
- [ ] Identify the module entry/control object
- [ ] Recover the `Proc` lifecycle functions
- [x] Add the first symbol map under `docs/symbols/`
- [ ] Reconstruct one function and compare its output with the original bytes

The disassembly helper is available as `tools/disassemble_cro.py`. It emits both ARM
and Thumb interpretations because the correct instruction mode must be confirmed
from the module's code and call sites.

The first parser is available as `tools/cro_info.py`. Its field meanings follow the
public CRO format references from [3dbrew](https://www.3dbrew.org/wiki/CRO0) and
[wwylele's CRO notes](https://gist.github.com/wwylele/325d53ee6a0f1dff6aa3473377335d93).

## Parsed header snapshot

The local target currently reports:

```text
magic: CRO0
file size: 0x3000
code: offset 0x180, size 0x1e80
data: offset 0x28e0, size 0x14
bss size: 0x20
segments: 6
named exports: 1
imported modules: 1
external patches: 62
module name: DllDialogCommon
```

The named export table contains one symbol:

```text
nnroControlObject_  segment tag 0x0000c580  (segment 0, offset 0xc58)
```

This is recorded in `docs/symbols/DllDialogCommon.map` and is the first anchor for
recovering the module's loader/control-object lifecycle.

The first source reconstruction is in `src/dialog_common_recovered.c`. It records
the confirmed object offsets and preliminary control flow for the small lifecycle
helpers at CRO offsets `0x2d8` through `0x43c`. Calls into imported services remain
explicitly marked unresolved.

## Comparison candidates

`DllFatalErrorProc.cro` is a useful secondary sample because it is also 12 KiB and
has a narrow type surface (`xy_system::error::FatalErrorProc`). It can help validate
the CRO parser without committing either binary.

