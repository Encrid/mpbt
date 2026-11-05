# src/shared/markdown/markdown_spans.c

This file finds the code spans of a text.

## A code span

A code span is a backtick, 1 byte or more with no backtick and no line end, then a backtick.
A lone backtick, with no other backtick after it on the line, stays a plain byte.
`prose` counts a span as one word, and `dup` compares its words. `xref` finds a path in it, and `cover` finds a public name in it.

## Functions

| Function | Result |
| --- | --- |
| `markdown_next_span` | `true` and the text of the next span with no backticks, or `false` when the text holds no more span. |
