# src/shared/markdown/markdown_units.c

This file cuts the text of a document into units. `prose` counts the sentences of each unit, and `dup` compares them.

## The units

`markdown_next_unit` reads the lines of text after the unit that it gets:

1. An empty line, or a line of spaces, ends the unit. A heading, a fence and a line of code end it too.
2. A line that starts with `|`, after spaces, is a row of a table. Each cell of the row is a unit.
3. Each `|` between 2 cells separates them. A `|` at an end of the row is no separator.
4. A `|` inside a code span is a byte of its cell.
5. A line that starts with `-`, `*` or `+` and a space, after spaces, starts an item.
6. A number, a `.` and a space start a step in the same way. The text of the unit starts after this mark.
7. A next line that starts with a space goes on with the item or the step.
8. A next line of a paragraph goes on with the paragraph, if it is no row and no item.
9. Each other line starts a paragraph.

Thus a heading and the lines of a block are in no unit.

## Functions

| Function | Result |
| --- | --- |
| `markdown_next_unit` | `true` and the next unit, or `false` at the end of the document. |
| `read_cell` | The next cell of a row. |
| `read_item` | Tells whether a line starts an item or a step, and where its text starts. |
