# src/build/build_world.c

This file holds the work of `build` with Bridge that no other module does. `src/shared/world/world.h` gives the rest.

## The declarations

`build_declare` gives `world_declare` the names of `docs/intern/build/build.c.md`, *The components*, in the order of that table, with their `on_unload`.
`mpbt:BuildSettings` is not in `include`, so `build_declare` declares it alone, with the descriptor of `src/build/build.h`.
Then `add_system` adds the 2 systems of `docs/intern/build/build.c.md`, *The systems*, with their terms and their changes.

## The reads

`build_read_world` calls `world_rows` for each type of a table, and its visit keeps each row in `build_state_t`.
`mpbt:Command` and `mpbt:BuildSettings` are singletons, so their values come from their kept cells, through the readers of BB-Native.
For `steps_make`, `steps` gets the rows of the 4 types of a build: variables, targets, kinds and steps.

## mpbt:Built

`build_attach_built` puts the output and the list of files into the persistent arena, with `alloc`, `lists_get_size` and `lists_write`.
Then `attach` gives `mpbt:Built` to the entity of the artifact.

## Functions

| Function | Result |
| --- | --- |
| `build_declare` | 0 when Bridge took each type and each system, or 1. |
| `build_read_world` | The state of one call of a system. |
| `build_attach_built` | Attaches `mpbt:Built` to the entity of one artifact. |
| `keep_row` | The visit of `world_rows`: keeps one row in the state. |
