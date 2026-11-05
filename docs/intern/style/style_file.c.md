# src/style/style_file.c

This file checks one file of C: it reads the tokens, finds the scope, and runs each rule in order.
It also checks the rules of the file as a whole: G1, F6, O3 and G2 of `docs/contributing/coding_style.md`.

## The files

`world_rows` gives each `mpbt:File` to `style_check_file`, which checks it if its path ends with `.c` or `.h`: `docs/extern/mpbt_file.h.md`, *The files of the project*.
After `failed` is set, `style_check_file` gives `false`, and the walk stops.

## The steps

1. `style_read_source` reads the tokens: `src/style/style_source.c`.
2. `style_find_scope` gives the functions of the file, and the statements of its file scope.
3. The rules of the file run in the order of the table below.
4. `style_check_function` checks each function, in the order of the file.

| Order | Rules | File |
| --- | --- | --- |
| 1 | F3, L2 and L3 of the bytes of the lines. | `style_lines.c` |
| 2 | L3 of a comma, a keyword and a call. | `style_spaces.c` |
| 3 | L3 of the operators, and V3. | `style_operators.c` |
| 4 | G1 and F6, then O3, then G2. | This file. |
| 5 | G3, H2, and the rules of each macro. | `style_directives.c` |
| 6 | The rules of the statements of the file scope. | `style_outside.c` |
| 7 | F5 of the pointers to functions, then of the prototypes. | `style_parameters.c` |

## The rules of the whole file

- G1: the first line is `/*`, then `notice_match` with the mark `**` takes the notice of `mpbt:Project`, then the line is `*/`. Else the fault is at line 1, with no column.
- F6: each comment but the notice is a fault, at the comment.
- O3: if the file has more functions than the limit `functions`, the first function past the limit has the fault.
- G2: after the closing bracket of a function, exactly one empty line comes before the next line with text.

The fault of G2 is at the first line after the bracket, with no column, and it belongs to that function.
If no line with text comes after the bracket, the count of the empty lines does not matter.

## Functions

| Function | Result |
| --- | --- |
| `style_check_file` | Checks one file, if its path ends with `.c` or `.h`. |
| `style_has_suffix` | `true` if a path ends with a suffix. |
| `check_comments` | Checks G1 and F6. |
| `check_count` | Checks O3. |
| `check_gaps` | Checks G2. |
