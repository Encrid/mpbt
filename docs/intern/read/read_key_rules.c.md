# src/read/read_key_rules.c

This file checks that a needed key is there, that a key has its type of TOML, and that mpbt knows its value.
The messages are in `docs/extern/mpbt_project.h.md`, *Messages*.

## The rules

| Function | Rule | The finding names |
| --- | --- | --- |
| `read_need_keys` | Each key of a list of names is in the table. | The header of the table, for example `[test]`, and the first key that is not there. |
| `read_add_missing` | None: it writes the finding of a needed key for a caller that finds the keys itself. | The same as `read_need_keys`. |
| `read_check_kind` | A node has the kind that its field needs. | The file and the key of the node, the kind of the node, and the kind that the field needs. |
| `read_check_value` | A text is one of the values of a list. | The header of the table, the key, the text, and each value of the list. |

`get_kind_name` names each kind of `toml_node_t` for a message, for example `an integer` or `a list`.
A table of a list of tables, for example of `[[source]]`, has the header of that list.

## The needed keys

A key with no default in its table of `docs/extern` is a needed key, but for a key with a rule of its own:

- the keys of `[parts]`, of `claims` and of `false` have their own messages;
- `[test] copies` can come from `--copies`, so the test writes its message;
- a `why` that is not there is a fault of the check or of the count that reads it.

Each file of `read` names its needed keys, for example `name`, `url`, `sha256` and `into` of `[[source]]`.

## Functions

| Function | Result |
| --- | --- |
| `read_need_keys` | `true` if each key is there, or `false` and a finding. |
| `read_add_missing` | Writes the finding of one needed key that is not there. |
| `read_check_kind` | `true` if the node has the kind, or `false` and a finding. |
| `read_check_value` | `true` and the place of the text in the list, or `false` and a finding. |
| `get_kind_name` | The name of a kind of TOML, for a message. |
