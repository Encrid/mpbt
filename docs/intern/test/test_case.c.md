# src/test/test_case.c

This file runs one copy of a case: its files, its helper, its command and its script, as `docs/extern/mpbt_case.h.md`, *[[case]]*, gives the order.

## The steps

1. `test_place` empties `{case}`, and puts the files and the folders of the use into it.
2. With a helper, `start_helper` starts it. `test_wait_line` then reads its output up to its text `wait`.
3. `start_command` starts the command, and `test_do_script` does the steps of the script.
4. `test_end` gives the command its `input`, then gets its end.
5. With a helper, `end_helper` does the same with `helper_input`, after the end of the command.

A use has a helper if `helper_run` has one item or more.
The texts of the use get the variables of the copy first: `run` and `helper_run` with `variables_expand_items`, each other text with `variables_expand`.
A text whose expansion fails keeps its finding in `fault`, and the copy stops.

## How a command starts

| Field of `os_process_start_t` | The command | The helper |
| --- | --- | --- |
| `argv` | The items of `run`. | The items of `helper_run`. |
| `folder` | `{root}`. | `{root}`. |
| `env`, `unset` | From `test_make_env`, with `C23_FAIL`. | From `test_make_env`, with no `C23_FAIL`. |
| `errors_apart` | `false`: the errors go into the output, in their order. | `false`. |
| `signals` | `true` if a step of the script sends a signal. | `false`. |
| `ignore_interrupt` | `ignore_interrupt` of the run. | `false`. |

If the system does not start a program, the copy keeps the fault with `argv[0]`: `docs/extern/mpbt_command.h.md`, *Messages*. The copy then stops.
The end of each command goes into `ends` of the copy, the command first.

## Functions

| Function | Result |
| --- | --- |
| `test_run_case` | Runs one copy. |
| `start_helper` | The helper that runs, after its text `wait`, or none. |
| `start_command` | The command that runs, or none after a fault. |
| `end_helper` | The end of the helper. |
| `has_signal` | Whether a step of the script sends a signal. |
