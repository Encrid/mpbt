# src/read/read_project.c

This file writes `mpbt:Project` and `mpbt:Variable`, and adds the variables of `[variables]` and of `[tools]`: `docs/extern/mpbt_project.h.md`.

## The project

`read_project` takes `[project] name`, and `path_read` of `src/shared/path/path.h` gives the bytes of `.toolchain/header.txt` of the root.
The name gets the values of its variables from `run_variables`, as each text of the config does.
A name that is not there gives a text with no bytes. The module that needs the name writes the finding.
A legal notice that is not there gives a text with no bytes too. `read` only writes it: the checks compare the files with it.

## The own variables

`read_own` adds the keys of `[variables]` to the variables of the run, in these steps:

1. A key with the name of a built-in variable or of a key of a target stops the read.
2. Each other key goes in, with its text or its list.
3. With `--debug`, each key of `[debug]` of the values of mpbt replaces its key.
4. Each line of `--set` replaces the value of its name with a text. A name that `[variables]` does not give stops the read.

The 4 keys that mpbt gives are in `[variables]` of `src/read/values.toml`. Thus `--set` can replace them too.
The messages are in `docs/extern/mpbt_project.h.md`, *Messages*.

## The tools

`read_tools` takes each key of `[tools]`. Its variables get their values, and `path_join` starts a relative path in `{root}`.
`os_path_find` finds the program with the extensions of this machine, and the variable gets its full path, with `/`.
A program that is not there stops the read, with its message of `docs/extern/mpbt_project.h.md`, *Messages*.

## The written variables

`read_write_variables` writes an entity with `mpbt:Variable` for each variable:

| Variables | `scope` | `target` | `value` |
| --- | --- | --- | --- |
| Each entry of `project` of `read_variables_t`, also each built-in variable | `MPBT_SCOPE_PROJECT` | No bytes. | The value for the target of the run. |
| Each key of each target, also `runs_on` | `MPBT_SCOPE_TARGET` | The name of the target. | The value for that target. |

A text gives `MPBT_VALUE_TEXT`, and a list gives `MPBT_VALUE_LIST`. Thus the modules that read a built-in variable, for example `clean` and `runner`, find it as a row.
The value replaces its variables with `variables_expand` or `variables_expand_items`, with the `variables_t` of its target.

## Functions

| Function | Result |
| --- | --- |
| `read_project` | `true` after the attach of `mpbt:Project`, or `false` with no memory. |
| `read_own` | `true` after the keys of `[variables]`, of `[debug]` and of `--set`, or `false` and a finding. |
| `read_tools` | `true` after the variable of each tool, or `false` and a finding. |
| `read_write_variables` | `true` after each entity of `mpbt:Variable`, or `false` and a finding. |
