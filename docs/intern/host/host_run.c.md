# src/host/host_run.c

This file runs the phases of the command, in the order of `docs/extern/mpbt_command.h.md`, *The commands*.

## The steps

1. For each phase of the list but `report`, `bridge_run_phase` runs the systems of the phase. Then the host runs `report`.
2. `report` gives `BRIDGE_END` if it wrote a finding. Then `bridge_run_phase` gives 2, and the host stops with the status 1.
3. After `load`, `host_load` loads the modules of the project.
4. A result of 1 tells that Bridge refused the call. The sink wrote the record that tells why, and the host stops with 1.
5. Between two phases, `os_signal_is_caught` tells whether a signal came. Then the host stops with 1.

## Functions

| Function | Result |
| --- | --- |
| `host_run` | The exit status: 0 or 1. |
| `run_phase` | Runs one phase, then `report`. |
