# src/read/read.c

This file is the module `read`: its exports, and the system that writes the command, the config and, in `test`, the cases as components.
The phase is in `docs/extern/mpbt_command.h.md`, *The phases*.

## The manifest

```text
mpbt:read@<version> abi=3 config=mpbt:Arguments settings=<names> pinned=false reloadable=false
```

`<version>` is the version of mpbt. `<names>` is the name of each field of `mpbt:Arguments`, with a space between 2 names.
`mpbt:Arguments` holds the command line: `docs/intern/read/read.h.md`, *mpbt:Arguments*.
The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## The components

`bridge_init` gives `world_declare` of `src/shared/world/world.h` the name of each type below but the last, from the first row down. Each enum and each bitmask is declared before the structs, which name them.
Then `declare_arguments` declares `mpbt:Arguments` with the descriptor of `src/read/read.h`, because no header of `include` holds it.

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | Written, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Written, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_value_kind_t` | Written, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_scope_t` | Written, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_system_t` | Written, in the exceptions | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_step_list_t` | Written, in `mpbt:Step` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_step_actions_t` | Written, in `mpbt:Step` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_load_from_t` | Written, in `mpbt:Load` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_claim_keys_t` | Written, in the claims | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_signal_t` | Written, in `mpbt:ScriptStep` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_script_actions_t` | Written, in `mpbt:ScriptStep` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_side_t` | Written, in `mpbt:BranchException` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_needs_t` | Written, in `mpbt:Ci` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Project` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Variable` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Target` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Source` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Dependency` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Agree` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Kind` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Step` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Artifact` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Compose` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Part` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Package` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Load` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Tests` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:TestRule` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Case` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Run` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:FalseVariant` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Claims` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:HelperClaims` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:ScriptStep` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:TextCheck` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:LayoutCheck` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:StyleCheck` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:ProseCheck` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Retired` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Make` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:StyleException` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:BranchException` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Leaks` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:LeakPair` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:LeakKind` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:LeakException` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:FailCall` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Ci` | Written | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:File` | Written, in `check` and `test` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Arguments` | Read: the settings of the module | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |

The place of a type in this table is its slot: `docs/intern/read/read.h.md`, *read_type_t*.
`on_destroy` is `BRIDGE_ON_DESTROY_REMOVE` for each type: the headers of `docs/extern` state it.
`read` writes each singleton with an `attach` to the id 0. Only `mpbt:Arguments` is a settings component of Bridge. The other singletons come from the tables of the config.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `read` | `read` | `mpbt:Arguments`: `BRIDGE_READ`, `BRIDGE_OPTIONAL`. | Each struct of *The components* but `mpbt:Arguments`. |

No other module has a system in the phase `read`, so the system has no conflict.

## The steps

`bridge_read` does these steps.
After a step that writes a finding, the run stops, because the later steps need its result.

1. `read_get_arguments` reads the settings, and `read_command` writes `mpbt:Command`. In `cla`, the run ends here.
2. `read_config` reads the config.
3. `read_targets` decides `{home}` and the target of the run.
4. `read_variables` collects each variable. `read_check_parts` checks `[parts]`, and the cycles of their `uses`.
5. `read_paths` adds `{paths}`, from the names of the artifacts.
6. `read_project`, `read_write_variables` and `read_write_targets` write the project, the variables and the targets.
7. The sources, the kinds, the parts, the artifacts, the loads and the singletons of the tables follow.
8. Then come the checks, the leaks and the calls that fail. The cases need these calls.
9. In `test`, `read_tests` writes the rules and the cases. In `check` and `test`, `read_files` writes `mpbt:File`.
10. `toml_doc_free` and `read_free_variables` give the memory of the run back.

A function gives `false` after a finding, and also with no memory. With no finding, `bridge_read` then gives 1, and Bridge records the failure.

## The limits

`read` makes each of its entities in one phase, before the first barrier. Thus its config bounds one run:

- `spawns` holds an id for each entity. In `check` and `test`, that also counts the files.
- `changes` holds 24 bytes and the value of each `attach`.
- `persistent` holds each text, list and map that `read` writes, also the bytes of each file.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0 after the declarations of *The components* and the system `read`. Else the status of the call that Bridge refused. |
| `bridge_shutdown` | 0. No state of `read` stays between 2 calls. |
| `bridge_reload` | The result of `bridge_init`. Bridge does not call it, since `read` is not reloadable. |
| `bridge_read` | 0 when the steps end, with or without a finding. 1 if a step got no memory. |
| `declare_arguments` | Declares `mpbt:Arguments` as a singleton, after the types of `world_declare`. |
