# src/shared/lists/lists_write.c

This file writes a list into the persistent arena of a module, in one `alloc`.

## The bytes of a list

A list of `n` items takes `8 * n` bytes for its array of `bridge_text_t`, then the bytes of each item, one after the other.
`lists_get_size` adds these numbers. The module then calls `alloc` once, with that size.
Bridge rounds the size of each `alloc` up to a multiple of 8, so the array keeps the alignment of `bridge_text_t`.

`lists_write` gets the offset that `alloc` gave, and the items. It does these steps:

1. It writes the array at the offset.
2. It copies the bytes of each item after the array, in the order of the items.
3. It gives item `i` the offset and the length of its own bytes.
4. It gives the module the `bridge_text_t` of the whole list: the offset, and `8 * n` as `len`.

A map is a list with each key followed by its value, so `lists_write` writes it in the same way.
A value that is a list itself is written first, as an item whose bytes are its own array and items.

## The limits

The offsets and the lengths are `uint32_t`, as those of `bridge_text_t`. A list that needs more bytes than the share of the module is refused by `alloc`.

## Functions

| Function | Result |
| --- | --- |
| `lists_get_size` | The size of the `alloc` of a list. |
| `lists_write` | The `bridge_text_t` of a written list. |
