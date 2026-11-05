# src/test/test_hits.c

This file sizes the file of the hits, writes it with zeros before the cases, and reads its bits after them.
The file is `{out}/hits.bin` of the run `branches`.

## The parts

`test_get_parts` gives each file with probes a part of the file of the hits, in the order of the paths:

1. A part has 2 bytes for each probe of the file, and 2 bytes for a file with no probe.
2. The first part starts at byte 0. Each next part starts after the end of the part before it.
3. The size of the file is the end of the last part.

A probe of a condition has 2 outcomes: the byte `2 * n` for false, and `2 * n + 1` for true.
A probe of a function or of a label has 1 outcome: the byte `2 * n + 1`.

## The file

`test_write_hits` writes the file with a byte 0 for each byte of its size, with `test_write_file`.
Each program and each library of a case maps the same file. Thus the file holds the outcomes of each program of each case.
`test_read_hits` reads the file after the last case, with `path_read`. A byte that is not 0 is an outcome that a case reached.
If `path_read` fails, the finding names the file that mpbt cannot read: `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `test_get_parts` | The first byte and the size of the part of each file, and the size of the file. |
| `test_write_hits` | `true` after the write of the zeros. |
| `test_read_hits` | `true` and the bytes of the hits, or `false`. |
