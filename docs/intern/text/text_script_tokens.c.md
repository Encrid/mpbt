# src/text/text_script_tokens.c

This file reads the next token of a script of Python, as `text_script.c` needs it.

## The tokens by their first bytes

| First bytes | Token |
| --- | --- |
| A space, a tab, `\r` or `\f` | No token: the scan goes on. |
| `\` before a line end | No token: the line goes on in the next line. |
| `\n` | A line end. |
| `#` | A comment, to the line end. |
| `'''`, `"""`, `'` or `"` | A string: *The strings*. |
| 1 or 2 letters of `rRbBuUfF`, then a quote | A string with a prefix. |
| `(`, `)`, `[`, `]`, `{` or `}` | A bracket. |
| `;` | The end of a statement. |
| A letter, a digit or `_` | A name or a number, to its last letter, digit or `_`. |
| Each other byte | A mark of one byte. |

## The strings

A string of 3 quotes ends after the next 3 quotes of the same kind. It can hold line ends.
A string of 1 quote ends after the next quote of the same kind, or before a line end.
In each string, a `\` makes the next byte a part of the string, so `\"` does not end it.
A string is plain if it has no prefix, or if its prefix has only `r`, `R`, `u` and `U`.

## The limits

A format string can hold a quote of its own kind in its braces, for example `f"{x["a"]}"`. The scan reads such a string as 2 strings.
Then a `#` between the 2 strings can give a comment that is not there.

## Functions

| Function | Result |
| --- | --- |
| `text_next_token` | The next token, or the end of the script. |
| `get_prefix` | How many letters of a prefix come before a quote, or 0. |
| `read_string` | A string, to its end. |
| `read_name` | A name or a number, to its end. |
