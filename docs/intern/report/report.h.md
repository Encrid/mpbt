# src/report/report.h

This private header declares a finding as `report` sorts it, and the functions that the files of `src/report` share.

## report_row_t

| Field | Value |
| --- | --- |
| `check`, `path`, `text` | The bytes of each text of the finding, in the shared memory, with their counts. |
| `line`, `column` | The line and the column of the finding, or 0. |
| `rank` | The place of `check` among the checks, from `report_sort`. |
| `index` | The place of the row in the walk of the spans, from 0. |

The bytes stay in the shared memory, and `report` copies none of them. They stay valid for the whole phase.

## Functions

| Function | File |
| --- | --- |
| `report_get_rows` | `report_rows.c` |
| `report_sort` | `report_sort.c` |
| `report_write` | `report_write.c` |
