# src/host/host_load.c

This file loads the modules of a project, after the phase `load`: `docs/extern/mpbt_load.h.md`, *The modules of a project*.

## The steps

1. `os_folder_open` and `os_folder_read_file` read `<build>/load.txt`: one path on each line, in the order of `[[load]]`.
2. For each path, the library of the manifest reads the manifest. Its form tells the backend: a native library for BB-Native, or a module of wasm for BB-Wasm.
3. The keys of its table `[[load]]` go to the library as typed values, over the defaults of the manifest. The library gives the `bridge_module_config_t`.
4. A module that joins `read`, `fetch`, `clean`, `cla` or `runner` stops mpbt.
5. `bridge_load` loads the module.

The messages are in `docs/extern/mpbt_load.h.md`, *Messages*.

## Functions

| Function | Result |
| --- | --- |
| `host_load` | 0 if each module of `[[load]]` loaded, or 1. |
| `load_path` | Loads the module of one path. |
