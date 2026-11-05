# src/runner/runner.h

This private header declares the machine of a target, and the functions that the files of `src/runner` share.

## runner_machine_t

| Field | Value |
| --- | --- |
| `system` | Item 0 of `runs_on`: `Linux`, `Windows` or `Darwin`. |
| `processor` | Item 1 of `runs_on`, for example `AMD64` or `ARM64`. |

Each field is the bytes of the item in the shared memory, with their count.

## Functions

| Function | File |
| --- | --- |
| `runner_get_machine` | `runner_machine.c` |
| `runner_write_commands` | `runner_commands.c` |
