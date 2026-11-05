# src/shared/steps/steps_do.c

This file does the steps of one list of a kind, for one artifact: `docs/extern/mpbt_kind.h.md`, *Steps*.

## The steps

1. A step of the list is a row of `mpbt:Step`, with the kind in `owner` and the list in `list`.
2. The steps run in the order of their field `order`.
3. Each step does the actions of its bits, in the order of `docs/extern/mpbt_kind.h.md`, *Steps*.
4. Each text of a step gets its variables from the plan, through `variables_expand` or `variables_expand_items`.
5. `steps_run` does the action `run`.
6. `section` adds a section to the end of the output. A variant with `unstamped` adds none.
7. `contains` gives a fault if the bytes of the output do not hold its text.
8. `copy` gives the bytes of the first file to the second file, with `copy_file`.
9. `rename` gives the first file the path of the second file, with `os_path_move`.
10. `path_join` puts each path of `copy` and of `rename` after the folder of the project.
11. After a fault, no other action and no other step runs.

## A section

`put_leb` writes a number in groups of 7 bits, from the lowest group. Each group but the last also has the bit `0x80`.
`add_section` reads the output with `path_read`, and adds the section after its bytes.
Then `os_file_write` writes the file again, and keeps its execute bit.

An output that `section` or `contains` cannot read, or a first file of `copy` that does not read, is a fault.
A section, a copy or a move that the system refuses to write is a fault too.
The messages of these faults are in `docs/extern/mpbt_command.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `steps_do` | 0 after the last step, or 1 after a fault. |
| `do_step` | Does the actions of one step. |
| `add_section` | Adds a section to the end of the output. |
| `put_leb` | Adds a number to a `buffer_t`, as an unsigned LEB128. |
| `has_text` | Whether the bytes of the output hold a text. |
