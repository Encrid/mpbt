# src/fetch/fetch.c

This file gives the exports of `fetch`, a module whose systems get zig and the sources, and check that the sources are there.
The behavior is in `docs/extern/mpbt_source.h.md`.

## The manifest

```text
mpbt:fetch@<version> abi=3 config=none pinned=false reloadable=false
```

`<version>` is the version of mpbt. The module has no settings, and the host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## The components

`bridge_init` gives the names of these 8 types to `world_declare` of `src/shared/world/world.h`, in the order of the rows, with the descriptors of `include`.

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_value_kind_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_scope_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Variable` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Source` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

For `on_destroy`, the 8 types state `BRIDGE_ON_DESTROY_REMOVE`, as their headers do.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `fetch` | `fetch` | `mpbt:Variable` and `mpbt:Source`: `BRIDGE_READ`, `BRIDGE_OPTIONAL`. | `mpbt:Finding` |
| `check_fetched` | `load` | `mpbt:Command`, `mpbt:Variable` and `mpbt:Source`: `BRIDGE_READ`, `BRIDGE_OPTIONAL`. | `mpbt:Finding` |

A variable and a source are on different entities. Each term is optional, so the query of each system matches the tables of both.
`check_fetched` writes `mpbt:Finding` in the phase `load`, as `load_artifacts` of `build` does. Thus the host runs `check_fetched` first: `docs/intern/host/host_world.c.md`, *The deployment*.

## The steps

`bridge_fetch` runs only in the command `fetch`:

1. `fetch_get_world` takes the variables and the sources.
2. `fetch_zig` gets zig if it is not there, and writes the path of zig.
3. `fetch_sources` gets each source that its `fetched.txt` does not state.

`bridge_check_fetched` acts only in `build`, `pack` and `test`, which download nothing:

1. `fetch_get_world` takes the variables and the sources.
2. `fetch_check_fetched` writes a finding for each source that its `fetched.txt` does not state.

A finding of a step stops the system at that step. Each system then calls `fetch_free_world`.
If the memory runs out, the function gives `false`, and the system gives 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | The declarations of *The components* and the 2 systems: 0, or the status that a refused call gave. |
| `bridge_shutdown` | 0, since `fetch` holds no resource after a call. |
| `bridge_reload` | The result of `bridge_init`. Bridge does not call it, since `fetch` is not reloadable. |
| `bridge_fetch` | 0 when zig and the sources are done or a finding stopped them. 1 with no memory. |
| `bridge_check_fetched` | 0 when each source was checked, with or without findings. 1 with no memory. |
