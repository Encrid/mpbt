# src/clean/clean.h

This private header declares the paths of a clean, and the functions that the files of `src/clean` share.

## clean_paths_t

| Field | Value |
| --- | --- |
| `build` | The text of `{build}`, as the variable gives it, for the lines and the findings of `clean`. |
| `there` | `true` if a folder is at `{build}`. |
| `whole` | The output folder, after `os_path_whole`. |
| `holds_root` | `true` if the root of the project is the output folder, or is inside it. |
| `kept` | The paths that stay inside the output folder, each a `buffer_t` that starts after `whole` and its separator. |
| `count` | The count of the paths in `kept`. |

## Functions

| Function | File |
| --- | --- |
| `clean_get_paths` | `clean_paths.c` |
| `clean_free_paths` | `clean_paths.c` |
| `clean_is_same` | `clean_paths.c` |
| `clean_is_inside` | `clean_paths.c` |
| `clean_remove` | `clean_remove.c` |
