# src/read/read_sources.c

This file reads `[[source]]`, `[[dependency]]` and `[[agree]]`: `docs/extern/mpbt_source.h.md` and `docs/extern/mpbt_dependency.h.md`.

## The variables

`read_add_sources` runs before the other variables are complete, so each value goes in with its variables:

| Table | Variable | Value |
| --- | --- | --- |
| `[[source]]` | `{<name>}` | `into`, then `/` and `top` if `top` is there. |
| `[[dependency]]` | `{<name>}` | `into`. |

## The components

After the variables, each table gives one entity, in the order of the config:

| Table | Component | Steps |
| --- | --- | --- |
| `[[source]]` | `mpbt:Source` | `toml_doc_check_keys` checks the keys: `docs/extern/mpbt_source.h.md`, *[[source]]*. Each text and each patch replaces its variables. |
| `[[dependency]]` | `mpbt:Dependency` | Each text and each item of `make` replaces its variables. `optional` is `false` if the table does not give it. |
| `[[agree]]` | `mpbt:Agree` | Each item of `keys` replaces its variables. |

A key of a source that the header does not give stops the read, with its message of `docs/extern/mpbt_source.h.md`, *Messages*.
`read_need_keys` checks the keys with no default. A source needs `name`, `url`, `sha256` and `into`.
A dependency needs `name`, `from`, `list` and `into`, and a rule needs `keys` and `length`.

## Functions

| Function | Result |
| --- | --- |
| `read_add_sources` | `true` when the sources and the dependencies have their variables, or `false` with no memory. |
| `read_sources` | `true` after each entity of `mpbt:Source`, or `false` and a finding. |
| `read_dependencies` | `true` after each entity of `mpbt:Dependency`, or `false` and a finding. |
| `read_agrees` | `true` after each entity of `mpbt:Agree`, or `false` and a finding. |
