# src/shared/c_tokens/c_tokens_decode.c

This file gives the bytes of a string token, with its escapes replaced, into a `buffer_t`.
The check of the messages compares these bytes with the output of the cases: `docs/extern/mpbt_case.h.md`, *The messages of the code*.

## The escapes

| Escape | Bytes |
| --- | --- |
| `\n`, `\t`, `\r`, `\a`, `\b`, `\f`, `\v` | The control byte. |
| `\\`, `\'`, `\"`, `\?` | The byte after the backslash. |
| `\` and 1 to 3 octal digits | The byte of that value. |
| `\x` and hexadecimal digits | The byte of that value. |
| `\u` and 4, or `\U` and 8, hexadecimal digits | The character, in UTF-8. |

2 string tokens with only spaces, line ends and comments between them make one text, as in C.
The caller gives the first token, and `c_tokens_decode` reads the next ones from the scan.

## Functions

| Function | Result |
| --- | --- |
| `c_tokens_decode` | The bytes of the strings that follow each other. |
| `decode_escape` | The bytes of one escape. |
