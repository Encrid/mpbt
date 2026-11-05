# src/shared/copy/copy.c

This file copies a file with the calls of mosl: a read of the file, then a write of the copy.

## The steps

1. `path_read` reads the file, and `os_path_entry` tells whether it has an execute bit.
2. If the copy has the same bytes and the same answer of `os_path_entry`, the copy changes nothing.
3. Else `os_folder_make` makes the folder of the copy.
4. Then `os_file_write` writes the bytes, with the execute bit of the file.

Thus mpbt writes a copy only for a new or a changed file, and a program keeps its execute bit: `docs/extern/mpbt_compose.h.md`, *The deliverable*.
On Windows, `os_path_entry` gives the same answer for each file, since a file has no execute bit there.

A file that does not read gives -1, and a copy that cannot be written gives -2.
With -1, the caller gives the fault of a file that mpbt cannot read. With -2, it gives the fault of a file that mpbt cannot write.
Both faults are in `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `copy_file` | 0 when the copy holds the bytes and the execute bit of the file, -1, or -2. |
| `is_same` | Whether the copy is the same as the file already. |
