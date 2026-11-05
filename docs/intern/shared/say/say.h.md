# src/shared/say/say.h

This header declares the writer of the lines of mpbt. The host and each native module write each line of the output through it.

## The lines

- A line goes to the standard output whole, with one line end after it.
- A line can come from each thread, and it does not mix with a line of another thread.
- A line comes at once, also in the middle of a long phase.

## Functions

| Function | Result |
| --- | --- |
| `say` | Writes `len` bytes and one line end, as one line. |
| `say_format` | Writes the line of a format of `printf` and its values, as one line. |
