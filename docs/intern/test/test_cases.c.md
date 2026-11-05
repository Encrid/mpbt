# src/test/test_cases.c

This file makes a `test_case_t` of each case, with the components of its entity, its false variant and its scripts: `docs/extern/mpbt_case.h.md`, *mpbt:Case*.

## The steps

1. The rows of `mpbt:Run`, `mpbt:Claims` and `mpbt:HelperClaims` go into the order of their ids, with `qsort`.
2. Each row of `mpbt:Case` gives a case. `find_row` gives the run, the claims and the helper claims of the same id.
3. The cases go into the order of their ids. Thus `find_use` finds an owner by a binary search.
4. Each false variant gets its run and its helper claims by its own id. It becomes the `broken` of its owner.
5. The steps go into the order of `owner`, then of `order`.
6. The steps of one owner become the `steps` of its use, for the case or its false variant.

The module `read` writes the whole script of each false variant, also when `false` takes the script of its case: `docs/intern/read/read_case.c.md`, *The false variant*.
Thus a use runs only its own steps, and a false variant with `script = []` runs no step.

## test_get_use

`test_get_use` gives the `use` of a case, or its `broken` with `--break`.
The claims stay those of the case. `docs/extern/mpbt_case.h.md`, *The false variant*, tells why.

## Functions

| Function | Result |
| --- | --- |
| `test_link_cases` | Each case with its components, its false variant and its steps, or `false` with no memory. |
| `test_get_use` | What one run of a case uses. |
| `find_row` | The row of a type with an id, or none. |
| `find_use` | The use of an owner, or none. |
| `compare_steps` | The order of 2 steps by their owners, then by `order`. |
