# src/cla/cla.c

This file is the module `cla`, which acts on the agreement for each pull request: `docs/extern/mpbt_command.h.md`, *The agreement*.

## The manifest

`mpbt:cla@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## The components

`bridge_init` takes each descriptor from `include/mpbt_command.h` or `include/mpbt_finding.h`. `world_declare` declares the enum and the bitmask first.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

The 4 types have `BRIDGE_ON_DESTROY_REMOVE`.
In the command `cla`, the phase `read` writes only `mpbt:Command`: `docs/extern/mpbt_command.h.md`, *The phases*.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `cla` | `cla` | `mpbt:Command`, with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

The changes of `cla` name `mpbt:Finding`.

## The steps

1. `bridge_cla` reads `options` and `decide` of `mpbt:Command`.
2. With `MPBT_OPTION_DECIDE`, `cla_write_decision` writes the decision of the values of `decide`.
3. Else `cla_settle` decides about the pull request of the event of GitHub, and acts on it.
4. A fault of `cla_settle` becomes one finding of `finding_write`, whose `check` is `cla`: `docs/intern/cla/cla.h.md`, *The faults*.
5. A fault with no text makes `bridge_cla` give 1 in place of a finding.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0 on success. A call that Bridge refuses gives its status. |
| `bridge_shutdown` | 0. Each step of `cla` frees its memory before it returns. |
| `bridge_reload` | The declarations and the system of `bridge_init`, again. Bridge does not call it for a module of `reloadable=false`. |
| `bridge_cla` | 0 after the decision or a finding. 1 after a fault with no text. |
