# src/test/test_tree_read.c

This file reads a syntax tree of `-ast-dump=json` from the reader of `src/shared/json`, token after token, into `test_node_t`.
It keeps only the nodes that a run needs, and skips the rest of the tree.

## The order of the keys

The top is the object of `TranslationUnitDecl`. Its `inner` holds the nodes at the top: the declarations of each file that the source includes.
zig writes `id`, `kind`, `loc` and `range` first in a node, and `inner` last.
Thus the reader knows the kind, the place and the name of a node before it reads its `inner`.

## The nodes at the top

`is_kept` keeps a node at the top in these cases:

1. Its `loc` is in a file of `src` or of `include`. A `loc` with no offset gives way to `begin` of `range`.
2. Its kind is `TypedefDecl`. The visitor needs the types of the names of `typedef`.
3. Its kind is `FunctionDecl`, its `name` is a name of the run, and it is not `isImplicit`.

`read_node` reads a kept node whole, with its children. Each item of `inner` is a child, and an empty object is a child with no node.
The visitor gets the node, and `test_free_tree` frees it after the visitor returns.
`skip_node` skips each other node: it reads only its locations, and `json_skip` skips each other value.

## The file of a location

The dump writes `file` in a location only when the file differs from that of the location before it, in the order of the document.
Thus the reader keeps the last `file`, also in each node that it skips.

1. In a location of a macro, `read_location` reads `spellingLoc` first, then `expansionLoc`. Each one can change the last file.
2. The location then takes the last file: the file of the expansion.
3. A `file` in `includedFrom` names the file that includes, so it does not change the last file.

`test_get_path` turns the last file into a path from the root. A file outside `src` and `include` gives no path.

## Functions

| Function | Result |
| --- | --- |
| `test_read_tree` | Gives each kept node at the top to the visitor, or a fault of the JSON. |
| `read_node` | A node and its children. |
| `read_location` | A location, with its file. |
| `skip_node` | Reads past a node, and keeps the last file of its locations. |
| `is_kept` | Whether a node at the top goes to the visitor. |
