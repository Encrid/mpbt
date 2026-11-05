# src/shared/world/world.h

This header declares the seam to Bridge that each native module of mpbt needs. It declares the types of mpbt, and walks the rows of a type.
A module keeps in its own files only the work with Bridge that no other module does.

## world_walk_t

One walk of the rows of a type, for `world_rows`.

| Field | Value |
| --- | --- |
| `query` | The slot of the system whose query gives the spans. |
| `slot` | The slot of the type, as `world_declare` gave it. |
| `visit` | The function of the caller for each row. It gets `data`, the row and the id of its entity, and gives `false` to stop the walk. |
| `data` | The state of the caller. |

## world_type_t

One type of mpbt, for the table of `src/shared/world/world_declare.c`.

| Field | Value |
| --- | --- |
| `name` | The name of the type in Bridge, for example `mpbt:File`. |
| `kind` | `BRIDGE_STRUCT`, `BRIDGE_ENUM` or `BRIDGE_BITMASK`. |
| `size`, `align` | `sizeof` and `alignof` of its C type. |
| `desc`, `desc_len` | The descriptor of its header, and the count of its bytes with no zero byte. |
| `storage`, `on_destroy` | The storage layout and the `on_destroy` of its declaration. |

`WORLD_TYPE` makes one `world_type_t` from the name, the C type, the kind, the storage layout and the `on_destroy`.
It takes the size, the alignment and the descriptor from the C type, so a row of the table never repeats them.

## Functions

| Function | Parameters | File |
| --- | --- | --- |
| `world_declare` | `api`, the names of the types, their count, and the `on_unload` that they all get. | `world_declare.c` |
| `world_rows` | `api` and a `world_walk_t`. | `world_rows.c` |
