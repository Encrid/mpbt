# src/cover/cover_spans.c

This file looks for a public name in the code spans of a document.

## The spans

`cover_get_spans` puts the text of each code span of the lines of text into `spans`, with a line end after each span.
A block of code holds no code span: `docs/intern/shared/markdown/markdown_read.c.md`, *The blocks*.
A document that is not a `mpbt:File` gives no span. Then each name of its header gives a finding, and `layout` names the missing document.

## The names

`cover_is_named` finds the name in `spans` as a word: no letter, digit or `_` touches it on its 2 sides.
Thus a span `sample_add_all` does not hold `sample_add`, and a span `sample_add(a, b)` holds it.

## Functions

| Function | Result |
| --- | --- |
| `cover_get_spans` | The code spans of a document, in `spans`. |
| `cover_is_named` | `true` if a word of the spans is the name. |
