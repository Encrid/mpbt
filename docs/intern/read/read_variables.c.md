# src/read/read_variables.c

This file collects the variables of the run into `read_variables_t`, and makes the `variables_t` of a target: `docs/extern/mpbt_project.h.md`, *Variables*.

## The order

`read_variables` adds the entries of `project` in this order. A later entry replaces an earlier entry with the same name.

1. `add_built_ins` adds `{root}`, `{build}`, `{dist}`, `{out}`, `{target}`, `{home}` and `{toolchain}`. With no target of this machine, it adds no `{home}`.
2. `read_own` adds the keys of `[variables]`, with `--debug` and `--set`.
3. `read_add_sources` adds a variable for each source, and one for each dependency.
4. `read_tools` adds the variable of each tool, and `read_zig` adds `{zig}`.

The keys of the targets are apart, in `targets`. `read_targets` adds them first, because `read_own` compares the names of `[variables]` with them.
`read_paths` adds `{paths}` later, because it needs the names of the artifacts: `docs/intern/read/read_paths.c.md`.

## The built-in variables

| Variable | Value |
| --- | --- |
| `{root}` | `--root`, or the current folder, made whole by `os_path_whole`. |
| `{build}` | `--out`, made whole by `os_path_whole`, or `<root>/build`. |
| `{dist}` | `<build>/<target>`, and `-debug` after it with `--debug`. |
| `{out}` | `<dist>/scratch`. |
| `{target}` and `{home}` | The targets that `read_targets` found. |
| `{toolchain}` | The folder `toolchain` in the folder of `os_get_program_path`, from `path_join` of `src/shared/path/path.h`. |

Each path has `/` between its names, also on Windows, where `add_built_ins` replaces each `\`.

## The names of the later phases

The build and the test give some variables only when they make an artifact or run a case: `docs/extern/mpbt_kind.h.md`, *Steps*, and `docs/extern/mpbt_case.h.md`, *[[case]]*.
A key of a target can hold such a name, for example `{name}` in `soname`.
`read` gives these names to `variables_expand` as the names of a later phase: `docs/intern/shared/variables/variables_expand.c.md`, *The names of a later phase*.
Thus `read` replaces only the variables that it gives, and the build or the test replaces the others.

## The variables of a target

`read_get_variables` makes the `variables_t` of one target in these steps:

1. The keys of that target go in first.
2. Each entry of `project` goes in after them, and replaces a key with the same name.
3. The name of that target replaces `{target}`.
4. `variables_sort` sorts the entries by name.

`run_variables` of `read_t` holds the result for the target of the run, for the whole run.
A different target gets its own result only when an artifact names that target.
A `variables_t` points to the values of `read_variables_t`. Only its array of entries is its own, and the caller gives it back with `free`.

## Functions

| Function | Result |
| --- | --- |
| `read_variables` | `true` after each variable of the order, or `false` and a finding. |
| `add_built_ins` | `true` after the built-in variables, or `false` with no memory. |
| `read_add_variable` | Adds one entry, or replaces the entry with the same name. |
| `read_get_variables` | `true` and the `variables_t` of one target, or `false` with no memory. |
| `read_free_variables` | Gives the memory of `read_variables_t` back. |
