# src/shared/buffer/buffer.c

This file grows a `buffer_t` with `realloc`, and keeps a zero byte after its last byte.
Thus a caller can give `bytes` to a function that reads a text that ends with a zero.

## The growth

When the new bytes do not fit, `grow` doubles `size` until they fit, from 64 bytes at the first growth.
Thus a text of `n` bytes costs about `log2(n)` calls of `realloc`.

## The errors

If `realloc` fails, `buffer_add` and `buffer_add_byte` give `false` and keep the old bytes.
The caller then writes the finding of its own work. The fail layer of `test` can make this call fail: `docs/extern/mpbt/fail.h.md`.

## Functions

| Function | Result |
| --- | --- |
| `buffer_add` | `true`, or `false` with no memory. |
| `buffer_add_byte` | `true`, or `false` with no memory. |
| `buffer_clear` | An empty text with its memory. |
| `buffer_free` | A buffer of zeros. |
| `grow` | Room for the new bytes. |
