# src/host/host_config.c

This file reads the tables `[[load]]` of the config, before the world exists: `docs/extern/mpbt_load.h.md`.

## The steps

1. `toml_doc_read` reads each file of the config, and `toml_doc_merge` merges them: `docs/extern/mpbt_project.h.md`, *The files of the config*.
2. `toml_doc_find` gives the list `load`. Each of its tables gives `artifact` or `file`, then `phases`, `config` and its other keys.
3. A table with both or neither of `artifact` and `file` stops mpbt, with its message of `docs/extern/mpbt_load.h.md`, *Messages*.
4. Each phase of mpbt in `phases` must come after `load`.

The host reads no other table. The module `read` reads the whole config, and writes its components.

## Functions

| Function | Result |
| --- | --- |
| `host_config` | The tables `[[load]]`, or 1 after a message. |
| `take_load` | Takes one table `[[load]]`. |
