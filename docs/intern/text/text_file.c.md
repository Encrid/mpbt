# src/text/text_file.c

This file selects the checks of one file by its path.

## The checks of a file

| Path | Check |
| --- | --- |
| Each path that no glob of `unicode` matches | `text_check_ascii` |
| A path that ends with `.py`: a script | `text_check_script` |
| A path that ends with `.toml` or `.yml` | `text_check_hashes` |
| A path that ends with `.md`: a document | `text_check_markup` |
| Each path that does not start with `.toolchain/` | `text_check_retired` |
| A path of `src` or of `include` that ends with `.c` or `.h` | `text_check_calls` |

`lists_get_line` gives each line of `unicode`, and `glob_match` tells whether that glob matches the path: `docs/intern/shared/glob/glob_match.c.md`.
A file of `tests` gets only `text_check_retired`: `docs/extern/mpbt_file.h.md`, *The files of the project*.
The table of the retired words is in `.toolchain`. Thus the table itself is no fault, and a project gets no fault that only the toolchain can remove.

## Functions

| Function | Result |
| --- | --- |
| `text_check_file` | Runs each check that the path of a file asks for. |
| `has_end` | Whether a path ends with a text. |
| `is_unicode` | Whether a glob of `unicode` matches a path. |
