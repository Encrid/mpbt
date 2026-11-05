# src/join/join.c

Here are the 4 exports of `join`: `bridge_init`, `bridge_shutdown`, `bridge_reload`, and the system `join`.
For a part, that system makes one zip from the zip of each target: `docs/extern/mpbt_compose.h.md`, *The release*.

## The manifest

```text
mpbt:join@<version> abi=3 config=none pinned=false reloadable=false
```

`<version>` is the version of mpbt.

## The components

The types that the fields name come first: `mpbt:mpbt_command_name_t`, `mpbt:mpbt_options_t`, `mpbt:mpbt_value_kind_t` and `mpbt:mpbt_scope_t`.
Their storage and their policy are those of `docs/intern/build/build.c.md`, *The components*.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:Command` | Read. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Variable` | Read: `{build}`. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Target` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Part` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Finding` | Written: `finding_write` gives each fault an entity. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `join` | `join` | `BRIDGE_READ` and `BRIDGE_OPTIONAL`: `mpbt:Command`, `mpbt:Variable`, `mpbt:Target`, `mpbt:Part` | `mpbt:Finding` |

## join

1. `join_read_world` reads the components.
2. With no `--part`, the system joins nothing, and writes nothing.
3. For each part that `--part` names, `join_write_zip` writes its zip. The parts keep the order of the command line.
4. After a fault, the system stops, and `finding_write` writes the fault under the check `join`.

The workflow `release` reads the output of `join`. Thus each line that `join` writes is the path of a zip that it made.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0 if `join_declare` succeeds, else 1. |
| `bridge_reload` | Does what `bridge_init` does. |
| `bridge_shutdown` | 0: the module frees nothing. |
| `bridge_join` | The system `join`: 0. A fault gives a finding. |
