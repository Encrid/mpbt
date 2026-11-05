# src/shared/toml/toml_doc_read.c

This file reads the bytes of one file with tomlc17, and copies its tree into the nodes of a `toml_doc_t`.

## The steps

1. `toml_doc_read` gives the bytes and the name of the file to `toml_parse_named` of tomlc17.
2. If the result is not `ok`, it writes the finding `<path>:<line>: <reason>`, with the line and the reason of `errmsg`.
3. Else `copy_datum` walks the tree of tomlc17, and makes a `toml_node_t` for each datum, with its `lineno`.
4. `toml_free` of tomlc17 then gives the memory of its tree back.

A copy owns its bytes, so the document lives after the result of tomlc17.
A key of a table keeps the order of the file. The merge and the read of the config need that order, for example for `[[artifact]]`.

## Functions

| Function | Result |
| --- | --- |
| `toml_doc_read` | A document, or a finding. |
| `copy_datum` | The node of one datum, and of the datums below it. |
| `copy_text` | The bytes of a text of tomlc17. |
