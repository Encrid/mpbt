# src/shared/archive/archive_zip.c

This file reads a zip in memory with miniz: https://github.com/richgel999/miniz/releases/tag/3.1.2.

## The steps

1. `mz_zip_reader_init_mem` opens the bytes of the zip.
2. For each entry, `mz_zip_reader_file_stat` gives its name, whether it is a folder, and its external attributes.
3. `mz_zip_reader_extract_to_heap` gives the bytes of a file.
4. The entry goes to the function of the caller, then its bytes are freed.

The upper 16 bits of the external attributes hold the mode of Unix, when the zip was made on Unix. Thus a program of a zip keeps its execute bits.
A zip of Windows has no mode, so its entries get `0644`, and `0755` for a folder.

## Functions

| Function | Result |
| --- | --- |
| `read_zip` | Each entry of a zip, or a finding. |
| `zip_mode` | The mode of an entry. |
