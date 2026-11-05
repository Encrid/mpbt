# src/shared/files/files.h

This header declares `files_item_t`, a file of `mpbt:File` that a check keeps. It also declares the functions that sort such files by path, and find a path among them.
The checks `layout`, `licence`, `xref` and `cover` use it. `glob_files` uses its order of the paths.

## files_item_t

| Field | Value |
| --- | --- |
| `path`, `path_len` | Its path from the root, with `/` between the names. |
| `bytes`, `len` | The bytes of the file. |

The fields point into the shared memory, where the row of `mpbt:File` holds the bytes. Thus an item copies no byte.

## Functions

| Function | Result |
| --- | --- |
| `files_sort` | Sorts the items by path. |
| `files_find` | Gives the item of a path, or none. |
| `files_compare` | Gives the order of 2 paths. |
