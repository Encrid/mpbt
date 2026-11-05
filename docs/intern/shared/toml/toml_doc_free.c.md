# src/shared/toml/toml_doc_free.c

This file gives back the memory of a document: each node, each copied text, and the names of the files.
A node of a merged document is in one document only, because the merge moves nodes and does not copy them.
Thus one walk of the tree from `root` frees each node one time.

## Functions

| Function | Result |
| --- | --- |
| `toml_doc_free` | A document with no memory. |
| `free_node` | Frees a node and the nodes below it. |
