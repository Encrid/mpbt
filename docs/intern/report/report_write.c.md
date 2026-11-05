# src/report/report_write.c

This file writes each finding as one line, then the lines after them: `docs/extern/mpbt_finding.h.md`, *The report*.

## A line

1. A `check` with bytes comes first, then a colon and a space.
2. Then the place: `path`, `line` and `column`, with a colon between 2 parts that are there.
3. A part with no bytes, or 0, is not there. A place with a part gets a colon and a space after it.
4. The `text` comes last.

`snprintf` writes `line` and `column` into 2 arrays of 11 bytes. Thus one call of `say_format` writes the whole line, and `report` makes no allocation for it.
A text can hold line ends: `docs/extern/mpbt_finding.h.md`, *The report*. The prefix then comes only before its first line.
`say_format` writes the other lines of the text as they are, in the same call.

## After the lines

1. With a finding, `say_format` writes the count of the faults.
2. After the phase `check`, `write_failed` then writes the names of the checks that found faults.
3. These names follow the order of `CHECKS_NAMES`, with a space between 2 names.
4. A name that is not in the list comes after them, one time, in the order of the rows.
5. After the phase `check` with no finding, `say` writes that every check passes.

The count is in `docs/extern/mpbt_finding.h.md`, *Messages*. The lines of `check` are in `docs/extern/mpbt_check.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `report_write` | Writes the lines of the findings, the count, and the lines of `check`. |
| `write_row` | Writes one row as one line. |
| `write_failed` | Writes the names of the checks that found faults. |
