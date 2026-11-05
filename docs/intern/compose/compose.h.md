# src/compose/compose.h

`compose.h` declares what the files of the module `compose` share: its types and its functions.

## compose_state_t

`compose_state_t` holds what the system reads in one call.

| Field | Value |
| --- | --- |
| `command` | The value of `mpbt:Command`. |
| `project` | The value of `mpbt:Project`. |
| `rows` | The rows of `mpbt:Variable`, `mpbt:Artifact`, `mpbt:Built`, `mpbt:Compose` and `mpbt:Part`, each with the id of its entity. |
| `fault` | The first fault, or no bytes. The system writes it with `finding_write`. |

## compose_deliverable_t

One deliverable of a run: of a part, or of the project.

| Field | Value |
| --- | --- |
| `part` | The row of `mpbt:Part`, or none for the project. |
| `name` | The name of its zips: `name` of the part, or `[project] name`. |

## compose_list_t

The files of one deliverable, in the order of their names: `docs/intern/compose/compose_list.c.md`.

| Field | Value |
| --- | --- |
| `files` | Each file: its name in `{dist}`, and the path of the file that it copies. |
| `count` | The count of the files. |

## Functions

| Function | File |
| --- | --- |
| `compose_declare` | `compose_world.c` |
| `compose_read_world` | `compose_world.c` |
| `compose_write_deliverable` | `compose_world.c` |
| `compose_write_package` | `compose_package.c` |
| `compose_get_deliverables` | `compose_deliverables.c` |
| `compose_get_files` | `compose_files.c` |
| `compose_add_file` | `compose_list.c` |
| `compose_remove_file` | `compose_list.c` |
