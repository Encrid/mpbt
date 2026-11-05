# src/shared/finding/finding.h

This header declares the writer of `mpbt:Finding`, which each native module of mpbt calls for each fault: `docs/extern/mpbt_finding.h.md`, *The report*.

## finding_t

The place of a finding. A caller fills it one time, and changes its line and its column for each fault.

| Field | Value |
| --- | --- |
| `slot` | The slot of `mpbt:Finding` in the module. |
| `check` | The name of the check or of the phase that found the fault, with a zero byte after it. A check takes its name from `CHECKS_NAMES` of `src/shared/checks/checks.h`. |
| `path`, `path_len` | The bytes of the path of the file of the fault, or no bytes. |
| `line`, `column` | The place of the fault, each from 1, or 0 when it has none. |

## Functions

| Function | Parameters | File |
| --- | --- | --- |
| `finding_write` | `api`, the `finding_t`, the bytes of the text, and their count. | `finding.c` |
| `finding_format` | `api`, the `finding_t`, a format of `printf`, and its values. | `finding.c` |
| `finding_vformat` | `api`, the `finding_t`, a format of `printf`, and a `va_list` of its values. | `finding.c` |

Each one gives `true` when Bridge holds the new finding: `src/shared/finding/finding.c`.
