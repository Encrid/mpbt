# src/test/test.c

This file is the module `test` of mpbt: it declares its types, and runs the cases in the phase `test`.
The behavior is in `docs/extern/mpbt_case.h.md`, `docs/extern/mpbt_branches.h.md`, `docs/extern/mpbt_leaks.h.md` and `docs/extern/mpbt_fail.h.md`.

## The manifest

`mpbt:test@<version> abi=3 config=none pinned=false reloadable=false`, where `<version>` is the version of mpbt.
The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.
The module has no settings. The module `read` writes `mpbt:Tests` and `mpbt:Leaks` in the phase `read`, and `test` reads them as components.

## The components

`bridge_init` gives the names of this table to `world_declare` of `src/shared/world/world.h`, row after row. Thus the slot of a type is the number of its row.
An enum or a bitmask goes first, since a field of a later type names it. `world_declare` takes the descriptor of the C type of each name.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_claim_keys_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_signal_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_script_actions_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_value_kind_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_scope_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_step_list_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_step_actions_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_system_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_side_t` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Read: the options of the run. | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Tests` | Read: `[test]`. | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:TestRule` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Case` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Run` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:FalseVariant` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Claims` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:HelperClaims` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:ScriptStep` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Variable` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Target` | Read: for the build of the copies. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Artifact` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Built` | Read: the build of the phase `build`. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Kind` | Read: for the build of the copies. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Step` | Read: for the build of the copies. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Part` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:FailCall` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Leaks` | Read: `[leaks]`. | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:LeakPair` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:LeakKind` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:LeakException` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:BranchException` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written by `finding_write` and `finding_format`: one entity for each fault. | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`, as its row of `docs/extern` gives it, and `BRIDGE_SWEEP`, as each module of mpbt states it.
Thus an entity that holds nothing more after the last unload goes, for example the entity of a finding.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `test` | `test` | Each type of *The components* from `mpbt:Command` to `mpbt:BranchException`, with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. | `mpbt:Finding` |

Each term is optional, so each table matches, and `world_rows` reads the rows of each type from the spans.

## The steps of the system

1. `test_read_world` reads the singletons and the rows of each type into a `test_world_t`.
2. With `--leaks`, `test_run_leaks` runs. With `--branches`, `test_run_branches` runs.
3. Else `test_run_plain` runs.
4. The system gives 1 if `failed` of the run is set, else 0.

Each fault becomes a finding with the check `test`, through `src/shared/finding/finding.h`. Only the thread of the system writes it.
With 1, Bridge writes the record of the failure at the level of an error, and the host ends with 1: `docs/intern/host/host_sink.c.md`, *The lines*.
The memory of the run goes back before the system returns. Thus `bridge_shutdown` has nothing to free.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0 after `declare_all`, or 1. |
| `bridge_reload` | The result of `bridge_init`. The module is not reloadable, but Bridge needs the export. |
| `bridge_shutdown` | 0. The module holds nothing between 2 calls. |
| `bridge_test` | The system: 0, or 1. |
| `declare_all` | Declares the types of *The components* with `world_declare`, then adds the system `test` with `add_system`. |
