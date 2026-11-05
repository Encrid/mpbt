# src/shared/markdown/markdown_read.c

This file cuts the bytes of a document into lines, and gives the kind of each line.

## The lines

A line ends at a `\n`. A `\r` just before the `\n` is not in the line, so `\r\n` and `\n` end a line in the same way.
The lines count from 1, as the lines of a finding do.

## The blocks

A fence is a line that starts with 3 backticks, after spaces. Its tag is the text after the backticks, with no spaces at its ends.
A fence opens a block, and the next fence closes it. The lines between the 2 fences are the code of the block.
A fence that no other fence follows opens no block. Thus it and the lines after it stay text.

## The headings

A heading is a line outside the blocks that starts with 1 to 6 `#`, a space, and a text.
Its level is the count of its `#`. Its text is the rest of the line, with no spaces at its 2 ends.
`markdown_has_heading` compares a text with the text of each heading of a document, byte for byte.

## Functions

| Function | Result |
| --- | --- |
| `markdown_read` | `true` and the document, or `false` with no memory. |
| `markdown_free` | Gives the lines and the blocks back. |
| `markdown_get_heading` | The level and the text of a heading, or 0 for a line that is no heading. |
| `markdown_has_heading` | `true` if a heading of the document has the text. |
| `read_fence` | `true` and the tag, if the line is a fence. |
