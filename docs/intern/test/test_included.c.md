# src/test/test_included.c

This file finds the byte of a source after its last `#include`. The block of a new name goes there: `test_rename.c`.
No header sees the new name, because each header comes before that byte.

## The steps

1. `get_directive` gives the name of the directive of each line: `include`, `if`, `endif` and so on. A blank line gives an empty name, and a line of code gives none.
2. The last line with `include` is the end.
3. `find_endif` pairs each `#if`, `#ifdef` and `#ifndef` with its `#endif`.
4. An `#if` around the end that holds only directives and blank lines moves the end to its `#endif`.
5. The inner `#if` comes first, then the outer ones. The first `#if` with a line of code stops the moves.
6. The byte is the first byte of the line after the end. A source with no `#include` gives 0.

A directive is a line whose first byte that is not a space or a tab is `#`. Spaces and tabs can come between `#` and the name.
Thus a block such as `#ifdef _WIN32` with only `#include` lines in it keeps the new name out of each header in it.

## Functions

| Function | Result |
| --- | --- |
| `test_find_included` | The byte after the last `#include`. |
| `get_directive` | The name of the directive of a line, an empty name, or none. |
| `find_endif` | The line of the `#endif` of each `#if` that holds the end. |
