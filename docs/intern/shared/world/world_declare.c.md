# src/shared/world/world_declare.c

This file declares the types that a module names, in the order of the names. Each type then has the slot of its place in the list, from 0.

## The table of the types

The file holds a `world_type_t` for each type of the headers of `include`. Each one is a row of a table of declarations, for example `docs/extern/mpbt_file.h.md`, *The declarations*.
The kind of a type, its storage and its `on_destroy` come from its row there. Its descriptor, its size and its alignment come from its header.
A type that is not in `include`, for example the settings of a module, is not in the table. Its module declares it alone.

## The steps

1. `find_type` finds the row of each name of the list, with `strcmp`.
2. `bridge_native_put` puts the name and the descriptor into the scratch arena.
3. `declare` of Bridge takes a `bridge_declaration_t` with the values of the row, and the `on_unload` that the module gives.

A name with no row stops the declarations, and `world_declare` gives 1. Then `init` gives 1, and the load of the module fails.
The module names an enum or a bitmask before the struct that holds it, as Bridge needs.

## Functions

| Function | Result |
| --- | --- |
| `world_declare` | 0 when each name has a row, or 1. |
| `find_type` | The row of a name, or none. |
