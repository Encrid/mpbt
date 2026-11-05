# src/xref/xref_references.c

This file checks each reference of a document: a heading of the same document between 2 asterisks.

## References

A reference is a text between 2 asterisks, outside the code spans and the citations:

1. No letter, digit, `_` or asterisk comes just before the first asterisk, or just after the second.
2. No space comes just after the first asterisk, or just before the second.
3. The text holds no asterisk. Like the heading of a citation, it can hold a line end.

The text must be the text of a heading of the same document: `markdown_has_heading`.
Thus a text in italics that is no heading gives a finding.

## Functions

| Function | Result |
| --- | --- |
| `xref_check_references` | A finding for each reference that names no heading of the document. |
| `read_reference` | The text of the next reference, with a line end in it as one space. |
