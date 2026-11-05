# src/read/read_files.c

This file gives each file of the project an entity with `mpbt:File`, in `check` and in `test`: `docs/extern/mpbt_file.h.md`, *The files of the project*.

## The top of a repository

`is_top` runs `git rev-parse --show-prefix` in `{root}` with `run_command` of `src/shared/run/run.h`, with `apart`.
If git ends with 0 and writes only a line end, `{root}` is the top of its repository.
A status other than 0 tells that `{root}` is in no repository. An output with a path tells that `{root}` is a folder inside one.
A git that does not start stops the read: `docs/extern/mpbt_command.h.md`, *Messages*.

## The list

- At the top of a repository, `list_files` runs `git ls-files -z -co --exclude-standard` in `{root}`. With `-z`, a zero byte ends each path, so a name with a space or a quote stays whole.
- A status of git other than 0 stops the read with the errors of git, in the message of `docs/extern/mpbt_file.h.md`, *Messages*.
- Else `walk_files` gives the glob `**/*` to `glob_files` of `src/shared/glob/glob.h`, which gives each file under `{root}`.
- If `{build}` is inside `{root}`, `walk_files` leaves out each path that starts with the path of `{build}` from the root and a `/`.

## The files

For each path of the list, in its order:

1. `os_path_entry` leaves out a path with no file, for example a file that git tracks and that a person removed.
2. `path_read` of `src/shared/path/path.h` gives the bytes of the file.
3. `write_file` puts the path and the bytes into the arena, takes an id with `spawn`, and attaches `mpbt:File`.

The files of `tests` are among them, because `xref` and `text` read them.
The read stops at the first file that `path_read` cannot read: `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `read_files` | `true` after each entity of `mpbt:File`, or `false` and a finding. |
| `is_top` | `true` and whether `{root}` is the top of a repository, or `false` and a finding. |
| `list_files` | `true` and the paths that git gives, or `false` and a finding. |
| `walk_files` | `true` and each path under `{root}` but those of `{build}`, or `false` with no memory. |
| `write_file` | `true` after one entity of `mpbt:File`, or `false` with no memory. |
