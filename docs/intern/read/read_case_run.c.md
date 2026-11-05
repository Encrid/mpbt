# src/read/read_case_run.c

This file attaches `mpbt:Run` to the entity of a case or of a false variant: `docs/extern/mpbt_case.h.md`, *mpbt:Run*.

## The fields

| Field | Key | Value |
| --- | --- | --- |
| `run` | `run` | The list of the command. |
| `env`, `unset` | `env` | `put_env` puts each variable with a text into the map `env`, and each variable with `false` into the list `unset`. |
| `input` | `stdin` | The text. |
| `files` | `files` | A map: each path, then its text. |
| `folders` | `folders` | A map: each path, then the list of what goes there. |
| `fail` | `fail` | `put_fail` makes a map of each function and the decimal text of its number. |
| `helper_run`, `helper_wait`, `helper_input` | `helper` | `run`, `wait` and `stdin` of the helper. An empty table gives no item and no bytes. |
| `ignore_interrupt` | `ignore` | `true` if the list holds `interrupt`. |

Each text keeps its variables, because the test replaces them for each copy of the case.

## The false variant

`read_write_run` gets the table of the case, and the table of `false` or none.

- `find_key` takes a key from `false` first, and from the case if `false` does not give it.
- `put_paths` makes `files` and `folders` from the paths of the case. A path of `false` replaces only the path with the same name.
- A table `helper` of `false` replaces the whole helper of the case. An empty table removes it.

## Functions

| Function | Result |
| --- | --- |
| `read_write_run` | `true` after the attach of `mpbt:Run`, or `false` with no memory. |
| `find_key` | The node of a key, from `false` first and then from the case. |
| `put_env` | `true` and the map `env` and the list `unset`, or `false` with no memory. |
| `put_paths` | `true` and the map of `files` or of `folders`, or `false` with no memory. |
| `put_fail` | `true` and the map of `fail`, or `false` with no memory. |
