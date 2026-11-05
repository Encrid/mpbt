# src/shared/files/files.c

This file sorts the files that a check keeps by their paths, and finds a path among them with a binary search.

## The order of 2 paths

`files_compare` compares the bytes of 2 paths, from their first byte:

1. The first byte that is different decides. A `/` comes before each other byte.
2. If one path is the start of the other, the shorter path comes first.

Thus the paths come in the order of their names, folder by folder. For example, the files of the folder `a` come before the file `a.b`.
The compare keeps the case of the letters: `A` and `a` are 2 different bytes. Thus the order is the same on each system.

## The search

`files_sort` sorts the items with `qsort`, and `files_find` finds a path with `bsearch`. Both use `files_compare`.
A search costs about `log2(n)` compares for `n` files.

## Functions

| Function | Result |
| --- | --- |
| `files_sort` | The items, sorted with `files_compare`. |
| `files_find` | The item of a path, or none. |
| `files_compare` | Less than 0, 0 or more than 0, as `memcmp` gives it. |
| `compare_items` | The order of 2 items, for `qsort`. |
| `compare_key` | The order of a path and an item, for `bsearch`. |
