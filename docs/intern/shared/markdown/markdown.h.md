# src/shared/markdown/markdown.h

This header declares a document of Markdown, cut into lines, blocks of code and units, and the functions that read it.
The checks `prose`, `pseudo`, `dup`, `xref` and `cover` read each document through it. Thus each of them cuts a document in the same way.

## markdown_line_t

| Field | Value |
| --- | --- |
| `at`, `len` | The bytes of the line, with no line end. |
| `kind` | What the line is: *The kinds of a line*. |
| `level` | The count of `#` of a heading, or 0. |

## The kinds of a line

`enum markdown_line_kind : uint8_t` tells what a line is.

| Constant | The line |
| --- | --- |
| `MARKDOWN_TEXT` | A line of text. |
| `MARKDOWN_FENCE` | The first or the last line of a block of code. |
| `MARKDOWN_CODE` | A line between the 2 fences of a block. |
| `MARKDOWN_HEADING` | A heading, outside the blocks. |

## markdown_block_t

| Field | Value |
| --- | --- |
| `first`, `last` | The lines of its 2 fences, from 1. |
| `tag`, `tag_len` | The tag of the block: the text after the backticks of its first fence. |

## markdown_doc_t

| Field | Value |
| --- | --- |
| `lines`, `count` | Each line of the document, from `malloc`. |
| `blocks`, `block_count` | Each block of code, in the order of the lines, from `malloc`. |

The document holds no copy of the bytes. Thus the bytes of the caller must stay while a check reads the document.

## markdown_unit_t

A unit is a part of the text that holds sentences: `docs/intern/shared/markdown/markdown_units.c.md`, *The units*.

| Field | Value |
| --- | --- |
| `kind` | What the unit is: *The kinds of a unit*. |
| `line`, `last` | The first and the last line of the unit, from 1. |
| `at`, `end` | The bytes of the unit, from its first byte to the byte after its last byte. |

A unit of zeros is the start of the document. `markdown_next_unit` gives the unit that comes after the unit that it gets.

## The kinds of a unit

`enum markdown_unit_kind : uint8_t` tells what a unit is.

| Constant | The unit |
| --- | --- |
| `MARKDOWN_PARAGRAPH` | A paragraph. |
| `MARKDOWN_ITEM` | An item of a list. |
| `MARKDOWN_STEP` | An item of a numbered list. |
| `MARKDOWN_CELL` | A cell of a table. |

## Functions

| Function | Result |
| --- | --- |
| `markdown_read` | Reads a document: its lines, its blocks and its headings. |
| `markdown_free` | Gives the memory of a document back. |
| `markdown_get_heading` | Reads one heading. |
| `markdown_has_heading` | Tells whether a document has a heading with a given text. |
| `markdown_next_unit` | Gives the next paragraph, item, step or cell. |
| `markdown_next_sentence` | Gives the next sentence of a unit. |
| `markdown_next_word` | Gives the next word of a sentence. |
| `markdown_next_span` | Gives the next code span of a text. |
| `markdown_is_document` | Tells whether `prose`, `pseudo` and `dup` read a file. |
