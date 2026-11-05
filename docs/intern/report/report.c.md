# src/report/report.c

This file is the module `report`. Its system writes the findings after each phase, as `docs/extern/mpbt_finding.h.md`, *The report*, tells.

## The manifest

`mpbt:report@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The host gives each other key: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## The components

`bridge_init` declares one type with `world_declare`, and the descriptor `mpbt_finding_t_desc` of `include/mpbt_finding.h`.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:Finding` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

The type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `report` | `report` | `mpbt:Finding`, with `BRIDGE_READ` and `BRIDGE_AND`. |
| `note_check` | `check` | None. |

`note_check` sets a flag of the module when the phase `check` runs, so `report` knows that the checks ran.
It touches no component, so it needs no place in the order of the 12 checks.

## The steps

1. `report_get_rows` gives the count of the findings, and a `report_row_t` for each one.
2. `report_sort` sorts the rows by check, path, line and column.
3. `report_write` writes the lines of the findings and the lines after them.
4. With no finding, `report` gives 0, and the host runs the next phase.
5. Else `report` gives `BRIDGE_END`. Then the host stops with the status 1: `docs/intern/host/host_run.c.md`.

With no memory for the rows, `report` gives 1, and Bridge stops the world: `docs/intern/host/host_world.c.md`, *The keys of the modules of mpbt*.

## One time for each finding

The host runs `report` after each phase. A finding of a phase is visible from the next phase on, thus `report` sees it after that phase.
The host stops after the first `report` that gives `BRIDGE_END`. Thus no later run of `report` sees the finding again, and the line comes one time.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0 after the declaration and the 2 systems, or the status of a refused call. |
| `bridge_shutdown` | 0. The module frees its rows before each system returns. |
| `bridge_reload` | Does what `bridge_init` does. The manifest states `reloadable=false`, so no reload calls it. |
| `bridge_report` | 0 with no finding, `BRIDGE_END` after the lines, or 1 with no memory for the rows. |
| `bridge_note_check` | 0, after it sets the flag. |
