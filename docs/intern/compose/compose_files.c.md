# src/compose/compose_files.c

This file gives the files of one deliverable, in the 4 groups of `docs/extern/mpbt_compose.h.md`, *The deliverable*.

## The groups

1. Each artifact of the deliverable that ships gives each file of its `mpbt:Built`, by its name with no folder.
2. Each table of `[compose]` of the deliverable gives its headers, which `glob_files` finds below `from`. Each header goes into `into`, with its path below `from`.
3. Each item of `assets` of these tables gives the file `{out}/<item>`, by its name with no folder.
4. Last come `license` of the root, if it is there, and the licences of `third_party`, at their paths.

`path_join` puts a relative `from` after the folder of the project.

An artifact or a table of `[compose]` is of the deliverable of a part if its `part` is that part. In a project with no parts, each one is of the deliverable of the project.
For a part, the licences of `third_party` are the file `license` of each folder of its list `third_party`. A licence that is not there is a fault.
For the project, `glob_files` finds them: the file `license` of each folder of `third_party` that has one.
An artifact that is not linked has no file in `mpbt:Built`, so it adds no file.

## --leave

With `--leave`, `compose_remove_file` takes the file of that name out of the list. A name that the list does not hold is a fault.
The messages are in `docs/extern/mpbt_compose.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `compose_get_files` | The files of one deliverable, or 1 after a fault. |
| `add_artifacts` | Adds the files of the artifacts. |
| `add_tables` | Adds the headers and the assets of the tables of `[compose]`. |
| `add_licences` | Adds `license`, and the licences of `third_party`. |
