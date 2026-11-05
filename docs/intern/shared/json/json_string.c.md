# src/shared/json/json_string.c

This file reads a string of JSON into `text`, and replaces each escape with its bytes.

## The escapes

| Escape | Bytes |
| --- | --- |
| `\"`, `\\`, `\/` | The byte after the backslash. |
| `\b`, `\f`, `\n`, `\r`, `\t` | The control byte. |
| `\u` and 4 hexadecimal digits | The character, in UTF-8. |
| `\u` of a high surrogate, then `\u` of a low surrogate | The character of the pair, in UTF-8, as 4 bytes. |

A surrogate with no pair, or a control byte before the end quote, gives `JSON_FAULT`.

## Functions

| Function | Result |
| --- | --- |
| `json_read_string` | The bytes of a string, or a fault. |
| `read_escape` | The bytes of one escape. |
| `put_utf8` | Writes a character as UTF-8. |
