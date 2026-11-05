# src/read/read_targets.c

This file finds the target of this machine and the target of the run, and writes `mpbt:Target`: `docs/extern/mpbt_target.h.md`.

## The target of this machine

`runs_on` holds 2 names, for example `Linux` and `x86_64`. The machine of the program has the 2 names of the target of mpbt, which zig knows when it builds mpbt.
Thus the build of mpbt gives `read` these 2 names as 2 macros, and mosl needs no call for them.
A program under emulation gets the names of its own target too, as the tools of Python did.

`is_here` compares `runs_on` of each target with the 2 macros. The result is `here` of `mpbt:Target`.
`{home}` is the first target that is here. If the config lists no target with the `runs_on` of the program, `read` writes no `{home}`, and each `here` is `false`.

## The target of the run

`get_run_target` decides the target of the run by the command:

| Command | The target of the run | With no `--target` and no `{home}` |
| --- | --- | --- |
| `fetch` | `{home}`, also with `--target`. | The message of a fetch on a machine of no target. |
| `join`, `clean`, `distclean` | `--target`, or `{home}`. | The message that no target runs here. |
| `build`, `pack`, `test`, `check`, `runner` | `--target`, or `{home}`. | The message that no target runs on the system and the processor of the 2 macros. |

A `--target` that names no target stops the read. In `test`, a target that is not `{home}` stops it too.
These 5 messages are in `docs/extern/mpbt_target.h.md`, *Messages*. `cla` needs no target, because `read` writes only `mpbt:Command` there.
With `--target` and no `{home}`, the run goes on. Then the phase `load` writes its own message if a `[[load]]` needs the target of this machine.

## The keys of a target

Each table of `targets` in the config is a target: each target of `src/read/values.toml`, with the keys that the project adds.
`read_targets` adds the keys of each target to `targets` of `read_variables_t`, with no change to their values.
`read_write_targets` writes an entity with `mpbt:Target` for each target, in the order of the config.

## Functions

| Function | Result |
| --- | --- |
| `read_targets` | `true` after `{home}`, the target of the run and the keys of each target, or `false` and a finding. |
| `read_write_targets` | `true` after each entity of `mpbt:Target`, or `false` with no memory. |
| `get_run_target` | The target of the run, or a finding. |
| `is_here` | Whether `runs_on` of a target names this machine. |
