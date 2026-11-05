# src/cover/cover.c

This file is the module `cover`. Its system finds the public names of each header of `include`, and looks for each one in the document of the header.
The message is in `docs/extern/mpbt_check.h.md`, *dup, cover and licence*.

## The manifest

`mpbt:cover@<version> abi=3 config=none pinned=false reloadable=false`

`<version>` is the version of mpbt. The module has no settings.

## The components

| Type | Written or read | Storage | `on_unload` |
| --- | --- | --- | --- |
| `mpbt:File` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Make` | Read | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |
| `mpbt:Finding` | Written | `BRIDGE_TABLE` | `BRIDGE_SWEEP` |

`world_declare` gives the slots 0, 1 and 2, in the order of the table. The descriptors come from `include/mpbt_file.h`, `include/mpbt_check.h` and `include/mpbt_finding.h`.

## The systems

| System | Phase | Terms | Changes |
| --- | --- | --- | --- |
| `cover` | `check` | `mpbt:File` and `mpbt:Make`: `BRIDGE_READ`, `BRIDGE_OPTIONAL`. | `mpbt:Finding` |

A file and a macro of `[check.makes]` are on different entities, so both terms are optional, and the walk reads each table.
The name `cover` comes from `CHECKS_NAMES`.

## The steps

1. `world_rows` gives each row of `mpbt:File` and each row of `mpbt:Make`.
2. `files_sort` puts the files in the order of their paths. Then `files_find` can find a document.
3. For each file of `include` whose name ends with `.h`, `cover_read_names` gives its public names.
4. `mirror_get_document` gives the 3 parts of the path of its document: `docs/intern/shared/mirror/mirror.h.md`, *mirror_t*.
5. The parts go into `document`, and `files_find` finds that path among the files.
6. `cover_get_spans` takes the code spans of that document, and `cover_is_named` looks for each name in them.

`finding_write` writes each finding. No memory gives the status 1.

## The findings

| Field | Value |
| --- | --- |
| `check` | `cover`. |
| `path` | The path of the header. |
| `text` | The rest of the message, after the header and its colon. |
| `line`, `column` | 0. |

## Functions

| Function | Result |
| --- | --- |
| `bridge_init` | Declares the 3 types, then the system `cover`. |
| `bridge_shutdown` | 0. The module holds nothing. |
| `bridge_reload` | The result of `bridge_init`. |
| `bridge_cover` | A finding for each public name that a document lacks. |
