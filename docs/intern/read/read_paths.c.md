# src/read/read_paths.c

This file adds the list variable `{paths}`: `docs/extern/mpbt_artifact.h.md`, *The macros of the paths*.

## The steps

1. `read_get_rows` makes the rows of the artifacts, with their names.
2. A row of the kind `library` gives a macro if its `folder` is `built` and its `path` is `true`.
3. A row of the kind `library` with the `folder` `backends` gives a macro too.
4. `put_macro` makes each macro, in the order of the rows.
5. `BUILT_DIR` and `BUILT_SUFFIX` come after the macros of the rows.
6. `read_add_variable` adds the list as `{paths}`.

## A macro

`put_macro` takes the name of the row, with no `bridge_` at its start. It puts it in upper case, with `_` for each `-`, and adds `_PATH`.
The value is `"{out}/<folder>/<name>{library}"`, with the name of the row.
The items keep `{out}` and `{library}`. Thus each artifact that names `{paths}` gets `{library}` of its own target.

## Functions

| Function | Result |
| --- | --- |
| `read_paths` | `true` after `{paths}`, or `false` and a finding. |
| `put_macro` | Adds the item of one macro, or `false` with no memory. |
