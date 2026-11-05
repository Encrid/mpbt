# src/build/build.h

This private header gives the types of `build`, and the functions that its files share.

## mpbt:BuildSettings

`build_settings_t` holds the settings of the module: the component that `config=mpbt:BuildSettings` of its manifest names.
It is a singleton. Bridge fills it after `init`, from the setting that the host gives.

| Field | C type | Value |
| --- | --- | --- |
| `load_list` | `bridge_text_t` | The path of the list of the modules of the project: `<build>/load.txt`. |

`BUILD_SETTINGS_FIELDS` gives its fields, and `build_settings_t_desc` gives its descriptor.

## build_state_t

`build_state_t` holds what a system of the module reads in one call. A row does not outlive a barrier, so the state lives only during that call.

| Field | Value |
| --- | --- |
| `command` | The value of `mpbt:Command`. |
| `settings` | The value of `mpbt:BuildSettings`. |
| `steps` | The `steps_t` of `src/shared/steps/steps.h`: the rows that the build of an artifact reads, and the fault. |
| `artifacts` | The rows of `mpbt:Artifact`, each with the id of its entity. |
| `parts` | The rows of `mpbt:Part`. |
| `loads` | The rows of `mpbt:Load`. |

## Functions

| Function | File |
| --- | --- |
| `build_declare` | `build_world.c` |
| `build_read_world` | `build_world.c` |
| `build_attach_built` | `build_world.c` |
| `build_order` | `build_order.c` |
| `build_list_loads` | `build_load.c` |
