# src/shared/path/path_read.c

This file reads the whole file of a path into a `buffer_t`, with the calls of mosl that read a folder: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-folders.

## The steps

1. `split_path` cuts the path at its last `/` or `\`. The part before it is the folder, and the part after it is the name.
2. A path with no separator names a file of the current folder, `.`.
3. `os_folder_open` opens the folder, and `os_folder_read_file` reads the name.
4. The bytes belong to the folder, so `buffer_add` copies them into the `buffer_t` of the caller.
5. `os_folder_close` closes the folder, also after a read that failed.

Thus a file can be past the path limit of the system: mosl opens the name from its folder.
The `buffer_t` gets the bytes after the bytes that it holds, so a caller clears it first with `buffer_clear` to read a new file.

## The result

| Result | Meaning |
| --- | --- |
| 0 | The buffer holds the bytes of the file. |
| 1 | No file reads at the path: it is not there, it is a folder, or the system refuses the read. |
| -1 | The buffer cannot grow. |

`path_read` writes no finding. Each caller writes the fault of its own work, for example one of `docs/extern/mpbt_command.h.md`, *Messages*.
A caller that must tell a file that is not there from a file that does not read asks `os_path_entry` first.

## Functions

| Function | Result |
| --- | --- |
| `path_read` | 0 and the bytes of the file, 1, or -1, as *The result* tells. |
| `split_path` | The count of the bytes of the folder, and where the name starts. |
