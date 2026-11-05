# src/layout/layout.h

This private header declares `layout_t`, what the check `layout` reads in one run, and the functions that the files of `src/layout` share.

## layout_t

| Field | Value |
| --- | --- |
| `files` | Each file of `mpbt:File`, as a `files_item_t`, in the order of `files_sort`. |
| `count` | How many files `files` holds. |
| `guides` | `guides` of `mpbt:LayoutCheck`: the name of each guide that the project adds, one name on each line. |

## Functions

| Function | File |
| --- | --- |
| `layout_check_paths` | `layout_paths.c` |
| `layout_check_names` | `layout_names.c` |
| `layout_check_documents` | `layout_documents.c` |
