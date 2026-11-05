# src/style/style_operators.c

This file checks the spaces around the operators, and where the pointer symbol is: L3 and V3 of `docs/contributing/coding_style.md`.

## The rules

As in `src/style/style_spaces.c`, a rule reports a line one time at most, at the operator.

- L3, unary: `!` or `~` with a space after it on its line.
- L3, unary: `++` or `--` that touches no operand. Its operand is a name, a number, `)` or `]` before it, or a name, a number or `(` after it.
- L3, spaced: an operator of the list below touches the token before it or the token after it, on its line. The fault names the operator.
- L3, binary: `+`, `-`, `*`, `&` or `|` touches the token before it and the token after it.
- V3, attached: a word of a type, one `*` or more that touch it, a space, then a name or `(`.
- V3, apart: a word of a type, a space, one `*` or more, a space, then a name.

For the binary rule, the token before is a name, a number or `]`, and the token after is a name, a number or `(`.
A `)` before `+` or `|` counts too. A `)` before `-`, `*` or `&` does not, because a cast comes before a unary operator.

The spaced operators are `=`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `<<`, `>>`, `&&`, `||`, `?`, `/`, `%` and `^`.
Each assignment with an operator is one too, for example `+=` or `<<=`. `->` is not an operator of the list.
The words of a type are those of `src/style/style_words.c`. The messages are in `docs/extern/mpbt_check.h.md`, *style*.

## Functions

| Function | Result |
| --- | --- |
| `style_check_operators` | Runs the rules of the operators and of the pointers. |
| `check_unary` | Checks the unary operators. |
| `check_spaced` | Checks the operators of the list. |
| `check_binary` | Checks the binary operators. |
| `check_pointers` | Checks V3. |
