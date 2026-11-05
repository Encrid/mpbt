# src/shared/c_tokens/c_tokens.h

This header declares the one tokenizer of C that the checks `style`, `c23` and `text`, and the check of the messages of the code, share.
Each of them reads the tokens of a file in their order, with their lines and their columns.

## c_token_t

| Field | Value |
| --- | --- |
| `kind` | A name, a number, a string, a character, a mark, a comment, a directive, a space, a line end, or the end of the file. |
| `at`, `len` | The bytes of the token in the file. |
| `line`, `column` | The place of its first byte, each from 1. A tab counts as one column. |

A directive is a whole line that starts with `#`, with each line that a `\` at its end joins to it.

## c_scan_t

| Field | Value |
| --- | --- |
| `text`, `len` | The bytes of the file. |
| `at`, `line`, `column` | The position of the next token. |

## Functions

| Function | Result |
| --- | --- |
| `c_tokens_start` | Starts a scan at the first byte. |
| `c_tokens_next` | Gives the next token. |
| `c_tokens_decode` | Gives the bytes of a string, with its escapes replaced. |
