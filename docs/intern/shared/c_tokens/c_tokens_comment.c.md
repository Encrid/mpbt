# src/shared/c_tokens/c_tokens_comment.c

This file reads a comment and a directive to their end.

## A comment

A comment from `/*` ends after the next `*/`. A comment from `//` ends before the line end, and a `\` at the end of the line makes it go on.
A `/*` with no `*/` makes one token to the end of the file.

## A directive

A directive goes from `#` to the line end that no `\` escapes.
The check `style` reads its depth of indent and the name after `#` from it. The check `c23` reads `#include <stdbool.h>` and `#define` of a number from it.

## Functions

| Function | Result |
| --- | --- |
| `read_comment` | A comment, to its end. |
| `read_directive` | A directive, to its end. |
