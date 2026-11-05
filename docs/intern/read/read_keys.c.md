# src/read/read_keys.c

This file copies the value of one key of the config into the arena, in the form that its field needs.
Each function gets the node of the key from `toml_doc_find_key`, or none when the table does not give the key.

## The variables

Each copy gets a `variables_t`, or none.

- With a `variables_t`, a text goes through `variables_expand`, and a list goes through `variables_expand_items`.
- With none, the text keeps its variables, as the steps of the kinds and the cases need: `docs/extern/mpbt_project.h.md`, *Variables*.

A name that no entry gives stops the copy with the finding of `variables_expand`.

## The copies

| Function | The node | The copy |
| --- | --- | --- |
| `read_copy_text` | A text, or none. | The text. None gives no bytes. |
| `read_copy_list` | A list of texts, or none. | A list of the items. None gives a list of no item. |
| `read_copy_map` | A table of texts, or none. | A map: each key, then its text. |
| `read_get_number` | An integer, or none. | The number, or the default of the caller. |
| `read_get_flag` | A bool, or none. | `true` or `false`, or the default of the caller. |

A node of a different kind stops the copy: `read_check_kind` writes the finding of `docs/intern/read/read_key_rules.c.md`, *The rules*.
A key keeps the order of its file, so a map keeps the order of the config.

## Functions

| Function | Result |
| --- | --- |
| `read_copy_text` | `true` and the `bridge_text_t` of a text, or `false` and a finding. |
| `read_copy_list` | `true` and the `bridge_text_t` of a list, or `false` and a finding. |
| `read_copy_map` | `true` and the `bridge_text_t` of a map, or `false` and a finding. |
| `read_get_number` | `true` and the integer of a node or the default, or `false` and a finding. |
| `read_get_flag` | `true` and the bool of a node or the default, or `false` and a finding. |
