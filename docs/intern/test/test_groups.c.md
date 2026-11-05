# src/test/test_groups.c

This file sorts the cases by their groups, and keeps the cases that `--part` and `-k` choose: `docs/extern/mpbt_case.h.md`, *Groups*.

## The steps

1. `compare_cases` gives the order of `group`, byte by byte, then of `index`. Thus each group is one run of cases.
2. With `--part`, a group stays if `is_in_parts` finds it in the `folder` of a named part.
3. If no group stays, a finding names the parts: `docs/extern/mpbt_compose.h.md`, *Messages*.
4. With `-k`, a case stays if its `name` holds the text of `filter`.
5. If no case stays, the finding comes from `docs/extern/mpbt_case.h.md`, *Messages*.

A group is in a folder if its name is the folder, or if its name starts with the folder and `/`.
The parts are those of `parts` of `mpbt:Command`. A part that a named part uses adds no group: its own cases run with its own `--part`.
A case that does not stay keeps `chosen` at `false`. The other files skip it, and a group with no chosen case writes no line.

## Functions

| Function | Result |
| --- | --- |
| `test_pick_cases` | `true`, or `false` after a finding. |
| `compare_cases` | The order of 2 cases by `group`, then by `index`. |
| `is_in_parts` | Whether a group is in the folder of a named part. |
| `pick_filter` | The cases whose name holds the text of `-k`. |
