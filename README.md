# Pokémon X decompilation

This repository contains the reconstructed source code and build tools for Pokémon X.

The game ROM and extracted assets are intentionally **not** included. You must provide
your own legally obtained copy of a supported Pokémon X release. The setup script
validates the supplied image and extracts its contents into ignored local directories.

The repository also does not include the `ctrtool` or `makerom` binaries. Obtain them
from the [Project_CTR releases](https://github.com/3DSGuy/Project_CTR/releases) and
place them in `tools/`, or make them available in your `PATH`.

## Quick start

```sh
python3 tools/setup.py --rom /path/to/Pokemon_X.cci
```

After setup, the ROM-derived files will be under `extracted/`. They are ignored by
Git and must never be committed. The build command will be added as the source tree
is reconstructed.

## Repository policy

Committed files should be source code, reverse-engineering metadata, tools,
documentation, tests, and build configuration. Do not commit ROMs, extracted
ExeFS/RomFS data, copyrighted assets, or generated binaries.

