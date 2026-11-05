# src/take/take_list.c

This file reads the list of a dependency, for example the `package.txt` of a different project: `docs/extern/mpbt_dependency.h.md`, *[[dependency]]*.

## The lines

`take_read_list` reads the file of `list` of `take_dependency_t` with `path_read` of `src/shared/path/path.h`, and splits it at each `\n` into lines with no `\r`.
A list that is there, and that `path_read` cannot read, is a fault: `docs/extern/mpbt_command.h.md`, *Messages*.
`add_line` reads one line:

| The first word | The line gives |
| --- | --- |
| 64 lower-case hexadecimal digits, as `is_digest` tells | A pair of `files`: the digest, and the rest of the line with no space at its 2 ends. |
| Each other word | A pair of `keys`: the word, and the rest of the line with no space at its 2 ends. |
| No word | Nothing. |

A word ends at the first space. The form of the lines is in `docs/extern/mpbt_compose.h.md`, *package.txt*.
The bytes of the file stay in a `buffer_t` of the dependency, and each pair points into them.

## Functions

| Function | Result |
| --- | --- |
| `take_read_list` | `true` when the pairs of the list are read, else `false` and the finding. |
| `add_line` | Adds the pair of one line, if the line has a word. |
| `is_digest` | Whether a word is a SHA-256 digest in hexadecimal. |
