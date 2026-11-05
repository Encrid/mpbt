# src/shared/run/run.h

This header declares the run of one command through the calls of mosl, and the text of a command that failed.
`steps` runs the commands of the steps with it, and `pack` runs its proof. `cla`, `commits` and `read` run their programs with it.
The dumps of `test` do not use it: `run_command` keeps all the output in memory, and a syntax tree can hold some hundred MB. So `test` reads a dump as a stream.

## run_t

`run_t` is the one argument of `run_command`: the command and its limits.

| Field | Value |
| --- | --- |
| `argv` | The arguments, with `nullptr` after the last. `argv[0]` names the program. |
| `folder` | The folder in which the command runs. |
| `env` | The variables that change, each as `NAME=value`, with `nullptr` after the last. |
| `apart` | `true`: the errors go into `errors`. `false`: they go into `output`, in the order that the program writes them. |
| `nanos` | The longest time of the command, in nanoseconds, or `OS_FOREVER`. |

## run_result_t

| Field | Value |
| --- | --- |
| `started` | `false` if the program did not start. |
| `ended` | `false` if the time ran out, so that the command was killed. |
| `status` | The status that `os_process_wait` gives. |
| `output` | A `buffer_t`: the output, and also the errors when `apart` is `false`. |
| `errors` | A `buffer_t`: the errors, when `apart` is `true`. |

The caller frees the 2 buffers with `buffer_free`.

## Functions

| Function | File |
| --- | --- |
| `run_command` | `run.c` |
| `run_add_fault` | `run_fault.c` |
| `run_add_status` | `run_fault.c` |

`run_add_status` writes a status in the form of `docs/extern/mpbt_kind.h.md`, *Messages*. `test` writes the status of a case that failed with it too.
