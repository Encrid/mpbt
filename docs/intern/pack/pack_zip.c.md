# src/pack/pack_zip.c

This file writes the zip of one deliverable: `docs/extern/mpbt_compose.h.md`, *The zip*.

## The steps

1. Each file of the deliverable becomes an entry, at its name, with the bytes that `path_read` gives for `{dist}/<name>`.
2. The mode of an entry is `0755` if `os_path_entry` finds an execute bit, and else `0644`.
3. `archive_zip_make` writes the entries into a `buffer_t`, in the order of the names.
4. `os_file_write` writes the bytes into `<build>/<name>-<target>.zip`. `<name>` is the name of the zips of the deliverable.
5. `say` writes the path of the zip, then each name in it, one on each line.

The zip holds only the files of its deliverable, also when `{dist}` holds the files of more parts.
A file that `path_read` cannot read, or a zip that `os_file_write` cannot write, gives its fault of `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `pack_write_zip` | 0 when the zip is written, or 1 after a fault. |
| `add_file` | Adds one file of the deliverable as an entry. |
