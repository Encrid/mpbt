# src/shared/lists/lists_read.c

This file reads a list or a map of a component, and the lines of a list of a setting.
It reads the shared memory only, so a module of wasm can use it too.

## A list or a map

`lists_get_count` gives `len / 8` of the list.
`lists_get_item` gives the `bridge_text_t` at `at + 8 * i` of the shared memory. An index past the count gives an item with no bytes.
`lists_find` walks the pairs of a map, and gives the value of the first key with the same bytes. A missing key gives an item with no bytes, and `false`.

## A list of a setting

A setting holds its list as lines: `docs/extern/mpbt/project.h.md`, *Lists and maps*.
`lists_get_line` gives the next line from a position, without its `\n`, and moves the position past it.
At the end of the text, it gives `false`.

## Functions

| Function | Result |
| --- | --- |
| `lists_get_count` | The count of the items of a list. |
| `lists_get_item` | One item, by its index. |
| `lists_find` | The value of a key, and whether it was found. |
| `lists_get_line` | The next line of a setting. |
