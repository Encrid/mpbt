# src/runner/runner.c

This file is the module `runner`, which writes the commands for a runner of GitHub: `docs/extern/mpbt_ci.h.md`, *runner*.

## The manifest

`mpbt:runner@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.
`runner` has no settings of Bridge. It reads `mpbt:Ci` as a component, which `read` writes from `[ci]`: `docs/extern/mpbt_ci.h.md`, *The grants*.

## The components

`world_declare` declares these types for `bridge_init`, with the descriptors of `include/mpbt_ci.h`, `include/mpbt_project.h` and `include/mpbt_finding.h`.
The bitmask and the 2 enums come before the structs that name them.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:mpbt_needs_t` | Read, in `mpbt:Ci` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Ci` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_value_kind_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_scope_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Variable` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each of the 6 types has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `runner` | `runner` | `mpbt:Variable`, with `BRIDGE_READ` and `BRIDGE_AND`. `mpbt:Ci`, with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

`runner` attaches `mpbt:Finding`, so its changes name that type.

## The steps

1. `runner_get_machine` gives the system and the processor of the target of the run.
2. `bridge_native_get_single` gives `mpbt:Ci`. With no value, or with no bit in `needs`, `runner` writes nothing.
3. `runner_write_commands` writes the commands of the needs, for that machine.

A target with no machine stops `runner` before step 2. `finding_write` then writes a finding whose `check` is `runner`.
Its text is the message of `docs/extern/mpbt_target.h.md`, *Messages*, for a target that no machine runs.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0 when Bridge took each type and the system, or the status of a refused call. |
| `bridge_shutdown` | 0. `runner` holds no resource after a call returns. |
| `bridge_reload` | Repeats the work of `bridge_init`. With `reloadable=false` in the manifest, Bridge does not call it. |
| `bridge_runner` | 0, after the commands or after a finding. |
