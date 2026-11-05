# src/cla/cla_base64.c

This file turns bytes into the text of base64, and that text back into bytes. The API of GitHub gives and takes the bytes of a file in it.
The form is that of RFC 4648, section 4: https://www.rfc-editor.org/rfc/rfc4648#section-4.

## The text

- Each group of 3 bytes gives 4 characters of the alphabet of the RFC: the ASCII letters, the digits, `+` and `/`.
- The last group gets one `=` for each byte that it lacks.
- GitHub cuts its text into lines. The decoder skips each `\n` and each `\r`.
- The decoder refuses each other character that is not of the text, and a text with a wrong length.

## Functions

| Function | Result |
| --- | --- |
| `cla_base64_encode` | The text of the bytes, in a `buffer_t`. |
| `cla_base64_decode` | `true` and the bytes, or `false` for a text that is not base64. |
