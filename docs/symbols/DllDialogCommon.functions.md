# DllDialogCommon function candidates

These are preliminary boundaries identified from ARM prologues/epilogues in the
local disassembly. Names are intentionally provisional until cross-module call sites
and RTTI references confirm their roles.

| Address | Evidence | Provisional role |
|---:|---|---|
| `0xc34` | `push {r4, lr}`, initializes fields at offsets `0x00` and `0x74`, calls `0x2c0`, `0x2c8`, `0x2d0` | Constructor / initialization |
| `0xc68` | `push {r4, lr}`, initializes the same object fields, calls `0x2c0`, `0x2c8`, `0x2d0` | Alternate constructor / initialization |
| `0xca4` | Stores a new vtable pointer; releases field at offset `0x14` when non-null | Destructor / cleanup |
| `0xcdc` | Reads field at offset `0x14` and branches through cleanup helpers | Cleanup or state transition |
| `0x300` | Dispatch table on state byte at `this + 0x24` | Main process update |
| `0x404` | Virtual cleanup at child vtable `+0x18`, finalizes work area, sets state 4 | Main process shutdown |
| `0x43c` | Checks work mode at `work + 0x08`, updates timer at `this + 0x28`, changes state | Active dialog update |
| `0x5e8` | Replaces vtable, destroys child, finalizes two work-area objects | Destructor variant |
| `0x638` | Same cleanup pattern with a different vtable | Destructor variant |
| `0x688` | Calls `0x300`, then child virtual method `+0x20`; returns inverted result | Process callback |
| `0x6c4` | Calls child virtual method `+0x08` | Process callback |
| `0x6e8` | Forwards to child virtual method `+0x24` | Process callback |
| `0x710` | Allocates/initializes a work object, stores argument at `this + 0x28` | Constructor |
| `0x7a4` | Destroys work object and optional field at `this + 0x14` | Destructor variant |
| `0x7f0` | Same work-object cleanup with a different vtable | Destructor variant |
| `0x840` | Dispatches event IDs 4, 5, 10, 13, and 16 through child virtual calls | Input/event handler |
| `0x900` | Large dialog operation using work fields and imported helpers | Dialog operation |
| `0xd20` | Dispatches event IDs through object at `this + 0x08` | Listener/event handler |
| `0xdd8` | Dispatches event IDs and writes callback/object fields | Listener callback setup |

The export `nnroControlObject_` resolves to segment 0, offset `0xc58`. This falls
inside the first candidate's epilogue and should be treated as a loader/control
object address until the CRO segment-tag semantics are fully mapped.

## Next validation

- Compare the candidate vtable pointers at `0xc64`, `0xc9c`, and `0xcd8`.
- Resolve calls at `0x2c0`, `0x2c8`, and `0x2d0`.
- Search the static module and other CROs for references to `DllDialogCommon`.
- Confirm whether the exported control object is a function, object, or table entry.

The remaining functions are not safely nameable yet because their imported calls are
represented by CRO stubs and the static module's symbol table (`.crs`) has not been
parsed. The allocator, UI service calls, and virtual interfaces need cross-module
symbol resolution before a faithful buildable implementation is possible.

