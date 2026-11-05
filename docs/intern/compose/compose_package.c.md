# src/compose/compose_package.c

This file writes `{out}/package.txt`: `docs/extern/mpbt_compose.h.md`, *package.txt*.

## The steps

1. A project with no name stops the system with its fault of `docs/extern/mpbt_project.h.md`, *Messages*.
2. The first line names the project, and the second line names the target of the run.
3. Each file of `files` of each `mpbt:Built` gives a line, if its artifact has `test` at `false`.
4. A line holds the digest of the file, 2 spaces, then the path of the file below `{out}`.
5. `path_read` reads the file. If the read fails, the system stops.
6. `sha256_start`, `sha256_add` and `sha256_end` make its digest, and `sha256_get_hex` writes it.
7. A file that 2 artifacts list gives one line. The lines of the files come in the order of `files_compare`.
8. `os_folder_make` makes `{out}`, and `os_file_write` writes the lines, each with `\n` at its end.
9. If one of these 2 calls fails, the system stops.

The faults of a read and of a write are in `docs/extern/mpbt_command.h.md`, *Messages*.

The order of the paths is the same on each run, since it does not depend on the order of the rows.

## Functions

| Function | Result |
| --- | --- |
| `compose_write_package` | 0 when `package.txt` is written, or 1 after a fault. |
| `add_line` | Adds the line of one file. |
