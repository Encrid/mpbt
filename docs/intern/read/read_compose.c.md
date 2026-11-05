# src/read/read_compose.c

This file reads `[parts]`, `[compose]` and `[package]`, and writes `mpbt:Part`, `mpbt:Compose` and `mpbt:Package`: `docs/extern/mpbt_compose.h.md`.

## The checks of the parts

`read_check_parts` does each check of `[parts]`, so that `build`, `compose`, `pack` and `join` only read `mpbt:Part`.
It keeps the names of the parts in `parts` of `read_t`.

1. `toml_doc_check_keys` checks the keys of each table of `parts`.
2. A part with no `name`, `folder`, `uses` or `third_party` stops the read.
3. Each part of `uses`, of `--part` and of `--tag` must be a part of the config.
4. For each part of the config, a walk in depth follows its `uses`.
5. A part that the walk meets again before its end is in a cycle. The cycle stops the read, with the parts of the cycle.

The messages are in `docs/extern/mpbt_compose.h.md`, *Messages*. The build ranks the parts by their `uses` itself.

## The part of a table

`read_check_part` checks the key `part` of an artifact or of a table of `[compose]`. A part owns the tables that name it:

| The project | The key `part` | The result |
| --- | --- | --- |
| Has parts | Is not there | A finding. |
| Has parts | Names no part of the config | A finding. |
| Has parts | Names a part | No finding. |
| Has no parts | Any value | No finding. The field `part` has no bytes. |

## The components

| Table | Component | Values that the table does not give |
| --- | --- | --- |
| `[parts.<part>]` | `mpbt:Part` | None: each key is needed. |
| `[compose.<name>]` | `mpbt:Compose` | `from` is `{root}`. `into` has no bytes: the top of the deliverable. The lists have no item. |
| `[package]` | `mpbt:Package`, with no bytes in `part` | `proof` has no bytes: no proof. The lists have no item. |
| `[parts.<part>.package]` | `mpbt:Package`, with the part | The same as `[package]`. |

Each text and each list gets the values of its variables, with `run_variables`.

## Functions

| Function | Result |
| --- | --- |
| `read_check_parts` | `true` if each part passes *The checks of the parts*, or `false` and a finding. |
| `read_parts` | `true` after each entity of `mpbt:Part`, or `false` and a finding. |
| `read_check_part` | `true` if *The part of a table* gives no finding, else `false` and the finding. |
| `read_compose` | `true` after each entity of `mpbt:Compose`, or `false` and a finding. |
| `read_packages` | `true` after each entity of `mpbt:Package`, or `false` and a finding. |
