# src/read/read_checks.c

This file writes the words, the macros and the exceptions that the checks read: `docs/extern/mpbt_check.h.md` and `docs/extern/mpbt_branches.h.md`.

## The components

| Table | Component | Fields |
| --- | --- | --- |
| Each key of `[check.retired]` | `mpbt:Retired` | `word` is the key, and `text` is its value. |
| Each key of `[check.makes]` | `mpbt:Make` | `macro` is the key, and `suffix` is its value. |
| Each table of `[[style.exception]]` | `mpbt:StyleException` | `rule`, `path` and `why`. |
| Each table of `[[branches.exception]]` | `mpbt:BranchException` | `path`, `why`, `line`, `col`, `side` and `system`. |

An exception with no `why` gets a `why` with no bytes. The check of the exception writes the finding, as its document tells.
`read_need_keys` checks `rule` and `path` of a style exception, and `path`, `line`, `col` and `side` of a branch exception.
The texts get the values of their variables from `run_variables`.

## The enums

| Text | Constant |
| --- | --- |
| `side = "true"` | `MPBT_SIDE_TRUE` |
| `side = "false"` | `MPBT_SIDE_FALSE` |
| `side = "function"` | `MPBT_SIDE_FUNCTION` |
| `side = "case"` | `MPBT_SIDE_CASE` |
| No `system` | `MPBT_SYSTEM_EVERY` |
| `system = "posix"` | `MPBT_SYSTEM_POSIX` |
| `system = "windows"` | `MPBT_SYSTEM_WINDOWS` |

`get_side` gives the constant of `side`. `read_get_system` gives the constant of `system`, and `read_leak_exceptions` uses it too.
`read_check_value` refuses each other text, with the values of the table.

## Functions

| Function | Result |
| --- | --- |
| `read_checks` | `true` after each entity of `mpbt:Retired` and of `mpbt:Make`, or `false` and a finding. |
| `read_style_exceptions` | `true` after each entity of `mpbt:StyleException`, or `false` and a finding. |
| `read_branch_exceptions` | `true` after each entity of `mpbt:BranchException`, or `false` and a finding. |
| `read_get_system` | The constant of a key `system`, by *The enums*. |
| `get_side` | The constant of a key `side`, by *The enums*. |
