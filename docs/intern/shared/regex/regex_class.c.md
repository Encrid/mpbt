# src/shared/regex/regex_class.c

This file makes the set of bytes of a class: 256 bits, one for each byte.

## The sets

| Class | Bytes |
| --- | --- |
| `.` | Each byte, also the line end, as the claim `matches` asks. |
| `\d` | `0` to `9`. |
| `\w` | `a` to `z`, `A` to `Z`, `0` to `9` and `_`. |
| `\s` | The space, and the bytes 9 to 13. |
| `\D`, `\W`, `\S` | The bytes that the class of the lower-case letter does not hold. |
| `[...]` | Each byte, each range `a-z` and each class of the list. |
| `[^...]` | The bytes that `[...]` does not hold. |

In a list, `\` makes the next byte a byte, so `\]` and `\-` are bytes. A `-` at the start or at the end of the list is a byte.

## The limits

A pattern works on bytes. Thus `\w` holds no letter that is not ASCII, and `.` is one byte of a character of UTF-8.
The projects of mpbt write ASCII, so a claim sees the same output as a person.

## Functions

| Function | Result |
| --- | --- |
| `class_parse` | The set of a list in brackets. |
| `class_escape` | The set of `\d`, `\w`, `\s` and their negations. |
| `class_add_range` | Sets the bits of a range. |
| `class_invert` | The bytes that a set does not hold. |
