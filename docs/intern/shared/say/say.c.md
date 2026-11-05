# src/shared/say/say.c

This file writes each line of mpbt whole: `docs/extern/mpbt_finding.h.md`, *The report*.

## The steps

1. `say_format` measures the line with `vsnprintf`, and makes it in a `buffer_t`.
2. `say` copies the bytes and one line end into a `buffer_t`.
3. `os_output_write` of mosl gives the whole line to the standard output, with one call of the system.

The line end is LF alone on each system, because mosl writes the bytes with no text mode. Thus `bash -e` reads the output of `runner` on Windows too.
No `FILE` of the C library holds a line. So each line comes at once, also from a module that links its own C library.
The line of a signal of mosl takes the same path: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-signals.
`os_output_write` comes with the next version of mosl.

## The limits

- Each line is one call of the system, so the lines of 2 threads stay apart.
- On a pipe, a line of more than `PIPE_BUF` bytes can mix with a line of another process. `PIPE_BUF` is 4096 bytes on Linux.
- If the buffer cannot grow, `say` writes the bytes and the line end with two calls. Thus the line still comes, but another line can come between its parts.
- A write that fails loses its line, and mpbt goes on. The exit status still tells the result of the run.

## Functions

| Function | Result |
| --- | --- |
| `say` | Writes the bytes and a line end, with one call of `os_output_write`. |
| `say_format` | Makes the line with `vsnprintf`, then writes it as `say` does. |
