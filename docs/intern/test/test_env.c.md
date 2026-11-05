# src/test/test_env.c

This file makes the arrays `env` and `unset` of `os_process_start_t` for the command or the helper of a copy.
The process gets the environment of mpbt with these changes: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-processes.

## The changes

| Variable | The command | The helper | Value |
| --- | --- | --- | --- |
| Each key of `env` of the run | Yes | No | `NAME=value`, with the variables of the copy in the value. |
| Each item of `unset` of the run | Yes | No | The name goes. |
| `C23_FAIL` | Yes | No | A space, then `<function>=<number>`, for each pair of `fail`. A run with no `fail` removes the variable. |
| `C23_LEAKS` | In the run `leaks` | In the run `leaks` | The folder of the copy, then `.leaks`. |
| `C23_BRANCHES` | In the run `branches` | In the run `branches` | The file of the hits. |

The code of the copies reads these 3 variables: `test_fail.c`, `test_count_write.c` and `test_probe_write.c`.
A key of `env` or an item of `unset` with the name of such a variable replaces it.
Thus a case of mpbt itself can state `env` for the program of a different run.

The removal of `C23_FAIL` keeps a plan of failed calls in the place where the case states it.
For example, `mpbt` that runs with a plan does not give that plan to the commands of its own cases.

## Functions

| Function | Result |
| --- | --- |
| `test_make_env` | The arrays `env` and `unset`, with `nullptr` after the last item, or `false` after a fault. |
| `test_free_env` | Gives the texts and the arrays back. |
| `add_change` | Adds one `NAME=value`, if `env` and `unset` of the case do not name it. |
| `make_plan` | The value of `C23_FAIL`. |
