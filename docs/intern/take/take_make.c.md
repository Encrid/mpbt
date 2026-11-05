# src/take/take_make.c

This file runs the command `make` of a dependency, before `take` reads its list: `docs/extern/mpbt_dependency.h.md`, *[[dependency]]*.

## The steps

1. `run_command` of `src/shared/run/run.h` runs the items of `make` in `{root}`. The errors go into the output, with no time limit.
2. After a status of 0, the output goes to `say`, if the command printed a byte.
3. Else `run_add_fault` writes the command, the line of its status and the output, and `finding_write` gives it as one finding.

The text of the fault has the form of `docs/extern/mpbt_kind.h.md`, *Messages*, with its lines in one finding.
A program that does not start gives the fault too, with the message of `docs/extern/mpbt_command.h.md`, *Messages*. Then `take` reads no list.

## Functions

| Function | Result |
| --- | --- |
| `take_make` | `true` after a command that ended with 0, or `false` and a finding. |
