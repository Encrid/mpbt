# src/shared/steps/steps_run.c

This file does the action `run` of a step: it runs the command with `run_command`, and writes what the command printed.

## The folder

1. The folder of a command is `cwd`, or the folder of the project with no `cwd`.
2. `path_join` puts a relative `cwd` after the folder of the project.
3. If `os_path_entry` finds no folder at `cwd`, the step stops with its fault.
4. With `cwd`, the items get their variables from a copy of the variables of the plan.
5. In that copy, each item of `{sources}` and each folder of `{include}` is a whole path.

## The caches of zig

`steps_get_caches` gives the texts `ZIG_GLOBAL_CACHE_DIR=<folder>` and `ZIG_LOCAL_CACHE_DIR=<folder>`, for `env` of `run_t`.
The folders are those of `docs/extern/mpbt_kind.h.md`, *Steps*. The folder of the program comes from `os_get_program_path`.

If a cache is in the folder of the project, its variable is a path from that folder. Thus an archive of zig names its members with no folder of the machine.
With `cwd`, each one is a whole path. `test` gives its dumps of zig the same caches.

## The command

1. The items of `run`, with their variables replaced, are `argv`. The first item names the program.
2. `apart` is `false`, and `nanos` is `OS_FOREVER`: a step has no time limit.
3. With the status 0, `say` writes the output, if the command printed a byte.
4. Else `run_add_fault` writes the text of the command into `fault`.

## Functions

| Function | Result |
| --- | --- |
| `steps_run` | 0 when the command ends with 0, or 1 after a fault. |
| `steps_get_caches` | The 2 variables of the caches of zig, for the folder of a command. |
| `make_whole` | The copy of the variables with whole paths, for `cwd`. |
