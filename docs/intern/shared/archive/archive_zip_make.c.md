# src/shared/archive/archive_zip_make.c

This file writes a zip into memory with miniz, for `pack` and `join`: `docs/extern/mpbt_compose.h.md`, *The zip*.

## The steps

1. `mz_zip_writer_init_heap` starts an empty zip in memory.
2. Each entry goes in with its name, its bytes and its mode, in the order of the caller.
3. The mode goes where `archive_zip.c` reads it. Thus `fetch` gives the bits back to each file.
4. `mz_zip_writer_finalize_heap_archive` gives the bytes, and they go into the `buffer_t` of the caller.

`join` gives each entry of a zip of a target, with the name of the target and `/` before its name.

## Functions

| Function | Result |
| --- | --- |
| `archive_zip_make` | The bytes of a zip, or a finding. |
| `add_entry` | Adds one entry, with its mode. |
