# src/style/style_function.c

This file checks one function that a source defines: F2, F4, F5, L4, L6, H1 and G5 of `docs/contributing/coding_style.md`.
`style_walk_body` of `src/style/style_body.c` checks the tokens of its body.

## The rules of the function

| Rule | Fault |
| --- | --- |
| F2 | The name is not in snake case. |
| F5 | `style_check_parameters` checks the list. A function that a macro makes has no such check. |
| F4 | Between the lines of its 2 brackets, the body takes more lines than the limit `lines`. |
| L4 | The opening bracket or the closing bracket shares its line with another token of the code. |
| H1 | In a file `.h`, the tokens before the name do not hold both `static` and `inline`. In a file `.c`, they hold `inline`. |
| G5 | In a file `.c`, the function is not `static`, and `style_is_declared` does not find its name. |

G5 excuses `main`, a function that a macro makes, and a function that the code exports.
The code exports a function if the tokens before its name hold `dllexport` or `visibility`, or a name that ends with `EXPORT` or `_API`.
The fault of F4 is at the opening bracket, and each fault of L4 at its bracket. Each other fault is at the name.

## L6

`style_is_empty_line` tells which lines between the 2 brackets are empty.

1. If the body starts with declarations and has statements after them, the line after the last declaration must be empty.
2. Each other empty line of the body is a fault.

Each fault of L6 is at its line, with no column.

## Functions

| Function | Result |
| --- | --- |
| `style_check_function` | Checks one function, and walks its body. |
| `check_brackets` | Checks F4 and L4. |
| `check_empty_lines` | Checks L6. |
| `check_linkage` | Checks H1 and G5. |
| `is_exported` | `true` if the code exports a function. |
