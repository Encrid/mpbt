# src/pack/pack.c

The exports of `pack` are here: `bridge_init`, `bridge_shutdown`, `bridge_reload`, and the system `pack`.
For each deliverable, the system writes a zip, then proves its package: `docs/extern/mpbt_compose.h.md`, *The zip*.

## The manifest

```text
mpbt:pack@<version> abi=3 config=none pinned=false reloadable=false
```

`<version>` is the version of mpbt.

## The components

Before the components, `pack_declare` declares the types that their fields name, as `docs/intern/build/build.c.md`, *The components*, does.
These are `mpbt:mpbt_command_name_t`, `mpbt:mpbt_options_t`, `mpbt:mpbt_value_kind_t`, `mpbt:mpbt_scope_t`, `mpbt:mpbt_step_list_t` and `mpbt:mpbt_step_actions_t`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:Command` | Read. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Project` | Read. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Variable` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Target` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Deliverable` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Part` | Read: the name of the zips of a part. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Package` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Artifact` | Read: the archives of a deliverable. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Built` | Read: the archives of a deliverable. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Kind` | Read: for the proof. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Step` | Read: for the proof. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Finding` | Written: the faults, through `finding_write`. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `pack` | `pack` | A term of `BRIDGE_READ` and `BRIDGE_OPTIONAL` for each type that it reads | `mpbt:Finding` |

## pack

1. `pack_read_world` reads the components.
2. The deliverables come in the order of their parts, by name. The files of each one are those of its `mpbt:Deliverable`.
3. For each deliverable, `pack_scan_files` refuses a file that holds a folder of this machine.
4. Then `pack_write_zip` writes the zip, and `pack_prove` proves the package.
5. A fault ends the system: `finding_write` gives it the check `pack`.

The name of the zips of a deliverable is `name` of its part, or `[project] name` in a project with no parts.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | The status of `pack_declare`. |
| `bridge_reload` | Does what `bridge_init` does. |
| `bridge_shutdown` | 0. |
| `bridge_pack` | The system `pack`: 0. A fault gives a finding. |
| `pack_deliverable` | Scans, zips and proves one deliverable. |
