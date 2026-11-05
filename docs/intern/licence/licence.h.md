# src/licence/licence.h

This private header declares `licence_t`, the files that the check `licence` reads, and the functions of the files of `src/licence`.

## licence_t

| Field | Value |
| --- | --- |
| `files` | The files of the project: a `files_item_t` for each, sorted by `files_sort`. |
| `count` | The count of the files. |

## Functions

| Function | File |
| --- | --- |
| `licence_check_text` | `licence_text.c` |
| `licence_check_reserved` | `licence_reserved.c` |
| `licence_check_notices` | `licence_notices.c` |
