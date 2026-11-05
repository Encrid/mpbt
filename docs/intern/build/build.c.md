# src/build/build.c

`bridge_init`, `bridge_shutdown` and `bridge_reload` of the module `build` are in this file, beside its 2 systems.
The systems build the artifacts: `docs/extern/mpbt_artifact.h.md`, *The build*.

## The manifest

```text
mpbt:build@<version> abi=3 config=mpbt:BuildSettings settings=load_list pinned=false reloadable=false
```

`<version>` is the version of mpbt. The host gives the setting `load_list`, and each other key of the module: `docs/intern/host/host_world.c.md`.

## The components

`build_declare` declares the enums and the bitmasks first, each with `BRIDGE_TABLE` and `BRIDGE_STRIP`.
They are `mpbt:mpbt_command_name_t`, `mpbt:mpbt_options_t`, `mpbt:mpbt_value_kind_t`, `mpbt:mpbt_scope_t`, `mpbt:mpbt_step_list_t`, `mpbt:mpbt_step_actions_t` and `mpbt:mpbt_load_from_t`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:BuildSettings` | Read: the settings of `src/build/build.h`. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Command` | Read. | `BRIDGE_SINGLETON` | `BRIDGE_STRIP` |
| `mpbt:Variable` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Target` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Part` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Kind` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Step` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Artifact` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Load` | Read. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Built` | Written: attached to the entity of each artifact that the system `build` made. | `BRIDGE_TABLE` | `BRIDGE_STRIP` |
| `mpbt:Finding` | Written by `finding_write`: an entity for each fault. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.
`BRIDGE_STRIP` keeps the entities that a different module made. `BRIDGE_SWEEP` also removes an entity that held only a finding.

## The systems

Each term is `BRIDGE_READ` and `BRIDGE_OPTIONAL`, so each table matches, and the system reads the tables that hold its types.

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `build` | `build` | `mpbt:Command`, `mpbt:Variable`, `mpbt:Target`, `mpbt:Part`, `mpbt:Kind`, `mpbt:Step`, `mpbt:Artifact` | `mpbt:Built`, `mpbt:Finding` |
| `load_artifacts` | `load` | The terms of `build`, then `mpbt:Load` and `mpbt:BuildSettings` | `mpbt:Finding` |

## build

1. `build_read_world` reads the components.
2. `build_order` chooses the artifacts, and sorts them.
3. For each artifact, `steps_read_input` reads its row, and `steps_make` builds it in the place of the system `build`.
4. Then `build_attach_built` attaches its `mpbt:Built`.
5. A fault stops the loop, and `finding_write` writes it with the check `build`.
6. With the command `build` or `pack`, `say` then writes the path of each output, one on each line.

The place is in `docs/intern/shared/steps/steps.h.md`, *steps_place_t*. The messages are in `docs/extern/mpbt_artifact.h.md`, *Messages*.
In the command `test`, the module `test` refuses an artifact that is not linked.

## load_artifacts

`build_read_world` reads the components. Then `build_list_loads` builds the modules of `[[load]]`, and writes their list into the file of `load_list`.
A fault gives a finding with the check `load`.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares the types and adds the systems with `build_declare`: 0, or 1. |
| `bridge_reload` | Does what `bridge_init` does. The manifest states `reloadable=false`, so a host does not call it. |
| `bridge_shutdown` | 0: no memory of the module stays between two calls. |
| `bridge_build` | The system `build`: 0. A fault gives a finding, and not a status. |
| `bridge_load_artifacts` | The system `load_artifacts`: 0. A fault gives a finding. |
