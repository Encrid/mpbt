# src/shared/run/run_fault.c

This file writes the text of a command that did not end with 0, in the 3 lines of `docs/extern/mpbt_kind.h.md`, *Messages*.

## The text

1. The first line is the command: its arguments, with a space between 2 of them.
2. The second line gives the status, which `run_add_status` writes.
3. The output follows as it is, with no line end after its last line.

`run_add_status` writes a status in decimal, a space, then its low 32 bits in hexadecimal with 8 digits, after `0x` and between parentheses.
For example, the status -9 gives `-9 (0xFFFFFFF7)`.

A program that did not start gives only the first line, then the message of `docs/extern/mpbt_command.h.md`, *Messages*, for such a program.
The text goes into a finding, which can hold line ends: `docs/extern/mpbt_finding.h.md`, *The report*.
A caller with a time limit writes its own text for a command that it killed.

## Functions

| Function | Result |
| --- | --- |
| `run_add_fault` | Adds the text to a `buffer_t`: `true`, or `false` with no memory. |
| `run_add_status` | Adds the text of a status to a `buffer_t`: `true`, or `false` with no memory. |
