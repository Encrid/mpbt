# src/test/test_tree.c

This file gives the small facts of a node and of a location that the visitors of the 3 changed runs share.

## The path of a file

`test_get_path` turns the text of `file` in a location into a path from the root, in these steps:

1. Each `\` becomes `/`.
2. A start that is the whole path of `{root}` and `/` goes. The case of the letters does not count there.
3. Each `.` part goes, and each `..` part takes the part before it away.
4. A path that starts with `src/` or `include/` is a file of the project. Each other path gives none.

zig writes a path as the command or an `#include` gives it, for example `src/../include/<name>.h`. Step 3 gives `include/<name>.h`, the path of its `mpbt:File`.

## The other facts

- `test_is_macro` tells that a location comes from a macro: it has an `expansion`.
- `test_get_child` gives the child at a place of `inner`, or none for a place past the end or for an empty object.
- `test_free_tree` frees a node, its locations, and each node below it.

## Functions

| Function | Result |
| --- | --- |
| `test_get_path` | The path of a file of the project, or none. |
| `test_is_macro` | Whether a location comes from a macro. |
| `test_get_child` | A child of a node, or none. |
| `test_free_tree` | Frees a node and its children. |
