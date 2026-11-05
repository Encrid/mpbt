# src/text/text_comment.c

This file finds the comments of a file `.toml` or `.yml`, and of a document.

## TOML and YAML

A comment starts at each `#` that is in no string, and ends at the line end.
A string starts at `"""`, `'''`, `"` or `'`:

- A string of `"""` ends after the next `"""`, and a string of `'''` after the next `'''`.
- A string of `"` ends after the next `"` of its line. In it, the byte after a `\` does not end it.
- A string of `'` ends after the next `'` of its line.
- A quote with no end on its line is a byte of the text, and the scan goes on after it.

## A document

A document holds no comment of HTML. Such a comment starts with the 4 bytes `<`, `!`, `-` and `-`, in this order.
Each line that holds them gets a finding.

## Functions

| Function | Result |
| --- | --- |
| `text_check_hashes` | A finding for each comment of a file `.toml` or `.yml`. |
| `skip_string` | The position after a string, or after its first quote if the string has no end. |
| `text_check_markup` | A finding for each line of a document with a comment of HTML. |
