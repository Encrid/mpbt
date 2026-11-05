# src/test/test_patterns.c

This file judges the claims `matches` and `matches_not` with `src/shared/regex`, and refuses each pattern of a form that mpbt does not have.
The forms are in `docs/extern/mpbt_case.h.md`, *Claims*.

## Before the first case

`test_check_patterns` compiles each pattern of each case, also of a case that `-k` or `--part` leaves out.

1. It takes the claims of the case, then the helper claims of its use and of its false variant.
2. Each pattern gets the variables of the run, the `{case}` of the first copy, and `0` as `{port}`.
3. `regex_compile` compiles the pattern, and `regex_free` gives the program back.
4. A refused form or a program of more than 65536 steps gives a finding, and the run stops.

The finding has the path of the file of the group: `cases` of `mpbt:Tests`, `/`, the group, then `.toml`. Its text comes from `docs/extern/mpbt_case.h.md`, *Messages*.
A form does not change with the value of `{case}` or of `{port}`. Thus a pattern that passes here also compiles in each copy.

## The claims of a copy

`test_hold_patterns` gets each pattern of a list with the variables of the copy, compiles it, and searches the output with `regex_search`.
`matches` holds if each pattern is in the output. `matches_not` holds if no pattern is in it.
The search goes through the output one time, so a long output costs a time that only grows with its length.

## Functions

| Function | Result |
| --- | --- |
| `test_check_patterns` | `true`, or `false` after the finding of a pattern. |
| `test_hold_patterns` | Whether the claims `matches` and `matches_not` hold. |
| `check_list` | Compiles each pattern of one list, before the first case. |
| `find_pattern` | Whether one pattern is in the output. |
