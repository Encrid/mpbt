# src/shared/toml/toml_doc.h

This header declares a document of TOML that mpbt merges from several files, and the functions that read, merge, find and free it.
The read of the config and the read of the cases use it.
tomlc17 reads each file: https://github.com/cktan/tomlc17/releases/tag/R261003.

## toml_node_t

| Field | Value |
| --- | --- |
| `key` | The key of the node in its table, or no bytes for an item of a list. |
| `kind` | A text, an integer, a real number, a bool, a time, a list or a table. |
| `text`, `integer`, `real`, `flag` | The value of its kind. A time keeps its text of TOML. |
| `nodes`, `count` | The items of a list, or the keys of a table. |
| `file`, `line` | The file of the node, as an index into `toml_doc_t`, and its line from 1. |

## toml_doc_t

| Field | Value |
| --- | --- |
| `root` | The table at the top. |
| `files` | The names of the files, in the order of the read. The first name is `mpbt`, for the values that mpbt holds. |

## Functions

| Function | Result |
| --- | --- |
| `toml_doc_read` | Reads one file into a document. |
| `toml_doc_merge` | Merges 2 documents. |
| `toml_doc_find` | Gives the node of a dotted path. |
| `toml_doc_check_keys` | Finds each key of a table that is not allowed. |
| `toml_doc_free` | Gives the memory of a document back. |
