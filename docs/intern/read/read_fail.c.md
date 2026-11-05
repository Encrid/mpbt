# src/read/read_fail.c

This file writes an entity with `mpbt:FailCall` for each function of `[fail.calls]` that a case can make fail: `docs/extern/mpbt_fail.h.md`.

## The steps

1. `calls` of `read_t` starts with `malloc`, `calloc` and `realloc`, which can always fail.
2. `read_with_tables` gives `[fail]`, then the table `[fail]` of each file of `with`.
3. Each key of `calls` of each table gives a function, with its value of C as a text.
4. A function that `calls` holds already stops the read, with its message of `docs/extern/mpbt_fail.h.md`, *Messages*. A table that names `malloc` stops it too.
5. Each other function goes into `calls`, then into an entity with `mpbt:FailCall`.

`malloc`, `calloc` and `realloc` get no entity, because `test` adds them with the value `nullptr` itself.
Later, `read_case` asks `read_is_listed` for each function of `fail`, in the case and in `false`.

## Functions

| Function | Result |
| --- | --- |
| `read_fail` | `true` after each entity of `mpbt:FailCall`, or `false` and a finding. |
| `read_is_listed` | Whether a function is in `calls` of `read_t`, also `malloc`, `calloc` and `realloc`. |
