# src/workflows/workflows.h

This private header declares `workflows_name_t`, a name that the check `workflows` compares, and the functions of the files of `src/workflows`.

## workflows_name_t

| Field | Value |
| --- | --- |
| `bytes` | The bytes of the name, in a row of `mpbt:Target` or in a line of a workflow. |
| `len` | The count of these bytes. |

## Functions

| Function | File |
| --- | --- |
| `workflows_read_matrix` | `workflows_matrix.c` |
| `workflows_check_targets` | `workflows_targets.c` |
