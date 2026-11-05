# src/style/style_outside.c

This file checks each statement of the file scope: V1, H1 and G4 of `docs/contributing/coding_style.md`.

## The kind of a statement

`get_statement_kind` skips the attributes `[[ ]]` at the start. Then the first of these tests that holds gives the kind:

1. `STYLE_TYPEDEF`: the first token is `typedef`.
2. `STYLE_TYPE`: `struct`, `enum` or `union` first, then a `{` with no `=` and no `(` before it.
3. `STYLE_OTHER`: the first token is `static_assert`, or a name in upper case and `(` as the call of a macro.
4. `STYLE_PROTOTYPE`: the statement ends with `)`, and holds no `=`.
5. `STYLE_VARIABLE`: `style_get_declared` finds the name of a variable.
6. `STYLE_OTHER` for each other statement.

A `switch` on the kind runs the rules of the kind.

## The rules

| Kind | Fault |
| --- | --- |
| `STYLE_TYPEDEF` | V1: the name of the type does not end with `_t`. H1: the statement is in a file `.c`. |
| `STYLE_TYPE`, `STYLE_PROTOTYPE` | H1: the statement is in a file `.c`. |
| `STYLE_VARIABLE` | G4: `style_is_constant` refuses the declaration. V1: a constant has a name that is not in upper case. |

The name of a type is the last name of the statement, before a last `[ ]`.
For a pointer to a function with no `{`, it is the name in `(*name)`.
In each statement, `check_enum_items` checks that each item of an `enum` with a `{` is in upper case: V1.

A fault that names a name is at that name, and each other fault at the start of the statement.

## Functions

| Function | Result |
| --- | --- |
| `style_check_outside` | Checks each statement of the file scope. |
| `get_statement_kind` | The kind of a statement. |
| `check_typedef` | Checks the name of a type. |
| `check_variable` | Checks a global variable. |
| `check_enum_items` | Checks the case of each item of an enum. |
