# src/style/style_spaces.c

This file checks the space after a comma and after a keyword, and before the parenthesis of a call: L3 of `docs/contributing/coding_style.md`.

## The rules

Each rule walks `tokens`, and keeps the line of its last fault. Thus it gives one fault on a line at most, at the first token that breaks it.
Two tokens touch when no byte is between them, as `style_touch` tells.

| Rule | Fault |
| --- | --- |
| A comma | A `,` touches the next token of its line. |
| A keyword | `if`, `while`, `for` or `switch` touches the `(` after it. `return` touches a token that is not `;`. |
| `sizeof` | A space or a tab comes after `sizeof`, on its line. |
| A call | A name that starts with a lower-case letter or `_`, a space, then a `(` whose next token is not `*`. |

A keyword, a word of a type and a qualifier of `src/style/style_words.c` make no fault of a call.
The fault of a call names the name. The messages are in `docs/extern/mpbt_check.h.md`, *style*.

## Functions

| Function | Result |
| --- | --- |
| `style_check_spaces` | Runs the 4 rules. |
| `check_commas` | Checks the space after each comma. |
| `check_keywords` | Checks the space after each keyword. |
| `check_sizeof` | Checks that no space comes after `sizeof`. |
| `check_calls` | Checks that no space comes before the parenthesis of a call. |
