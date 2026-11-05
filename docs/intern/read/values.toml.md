# src/read/values.toml

This file holds the values that mpbt gives to each project, in TOML 1.1. `read_config` reads it first, as the document `mpbt`.
A file of a project can add keys to its tables, but no key of this file can change: `docs/extern/mpbt_project.h.md`, *The files of the config*.

## The tables

| Table | Keys | The values |
| --- | --- | --- |
| `[variables]` | `language`, `optimize`, `float` and `strip` | `docs/extern/mpbt_project.h.md`, *[variables]* |
| `[debug]` | `optimize` and `strip` | The values with `--debug`: `docs/extern/mpbt_project.h.md`, *[variables]* |
| `[targets.<target>]` | The keys of a target, for each of the 6 targets | `docs/extern/mpbt_target.h.md`, *The targets*, and `docs/extern/mpbt_target.h.md`, *The keys of a target* |
| `[kinds.<kind>]` | `output` and `steps`, for `program`, `library`, `archive` and `file` | `docs/extern/mpbt_kind.h.md`, *[kinds.\<kind\>]* |

The module holds the file with `#embed`, so a program of mpbt needs no file beside it for these values.
A key of `[debug]` replaces the key of `[variables]` with the same name, with `--debug`: `docs/intern/read/read_project.c.md`, *The own variables*.

## The steps of the kinds

Each kind has one step, `run`, with the variables of `docs/extern/mpbt_kind.h.md`, *Steps*, and of its target.
The kind `file` has a step `copy` in place of `run`.
The kind `archive` gives `{strip}` to zig before `-cflags`, and the sources after `--`.
