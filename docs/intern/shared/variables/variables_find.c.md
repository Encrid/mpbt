# src/shared/variables/variables_find.c

This file keeps the entries of a `variables_t` in the order of their names, and finds an entry by a binary search.

## The order

`variables_sort` compares 2 names byte by byte, and a shorter name comes first when it is the start of the other.
The read of the config gives one entry for each name, because each later value replaces the earlier one.
Thus 2 entries never have one name.

## The search

`variables_find` halves the range of the entries at each step. It gives the entry, or none.
A search costs about `log2(n)` comparisons for `n` variables.

## Functions

| Function | Result |
| --- | --- |
| `variables_sort` | The entries in the order of their names. |
| `variables_find` | The entry of a name, or none. |
