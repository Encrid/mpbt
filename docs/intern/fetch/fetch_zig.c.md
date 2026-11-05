# src/fetch/fetch_zig.c

This file gets zig when the zig of `{zig}` is not there, and writes its path: `docs/extern/mpbt_source.h.md`, *zig*.

## The pin

The pin of zig is in `src/shared/zig/zig.h`: `ZIG_VERSION`, and a row with a host, a form and a digest for each target.
`zig_find_archive` gives the row of `{home}`, and `zig_add_address` gives the address of its archive.

## The steps

1. `is_zig_there` runs `{zig} version` with `run_command` of `src/shared/run/run.h`. If the output is `ZIG_VERSION`, go to step 7.
2. `zig_find_archive` gives the row of `{home}`. With no row, the run stops.
3. `os_path_remove` removes the folder of `{zig}`, and `os_folder_make` makes it again.
4. `fetch_download` gives the archive. A digest that is not the digest of the row stops the run.
5. `fetch_unpack` puts the files of the folder `zig-<host>-<version>` of the archive into the folder of `{zig}`.
6. `is_zig_there` checks `{zig}` again. A different output stops the run.
7. `say` writes `{zig}`.

`read` gives `{zig}` the path beside the program when no zig of the version is there: `docs/intern/read/read_zig.c.md`.
Thus step 1 finds the zig that `read` chose, and the steps 3 to 5 put zig where `{zig}` names it.
The messages are in `docs/extern/mpbt_source.h.md`, *Messages*. A folder that does not take a file gives the message of `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `fetch_zig` | `true` after the line of zig, or `false` and a finding. |
| `is_zig_there` | Whether `{zig}` writes `ZIG_VERSION`. |
