# src/shared/json/json_skip.c

This file skips a whole value from its first token, and copies no string.
The probes and the count skip each node of the syntax tree from a file that is not a file of the project.
Thus they skip most of a tree of zig.

## The steps

`json_skip` counts the objects and the lists that open and close, and stops when the count is 0 again.
In a string, it looks only for the end quote and for a backslash, and skips the byte after a backslash.
Thus a skip reads each byte one time, and writes no byte.

## Functions

| Function | Result |
| --- | --- |
| `json_skip` | The reader after the value. |
| `skip_string` | The reader after the end quote. |
