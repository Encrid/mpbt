# src/shared/buffer/buffer.h

This header declares a text that grows: the parts of mpbt that make a text of a length they cannot know first use it.
Examples are an expanded variable, a JSON document and a line of a finding.

## buffer_t

| Field | Value |
| --- | --- |
| `bytes` | The bytes, from `malloc`, with one zero byte after the last byte. |
| `len` | The count of the bytes, with no zero byte. |
| `size` | The count of the bytes that `bytes` can hold. |

A `buffer_t` of zeros is an empty text that holds no memory yet.

## Functions

| Function | Result |
| --- | --- |
| `buffer_add` | Adds bytes at the end. |
| `buffer_add_byte` | Adds one byte at the end. |
| `buffer_clear` | Sets the length to 0, and keeps the memory. |
| `buffer_free` | Gives the memory back. |
