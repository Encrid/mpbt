# src/join/join_zip.c

This file joins the zips of the targets of one part: `docs/extern/mpbt_compose.h.md`, *The release*.

## The steps

1. The name of the zips is `name` of the part.
2. For each target, the zip is `<build>/<name>-<target>.zip`. The targets come in the order of their names.
3. If a zip is not there, its fault of `docs/extern/mpbt_compose.h.md`, *Messages*, stops the part before a write.
4. `path_read` reads each zip, and `archive_read` gives each of its entries to `add_entry`.
5. Each entry gets the name of its target and `/` before its name, and it keeps its mode.
6. `archive_zip_make` writes the entries into a `buffer_t`, and `os_file_write` writes `<build>/<name>.zip`.
7. `say` writes the path of the new zip.

`archive_read` frees the bytes of an entry after the call, so `add_entry` keeps a copy of them.
A zip that is there but does not read is a fault, and so is a new zip that the system refuses to write.
These faults are in `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `join_write_zip` | 0 when the zip of the part is written, or 1 after a fault. |
| `find_zips` | The zip of each target, or a fault for the first zip that is not there. |
| `add_target` | Adds the entries of the zip of one target. |
| `add_entry` | Adds one entry under the name of its target: the function that `archive_read` calls. |
