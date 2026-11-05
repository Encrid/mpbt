# src/test/test_script.c

This file does the steps of the script of a use while its command runs. Each step does its actions in the order of `docs/extern/mpbt_case.h.md`, *Scripts*.

## The actions

| Bit of `actions` | What `do_step` does |
| --- | --- |
| `MPBT_SCRIPT_WAIT` | `test_wait_line` reads up to a line with the text. If the output ends first, the script stops. |
| `MPBT_SCRIPT_PUT` | `put_files` copies the file of each item to its path, with `test_find_item` and `copy_file`. |
| `MPBT_SCRIPT_REMOVE` | `os_path_remove` removes each path of the list. A path with nothing there is no fault. |
| `MPBT_SCRIPT_TYPE` | `test_type` writes the text. |
| `MPBT_SCRIPT_CLOSE` | `os_process_close` closes `OS_OUTPUT`. |
| `MPBT_SCRIPT_SIGNAL` | `send_signal` sends the signal with `os_process_signal`. |
| `MPBT_SCRIPT_PAUSE` | `pause_step` reads the output for the seconds of `pause`. |

A step expands its texts and its paths with the variables of the copy. `path_join` puts `{root}` before a relative path, as for `files`.
A pause reads the output while it waits, so that the pipe of the output does not fill. The bytes go into the output, as with each read.

## The signals

| `mpbt_signal_t` | Signal of mosl |
| --- | --- |
| `MPBT_SIGNAL_INTERRUPT` | `OS_INTERRUPT` |
| `MPBT_SIGNAL_TERMINATION` | `OS_TERMINATION` |
| `MPBT_SIGNAL_HANG_UP` | `OS_HANG_UP` |

The command started with `signals`, because its script sends a signal: `test_case.c`.
If `os_process_signal` does not give 0, the copy keeps the fault of `docs/extern/mpbt_case.h.md`, *Messages*, with `argv[0]` and the signal. The script then stops.

## Functions

| Function | Result |
| --- | --- |
| `test_do_script` | `true` after the steps, or `false` after a fault. |
| `do_step` | The actions of one step. |
| `put_files` | The copies of one step `put`. |
| `send_signal` | `true` if the command got the signal. |
| `pause_step` | Reads the output for the time of a pause. |
