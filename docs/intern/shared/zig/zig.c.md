# src/shared/zig/zig.c

This file finds the row of the pin of zig for a target, and makes the address of its archive: `docs/extern/mpbt_source.h.md`, *zig*.

## The row

`zig_find_archive` compares the name of the target with `target` of each row of `ZIG_ARCHIVES`, byte by byte.
A target with no row has no archive of zig, and the result is none.

## The address

`zig_add_address` adds these texts to a `buffer_t`, one after the other:

1. `https://ziglang.org/download/`, then `ZIG_VERSION`, then `/zig-`.
2. `host` of the row, then `-`, then `ZIG_VERSION`.
3. `.`, then `format` of the row.

In its messages, `fetch` names the archive by the last name of its address.

## Functions

| Function | Result |
| --- | --- |
| `zig_find_archive` | The row of a target, or none. |
| `zig_add_address` | `true` after the address of a row, or `false` with no memory. |
