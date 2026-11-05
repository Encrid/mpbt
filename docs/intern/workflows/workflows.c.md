# src/workflows/workflows.c

Here are the exports of the module `workflows`. Its system checks that the matrix of each workflow builds each target of mpbt.
The messages are in `docs/extern/mpbt_check.h.md`, *workflows*.

## The manifest

`mpbt:workflows@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

`include/mpbt_file.h`, `include/mpbt_target.h` and `include/mpbt_finding.h` give the descriptors that `world_declare` declares.

| Type | Written or read | Storage | on_unload |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Target` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

Each type has `BRIDGE_ON_DESTROY_REMOVE`.

## The systems

| System | Phase | Terms |
| --- | --- | --- |
| `workflows` | `check` | `mpbt:File` and `mpbt:Target`, each with `BRIDGE_READ` and `BRIDGE_OPTIONAL`. |

No entity carries both a file and a target. Thus both terms are of `BRIDGE_OPTIONAL`, and the walk reads both tables.
The changes of `workflows` name `mpbt:Finding`.

## The steps

1. `world_rows` walks the rows. `take_rows`, its visit, keeps the name of each target, and each file of `.github/workflows/<name>.yml`.
2. For each such file, `workflows_read_matrix` gives the names of its matrix.
3. A workflow with no name has no matrix, and gets no finding.
4. `workflows_check_targets` compares the names of each other workflow with the targets.

Each finding has the check `workflows`, and the path of its workflow.
`finding_write` and `finding_format` write the findings: `docs/intern/shared/finding/finding.h.md`.
No memory gives the status 1.

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | 0, or the status of the refusal. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_workflows` | 0, also after a finding. |
| `take_rows` | The targets of mpbt, and the workflows of the project, from the spans of the query. |
