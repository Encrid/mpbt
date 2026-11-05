# src/pack/pack_world.c

This file holds the work of `pack` with Bridge that is its own. `src/shared/world/world.h` gives the rest.

## The steps

1. `pack_declare` names the types of `docs/intern/pack/pack.c.md`, *The components*, to `world_declare`, then adds the system `pack`.
2. `pack_read_world` takes the rows of each type from `world_rows`, and the 2 singletons from their kept cells.
3. `steps` gets the 4 types that `steps_make` reads, for the build of a proof.

## Functions

| Function | Result |
| --- | --- |
| `pack_declare` | 0 when each declaration passes, or 1. |
| `pack_read_world` | The state of a call of `pack`. |
| `keep_row` | The visit that keeps a row of `world_rows`. |
