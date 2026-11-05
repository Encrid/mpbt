# src/test/test_plain.c

This file runs the command `test` with no `--branches` and no `--leaks`. The module `build` made each artifact in the phase `build` before it.

## The steps

1. `test_check_linked` stops the run if an artifact is not linked.
2. If the world holds no case, the run writes the line of `docs/extern/mpbt_case.h.md`, *Messages*, with `cases` of `mpbt:Tests`. It ends with no finding.
3. `test_pick_cases` keeps the cases of `--part` and of `-k`.
4. `get_copies` gives the copies of each case.
5. `test_check_patterns` checks the patterns of each case, before the first case runs.
6. If `test_needs_fail` tells that a use states `fail`, `test_run_fail` makes the run `fail` into `failing`.
7. `test_run_rounds` runs the cases, one round after the other.
8. If each case passed in a full run, `test_check_said` checks the messages, when `writers` of `mpbt:Tests` names a function.

A full run is a run with none of `--break`, `-k` and `--part`: `docs/extern/mpbt_case.h.md`, *The messages of the code*.
The run takes `{out}` of the build, and the output of each artifact from its `mpbt:Built`.

## The copies

`copies` of `mpbt:Command` counts with `--copies`. Else `copies` of `mpbt:Tests` counts.
If neither gives a number, the finding is the message about `[test] copies` of `docs/extern/mpbt_case.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `test_run_plain` | `true`, or `false` when the run stops. |
| `get_copies` | The copies of each case, or 0 after a finding. |
| `is_full` | Whether the run checks the messages of the code. |
