# src/shared/toml/toml_doc_find.c

This file finds a node by its path, and checks the keys of a table.

## The path

A path is keys with a `.` between them, for example `test.timeout`.
`toml_doc_find` follows each key from the table at the top. A key that is not there, or a node that is not a table, gives no node.
A key that holds a `.`, such as a target, is found with `toml_doc_find_key` in its table.

## The keys of a table

`toml_doc_check_keys` gets a table, the allowed keys, and the name of the table for the message.
For each key that is not allowed, it writes the finding `<where>: a <what> has no key <keys>`. `<keys>` gives each such key, with a space between them.

## Functions

| Function | Result |
| --- | --- |
| `toml_doc_find` | The node of a path, or none. |
| `toml_doc_find_key` | The node of one key of a table, or none. |
| `toml_doc_check_keys` | `true`, or `false` and a finding. |
