# src/style/style_macros.c

This file checks one `#define` of a source: V1, H1, H3 and H4 of `docs/contributing/coding_style.md`.

## The parts of a macro

`c_tokens_next_code` gives the name after `define`: the name of the macro. A `(` that touches the name opens the arguments of the macro.
The body is each token after the name, or after the closing parenthesis of the arguments.

## The rules

| Rule | Fault |
| --- | --- |
| V1 | The name is not in upper case. |
| H3 | A macro with no arguments is a constant: `is_constant_body` accepts its body. |
| H3 | The body holds a `;`, and the macro is not a macro of a text. |
| H1 | The macro is in a file `.c`. |
| H4 | A macro of a text breaks a step of *A macro of a text*. |

`is_constant_body` accepts a body whose first token is a number, a string or a character, after each `-`, `+` and `(`.
Each fault is at the directive. The messages name the macro: `docs/extern/mpbt_check.h.md`, *style*.

## A macro of a text

A macro with no arguments whose body starts with `{` and ends with `}` is a macro of a text.
`check_text_macro` reads the lines of the directive, each with no `\` and no space at its end:

1. The first line ends with `{`, and the macro has 3 lines or more.
2. The last line is `}`, after as many spaces as the first line has before `#`.
3. Each other line starts with 4 spaces more than the first line.
4. Each other line holds text, and one `;` or `,` at most out of its brackets.

## Functions

| Function | Result |
| --- | --- |
| `style_check_define` | Checks one `#define`. |
| `check_text_macro` | Checks H4. |
| `is_constant_body` | `true` if the body of a macro is a constant. |
