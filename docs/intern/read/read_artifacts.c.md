# src/read/read_artifacts.c

This file finds the rows of the artifacts, and writes an entity with `mpbt:Artifact` for each row: `docs/extern/mpbt_artifact.h.md`.

## The rows

`read_get_rows` makes the rows in these steps, and keeps them in `rows` of `read_t`:

1. Each table of `[[modules]]` gives a row over `[module]`, in the order of the config.
2. Each table of `[[artifact]]` gives a row after them.
3. Each table of `variants` of a row gives a row of its own, just after that row.
4. The place of each row in `rows`, from 0, is its `order`.

`find_key` gives a key of a row: from the variant first, then from the row, then from `[module]`.
A row needs `name`, `kind` and `sources`. A needed key that `find_key` does not find gets the finding of `read_add_missing`.
`read_get_variables` gives the variables of the target of the row, and the name of the row takes their values. `read_paths` needs these names.

## The entities

`read_artifacts` writes one entity for each row, with its `order`: `docs/extern/mpbt_artifact.h.md`, *mpbt:Artifact*.
`read` sorts nothing. The build orders the artifacts by the rank of their part in the `uses`, then by `order`.
`write_artifact` writes one entity in these steps:

1. `target` is the key `target` of the row, or the target of the run. A target that the config does not give stops the read.
2. `read_get_variables` gives the `variables_t` of that target.
3. Each text and each list of the row replaces its variables with it.
4. `read_check_value` checks that `kind` names a kind of the config. `test`, `path` and `unstamped` are `false` if the row does not give them.
5. `read_check_part` checks the part of the row: `docs/intern/read/read_compose.c.md`, *The part of a table*.

In a list, an item that is only a list variable becomes the items of that list: `docs/intern/shared/variables/variables_items.c.md`.
The message of a target that is not there is in `docs/extern/mpbt_artifact.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `read_get_rows` | `true` after the rows and their names, or `false` and a finding. |
| `read_artifacts` | `true` after each entity of `mpbt:Artifact`, or `false` and a finding. |
| `write_artifact` | `true` after the entity of one row, or `false` and a finding. |
| `find_key` | The node of a key of a row, or none. |
