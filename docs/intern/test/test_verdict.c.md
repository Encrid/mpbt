# src/test/test_verdict.c

This file gives the verdict of one copy, and writes the lines of a case and of a group with `say_format`.
The verdicts are in `docs/extern/mpbt_case.h.md`, *Verdicts*. The lines are in `docs/extern/mpbt_case.h.md`, *Messages*.

## The verdict of a copy

1. If the command or the helper is late, the verdict names the `timeout` of `mpbt:Tests`. The copy fails, also with `--break`.
2. Else `test_hold_claims` judges the command by the claims of the case, and the helper by its own claims.
3. With `--break`, the copy passes if a claim does not hold: the verdict is `fails, as it must`, else `still as written`.
4. With no `--break`, the copy passes if each claim holds: the verdict is `as written`, else `differs`.

A fault of the variables of a claim stops the verdict, and the copy keeps the fault.

## The lines of a case

`test_say_case` writes the name of the case and its verdict. With `--break`, the name gets `, made false` after it.
For a case that failed, `say_end` writes the status and the output of the command, then of the helper if the copy had one.
`run_add_status` of `src/shared/run/run.h` writes the status, in the form that the steps of a kind use too.
A late command has `no status`. The output loses its white space at its end, and goes out with the line before it, as one call of `say`.

## Functions

| Function | Result |
| --- | --- |
| `test_judge` | The verdict of a copy, and whether it passes. |
| `test_say_case` | The lines of a case. |
| `test_say_group` | The line of a group: the count of its chosen cases, and how many passed. |
| `say_end` | The status and the output of one command. |
