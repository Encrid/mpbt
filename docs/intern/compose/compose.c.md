# src/compose/compose.c

This file is the module `compose` for BB-Native: `bridge_init`, `bridge_shutdown`, `bridge_reload` and the system `compose`.
That system writes `package.txt`, then copies each deliverable into `{dist}`: `docs/extern/mpbt_compose.h.md`, *The deliverable*.

## The manifest

```text
mpbt:compose@<version> abi=3 config=none pinned=false reloadable=false
```

`<version>` is the version of mpbt.

## The components

First come the 3 enums and the bitmask that the fields name: `mpbt:mpbt_command_name_t`, `mpbt:mpbt_options_t`, `mpbt:mpbt_value_kind_t` and `mpbt:mpbt_scope_t`.
Each one has the storage and the policy of `docs/intern/build/build.c.md`, *The components*.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:Command` | Read. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Project` | Read. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Variable` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Artifact` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Built` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Compose` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Part` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Deliverable` | Written: an entity for each deliverable, for `pack`. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written: one entity for each fault, by `finding_write`. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `compose` | `compose` | Each type that the system reads, with `BRIDGE_READ` and `BRIDGE_OPTIONAL` | `mpbt:Deliverable`, `mpbt:Finding` |

## compose

1. `compose_read_world` reads the components.
2. `compose_write_package` writes `{out}/package.txt`.
3. `compose_get_deliverables` gives the deliverables of the run.
4. For each deliverable, `compose_get_files` gives its files, and `copy_file` copies each one into `{dist}`.
5. `say` writes the name of each file of the deliverable, on its own line.
6. `compose_write_deliverable` gives the deliverable its entity of `mpbt:Deliverable`.
7. A fault stops the system, and `finding_write` writes it with the check `compose`.

A file of the deliverable that does not read, or a copy in `{dist}` that cannot be written, stops the copies.
Its fault is in `docs/extern/mpbt_command.h.md`, *Messages*.
All the deliverables of a run go into the one folder `{dist}`. The zip of each one holds only the files of its `mpbt:Deliverable`.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Calls `compose_declare`: 0, or 1. |
| `bridge_reload` | Does what `bridge_init` does. |
| `bridge_shutdown` | 0, since the module holds nothing. |
| `bridge_compose` | The system `compose`: 0. A fault gives a finding. |
| `put_deliverable` | Copies the files of one deliverable, writes their names, and writes its entity. |
