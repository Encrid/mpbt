# src/style/style_names.c

This file gathers the names that the headers of the project declare. A function that a header declares needs no `static`: G5 of `docs/contributing/coding_style.md`.

## The steps

1. `world_rows` gives each `mpbt:File`, and `add_names` reads each one whose path ends with `.h`.
2. `c_tokens_next_code` gives its tokens, and each name that has `(` as its next token counts.
3. The place and the length of each name go into `names`. The bytes stay in the shared memory.
4. After the last header, `qsort` puts the names in the order of their bytes.
5. `style_is_declared` finds a name with `bsearch`.

The scan skips the spaces, the line ends, the comments and the directives. Thus a call in the text of a macro does not count.

## Functions

| Function | Result |
| --- | --- |
| `style_read_names` | `true` and `names`, or `false` with no memory. |
| `add_names` | Adds the names of one header. |
| `compare_names` | The order of 2 names, by their bytes. |
| `style_is_declared` | `true` if a header declares the name. |
