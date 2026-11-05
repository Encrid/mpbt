# src/shared/say/say.c

This file writes each line of mpbt whole: `docs/extern/mpbt_finding.h.md`, *The report*.

## The steps

1. `say_format` measures the line with `vsnprintf`, and makes it in a `buffer_t`.
2. `say` copies the bytes and one line end into a `buffer_t`.
3. One `fwrite` gives the whole line to the C library, and `fflush` gives it to the system at once.
4. The C library locks the standard output in each call. Thus the lines of 2 threads stay apart.

Each module can have its own `FILE` of the standard output. The flush after each line keeps each line whole, and keeps the order of the lines of one thread.
The layer mosl writes the line of a signal with one call of the system: https://github.com/Encrid/mosl/blob/dev/docs/extern/os.h.md#the-signals.
The flush keeps that line in its place too.

If the buffer cannot grow, `say` writes the bytes and the line end with two calls. Thus the line still comes, but another line can come between its parts.

## Functions

| Function | Result |
| --- | --- |
| `say` | Writes the bytes and a line end, with one `fwrite` and one `fflush`. |
| `say_format` | Makes the line with `vsnprintf`, then writes it as `say` does. |
