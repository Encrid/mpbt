# src/style/style_declaration.c

This file tells whether a statement declares a variable, and finds the name of the variable.
`src/style/style_outside.c` uses it for the file scope, and `src/style/style_statement.c` for a body.

## The form of a declaration

The tokens of a declaration come in this order. A part with "if any" can be absent.

1. The attributes `[[ ]]` and the qualifiers of `style_is_qualifier`, if any.
2. Any name, as the type. Or `struct`, `enum` or `union` with its name.
3. More words of a type and `const`, if any.
4. The marks `*` and the word `const`, if any.
5. `(` and `*` of a pointer to a function, if any.
6. The name of the variable.
7. The `)` and the list of step 5, if any, then each `[ ]`.
8. `=`, `,` or the end of the statement.

`skip_head` skips step 1, `skip_type` skips the steps 2 to 5, and `skip_tail` skips step 7.

## A constant

A declaration declares a constant if `const` or `constexpr` is before its first `=`, and after its last `*`.
Thus `char *const name` declares a constant, and `const char *name` does not.

## Functions

| Function | Result |
| --- | --- |
| `style_get_declared` | The token of the name of the variable, or `STYLE_NONE`. |
| `style_is_constant` | `true` if a declaration declares a constant. |
| `skip_head` | The token after the attributes and the qualifiers. |
| `skip_type` | The token after the type and the stars. |
| `skip_tail` | The token after the parameters and the arrays. |
