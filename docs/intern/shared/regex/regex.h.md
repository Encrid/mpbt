# src/shared/regex/regex.h

This header declares a compiled pattern, and the functions that compile it and find it in a text.
The claims `matches` and `matches_not` of a case use it: `docs/extern/mpbt/case.h.md`, *Claims*.

## regex_t

| Field | Value |
| --- | --- |
| `steps` | The steps of the program, from `malloc`. |
| `count` | The count of the steps. |
| `sets` | The sets of bytes of the classes, 256 bits each. |
| `set_count` | The count of the sets. |

## Functions

| Function | Result |
| --- | --- |
| `regex_compile` | Gives the program of a pattern, or the form that mpbt refuses. |
| `regex_search` | Tells whether the pattern is in a text. |
| `regex_free` | Gives the memory of a program back. |
