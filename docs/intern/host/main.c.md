# src/host/main.c

This file is the entry of mpbt. It reads the command line, makes the world, runs the phases, and ends with the status: `docs/extern/mpbt_command.h.md`.

## The steps

1. `host_arguments` makes the settings of `read` from `argv`. A wrong command line stops mpbt with the status 2.
2. `os_signal_catch` catches the signals that stop the process, with its line of `docs/extern/mpbt_command.h.md`, *Messages*.
3. `host_config` reads the tables `[[load]]` of the config.
4. `host_modules` writes the files that BB-Native loads, if they are not there yet.
5. `host_world` makes the world, and loads the modules of mpbt.
6. `host_run` runs the phases of the command.
7. `bridge_destroy` frees the world, and `main` gives the status.

## Functions

| Function | Result |
| --- | --- |
| `main` | The exit status of mpbt: 0, 1 or 2. |
