# src/fetch/fetch_download.c

This file gives the bytes of an archive from its address, with the program `curl`.

## The steps

1. For an address without `://`, `get_file_address` makes the address `file://` of that file of the project.
2. `os_path_find` finds `curl`. With no `curl`, the run stops.
3. `run_command` of `src/shared/run/run.h` runs `curl -fsSL <address>` in `{root}`, with `apart`. The bytes of its output are the archive.
4. If `curl` does not start, the run stops: `docs/extern/mpbt_command.h.md`, *Messages*.
5. A status of `curl` other than 0 stops the run, with the address and the status.
6. The name of the archive is the text after the last `/` of the address.

`-f` makes `curl` fail on an answer of an error, `-L` follows a move of the address, and `-sS` writes only the errors.
Thus a file of the project and a file of the network take one path, and give the same messages: `docs/extern/mpbt_source.h.md`, *Messages*.

## A file address

`get_file_address` starts with `file://`, then the path of the file from `{root}`, with `/` between its names.
A path of Windows starts with a drive, so a `/` comes before it.
A byte that an address cannot hold, for example a space or `%`, becomes `%` and its 2 hexadecimal digits.

## Functions

| Function | Result |
| --- | --- |
| `fetch_download` | `true` and the archive, or `false` and a finding. |
| `get_file_address` | `true` and the address `file://` of a file of the project, or `false` with no memory. |
