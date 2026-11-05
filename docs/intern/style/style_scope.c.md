# src/style/style_scope.c

This file finds the functions and the statements of the file scope of a source, from its `tokens`.

## The walk

The walk reads the tokens of the file scope in their order:

1. A `;` ends a statement. Its first token and its last token go into `statements`.
2. A `{` that `take_function` accepts starts a function. A new statement starts after its closing bracket.
3. Each other `{` is a part of the statement, for example of a `struct` or of a value. The walk jumps to its closing bracket.

## A function

`take_function` accepts a `{` if the tokens of the statement before it obey these rules:

1. The last token is `)`, and no token is `=`.
2. The token before the `(` of that `)` is a name, and `style_is_keyword` refuses it.

A name in upper case is a macro that makes the function, for example `BRIDGE_NATIVE(init)`.
Then the name of the function is the token between the parentheses of the macro.

## Functions

| Function | Result |
| --- | --- |
| `style_find_scope` | `true` and the scope, or `false` if a list cannot grow. |
| `take_function` | `true` and a `style_function_t`, if a `{` starts a function. |
