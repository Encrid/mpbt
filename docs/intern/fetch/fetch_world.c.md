# src/fetch/fetch_world.c

This file takes the rows that the systems of `fetch` read, with `world_rows` of `src/shared/world/world.h`.

## The rows

`fetch_get_world` gives each type to `world_rows`, with the slot of the system that runs:

- `keep_variable` keeps the 3 rows of `mpbt:Variable` named `root`, `zig` and `home`, with `MPBT_SCOPE_PROJECT`. They give the fields of `fetch_t` with these names.
- `keep_source` adds each row of `mpbt:Source` to `sources`, in the order of the walk.
- `bridge_check_fetched` also reads `name` of `mpbt:Command`, from its kept cell.

The texts stay in the shared memory for the whole phase, and `fetch_t` copies no byte of them.
`fetch_free_world` gives back the array of `sources`, which is the only memory of `fetch_t`.

## The findings

`finding_write` and `finding_format` of `src/shared/finding/finding.h` write each fault of `fetch`, with `finding` of `fetch_t`. Then `findings` grows by 1.
The line and the column are 0, because each message of `fetch` names its place itself.

## Functions

| Function | Result |
| --- | --- |
| `fetch_get_world` | `true` when `fetch_t` holds the rows, or `false` with no memory. |
| `fetch_free_world` | Gives the memory of `fetch_t` back. |
| `keep_variable` | Keeps a row of `mpbt:Variable` if it is `root`, `zig` or `home`. |
| `keep_source` | Adds a row of `mpbt:Source` to `sources`, or `false` with no memory. |
