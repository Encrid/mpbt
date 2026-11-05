# src/host/host_world.c

This file makes the world of Bridge, and loads the modules of mpbt.

## The deployment

| Field of `bridge_config_t` | Value |
| --- | --- |
| `abi` | `BRIDGE_HOST_ABI`. |
| `backends` | BB-Native, from `{toolchain}/modules`. BB-Wasm too, if a table `[[load]]` names a module of wasm. |
| `phases` | The 14 phases of `docs/extern/mpbt_command.h.md`, *The phases*. |
| `order` | The systems of the 12 checks, in the order of `docs/extern/mpbt_check.h.md`, *The checks*. Each check writes `mpbt:Finding`, so Bridge needs their order. |
| `threads` | 1. The systems of a phase run one after another, and a module that needs threads starts its own, as `test` does. |
| `budget` | 1048576 entities, and 64 modules. The other bounds follow from the types of the headers of mpbt. |

`bridge_create` makes the world, with `host_sink` as its sink.

## The modules of mpbt

For each module of mpbt, the library of the manifest of Bridge-Host reads the manifest of its file. Then `bridge_load` loads it with BB-Native.
The settings of `read` come from the command line. The settings of `build` give the path `<build>/load.txt` of the list of `load`.

## Functions

| Function | Result |
| --- | --- |
| `host_world` | The world with the modules of mpbt, or 1. |
| `fill_config` | Fills `bridge_config_t`. |
| `load_module` | Loads one module of mpbt. |
