# src/fetch/fetch_sources.c

This file gets each source that is not fetched, and checks that each source is fetched: `docs/extern/mpbt_source.h.md`, *fetch*.

## The paths

`path_join` of `src/shared/path/path.h` puts `into` and each patch after `{root}` when they are not whole. `clean` starts `into` in the same way.
The folder `top` is in `into`: `into`, `/`, then `top`, if `top` holds a byte.

## The stamp

`get_stamp` makes the stamp of a source: `sha256` of its row, then the digest of each patch, with a space between 2 digests.
`path_read` reads each patch. The digest comes from `sha256_start`, `sha256_add`, `sha256_end`, then `sha256_get_hex`.
If a patch does not read, `get_stamp` stops the run: `docs/extern/mpbt_command.h.md`, *Messages*.
`is_fetched` reads `fetched.txt` of `into` with `path_read`, and tells whether it holds the stamp and no other byte.

## Get the sources

`fetch_sources` does these steps for each source, in the order of the rows:

1. If `is_fetched` tells yes, the source is there, and the next source follows.
2. `os_path_remove` removes the folder `into`, and `os_folder_make` makes it again.
3. `fetch_download` gives the archive. A digest that is not `sha256` stops the run.
4. `fetch_unpack` puts each file of the archive into `into`.
5. `fetch_patch` applies each patch to the folder `top`, in the order of the list.
6. `os_file_write` writes the stamp into `fetched.txt` of `into`.

The archive stays in memory, so no file of it stays in `into`. A source writes no line.
The steps 2 and 6 stop the run if the system refuses the folder or the file: `docs/extern/mpbt_command.h.md`, *Messages*.

## Check the sources

`fetch_check_fetched` asks `is_fetched` for each source. Each source that is not fetched gets its finding, and the check goes on.
Thus one run of `build`, `pack` or `test` names each source to fetch.
The messages are in `docs/extern/mpbt_source.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `fetch_sources` | `true` after each source, or `false` and a finding. |
| `fetch_check_fetched` | `true` if each source is fetched, or `false` and a finding for each other source. |
| `fetch_source` | `true` after the steps 2 to 6 of one source, or `false` and a finding. |
| `get_stamp` | `true` and the stamp of a source, or `false` and a finding. |
| `is_fetched` | Whether `fetched.txt` of a source holds its stamp. |
