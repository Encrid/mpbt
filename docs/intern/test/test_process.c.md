# src/test/test_process.c

This file starts a command of a copy, reads its output, writes to its input, and waits for its end.
One read of mosl gives the next bytes of the output or of the errors: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-processes.

## The time of a command

`test_start` sets the deadline of the command: the start, then `timeout` of `mpbt:Tests` in seconds, by the clock of `os_get_now`.
Each read and each wait of the command waits at most the time that is left before the deadline.
A write has no time limit in mosl. Thus `test_timer_start` also starts the timer that kills the command at the deadline.

## The output

`test_read` adds the bytes of each read to the output of the command, with no `\r`.
The output holds the errors too, in the order of the writes, because the command starts with `errors_apart` at `false`.

| Result of `os_process_read` | `test_read` |
| --- | --- |
| `OS_OUTPUT` or `OS_ERRORS` | Adds the bytes, and gives 1. |
| 0 | The output ended: it gives 0. |
| -1 | The read failed: it gives -1. |
| -2 | The time passed: it gives -2. |

## The steps of the end

1. `test_end` writes the text of `input` with `os_process_write`, then closes the input with `os_process_close`.
2. It reads the output until it ends, or until the deadline. A step `close` ended it already.
3. `test_timer_stop` stops the timer. From here, no other thread acts on the process.
4. `os_process_wait` waits for the end, with the time that is left.
5. The command is late if the timer killed it, or if it still runs at the deadline.
6. `os_process_free` kills a command that still runs, and frees it.

`test_wait_line` reads until a line of the output holds its text, from the byte `seen` on. At the end of the output, the last line counts too, also with no line end.
`test_type` writes its text and `\n`. A write into an input that the command closed does not stop the copy, because the claims judge what the command did.

## Functions

| Function | Result |
| --- | --- |
| `test_start` | A `test_running_t`, or none if the program does not start. |
| `test_read` | 1, 0, -1 or -2, as *The output* tells. |
| `test_wait_line` | `true` if a line holds the text, or `false` if the output ends first. |
| `test_type` | Writes a text, then `\n`, into the input. |
| `test_end` | The `test_end_t` of the command. |
