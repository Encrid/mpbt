# src/compose/compose_list.c

This file keeps the files of a deliverable in the order of their names, with one file for each name.

## The order

`find_place` finds the place of a name in the list, by a binary search with `files_compare`.
`compose_add_file` puts a new name at its place. A name that the list holds already gets the new file, so a later group replaces an earlier one.
`compose_remove_file` takes a name out of the list, and moves the later files up.
Thus the lines of `say`, the copies and the list of `mpbt:Deliverable` see the files in one order, on each run.

## Functions

| Function | Result |
| --- | --- |
| `compose_add_file` | Adds a file, or replaces the file of its name: `false` with no memory. |
| `compose_remove_file` | `true` if the list held the name. |
| `find_place` | The place of a name in the list. |
