# src/take/take.c

The module `take` starts here: its exports, and its system, which copies the files that each dependency lists.
The behavior is in `docs/extern/mpbt_dependency.h.md`.

## The manifest

```text
mpbt:take@<version> abi=3 config=none pinned=false reloadable=false
```

`<version>` is the version of mpbt. The module has no settings. The host gives each other key, as `docs/intern/host/host_world.c.md` tells.

## The components

`world_declare` of `src/shared/world/world.h` declares the 6 types of this table for `bridge_init`, from the top row down, with the descriptors of `include`.

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:mpbt_value_kind_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_scope_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Variable` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Dependency` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Agree` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each of the 6 types gets `BRIDGE_ON_DESTROY_REMOVE` for `on_destroy`.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `take` | `take` | `mpbt:Variable`, `mpbt:Dependency` and `mpbt:Agree`: `BRIDGE_READ`, `BRIDGE_OPTIONAL`. | `mpbt:Finding` |

The 3 types are on different entities. With 3 terms of `BRIDGE_OPTIONAL`, each table matches, and the walk reads the type that each table carries.

## The steps

`bridge_take` does these steps, in the order of `docs/extern/mpbt_dependency.h.md`, *[[dependency]]*:

1. `take_get_world` takes `{root}`, the dependencies and the rules.
2. For each dependency, `take_make` runs `make` if it has items.
3. `os_path_entry` tells whether the list is there. A list that is not there skips a dependency with `optional`, and `say` writes its line. Else the run stops.
4. `take_read_list` reads each list that is there.
5. `take_agree` checks each rule. A rule whose values differ stops the run.
6. `take_check_copies` checks each file of each list, and keeps the copies to write.
7. `take_write_copies` writes the copies. Then `say` writes a line for each dependency that `take` took.
8. `take_free_world` gives the memory of the run back.

When a step writes a finding, no later step runs. Thus a refusal changes no file.
The lines and the messages are in `docs/extern/mpbt_dependency.h.md`, *Messages*.
No memory makes a function give `false`, and then `bridge_take` gives 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares each type of *The components*, then adds `take`. It gives 0, or the status of the refused call. |
| `bridge_shutdown` | 0. `take` frees each resource before its system returns. |
| `bridge_reload` | The result of `bridge_init`. Bridge does not call it, since `take` is not reloadable. |
| `bridge_take` | 0 when the last step ran, or when a finding stopped the steps. 1 with no memory. |
