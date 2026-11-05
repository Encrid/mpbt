# src/shared/toml/toml_doc_merge.c

This file adds the keys of one document to another one, by the rules of `docs/extern/mpbt_project.h.md`, *The files of the config*.

## The rules

`merge_table` takes each key of the new table, in its order:

| The key in the old table | The step |
| --- | --- |
| Not there | The new node goes into the old table. |
| A table, and the new node is a table | `merge_table` adds the keys of the new one. |
| A list of tables, and the new node is a list of tables | The new tables go after the old ones. |
| Each other case | A finding: `docs/extern/mpbt_project.h.md`, *Messages*. |

The first file is the one that states the key later. The second is the file that stated it first, or that stated its nearest table first.
The values of mpbt are the first document, with the name `mpbt`. Thus a file that states a value of mpbt gets the same finding.
The merge goes on after a finding, so that one run gives each clash.

## Functions

| Function | Result |
| --- | --- |
| `toml_doc_merge` | The old document, with the keys of the new one. |
| `merge_table` | One table, with the keys of a different table. |
| `is_table_list` | Whether a node is a list of tables. |
