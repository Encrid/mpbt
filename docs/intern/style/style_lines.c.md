# src/style/style_lines.c

This file checks the bytes of each line of a source: F3, L2 and L3 of `docs/contributing/coding_style.md`.
It reads the bytes and not the tokens, so the bytes of a comment or of a string count too.

## The rules of a line

A line is the bytes before its line end, `\n` or `\r\n`, or before the end of the file.

| Rule | Fault |
| --- | --- |
| F3 | The line takes more columns than the limit `columns`. A tab goes to the next multiple of 8 columns. Each other byte takes one column. |
| L2 | A tab is among the spaces before the first byte of text. |
| L3 | The last byte of the line is a space or a tab. |

Each of these faults is of the whole line, so its column is 0.
The messages are in `docs/extern/mpbt_check.h.md`, *style*.

## Functions

| Function | Result |
| --- | --- |
| `style_check_lines` | Checks each line. |
| `style_is_empty_line` | `true` if a line holds only spaces and tabs. |
| `count_columns` | The count of the columns of a line. |
