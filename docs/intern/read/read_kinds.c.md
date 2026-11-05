# src/read/read_kinds.c

This file writes `mpbt:Kind` and `mpbt:Step` from each table of `kinds`: `docs/extern/mpbt_kind.h.md`.

## The steps

1. Each table of `kinds`, in the order of the config, gives an entity with `mpbt:Kind`. `read_need_keys` checks its `output` and its `steps`.
2. `write_steps` writes an entity with `mpbt:Step` for each table of `steps`, then for each table of `unlinked`.
3. `toml_doc_check_keys` checks the keys of each step, with the name of the kind as the place of the message.
4. `get_actions` sets a bit for each action that the step gives: *The bits*.

The 4 kinds of mpbt come from `src/read/values.toml`, and a project adds its own.
Each text keeps its variables, because the build replaces them for each artifact.

## The bits

| Keys of the step | Bit |
| --- | --- |
| `run`, with `cwd` or without it | `MPBT_STEP_RUN` |
| `section` and `text` | `MPBT_STEP_SECTION` |
| `contains` | `MPBT_STEP_CONTAINS` |
| `copy` | `MPBT_STEP_COPY` |
| `rename` | `MPBT_STEP_RENAME` |

`owner` holds the id of its kind, and `order` counts the steps of a list from 0.
`list` is `MPBT_STEP_LIST_STEPS` or `MPBT_STEP_LIST_UNLINKED`.

## Functions

| Function | Result |
| --- | --- |
| `read_kinds` | `true` after each kind and each step, or `false` and a finding. |
| `write_kind` | `true` after one entity of `mpbt:Kind` and its steps, or `false` and a finding. |
| `write_steps` | `true` after the steps of one list, or `false` and a finding. |
| `get_actions` | The bits of the keys of one step. |
