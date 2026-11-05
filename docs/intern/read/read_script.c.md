# src/read/read_script.c

This file checks the steps of a script, and writes an entity with `mpbt:ScriptStep` for each step: `docs/extern/mpbt_case.h.md`, *Scripts*.

## The checks

`check_step` checks each step in the order of the script. It keeps 2 facts from the earlier steps: whether a step closed the output, and whether a step sent a hang-up.

1. `toml_doc_check_keys` checks the keys of the step.
2. A `wait` after a `close` is a fault.
3. `close` holds only `"output"`.
4. `get_signal` gives the constant of `signal`. A different signal is a fault.
5. A signal after a hang-up is a fault.
6. `pause` is a number above 0, and not a bool.

The first fault stops the read, with its message of `docs/extern/mpbt_case.h.md`, *Messages*.
`read_case` checks the script of the case, and the script of its false variant.

## The entities

`write_step` writes each step in the order of the script:

| Field | Value |
| --- | --- |
| `owner` | The id of the entity that owns the script: a case, or a false variant. |
| `wait`, `type` | The texts, with their variables. |
| `put` | A map from each path to the artifact or the file that goes there. |
| `remove` | A list of the files. |
| `pause` | The seconds, as a `double`, also from an integer. |
| `order` | The place of the step in the script, from 0. |
| `signal` | `MPBT_SIGNAL_INTERRUPT`, `MPBT_SIGNAL_TERMINATION` or `MPBT_SIGNAL_HANG_UP`. |
| `actions` | The bit of each key that the step gives. `close` gives `MPBT_SCRIPT_CLOSE` and no field. |

## Functions

| Function | Result |
| --- | --- |
| `read_write_script` | `true` after the steps of one script, or `false` and a finding. |
| `check_step` | `true` for a step that *The checks* allow, else `false` and its finding. |
| `write_step` | `true` after one entity of `mpbt:ScriptStep`, or `false` with no memory. |
| `get_signal` | The constant of a signal, or 0 for a different text. |
