.PHONY: help setup inventory modules inspect disassemble symbols patches check compare asmdiff inventory-verify inventory-verify-generate

MODULE ?= extracted/romfs/DllDialogCommon.cro
OFFSET ?=
SIZE   ?=
RECOVERED ?=

help:
	@printf '%s\n' \
	  'Available targets:' \
	  '  setup       Validate and extract a ROM (ROM=/path/to/file)' \
	  '  inventory   Hash local extracted files (legacy alias; use inventory-verify-generate)' \
	  '  modules     Generate the executable module inventory' \
	  '  inspect     Print CRO metadata (MODULE=...)' \
	  '  disassemble Generate ARM and Thumb listings (MODULE=...)' \
	  '  symbols     Extract named exports (MODULE=...)' \
	  '  patches     Dump external patch entries (MODULE=...)' \
	  '  check       Run tool smoke checks' \
	  '' \
	  'Round-1 verification pipeline:' \
	  '  inventory-verify             SHA-256 check every file in extracted/ vs rom.sha256' \
	  '  inventory-verify-generate    (re)generate rom.sha256 from current extracted/' \
	  '  asmdiff                      Per-function structural diff (MODULE=.. OFFSET=0x.. SIZE=0x..)' \
	  '  compare                      Substrate integrity gate (the equivalent of pret/pokeemerald make compare)'

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

# ---- Round-1 verification pipeline --------------------------------------------
# These are the honest equivalent of pret/pokeemerald's "make compare". Until
# we have a CRO build pipeline, the only thing we can byte-match is the substrate
# (the contents of extracted/), and the only thing we can structurally-diff is
# the recovered C source against the original disassembly. See
# docs/cci-byte-matching.md for the full rationale.

inventory-verify:
	python3 tools/inventory_verify.py

inventory-verify-generate:
	python3 tools/inventory_verify.py --generate

asmdiff:
	@if [ -z "$(MODULE)" ] || [ -z "$(OFFSET)" ] || [ -z "$(SIZE)" ]; then \
	  echo 'Usage: make asmdiff MODULE=<stem> OFFSET=0x<hex> SIZE=0x<hex> [RECOVERED=src/<stem>_recovered.c] [FN_NAME=...]' >&2; \
	  echo '   e.g. make asmdiff MODULE=DllDialogCommon OFFSET=0x2d8 SIZE=0x4c RECOVERED=src/dialog_common_recovered.c FN_NAME=dialog_can_run' >&2; \
	  exit 2; \
	fi
	python3 tools/asmdiff_cro.py \
	  $(shell STEM="$(MODULE)"; STEM="$${STEM##*/}"; STEM="$${STEM%.cro}"; STEM="$${STEM%.code}"; printf '%s' "$$STEM") \
	  "$(OFFSET)" "$(SIZE)" \
	  $(if $(RECOVERED),--recovered $(RECOVERED),) \
	  $(if $(FN_NAME),--fn-name $(FN_NAME),)

compare: inventory-verify
	@echo
	@printf '\033[1;32mextracted/ substrate matches rom.sha256 (657/657 files unchanged).\033[0m\n'
	@printf 'This is the Round-1 honesty floor. See docs/cci-byte-matching.md for what is NOT\n'
	@printf 'matched yet (the NCSD/NCCH RSA signatures), and what WILL be matched once a CRO\n'
	@printf 'build pipeline exists.\n'

check:
	python3 -m py_compile tools/*.py
	python3 tools/cro_info.py "$(MODULE)" >/dev/null
	python3 tools/export_symbols.py "$(MODULE)" --output /tmp/pokemon-x-symbol-check.map >/dev/null
	rm -f /tmp/pokemon-x-symbol-check.map
	@echo 'Tool checks passed.'
