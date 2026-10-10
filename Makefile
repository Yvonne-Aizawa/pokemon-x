.PHONY: help setup inventory modules inspect disassemble symbols patches check

MODULE ?= extracted/romfs/DllDialogCommon.cro

help:
	@printf '%s\n' 'Available targets:' '  setup       Validate and extract a ROM (ROM=/path/to/file)' '  inventory   Hash local extracted files' '  modules     Generate the executable module inventory' '  inspect     Print CRO metadata (MODULE=...)' '  disassemble Generate ARM and Thumb listings (MODULE=...)' '  symbols     Extract named exports (MODULE=...)' '  check       Run tool smoke checks'

setup:
	@test -n "$(ROM)" || (echo 'Usage: make setup ROM=/path/to/Pokemon_X.cci' >&2; exit 2)
	python3 tools/setup.py --rom "$(ROM)"

inventory:
	python3 tools/inventory.py

modules:
	python3 tools/module_info.py

inspect:
	python3 tools/cro_info.py "$(MODULE)"

disassemble:
	python3 tools/disassemble_cro.py "$(MODULE)"

symbols:
	python3 tools/export_symbols.py "$(MODULE)"

patches:
	python3 tools/cro_patches.py "$(MODULE)"

check:
	python3 -m py_compile tools/*.py
	python3 tools/cro_info.py "$(MODULE)" >/dev/null
	python3 tools/export_symbols.py "$(MODULE)" --output /tmp/pokemon-x-symbol-check.map >/dev/null
	rm -f /tmp/pokemon-x-symbol-check.map
	@echo 'Tool checks passed.'

