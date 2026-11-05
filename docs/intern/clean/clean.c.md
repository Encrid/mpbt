# src/clean/clean.c

This file is the module `clean`, which the commands `clean` and `distclean` run: `docs/extern/mpbt_command.h.md`, *The commands*.
It holds the exports of the module and its system.

## The manifest

`mpbt:clean@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## The components

`bridge_init` declares the 8 types with `world_declare`, from the top row down. Thus an enum or a bitmask comes before the struct that holds it.
The descriptor of each type is that of its header in `include`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:mpbt_command_name_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_options_t` | Read, in `mpbt:Command` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Command` | Read | `BRIDGE_SINGLETON` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_value_kind_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:mpbt_scope_t` | Read, in `mpbt:Variable` | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Variable` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Source` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`, as the declarations of `docs/extern` state.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `clean` | `clean` | `mpbt:Command`, `mpbt:Variable` and `mpbt:Source`, each with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

A variable and a source are in different tables, and each term is `BRIDGE_OPTIONAL`. Thus `clean` walks both tables.
Its changes name `mpbt:Finding`.

## The steps

1. `bridge_clean` reads `name` of `mpbt:Command`: `MPBT_COMMAND_CLEAN` or `MPBT_COMMAND_DISTCLEAN`.
2. `clean_get_paths` gives the output folder and, for `clean`, the paths that stay.
3. With no folder at `{build}`, `say_format` writes that nothing is there to clean, and `bridge_clean` returns.
4. An output folder that holds the root stops `clean` with a finding, and nothing goes.
5. For `distclean`, `os_path_remove` removes the output folder and each entry in it.
6. For `clean`, `clean_remove` removes the entries that do not stay: `docs/intern/clean/clean_remove.c.md`.
7. After the removal, `say_format` writes the line that names the cleaned folder.

The lines and the texts of the faults are in `docs/extern/mpbt_command.h.md`, *Messages*. The lines name the output folder with the text of `{build}`.
A fault in step 2, 4, 5 or 6 stops the module before step 7. `finding_write` writes the text of the fault as a finding, with `clean` as its `check`.

`clean_get_paths` and `clean_remove` give no text when a call fails and has no message, for example `malloc`.
Then `bridge_clean` gives 1, and Bridge stops the world: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.
mpbt then ends with 1, after the record of Bridge: `docs/extern/mpbt_command.h.md`, *The commands*.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0, or the status of the first call that Bridge refused. |
| `bridge_shutdown` | 0. No resource of the module lives between two calls. |
| `bridge_reload` | The same work as `bridge_init`. Bridge never calls it, because the manifest states `reloadable=false`. |
| `bridge_clean` | 0, also after a finding, or 1 after a call that fails with no message. |
