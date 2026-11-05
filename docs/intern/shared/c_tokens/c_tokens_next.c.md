# src/shared/c_tokens/c_tokens_next.c

This file decides the kind of the next token by its first bytes, and gives the token.

## The kinds by their first bytes

| First bytes | Token |
| --- | --- |
| A space or a tab | The run of spaces and tabs. |
| A line end, `\n` or `\r\n` | One line end. |
| A letter or `_` | A name: letters, digits and `_`. A name before a quote, such as `u8`, starts a string. |
| A digit, or `.` and a digit | A number: `c_tokens_literal.c`. |
| `"` or `'` | A string or a character: `c_tokens_literal.c`. |
| `/*` or `//` | A comment: `c_tokens_comment.c`. |
| `#` as the first byte of a line, after spaces | A directive: `c_tokens_comment.c`. |
| Each other byte | A mark: the longest one of C, for example `<<=`. |

A `\` at the end of a line joins it to the next line, inside a token or between 2 tokens. The column then starts again at 1.

`c_tokens_next_code` calls `c_tokens_next` until a token is not a space, a line end or a comment.
`c_tokens_start_directive` starts a scan of the bytes of a directive after its `#`, at the line and the column of those bytes. Thus a check reads the name and the words of a directive as tokens.

## Functions

| Function | Result |
| --- | --- |
| `c_tokens_start` | A scan at the first byte. |
| `c_tokens_next` | The next token, or the end. |
| `c_tokens_next_code` | The next token of code, or the end. |
| `c_tokens_start_directive` | A scan of the words of a directive. |
| `read_name` | A name, or the prefix of a string. |
| `read_mark` | The longest mark at the position. |
