# src/take/take_world.c

This file takes the rows that the system `take` reads, with `world_rows` of `src/shared/world/world.h`.

## The rows

`world_rows` walks the query of `take` for each type, and `take_get_world` gets the rows:

- `keep_variable` keeps the project variable `root` as `root` of `take_t`.
- `keep_dependency` adds each row of `mpbt:Dependency` to `dependencies`, in the order of the walk. `path_join` of `src/shared/path/path.h` puts a `from` or an `into` that is not whole after `{root}`.
- `keep_agree` adds each row of `mpbt:Agree` to `agrees`.

A row lasts as long as the phase, so `take_t` copies only the paths that it makes whole.
`take_free_world` gives back the paths, the lists and the copies of `take_t`.

## The findings

A fault of `take` goes to `finding_write` or to `finding_format` of `src/shared/finding/finding.h`, with `finding` of `take_t`.
Its line and its column are 0. Then `findings` of `take_t` grows by 1.

## Functions

| Function | Result |
| --- | --- |
| `take_get_world` | `true` with the variable, the dependencies and the rules in `take_t`, or `false` with no memory. |
| `take_free_world` | Gives the memory of `take_t` back. |
| `keep_variable` | Keeps the row of `mpbt:Variable` named `root`. |
| `keep_dependency` | Adds a row of `mpbt:Dependency`, or `false` with no memory. |
| `keep_agree` | Adds a row of `mpbt:Agree`, or `false` with no memory. |
