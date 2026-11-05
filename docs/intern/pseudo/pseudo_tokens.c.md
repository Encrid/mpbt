# src/pseudo/pseudo_tokens.c

This file cuts a line of pseudo code into tokens, and reads the tokens of a line one at a time.

## The tokens

| Token | Its bytes |
| --- | --- |
| A number | Digits, then a `.` and digits if they come. |
| A string | `"`, the bytes up to the next `"`, and that `"`. |
| A character | `'`, one character, and `'`. |
| A name | A letter, then letters, digits and `_`. |
| A mark | `<-`, `<>`, `<=`, `>=`, `:=` or `//`. |
| Each other byte | One token. The bytes of a character of UTF-8 make one token. |

Spaces separate the tokens, and are no tokens. A `"` with no second `"` on the line is no string.
A literal is a number, a string, a character, `TRUE` or `FALSE`.
A keyword is a word of `docs/intern/pseudo/pseudo_words.c.md`, *The words*. A keyword is no name.

## Functions

| Function | Result |
| --- | --- |
| `pseudo_read_tokens` | The tokens of a line. |
| `pseudo_get_token` | The token at an index, or an empty token after the last one. |
| `pseudo_read_token` | `true` if the next token is a given text, and moves past it. |
| `pseudo_read_name` | `true` if the next token is a name, and moves past it. |
| `pseudo_is_literal` | `true` if a token is a literal. |
