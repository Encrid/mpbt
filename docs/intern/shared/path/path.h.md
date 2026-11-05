# src/shared/path/path.h

This header declares the read of a whole file by its path, and the join of a path of the config to a folder.
Each module of mpbt that reads a file, or that starts a relative path of the config in `{root}`, uses it.

## The forms

- A path that a function gets as a C string ends with a zero byte, as the bytes of a `buffer_t` do: `docs/intern/shared/buffer/buffer.h.md`, *buffer_t*.
- A path of the config comes from a `bridge_text_t`, which has no zero byte. Thus `path_join` and `path_is_whole` get its bytes and their count.
- A path that `path_join` gives has `/` between its names, on each system.

## Functions

| Function | File |
| --- | --- |
| `path_read` | `path_read.c` |
| `path_join` | `path_join.c` |
| `path_is_whole` | `path_join.c` |
