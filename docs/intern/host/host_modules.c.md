# src/host/host_modules.c

This file puts the libraries of the modules of mpbt and of BB-Native into `{toolchain}/modules`, so that BB-Native loads each one by its path.

## The libraries

The program holds each library as bytes, with `#embed` of C23. The build makes the libraries before the program.
`sha256_start`, `sha256_add` and `sha256_end` give the digest of each library, and `sha256_get_hex` gives its text.
The file of a library is `{toolchain}/modules/<digest><suffix>`, with the suffix of a library of the system.
Thus a new version of a library gets a new file, and a file that is there holds the right bytes.

## The steps

1. `os_get_program_path` gives the program, and `{toolchain}` is the folder `toolchain` beside it.
2. `os_folder_make` makes `{toolchain}/modules`.
3. For each library, `os_path_entry` tells whether its file is there.
4. If it is not there, `os_file_write` writes the bytes into a file of a name of its own.
5. Then `os_path_move` gives that file the name of the library. Thus 2 runs of mpbt at the same time do not see half a library.
6. A folder that takes no file stops mpbt, with its message of `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `host_modules` | The path of each library, or 1 after a message. |
| `put_library` | Writes one library if its file is not there. |
