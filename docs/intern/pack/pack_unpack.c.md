# src/pack/pack_unpack.c

This file unpacks the zip of a deliverable into `{out}/proof`. Thus the proof sees the package, and no file of the project.

## The steps

1. `path_read` reads the zip. Then `archive_read` calls `write_entry` for each entry.
2. A folder of the zip becomes a folder, with `os_folder_make`.
3. A file of the zip becomes a file, with `os_file_write`, after `os_folder_make` makes its folder.
4. A mode with an execute bit gives the file its execute bit.

The zip is the one that `pack_write_zip` wrote, so each of its names stays in `{out}/proof`.
If the zip does not read, or a file or a folder of it cannot be written, the proof stops.
Its fault is in `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `pack_unpack` | 0 when each entry is written, or 1 after a fault. |
| `write_entry` | Writes one entry: the function that `archive_read` calls. |
