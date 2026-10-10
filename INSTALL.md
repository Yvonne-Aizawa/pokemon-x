# Installation

## Requirements

- Python 3.9 or newer
- A legally obtained Pokémon X ROM in CCI/3DS format
- `ctrtool` and `makerom` from the [Project_CTR releases](https://github.com/3DSGuy/Project_CTR/releases)

## Set up a local working copy

Run:

```sh
python3 tools/setup.py --rom /path/to/Pokemon_X.cci
```

Before running setup, download the required Project_CTR binaries and either place
`ctrtool` in `tools/` or install it somewhere on your `PATH`. `makerom` is needed
when the project build pipeline begins producing a final image.

The script records the ROM SHA-256 in `work/rom.sha256`, extracts the exheader,
ExeFS, and RomFS into `extracted/`, and prints the resulting paths. Both locations
are ignored by Git.

To inspect the available options:

```sh
python3 tools/setup.py --help
```

