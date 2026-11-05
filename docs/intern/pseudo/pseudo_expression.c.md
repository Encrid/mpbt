# src/pseudo/pseudo_expression.c

This file reads an expression, the items of a list, and the fields and the elements after a name.

## Expressions

An expression is an operand, then an operator and an operand as many times as they come.
The operators are the words of `operators`: `docs/intern/pseudo/pseudo_words.c.md`, *The words*.

An operand starts with `-` or `NOT` as many times as they come. Then it is one of these:

- a literal;
- an expression between `(` and `)`;
- a name, then the arguments of a call between `(` and `)` if they come, then its fields and its elements.

A field is `.` and a name. An element is `[`, expressions with a comma between them, and `]`.
A call has a name before its `(`. Thus the call of a method, such as `a.b(c)`, is not in the profile.

## Lists

`pseudo_read_list` reads items with a comma between 2 items, then the token that ends the list.
A function of the caller reads each item: an expression, a parameter, or the bounds of a dimension.

## Functions

| Function | Result |
| --- | --- |
| `pseudo_read_expression` | `true` after an expression. |
| `pseudo_read_list` | `true` after the items of a list and its end. |
| `pseudo_read_fields` | Moves past the fields and the elements after a name or a call. |
| `read_operand` | `true` after an operand. |
