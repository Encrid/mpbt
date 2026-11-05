# src/style/style_statement.c

This file checks one statement of a body: L1, L5, V1, C2 and C3 of `docs/contributing/coding_style.md`.

## The steps

1. `style_start_line` checks where the statement starts.
2. `find_end` gives the `;` out of brackets, or else the last token of the body.
3. A statement that starts with `goto` is a fault of C3.
4. A declaration goes to `check_declaration`, and each other statement to `check_expression`.
5. `extra` goes back to 0, and `ended` takes the line of the end.

A statement is a declaration if `style_get_declared` finds a name, and its first word is not `return`, `goto`, `break` or `continue`.

## The rules

| Rule | Fault |
| --- | --- |
| L5 | A declaration is in a nested block, after a control with no brackets, or after a statement that is not a declaration. |
| L5 | A declaration holds a `,` out of brackets. |
| V1 | The name of a declaration is not in snake case. A constant can have a name in upper case. |
| L1 | A statement that is not a declaration holds a `,` out of brackets, or 2 `=` or more out of brackets. |
| C2 | A statement holds 2 `?` or more. |
| C2 | A statement holds a `?` out of brackets and no assignment, and does not start with `return`. |

The fault of V1 is at the name, and each other fault at the first token of the statement.
`declared` takes the line of the `;` of each declaration at the start of the body, for L6.

## Functions

| Function | Result |
| --- | --- |
| `style_check_statement` | Checks a statement, and gives the token after its end. |
| `find_end` | The last token of a statement. |
| `check_declaration` | Checks L5 and V1. |
| `check_expression` | Checks L1 and C2. |
