# src/test/test_world.c

This file reads what the system needs from the world into a `test_world_t`, with the shared seam of `src/shared/world`.

## The steps

1. `bridge_native_get_single` gives `mpbt:Command`, `mpbt:Tests` and `mpbt:Leaks`. A singleton with no value gives none.
2. For each other type of the components of `test.c`, `world_rows` gives each row of the type to `keep_row`.
3. `keep_row` keeps the id of the entity and the place of the value in the `test_rows_t` of the type.
4. `keep_file` keeps each row of `mpbt:File` as a `files_item_t`, and `files_sort` then sorts them by path.
5. The rows of `mpbt:Variable`, `mpbt:Target`, `mpbt:Kind` and `mpbt:Step` also fill the `steps_t` of the changed runs.

The arrays grow with `realloc` as the rows come, and `test_free_world` frees them before the system returns.
A value stays where Bridge keeps it, until the next barrier. Thus the walk copies no byte of a component.

## Functions

| Function | Result |
| --- | --- |
| `test_read_world` | A `test_world_t`, or `false` with no memory. |
| `test_free_world` | Gives the arrays of the rows back. |
| `keep_row` | Keeps one row of a type. |
| `keep_file` | Keeps one row of `mpbt:File`. |
