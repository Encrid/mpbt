# src/host/host_world.c

This file makes the world of Bridge, and loads the modules of mpbt.

## The deployment

| Field of `bridge_config_t` | Value |
| --- | --- |
| `abi` | `BRIDGE_HOST_ABI`. |
| `backends` | BB-Native, from `{toolchain}/modules`. BB-Wasm too, if a table `[[load]]` names a module of wasm. |
| `phases` | The 14 phases of `docs/extern/mpbt_command.h.md`, *The phases*. |
| `order` | The systems of the 12 checks, in the order of the list of `src/shared/checks`. In the phase `load`, `check_fetched` of `fetch` comes before `load_artifacts` of `build`. Each of these systems writes `mpbt:Finding`, so Bridge needs their order. |
| `threads` | 1. The systems of a phase run one after another, and a module that needs threads starts its own, as `test` does. |
| `budget` | 1048576 entities, and 64 modules. The other bounds follow from the types of the headers of mpbt. |

`bridge_create` makes the world, with `host_sink` as its sink.

## The modules of mpbt

For each module of mpbt, the library of the manifest of Bridge-Host reads the manifest of its file. Then `bridge_load` loads it with BB-Native.
The settings of `read` come from the command line. The settings of `build` give the path `<build>/load.txt` of the list of `load`.

## The keys of the modules of mpbt

The manifest of a module of mpbt states only the words that only a manifest may state: its identity, `abi`, `config`, `settings`, `pinned` and `reloadable`.
The host gives each other key of `bridge_module_config_t`, as a deployment does:

| Key | Value |
| --- | --- |
| `hot_reload` | `false`. |
| `on_error` | `"fail"`, and `max_system_failures` 1. |
| `work_limit`, `memory_limit`, `element_limit`, `init_timeout`, `reload_timeout`, `shutdown_timeout` | `"none"`, because BB-Native has no limit. |
| `log_level` | 7, so each record comes to the sink. |
| `scratch`, `log_ring`, `spans` | 1048576, 65536 and 65536 bytes. |
| `spawns`, `persistent`, `changes` | 1048576, 268435456 bytes, and 67108864 bytes. |
| `losses` | `"none"`. |
| `read`, `write` | No name: the types of mpbt are in the namespace of each module of mpbt. |

A finding takes 1 id of `spawns` and 56 bytes of `changes`. Thus a module writes at most 1048576 findings between 2 barriers.

A module of a project takes its keys from its manifest and its table `[[load]]`: `docs/extern/mpbt_load.h.md`.

## Functions

| Function | Result |
| --- | --- |
| `host_world` | The world with the modules of mpbt, or 1. |
| `fill_config` | Fills `bridge_config_t`. |
| `load_module` | Loads one module of mpbt. |
