# src/cover/cover.h

This private header declares `cover_t`, the files and the macros that the check `cover` takes from Bridge, and the functions of `src/cover`.

## cover_t

| Field | Value |
| --- | --- |
| `api`, `check` | The table of BB-Native, and the name `cover` of `CHECKS_NAMES`. |
| `files`, `file_count` | The files of `mpbt:File`, as items of `files_item_t` that `files_sort` sorts. |
| `makes`, `make_count` | `macro` and `suffix` of each row of `mpbt:Make`. |
| `names` | A `buffer_t` with the public names of one header, with a line end after each name. |
| `spans` | A `buffer_t` with the code spans of one document, with a line end after each span. |
| `document` | A `buffer_t` with the path of the document of one header. |

## Functions

| Function | File |
| --- | --- |
| `cover_read_names`, `cover_read_inside` | `cover_names.c` |
| `cover_read_macro`, `cover_read_make` | `cover_macros.c` |
| `cover_get_spans`, `cover_is_named` | `cover_spans.c` |
