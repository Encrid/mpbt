# src/report/report_rows.c

This file reads the findings of the spans of the system `report` into rows, and copies none of their bytes.

## The steps

1. `world_rows` walks the rows of `mpbt:Finding` in the spans of the query, and `count_rows` counts them.
2. With a count of 0, `report_get_rows` gives no rows.
3. `malloc` gives the array of `report_row_t` for that count.
4. A second walk of `world_rows` gives each row to `fill_row`.
5. `fill_row` puts the 5 fields of the finding into a row, and its place in the walk into `index`.

Each `bridge_text_t` of a finding gives the bytes at its offset in the shared memory, and its count.
The 2 walks see the same rows, because the rows do not change during a phase.

## Functions

| Function | Result |
| --- | --- |
| `report_get_rows` | `true` with the count of the findings and their rows, or `false` with no memory. |
| `count_rows` | Counts one row of the first walk. |
| `fill_row` | One row, from one finding of the second walk. |
