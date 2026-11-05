# src/style/style.c

This file is the module `style`, which runs on Bridge: its exports, and the system that runs the check `style` of `docs/extern/mpbt_check.h.md`, *The checks*.

## The manifest

`mpbt:style@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.
The check has no settings component. `read` writes its limits as `mpbt:StyleCheck`, and each exception as an entity of its own.

## The components

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:StyleException` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Project` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:StyleCheck` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

`world_declare` of `src/shared/world/world.h` declares the 5 types in the order of the table. Thus their slots are 0 to 4.
Bridge applies the policy of the module that unloads last. Thus each type has the sweep that `read` states, and the order of the unloads changes nothing.

## The systems

| Name | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `style` | `check` | The first 4 types of *The components*, each with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. | `mpbt:Finding` |

The files and the exceptions are on different entities, so each term is optional. Thus the query matches each table, and `world_rows` takes only the tables of a type.
`CHECKS_NAMES` of `src/shared/checks/checks.h` gives the name `style` of the system, and the `check` of each finding. The host orders the 12 systems by these names.

## The steps of the system

1. `bridge_native_get_single` gives the notice of `mpbt:Project` and the limits of `mpbt:StyleCheck`.
2. `style_read_exceptions` reads each `mpbt:StyleException`: `src/style/style_exceptions.c`.
3. `style_read_names` reads the names that the headers declare: `src/style/style_names.c`.
4. `world_rows` gives each `mpbt:File` to `style_check_file`: `src/style/style_file.c`.
5. `style_end_exceptions` writes a finding for each exception that excused no fault.
6. Each list of the run gives its memory back.

`read` writes the 2 singletons before the phase `check`. Without a value of one of them, the system checks nothing and gives 1.
The system gives 1 if `failed` is set, else 0. Bridge records each status that is not 0, and the host then ends with 1.

## Functions

| Function | Result |
| --- | --- |
| `init` | Declares the 5 types, then adds the system `style`. |
| `shutdown` | 0. The module holds nothing between 2 calls. |
| `reload` | The result of `init`. Bridge calls it only for a module with `reloadable=true`. |
| `style` | The system: 0, or 1 when a value or the memory is missing. |

The native names of the exports are `bridge_init`, `bridge_shutdown`, `bridge_reload` and `bridge_style`.
