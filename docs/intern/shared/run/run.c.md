# src/shared/run/run.c

This file runs one command to its end with the calls of mosl: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-processes.

## The steps

1. `os_process_start` starts the program in `folder`, with `env`, and with `signals` and `ignore_interrupt` at `false`.
2. `os_process_close` closes the input at once, so a program that reads its input gets the end of it.
3. Each `os_process_read` takes the bytes that came on the output or on the errors. Thus one thread reads the 2 pipes.
4. The reads go on until the 2 pipes end, or until the time of `nanos` runs out.
5. If the time ran out, `os_process_kill` ends the process.
6. `os_process_wait` gives the status, and `os_process_free` frees the process.
7. Each `\r` before a `\n` goes from the buffers. Thus each line ends with `\n` on each system.

`os_get_now` tells the time from the start. Each read waits only for the time that is left.
A read waits while no pipe has bytes, so the run takes no time of a processor while the program works.

## Functions

| Function | Result |
| --- | --- |
| `run_command` | `true` and the result of the command, or `false` with no memory. |
| `read_pipes` | Reads the 2 pipes until they end or the time runs out. |
| `drop_returns` | Removes each `\r` that comes before a `\n`. |
