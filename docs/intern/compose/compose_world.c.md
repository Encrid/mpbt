# src/compose/compose_world.c

This file holds the work of `compose` with Bridge that is its own. The rest is in `src/shared/world/world.h`.

## The steps

1. `compose_declare` gives `world_declare` each type of `docs/intern/compose/compose.c.md`, *The components*, then adds the system.
2. `compose_read_world` fills `compose_state_t`: `world_rows` gives the rows of each table, and the kept cells give the 2 singletons.
3. `compose_write_deliverable` takes a new entity from `spawn` for one deliverable.
4. `lists_get_size` measures the list of the names, `alloc` gives its room, and `lists_write` writes it.
5. Then `attach` gives the entity its `mpbt:Deliverable`: the part, or no bytes for the project, and the list.

The names are those of the list after `--leave`: `docs/extern/mpbt_compose.h.md`, *mpbt:Deliverable*.

## Functions

| Function | Result |
| --- | --- |
| `compose_declare` | 0, or 1 when Bridge refuses a declaration. |
| `compose_read_world` | The rows that one call reads. |
| `compose_write_deliverable` | Writes the entity of one deliverable. |
| `keep_row` | Puts one row that `world_rows` gives into the state. |
