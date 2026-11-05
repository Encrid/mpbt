# include/mpbt_finding.h

`include/mpbt_finding.h` gives `mpbt:Finding`: a fault that a phase finds, for example a fault of a check.

## The report

Each module that finds a fault writes an entity with `mpbt:Finding`. A module of a project can write one too.
In the phase `report`, mpbt writes each finding on a line.
The order is the order of the phases, then of the paths, of the lines and of the columns:

```text
<check>: <path>:<line>:<column>: <text>
```

A part that holds no bytes, or 0, is not written, with its colon.
Then `report` writes `faults: <count>`, and mpbt ends with 1. With no finding, mpbt ends with 0.
Each other line of the output is a line of the log of a module.

## mpbt:Finding

`mpbt_finding_t` takes 32 bytes. Its alignment is 4.

| Field | C type | Offset | Value |
| --- | --- | --- | --- |
| `check` | `bridge_text_t` | 0 | The name of the phase or of the check that found the fault, for example `layout`. |
| `path` | `bridge_text_t` | 8 | The file of the fault, from the root, or no bytes. |
| `text` | `bridge_text_t` | 16 | The fault, as the documents of mpbt quote it. |
| `line` | `uint32_t` | 24 | The line of the fault, from 1, or 0. |
| `column` | `uint32_t` | 28 | The column of the fault, from 1, or 0. |

## The C types

| Type of Bridge | C type | Descriptor | Macro of the text |
| --- | --- | --- | --- |
| `mpbt:Finding` | `mpbt_finding_t` | `mpbt_finding_t_desc` | `MPBT_FINDING_FIELDS` |

```text
{ bridge_text_t check; bridge_text_t path; bridge_text_t text; uint32_t line; uint32_t column; }
```

## The declarations

| Type of Bridge | Kind | Storage layout | `on_destroy` |
| --- | --- | --- | --- |
| `mpbt:Finding` | `BRIDGE_STRUCT` | `BRIDGE_TABLE` | `BRIDGE_ON_DESTROY_REMOVE` |

## The grants

| Type | Written in the phase | Read by |
| --- | --- | --- |
| `mpbt:Finding` | Each phase | `report`. Each other module with a grant. |

A module needs `mpbt:Finding` in `write` to write a finding.

## Messages

| Message | When |
| --- | --- |
| `faults: <count>` | The run found faults. |
