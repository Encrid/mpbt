# src/text/text_refuse.c

This file reads the lists of `refuse`: the names of the functions that the code must not call.

## The lists

`read` replaced the variables of each path of `refuse`: `docs/extern/mpbt_project.h.md`, *Variables*.

1. `path_join` joins a relative path onto `{root}`, the folder of the project.
2. If `os_path_entry` finds nothing at the path, the list gets its finding of `docs/extern/mpbt_check.h.md`, *Messages*.
3. Else `path_read` reads the whole list. A list that does not read gets its finding of `docs/extern/mpbt_command.h.md`, *Messages*.
4. The check then reads the next list, and checks each file with the names that it has.
5. Each line of a list is a name, without the spaces and tabs around it.
6. A line with no text names nothing.
7. `qsort` puts the names in order, so that `text_calls.c` finds a name with `bsearch`.

## Functions

| Function | Result |
| --- | --- |
| `text_read_lists` | The names of all the lists, in order, each with the path of its list. |
| `take_names` | The names of the lines of one list. |
| `text_compare_names` | The order of 2 names, byte by byte. |
