# src/read/read_load.c

This file writes an entity with `mpbt:Load` for each table `[[load]]`: `docs/extern/mpbt_load.h.md`, *mpbt:Load*.

## The steps

1. `artifact` gives `MPBT_LOAD_ARTIFACT`, and `file` gives `MPBT_LOAD_FILE`. Its text gets the values of its variables.
2. Each key of `phases` gives a phase of the module and the phase of mpbt that it joins.
3. Each key of `config` gives a setting and the text of TOML of its value.
4. Each other key of the table goes into `keys` in the same form.
5. `order` counts the tables of `[[load]]` from 0. The build writes the list of the loads in that order.

`src/host/host_config.c` refused a table with both `artifact` and `file`, or with neither, before the world was there.
Thus `read` writes no finding for these tables.

## A text of TOML

`write_toml_value` writes a value in the form of TOML 1.1 into a `buffer_t`:

| Value | Text |
| --- | --- |
| A text | `write_toml_text` writes it between `"`, with `\"`, `\\` and the escape `\u` of each control character. |
| An integer, a real number or a time | The text of the number or of the time. |
| A bool | `true` or `false`. |
| A list | A list of TOML on one line, for example `["a", "b"]`. |
| A table | An inline table of TOML, for example `{ host = "a", format = "zip" }`. |

A key of a table that holds a character other than a letter, a digit, `_` and `-` goes between quotes, as a text does.
Thus a module of a project reads each value as TOML, for example `["mpbt:Finding"]` for a key `write`.

## Functions

| Function | Result |
| --- | --- |
| `read_loads` | `true` after each entity of `mpbt:Load`, or `false` and a finding. |
| `put_toml_map` | `true` and the map of the keys of a table, each value as a text of TOML, or `false` with no memory. |
| `write_toml_value` | Writes one value as a text of TOML. |
| `write_toml_text` | Writes one text between quotes, with its escapes. |
