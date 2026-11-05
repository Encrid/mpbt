# src/host/host.h

This private header declares `host_t`, the state of one run of mpbt, and the functions of the files of `src/host`.

## host_t

| Field | Value |
| --- | --- |
| `command` | The command, and its phases in order: `docs/extern/mpbt_command.h.md`, *The commands*. |
| `settings` | The settings of the module `read`, which `host_arguments.c` makes from the command line. |
| `build` | The output folder `{build}`: `docs/extern/mpbt_project.h.md`, *Variables*. |
| `toolchain` | The folder `toolchain` beside the program. |
| `loads` | The tables `[[load]]` of the config, which `host_config.c` reads. |
| `world` | The world of Bridge, from `bridge_create`. |
| `status` | The exit status: 0, 1 or 2. |

## Functions

| Function | File |
| --- | --- |
| `host_arguments` | `host_arguments.c` |
| `host_config` | `host_config.c` |
| `host_modules` | `host_modules.c` |
| `host_world` | `host_world.c` |
| `host_load` | `host_load.c` |
| `host_run` | `host_run.c` |
| `host_sink` | `host_sink.c` |
