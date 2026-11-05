# src/compose/compose_deliverables.c

This file gives the deliverables of a run, as `docs/extern/mpbt_compose.h.md`, *[parts]*, tells.

## The deliverables

| The project | `--part` | The deliverables |
| --- | --- | --- |
| Has no parts. | None. | The deliverable of the project. |
| Has parts. | One or more. | The deliverable of each part of `--part`, in the order of the command line. |
| Has parts. | None. | One deliverable for each part, sorted by the name of the part. |

A part that only `uses` names gets no deliverable, since the command line does not name it.
`compose_write_package` refused a project with no name before. Thus the deliverable of the project always has a name.

## Functions

| Function | Result |
| --- | --- |
| `compose_get_deliverables` | The deliverables of the run. |
| `find_part` | The row of `mpbt:Part` with a given name. |
