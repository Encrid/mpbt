# src/style/style_parameters.c

This file checks the parameters of the functions, the prototypes and the pointers to functions: F5 of `docs/contributing/coding_style.md`.

## The count

`count_parameters` reads the tokens between 2 parentheses:

- With no token, it gives `STYLE_NONE`. The list must say `void`, so this is a fault.
- With `void` alone, it gives 0.
- Else it gives the count of the `,` out of brackets, plus 1. Thus a `...` counts as one parameter.

A count above the limit `arguments` is a fault too. Each fault is at the `(` of the list.

## The lists

| List | The check |
| --- | --- |
| The parameters of a function that the file defines. A function that a macro makes has none. | `style_check_function` |
| The parameters of a pointer to a function, in each place of the code: `(`, `*`, a name and `)`, then the list. | `style_check_pointers` |
| The parameters of a prototype. | `style_check_prototypes` |

A prototype is a statement of the file scope that ends with a name and its list, and holds no `=`.
It does not start with `typedef` or `static_assert`, and its name is not a keyword or in upper case.
A fault of a prototype belongs to the function of its name. Thus an exception for that function excuses it.

## Functions

| Function | Result |
| --- | --- |
| `style_check_parameters` | Checks the list after a `(`. |
| `count_parameters` | The count of the parameters, or `STYLE_NONE` for an empty list. |
| `style_check_pointers` | Checks the list of each pointer to a function. |
| `style_check_prototypes` | Checks the list of each prototype. |
