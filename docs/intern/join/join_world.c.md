# src/join/join_world.c

This file declares the types of `join`, and reads its rows. `src/shared/world/world.h` does the work with Bridge.

## The steps

1. `join_declare` passes the types of `docs/intern/join/join.c.md`, *The components*, to `world_declare`, and adds the system `join`.
2. `join_read_world` reads `mpbt:Command` from its kept cell, and the other types with `world_rows`.

## Functions

| Function | Result |
| --- | --- |
| `join_declare` | 0, or 1 if Bridge refuses a call. |
| `join_read_world` | The rows of one call of `join`. |
| `keep_row` | Copies the place of one row into the state. |
