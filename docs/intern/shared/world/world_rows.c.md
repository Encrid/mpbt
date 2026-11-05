# src/shared/world/world_rows.c

This file gives each row of one type to a function of the caller, from the spans of the query of a system.

## The steps

1. `bridge_native_get_query` gives the query of the system, and `bridge_native_get_span` gives each of its spans.
2. A span holds the id of a table. `walk_table` reads the column of the type in that table from the header of the module.
3. A table with no column of the type gives no row. Thus a query with optional terms gives only the rows of the type.
4. `bridge_native_get_rows` gives the count of the rows, and `bridge_native_get_block` gives the id of each row.
5. `visit` gets each row in turn, with its id. A `false` of `visit` stops the walk.

The header holds the column of each type in each table, or 0: https://github.com/Encrid/Bridge/blob/v0.4.1/docs/extern/bridge_abi.h.md#spans.
A row stays good until the next barrier, as the spans do. A caller that needs a row after its system copies it.

## Functions

| Function | Result |
| --- | --- |
| `world_rows` | The count of the rows that `visit` got. |
| `walk_table` | Gives the rows of one table to `visit`, or `false` when `visit` stops. |
