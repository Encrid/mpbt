# src/build/build_load.c

This file builds the modules of `[[load]]` for this machine, and writes their list for the host: `docs/extern/mpbt_load.h.md`, *The modules of a project*.

## The steps

For each table `[[load]]`, in the order of its field `order`, `build_list_loads` does these steps:

1. With `MPBT_LOAD_FILE`, `path_join` puts `file` after the folder of the project. `os_path_entry` must find a file there.
2. With `MPBT_LOAD_ARTIFACT`, an artifact must have the name `artifact`.
3. `steps_read_input` reads its row. Its target is the target of this machine.
4. `steps_make` builds the artifact in the place of `load_artifacts`.
5. A module that is not linked is a fault, with the message of a kind with no `unlinked` steps.

Then `os_file_write` writes the paths into the file of `load_list`, one on each line, in the order of the tables. Each path is whole.
A list that cannot be written is a fault: `docs/extern/mpbt_command.h.md`, *Messages*.
With no table `[[load]]`, the system writes no file.
The place is in `docs/intern/shared/steps/steps.h.md`, *steps_place_t*.
The messages are in `docs/extern/mpbt_load.h.md`, *Messages*, and in `docs/extern/mpbt_kind.h.md`, *Messages*.

## The target of this machine

The target of this machine is the row of `mpbt:Target` with `here` at `true`. With no such row, the first artifact is a fault.
That fault is in `docs/extern/mpbt_target.h.md`, *Messages*, for a command that needs the target of this machine.
A table with `MPBT_LOAD_FILE` needs no target, since nothing builds it.

## The reasons

The place of `load_artifacts` is `<build>/load`, and not `{out}`. Thus the phase `build` never writes over a library that the host loaded.
The host can only load a linked module. Thus a module whose `link` names a file that is not there is a fault.

## Functions

| Function | Result |
| --- | --- |
| `build_list_loads` | 0 when the list is written, or 1 after a fault. |
| `find_artifact` | The row of `mpbt:Artifact` with a given name, or none. |
| `build_module` | The path of the module of one table, which it builds first for an artifact, or 1 after a fault. |
| `write_list` | Writes the paths into the file of `load_list`. |
